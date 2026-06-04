#include "HashTable.h"

HashTable::HashTable() : itemCount(0) {
    for (std::size_t i = 0; i < kBucketCount; ++i) {
        buckets[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (std::size_t i = 0; i < kBucketCount; ++i) {
        clearBucketList(buckets[i]);
        buckets[i] = nullptr;
    }
}

void HashTable::clearBucketList(Node* head) {
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

std::size_t HashTable::hashIndex(const std::string& product) const {
    unsigned long long hash = 14695981039346656037ULL;
    for (unsigned char ch : product) {
        hash ^= ch;
        hash *= 1099511628211ULL;
    }
    return static_cast<std::size_t>(hash % kBucketCount);
}

HashTable::Node* HashTable::findNode(const std::size_t index, const std::string& product) const {
    Node* current = buckets[index];
    while (current != nullptr) {
        if (current->data.product == product) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void HashTable::add(const std::string& product, const double price) {
    const std::size_t index = hashIndex(product);
    Node* existing = findNode(index, product);

    if (existing != nullptr) {
        existing->data.price = price;
        return;
    }

    Node* node = new Node(Entry{product, price});
    node->next = buckets[index];
    buckets[index] = node;
    ++itemCount;
}

bool HashTable::remove(const std::string& product) {
    const std::size_t index = hashIndex(product);
    Node* current = buckets[index];
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data.product == product) {
            if (previous == nullptr) {
                buckets[index] = current->next;
            } else {
                previous->next = current->next;
            }
            delete current;
            --itemCount;
            return true;
        }
        previous = current;
        current = current->next;
    }

    return false;
}

bool HashTable::find(const std::string& product, double& price) const {
    const std::size_t index = hashIndex(product);
    const Node* node = findNode(index, product);
    if (node == nullptr) {
        return false;
    }
    price = node->data.price;
    return true;
}

bool HashTable::isEmpty() const {
    return itemCount == 0;
}

std::size_t HashTable::size() const {
    return itemCount;
}