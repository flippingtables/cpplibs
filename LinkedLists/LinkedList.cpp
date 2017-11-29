#include "stdafx.h"
#include "LinkedList.h"
#include <Windows.h>
#include <sstream>

LinkedList::LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {

}


LinkedList::~LinkedList() {
}

void LinkedList::add(const int data) {
  Node* newNode = new Node(data);

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

void LinkedList::add(const size_t index, const int data) {


  if (empty()) {
    add(data);
    return;
  }
  if (index >= 0 && index < size()) {
    Node* node = _head;
    for (size_t i = 0; i < index; ++i) {
      node = node->_next;
    }
    Node* newNode = new Node(data);
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

int LinkedList::get(size_t index) const {
  if (index >= 0 && index < size()) {
    Node* node = _head;
    for (size_t i = 0; i < index; ++i) {
      node = node->_next;
    }
    return node->data;
  }
  else
    throw std::out_of_range("LinkedList :: get(index)");

  return 0;
}

bool LinkedList::contains(const int data) const {
  
  Node* node = _head;
  for (size_t i = 0; i < size(); ++i) {
    if (node->data == data) {
      return true;
    }
    node = node->_next;
  }
  return false;
}

Node& LinkedList::operator[](size_t index) const {
  if (index >= 0 && index < size()) {
    Node* node = _head;
    for (size_t i = 0; i < index; ++i) {
      node = node->_next;
    }
    return *node;
  }
  else {
    throw std::out_of_range("LinkedList :: operator [index]");
  }

}

bool LinkedList::remove(const int data) {
  Node *node = _head;
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
      Node *tmp = node->_next;
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

bool LinkedList::remove(const size_t index) {
  if (index >= 0 && index < size()) {
    Node *node = _head;
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


void LinkedList::clear() {
  if (!empty()) {
    Node *node = _tail;
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

bool LinkedList::empty() const {
  return size() == 0;
}

size_t LinkedList::size() const {
  return _size;
}

std::string LinkedList::str() const {
  std::stringstream ss;

  Node* tmp = _head;
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
