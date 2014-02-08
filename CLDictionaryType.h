//
//  CLDictionaryType.h
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "CLStringType.h"
#include "CLArrayType.h"

#ifndef CLDictionaryType_h
#define CLDictionaryType_h

typedef struct CLDictionaryType CLDictionaryType;

CLDictionaryType *CLDictionaryTypeCreateWithObjectsAndKeys(CLArrayType *, CLArrayType *);
void *CLDictionaryTypeObjectForKey(CLDictionaryType *, CLStringType *);

#endif