//
//  CLArrayType.c
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include "CLArrayType.h"
#include "CLMutableArrayType.h"
#include <memory.h>

struct CLArrayType
{
    size_t count;
    void **objs;
};

struct CLMutableArrayType
{
    size_t count;
    void **objs;
};

CLArrayType *CLArrayTypeCreateWithObjects(void *o, ...)
{
    CLArrayType *retval = calloc(1, sizeof(CLArrayType));
    if (!o)
        return retval;
    va_list list;
    va_start(list, o);
    int count = 1;
    while (va_arg(list, void *) != NULL)
    {
        count++;
    }
    va_end(list);
    va_start(list, o);
    retval->objs = malloc(100 + (100 * count));
    retval->objs[0] = o;
    int i = 1;
    for (; i < count; i++)
    {
        retval->objs[i] = va_arg(list, void *);
    }
    va_end(list);
    retval->count = count;
    return retval;
}

CLArrayType *CLArrayTypeCreateWithList(void *o, va_list list, int count)
{
    CLArrayType *retval = calloc(1, sizeof(CLArrayType));
    if (!o)
        return retval;

    retval->objs = malloc(100 + (100 * count));
    retval->objs[0] = o;
    int i = 1;
    for (; i < count; i++)
    {
        retval->objs[i] = (void *)va_arg(list, void *);
    }
    retval->count = count;

    return retval;
}

void *CLArrayTypeMutableCopy(CLArrayType *a)
{
    CLMutableArrayType *arr = calloc(1, sizeof(CLMutableArrayType));
    size_t count = CLArrayTypeCount(a);
    arr->objs = calloc(count, 100);
    int i = 0;
    for (; i < count; i++)
    {
        arr->count++;
        arr->objs[i] = a->objs[i];
        //memcpy(arr->objs[i], a->objs[i], strlen(a->objs[i]));
    }
    return arr;
}

size_t CLArrayTypeCount(CLArrayType *a)
{
    return a->count;
}

void *CLArrayObjectAtIndex(CLArrayType *arr, int ind)
{
    size_t max = CLArrayTypeCount(arr) - 1;
    if (ind > max)
        fputs("Index out of bounds", stderr);
    void *o = arr->objs[ind];
    if (o)
        return o;
    else
        fputs("Attempt to access NULL object", stderr);
    return o;
}

bool CLArrayContainsObject(CLArrayType *arr, void *o)
{
    int i = 0;
    size_t count = CLArrayTypeCount(arr) - 1;
    for (; i < count; i++)
    {
        if (CLArrayObjectAtIndex(arr, i) == o)
            return true;
    }
    return false;
}

CLArrayType *CLArrayCopy(CLArrayType *a)
{
    size_t count = CLArrayTypeCount(a) - 1;
    int i = 0;
    CLArrayType *arr = calloc(1, sizeof(CLArrayType));
    arr->objs = calloc(count + 1, 100);
    for (; i < count; i++)
    {
        void *np = malloc(sizeof(a->objs[i]));
        memcpy(np, a->objs[i], sizeof(a->objs[i]));
        arr->objs[i] = np;
    }
    return arr;
}

void CLArrayRelease(CLArrayType *a)
{
    free(a->objs);
    free(a);
}