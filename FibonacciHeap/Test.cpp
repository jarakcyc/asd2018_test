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
}
