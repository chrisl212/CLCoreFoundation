//
//  CLErrorType.h
//  CLCoreFoundation
//
//  Created by Chris on 2/14/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include <stdio.h>
#include "CLStringType.h"

#ifndef CLCoreFoundation_CLErrorType_h
#define CLCoreFoundation_CLErrorType_h

typedef struct CLErrorType CLErrorType;

CLErrorType *CLErrorWithDomainAndDescription(CLStringType *, CLStringType *);
void CLErrorRelease(CLErrorType *);

#endif
