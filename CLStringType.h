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
bool CLStringCompare(CLStringType *, CLStringType *);
const char *CLStringCString(CLStringType *);