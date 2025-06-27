#include "TreapNode.h"

TreapNode::TreapNode(const std::string& k, int p) 
    : key(k), priority(p), left(nullptr), right(nullptr) {}