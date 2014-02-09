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

#ifndef CLArrayType_h
#define CLArrayType_h

typedef struct CLArrayType CLArrayType;

CLArrayType *CLArrayTypeCreateWithObjects(void *, ...);
CLArrayType *CLArrayTypeCreateWithList(void *, va_list, int);
int CLArrayTypeCount(CLArrayType *);
void *CLArrayObjectAtIndex(CLArrayType *, int);

#endif