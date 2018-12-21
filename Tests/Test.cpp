#include "UnitTestFramework.h"
#include "Test.h"

#include "TVector.h"
#include "THeap.h"
#include "TBinomialHeap.h"
#include "FibonacciHeap.h"

#include "StupidHeap.h"
#include "Generator.h"

void TestAll() {
    TestRunner tr;

    tr.RunTest(TestVector, "Tests for Vector");
    cerr << endl;

    tr.RunTest(TestHeap, "Tests for Heap");
    cerr << endl;

    tr.RunTest(TestBinomialHeap, "Tests for BinomialHeap");
    cerr << endl;

    tr.RunTest(TestFibonacciHeap, "Tests for FibonacciHeap");
    cerr << endl;

    tr.RunTest(TestMerge, "Tests for merge");
    cerr << endl;
}

void TestVector() {
    {
        TVector<int> a;
        bool ex = 0;

        for (int i = 0; i < 10; ++i) {
            a.push_back(i);
        }

        for (int i = 9; i >= 0; --i) {
            Assert(a.back() == i, "TVector back()");
            a.pop_back();
        }

        Assert(a.is_empty(), "TVector is_empty");

        ex = 0;
        try {
            a.pop_back();
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for TVector pop_back()");

        ex = 0;
        try {
            int x = a.back();
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for TVector back()");
    }
}

void TestHeap() {
    /// Test exceptions
    {
        THeap<int> heap;
        bool ex = 0;

        for (int i = 0; i < 10; ++i) {
            heap.insert(i);
        }
        for (int i = 50; i < 60; ++i) {
            heap.insert(i);
        }

        auto it = heap.insert(15);

        for (int i = 0; i < 5; ++i) {
            heap.extract_min();
        }

        heap.erase(it);

        int cnt = 0;
        while (!heap.is_empty()) {
            cnt++;
            heap.extract_min();
        }

        Assert(cnt == 10 + 10 + 1 - 5 - 1, "THeap works incorrect :(");

        ex = 0;
        try {
            heap.extract_min();
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for THeap extract_min()");

        ex = 0;
        try {
            heap.erase(it);
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for THeap erase(it)");

        ex = 0;
        try {
            heap.change(it, 18);
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for THeap change(it)");

        ex = 0;
        try {
            int mn = heap.get_min();
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for THeap get_min");
    }
    ///Random sequence of operations
    {
        vector<Query> sequence = GRS(0, 10000, 100000, 0);

        StupidHeap stupid;
        vector<int> stupid_ptrs;

        THeap<int> heap;
        vector<THeap<int>::Pointer> ptrs;

        for (Query query : sequence) {
            if (query.type == Type::INSERT) {
                stupid_ptrs.push_back(stupid.insert(query.key));
                ptrs.push_back(heap.insert(query.key));
            } else if (query.type == Type::EXTRACT_MIN) {
                Assert(stupid.extract_min().first == heap.extract_min(), "THeap extract_min");
            } else if (query.type == Type::ERASE) {
                int id = query.ptr_index;
                Assert(stupid.erase(stupid_ptrs[id]) == heap.erase(ptrs[id]),
                       "THeap erase");
            } else if (query.type == Type::CHANGE) {
                int id = query.ptr_index;
                int x = query.key;
                Assert(stupid.change(stupid_ptrs[id], x) == heap.change(ptrs[id], x),
                       "THeap change");
            }
        }
    }
    {
        vector<Query> sequence = GRS(0, 1000, 100000, 500);

        StupidHeap stupid;
        vector<int> stupid_ptrs;

        THeap<int> heap;
        vector<THeap<int>::Pointer> ptrs;

        for (Query query : sequence) {
            if (query.type == Type::INSERT) {
                stupid_ptrs.push_back(stupid.insert(query.key));
                ptrs.push_back(heap.insert(query.key));
            } else if (query.type == Type::EXTRACT_MIN) {
                Assert(stupid.extract_min().first == heap.extract_min(), "THeap extract_min");
            } else if (query.type == Type::ERASE) {
                int id = query.ptr_index;
                Assert(stupid.erase(stupid_ptrs[id]) == heap.erase(ptrs[id]),
                       "THeap erase");
            } else if (query.type == Type::CHANGE) {
                int id = query.ptr_index;
                int x = query.key;
                Assert(stupid.change(stupid_ptrs[id], x) == heap.change(ptrs[id], x),
                       "THeap change");
            }
        }
    }
    {
        mt19937 rnd(time(NULL));
        for (int i = 0; i < 100; ++i) {
            int n = rnd() % 300;
            int start_inserts = rnd() % 300;
            vector<Query> sequence = GRS(0, n, 100000, start_inserts);

            StupidHeap stupid;
            vector<int> stupid_ptrs;

            THeap<int> heap;
            vector<THeap<int>::Pointer> ptrs;

            for (Query query : sequence) {
                if (query.type == Type::INSERT) {
                    stupid_ptrs.push_back(stupid.insert(query.key));
                    ptrs.push_back(heap.insert(query.key));
                } else if (query.type == Type::EXTRACT_MIN) {
                    Assert(stupid.extract_min().first == heap.extract_min(), "THeap extract_min");
                } else if (query.type == Type::ERASE) {
                    int id = query.ptr_index;
                    Assert(stupid.erase(stupid_ptrs[id]) == heap.erase(ptrs[id]),
                           "THeap erase");
                } else if (query.type == Type::CHANGE) {
                    int id = query.ptr_index;
                    int x = query.key;
                    Assert(stupid.change(stupid_ptrs[id], x) == heap.change(ptrs[id], x),
                           "THeap change");
                }
            }
        }
    }
}

void TestBinomialHeap() {
    /// Test exceptions
    {
        TBinomialHeap<int> heap;
        bool ex = 0;

        for (int i = 0; i < 10; ++i) {
            heap.insert(i);
        }
        for (int i = 50; i < 60; ++i) {
            heap.insert(i);
        }

        auto it = heap.insert(15);

        for (int i = 0; i < 5; ++i) {
            heap.extract_min();
        }

        heap.erase(it);

        int cnt = 0;
        while (!heap.is_empty()) {
            cnt++;
            heap.extract_min();
        }

        Assert(cnt == 10 + 10 + 1 - 5 - 1, "TBinomialHeap works incorrect :(");

        ex = 0;
        try {
            heap.extract_min();
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for TBinomialHeap extract_min()");

        ex = 0;
        try {
            heap.erase(it);
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for TBinomialHeap erase(it)");

        ex = 0;
        try {
            heap.change(it, 18);
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for TBinomialHeap change(it)");

        ex = 0;
        try {
            int mn = heap.get_min();
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for TBinomialHeap get_min");
    }
    ///Random sequence of operations
    {
        vector<Query> sequence = GRS(1, 10000, 100000, 0);

        StupidHeap stupid;
        vector<int> stupid_ptrs;

        TBinomialHeap<int> heap;
        vector<TBinomialHeap<int>::Pointer> ptrs;

        for (Query query : sequence) {
            if (query.type == Type::INSERT) {
                stupid_ptrs.push_back(stupid.insert(query.key));
                ptrs.push_back(heap.insert(query.key));
            } else if (query.type == Type::EXTRACT_MIN) {
                Assert(stupid.extract_min().first == heap.extract_min(), "TBinomialHeap extract_min");
            } else if (query.type == Type::ERASE) {
                int id = query.ptr_index;
                Assert(stupid.erase(stupid_ptrs[id]) == heap.erase(ptrs[id]),
                       "TBinomialHeap erase");
            } else if (query.type == Type::CHANGE) {
                int id = query.ptr_index;
                int x = query.key;
                Assert(stupid.change(stupid_ptrs[id], x) == heap.change(ptrs[id], x),
                       "TBinomialHeap change");
            }
        }
    }
    {
        vector<Query> sequence = GRS(1, 1000, 100000, 500);

        StupidHeap stupid;
        vector<int> stupid_ptrs;

        TBinomialHeap<int> heap;
        vector<TBinomialHeap<int>::Pointer> ptrs;

        for (Query query : sequence) {
            if (query.type == Type::INSERT) {
                stupid_ptrs.push_back(stupid.insert(query.key));
                ptrs.push_back(heap.insert(query.key));
            } else if (query.type == Type::EXTRACT_MIN) {
                Assert(stupid.extract_min().first == heap.extract_min(), "TBinomialHeap extract_min");
            } else if (query.type == Type::ERASE) {
                int id = query.ptr_index;
                Assert(stupid.erase(stupid_ptrs[id]) == heap.erase(ptrs[id]),
                       "TBinomialHeap erase");
            } else if (query.type == Type::CHANGE) {
                int id = query.ptr_index;
                int x = query.key;
                Assert(stupid.change(stupid_ptrs[id], x) == heap.change(ptrs[id], x),
                       "TBinomialHeap change");
            }
        }
    }
    {
        mt19937 rnd(time(NULL));
        for (int i = 0; i < 100; ++i) {
            int n = rnd() % 300;
            int start_inserts = rnd() % 300;
            vector<Query> sequence = GRS(1, n, 100000, start_inserts);

            StupidHeap stupid;
            vector<int> stupid_ptrs;

            TBinomialHeap<int> heap;
            vector<TBinomialHeap<int>::Pointer> ptrs;

            for (Query query : sequence) {
                if (query.type == Type::INSERT) {
                    stupid_ptrs.push_back(stupid.insert(query.key));
                    ptrs.push_back(heap.insert(query.key));
                } else if (query.type == Type::EXTRACT_MIN) {
                    Assert(stupid.extract_min().first == heap.extract_min(), "TBinomialHeap extract_min");
                } else if (query.type == Type::ERASE) {
                    int id = query.ptr_index;
                    Assert(stupid.erase(stupid_ptrs[id]) == heap.erase(ptrs[id]),
                           "TBinomialHeap erase");
                } else if (query.type == Type::CHANGE) {
                    int id = query.ptr_index;
                    int x = query.key;
                    Assert(stupid.change(stupid_ptrs[id], x) == heap.change(ptrs[id], x),
                           "TBinomialHeap change");
                }
            }
        }
    }
}

void TestFibonacciHeap() {
    /// Test exceptions
    {
        FibonacciHeap<int> heap;
        bool ex = 0;

        for (int i = 0; i < 10; ++i) {
            heap.insert(i);
        }
        for (int i = 50; i < 60; ++i) {
            heap.insert(i);
        }

        auto it = heap.insert(25);

        for (int i = 0; i < 5; ++i) {
            heap.extract_min();
        }

        ex = 0;
        try {
            heap.decrease(it, 30);
        } catch (std::invalid_argument) {
            ex = 1;
        }
        Assert(ex, "exceptions for FibonacciHeap get_min");

        heap.erase(it);

        int cnt = 0;
        while (!heap.is_empty()) {
            cnt++;
            heap.extract_min();
        }

        Assert(cnt == 10 + 10 + 1 - 5 - 1, "FibonacciHeap works incorrect :(");

        ex = 0;
        try {
            heap.extract_min();
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for FibonacciHeap extract_min()");

        ex = 0;
        try {
            heap.erase(it);
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for FibonacciHeap erase(it)");

        ex = 0;
        try {
            heap.decrease(it, 18);
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for FibonacciHeap change(it)");

        ex = 0;
        try {
            int mn = heap.get_min();
        } catch (std::out_of_range) {
            ex = 1;
        }
        Assert(ex, "exceptions for FibonacciHeap get_min");
    }
    ///Random sequence of operations
    {
        vector<Query> sequence = GRS(2, 10000, 200000, 0);
        /*cerr << "sequence:" << endl;
        for (Query q : sequence) {
            if (q.type == Type::INSERT) {
                cerr << "INSERT " << q.key << endl;
            } else if (q.type == Type::EXTRACT_MIN) {
                cerr << "EXTRACT_MIN" << endl;
            } else if (q.type == Type::ERASE) {
                cerr << "ERASE " << q.ptr_index << endl;
            } else if (q.type == Type::CHANGE) {
                cerr << "DECREASE " << q.ptr_index << ' ' << q.key << endl;
            }
        }
        cerr << endl;*/

        StupidHeap stupid;
        vector<int> stupid_ptrs;

        FibonacciHeap<int> heap;
        vector<FibonacciHeap<int>::Pointer> ptrs;

        for (Query query : sequence) {
            if (query.type == Type::INSERT) {
                stupid_ptrs.push_back(stupid.insert(query.key));
                ptrs.push_back(heap.insert(query.key));
            } else if (query.type == Type::EXTRACT_MIN) {
                Assert(stupid.extract_min().first == heap.extract_min(), "FibonacciHeap extract_min");
            } else if (query.type == Type::ERASE) {
                int id = query.ptr_index;
                Assert(stupid.erase(stupid_ptrs[id]) == heap.erase(ptrs[id]),
                       "FibonacciHeap erase");
            } else if (query.type == Type::CHANGE) {
                int id = query.ptr_index;
                int x = query.key;
                Assert(stupid.change(stupid_ptrs[id], x) == heap.decrease(ptrs[id], x),
                       "FibonacciHeap decrease");
            }
        }
    }
    {
        vector<Query> sequence = GRS(2, 1000, 100000, 500);

        StupidHeap stupid;
        vector<int> stupid_ptrs;

        FibonacciHeap<int> heap;
        vector<FibonacciHeap<int>::Pointer> ptrs;

        for (Query query : sequence) {
            if (query.type == Type::INSERT) {
                stupid_ptrs.push_back(stupid.insert(query.key));
                ptrs.push_back(heap.insert(query.key));
            } else if (query.type == Type::EXTRACT_MIN) {
                Assert(stupid.extract_min().first == heap.extract_min(), "FibonacciHeap extract_min");
            } else if (query.type == Type::ERASE) {
                int id = query.ptr_index;
                Assert(stupid.erase(stupid_ptrs[id]) == heap.erase(ptrs[id]),
                       "FibonacciHeap erase");
            } else if (query.type == Type::CHANGE) {
                int id = query.ptr_index;
                int x = query.key;
                Assert(stupid.change(stupid_ptrs[id], x) == heap.decrease(ptrs[id], x),
                       "FibonacciHeap decrease");
            }
        }
    }
    {
        mt19937 rnd(time(NULL));
        for (int i = 0; i < 100; ++i) {
            int n = rnd() % 300;
            int start_inserts = rnd() % 300;
            vector<Query> sequence = GRS(2, n, 100000, start_inserts);

            StupidHeap stupid;
            vector<int> stupid_ptrs;

            FibonacciHeap<int> heap;
            vector<FibonacciHeap<int>::Pointer> ptrs;

            for (Query query : sequence) {
                if (query.type == Type::INSERT) {
                    stupid_ptrs.push_back(stupid.insert(query.key));
                    ptrs.push_back(heap.insert(query.key));
                } else if (query.type == Type::EXTRACT_MIN) {
                    Assert(stupid.extract_min().first == heap.extract_min(), "FibonacciHeap extract_min");
                } else if (query.type == Type::ERASE) {
                    int id = query.ptr_index;
                    Assert(stupid.erase(stupid_ptrs[id]) == heap.erase(ptrs[id]),
                           "FibonacciHeap erase");
                } else if (query.type == Type::CHANGE) {
                    int id = query.ptr_index;
                    int x = query.key;
                    Assert(stupid.change(stupid_ptrs[id], x) == heap.decrease(ptrs[id], x),
                           "FibonacciHeap decrease");
                }
            }
        }
    }
}

void TestMerge() {
    /// Test TBinomialHeap
    {
        TBinomialHeap<int> heap;
        vector<int> test;

        heap.insert(1);
        test = heap.get_roots();
        Assert(test.size() == 1 && test[0] == 0, "TBinomialHeap merge 1");

        heap.insert(2);
        test = heap.get_roots();
        Assert(test.size() == 1 && test[0] == 1, "TBinomialHeap merge 2");

        heap.insert(0);
        for (int i = 3; i < 10; ++i) {
            heap.insert(i);
        }

        test = heap.get_roots();
        Assert(test.size() == 2 && test[0] == 1 && test[1] == 3, "TBinomialHeap merge 3");
    }
    {
        TBinomialHeap<int> heap_1, heap_2;

        for (int i = 0; i < 5; ++i) {
            heap_1.insert(i);
        }
        for (int i = 5; i < 10; ++i) {
            heap_2.insert(i);
        }

        heap_1.merge(heap_2);

        vector<int> test = heap_1.get_roots();
        Assert(test.size() == 2 && test[0] == 1 && test[1] == 3, "TBinomialHeap merge 4");
    }
    {
        const int n = 1e5;

        auto sets = GenTwoSets(n, 1e9);

        TBinomialHeap<int> heap_1, heap_2;

        for (int i = 0; i < n; ++i) {
            heap_1.insert(sets.first[i]);
        }
        for (int i = 0; i < n; ++i) {
            heap_2.insert(sets.second[i]);
        }

        int start = clock();
        heap_1.merge(heap_2);
        cerr << "Test TBinomialHeap merge. Time used: " << (double)(clock() - start) / 1000.0 << endl;
        // average res = 0
    }
    /// Test FibonacciHeap
    {
        FibonacciHeap<int> heap;
        vector<int> test;

        heap.insert(1);
        test = heap.get_roots();
        Assert(test.size() == 1 && test[0] == 0, "FibonacciHeap merge 1");

        heap.insert(2);
        test = heap.get_roots();
        Assert(test.size() == 2 && test[0] == 0 && test[1] == 0, "FibonacciHeap merge 2");

        heap.insert(0);
        for (int i = 3; i < 10; ++i) {
            heap.insert(i);
        }

        test = heap.get_roots();
        Assert(test.size() == 10, "FibonacciHeap merge 3");

        heap.extract_min();

        test = heap.get_roots();
        Assert(test.size() == 2, "FibonacciHeap merge 4");
    }
    {
        const int n = 1e5;

        auto sets = GenTwoSets(n, 1e9);

        FibonacciHeap<int> heap_1, heap_2;

        for (int i = 0; i < n; ++i) {
            heap_1.insert(sets.first[i]);
        }
        for (int i = 0; i < n; ++i) {
            heap_2.insert(sets.second[i]);
        }

        int start = clock();
        heap_1.merge(heap_2);
        cerr << "Test FibonacciHeap merge. Time used: " << (double)(clock() - start) / 1000.0 << endl;
        // average res = 0
    }
    /// Multiple tests
    {
        const int n = 1e5;

        auto sets = GenTwoSets(n, 1e9);

        TBinomialHeap<int> Bheap_1, Bheap_2;

        for (int i = 0; i < n; ++i) {
            Bheap_1.insert(sets.first[i]);
        }
        for (int i = 0; i < n; ++i) {
            Bheap_2.insert(sets.second[i]);
        }
        Bheap_1.merge(Bheap_2);

        FibonacciHeap<int> Fheap_1, Fheap_2;

        for (int i = 0; i < n; ++i) {
            Fheap_1.insert(sets.first[i]);
        }
        for (int i = 0; i < n; ++i) {
            Fheap_2.insert(sets.second[i]);
        }
        Fheap_1.merge(Fheap_2);

        mt19937 rnd(time(NULL));
        for (int i = 0; i < n; ++i) {
            int type = rnd() % 2;
            if (type == 0) { // insert
                int x = rnd() % (int)(1e9);
                Bheap_1.insert(x);
                Fheap_1.insert(x);
            } else if (type == 1) { // extract_min
                if (!Bheap_1.is_empty() && !Fheap_1.is_empty()) {
                    Assert(Bheap_1.extract_min() == Fheap_1.extract_min(), "multiple test_1 extract_min()");
                } else {
                    Assert(Bheap_1.is_empty() && Fheap_1.is_empty(), "multiple test_1 is_empty");
                }
            }
            Assert(Bheap_1.get_min() == Fheap_1.get_min(), "multiple test_1 get_min()");
        }
    }
    {
        for (int i = 0; i < 500; ++i) {
            const int n = 1000;

            auto sets = GenTwoSets(n, 1e9);

            TBinomialHeap<int> Bheap_1, Bheap_2;

            for (int i = 0; i < n; ++i) {
                Bheap_1.insert(sets.first[i]);
            }
            for (int i = 0; i < n; ++i) {
                Bheap_2.insert(sets.second[i]);
            }
            Bheap_1.merge(Bheap_2);

            FibonacciHeap<int> Fheap_1, Fheap_2;

            for (int i = 0; i < n; ++i) {
                Fheap_1.insert(sets.first[i]);
            }
            for (int i = 0; i < n; ++i) {
                Fheap_2.insert(sets.second[i]);
            }
            Fheap_1.merge(Fheap_2);

            mt19937 rnd(time(NULL));
            for (int i = 0; i < n; ++i) {
                int type = rnd() % 2;
                if (type == 0) { // insert
                    int x = rnd() % (int)(1e9);
                    Bheap_1.insert(x);
                    Fheap_1.insert(x);
                } else if (type == 1) { // extract_min
                    if (!Bheap_1.is_empty() && !Fheap_1.is_empty()) {
                        Assert(Bheap_1.extract_min() == Fheap_1.extract_min(), "multiple test_2 extract_min()");
                    } else {
                        Assert(Bheap_1.is_empty() && Fheap_1.is_empty(), "multiple test_2 is_empty");
                    }
                }
                Assert(Bheap_1.get_min() == Fheap_1.get_min(), "multiple test_2 get_min()");
            }
        }
    }
}
