//
//  CLFileType.h
//  CLCoreFoundation
//
//  Created by Chris on 2/15/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include "CLErrorType.h"

#ifndef CLCoreFoundation_CLFileType_h
#define CLCoreFoundation_CLFileType_h

struct CLStringType;
struct CLArrayType;

typedef struct
{
    struct CLStringType *fileName;
    struct CLStringType *filePath;
    struct CLStringType *pathExtension;
    bool isDir;
    struct CLArrayType *directoryContents;
    struct CLArrayType *hiddenFiles;
} CLFileType;

CLFileType *CLFileWithPath(struct CLStringType *, CLErrorType **);

#endif
