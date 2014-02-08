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

CLArrayType CLArrayTypeCreateWithObjects(void *o, ...)
{
    CLArrayType retval;
    va_list list;
    va_start(list, o);
    int count = 0;
    while (va_arg(list, void *) != NULL)
    {
        count++;
    }
    va_end(list);
    va_start(list, o);
    retval.objs = malloc(sizeof(void) * count);
    for (int i = 0; i < count; i++)
    {
        retval.objs[i] = va_arg(list, void *);
    }
    va_end(list);
    
    return retval;
}

int CLArrayTypeCount(CLArrayType arr)
{
    int c = 0;
    for (; arr.objs[c] != NULL; c++);
    return c;
}

void *CLArrayObjectAtIndex(CLArrayType arr, int ind)
{
    return arr.objs[ind];
}