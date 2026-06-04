#include "voting.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace {
    void setupConsoleUtf8() {
        #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
        #endif
        std::ios::sync_with_stdio(false);
    }
}

int main() {
    setupConsoleUtf8();

    std::cout << "Загрузка файла с одногруппниками...\n";
    enrolled(CLASSMATES_FILE);

    std::cout << "Введите фамилии (для завершения введите 'end'):\n";
    std::string surname;
    while (std::getline(std::cin, surname)) {
        if (surname == "end") {
            break;
        }
        unenrolled(surname);
    }

    std::cout << "\n--- Итоги голосования ---\n";
    std::cout << "Голосующих: " << voterCount() << '\n';
    std::cout << "Дубликатов: " << duplicates() << '\n';
    std::cout << "Фамилии голосующих:\n";
    for (const std::string& name : voterSurnames()) {
        std::cout << "  " << name << '\n';
    }

    return 0;
}