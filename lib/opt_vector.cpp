#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct opt_vector {
    vector<T> vec;

    opt_vector(vector<T> _vec) : vec(_vec) {}

    void push_back(T e) {
        vec.push_back(e);
    }

    void remove(T e) {
        vec.erase(find_iter(vec, e));
    }

    void remove_at(int idx) {
        assert(0 <= idx and idx < vec.size());
        swap(vec[idx], vec.back());
        vec.pop_back();
    }

    int find_idx(T &e) {
        auto it = find_iter(vec, e);
        if (it == vec.end()) return -1;
        return it - vec.begin();
    }

    T &operator[](int idx) {
        return &vec[idx];
    }

    size_t size() {
        return vec.size();
    }
};
