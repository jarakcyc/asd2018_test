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

        heap.insert(1);
        heap.insert(3);
        heap.insert(2);
        heap.insert(1);
    }
    {/// Test_Heap_1
        TBinomialHeap<int> heap;
        Assert(heap.is_empty(), "Test_Heap_1");
        heap.insert(3);
        heap.insert(1);
        heap.insert(4);
        Assert(!heap.is_empty(), "Test_Heap_1");
        Assert(heap.get_min() == 1, "Test_Heap_1");
    }
    {/// Test_Heap_2
        TBinomialHeap<int> heap;
        Assert(heap.is_empty(), "Test_Heap_2");
        heap.insert(3);
        heap.insert(1);
        heap.insert(4);
        Assert(!heap.is_empty(), "Test_Heap_2");
        Assert(heap.get_min() == 1, "Test_Heap_2");
        Assert(heap.extract_min() == 1, "Test_Heap_2");
        Assert(heap.get_min() == 3, "Test_Heap_2");
    }
    {///Test_Heap_3
        TBinomialHeap<int> heap;
        Assert(heap.is_empty(), "Test_Heap_3");
        heap.insert(3);
        heap.insert(1);
        heap.insert(4);
        heap.insert(0);
        heap.insert(10);
        Assert(!heap.is_empty(), "Test_Heap_3");
        Assert(heap.get_min() == 0, "Test_Heap_3");
        Assert(heap.extract_min() == 0, "Test_Heap_3");
        Assert(heap.get_min() == 1, "Test_Heap_3");
    }
    {///Test_Heap_4
        TBinomialHeap<int> heap;

        heap.insert(4);
        heap.insert(0);
        heap.insert(4);
        heap.insert(2);
        heap.insert(4);

        Assert(heap.get_min() == 0, "Test_Heap_4");
        Assert(heap.extract_min() == 0, "Test_Heap_4");
        Assert(heap.get_min() == 2, "Test_Heap_4");
    }
    {///Test_Heap_5
        TBinomialHeap<int> heap;

        heap.insert(4);

        Assert(heap.extract_min() == 4, "Test_Heap_5");
    }
    {///Test_Heap_6
        TBinomialHeap<int> heap;

        heap.insert(4);
        heap.insert(0);
        heap.insert(2);
        heap.insert(0);
        heap.insert(3);

        Assert(heap.extract_min() == 0, "Test_Heap_6");
        Assert(heap.extract_min() == 0, "Test_Heap_6");
        Assert(heap.extract_min() == 2, "Test_Heap_6");
        Assert(heap.extract_min() == 3, "Test_Heap_6");
        Assert(heap.extract_min() == 4, "Test_Heap_6");
    }
    {///Test_Heap_7
        int start = clock();
        TBinomialHeap<int> heap;
        priority_queue<int, vector<int>, greater<int> > std_heap;
        const int bnd = 1e5;
        for (int i = 0; i < 100000; ++i) {
            int x = rnd() % bnd;
            heap.insert(x);
            std_heap.push(x);
        }
        for (int i = 0; i < 100000; ++i) {
            Assert(heap.get_min() == std_heap.top(), "Test_Heap_7");
            heap.extract_min();
            std_heap.pop();
        }
        cerr << "time used : ";
        cerr << (clock() - start) / 1000.0 << endl;
    }
    {///Test_Heap_8
        TBinomialHeap<int> heap;

        auto it1 = heap.insert(1);
        auto it2 = heap.insert(2);

        heap.erase(it1);
        Assert(heap.get_min() == 2, "Test_Heap_8");
        heap.erase(it2);
        Assert(heap.is_empty(), "Test_Heap_8");
    }
    {///Test_Heap_9
        TBinomialHeap<int> heap;

        auto it1 = heap.insert(1);
        auto it2 = heap.insert(2);

        heap.erase(it2);
        Assert(heap.get_min() == 1, "Test_Heap_9");
        heap.erase(it1);
        Assert(heap.is_empty(), "Test_Heap_9");
    }
    {///Test_Heap_10
        TBinomialHeap<int> heap;

        auto it5 = heap.insert(5);
        auto it3 = heap.insert(3);
        auto it1 = heap.insert(1);
        auto it4 = heap.insert(4);

        heap.erase(it3);
        Assert(heap.get_min() == 1, "Test_Heap_10");

        heap.erase(it1);
        Assert(heap.get_min() == 4, "Test_Heap_10");

        try {
            heap.erase(it1);
        } catch (...) {
            cerr << "caught exception" << endl;
        }

        heap.erase(it4);
        Assert(heap.get_min() == 5, "Test_Heap_10");

        heap.erase(it5);
        Assert(heap.is_empty(), "Test_Heap_10");
    }
    {///Test_Heap_11
        TBinomialHeap<int> heap;

        auto it2 = heap.insert(2);
        auto it1 = heap.insert(1);
        auto it4 = heap.insert(4);
        auto it5 = heap.insert(5);

        heap.change(it1, 5);
        Assert(heap.get_min() == 2, "Test_Heap_11");

        heap.change(it4, 1);
        Assert(heap.get_min() == 1, "Test_Heap_11");
    }
    {///Test_Heap_12
        TBinomialHeap<int> heap;
        TBinomialHeap<int>::Pointer p[10];
        for (int i = 0; i < 10; ++i)
            p[i] = heap.insert(i);

        Assert(heap.get_min() == 0, "Test_Heap_12");
        heap.change(p[5], -1);
        Assert(heap.get_min() == -1, "Test_Heap_12");
        heap.extract_min();
        try {
            heap.erase(p[5]);
        }
        catch (...) {
            cerr << "Test exception_1 is OK" << endl;
        }
    }
    {///Test_Heap_13
        TBinomialHeap<int> heap;
        vector<int> q;

        const int n = 1000;

        vector<pair<TBinomialHeap<int>::Pointer, int> > order;

        for (int i = 0; i < n; ++i) {
            int x = rnd() % n;
            order.push_back(make_pair(heap.insert(x), x));
            q.push_back(x);
        }

        shuffle(order.begin(), order.end(), rnd);

        vector<int> foo;
        for (int i = 0; i < n; ++i) {
            sort(q.begin(), q.end());
            Assert(q[0] == heap.get_min(), "Test_Heap_13");

            auto p = order.back();
            order.pop_back();

            heap.erase(p.first);

            bool found = false;
            while (!q.empty()) {
                int cur = q.back();
                q.pop_back();

                if (cur == p.second && !found) {
                    found = true;
                } else {
                    foo.push_back(cur);
                }
            }

            while (!foo.empty()) {
                q.push_back(foo.back());
                foo.pop_back();
            }
        }
    }
}
