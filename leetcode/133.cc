#include "leetc.h"
#include <unordered_map>

using namespace std;

class Solution {
    private:
        unordered_map<int, UndirectedGraphNode *> my_map;
        UndirectedGraphNode *find_node_by_id(int id) {
            auto it = my_map.find(id);
            if(it == my_map.end()) return NULL;
            else return it->second;
        }
    public:
        UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
            if(node == NULL) return NULL;
            UndirectedGraphNode *root = find_node_by_id(node->label);
            if(root == NULL) {
                root = new UndirectedGraphNode(node->label);
                my_map.insert(std::make_pair(root->label, root));
                auto it = node->neighbors.begin();
                while(it != node->neighbors.end()) {
                    root->neighbors.push_back(cloneGraph(*it));
                    it++;
                }
            }
            return root;
        }
};
