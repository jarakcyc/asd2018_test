#include <bits/stdc++.h>

#include "UnitTestFramework.h"
#include "Test.h"
#include "TBinomialHeap.h"

using namespace std;

mt19937 rnd(time(NULL));

void TestTHeap();

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestTHeap, "TestHeap");
}

void TestTHeap() {
    {
        TBinomialHeap<int> heap;
        Assert(heap.is_empty(), "row_21");
        heap.insert(3);
        heap.insert(1);
        heap.insert(4);
        Assert(!heap.is_empty(), "row_25");
        Assert(heap.get_min() == 1, "row_26");
    }
    {
        TBinomialHeap<int> heap;
        Assert(heap.is_empty(), "row_30");
        heap.insert(3);
        heap.insert(1);
        heap.insert(4);
        Assert(!heap.is_empty(), "row_34");
        Assert(heap.get_min() == 1, "row_35");
        Assert(heap.extract_min() == 1, "row_36");
        Assert(heap.get_min() == 3, "row_37");
    }
    {
        TBinomialHeap<int> heap;
        Assert(heap.is_empty(), "row_41");
        heap.insert(3);
        heap.insert(1);
        heap.insert(4);
        heap.insert(0);
        heap.insert(10);
        Assert(!heap.is_empty(), "row_47");
        Assert(heap.get_min() == 0, "row_48");
        Assert(heap.extract_min() == 0, "row_49");
        Assert(heap.get_min() == 1, "row_50");
    }
    {
        TBinomialHeap<int> heap;

        heap.insert(4);
        heap.insert(0);
        heap.insert(4);
        heap.insert(2);
        heap.insert(4);

        Assert(heap.get_min() == 0, "row_61");
        Assert(heap.extract_min() == 0, "row_62");
        Assert(heap.get_min() == 2, "row_63");
    }
    {
        TBinomialHeap<int> heap;

        heap.insert(4);

        Assert(heap.extract_min() == 4, "row_70");
    }
    {
        TBinomialHeap<int> heap;

        heap.insert(4);
        heap.insert(0);
        heap.insert(2);
        heap.insert(0);
        heap.insert(3);

        Assert(heap.extract_min() == 0, "row_81");
        Assert(heap.extract_min() == 0, "row_82");
        Assert(heap.extract_min() == 2, "row_83");
        Assert(heap.extract_min() == 3, "row_84");
        Assert(heap.extract_min() == 4, "row_85");
    }
    {
        int start = clock();
        TBinomialHeap<int> heap;
        priority_queue<int, vector<int>, greater<int> > std_heap;
        const int bnd = 1e5;
        for (int i = 0; i < 200000; ++i) {
            int x = rnd() % bnd;
            heap.insert(x);
            std_heap.push(x);
        }
        for (int i = 0; i < 200000; ++i) {
            Assert(heap.get_min() == std_heap.top(), "row_98");
            heap.extract_min();
            std_heap.pop();
        }
        cerr << "time used : ";
        cerr << (clock() - start) / 1000.0 << endl;
    }
}
