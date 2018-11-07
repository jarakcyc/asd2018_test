#pragma once

#include "IVector.h"

#include <stdexcept>

template<class T>
TVector<T>::TVector() :
    capasity(0),
    size(0)
{}

template<class T>
TVector<T>::~TVector() {
    delete[] buffer;
}

template<class T>
bool TVector<T>::is_empty() const {
    return (size == 0);
}

template<class T>
void TVector<T>::push_back(T element) {
    if (size == capasity) {
        Increase();
    }

    buffer[size] = element;
    size++;
}

template<class T>
void TVector<T>::pop_back() {
    if (is_empty()) {
        throw std::out_of_range("no elements");
    }

    size--;

    if (size * 4 < capasity) {
        Decrease();
    }
}

template<class T>
T& TVector<T>::operator [] (int index) const {
    return buffer[index];
}

template<class T>
void TVector<T>::Increase() {
    if (capasity == 0) {
        capasity = 1;
        buffer = new T[1];
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

template<class T>
void TVector<T>::Decrease() {
    capasity /= 2;
    T* new_buffer = new T[capasity];

    for (int i = 0; i < size; ++i) {
        new_buffer[i] = buffer[i];
    }

    delete[] buffer;

    buffer = new_buffer;
}
