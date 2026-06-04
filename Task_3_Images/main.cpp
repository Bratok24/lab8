#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <openssl/sha.h>

// Функция для вычисления SHA256 от байтового массива
std::string sha256(const unsigned char* data, size_t len) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data, len);
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

// Функция для вычисления SHA256 от изображения (пиксельные данные)
std::string imageSHA256(const cv::Mat& image) {
    if (image.empty()) return "";
    return sha256(image.data, image.total() * image.elemSize());
}

int main() {
    std::string imagePath;
    std::cout << "Введите путь к изображению: ";
    std::getline(std::cin, imagePath);

    // 1. Загружаем изображение
    cv::Mat img = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Ошибка: не удалось загрузить изображение!" << std::endl;
        std::cerr << "Проверьте путь и имя файла (не должно быть русских букв и пробелов)" << std::endl;
        return 1;
    }

    std::cout << "Изображение загружено: " << img.cols << " x " << img.rows << " пикселей" << std::endl;

    // 2. Хэш исходного изображения
    std::string hash1 = imageSHA256(img);
    std::cout << "Хэш SHA256 исходного изображения:\n" << hash1 << std::endl;

    // 3. Меняем один канал одного пикселя (красный канал верхнего левого)
    std::cout << "Изменяем красный канал пикселя (0,0) на +1..." << std::endl;
    cv::Vec3b& pixel = img.at<cv::Vec3b>(0, 0);
    pixel[2] = pixel[2] + 1;  // BGR: [0]=Blue, [1]=Green, [2]=Red

    // 4. Хэш изменённого изображения
    std::string hash2 = imageSHA256(img);
    std::cout << "Хэш SHA256 изменённого изображения:\n" << hash2 << std::endl;

    // 5. Сравнение
    bool equal = (hash1 == hash2);
    std::cout << "\nХэши совпадают? " << (equal ? "ДА" : "НЕТ") << std::endl;

    // 6. Сохраняем результат в txt-файл
    std::ofstream out("hash_result.txt");
    if (out.is_open()) {
        out << "=== Результат сравнения хэшей ===\n";
        out << "Исходный хэш:\n" << hash1 << "\n\n";
        out << "Изменённый хэш:\n" << hash2 << "\n\n";
        out << "Совпадают? " << (equal ? "ДА" : "НЕТ") << std::endl;
        out.close();
        std::cout << "\nРезультат сохранён в hash_result.txt" << std::endl;
    } else {
        std::cerr << "Не удалось создать файл hash_result.txt" << std::endl;
    }

    return 0;
}