//
//  CLErrorType.h
//  CLCoreFoundation
//
//  Created by Chris on 2/14/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#ifndef CLCoreFoundation_CLErrorType_h
#define CLCoreFoundation_CLErrorType_h

typedef struct CLErrorType CLErrorType;
struct CLStringType;

CLErrorType *CLErrorWithDomainAndDescription(struct CLStringType *, struct CLStringType *);
void CLErrorRelease(CLErrorType *);

#endif
