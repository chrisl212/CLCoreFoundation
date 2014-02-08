//
//  CLStringType.c
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include "CLStringType.h"

struct CLStringType
{
    char *str;
    CLStringTypeEncoding encoding;
};

CLStringType *CLStringTypeCreate()
{
    CLStringType *str = calloc(1, sizeof(CLStringType));
    str->str = "";
    str->encoding = CLStringTypeEncodingUTF8;
    return str;
}

CLStringType *CLStringTypeCreateWithCString(const char *string)
{
    CLStringType *str = CLStringTypeCreate();
    char *dup = strdup(string);
    str->str = dup;
    return str;
}

CLStringType *CLStringTypeCreateWithContentsOfPath(const char *path)
{
    FILE *f = fopen(path, "r");
    CLStringType *str = CLStringTypeCreateWithContentsOfFile(f);
    fclose(f);
    return str;
}

CLStringType *CLStringTypeCreateWithContentsOfFile(FILE *f)
{
    CLStringType *str = calloc(1, sizeof(CLStringType));
    str->encoding = CLStringTypeEncodingUTF8;
    fseek(f, 0L, SEEK_END);
    long long fsize = ftell(f);
    fseek(f, 0L, SEEK_SET);
    char *buf = malloc(sizeof(char) * fsize);
    fread(buf, fsize, 1, f);
    str->str = strdup(buf);
    free(buf);
    return str;
}

CLStringType *CLStringCopy(CLStringType *string)
{
    CLStringType *newstr = calloc(1, sizeof(CLStringType));
    newstr->encoding = string->encoding;
    newstr->str = strdup(string->str);
    return newstr;
}

CLStringType *CLStringByAppendingString(CLStringType *s1, CLStringType *s2)
{
    char *newstr = strdup(s1->str);
    strcat(newstr, s2->str);
    CLStringType *str = CLStringTypeCreateWithCString(newstr);
    return str;
}

bool _clstrcmp(const char *s1, const char *s2)
{
    size_t s1len = strlen(s1);
    size_t s2len = strlen(s2);
    if (s1len != s2len)
        return false;
    for (int i = 0; i < s1len; i++)
        if (s1[i] != s2[i])
            return false;
    return true;
}

bool CLStringCompare(CLStringType *str1, CLStringType *str2)
{
    return _clstrcmp(str1->str, str2->str);
}

char *CLStringCString(CLStringType *str)
{
    return strdup(str->str);
}
