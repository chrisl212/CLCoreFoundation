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

typedef enum
{
    file_size_type_bytes,
    file_size_type_kb,
    file_size_type_mb,
    file_size_type_gb
} file_size_type_t;

typedef struct
{
    long long byteSize;
    file_size_type_t sizeType;
} file_size_t;

typedef struct
{
    struct CLStringType *fileName;
    struct CLStringType *filePath;
    struct CLStringType *pathExtension;
    bool isDir;
    struct CLArrayType *directoryContents;
    struct CLArrayType *hiddenFiles;
    file_size_t fileSize;
} CLFileType;

CLFileType *CLFileWithPath(struct CLStringType *, CLErrorType **);

#endif
