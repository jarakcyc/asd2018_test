#pragma once

#include <iostream>
#include <stdexcept>

#include <cassert>

using namespace std;

template<class Key>
class FibonacciHeap {
public:
	FibonacciHeap();
	bool is_empty() const;
	void insert(Key key);
	Key get_min() const;
	Key extract_min();
	void merge(FibonacciHeap &otherHeap);
private:
	class Node {
		friend FibonacciHeap<Key>;
	private:
	    Node();
		Node(Key _key);

		Node* parent;
		Node* right_brother;
		Node* first_son;
		Node* last_son;

		Key key;

		int degree;

        bool mark;

        void join(Node*& node);
	};

	Node* root;
	Node* last_root;
	Node* min_node;

	void setmin(Node*& node, Node* new_node);
	void join(Node*& left, Node*& right);

    void consolidate();
    void clear(Node* node);

	const int MAX_SIZE = 30;
};

template<class Key>
FibonacciHeap<Key>::FibonacciHeap() {
	root = nullptr;
	last_root = nullptr;
	min_node = nullptr;
}

template<class Key>
FibonacciHeap<Key>::Node::Node(Key _key) {
	key = _key;
	degree = 0;
	mark = false;

	parent = nullptr;
	right_brother = nullptr;
	first_son = nullptr;
	last_son = nullptr;
}

template<class Key>
FibonacciHeap<Key>::Node::Node() {
	key = 0;
	degree = 0;
	mark = false;

	parent = nullptr;
	right_brother = nullptr;
	first_son = nullptr;
	last_son = nullptr;
}

template<class Key>
void FibonacciHeap<Key>::join(Node*& left, Node*& right) {
    if (left->key > right->key) {
        swap(left, right);
    }

    if (left->first_son == nullptr) {
        left->first_son = right;
        left->last_son = right;

        right->parent = left;
    } else {
        left->last_son->right_brother = right;
        left->last_son = right;

        right->parent = left;
    }

    right = nullptr;

    left->degree++;
}

template<class Key>
void FibonacciHeap<Key>::setmin(Node*& node, Node* new_node) {
    if (node == nullptr) {
        node = new_node;
    }
    if (node->key > new_node->key) {
        node = new_node;
    }
}

template<class Key>
bool FibonacciHeap<Key>::is_empty() const {
	return (root == nullptr);
}

template<class Key>
void FibonacciHeap<Key>::clear(Node* node) {
    if (node == nullptr) {
        return;
    }
    clear(node->right_brother);
    delete node;
}

template<class Key>
void FibonacciHeap<Key>::merge(FibonacciHeap &otherHeap) {
    if (otherHeap.root == nullptr)
        return;

    if (root == nullptr) {
        root = otherHeap.root;
        last_root = otherHeap.last_root;
        min_node = otherHeap.min_node;
    } else {
        last_root->right_brother = otherHeap.root;
        last_root = otherHeap.last_root;

        if (min_node == nullptr ||
            otherHeap.root != nullptr && otherHeap.min_node->key < min_node->key) {
            min_node = otherHeap.min_node;
        }
    }

    otherHeap.root = nullptr;
    otherHeap.last_root = nullptr;
    otherHeap.min_node = nullptr;
}

template<class Key>
void FibonacciHeap<Key>::insert(Key key) {
	FibonacciHeap<Key> new_heap;

	new_heap.root = new Node(key);
	new_heap.min_node = new_heap.root;
	new_heap.last_root = new_heap.root;

	merge(new_heap);
}

template<class Key>
Key FibonacciHeap<Key>::get_min() const {
	if (is_empty()) {
		throw out_of_range("heap is empty");
	}
	return min_node->key;
}

template<class Key>
Key FibonacciHeap<Key>::extract_min() {
	if (is_empty()) {
		throw out_of_range("heap is empty");
	}
	Key res = get_min();

	FibonacciHeap<Key> children;

	children.root = min_node->first_son;

	while (children.root != nullptr) {
		children.root->parent = NULL;

		setmin(children.min_node, children.root);
        children.last_root = children.root;

		children.root = children.root->right_brother;
	}

	Node* vertex = root;
	if (min_node != vertex) {
		while (vertex->right_brother != min_node) {
			vertex = vertex->right_brother;
		}
		vertex->right_brother = min_node->right_brother;

		if (min_node == last_root) {
            last_root = vertex;
		}
	}
	else {
		root = vertex->right_brother;

		if (min_node == last_root) {
            last_root = vertex->right_brother;
		}
	}

	children.root = min_node->first_son;

	delete min_node;
	min_node = nullptr;

	merge(children);

	consolidate();

	return res;
}

template<class Key>
void FibonacciHeap<Key>::consolidate() {
    Node** array = new Node*[MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; ++i)
        array[i] = nullptr;

    Node* vertex = root;

    while (vertex != nullptr) {
        Node* next = vertex->right_brother;
        vertex->right_brother = nullptr;

        while (array[vertex->degree] != nullptr) {
            join(vertex, array[vertex->degree]);
        }

        array[vertex->degree] = vertex;

        vertex = next;
    }

    root = nullptr;
    min_node = nullptr;
    last_root = nullptr;

    for (int i = 0; i < MAX_SIZE; ++i) {
        if (array[i] != nullptr) {
            setmin(min_node, array[i]);

            if (root == nullptr) {
                root = array[i];
                last_root = array[i];
            } else {
                last_root->right_brother = array[i];
                last_root = array[i];
            }
        }
    }

    delete[] array;
}
