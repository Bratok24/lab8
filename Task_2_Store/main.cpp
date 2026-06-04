#include "HashTable.h"
#include <iostream>
#include <string>

int main() {
    HashTable priceList;

    // Добавляем товары и их цены
    priceList.add("молоток", 500.0);
    priceList.add("гвозди", 50.0);
    priceList.add("дрель", 3000.0);
    priceList.add("пила", 1200.0);
    priceList.add("отвёртка", 150.0);
    priceList.add("молоток", 550.0); // обновляем цену

    std::cout << "Размер таблицы: " << priceList.size() << std::endl;

    // Поиск цены
    double price;
    if (priceList.find("дрель", price)) {
        std::cout << "Цена дрели: " << price << " руб." << std::endl;
    } else {
        std::cout << "Товар 'дрель' не найден" << std::endl;
    }

    if (priceList.find("гвозди", price)) {
        std::cout << "Цена гвоздей: " << price << " руб." << std::endl;
    }

    // Удаление товара
    if (priceList.remove("гвозди")) {
        std::cout << "Товар 'гвозди' удалён" << std::endl;
    } else {
        std::cout << "Товар 'гвозди' не найден" << std::endl;
    }

    // Проверяем, что гвоздей больше нет
    if (priceList.find("гвозди", price)) {
        std::cout << "Цена гвоздей: " << price << " руб." << std::endl;
    } else {
        std::cout << "Товар 'гвозди' не найден" << std::endl;
    }

    // Поиск несуществующего товара
    if (!priceList.find("шланг", price)) {
        std::cout << "Товар 'шланг' не найден" << std::endl;
    }

    // Проверка на пустоту и размер
    std::cout << "Таблица пуста? " << (priceList.isEmpty() ? "да" : "нет") << std::endl;
    std::cout << "Итоговый размер таблицы: " << priceList.size() << std::endl;

    return 0;
}