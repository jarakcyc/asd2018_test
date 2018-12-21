#pragma once

enum Type {
    INSERT, // insert
    EXTRACT_MIN, // extrace_min
    GET_MIN, // get_min
    GET_SIZE, // get_size
    ERASE, // erase
    CHANGE, // change/decrease
    IS_EMPTY // is_empty
};

struct Query {
    Type type;
    int key, ptr_index;
};

/// Generate Random Sequence - GRS

vector<Query> GRS(int heap_id, int n, int range, int start_inserts) {
    /*
    heap_id = 0 if THeap
    heap_id = 1 if TBinomialHeap
    heap_id = 2 if FibonacciHeap
    */

    mt19937 rnd(time(NULL));
    vector<Query> result;

    StupidHeap heap;
    vector<int> ptrs; // pointers

    /*
    we will add operation to the end of the sequence if
    we can do it correctly with stupid heap
    */

    set<int> was; // values which was already used

    set<int> ptr_ids; // unused ptr_indexes

    int all[4] = {};

    for (int i = 0; i < start_inserts; ++i) {
        int x = rnd() % range;
        while (was.count(x)) {
            x = rnd() % range;
        }

        was.insert(x);
        int it = heap.insert(x);
        ptrs.push_back(it);
        ptr_ids.insert((int)ptrs.size() - 1);

        Query q;
        q.type = Type::INSERT;
        q.key = x;
        result.push_back(q);

        all[0]++;
    }

    int cnt = 0;
    while (cnt < n) {
        int id = rnd() % 4;
        bool success = 0;
        if (id == 0) { // insert
            int x = rnd() % range;
            while (was.count(x)) {
                x = rnd() % range;
            }

            was.insert(x);
            int it = heap.insert(x);
            ptrs.push_back(it);
            ptr_ids.insert((int)ptrs.size() - 1);

            Query q;
            q.type = Type::INSERT;
            q.key = x;
            result.push_back(q);

            success = 1;
        } else if (id == 1) { // extract_min
            if (!heap.is_empty()) {
                pair<int, int> mn = heap.extract_min();

                for (int i = 0; i < ptrs.size(); ++i) {
                    if (ptrs[i] == mn.second) {
                        ptr_ids.erase(i);
                        break;
                    }
                }

                Query q;
                q.type = Type::EXTRACT_MIN;
                result.push_back(q);

                success = 1;
            }
        } else if (id == 2) { // erase
            if (!heap.is_empty()) {
                int sz = ptr_ids.size();
                int num = rnd() % sz;

                int ptr_index;
                for (auto it = ptr_ids.begin(); num >= 0; it++, num--) {
                    ptr_index = *it;
                }

                heap.erase(ptrs[ptr_index]);
                ptr_ids.erase(ptr_index);

                Query q;
                q.type = Type::ERASE;
                q.ptr_index = ptr_index;
                result.push_back(q);

                success = 1;
            }
        } else if (id == 3) { // change/decrease
            if (!heap.is_empty()) {
                int sz = ptr_ids.size();
                int num = rnd() % sz;

                int ptr_index;
                for (auto it = ptr_ids.begin(); num >= 0; it++, num--) {
                    ptr_index = *it;
                }

                int x = 0;
                if (heap_id == 2) { // decrease
                    int current_value = heap.get(ptrs[ptr_index]);
                    if (current_value > 0) {
                        x = rnd() % current_value;
                    }
                } else { // change
                    x = rnd() % range;
                }

                if (!was.count(x)) {
                    was.insert(x);
                    heap.change(ptrs[ptr_index], x);

                    Query q;
                    q.type = Type::CHANGE;
                    q.ptr_index = ptr_index;
                    q.key = x;
                    result.push_back(q);

                    success = 1;
                }
            }
        }

        cnt += success;

        if (success)
            all[id]++;
    }

    /*cerr << "generated : " << endl;
    for (int i = 0; i < 4; ++i) {
        cerr << i << ' ' << all[i] << endl;
    }*/
    return result;
}

pair<vector<int>, vector<int> > GenTwoSets(int n, int range) {
    vector<int> a, b;
    set<int> was;
    mt19937 rnd(time(NULL));
    for (int i = 0; i < n; ++i) {
        int x = rnd() % range;
        while (was.count(x)) {
            was.insert(x);
            x = rnd() % range;
        }
        a.push_back(x);
    }
    for (int i = 0; i < n; ++i) {
        int x = rnd() % range;
        while (was.count(x)) {
            was.insert(x);
            x = rnd() % range;
        }
        b.push_back(x);
    }
    return {a, b};
}
