//
//  CLDataType.h
//  CLCoreFoundation
//
//  Created by Chris on 2/15/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include <stdio.h>

#ifndef CLCoreFoundation_CLDataType_h
#define CLCoreFoundation_CLDataType_h

struct CLErrorType;
struct CLStringType;
typedef struct CLDataType CLDataType;

CLDataType *CLDataWithContentsOfFile(struct CLStringType *, struct CLErrorType **);
void *CLDataBytes(CLDataType *);
size_t CLDataLength(CLDataType *);
struct CLStringType *CLDataStringRepresentation(CLDataType *);

#endif
