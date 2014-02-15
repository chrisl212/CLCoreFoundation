//
//  CLErrorType.h
//  CLCoreFoundation
//
//  Created by Chris on 2/14/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#ifndef CLCoreFoundation_CLErrorType_h
#define CLCoreFoundation_CLErrorType_h

struct CLStringType;

typedef struct
{
    struct CLStringType *domain;
    struct CLStringType *description;
} CLErrorType;

CLErrorType *CLErrorWithDomainAndDescription(struct CLStringType *, struct CLStringType *);
struct CLStringType *CLErrorString(CLErrorType *);
void CLErrorRelease(CLErrorType *);
void CLErrorPrint(CLErrorType *);

#endif
