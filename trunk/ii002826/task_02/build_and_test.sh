#!/bin/bash

# Создание директории сборки
mkdir -p build
cd build

# Конфигурация проекта
cmake ..

# Сборка
make -j4

# Запуск тестов
echo "Running tests..."
./model_tests

# Анализ покрытия (если собранно в Debug)
if [ -f "model_tests" ]; then
    echo "Test results:"
    ./model_tests --gtest_output=xml:test_results.xml
    
    # Генерация отчета о покрытии
    if command -v gcovr &> /dev/null; then
        echo "Generating coverage report..."
        gcovr -r .. --html --html-details -o coverage_report.html
        echo "Coverage report generated: coverage_report.html"
    fi
fi