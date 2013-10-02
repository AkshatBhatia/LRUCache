//
//  LRUCache.h
//  LRUCache
//
//  Created by Akshat Bhatia on 9/18/13.
//  Copyright (c) 2013 Zonked. All rights reserved.
//

#ifndef __LRUCache__LRUCache__
#define __LRUCache__LRUCache__

#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef pair<string, string> KeyValuePair;

typedef struct LRUCacheNode
{
    KeyValuePair keyValue;
    LRUCacheNode * prev;
    LRUCacheNode * next;
    LRUCacheNode(KeyValuePair param)
    {
        prev = next  = nullptr;
        keyValue = param;
    }
} LRUCacheNode;

class LRUCache
{
public:
    
    /*
     Params:
        maxNoOfKeys - Max number of keys that can be saved in the cache. This number is used to initialize the cache.
     */
    LRUCache(size_t maxNoOfKeys, ofstream& outStreamParam);
    
    ~LRUCache();
    
    /*
     This function sets the max number of keys that can be saved in the cache. IF the current number of objects in the cache is greater than the current number of objects in the cache then this function deletes the least recently used objects from the cache and reduces the size to noOfKeys.
     
     Params:
        noOfKeys - Max number of keys that can be saved in the cache.
     */
    void Bound(const size_t noOfKeys);
    
    
    void Set(const KeyValuePair& keyValuePair);
    
    void Get(const string key);
    
    void Peek(const string key) const;
    
    void Dump();
    
private:
    LRUCacheNode* FindLRUCacheNode(const string key) const;
    void MoveToHead(LRUCacheNode* cacheNode);
    void RemoveCacheNode(LRUCacheNode* cacheNode);
    void InsertNewNodeAtHead(LRUCacheNode* cacheNode);
    void RemoveTailNode();
    
private:
    size_t currentSize;
    size_t maxNoOfKeys;
    LRUCacheNode* headOfCache;
    LRUCacheNode* tailOfCache;
    map<string, LRUCacheNode*> cacheMap;
    ofstream & outStream;
};


#endif /* defined(__LRUCache__LRUCache__) */
