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
