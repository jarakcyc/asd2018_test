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
    {///Test_Heap_1
        THeap<int> heap;
        Assert(heap.is_empty(), "Test_Heap_1");
        heap.insert(3);
        heap.insert(1);
        heap.insert(4);
        Assert(!heap.is_empty(), "Test_Heap_1");
        Assert(heap.get_min() == 1, "Test_Heap_1");
        Assert(heap.extract_min() == 1, "Test_Heap_1");
        Assert(heap.get_min() == 3, "Test_Heap_1");
    }
    {///Test_Heap_2
        int start = clock();
        THeap<int> heap;
        priority_queue<int, vector<int>, greater<int> > std_heap;
        const int bnd = 1e7 + 7;
        for (int i = 0; i < 1e5; ++i) {
            int x = rnd() % bnd;
            heap.insert(x);
            std_heap.push(x);
        }
        for (int i = 0; i < 1e5; ++i) {
            Assert(heap.get_min() == std_heap.top(), "Test_Heap_2");
            heap.extract_min();
            std_heap.pop();
        }
        cerr << "Test_Heap_2 time used: " << (clock() - start) / 1000.0 << endl;
        // average result = 0.3
    }
    {///Test_Heap_3
        THeap<int> heap;

        auto it5 = heap.insert(5);
        auto it3 = heap.insert(3);
        auto it1 = heap.insert(1);
        auto it4 = heap.insert(4);

        heap.erase(it3);
        Assert(heap.get_min() == 1, "Test_Heap_3");

        heap.erase(it1);
        Assert(heap.get_min() == 4, "Test_Heap_3");

        try {
            heap.erase(it1);
        } catch (...) {
            cerr << "Test_Heap_2 OK" << endl;
        }

        heap.erase(it4);
        Assert(heap.get_min() == 5, "Test_Heap_3");

        heap.erase(it5);
        Assert(heap.is_empty(), "Test_Heap_3");
    }
    {///Test_Heap_4
        THeap<int> heap;

        auto it2 = heap.insert(2);
        auto it1 = heap.insert(1);
        auto it4 = heap.insert(4);
        auto it5 = heap.insert(5);

        heap.change(it1, 5);
        Assert(heap.get_min() == 2, "Test_Heap_4");

        heap.change(it4, 1);
        Assert(heap.get_min() == 1, "Test_Heap_4");
    }
    {///Test_Heap_5
        /*
        insert:
        2 5 0 4 6 3 1
        erase:
        5 0 1 4 2 3 6
        */
        THeap<int> heap;

        auto it2 = heap.insert(2);
        auto it5 = heap.insert(5);
        auto it0 = heap.insert(0);
        auto it4 = heap.insert(4);
        auto it6 = heap.insert(6);
        auto it3 = heap.insert(3);
        auto it1 = heap.insert(1);

        Assert(heap.get_min() == 0, "Test_Heap_5");

        heap.erase(it5);
        Assert(heap.get_min() == 0, "Test_Heap_5");
        heap.erase(it0);
        Assert(heap.get_min() == 1, "Test_Heap_5");
        heap.erase(it1);
        Assert(heap.get_min() == 2, "Test_Heap_5");
        heap.erase(it4);
        Assert(heap.get_min() == 2, "Test_Heap_5");
        heap.erase(it2);
        Assert(heap.get_min() == 3, "Test_Heap_5");
        heap.erase(it3);
        Assert(heap.get_min() == 6, "Test_Heap_5");
        heap.erase(it6);
        Assert(heap.is_empty(), "Test_Heap_5");
    }
    for (int iter = 0; iter < 1000; ++iter) {///Test_Heap_6
        THeap<int> heap;
        vector<int> q;

        const int n = 50;

        vector<pair<THeap<int>::Pointer, int> > order;

        for (int i = 0; i < n; ++i) {
            int x = rnd() % n;
            order.push_back(make_pair(heap.insert(x), x));
            q.push_back(x);
        }

        shuffle(order.begin(), order.end(), rnd);

        vector<int> foo;
        for (int i = 0; i < n; ++i) {
            sort(q.begin(), q.end());
            Assert(q[0] == heap.get_min(), "Test_Heap_6");

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
    {///Test_Heap_7
        vector<int> a;
        const int n = 100000;

        for (int i = 0; i < n; ++i) {
            a.push_back(i);
        }

        shuffle(a.begin(), a.end(), rnd);

        int start = clock();

        THeap<int> heap(a.begin(), a.end());
        sort(a.begin(), a.end());

        assert(a.size() == n);
        for (int i = 0; i < n; ++i) {
            Assert(heap.extract_min() == a[i], "Test_Heap_7");
        }

        cerr << "Test_Heap_7 time used: " << (clock() - start) / 1000.0 << endl;
        // average result = 0.19
    }
}
