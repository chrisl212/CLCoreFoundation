//
//  CLFileType.c
//  CLCoreFoundation
//
//  Created by Chris on 2/15/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include "CLFileType.h"
#include "CLStringType.h"
#include "CLErrorType.h"
#include "CLArrayType.h"

CLFileType *CLFileWithPath(CLStringType *path, CLErrorType **e)
{
    if (!path || CLStringLength(path) == 0)
        return NULL;
    
    char *dname = CLStringCString(path);
    DIR *d = opendir(dname);
    
    CLFileType *file = calloc(1, sizeof(CLFileType));
    file->fileName = CLStringLastPathComponent(path);
    file->filePath = path;
    if (d)
    {
        path = CLStringByAppendingString(path, CLStringTypeCreateWithCString("/"));
        file->isDir = true;
        struct dirent *ent;
        CLMutableArrayType *tempArray = CLMutableArrayTypeCreateWithObjects(NULL);
        CLMutableArrayType *hiddenTemp = CLMutableArrayTypeCreateWithObjects(NULL);
        while ((ent = readdir(d)) != NULL)
        {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;
            bool isHidden = false;
            if (ent->d_name[0] == '.')
                isHidden = true;
            CLStringType *newPath = CLStringByAppendingString(path, CLStringTypeCreateWithCString(ent->d_name));
            if (!isHidden)
                CLMutableArrayTypeAddObject(tempArray, newPath);
            else
                CLMutableArrayTypeAddObject(hiddenTemp, newPath);
        }
        file->hiddenFiles = CLMutableArrayImmutableCopy(hiddenTemp);
        file->directoryContents = CLMutableArrayImmutableCopy(tempArray);
        closedir(d);
    }
    else
    {
        FILE *f = fopen(CLStringCString(path), "rb");
        extern char *CLCoreFoundationFileErrorDomain;
        if (!f)
        {
            *e = CLErrorWithDomainAndDescription(CLStringTypeCreateWithCString(CLCoreFoundationFileErrorDomain), CLStringTypeCreateWithCString(strerror(errno)));
            fclose(f);
            return NULL;
        }
        if (ferror(f))
        {
            *e = CLErrorWithDomainAndDescription(CLStringTypeCreateWithCString(CLCoreFoundationFileErrorDomain), CLStringTypeCreateWithCString(strerror(ferror(f))));
            return NULL;
        }
        fseek(f, 0L, SEEK_END);
        long sz = ftell(f);
        fseek(f, 0L, SEEK_SET);
        fclose(f);
        
        file->isDir = false;
        file->pathExtension = CLStringPathExtension(path);
        file->directoryContents = NULL;
        file->fileSize.byteSize = sz;
        if ((sz/1024.0) >= 1)
            file->fileSize.sizeType = file_size_type_kb;
        else
            file->fileSize.sizeType = file_size_type_bytes;
        if ((sz/1024.0/1024.0) >= 1)
            file->fileSize.sizeType = file_size_type_mb;
        if ((sz/1024.0/1024.0/1024.0) >= 1)
            file->fileSize.sizeType = file_size_type_gb;
    }
    return file;
}
