// LinkedLists.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "LinkedList.h"

int main() {
  int x, y;

  LinkedList<int> ll;
  int veryLarge = 10000000;
  for (int i = 0; i < veryLarge; i++) {
    ll.insert(i);
  }
  ll.remove(5);
  x = ll.get(1000);
  ll.clear();

  std::cout << "Press enter to close.\n";

  std::cin.ignore();
  return 0;
}

