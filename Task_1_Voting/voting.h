#pragma once

#include <string>
#include <vector>

// Собственная хэш-функция для фамилий 
unsigned long long hashSurname(const std::string& surname);

// Загрузка голосов из txt-файла (по одной фамилии на строку)
void enrolled(const std::string& filepath);

// Регистрация голоса по фамилии с клавиатуры
void unenrolled(const std::string& surname);

// Получение статистики
int voterCount();
int duplicates();
const std::vector<std::string>& voterSurnames();