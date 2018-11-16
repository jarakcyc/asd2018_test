#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

template<class Key>
class TBinomialHeap {
public:
    TBinomialHeap();
    bool is_empty() const;
    void insert(Key key);
    Key get_min();
    Key extract_min();
    void merge(TBinomialHeap &otherHeap);
private:
    class Node {
    friend TBinomialHeap<Key>;
    private:
        Node(Key _key);

        Node* parent;
        Node* right_brother;
        Node* first_son;
        Node* last_son;

        Key key;

        int degree;
    };

    Node* root;
    Node* min_node;

    void setmin(Node*& node, Node* new_node);
    void set_next_node(Node*& head, Node*& current, Node*& next);
    void clear(Node* node);
};

template<class Key>
TBinomialHeap<Key>::TBinomialHeap() {
    root = nullptr;
    min_node = nullptr;
}

template<class Key>
TBinomialHeap<Key>::Node::Node(Key _key) {
    key = _key;
    degree = 0;
    parent = nullptr;
    right_brother = nullptr;
    first_son = nullptr;
    last_son = nullptr;
}

template<class Key>
void TBinomialHeap<Key>::setmin(Node*& node, Node* new_node) {
    if (node == nullptr) {
        node = new_node;
    }
    assert(new_node != nullptr);
    if (node->key > new_node->key) {
        node = new_node;
    }
}

template<class Key>
void TBinomialHeap<Key>::set_next_node(Node*& head, Node*& current, Node*& next) {
    if (current == nullptr) {
        current = next;
        head = current;
        next = next->right_brother;
    } else {
        current->right_brother = next;
        current = current->right_brother;
        next = next->right_brother;
    }
}

template<class Key>
bool TBinomialHeap<Key>::is_empty() const {
    return (min_node == nullptr);
}

template<class Key>
void TBinomialHeap<Key>::clear(Node* node) {
    if (node == nullptr) {
        return;
    }
    clear(node->right_brother);
    delete node;
}

template<class Key>
void TBinomialHeap<Key>::merge(TBinomialHeap<Key> &otherHeap) {
    Node* head = nullptr;
    Node* new_root = nullptr;
    min_node = nullptr;

    Node* child_1 = root;
    Node* child_2 = otherHeap.root;

    while (child_1 != nullptr && child_2 != nullptr) {
        bool first = false;

        if (child_1->degree < child_2->degree) {
            first = true;
        } else if (child_1->degree > child_2->degree) {
            first = false;
        } else if (child_1->key < child_2->key) {
            assert(child_1->degree == child_2->degree);
            first = true;
        } else {
            assert(child_1->degree == child_2->degree);
            first = false;
        }

        if (first) {
            setmin(min_node, child_1);
            set_next_node(head, new_root, child_1);
        } else {
            setmin(min_node, child_2);
            set_next_node(head, new_root, child_2);
        }
    }

    while (child_1 != nullptr) {
        setmin(min_node, child_1);
        set_next_node(head, new_root, child_1);
    }

    while (child_2 != nullptr) {
        setmin(min_node, child_2);
        set_next_node(head, new_root, child_2);
    }

    new_root = head;

    Node* previous = nullptr;

    while (head != nullptr && head->right_brother != nullptr) {
        bool need_swap = false;
        if (head->degree > head->right_brother->degree) {
            need_swap = true;
        } else if (head->degree == head->right_brother->degree) {
            if (head->key > head->right_brother->key) {
                need_swap = true;
            }
        }

        if (need_swap == true) {
            if (previous == nullptr) {
                Node* tmp = head->right_brother->right_brother;
                Node* new_head = head->right_brother;

                head->right_brother->right_brother = head;
                head->right_brother = tmp;
                head = new_head;

                new_root = new_head;
            } else {
                previous->right_brother = head->right_brother;

                Node* tmp = head->right_brother->right_brother;
                Node* new_head = head->right_brother;

                head->right_brother->right_brother = head;
                head->right_brother = tmp;
                head = new_head;
            }
        }

        if (head->degree == head->right_brother->degree) {
            Node* tmp = head->right_brother;

            tmp->parent = head;

            head->right_brother = tmp->right_brother;

            tmp->right_brother = nullptr;
            if (head->first_son == nullptr) {
                head->first_son = tmp;
                head->last_son = tmp;
            } else {
                assert(head->last_son->degree < tmp->degree);
                head->last_son->right_brother = tmp;
                head->last_son = tmp;
            }

            head->degree++;
        } else {
            previous = head;
            head = head->right_brother;
        }
    }

    root = new_root;
}

template<class Key>
void TBinomialHeap<Key>::insert(Key key) {
    TBinomialHeap<Key> new_heap;
    new_heap.root = new Node(key);
    merge(new_heap);
}

template<class Key>
Key TBinomialHeap<Key>::get_min() {
    if (is_empty()) {
        throw out_of_range("heap is empty");
    }
    return min_node->key;
}

template<class Key>
Key TBinomialHeap<Key>::extract_min() {
    if (is_empty()) {
        throw out_of_range("heap is empty");
    }
    Key res = get_min();

    TBinomialHeap<Key> children;

    children.root = min_node->first_son;

    while (children.root != nullptr) {
        children.root->parent = NULL;
        children.root = children.root->right_brother;
    }

    Node* vertex = root;
    if (min_node != vertex) {
        while (vertex->right_brother != min_node) {
            vertex = vertex->right_brother;
        }
        vertex->right_brother = min_node->right_brother;
    } else {
        root = vertex->right_brother;
    }

    children.root = min_node->first_son;

    delete min_node;

    merge(children);

    return res;
}
