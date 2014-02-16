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
    CLStringType *path;
    CLStringType *type;
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

    CLMutableArrayType *comps = CLStringComponentsSeparatedByString(url->path, CLStringTypeCreateWithCString("/"));
    CLStringType *baseServer = CLMutableArrayObjectAtIndex(comps, 0);
    
    size_t count = CLMutableArrayTypeCount(comps);
    CLStringType *restOfURL = CLStringTypeCreate();
    int i = 1;
    for (; i < count; i++)
    {
        restOfURL = CLStringByAppendingString(restOfURL, CLMutableArrayObjectAtIndex(comps, i));
    }
    
    
	if ((rv = getaddrinfo(CLStringCString(baseServer), CLStringCString(url->type), &hints, &servinfo)) != 0) {
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
    
	freeaddrinfo(servinfo); // all done with this structure
    
    char request[300];
    sprintf(request, "GET /%s HTTP/1.1\r\nHost:%s\r\n\r\n", CLStringCString(restOfURL), CLStringCString(baseServer));
    send(sockfd, request, strlen(request), 0);
    
    FILE *temp = tmpfile();
    
    char *buf = malloc(400);
    while ((numbytes = (int)recv(sockfd, buf, 400, 0)) > 0)
    {
        fwrite(buf, 1, numbytes, temp);
    }
    
    fseek(temp, 0L, SEEK_END);
    long size = ftell(temp);
    fseek(temp, 0L, SEEK_SET);
    char *newBuf = malloc(size);
    fread(newBuf, 1, size, temp);
    fclose(temp);
    
    close(sockfd);
    retval = CLStringTypeCreateWithCString(newBuf);
    return retval;
}
