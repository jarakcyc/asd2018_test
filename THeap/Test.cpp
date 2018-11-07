#include <bits/stdc++.h>

#include "UnitTestFramework.h"
#include "Test.h"

#include "TVector.cpp"
#include "THeap.cpp"

using namespace std;

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestTVector, "TestTVector");
    tr.RunTest(TestTHeap, "TestTHeap");
}

void TestTVector() {
    {
        TVector<int> a;

        Assert(a.is_empty(), "TestTVector_test_1");

        a.push_back(1);
        a.push_back(2);
        a.push_back(3);

        Assert(!a.is_empty(), "TestTVector_test_2");
        Assert(a[0] == 1 && a[1] == 2 && a[2] == 3, "TestTVector_test_3");

        a.pop_back();
        a.pop_back();
        a.pop_back();
        Assert(a.is_empty(), "TestTVector_test_4");
    }
}

void TestTHeap() {
    {
        THeap<int> heap;
        Assert(heap.is_empty(), "TestTHeap_test_1");
        heap.insert(3);
        heap.insert(1);
        heap.insert(4);
        Assert(!heap.is_empty(), "TestTHeap_test_2");
        Assert(heap.get_min() == 1, "TestTHeap_test_3");
        Assert(heap.extract_min() == 1, "TestTHeap_test_4");
        Assert(heap.get_min() == 3, "TestTHeap_test_5");
    }
}
