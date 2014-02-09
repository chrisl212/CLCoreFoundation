//
//  CLInternetRequest.c
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "CLInternetRequest.h"

#define PORT 80

struct CLURLType
{
    char *path;
    char *type;
};

struct CLStringType
{
    char *str;
    CLStringTypeEncoding encoding;
};

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
    
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

CLStringType *CLInternetRequestContentsOfURL(CLURLType *url)
{
    CLStringType *retval = NULL;
    
    int sockfd, numbytes;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
    
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

    CLMutableArrayType *comps = CLStringComponentsSeparatedByString(CLStringTypeCreateWithCString(url->path), CLStringTypeCreateWithCString("/"));
    CLStringType *baseServer = CLMutableArrayObjectAtIndex(comps, 0);
    
    int count = CLMutableArrayTypeCount(comps);
    CLStringType *restOfURL = CLStringTypeCreate();
    for (int i = 1; i < count; i++)
    {
        restOfURL = CLStringByAppendingString(restOfURL, CLMutableArrayObjectAtIndex(comps, i));
    }
    
    
	if ((rv = getaddrinfo(CLStringCString(baseServer), url->type, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));

	}
    
	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}
        
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}
        
		break;
	}
    
	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");

	}
    
	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
              s, sizeof s);
	printf("client: connecting to %s\n", s);
    
	freeaddrinfo(servinfo); // all done with this structure
    
    char request[300];
    sprintf(request, "GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n", CLStringCString(restOfURL), CLStringCString(baseServer));
    send(sockfd, request, strlen(request), 0);
    char *buf = malloc(400);
    if ((numbytes = (int)recv(sockfd, buf, 400 - 1, 0)) == -1) {
	    perror("recv");
	    exit(1);
	}
    CLStringType *headerstr = CLStringTypeCreateWithCString(buf);
    //free(buf);
    
    CLMutableArrayType *headerandbody = CLStringComponentsSeparatedByString(headerstr, CLStringTypeCreateWithCString("\r\n\r\n"));
    CLStringType *headerString = CLMutableArrayObjectAtIndex(headerandbody, 0);
    CLMutableArrayType *headers = CLStringComponentsSeparatedByString(headerString, CLStringTypeCreateWithCString("\r\n"));
    
    int header_count = CLMutableArrayTypeCount(headers);
    long long contentlength = 0;
    CLStringType *chk = CLStringTypeCreateWithCString("Content-Length");
    for (int i = 0; i < header_count; i++)
    {
        CLStringType *header = CLMutableArrayObjectAtIndex(headers, i);
        if (header->str && CLStringContainsString(header, chk))
        {
            CLMutableArrayType *comps = CLStringComponentsSeparatedByString(header, CLStringTypeCreateWithCString(":"));
            const char *lengthstr = CLStringCString(CLStringByRemovingWhiteSpace(CLMutableArrayObjectAtIndex(comps, 1)));
            contentlength = strtoll(lengthstr, NULL, 0);
        }
    }
    free(buf);
    if (contentlength > 0)
    {
        buf = malloc(contentlength);
        if ((numbytes = (int)recv(sockfd, buf, contentlength - 1, 0)) == -1) {
            perror("recv");
            exit(1);
        }
        
        buf[numbytes] = '\0';
    }
    else
    {
        buf = malloc(2000);
        if ((numbytes = (int)recv(sockfd, buf, 2000 - 1, 0)) == -1) {
            perror("recv");
            exit(1);
        }
        
        buf[numbytes] = '\0';
    }

    
	printf("client: received '%s'\n", buf);
    
	close(sockfd);
    retval = CLStringTypeCreateWithCString(buf);
    return retval;
}
