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
        while ((ent = readdir(d)) != NULL)
        {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;
            CLStringType *newPath = CLStringByAppendingString(path, CLStringTypeCreateWithCString(ent->d_name));
            CLMutableArrayTypeAddObject(tempArray, newPath);
        }
        file->directoryContents = CLMutableArrayImmutableCopy(tempArray);
        closedir(d);
    }
    else
    {
        FILE *f = fopen(CLStringCString(path), "r");
        extern char *CLCoreFoundationFileErrorDomain;
        if (!f)
        {
            *e = CLErrorWithDomainAndDescription(CLStringTypeCreateWithCString(CLCoreFoundationFileErrorDomain), CLStringTypeCreateWithCString(strerror(errno)));
            return NULL;
        }
        if (ferror(f))
        {
            *e = CLErrorWithDomainAndDescription(CLStringTypeCreateWithCString(CLCoreFoundationFileErrorDomain), CLStringTypeCreateWithCString(strerror(ferror(f))));
            return NULL;
        }
        fclose(f);
        
        file->isDir = false;
        file->pathExtension = CLStringPathExtension(path);
        file->directoryContents = NULL;
    }
    return file;
}
