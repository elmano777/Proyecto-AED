#ifndef TREAP_H
#define TREAP_H
#include "TreapNode.h"
#include <vector>

class Treap {
private:
    TreapNode* root;
    // Tus métodos privados (rotateRight, rotateLeft, etc.)
    
public:
    Treap();
    ~Treap();
    void insert(const std::string& key, int priority);
    void deleteKey(const std::string& key);
    bool search(const std::string& key);
    std::vector<std::string> getAllKeys(); // para listar reservas
};

#endif