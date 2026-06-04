#pragma once

#include <string>

class HashTable {
public:
    HashTable();
    ~HashTable();

    void add(const std::string& product, double price);
    bool remove(const std::string& product);
    bool find(const std::string& product, double& price) const;

    bool isEmpty() const;
    std::size_t size() const;

private:
    static constexpr std::size_t kBucketCount = 10;

    struct Entry {
        std::string product;
        double price;
    };

    struct Node {
        Entry data;
        Node* next;

        Node(Entry entry) : data(std::move(entry)), next(nullptr) {}
    };

    Node* buckets[kBucketCount];
    std::size_t itemCount;

    std::size_t hashIndex(const std::string& product) const;
    Node* findNode(std::size_t index, const std::string& product) const;
    void clearBucketList(Node* head);
};