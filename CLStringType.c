//
//  CLStringType.c
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include "CLStringType.h"
#include <math.h>
#include <ctype.h>

char *CLCoreFoundationFileErrorDomain = "File Error";

struct CLMutableArrayType
{
    size_t count;
    void **objs;
};

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

CLStringType *CLStringTypeCreateWithContentsOfPath(const char *path, CLErrorType **e)
{
    FILE *f = fopen(path, "r");
    CLStringType *str = CLStringTypeCreateWithContentsOfFile(f, e);
    fclose(f);
    return str;
}

CLStringType *CLStringTypeCreateWithContentsOfFile(FILE *f, CLErrorType **e)
{
    CLStringType *str = calloc(1, sizeof(CLStringType));
    str->encoding = CLStringTypeEncodingUTF8;
    
    if (!f)
    {
        char *err = "File does not exist";
        extern char *CLCoreFoundationFileErrorDomain;
        *e = CLErrorWithDomainAndDescription(CLStringTypeCreateWithCString(CLCoreFoundationFileErrorDomain), CLStringTypeCreateWithCString(err));
        free(str);
        return NULL;
    }
    if (ferror(f) != 0)
    {
        char *err = strerror(ferror(f));
        extern char *CLCoreFoundationFileErrorDomain;
        *e = CLErrorWithDomainAndDescription(CLStringTypeCreateWithCString(CLCoreFoundationFileErrorDomain), CLStringTypeCreateWithCString(err));
        free(str);
        return NULL;
    }
    
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
    char *newstr = malloc(strlen(s1->str) + strlen(s2->str) + 1);
    strcpy(newstr, s1->str);
    strcat(newstr, s2->str);
    CLStringType *str = CLStringTypeCreateWithCString(newstr);
    return str;
}

CLMutableArrayType *CLStringComponentsSeparatedByString(CLStringType *str, CLStringType *delimit)
{
    CLMutableArrayType *retval = CLMutableArrayTypeCreateWithObjects(NULL);
    
    char *s = CLStringCString(str);
    char *sv;
    char *s1 = strtok_r(s, delimit->str, &sv);
    while (s1 != NULL)
    {
        CLStringType *newstr = CLStringTypeCreateWithCString(s1);
        CLMutableArrayTypeAddObject(retval, newstr);
        s1 = strtok_r(NULL, delimit->str, &sv);
    }
    
    return retval;
}

CLStringType *CLStringByRemovingWhiteSpace(CLStringType *str)
{
    const char *s = strdup(str->str);
    char *p = (char *)s;
    char ch = ' ';
    while (*s) {
        if (*s != ch)
            *p++ = *s;
        
        s++;
    }
    *p = 0;
    return CLStringTypeCreateWithCString(p);
}

CLStringType *CLStringByReplacingFirstStringWithString(CLStringType *str, CLStringType *s1, CLStringType *s2)
{
    char *orig, *rep, *with;
    orig = str->str;
    rep = s1->str;
    with = s2->str;
    char *result;
    char *ins;
    char *tmp;
    size_t len_rep, len_with, len_front;

    
    if (!(ins = strstr(orig, rep)))
        return NULL;
    
    len_rep = strlen(rep);
    len_with = strlen(with);
    len_front = ins - orig;
    result = malloc(strlen(orig) + len_with - len_rep + 1);
    tmp = strncpy(result, orig, len_front) + len_front;
    tmp = strcpy(tmp, with) + len_with;
    strcpy(tmp, ins + len_rep);
    return CLStringTypeCreateWithCString(result);
}

CLStringType *CLStringByReplacingStringsWithString(CLStringType *str, CLStringType *s1, CLStringType *s2)
{
	char *ret, *r;
	const char *p, *q;
    const char *string = str->str;
    const char *old, *new;
    old = s1->str;
    new = s2->str;
	size_t oldlen = strlen(old);
	size_t count, retlen, newlen = strlen(new);
    
	if (oldlen != newlen) {
		for (count = 0, p = string; (q = strstr(p, old)) != NULL; p = q + oldlen)
			count++;
		/* this is undefined if p - str > PTRDIFF_MAX */
		retlen = p - string + strlen(p) + count * (newlen - oldlen);
	} else
		retlen = strlen(string);
    
	if ((ret = malloc(retlen + 1)) == NULL)
		return NULL;
    
	for (r = ret, p = string; (q = strstr(p, old)) != NULL; p = q + oldlen) {
		signed long l = q - p;
		memcpy(r, p, l);
		r += l;
		memcpy(r, new, newlen);
		r += newlen;
	}
	strcpy(r, p);
    
    return CLStringTypeCreateWithCString(ret);
}

CLStringType *CLStringWithFormat(CLStringType *fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    CLStringType *final = CLStringWithListFormat(fmt, list);
    va_end(list);
    return final;
}

CLStringType *CLStringWithListFormat(CLStringType *fmt, va_list lst)
{
    CLStringType *str = calloc(1, sizeof(CLStringType));
    str->encoding = CLStringTypeEncodingUTF8;
    str->str = malloc(pow(strlen(fmt->str), 2));
    vsprintf(str->str, fmt->str, lst);
    return str;
}

CLStringType *CLStringUppercaseString(CLStringType *s)
{
    CLStringType *str = CLStringTypeCreate();
    str->str = strdup(s->str);
    size_t len = CLStringLength(str);
    int i = 0;
    for (; i < len; i++)
    {
        str->str[i] = toupper(str->str[i]);
    }
    return str;
}

CLStringType *CLStringLowercaseString(CLStringType *s)
{
    CLStringType *str = CLStringTypeCreate();
    str->str = strdup(s->str);
    size_t len = CLStringLength(str);
    int i = 0;
    for (; i < len; i++)
    {
        str->str[i] = tolower(str->str[i]);
    }
    return str;
}

bool _clstrcmp(const char *s1, const char *s2)
{
    size_t s1len = strlen(s1);
    size_t s2len = strlen(s2);
    if (s1len != s2len)
        return false;
    int i = 0;
    for (; i < s1len; i++)
        if (s1[i] != s2[i])
            return false;
    return true;
}

bool CLStringCompare(CLStringType *str1, CLStringType *str2)
{
    return _clstrcmp(str1->str, str2->str);
}

bool CLStringContainsString(CLStringType *s1, CLStringType *s2)
{
    if (!s1 || !s2)
        return false;
    if (strstr(s1->str, s2->str))
        return true;
    return false;
}

char *CLStringCString(CLStringType *str)
{
    return strdup(str->str);
}

char **CLStringOccurencesOfString(CLStringType *str, CLStringType *occ)
{
    CLMutableArrayType *final = CLMutableArrayTypeCreateWithObjects(NULL);
    char *string = str->str;
    char *sub = occ->str;
    size_t len = strlen(occ->str);
    char *c, *f;
    c = strstr(string, sub);
    f = "";
    while (c && strcmp(c, f) != 0)
    {
        f = strdup(c);
        CLMutableArrayTypeAddObject(final, c);
        string += len;
        c = strstr(string, sub);
    }
    return (char **)final->objs;
}

int CLStringLength(CLStringType *str)
{
    return (int)strlen(str->str);
}