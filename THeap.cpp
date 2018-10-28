#include <iostream>

template<typename T>
class TVector {
public:
    TVector() :
        capasity(0),
        size(0)
    {}

    bool is_empty() const {
        return (size == 0);
    }

    void push_back(T element) {
        if (size == capasity) {
            Increase();
        }

        buffer[size] = element;
        size++;
    }

    void pop_back() {
        if (is_empty()) {
            throw std::out_of_range("no elements");
        }

        size--;

        if (size * 4 < capasity) {
            Decrease();
        }
    }

    T& operator [] (int index) const {
        return buffer[index];
    }

    ~TVector() {
        delete[] buffer;
    }
private:
    int capasity;
    int size;
    T* buffer;

    void Increase() {
        if (capasity == 0) {
            capasity = 3;
            buffer = new T[3];
            return;
        }

        capasity *= 2;
        T* new_buffer = new T[capasity];

        for (int i = 0; i < size; ++i) {
            new_buffer[i] = buffer[i];
        }

        delete[] buffer;

        buffer = new_buffer;
    }

    void Decrease() {
        capasity /= 2;
        T* new_buffer = new T[capasity];

        for (int i = 0; i < size; ++i) {
            new_buffer[i] = buffer[i];
        }

        delete[] buffer;

        buffer = new_buffer;
    }
};

class IPriorityQueue {
public:
    virtual void Insert(int x) = 0;
    virtual void EraseMin() = 0;
    virtual int GetMin() const = 0;
    virtual int GetSize() const = 0;
};

template<int K>
class THeap: public IPriorityQueue {
private:
    int nElements;
    TVector<int> a;

    void SiftUp(int x) {
        while (x > 0 && a[x] < a[(x - 1) / K]) {
            std::swap(a[x], a[(x - 1) / K]);
            x = (x - 1) / K;
        }
    }

    void SiftDown(int x) {
        while (1){
            int minIndex = x;
            for (int i = 0; i < K && K * x + i + 1 < nElements; ++i) {
                int curIndex = x * K + i + 1;
                if (a[curIndex] < a[minIndex])
                    minIndex = curIndex;
            }
            if (minIndex == x)
                break;
            else{
                std::swap(a[x], a[minIndex]);
                x = minIndex;
            }
        }
    }
public:
    THeap(){
        nElements = 0;
    }

    int GetMin() const {
        return a[0];
    }

    int GetSize() const {
        return nElements;
    }

    bool is_empty() const {
        return GetSize() == 0;
    }

    void Insert(int x) {
        a.push_back(x);
        SiftUp(nElements);
        nElements++;
    }

    void EraseMin() {
        if (is_empty()) {
            throw std::out_of_range("no elements");
        }

        std::swap(a[0], a[nElements - 1]);
        nElements--;
        a.pop_back();
        SiftDown(0);
    }
};

int main() {
    return 0;
}
