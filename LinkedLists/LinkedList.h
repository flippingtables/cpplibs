#pragma once

#include <string>

class LinkedList;

class Node {
public:
  int data;
  Node* _next;
  Node* _prev;
  friend LinkedList;
  Node(int data) : data(data), _next(nullptr), _prev(nullptr) {}
  Node& Node::operator =(const Node &element) { data = element.data; return *this; }
  Node& Node::operator =(const Node *element) { data = element->data; return *this; }
};

class LinkedList {
private:


private:
  Node *_head, *_tail;
  size_t _size;
public:
  
  LinkedList();
  
  ~LinkedList();

  void add(const int data);
  void add(const size_t index, const int data);
  int get(size_t index) const;
  bool contains(const int data) const;
  /*Node* search(int data);*/
  bool remove(const int data);
  bool remove(const size_t index);
  void clear();
  bool empty() const;
  size_t size() const;
  std::string str() const;

  Node& LinkedList::operator [](size_t index) const;
};

