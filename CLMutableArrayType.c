//
//  CLMutableArrayType.c
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include "CLMutableArrayType.h"
#include "CLArrayType.h"

struct CLMutableArrayType
{
    size_t count;
    void **objs;
};

struct CLArrayType
{
    size_t count;
    void **objs;
};

CLMutableArrayType *CLMutableArrayTypeCreateWithObjects(void *o, ...)
{
    CLMutableArrayType *retval = calloc(1, sizeof(CLMutableArrayType));
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
    retval->objs = malloc(100 * count);
    retval->objs[0] = o;
    int i = 1;
    for (; i < count; i++)
    {
        retval->objs[i] = va_arg(list, void *);
    }
    va_end(list);
    
    return retval;
}

CLMutableArrayType *CLMutableArrayTypeCreateWithList(void *o, va_list list, int count)
{
    CLMutableArrayType *retval = calloc(1, sizeof(CLMutableArrayType));
    if (!o)
        return retval;
    
    retval->objs = malloc(100 * count);
    retval->objs[0] = o;
    int i = 1;
    for (; i < count; i++)
    {
        retval->objs[i] = va_arg(list, void *);
    }
    
    return retval;
}

CLArrayType *CLMutableArrayImmutableCopy(CLMutableArrayType *arr)
{
    CLArrayType *array = CLArrayTypeCreateWithObjects(NULL);
    size_t count = CLMutableArrayTypeCount(arr);
    array->objs = malloc(100 * count);
    array->count = arr->count;
    int i = 0;
    for (; i < count; i++)
    {
        array->objs[i] = arr->objs[i];
    }
    return array;
}

size_t CLMutableArrayTypeCount(CLMutableArrayType *arr)
{
    return arr->count;
}

void *CLMutableArrayObjectAtIndex(CLMutableArrayType *arr, int ind)
{
    size_t max = CLMutableArrayTypeCount(arr) - 1;
    if (ind > max)
        fputs("Index out of bounds", stderr);
    void *o = arr->objs[ind];
    if (o)
        return o;
    else
        fputs("Attempt to access NULL object", stderr);
    return o;
}

void CLMutableArrayTypeInsertObjectAtIndex(CLMutableArrayType *arr, void *o, int ind)
{
    if (!o)
    {
        fputs("Attempt to insert a NULL object into an array.", stderr);
        return;
    }
    size_t count = CLMutableArrayTypeCount(arr);
    void **newobjs = malloc(100 * (count + 1));
    int i;
    for (i = 0; i < count; i++)
    {
        if (i == ind)
        {
            newobjs[i] = o;
            continue;
        }
        newobjs[i] = arr->objs[i];
    }
    arr->objs = newobjs;
    arr->count++;
}

void CLMutableArrayTypeRemoveObjectAtIndex(CLMutableArrayType *arr, int ind)
{
    size_t count = CLMutableArrayTypeCount(arr);
    if (ind >= count)
    {
        fputs("Index out of bounds", stderr);
    }
    void **newobjs = malloc(100 * (count - 1));
    int i, newI;
    for (i = 0, newI = 0; i < count; i++, newI++)
    {
        if (i == ind)
        {
            newI--;
            continue;
        }
        newobjs[newI] = arr->objs[i];
    }
    arr->objs = newobjs;
    arr->count--;
}

void CLMutableArrayTypeAddObject(CLMutableArrayType *arr, void *o)
{
    CLMutableArrayTypeInsertObjectAtIndex(arr, o, 0);
}

bool CLMutableArrayContainsObject(CLMutableArrayType *a, void *o)
{
    int i = 0;
    size_t count = CLMutableArrayTypeCount(a);
    for (; i < count; i++)
    {
        if (CLMutableArrayObjectAtIndex(a, i) == o)
            return true;
    }
    return false;
}

CLMutableArrayType *CLMutableArrayCopy(CLMutableArrayType *a)
{
    size_t count = CLMutableArrayTypeCount(a) - 1;
    int i = 0;
    CLMutableArrayType *arr = calloc(1, sizeof(CLMutableArrayType));
    arr->objs = calloc(count + 1, 100);
    for (; i < count; i++)
    {
        void *np = malloc(sizeof(a->objs[i]));
        memcpy(np, a->objs[i], sizeof(a->objs[i]));
        arr->objs[i] = np;
    }
    return arr;
}

void CLMutableArrayRelease(CLMutableArrayType *a)
{
    free(a->objs);
    free(a);
}
