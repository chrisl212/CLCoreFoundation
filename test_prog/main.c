//
//  main.c
//  test_prog
//
//  Created by Chris on 2/8/14.
//  Copyright (c) 2014 A and C Studios. All rights reserved.
//

#include <stdio.h>
#include "CLCoreFoundation.h"

int main(int argc, const char * argv[])
{
    CLStringType *str = CLStringTypeCreateWithCString("Hello, World!");
    CLArrayType *arr = CLArrayTypeCreateWithObjects(str, NULL);
    puts(CLStringCString(str));
    int c = CLArrayTypeCount(arr);
    for (int i = 0; i < c; i++)
    {
        void *b = CLArrayObjectAtIndex(arr, i);
        printf("%s\n", CLStringCString(b));
    }
    puts("-----------------\nDictionary Tests");
    CLArrayType *objs = CLArrayTypeCreateWithObjects("hello", "world", "it's chris", NULL);
    
    CLStringType *key1 = CLStringTypeCreateWithCString("key1");
    CLStringType *key2 = CLStringTypeCreateWithCString("key2");
    CLStringType *key3 = CLStringTypeCreateWithCString("key to use");
    
    CLArrayType *keys = CLArrayTypeCreateWithObjects(key1, key2, key3, NULL);
    CLDictionaryType *dict = CLDictionaryTypeCreateWithObjectsAndKeys(objs, keys);
    puts(CLDictionaryTypeObjectForKey(dict, key3));
    return 0;
}
