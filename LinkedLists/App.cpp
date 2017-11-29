// LinkedLists.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "LinkedList.h"

void log(const std::string& out) {
  OutputDebugStringA(out.c_str());
}

// Single node in the list
struct node {
	int data;
	struct node* next;
};


// LinkedList
struct list {
  node  *head, *tail;
  list() {
    head = NULL;
    tail = NULL;
  }
};

void initNode(struct node* head, int value) {
  head->data = value;
  head->next = NULL;
}

void addNode(struct node* head, int value) {
  node* newNode = new node;
  newNode->data = value;
  newNode->next = NULL;
  node* cur = head;
  while (cur) {
    if (cur->next == NULL) {
      cur->next = newNode;
      return;
    }
    cur = cur->next;
  }
}

void insertFront(node** head, int n) {
  node* newNode = new node;
  newNode->data = n;
  newNode->next = *head;
  *head = newNode;
}

node* search(node* head, int toFind) {
  node* cur = head;
  while (cur) {
    if (cur->data == toFind) {
      break;
    }
    cur = cur->next;
  }
  return cur;
}


// Return the number of nodes in a list (while-loop version)
int Length(struct node* head) {
	int count = 0;
	struct node* current = head;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return(count);
}

void display(struct node* head) {
  
  node* list = head;
  OutputDebugStringA("\r\n");OutputDebugStringA("\r\n");
  OutputDebugStringA("\r\n");
  while (list) {
    char buffer[100];
    sprintf_s(buffer, "%d ", list->data);
    OutputDebugStringA(buffer);
    list = list->next;
  }
  OutputDebugStringA("\r\n");
}


int main() {

  LinkedList ll;
  
  for (int i = 0; i < 10; i++) {
    ll.add(i);
  }
  ll.remove(5);
  ll.print();
  return 0;
}

