cmake_minimum_required(VERSION 3.10)
project(Lab8)

set(CMAKE_CXX_STANDARD 17)

add_executable(Task1_Voting Task_1_Voting/main.cpp Task_1_Voting/voting.cpp)

target_compile_definitions(Task1_Voting PRIVATE
    CLASSMATES_FILE="${CMAKE_SOURCE_DIR}/Task_1_Voting/classmates.txt")

if(MINGW OR MSVC)
    target_compile_options(Task1_Voting PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

add_executable(Task2_Store Task_2_Store/main.cpp Task_2_Store/HashTable.cpp)

if(MINGW OR MSVC)
    target_compile_options(Task2_Store PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

find_package(OpenCV REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(Task3_Images Task_3_Images/main.cpp)

target_link_libraries(Task3_Images ${OpenCV_LIBS} OpenSSL::Crypto)

file(COPY ${CMAKE_SOURCE_DIR}/Task_3_Images/istockphoto-682143832-612x612.jpg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})