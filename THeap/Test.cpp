#include <bits/stdc++.h>

#include "UnitTestFramework.h"
#include "Test.h"

#include "TVector.h"
#include "THeap.h"

using namespace std;

mt19937 rnd(time(NULL));

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
    {
        TVector<int> v;
        vector<int> stdv;
        const int bnd = 1e7 + 7;
        for (int i = 0; i < 1e5; ++i) {
            int x = rnd() % bnd;
            v.push_back(x);
            stdv.push_back(x);
        }
        for (int i = 0; i < 1e5; ++i) {
            Assert(v.back() == stdv.back(), "TestTVector_test_5");
            v.pop_back();
            stdv.pop_back();
        }
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
    {
        THeap<int> heap;
        priority_queue<int, vector<int>, greater<int> > std_heap;
        const int bnd = 1e7 + 7;
        for (int i = 0; i < 1e5; ++i) {
            int x = rnd() % bnd;
            heap.insert(x);
            std_heap.push(x);
        }
        for (int i = 0; i < 1e5; ++i) {
            Assert(heap.get_min() == std_heap.top(), "TestTVector_test_6");
            heap.extract_min();
            std_heap.pop();
        }
    }
}
