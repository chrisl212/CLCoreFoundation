//
//  CLDataType.c
//  CLCoreFoundation
//
//  Created by Chris on 2/15/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include <errno.h>
#include "CLErrorType.h"
#include "CLStringType.h"

struct CLDataType
{
    char *bytes;
    size_t length;
};

struct CLDataType *CLDataWithContentsOfFile(CLStringType *s, CLErrorType **e)
{
    char *filePath = CLStringCString(s);
    FILE *f = fopen(filePath, "r");
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
    size_t len;
    fseek(f, 0L, SEEK_END);
    len = ftell(f);
    fseek(f, 0L, SEEK_SET);
    struct CLDataType *data = calloc(1, sizeof(struct CLDataType));
    data->length = len;
    char *bytes = malloc(len);
    fread(bytes, 1, len, f);
    data->bytes = bytes;
    return data;
}

struct CLDataType *CLDataWithBytes(void *b)
{
    struct CLDataType *data = calloc(1, sizeof(struct CLDataType));
    if (!b)
    {
        data->length = 0;
        data->bytes = "";
        return data;
    }
    data->bytes = strdup(b);
    data->length = sizeof(b);
    return data;
}

void CLDataAppendData(struct CLDataType *d, struct CLDataType *d2)
{
    char *newData = malloc(d->length + d2->length + 1);
    strcpy(newData, d->bytes);
    strcat(newData, d2->bytes);
    newData[d->length + d2->length + 1] = '\0';
    d->bytes = newData;
}

void *CLDataBytes(struct CLDataType *d)
{
    return d->bytes;
}

size_t CLDataLength(struct CLDataType *d)
{
    return d->length;
}

CLStringType *CLDataStringRepresentation(struct CLDataType *d)
{
    return CLStringTypeCreateWithCString(d->bytes);
}