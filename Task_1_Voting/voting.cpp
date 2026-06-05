#include "voting.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>


static std::vector<std::string> names;                     
static std::unordered_set<unsigned long long> votedHashes; 
static size_t duplicateCount = 0;                       

// Собственная хэш-функция
unsigned long long hashSurname(const std::string& surname) {
    unsigned long long h = 0;
    const unsigned long long base = 31;
    for (char c : surname) {
        h = h * base + static_cast<unsigned char>(c);
    }
    return h;
}

void enrolled(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filepath << std::endl;
        return;
    }

    std::string surname;
    while (std::getline(file, surname)) {
        size_t end = surname.find_last_not_of(" \t\r\n");
        if (end != std::string::npos) {
            surname = surname.substr(0, end + 1);
        } else {
            continue;  
        }
        if (surname.empty()) continue;

        // ВЫЗОВ ХЭШ ФУНКЦИИ 
        unsigned long long hash = hashSurname(surname);

        if (votedHashes.find(hash) != votedHashes.end()) {
            duplicateCount++; 
        } else {
            votedHashes.insert(hash);
            names.push_back(surname);
        }
    }
    file.close();
}

void unenrolled(const std::string& surname) {
    if (surname.empty()) return;

    unsigned long long hash = hashSurname(surname);

    if (votedHashes.find(hash) != votedHashes.end()) {
        duplicateCount++; 
    } else {
        votedHashes.insert(hash);
        names.push_back(surname);
    }
}

int voterCount() {
    return static_cast<int>(names.size());
}

int duplicates() {
    return static_cast<int>(duplicateCount);
}

const std::vector<std::string>& voterSurnames() {
    return names;
}