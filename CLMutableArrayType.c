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
    void **objs;
};

struct CLArrayType
{
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
    for (int i = 1; i < count; i++)
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
    for (int i = 1; i < count; i++)
    {
        retval->objs[i] = va_arg(list, void *);
    }
    
    return retval;
}

CLArrayType *CLMutableArrayImmutableCopy(CLMutableArrayType *arr)
{
    CLArrayType *array = CLArrayTypeCreateWithObjects(NULL);
    int count = CLMutableArrayTypeCount(arr);
    array->objs = malloc(100 * count);
    for (int i = 0; i < count; i++)
    {
        array->objs[i] = arr->objs[i];
    }
    return array;
}

int CLMutableArrayTypeCount(CLMutableArrayType *arr)
{
    if (!arr->objs)
        return 0;
    int c = 0;
    for (; arr->objs[c] != NULL; c++);
    return c;
}

void *CLMutableArrayObjectAtIndex(CLMutableArrayType *arr, int ind)
{
    void *o = arr->objs[ind];
    if (o)
        return o;
    else
        perror("Attempt to access NULL object or index out of bounds."), abort();
}

void CLMutableArrayTypeAddObject(CLMutableArrayType *arr, void *o)
{
    int count = CLMutableArrayTypeCount(arr);
    void **newobjs = malloc(100 * (count + 1));
    int i;
    for (i = 0; i < count; i++)
    {
        newobjs[i] = arr->objs[i];
    }
    newobjs[i] = o;
    arr->objs = newobjs;
}
