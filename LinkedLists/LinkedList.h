#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>

class PositionException : public std::exception {
protected:
  std::string message;

public:
  PositionException(const std::string &msg)
      : std::exception(msg.c_str()), message(msg) {}
};

template <typename T> class LinkedList;

template <typename T> class Node {
private:
  using Nodeptr = Node<T> *;

public:
  T data;
  Nodeptr next;
  Nodeptr prev;
  friend LinkedList<T>;
  Node(const T &data);
  Node() = delete;
  Node<T> &operator=(const T &data);
  Node<T> &operator=(const Node<T> &element);
  Node<T> &operator=(const Node<T> *element);

  bool operator==(const Node<T> &rhs) { return data == rhs.data; }

  template <typename T>
  friend std::ostream &operator<<(std::ostream &, const Node<T> &node);
  template <typename T>
  friend std::ostream &operator<<(std::ostream &, const LinkedList<T> &list);
};

template <typename T> class LinkedList {
private:
  using Nodeptr = Node<T> *;

private:
  Nodeptr head;
  Nodeptr tail;
  size_t my_size;

public:
  class iterator {
  public:
    iterator() noexcept : m_pCurrentNode(m_spRoot) {}

    iterator(const Node<T> *pNode) noexcept : m_pCurrentNode(pNode) {}

    iterator &operator=(Node<T> *pNode) {
      this->m_pCurrentNode = pNode;
      return *this;
    }

    // Prefix ++ overload
    iterator &operator++() {
      if (m_pCurrentNode)
        m_pCurrentNode = m_pCurrentNode->next;
      return *this;
    }

    // Postfix ++ overload
    iterator operator++(int) {
      iterator iterator = *this;
      ++*this;
      return iterator;
    }

    bool operator!=(const iterator &iterator) {
      return m_pCurrentNode != iterator.m_pCurrentNode;
    }

    bool operator==(const iterator &iterator) {
      return m_pCurrentNode == iterator.m_pCurrentNode;
    }

    T operator*() { return m_pCurrentNode->data; }

  private:
    const Node<T> *m_pCurrentNode;
  };

  class const_iterator {
  public:
    const_iterator() noexcept : m_pCurrentNode(m_spRoot) {}

    const_iterator(const Node<T> *pNode) noexcept : m_pCurrentNode(pNode) {}

    const_iterator &operator=(Node<T> *pNode) {
      this->m_pCurrentNode = pNode;
      return *this;
    }

    // Prefix ++ overload
    const_iterator &operator++() {
      if (m_pCurrentNode)
        m_pCurrentNode = m_pCurrentNode->next;
      return *this;
    }

    // Postfix ++ overload
    const_iterator operator++(int) {
      const_iterator iterator = *this;
      ++*this;
      return iterator;
    }

    bool operator!=(const const_iterator &iterator) const {
      return m_pCurrentNode != iterator.m_pCurrentNode;
    }

    bool operator==(const const_iterator &iterator) const {
      return m_pCurrentNode == iterator.m_pCurrentNode;
    }

    T operator*() const { return m_pCurrentNode->data; }
    T *operator->() const { return m_pCurrentNode; }

  private:
    const Node<T> *m_pCurrentNode;
  };

  LinkedList();
  LinkedList(const std::initializer_list<T> &elements);

  ~LinkedList();

  void insert(const T &data);
  void insert(const size_t &index, const T &data);
  void insert(const std::initializer_list<T> &elements);
  void push_front(const T &data);
  void push_back(const T &data);

  void merge(LinkedList<T> &otherList);

  T get(const size_t &index) const;
  bool contains(const T &data) const;
  void remove(const T &data);
  void remove(const std::initializer_list<T> &elements);
  void remove(const size_t &index);

  void pop_back();
  void pop_front();

  void erase(Nodeptr toRemove); // NON STL erase

  void unique();

  void clear();

  // Sorting related
  void sort();
  Node<T> *lastNode();
  void swap(const size_t &l, const size_t &r);
  // Sorting related END

  bool empty() const;
  const size_t &size() const noexcept;
  size_t firstIndex() const;
  size_t lastIndex() const;
  size_t indexOf(const T &data) const;

  iterator begin() { return iterator(head); }
  iterator end() { return iterator(nullptr); }

  const_iterator cbegin() const { return const_iterator(head); }
  const_iterator cend() const { return const_iterator(nullptr); }

  T &front();
  const T &front() const;
  T &back();
  const T &back() const;

  Node<T> &operator[](const size_t &index) const;
  Node<T> *operator[](const size_t &index);

  template <typename T>
  friend std::ostream &operator<<(std::ostream &, const LinkedList<T> &list);

  std::string str() const;

private:
  void _quickSort(Node<T> *l, Node<T> *h);
  void swap(Node<T> *l, Node<T> *r);
  Node<T> *partition(Node<T> *l, Node<T> *h);
};

