#include <iostream>
#include <map>

using namespace std;

#define MAXM 5010

struct node_t {
    const string str;
    node_t *prior;
    node_t *next;
    node_t(const string &str) : str(str), prior(NULL), next(NULL) {}
    node_t(const string &str, node_t *prior, node_t *next) : str(str), prior(prior), next(next) {} 
};

int main(void) {
    int N, M;
    cin >> N >> M;
    map<string, node_t *> mymap;
    // double list
    node_t *caches_begin = NULL;
    node_t *caches_end = NULL;
    int cache_count = 0;

    string url;
    for(int i = 0; i < N; i++) {
        cin >> url;
        if(mymap.find(url) != mymap.end()) {
            cout << "Cache" << endl;
            node_t *node = mymap[url];
            // node->prior == NULL means node is already at begining
            if(node->prior) {
                node->prior->next = node->next;
                if(node->next) 
                    node->next->prior = node->prior;
                else {
                    // node->next == NULL means node is at end 
                    caches_end = node->prior;
                }
                node->prior = NULL;
                node->next = caches_begin;
                caches_begin->prior = node;
                caches_begin = node;
            }
        }
        else {
            cout << "Internet" << endl;
            node_t *node = new node_t(url);
            mymap.insert(std::make_pair(url, node));
            cache_count++;
            if(caches_begin == NULL) {
                caches_begin = caches_end = node;
            }
            else {
                node->next = caches_begin;
                caches_begin->prior = node;
                caches_begin = node;
                if(cache_count > M) {
                    cache_count = M;
                    node_t *tmp = caches_end;
                    caches_end = caches_end->prior;
                    caches_end->next = NULL;
                    mymap.erase(tmp->str);
                    delete tmp;
                }
            }
        }

        /* cout << i << endl;
         * node_t *p = caches_begin;
         * while(p) {
         *     cout << p->str << endl;
         *     p = p->next;
         * } */
    }

    node_t *p = caches_begin;
    while(p) {
        node_t *tmp = p;
        p = p->next;
        delete tmp;
    }
    return 0;
}
