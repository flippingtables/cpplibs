#pragma once

#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>

template <typename T>
class LinkedList;

template <typename T>
class Node {
public:
  T _data;
  Node<T>* _next;
  Node<T>* _prev;
  friend LinkedList<T>;
  Node(const T& data);
  Node<T>& operator =(const T& data);
  Node<T>& operator =(const Node<T>& element);
  Node<T>& operator =(const Node<T>* element);

  template <typename T>
  friend std::ostream& operator <<(std::ostream&, const Node<T>& node);
  template <typename T>
  friend std::ostream& operator <<(std::ostream&, const LinkedList<T>& list);
};

template <typename T>
class LinkedList {
private:
  Node<T>* _head;
  Node<T>* _tail;
  size_t _size;
public:

  LinkedList();
  ~LinkedList();

  void add(const T& data);
  void add(const size_t& index, const T& data);
  void addAll(const std::initializer_list<T>& elements);
  T get(const size_t& index) const;
  bool contains(const T& data) const;
  void remove(const T& data);
  void removeAll(const std::initializer_list<T>& elements);
  void removeFromEnd();
  void removeFromBeginning();
  void remove(const size_t& index);
  void clear();

  // Sorting related
  void sort();
  Node<T>* lastNode();
  void swap(const size_t& l, const size_t& r);
  // Sorting related END

  bool empty() const;
  const size_t& size() const;
  size_t indexOf(const T& data) const;
  std::string str() const;

  Node<T>& operator[](const size_t& index) const;
  Node<T>* operator[](const size_t& index);

  template <typename T>
  friend std::ostream& operator <<(std::ostream&, const LinkedList<T>& list);

private:
  void _quickSort(Node<T>* l, Node<T>* h);
  void swap(Node<T>* l, Node<T>* r);
  Node<T>* partition(Node<T>* l, Node<T>* h);
};

/*
================================= Implementation of LinkedList =================================
*/
template <typename T>
Node<T>::Node(const T& data) : _data(data), _next(nullptr), _prev(nullptr) {}

template<typename T>
inline Node<T>& Node<T>::operator=(const T& data) {
  _data = data;
  return *this;
}

template <typename T>
Node<T>& Node<T>::operator =(const Node<T>& element) {
  _data = element._data;
  return *this;
}

template <typename T>
Node<T>& Node<T>::operator =(const Node<T>* element) {
  _data = element->_data;
  return *this;
}

template <typename T>
std::ostream& operator <<(std::ostream& out, const Node<T>& node) {
  out << element._value;
  return out;
}

/*
================================= Implementation of LinkedList =================================
*/

template <typename T>
LinkedList<T>::LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
  clear();
}

template <typename T>
void LinkedList<T>::add(const T& data) {
  Node<T>* newNode = new Node<T>(data);

  if (!empty()) {
    newNode->_prev = _tail;
    _tail->_next = newNode;
    _tail = newNode;
  }
  else {
    _head = _tail = newNode;
  }
  ++_size;
}

template <typename T>
void LinkedList<T>::add(const size_t& index, const T& data) {
  if (empty()) {
    add(data);
    return;
  }

  if (index >= 0 && index < size()) {
    Node<T>* node = _head;
    for (size_t i = 0; i < index; ++i) {
      node = node->_next;
    }
    Node<T>* newNode = new Node<T>(data);
    newNode->_next = node;
    newNode->_prev = node->_prev;
    if (node->_prev != nullptr) {
      node->_prev->_next = newNode;
    }
    node->_prev = newNode;
    if (index == 0) {
      _head = newNode;
    }
    if (index == size() - 1) {
      _tail = newNode->_next;
    }
    ++_size;
  }
  else {
    throw std::out_of_range("LinkedList :: add(index, value)");
  }
}

template<typename T>
void LinkedList<T>::addAll(const std::initializer_list<T>& elements) {
  for (T& element : elements) {
    add(element);
  }
}

template <typename T>
T LinkedList<T>::get(const size_t& index) const {
  Node<T>* newNode;
  if (index >= 0 && index < size()) {
    Node<T>* node = _head;
    for (size_t i = 0; i < index; ++i) {
      node = node->_next;
    }
    return node->_data;
  }
  else {
    return newNode->_data;
  }
}

template <typename T>
bool LinkedList<T>::contains(const T& data) const {
  Node<T>* node = _head;
  for (size_t i = 0; i < size(); ++i) {
    if (node->_data == data) {
      return true;
    }
    node = node->_next;
  }
  return false;
}

template <typename T>
Node<T>& LinkedList<T>::operator[](const size_t& index) const {
  if (index >= 0 && index < size()) {
    Node<T>* node = _head;
    for (size_t i = 0; i < index; ++i) {
      node = node->_next;
    }
    return *node;
  }
  else {
    return nullptr;
  }
}

