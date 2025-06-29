#ifndef TREAP_MODEL_H
#define TREAP_MODEL_H
#include "TreapNode.h"
#include <vector>

class Treap {
private:
  TreapNode *root;
  TreapNode *rotateRight(TreapNode *y);
  TreapNode *rotateLeft(TreapNode *x);
  TreapNode *insertRec(TreapNode *node, const std::string &key, int priority);
  TreapNode *deleteRec(TreapNode *node, const std::string &key);
  TreapNode *searchRec(TreapNode *node, const std::string &key);
  void destroyTree(TreapNode *node);
  std::string serializeNode(TreapNode* node);
  void getAllKeysRec(TreapNode* node, std::vector<std::string>& keys);
public:
  Treap();
  ~Treap();
  void insert(const std::string &key, int priority);
  void deleteKey(const std::string &key);
  bool search(const std::string &key);
  std::vector<std::string> getAllKeys();
  std::string serializeTree();
};

#endif
