# Перевірка версії CMake. Якщо версія встановленої програми нижче зазначеної - відбудеться аварійний вихід
cmake_minimum_required(VERSION 3.20) 

# Назва проєкту
project(CalculatorProject C) 

# Додати директорію
include_directories(include) 

# Створення статичної бібліотеки з ім'ям calc
add_library(calc STATIC src/calculator.c)

# Створення виконуваного файлу з ім'ям app
add_executable(app src/main.c)

# Лінкування програми з бібліотекою
target_link_libraries(app calc)

