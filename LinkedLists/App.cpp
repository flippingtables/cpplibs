// LinkedLists.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "LinkedList.h"

int main() {
  int x, y;
  {
    LinkedList<int> ll;

    for (int i = 0; i < 10000; i++) {
      ll.add(i);
    }
    ll.remove(5);
    x = ll.get(1000);
    //std::cout << ll.str();
  }
  std::cout << "Hello world\n" << x;

  {
    LinkedList<int> ll;

    for (int i = 0; i < 10000; i++) {
      ll.add(i);
    }
    ll.remove(5);
    y = ll.get(100);
    //std::cout << ll.str();
  }
  std::cout << "Hello world\n" << y;
  return 0;
}

