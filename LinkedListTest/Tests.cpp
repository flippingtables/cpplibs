#include "stdafx.h"

#include "LinkedList.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinkedListTest
{
  TEST_CLASS(UnitTest1) {
public:
  TEST_METHOD(Add) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    std::string expected("[1, 2, 3, 4]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(AddOne) {
    LinkedList<int> list;
    list.insert(1);
    std::string expected("[1]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(AddInitializerList1) {
    LinkedList<int> list;
    list.insert({ 1, 2, 3, 4 });
    std::string expected("[1, 2, 3, 4]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(AddInitializerList2) {
    LinkedList<int> list;
    list.insert({ false, false, false, true });
    std::string expected("[0, 0, 0, 1]");
    Assert::AreEqual(expected, list.str());
  }
  TEST_METHOD(Remove) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);

    list.remove(3);
    std::string expected("[1, 2, 4]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(RemoveAll2) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(1);
    list.insert(3);
    list.insert(5);
    list.insert(1);

    list.remove(1);

    std::string expected("[2, 3, 5]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(RemoveAll3) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(1);

    list.remove(1);

    std::string expected("[]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(Remove1) {
    LinkedList<int> list;
    list.insert(0);
    list.insert(1);
    list.remove((size_t)0);
    Assert::AreEqual((size_t)1, list.size());
  }


  TEST_METHOD(Remove2) {
    LinkedList<int> list;
    list.insert(0);
    list.insert(1);
    list.remove((int)0);
    Assert::AreEqual((size_t)1, list.size());
  }

  TEST_METHOD(Remove3) {
    LinkedList<int> list;
    list.remove((size_t)0);
    Assert::AreEqual((size_t)0, list.size());
  }

  TEST_METHOD(Remove4) {
    LinkedList<int> list;
    list.remove((size_t)2);
    Assert::AreEqual((size_t)0, list.size());
  }

  TEST_METHOD(Remove5) {
    LinkedList<int> list;
    list.insert(0);
    list.remove((size_t)2);
    Assert::AreEqual((size_t)1, list.size());
  }

  TEST_METHOD(RemoveEmpty) {
    LinkedList<int> list;
    Assert::ExpectException<PositionException>([&] {list.remove(3); });
  }

  TEST_METHOD(RemoveAt) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);

    size_t index = 3;
    list.remove(index);
    std::string expected("[1, 2, 3]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(RemoveFromBeginning) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);

    list.pop_front();
    std::string expected("[2, 3, 4]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(RemoveFromBeginningEmpty) {
    LinkedList<int> list;
    Assert::ExpectException<PositionException>([&] { list.pop_front(); });
  }

  TEST_METHOD(RemoveFromEnd) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);

    list.pop_back();
    std::string expected("[1, 2, 3]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(RemoveFromEndEmpty) {
    LinkedList<int> list;
    Assert::ExpectException<PositionException>([&] { list.pop_back(); });
  }

  TEST_METHOD(RemoveAll0) {
    LinkedList<std::string> list;
    list.insert("1");
    list.insert("2");
    list.insert("3");
    list.insert("4");

    list.remove("4");
    list.remove("1");
    std::string expected("[2, 3]");

    Assert::AreEqual(expected, list.str());
  }
  TEST_METHOD(RemoveAll1) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);

    std::initializer_list<int> arr = { 1,2,3,4 };
    list.remove(arr);
    std::string expected("[]");

    Assert::AreEqual(expected, list.str());
  }


  TEST_METHOD(Size) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);

    size_t expected = 4;
    Assert::AreEqual(expected, list.size());
  }

  TEST_METHOD(ClearOne) {
    LinkedList<int> list;
    list.insert(1);
    list.clear();
    size_t expected = 0;
    Assert::AreEqual(expected, list.size());
  }

  TEST_METHOD(ClearSeveral) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.clear();
    size_t expected = 0;
    Assert::AreEqual(expected, list.size());
  }

  TEST_METHOD(AddAt) {
    LinkedList<int> list;
    size_t index = 3;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(index, 666);
    std::string expected("[1, 2, 3, 666, 4, 5]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(AddAtFirst) {
    LinkedList<int> list;
    size_t index = 0;
    list.insert(index, 666);
    std::string expected("[666]");
    std::string out = list.str();
    Assert::AreEqual(expected, out);
  }

  TEST_METHOD(AddOutSideBoundsException) {
    LinkedList<int> list;
    size_t index = 1;
    Assert::ExpectException<PositionException>([&] { list.insert(index, 666); });
  }

  TEST_METHOD(OperatorSquare) {
    LinkedList<int> list;
    list.insert(666);
    Node<int> n = *list[0];
    Assert::IsTrue(n.next == n.prev);
  }

  TEST_METHOD(OperatorSquareNextPrev) {
    LinkedList<int> list;
    list.insert(100);
    list.insert(666);
    list.insert(200);
    Node<int> n = *list[1];
    Assert::IsTrue(n.prev->data == 100);
    Assert::IsTrue(n.next->data == 200);
  }

  TEST_METHOD(OperatorSquarePrevNULL) {
    LinkedList<int> list;
    list.insert(100);
    list.insert(666);
    list.insert(200);
    Node<int> n = *list[0];
    Assert::IsTrue(n.prev == nullptr);
  }

  TEST_METHOD(OperatorSquareNextNULL) {
    LinkedList<int> list;
    size_t index = 0;
    list.insert(100);
    list.insert(666);
    list.insert(200);
    Node<int> n = *list[2];
    Assert::IsTrue(n.next == nullptr);
  }

  TEST_METHOD(ContainsEmpty) {
    LinkedList<int> list;
    Assert::IsTrue(false == list.contains(0));
  }

  TEST_METHOD(ContainsNotEmpty) {
    LinkedList<int> list;
    list.insert(100);
    list.insert(666);
    list.insert(200);
    Assert::IsTrue(true == list.contains(666));
  }

  TEST_METHOD(IndexOfEmptyAssertCatch) {
    LinkedList<int> list;
    size_t index = list.indexOf(0);
    Assert::AreEqual(index, std::string::npos);
  }

  TEST_METHOD(IndexOfNegative) {
    LinkedList<int> list;
    size_t index = list.indexOf(-1);
    Assert::AreEqual(index, std::string::npos);
  }

  TEST_METHOD(IndexOf) {
    LinkedList<int> list;
    list.insert(100);
    list.insert(666);
    list.insert(200);
    Assert::IsTrue(1 == list.indexOf(666));
  }

  TEST_METHOD(IndexOfNotFound) {
    LinkedList<int> list;
    list.insert(100);
    list.insert(666);
    list.insert(200);
    size_t index = list.indexOf(777);
    Assert::AreEqual(index, std::string::npos);
  }

  TEST_METHOD(Swap) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(3);
    list.insert(2);
    list.swap(1, 2);
    std::string expected("[1, 2, 3]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(Sort) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(3);
    list.insert(2);
    list.insert(9);
    list.insert(4);
    list.sort();
    std::string expected("[1, 2, 3, 4, 9]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(Sort1) {
    LinkedList<int> list;
    list.insert(2);
    list.insert(1);
    list.sort();
    std::string expected("[1, 2]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(Sort2) {
    LinkedList<int> list;
    list.insert(1);
    list.sort();
    std::string expected("[1]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(SortLetters) {
    LinkedList<std::string> list;
    list.insert("a");
    list.insert("c");
    list.insert("b");
    list.sort();
    std::string expected("[a, b, c]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(Out) {
    std::ostream stream(nullptr);
    std::stringbuf str;
    stream.rdbuf(&str);

    LinkedList<std::string> list;
    list.insert("a");
    list.insert("c");
    list.insert("b");
    stream << list;
    std::string expected("[a, c, b]");
    Assert::AreEqual(expected, str.str());
  }

  TEST_METHOD(Speed1) {
    LinkedList<int> list;
    int size = 1000;
    for (int i = 0; i < size; ++i) {
      list.insert(i);
    }

    for (int i = 0; i < size; ++i) {
      list.remove(i);
    }

    Assert::AreEqual((size_t)0, list.size());
  }

  TEST_METHOD(PushFront1) {
    LinkedList<std::string> list;
    list.insert("b");
    list.insert("c");
    list.push_front("a");

    std::string expected("[a, b, c]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(PushFront2) {
    LinkedList<int> list;
    list.insert(2);
    list.insert(3);
    list.push_front(1);

    std::string expected("[1, 2, 3]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(PushBack1) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(3);
    list.push_back(2);

    std::string expected("[1, 3, 2]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(PushBack2) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(3);
    list.push_back(2);
    list.push_back(4);

    std::string expected("[1, 3, 2, 4]");
    Assert::AreEqual(expected, list.str());
  }

  TEST_METHOD(Merge1) {
    LinkedList<int> list1;
    list1.insert(1);
    list1.insert(3);

    LinkedList<int> list2;
    list2.insert(4);
    list2.insert(2);

    list1.merge(list2);
    std::string expected("[1, 2, 3, 4]");
    Assert::AreEqual(expected, list1.str());
  }

  TEST_METHOD(Merge2) {
    LinkedList<std::string> list1;
    list1.insert("1");
    list1.insert("3");

    LinkedList<std::string> list2;
    list2.insert("4");
    list2.insert("2");

    list1.merge(list2);
    std::string expected("[1, 2, 3, 4]");
    Assert::AreEqual(expected, list1.str());
  }

  TEST_METHOD(Merge3) {
    LinkedList<std::string> list1;
    list1.insert("1");
    list1.insert("3");

    LinkedList<std::string> list2;
    list2.insert("4");
    list2.insert("2");

    list1.merge(list2);

    // "The container other becomes empty after the operation."
    std::string expected("[]");
    Assert::AreEqual(expected, list2.str());
  }

  TEST_METHOD(FindOnList1) {
    LinkedList<std::string> l;
    l.insert("1");
    l.insert("3");
    l.insert("4");
    l.insert("2");

    auto it = std::find(l.begin(), l.end(), "4");

    Assert::IsNotNull(&it);
  }

  TEST_METHOD(FindOnList2) {
    LinkedList<std::string> l;
    l.insert("1");
    l.insert("3");
    l.insert("4");
    l.insert("2");

    auto it = std::find(l.begin(), l.end(), "5");
    bool isEqual = it == l.end();
    Assert::AreEqual(isEqual, true);
  }

  TEST_METHOD(FindOnList3) {
    LinkedList<int> l;
    l.insert(1);
    l.insert(2);
    l.insert(3);
    l.insert(4);

    auto it = std::find(l.cbegin(), l.cend(), 5);
    bool isEqual = l.cend() == it;
    Assert::AreEqual(isEqual, true);
  }

  TEST_METHOD(FindOnList4) {
    LinkedList<int> l;
    l.insert(1);
    l.insert(2);
    l.insert(3);
    l.insert(4);

    auto it = std::find(l.cbegin(), l.cend(), 3);
    bool isEqual = l.cend() != it;
    Assert::AreEqual(isEqual, true);
  }

  TEST_METHOD(FrontEmptyException) {
    LinkedList<int> list;
    Assert::ExpectException<PositionException>([&] { list.front(); });
  }

  TEST_METHOD(Front1) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(2);

    Assert::AreEqual(1, list.front());
  }

  TEST_METHOD(Front2) {
    LinkedList<std::string> list;
    list.insert("1");
    list.insert("2");
    std::string expected("1");
    Assert::AreEqual(expected, list.front());
  }

  TEST_METHOD(Front3) {
    std::string expected = "1";
    const LinkedList<std::string> list({expected, "2"});
    auto front = list.front();
    Assert::AreEqual(expected, front);
  }

  TEST_METHOD(BackEmptyException) {
    LinkedList<int> list;
    Assert::ExpectException<PositionException>([&] { list.front(); });
  }

  TEST_METHOD(Back1) {
    LinkedList<int> list;
    list.insert(1);
    list.insert(2);
    Assert::AreEqual(2, list.back());
  }

  TEST_METHOD(Back2) {
    LinkedList<std::string> list;
    list.insert("1");
    list.insert("2");
    std::string expected("2");
    Assert::AreEqual(expected, list.back());
  }

  TEST_METHOD(Back3) {
    std::string expected = "2";
    const LinkedList<std::string> list({ "1", expected});
    auto front = list.back();
    Assert::AreEqual(expected, front);
  }

  };
}
