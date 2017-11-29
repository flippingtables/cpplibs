#include "stdafx.h"
#include "CppUnitTest.h"
#include "LinkedList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinkedListTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestAdd)
		{
      LinkedList list;
      list.add(1);
      list.add(2);
      list.add(3);
      list.add(4);
      std::string expected("1 2 3 4");
      Assert::AreEqual(expected, list.str());
		}

    TEST_METHOD(TestAddOne) {
      LinkedList list;
      list.add(1);
      std::string expected("1");
      Assert::AreEqual(expected, list.str());
    }

    TEST_METHOD(TestRemove) {
      LinkedList list;
      list.add(1);
      list.add(2);
      list.add(3);
      list.add(4);

      list.remove(3);
      std::string expected("1 2 4");
      Assert::AreEqual(expected, list.str());
    }

    TEST_METHOD(TestRemoveAt) {
      LinkedList list;
      list.add(1);
      list.add(2);
      list.add(3);
      list.add(4);

      size_t index = 3;
      list.remove(index);
      std::string expected("1 2 3");
      Assert::AreEqual(expected, list.str());
    }

    TEST_METHOD(TestSize) {
      LinkedList list;
      list.add(1);
      list.add(2);
      list.add(3);
      list.add(4);

      size_t expected = 4;
      Assert::AreEqual(expected, list.size());
    }

    TEST_METHOD(TestClearOne) {
      LinkedList list;
      list.add(1);
      list.clear();
      size_t expected = 0;
      Assert::AreEqual(expected, list.size());
    }
    
    TEST_METHOD(TestClearSeveral) {
      LinkedList list;
      list.add(1);
      list.add(2);
      list.add(3);
      list.add(4);
      list.clear();
      size_t expected = 0;
      Assert::AreEqual(expected, list.size());
    }

    TEST_METHOD(TestAddAt) {
      LinkedList list;
      size_t index = 3;
      list.add(1);
      list.add(2);
      list.add(3);
      list.add(4);
      list.add(5);
      list.add(index, 666);
      std::string expected("1 2 3 666 4 5");
      Assert::AreEqual(expected, list.str());
    }
    
    TEST_METHOD(TestAddAtFirst) {
      LinkedList list;
      size_t index = 0;
      list.add(index, 666);
      std::string expected("666");
      Assert::AreEqual(expected, list.str());
    }

    TEST_METHOD(TestOperatorSquare) {
      LinkedList list;
      list.add(666);
      Node n = list[0];
      Assert::IsTrue(n._next == n._prev);
    }

    TEST_METHOD(TestOperatorSquareNextPrev) {
      LinkedList list;
      list.add(100);
      list.add(666);
      list.add(200);
      Node n = list[1];
      Assert::IsTrue(n._prev->data == 100);
      Assert::IsTrue(n._next->data == 200);
    }

    TEST_METHOD(TestOperatorSquarePrevNULL) {
      LinkedList list;
      list.add(100);
      list.add(666);
      list.add(200);
      Node n = list[0];
      Assert::IsTrue(n._prev == nullptr);
    }

    TEST_METHOD(TestOperatorSquareNextNULL) {
      LinkedList list;
      size_t index = 0;
      list.add(100);
      list.add(666);
      list.add(200);
      Node n = list[2];
      Assert::IsTrue(n._next == nullptr);
    }

    TEST_METHOD(TestContainsEmpty) {
      LinkedList list;      
      Assert::IsTrue(false == list.contains(0));
    }

    TEST_METHOD(TestContainsNotEmpty) {
      LinkedList list;
      list.add(100);
      list.add(666);
      list.add(200);
      Assert::IsTrue(true == list.contains(666));
    }
	};
}