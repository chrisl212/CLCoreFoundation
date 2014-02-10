//
//  ACURLType.h
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include "CLStringType.h"

#ifndef CLCoreFoundation_CLURLType_h
#define CLCoreFoundation_CLURLType_h

typedef struct CLURLType CLURLType;

typedef enum
{
    CLURLTypeHTTP,
    CLURLTypeFile
} CLURLRequestType;

CLURLType *CLURLTypeCreateWithPath(CLStringType *, CLURLRequestType);
CLURLType *CLURLTypeCreateWithString(CLStringType *);
CLStringType *CLURLStringValue(CLURLType *);
CLStringType *CLURLTypeString(CLURLType *);

#endif
