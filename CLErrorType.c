//
//  CLErrorType.c
//  CLCoreFoundation
//
//  Created by Chris on 2/14/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include "CLStringType.h"

CLErrorType *CLErrorWithDomainAndDescription(CLStringType *d, CLStringType *s)
{
    CLErrorType *err = calloc(1, sizeof(CLErrorType));
    err->description = s;
    err->domain = d;
    return err;
}

struct CLStringType *CLErrorString(CLErrorType *err)
{
    CLStringType *fmt = CLStringTypeCreateWithCString("Error: %s - %s\n");
    CLStringType *errorString = CLStringWithFormat(fmt, err->domain, err->description);
    return errorString;
}

void CLErrorRelease(CLErrorType *err)
{
    free(err);
}

void CLErrorPrint(CLErrorType *err)
{
    printf("Error: %s - %s\n", CLStringCString(err->domain), CLStringCString(err->description));
}