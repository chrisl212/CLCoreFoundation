//
//  CLArrayType.h
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <memory.h>

#ifndef CLArrayType_h
#define CLArrayType_h

typedef struct CLArrayType CLArrayType;

CLArrayType *CLArrayTypeCreateWithObjects(void *, ...);
CLArrayType *CLArrayTypeCreateWithList(void *, va_list, int);
void *CLArrayTypeMutableCopy(CLArrayType *);
size_t CLArrayTypeCount(CLArrayType *);
void *CLArrayObjectAtIndex(CLArrayType *, int);
bool CLArrayContainsObject(CLArrayType *, void *);
CLArrayType *CLArrayCopy(CLArrayType *);
void CLArrayRelease(CLArrayType *);

#endif