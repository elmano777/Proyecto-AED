#include "Treap.h"

TreapNode* Treap::rotateRight(TreapNode *y) {
    TreapNode *x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

TreapNode* Treap::rotateLeft(TreapNode *x) {
    TreapNode *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

TreapNode* Treap::insertRec(TreapNode *node, const std::string &key, int priority) {
    if (!node)
        return new TreapNode(key, priority);

    if (key < node->key) {
        node->left = insertRec(node->left, key, priority);
        if (node->left->priority > node->priority)
            node = rotateRight(node);
    }
    else if (key > node->key) {
        node->right = insertRec(node->right, key, priority);
        if (node->right->priority > node->priority)
            node = rotateLeft(node);
    }
    return node;
}

TreapNode* Treap::deleteRec(TreapNode *node, const std::string &key) {
    if (!node)
        return nullptr;

    if (key < node->key) {
        node->left = deleteRec(node->left, key);
    }
    else if (key > node->key) {
        node->right = deleteRec(node->right, key);
    }
    else {
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }
        if (!node->left) {
            TreapNode *temp = node->right;
            delete node;
            return temp;
        }
        if (!node->right) {
            TreapNode *temp = node->left;
            delete node;
            return temp;
        }
        if (node->left->priority > node->right->priority) {
            node = rotateRight(node);
            node->right = deleteRec(node->right, key);
        }
        else {
            node = rotateLeft(node);
            node->left = deleteRec(node->left, key);
        }
    }
    return node;
}

TreapNode* Treap::searchRec(TreapNode *node, const std::string &key) {
    if (node == nullptr || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return searchRec(node->left, key);
    }
    return searchRec(node->right, key);
}

void Treap::destroyTree(TreapNode *node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

Treap::Treap() : root(nullptr) {}

Treap::~Treap() {
    destroyTree(root);
}

void Treap::insert(const std::string &key, int priority) {
    root = insertRec(root, key, priority);
}

void Treap::deleteKey(const std::string &key) {
    root = deleteRec(root, key);
}

bool Treap::search(const std::string &key) {
    return searchRec(root, key) != nullptr;
}

void Treap::getAllKeysRec(TreapNode* node, std::vector<std::string>& keys){
    if(node){
        getAllKeysRec(node->left, keys);
        keys.push_back(node->key);
        getAllKeysRec(node->right, keys);
    }
}

std::vector<std::string> Treap::getAllKeys() {
    std::vector<std::string> keys;
    getAllKeysRec(root, keys);
    return keys;
}

std::string Treap::serializeTree(){
    return serializeNode(root);
}

std::string Treap::serializeNode(TreapNode* node) {
    if (!node) {
        return "null";
    }
    
    std::string result = "{";
    result += "\"key\":\"" + node->key + "\",";
    result += "\"priority\":" + std::to_string(node->priority) + ",";
    result += "\"left\":" + serializeNode(node->left) + ",";
    result += "\"right\":" + serializeNode(node->right);
    result += "}";
    
    return result;
}