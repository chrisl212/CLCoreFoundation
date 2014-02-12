//
//  CLMutableArrayType.h
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdlib.h>
#include "CLArrayType.h"

#ifndef CLCoreFoundation_CLMutableArrayType_h
#define CLCoreFoundation_CLMutableArrayType_h

typedef struct CLMutableArrayType CLMutableArrayType;

CLMutableArrayType *CLMutableArrayTypeCreateWithObjects(void *, ...);
CLMutableArrayType *CLMutableArrayTypeCreateWithList(void *, va_list, int);
CLArrayType *CLMutableArrayImmutableCopy(CLMutableArrayType *);
int CLMutableArrayTypeCount(CLMutableArrayType *);
void *CLMutableArrayObjectAtIndex(CLMutableArrayType *, int);
void CLMutableArrayTypeAddObject(CLMutableArrayType *, void *);
bool CLMutableArrayContainsObject(CLMutableArrayType *, void *);
CLMutableArrayType *CLMutableArrayCopy(CLMutableArrayType *);
void CLMutableArrayRelease(CLMutableArrayType *);

#endif
