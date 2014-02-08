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
};

CLURLType *CLURLTypeCreateWithPath(CLStringType *str, CLURLRequestType t)
{
    CLStringType *string;
    switch (t)
    {
        case CLURLTypeHTTP:
            string = CLStringByAppendingString(str, CLStringTypeCreateWithCString("http://"));
            break;
            
        case CLURLTypeFile:
            string = CLStringByAppendingString(str, CLStringTypeCreateWithCString("file://"));
            break;
            
        default:
            break;
    }
    return CLURLTypeCreateWithString(string);
}

CLURLType *CLURLTypeCreateWithString(CLStringType *s)
{
    CLURLType *url = calloc(1, sizeof(CLURLType));
    url->path = CLStringCString(s);
    return url;
}
