//
//  CLStringType.h
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "CLMutableArrayType.h"

#ifndef CLStringType_h
#define CLStringType_h

typedef struct CLStringType CLStringType;
typedef enum
{
    CLStringTypeEncodingASCII,
    CLStringTypeEncodingUTF8,
    CLStringTypeEncodingUnicode
} CLStringTypeEncoding;

CLStringType *CLStringTypeCreate();
CLStringType *CLStringTypeCreateWithCString(const char *);
CLStringType *CLStringTypeCreateWithContentsOfPath(const char *);
CLStringType *CLStringTypeCreateWithContentsOfFile(FILE *);
CLStringType *CLStringCopy(CLStringType *);
CLStringType *CLStringByAppendingString(CLStringType *, CLStringType *);
CLStringType *CLStringByRemovingWhiteSpace(CLStringType *);
CLStringType *CLStringByReplacingStringsWithString(CLStringType *, CLStringType *);
CLMutableArrayType *CLStringComponentsSeparatedByString(CLStringType *, CLStringType *);
bool CLStringCompare(CLStringType *, CLStringType *);
bool CLStringContainsString(CLStringType *, CLStringType *);
char *CLStringCString(CLStringType *);
int CLStringLength(CLStringType *);

#endif