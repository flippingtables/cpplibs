// LinkedLists.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "LinkedList.h"

int main() {
  try
  {
    

    LinkedList<int> ll;
    ll.remove(0);

    /*int veryLarge = 1;
    for (int i = 0; i < veryLarge; i++) {
      ll.insert(i);
    }
    ll.remove(5);
    x = ll.get(1000);
    ll.clear();

    std::cout << "Press enter to close.\n";
*/
    std::cin.ignore();
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
  
  return 0;
}

