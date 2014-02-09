//
//  CLURLType.c
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include <stdio.h>
#include "CLURLType.h"

struct CLURLType
{
    char *path;
    char *type;
};

CLURLType *CLURLTypeCreateWithPath(CLStringType *str, CLURLRequestType t)
{
    CLURLType *url = calloc(1, sizeof(CLURLType));
    url->path = CLStringCString(str);
    switch (t)
    {
        case CLURLTypeHTTP:
            url->type = "http";
            break;
            
        case CLURLTypeFile:
            url->type = "file";
            break;
            
        default:
            break;
    }
    return url;
}

CLURLType *CLURLTypeCreateWithString(CLStringType *s)
{
    CLURLType *url = calloc(1, sizeof(CLURLType));
    url->path = CLStringCString(s);
    return url;
}