template <typename T>
Node<T>* LinkedList<T>::operator[](const size_t& index) {
  if (index >= 0 && index < size()) {
    Node<T>* node = _head;
    for (size_t i = 0; i < index; ++i) {
      node = node->_next;
    }
    return node;
  }
  else {
    return nullptr;
  }
}

template <typename T>
void LinkedList<T>::remove(const T& data) {
  size_t indexOfData = indexOf(data);
  if (indexOfData != std::string::npos) {
    remove(indexOfData);
  }
}

template<typename T>
void LinkedList<T>::removeAll(const std::initializer_list<T>& elements) {
  for (const T& element : elements) {
    remove(element);
  }
}

template <typename T>
void LinkedList<T>::removeFromBeginning() {
  Node<T>* node = _head;
  if (size() == 0) {
    return;
  }
  _head = _head->_next;
  if (_head != nullptr) {
    _head->_prev = nullptr;
  }
  --_size;
  delete node;
}

template <typename T>
void LinkedList<T>::removeFromEnd() {
  Node<T>* node = _tail;
  if (size() == 0) {
    return;
  }
  _tail = _tail->_prev;
  if (_tail != nullptr) {
    _tail->_next = nullptr;
  }
  --_size;
  delete node;
}

template <typename T>
void LinkedList<T>::remove(const size_t& index) {
  if (index >= size()) {
    return;
  }
  Node<T>* node = _head;
  size_t i;
  for (i = 0; i < index; ++i) {
    node = node->_next;
  }

  if (i == 0) {
    removeFromBeginning();
  }
  else if (node == _tail) {
    removeFromEnd();
  }
  else if (node != nullptr) {
    node->_prev->_next = node->_next;
    node->_next->_prev = node->_prev;
    --_size;
    delete node;
  }
}

template <typename T>
void LinkedList<T>::clear() {
  Node<T>* current = _head;
  while (current) {
    Node<T>* next = current->_next;
    delete current;
    current = next;
    --_size;
  }
  _head = _tail = nullptr;
}

template <typename T>
bool LinkedList<T>::empty() const {
  return size() == 0;
}

template <typename T>
const size_t& LinkedList<T>::size() const {
  return _size;
}

template <typename T>
std::string LinkedList<T>::str() const {
  std::stringstream ss;

  Node<T>* node = _head;
  ss << '[';
  while (node != nullptr) {
    if (node->_next != nullptr) {
      ss << node->_data << ", ";
    }
    else {
      ss << node->_data;
    }

    node = node->_next;
  }
  ss << ']';

  return ss.str();
}

template <typename T>
size_t LinkedList<T>::indexOf(const T& data) const {
  Node<T>* node = _head;
  bool found = false;
  size_t foundIndex = std::string::npos;
  if (!empty()) {
    for (size_t indexOf = 0; !found && indexOf < size(); ++indexOf) {
      if (data == node->_data) {
        foundIndex = indexOf;
        found = true;
      }
      node = node->_next;
    }
  }

  return foundIndex;
}
template <typename T>
void LinkedList<T>::swap(Node<T>* l, Node<T>* r) {
  Node<T> tmp = *l;
  *l = *r;
  *r = tmp;
}

template <typename T>
void LinkedList<T>::swap(const size_t& l, const size_t& r) {
  Node<T>* lNode = (*this)[l];
  Node<T>* rNode = (*this)[r];
  swap(lNode, rNode);
}

// A utility function to find last node of linked list
template <typename T>
Node<T>* LinkedList<T>::lastNode() {
  Node<T>* node = _head;
  while (node && node->_next)
    node = node->_next;
  return node;
}

template <typename T>
Node<T>* LinkedList<T>::partition(Node<T>* l, Node<T>* h) {
  // set pivot as h element
  Node<T>* pivot = h;

  // similar to i = l-1 for array implementation
  Node<T>* i = l->_prev;

  // Similar to "for (int j = l; j <= h- 1; j++)"
  for (Node<T>* j = l; j != h; j = j->_next) {
    if (j->_data <= pivot->_data) {
      // Similar to i++ for array
      i = (i == nullptr) ? l : i->_next;

      swap(i, j);
    }
  }
  i = (i == nullptr) ? l : i->_next; // Similar to i++
  swap(i, h);
  return i;
}

template <typename T>
void LinkedList<T>::_quickSort(Node<T> * l, Node<T> * h) {
  if (h != nullptr && l != h && l != h->_next) {
    Node<T>* p = partition(l, h);
    _quickSort(l, p->_prev);
    _quickSort(p->_next, h);
  }
}

template <typename T>
void LinkedList<T>::sort() {
  Node<T>* last = lastNode();
  _quickSort(_head, last);
}

template <typename T>
std::ostream& operator <<(std::ostream & out, const LinkedList<T> & list) {
  Node<T>* node = list._head;
  out << '[';
  while (node != nullptr) {
    if (node->_next != nullptr) {
      out << node->_data << ", ";
    }
    else {
      out << node->_data;
    }

    node = node->_next;
  }
  out << ']';
  node = nullptr;
  return out;
}
