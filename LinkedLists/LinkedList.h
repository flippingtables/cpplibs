#pragma once

#include <sstream>
#include <string>

template <typename T>
class LinkedList;

template <typename T>
class Node {
public:
  T data;
  Node<T>* _next;
  Node<T>* _prev;
  friend LinkedList<T>;
  Node(const T data);
  Node<T>& operator =(const Node<T>&element);
  Node<T>& operator =(const Node<T>*element);
};

template <typename T>
class LinkedList {
private:
  Node<T> *_head;
  Node<T> *_tail;
  size_t _size;
public:
  
  LinkedList();
  
  ~LinkedList();

  void add(const T data);
  void add(const size_t index, const T data);
  T get(size_t index) const;
  bool contains(const T data) const;
  bool remove(const T data);
  T remove(const size_t index);
  void clear();
  bool empty() const;
  size_t size() const;
  std::string str() const;

  Node<T>& operator[](size_t index) const;
};

/*
================================= Implementation of LinkedList =================================
*/
template <typename T>
Node<T>::Node(const T data) : data(data), _next(nullptr), _prev(nullptr) {}

template <typename T>
Node<T>& Node<T>::operator =(const Node<T>& element) { data = element.data; return *this; }

template <typename T>
Node<T>& Node<T>::operator =(const Node<T>* element) { data = element->data; return *this; }
/*
================================= Implementation of LinkedList =================================
*/

template <typename T>
LinkedList<T>::LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {}


template <typename T>
LinkedList<T>::~LinkedList() {
  clear();
  delete _head;
  delete _tail;
  _head = nullptr;
  _tail = nullptr;
}


template <typename T>
void LinkedList<T>::add(const T data) {
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
void LinkedList<T>::add(const size_t index, const T data) {

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

template <typename T>
T LinkedList<T>::get(size_t index) const {
  if (index >= 0 && index < size()) {
    Node<T>* node = _head;
    for (size_t i = 0; i < index; ++i) {
      node = node->_next;
    }
    return node->data;
  }
  else
    throw std::out_of_range("LinkedList :: get(index)");

  return 0;
}

template <typename T>
bool LinkedList<T>::contains(const T data) const {

  Node<T> *node = _head;
  for (size_t i = 0; i < size(); ++i) {
    if (node->data == data) {
      return true;
    }
    node = node->_next;
  }
  return false;
}

template <typename T>
Node<T>& LinkedList<T>::operator[](size_t index) const {
  if (index >= 0 && index < size()) {
    Node<T> *node = _head;
    for (size_t i = 0; i < index; ++i) {
      node = node->_next;
    }
    return *node;
  }
  else {
    throw std::out_of_range("LinkedList :: operator [index]");
  }

}

template <typename T>
bool LinkedList<T>::remove(const T data) {
  Node<T> *node = _head;
  bool isDeleted = false;
  while (node != nullptr) {
    if (node->data != data) {
      node = node->_next;
    }
    else {
      if (node->_prev != nullptr) { node->_prev->_next = node->_next; }
      if (node->_next != nullptr) { node->_prev->_prev = node->_prev; }
      if (_tail == node && node->_prev != nullptr) _tail = node->_prev;
      if (_head == node && node->_next != nullptr) _head = node->_next;
      if (_head == _tail && _tail == node) _head = _tail = nullptr;
      Node<T> *tmp = node->_next;
      node->_next = nullptr;
      node->_prev = nullptr;
      node = tmp;
      tmp = nullptr;
      --_size;
      isDeleted = true;
    }
  }

  return false;
}

template <typename T>
T LinkedList<T>::remove(const size_t index) {
  if (index >= 0 && index < size()) {
    Node<T> *node = _head;
    for (size_t i = 0; i < index; ++i)
      node = node->_next;
    if (node->_prev != nullptr) node->_prev->_next = node->_next;
    if (node->_next != nullptr) node->_next->_prev = node->_prev;
    if (_tail == node && node->_prev != nullptr) _tail = node->_prev;
    if (_head == node && node->_next != nullptr) _head = node->_next;
    if (_head == _tail && _tail == node) _head = _tail = nullptr;
    node->_next = nullptr;
    node->_prev = nullptr;
    --_size;
    return node->data;
  }
  else
    throw std::out_of_range("LinkedList :: remove(index)");
  return false;
}


template <typename T>
void LinkedList<T>::clear() {
  if (!empty()) {
    Node<T> *node = _tail;
    while (node != nullptr) {
      if (nullptr != node->_next) {
        delete node->_next;
        node->_next = nullptr;
      }
      if (node->_prev != nullptr)
        node = node->_prev;
      else {
        delete node;
        node = nullptr;
      }
    }
    _head = _tail = nullptr;
    _size = 0;
  }
}

template <typename T>
bool LinkedList<T>::empty() const {
  return size() == 0;
}

template <typename T>
size_t LinkedList<T>::size() const {
  return _size;
}

template <typename T>
std::string LinkedList<T>::str() const {
  std::stringstream ss;

  Node<T> *tmp = _head;
  for (size_t i = 0; i < size(); ++i) {
    if (tmp == nullptr)
      break;

    ss << tmp->data;
    if (tmp->_next) {
      ss << " ";
    }
    tmp = tmp->_next;
  }
  return ss.str();
}

