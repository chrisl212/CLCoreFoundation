//
//  CLErrorType.c
//  CLCoreFoundation
//
//  Created by Chris on 2/14/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include "CLErrorType.h"

struct CLErrorType
{
    int domain;
    CLStringType *description;
};

CLErrorType *CLErrorWithDomainAndDescription(int d, CLStringType *s)
{
    CLErrorType *err = calloc(1, sizeof(CLErrorType));
    err->description = s;
    err->domain = d;
    return err;
}

void CLErrorRelease(CLErrorType *err)
{
    free(err);
}