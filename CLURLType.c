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
    CLStringType *path;
    CLStringType *type;
};

CLURLType *CLURLTypeCreateWithPath(CLStringType *str, CLURLRequestType t)
{
    CLURLType *url = calloc(1, sizeof(CLURLType));
    url->path = str;
    switch (t)
    {
        case CLURLTypeHTTP:
            url->type = CLStringTypeCreateWithCString("http");
            break;
            
        case CLURLTypeFile:
            url->type = CLStringTypeCreateWithCString("file");
            break;
            
        default:
            break;
    }
    return url;
}

CLURLType *CLURLTypeCreateWithString(CLStringType *s)
{
    CLURLType *url = calloc(1, sizeof(CLURLType));
    url->path = s;
    return url;
}

CLStringType *CLURLStringValue(CLURLType *url)
{
    CLStringType *str = url->path;
    return str;
}

CLStringType *CLURLTypeString(CLURLType *url)
{
    CLStringType *str = url->type;
    return str;
}