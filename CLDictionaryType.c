//
//  CLDictionaryType.c
//  CLCoreFoundation
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include "CLDictionaryType.h"
#include "CLStringType.h"
#include "CLArrayType.h"

struct CLDictionaryType
{
    CLArrayType *objs;
    CLArrayType *keys;
};

CLDictionaryType *CLDictionaryTypeCreateWithObjectsAndKeys(CLArrayType *objects, CLArrayType *keys)
{
    CLDictionaryType *dict = calloc(1, sizeof(CLDictionaryType));
    dict->objs = objects;
    dict->keys = keys;
    return dict;
}

CLArrayType *CLDictionaryAllObjects(CLDictionaryType *d)
{
    return d->objs;
}

CLArrayType *CLDictionaryAllKeys(CLDictionaryType *d)
{
    return d->keys;
}

void *CLDictionaryTypeObjectForKey(CLDictionaryType *dict, CLStringType *objectkey)
{
    size_t count = CLArrayTypeCount(dict->keys);
    int i = 0;
    for (; i < count; i++)
    {
        CLStringType *key = CLArrayObjectAtIndex(dict->keys, i);
        if (CLStringCompare(key, objectkey) == true)
            return CLArrayObjectAtIndex(dict->objs, i);
    }
    return NULL;
}