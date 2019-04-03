#include "stdafx.h"

#include "LinkedList.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinkedListTest
{
  TEST_CLASS(UnitTest1) {
public:

  TEST_METHOD(TestAdd) {
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    std::string expected("[1, 2, 3, 4]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(TestAddOne) {
    LinkedList<int> list;
    list.add(1);
    std::string expected("[1]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(TestRemove) {
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);

    list.remove(3);
    std::string expected("[1, 2, 4]");
    Assert::AreEqual(expected, list.str());
  }


  TEST_METHOD(TestRemove1) {
    LinkedList<int> list;
    list.add(0);
    list.add(1);
    list.remove((size_t)0);
    Assert::AreEqual((size_t)1, list.size());
  }


  TEST_METHOD(TestRemove2) {
    LinkedList<int> list;
    list.add(0);
    list.add(1);
    list.remove((int)0);
    Assert::AreEqual((size_t)1, list.size());
  }

  TEST_METHOD(TestRemove3) {
    LinkedList<int> list;
    list.remove((size_t)0);
    Assert::AreEqual((size_t)0, list.size());
  }

  TEST_METHOD(TestRemove4) {
    LinkedList<int> list;
    list.remove((size_t)2);
    Assert::AreEqual((size_t)0, list.size());
  }

  TEST_METHOD(TestRemove5) {
    LinkedList<int> list;
    list.add(0);
    list.remove((size_t)2);
    Assert::AreEqual((size_t)1, list.size());
  }

  TEST_METHOD(TestRemoveEmpty) {
    LinkedList<int> list;
    list.remove(3);
    Assert::IsTrue(list.empty());
  }

  TEST_METHOD(TestRemoveAt) {
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);

    size_t index = 3;
    list.remove(index);
    std::string expected("[1, 2, 3]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(TestRemoveFromBeginning) {
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);

    list.removeFromBeginning();
    std::string expected("[2, 3, 4]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(TestRemoveFromEnd) {
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);

    list.removeFromEnd();
    std::string expected("[1, 2, 3]");
    Assert::AreEqual(expected, list.str());
  }



  TEST_METHOD(TestRemoveAll0) {
    LinkedList<std::string> list;
    list.add("1");
    list.add("2");
    list.add("3");
    list.add("4");

    list.remove("4");
    list.remove("1");
    std::string expected("[2, 3]");

    Assert::AreEqual(expected, list.str());
  }
  TEST_METHOD(TestRemoveAll1) {
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);

    std::initializer_list<int> arr = { 1,2,3,4 };
    list.removeAll(arr);
    std::string expected("[]");

    Assert::AreEqual(expected, list.str());    
  }


  TEST_METHOD(TestSize) {
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);

    size_t expected = 4;
    Assert::AreEqual(expected, list.size());
  }

  TEST_METHOD(TestClearOne) {
    LinkedList<int> list;
    list.add(1);
    list.clear();
    size_t expected = 0;
    Assert::AreEqual(expected, list.size());
  }

  TEST_METHOD(TestClearSeveral) {
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.clear();
    size_t expected = 0;
    Assert::AreEqual(expected, list.size());
  }

  TEST_METHOD(TestAddAt) {
    LinkedList<int> list;
    size_t index = 3;
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);
    list.add(index, 666);
    std::string expected("[1, 2, 3, 666, 4, 5]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(TestAddAtFirst) {
    LinkedList<int> list;
    size_t index = 0;
    list.add(index, 666);
    std::string expected("[666]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(TestOperatorSquare) {
    LinkedList<int> list;
    list.add(666);
    Node<int> n = *list[0];
    Assert::IsTrue(n._next == n._prev);
  }

  TEST_METHOD(TestOperatorSquareNextPrev) {
    LinkedList<int> list;
    list.add(100);
    list.add(666);
    list.add(200);
    Node<int> n = *list[1];
    Assert::IsTrue(n._prev->_data == 100);
    Assert::IsTrue(n._next->_data == 200);
  }

  TEST_METHOD(TestOperatorSquarePrevNULL) {
    LinkedList<int> list;
    list.add(100);
    list.add(666);
    list.add(200);
    Node<int> n = *list[0];
    Assert::IsTrue(n._prev == nullptr);
  }

  TEST_METHOD(TestOperatorSquareNextNULL) {
    LinkedList<int> list;
    size_t index = 0;
    list.add(100);
    list.add(666);
    list.add(200);
    Node<int> n = *list[2];
    Assert::IsTrue(n._next == nullptr);
  }

  TEST_METHOD(TestContainsEmpty) {
    LinkedList<int> list;
    Assert::IsTrue(false == list.contains(0));
  }

  TEST_METHOD(TestContainsNotEmpty) {
    LinkedList<int> list;
    list.add(100);
    list.add(666);
    list.add(200);
    Assert::IsTrue(true == list.contains(666));
  }

  TEST_METHOD(TestIndexOfEmptyAssertCatch) {
    LinkedList<int> list;
    size_t index = list.indexOf(0);
    Assert::AreEqual(index, std::string::npos);
  }

  TEST_METHOD(TestIndexOfNegative) {
    LinkedList<int> list;
    size_t index = list.indexOf(-1);
    Assert::AreEqual(index, std::string::npos);
  }

  TEST_METHOD(TestIndexOf) {
    LinkedList<int> list;
    list.add(100);
    list.add(666);
    list.add(200);
    Assert::IsTrue(1 == list.indexOf(666));
  }

  TEST_METHOD(TestIndexOfNotFound) {
    LinkedList<int> list;
    list.add(100);
    list.add(666);
    list.add(200);
    size_t index = list.indexOf(777);
    Assert::AreEqual(index, std::string::npos);
  }

  TEST_METHOD(TestSwap) {
    LinkedList<int> list;
    list.add(1);
    list.add(3);
    list.add(2);
    list.swap(1, 2);
    std::string expected("[1, 2, 3]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(TestSort) {
    LinkedList<int> list;
    list.add(1);
    list.add(3);
    list.add(2);
    list.add(9);
    list.add(4);
    list.sort();
    std::string expected("[1, 2, 3, 4, 9]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(TestSort1) {
    LinkedList<int> list;
    list.add(2);
    list.add(1);
    list.sort();
    std::string expected("[1, 2]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(TestSort2) {
    LinkedList<int> list;
    list.add(1);
    list.sort();
    std::string expected("[1]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(TestSortLetters) {
    LinkedList<std::string> list;
    list.add("a");
    list.add("c");
    list.add("b");
    list.sort();
    std::string expected("[a, b, c]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(TestOut) {
    std::ostream stream(nullptr);
    std::stringbuf str;
    stream.rdbuf(&str);

    LinkedList<std::string> list;
    list.add("a");
    list.add("c");
    list.add("b");
    stream << list;
    std::string expected("[a, c, b]");
    Assert::AreEqual(expected, str.str());
  }

  TEST_METHOD(TestSpeed1) {
    LinkedList<int> list;
    size_t size = 1000;
    for (int i = 0; i < size; ++i) {
      list.add(i);
    }

    for (int i = 0; i < size; ++i) {
      list.remove(i);
    }

    Assert::AreEqual((size_t)0, list.size());
  }

  };
}