/*
================================= Implementation of LinkedList
=================================
*/
template <typename T>
Node<T>::Node(const T &data_) : data(data_), next(nullptr), prev(nullptr) {}

template <typename T> inline Node<T> &Node<T>::operator=(const T &data_) {
  data = data_;
  return *this;
}

template <typename T> Node<T> &Node<T>::operator=(const Node<T> &element) {
  data = element.data;
  return *this;
}

template <typename T> Node<T> &Node<T>::operator=(const Node<T> *element) {
  data = element->data;
  return *this;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Node<T> &node) {
  out << element._value;
  return out;
}

/*
================================= Implementation of LinkedList
=================================
*/

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), my_size(0) {}

template <typename T>
LinkedList<T>::LinkedList(const std::initializer_list<T> &elements)
    : LinkedList() {
  insert(elements);
}

template <typename T> LinkedList<T>::~LinkedList() { clear(); }

template <typename T> void LinkedList<T>::insert(const T &data) {
  Node<T> *newNode = new Node<T>(data);

  if (!empty()) {
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  } else {
    head = tail = newNode;
  }
  ++my_size;
}

template <typename T>
void LinkedList<T>::insert(const size_t &index, const T &data) {
  if (index > 0 && index >= size()) {
    throw PositionException("Index out of bounds");
  }

  if (empty()) {
    insert(data);
    return;
  }

  Node<T> *node = head;
  for (size_t i = 0; i < index; ++i) {
    node = node->next;
  }
  Node<T> *newNode = new Node<T>(data);
  newNode->next = node;
  newNode->prev = node->prev;
  if (node->prev != nullptr) {
    node->prev->next = newNode;
  }
  node->prev = newNode;
  if (index == 0) {
    head = newNode;
  }
  if (index == size() - 1) {
    tail = newNode->next;
  }
  ++my_size;
}

template <typename T>
void LinkedList<T>::insert(const std::initializer_list<T> &elements) {
  for (auto &element : elements) {
    insert(element);
  }
}

template <typename T> T LinkedList<T>::get(const size_t &index) const {
  if (index >= size()) {
    throw PositionException("Index out of bounds");
  }

  Node<T> *node = head;
  for (size_t i = 0; i < index; ++i) {
    node = node->next;
  }

  return node->data;
}

template <typename T> bool LinkedList<T>::contains(const T &data) const {
  Node<T> *node = head;
  for (size_t i = 0; i < size(); ++i) {
    if (node->data == data) {
      return true;
    }
    node = node->next;
  }
  return false;
}

template <typename T>
Node<T> &LinkedList<T>::operator[](const size_t &index) const {
  if (index >= size()) {
    throw PositionException("Index out of bounds");
  }

  Node<T> *node = head;
  for (size_t i = 0; i < index; ++i) {
    node = node->next;
  }
  return *node;
}

template <typename T> Node<T> *LinkedList<T>::operator[](const size_t &index) {
  if (index >= size()) {
    throw PositionException("Index out of bounds");
  }
  Node<T> *node = head;
  for (size_t i = 0; i < index; ++i) {
    node = node->next;
  }
  return node;
}

template <typename T> void LinkedList<T>::remove(const T &data) {
  size_t indexOfData = indexOf(data);
  if (indexOfData == std::string::npos) {
    throw PositionException("Element not found in list");
  }

  while (indexOfData != std::string::npos) {
    remove(indexOfData);
    indexOfData = indexOf(data);
  }
}

template <typename T>
void LinkedList<T>::remove(const std::initializer_list<T> &elements) {
  for (auto &element : elements) {
    remove(element);
  }
}

template <typename T> void LinkedList<T>::pop_front() {
  Node<T> *node = head;
  if (size() == 0) {
    throw PositionException("List empty, nothing to remove - pop_front");
  }
  head = head->next;
  if (head != nullptr) {
    head->prev = nullptr;
  }
  --my_size;
  delete node;
}

template <typename T> void LinkedList<T>::pop_back() {
  Node<T> *node = tail;
  if (size() == 0) {
    throw PositionException("List empty, nothing to remove - pop_back");
  }
  tail = tail->prev;
  if (tail != nullptr) {
    tail->next = nullptr;
  }
  --my_size;
  delete node;
}

template <typename T> void LinkedList<T>::remove(const size_t &index) {
  if (index >= size()) {
    return;
  }
  Node<T> *node = head;
  size_t i;
  for (i = 0; i < index; ++i) {
    node = node->next;
  }

  if (i == 0) {
    pop_front();
  } else if (node == tail) {
    pop_back();
  } else if (node != nullptr) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    --my_size;
    delete node;
  }
}

template <typename T> void LinkedList<T>::erase(Nodeptr toRemove) {
  if (!toRemove) {
    return;
  }
  Nodeptr node = head;
  size_t i;
  size_t siz = size();
  for (i = 0; i < siz; ++i) {

    if (node == toRemove) {
      break;
    }
    node = node->next;
  }

  if (node == head) {
    pop_front();
  } else if (node == tail) {
    pop_back();
  } else if (node != nullptr) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    --my_size;
    delete node;
  }
}

