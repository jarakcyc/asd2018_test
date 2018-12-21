#pragma once

struct StupidHeap {
    const int INF = 1e9;
    int id = 0;
    deque<pair<int, int> > mas;

    StupidHeap() :
        id(0),
        mas(0)
    {}

    bool is_empty() const {
        return mas.empty();
    }

    int insert(int x) {
        mas.push_back({x, id});
        id++;
        return id - 1;
    }

    pair<int, int> extract_min() {
        pair<int, int> mn = {INF, INF};
        for (int i = 0; i < mas.size(); ++i) {
            assert(mas[i].first != mn.first);
            mn = min(mn, mas[i]);
        }

        vector<pair<int, int> > st;
        while (mas.back() != mn) {
            st.push_back(mas.back());
            mas.pop_back();
        }

        mas.pop_back();

        while (!st.empty()) {
            mas.push_back(st.back());
            st.pop_back();
        }

        return mn;
    }

    int get_min() const {
        pair<int, int> mn = {INF, INF};
        for (int i = 0; i < mas.size(); ++i) {
            mn = min(mn, mas[i]);
        }
        return mn.first;
    }

    int get_size() const {
        return (int)mas.size();
    }

    int erase(int x) {
        vector<pair<int, int> > st;
        while (mas.back().second != x) {
            st.push_back(mas.back());
            mas.pop_back();
            assert(!mas.empty());
        }

        int erased = mas.back().first;
        mas.pop_back();

        while (!st.empty()) {
            mas.push_back(st.back());
            st.pop_back();
        }

        return erased;
    }

    int change(int x, int new_val) {
        int changed;
        for (int i = 0; i < mas.size(); ++i) {
            if (mas[i].second == x) {
                changed = mas[i].first;
                mas[i].first = new_val;
                break;
            }
        }
        return changed;
    }

    int get(int x) {
        for (int i = 0; i < mas.size(); ++i) {
            if (mas[i].second == x) {
                return mas[i].first;
            }
        }
    }
};
