#include "leetc.h"
#include <map>

using std::map;



class LRUCache {

struct LRUNode {
    int key;
    int val;
    LRUNode *next;
    LRUNode *prev;
    LRUNode() : key(-1), val(-1), next(NULL), prev(NULL) {}
    LRUNode(int key, int val) : key(key), val(val), next(NULL), prev(NULL) {};
    LRUNode(int key, int val, LRUNode *next, LRUNode *prev) : 
        key(key), val(val), next(next), prev(prev) {};
};

public:
    LRUCache(int capacity) : mCapacity(capacity), mHead(NULL), mTail(NULL) {}

    int get(int key) {
        auto it = mData.find(key);
        int result = it == mData.end() ? -1 : it->second->val;
        if(it != mData.end()) {
            AdjustNodeToHead(it->second);
        }
        return result;
    }

    void set(int key, int value) {
        auto it = mData.find(key);
        if(it == mData.end()) {
            if(mData.size() == mCapacity) {
                DeleteLRUNode();
            }
            LRUNode *node = new LRUNode(key, value, mHead, NULL);
            if(mHead != NULL) {
                mHead->prev = node;
                mHead = mHead->prev;
            }
            else {
                mHead = mTail = node;
            }

            if(mTail == NULL) {
                mTail = node;
            }
            mData.insert(std::make_pair(key, node));
        }
        else {
            it->second->val = value;
            AdjustNodeToHead(it->second);
        }
    }

    ~LRUCache() {
        while(mHead != NULL) {
            LRUNode *temp = mHead->next;
            delete mHead;
            mHead = temp;
        }
    }

private:
    void DeleteLRUNode() {
        if(mTail != NULL) {
            int key2Del = mTail->key;
            mTail = mTail->prev;
            auto it = mData.find(key2Del);
            delete it->second;
            mData.erase(it);
            if(mTail == NULL) {
                mHead = NULL;
            }
            else {
                mTail->next = NULL;
            }
        }
    }

    void AdjustNodeToHead(LRUNode *node) {
        if(node != NULL && node != mHead) {
            if(node != mTail) {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            else {
                node->prev->next = NULL;
                mTail = node->prev;
            }
            node->next = mHead;
            mHead->prev = node;
            mHead = mHead->prev;
            mHead->prev = NULL;
        }
    }

private:
    int mCapacity;
    map<int, LRUNode*> mData;
    LRUNode *mHead;
    LRUNode *mTail;
};

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    LRUCache lruCache(2);
    lruCache.set(2, 1);
    lruCache.set(1, 1);
    cout << lruCache.get(2) << endl;
    lruCache.set(4, 1);
    cout << lruCache.get(1) << endl;
    cout << lruCache.get(2) << endl;
    return 0;
}