template <typename T> void LinkedList<T>::clear() {
  Node<T> *current = head;
  while (current) {
    Node<T> *next = current->next;
    delete current;
    current = next;
    --my_size;
  }
  head = tail = nullptr;
}

template <typename T> bool LinkedList<T>::empty() const { return size() == 0; }

template <typename T> const size_t &LinkedList<T>::size() const noexcept {
  return my_size;
}

template <typename T> size_t LinkedList<T>::firstIndex() const { return 0; }

template <typename T> size_t LinkedList<T>::lastIndex() const {
  if (empty()) {
    throw PositionException("List empty, no last Index");
  }
  return size() - 1;
}

template <typename T> std::string LinkedList<T>::str() const {
  std::stringstream ss;

  Node<T> *node = head;
  ss << '[';
  while (node != nullptr) {
    if (node->next != nullptr) {
      ss << node->data << ", ";
    } else {
      ss << node->data;
    }

    node = node->next;
  }
  ss << ']';

  return ss.str();
}

template <typename T> size_t LinkedList<T>::indexOf(const T &data) const {
  size_t foundIndex = std::string::npos;

  if (empty()) {
    return foundIndex;
  }

  Node<T> *node = head;
  size_t listSize = size();
  for (size_t indexOf = 0; indexOf < listSize; ++indexOf) {
    if (data == node->data) {
      foundIndex = indexOf;
      break;
    }
    node = node->next;
  }
  return foundIndex;
}

template <typename T> void LinkedList<T>::swap(Node<T> *l, Node<T> *r) {
  Node<T> tmp = *l;
  *l = *r;
  *r = tmp;
}

template <typename T>
void LinkedList<T>::swap(const size_t &l, const size_t &r) {
  Node<T> *lNode = (*this)[l];
  Node<T> *rNode = (*this)[r];
  swap(lNode, rNode);
}

// A utility function to find last node of linked list
template <typename T> Node<T> *LinkedList<T>::lastNode() {
  Node<T> *node = head;
  while (node && node->next)
    node = node->next;
  return node;
}

template <typename T>
Node<T> *LinkedList<T>::partition(Node<T> *l, Node<T> *h) {
  // set pivot as h element
  Node<T> *pivot = h;

  // similar to i = l-1 for array implementation
  Node<T> *i = l->prev;

  // Similar to "for (int j = l; j <= h- 1; j++)"
  for (Node<T> *j = l; j != h; j = j->next) {
    if (j->data <= pivot->data) {
      // Similar to i++ for array
      i = (i == nullptr) ? l : i->next;

      swap(i, j);
    }
  }
  i = (i == nullptr) ? l : i->next; // Similar to i++
  swap(i, h);
  return i;
}

template <typename T> void LinkedList<T>::_quickSort(Node<T> *l, Node<T> *h) {
  if (h != nullptr && l != h && l != h->next) {
    Node<T> *p = partition(l, h);
    _quickSort(l, p->prev);
    _quickSort(p->next, h);
  }
}

template <typename T> void LinkedList<T>::sort() {
  Node<T> *last = lastNode();
  _quickSort(head, last);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const LinkedList<T> &list) {
  Node<T> *node = list.head;
  out << '[';
  while (node != nullptr) {
    if (node->next != nullptr) {
      out << node->data << ", ";
    } else {
      out << node->data;
    }

    node = node->next;
  }
  out << ']';

  return out;
}

template <typename T> void LinkedList<T>::push_front(const T &data) {
  insert(firstIndex(), data);
}

template <typename T> void LinkedList<T>::push_back(const T &data) {
  insert(data);
}

template <typename T> void LinkedList<T>::merge(LinkedList<T> &otherList) {
  for (auto element : otherList) {
    insert(element);
  }
  otherList.clear();
  sort();
}

template <typename T> T &LinkedList<T>::front() {
  if (empty()) {
    throw PositionException("List empty, no element at front - front()");
  }
  return head->data;
}

template <typename T> const T &LinkedList<T>::front() const {
  if (empty()) {
    throw PositionException("List empty, no element at front - front()");
  }
  return head->data;
}

template <typename T> T &LinkedList<T>::back() {
  if (empty()) {
    throw PositionException("List empty, no element at front - back()");
  }
  return tail->data;
}

template <typename T> const T &LinkedList<T>::back() const {
  if (empty()) {
    throw PositionException("List empty, no element at front - back()");
  }
  return tail->data;
}

template <typename T> void LinkedList<T>::unique() {
  if (empty()) {
    throw PositionException("List empty, no element to remove - unique()");
  }

  Nodeptr first = head;
  Nodeptr last = tail;
  Nodeptr next = first;

  while (next != last) {
    next = next->next;
    if (!next) {
      break;
    }

    if (*first == *next) {
      erase(next);
      next = first;
    } else {
      first = next;
    }
  }
}
