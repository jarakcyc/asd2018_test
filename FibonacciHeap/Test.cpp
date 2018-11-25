#include <bits/stdc++.h>

#include "UnitTestFramework.h"
#include "Test.h"
#include "FibonacciHeap.h"

using namespace std;

mt19937 rnd(time(NULL));

void TestTHeap();

void TestAll() {
	TestRunner tr;
	tr.RunTest(TestTHeap, "TestHeap");
}

void TestTHeap() {
	{
		FibonacciHeap<int> heap;
		Assert(heap.is_empty(), "row_1");
		heap.insert(3);
		heap.insert(1);
		heap.insert(4);
		Assert(!heap.is_empty(), "row_2");
		Assert(heap.get_min() == 1, "row_3");
	}
	{
        FibonacciHeap<int> heap;
        Assert(heap.is_empty(), "row_4");
        heap.insert(3);
        heap.insert(1);
        heap.insert(4);
        Assert(!heap.is_empty(), "row_5");
        Assert(heap.get_min() == 1, "row_6");
        Assert(heap.extract_min() == 1, "row_7");
        Assert(heap.get_min() == 3, "row_8");
    }
	{
		FibonacciHeap<int> heap;
		Assert(heap.is_empty(), "row_9");
		heap.insert(3);
		heap.insert(1);
		heap.insert(4);
		heap.insert(0);
		heap.insert(10);
		Assert(!heap.is_empty(), "row_10");
		Assert(heap.get_min() == 0, "row_11");
		Assert(heap.extract_min() == 0, "row_12");
		Assert(heap.get_min() == 1, "row_13");
	}
	{
		FibonacciHeap<int> heap;

		heap.insert(4);
		heap.insert(0);
		heap.insert(4);
		heap.insert(2);
		heap.insert(4);

		Assert(heap.get_min() == 0, "row_14");
		Assert(heap.extract_min() == 0, "row_15");
		Assert(heap.get_min() == 2, "row_16");
	}
	{
		FibonacciHeap<int> heap;

		heap.insert(4);

		Assert(heap.extract_min() == 4, "row_17");
	}
	{
		FibonacciHeap<int> heap;

		heap.insert(4);
		heap.insert(0);
		heap.insert(2);
		heap.insert(0);
		heap.insert(3);

		Assert(heap.extract_min() == 0, "row_18");
		Assert(heap.extract_min() == 0, "row_19");
		Assert(heap.extract_min() == 2, "row_20");
		Assert(heap.extract_min() == 3, "row_21");
		Assert(heap.extract_min() == 4, "row_22");
	}
	{
		int start = clock();
		FibonacciHeap<int> heap;
		priority_queue<int, vector<int>, greater<int> > std_heap;
		const int bnd = 100;
		for (int i = 0; i < 100000; ++i) {
			int x = rnd() % bnd;
			heap.insert(x);
			std_heap.push(x);
		}
		for (int i = 0; i < 100000; ++i) {
			Assert(heap.get_min() == std_heap.top(), "row_23");
			heap.extract_min();
			std_heap.pop();
		}
		cerr << "time used : ";
		cerr << (clock() - start) / 1000.0 << endl;
		// average result = 0.295
	}
	{
	    FibonacciHeap<int> heap;

	    heap.insert(4);
	    heap.insert(0);
	    heap.insert(1);
	    heap.insert(5);

	    Assert(heap.extract_min() == 0, "row_24");
	    Assert(heap.extract_min() == 1, "row_25");
	    Assert(heap.extract_min() == 4, "row_26");
	    Assert(heap.extract_min() == 5, "row_27");
	}
	{
	    FibonacciHeap<int> heap;
	    const int n = 100000;

        vector<int> mas;
        for (int i = 0; i < n; ++i)
            mas.push_back(0);
        for (int i = 0; i < n; ++i)
            mas.push_back(1);
        for (int i = 0; i < n; ++i)
            mas.push_back(2);

        shuffle(mas.begin(), mas.end(), rnd);

        for (int i : mas) {
            cout << i << ' ';
            heap.insert(i);
        }

	    for (int i = 0; i < n; ++i) {
	        assert(!heap.is_empty());
            Assert(heap.extract_min() == 0, "row_28");
	    }
	    for (int i = 0; i < n; ++i) {
	        assert(!heap.is_empty());
            Assert(heap.extract_min() == 1, "row_29");
	    }
	    for (int i = 0; i < n; ++i) {
	        assert(!heap.is_empty());
            Assert(heap.extract_min() == 2, "row_30");
	    }
	}
	{///Test_Heap_8
        FibonacciHeap<int> heap;

        auto it1 = heap.insert(1);
        auto it2 = heap.insert(2);

        heap.erase(it1);
        Assert(heap.get_min() == 2, "Test_Heap_8");
        heap.erase(it2);
        Assert(heap.is_empty(), "Test_Heap_8");
    }
    {///Test_Heap_9
        FibonacciHeap<int> heap;

        auto it1 = heap.insert(1);
        auto it2 = heap.insert(2);

        heap.erase(it2);
        Assert(heap.get_min() == 1, "Test_Heap_9");
        heap.erase(it1);
        Assert(heap.is_empty(), "Test_Heap_9");
    }
    {///Test_Heap_10
        FibonacciHeap<int> heap;

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
    /*{///Test_Heap_11
        FibonacciHeap<int> heap;

        auto it2 = heap.insert(2);
        auto it1 = heap.insert(1);
        auto it4 = heap.insert(4);
        auto it5 = heap.insert(5);

        heap.change(it1, 5);
        Assert(heap.get_min() == 2, "Test_Heap_11");

        heap.change(it4, 1);
        Assert(heap.get_min() == 1, "Test_Heap_11");
    }*/
    /*{///Test_Heap_12
        FibonacciHeap<int> heap;
        FibonacciHeap<int>::Pointer p[10];
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
    }*/
    {///Test_Heap_13
        FibonacciHeap<int> heap;
        vector<int> q;

        const int n = 1000;

        vector<pair<FibonacciHeap<int>::Pointer, int> > order;

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
    for (int i = 0; i < 1000; ++i) {///Tets_Heap_14
        FibonacciHeap<int> heap;
        vector<int> q;

        const int n = 50;

        vector<pair<FibonacciHeap<int>::Pointer, int> > order;

        for (int i = 0; i < n; ++i) {
            int x = rnd() % n;
            order.push_back(make_pair(heap.insert(x), x));
            q.push_back(x);
        }

        shuffle(order.begin(), order.end(), rnd);

        vector<int> foo;
        for (int i = 0; i < n; ++i) {
            sort(q.begin(), q.end());
            Assert(q[0] == heap.get_min(), "Tets_Heap_14");

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
