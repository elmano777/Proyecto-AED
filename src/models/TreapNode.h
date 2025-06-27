#ifndef TREAPNODE_H
#define TREAPNODE_H
#include <string>

struct TreapNode {
    std::string key;
    int priority;
    TreapNode* left;
    TreapNode* right;
    
    TreapNode(const std::string& k, int p);
};

#endif