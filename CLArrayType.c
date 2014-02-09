//
//  CLArrayType.c
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include "CLArrayType.h"

struct CLArrayType
{
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
    retval->objs = malloc(100 * count);
    retval->objs[0] = o;
    for (int i = 1; i < count; i++)
    {
        retval->objs[i] = va_arg(list, void *);
    }
    va_end(list);
    
    return retval;
}

CLArrayType *CLArrayTypeCreateWithList(void *o, va_list list, int count)
{
    CLArrayType *retval = calloc(1, sizeof(CLArrayType));
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

int CLArrayTypeCount(CLArrayType *arr)
{
    int c = 0;
    for (; arr->objs[c] != NULL; c++);
    return c;
}

void *CLArrayObjectAtIndex(CLArrayType *arr, int ind)
{
    void *o = arr->objs[ind];
    if (o)
        return o;
    else
        perror("Attempt to access NULL object or index out of bounds."), abort();
}