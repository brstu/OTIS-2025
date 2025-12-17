set -e

echo "=== Очистка предыдущей сборки ==="
rm -rf build

echo "=== Создание каталога сборки ==="
mkdir build
cd build

echo "=== Конфигурация проекта (CMake) ==="
cmake ..

echo "=== Сборка проекта ==="
cmake --build .

echo "=== Запуск модульных тестов ==="
ctest --output-on-failure