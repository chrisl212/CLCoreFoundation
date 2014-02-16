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
    puts("-----------------\nString Tests");
    CLStringType *str = CLStringTypeCreateWithCString("Hello, World!");
    puts(CLStringCString(str));
    CLMutableArrayType *comps = CLStringComponentsSeparatedByString(str, CLStringTypeCreateWithCString(","));
    int cnt = (int)CLMutableArrayTypeCount(comps);
    int i = 0;
    for (; i < cnt; i++)
    {
        puts(CLStringCString(CLMutableArrayObjectAtIndex(comps, i)));
    }
    
    puts("-----------------\nArray Tests");
    CLArrayType *arr = CLArrayTypeCreateWithObjects(str, NULL);
    int c = (int)CLArrayTypeCount(arr);
    i = 0;
    for (; i < c; i++)
    {
        void *b = CLArrayObjectAtIndex(arr, i);
        printf("%s\n", CLStringCString(b));
    }
    
    puts("-----------------\nMutable Array Tests");
    CLMutableArrayType *mutablearr = CLMutableArrayTypeCreateWithObjects(str, NULL);
    CLMutableArrayTypeAddObject(mutablearr, CLStringTypeCreateWithCString("schnitzel"));
    int co = (int)CLMutableArrayTypeCount(mutablearr);
    i = 0;
    for (; i < co; i++)
    {
        void *b = CLMutableArrayObjectAtIndex(mutablearr, i);
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
    
    puts("-----------------\nInternet Tests");
    CLURLType *url = CLURLTypeCreateWithPath(CLStringTypeCreateWithCString("www.a-cstudios.com/welcome.html"), CLURLTypeHTTP);
    CLStringType *string = CLInternetRequestContentsOfURL(url);
    puts(CLStringCString(string));
    
    /*
    CLErrorType *err = NULL;
    CLFileType *dir = CLFileWithPath(CLStringTypeCreateWithCString("/Users/macuser"), &err);
    if (err)
        CLErrorPrint(err);
    else
    {
        i = 0;
        int dircount = (int)CLArrayTypeCount(dir->directoryContents);
        for (; i < dircount; i++)
        {
            puts(CLStringCString(CLArrayObjectAtIndex(dir->directoryContents, i)));
        }
    }
    */
    return 0;
}
