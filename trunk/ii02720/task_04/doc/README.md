<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">"Брестский Государственный технический университет"</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №4</p>
<p align="center">По дисциплине "Общая теория интеллектуальных систем"</p>
<p align="center">Тема: "Работа с проектом "NIKA" (Intelligent Knowledge-driven Assistant)"</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Степанюк И.А.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Работа с проектом **"NIKA"** (Intelligent Knowledge-driven Assistant)

## Цель работы

1. Изучить [руководство](https://github.com/ostis-apps/nika).
2. Запустить данный проект на локальной машине.
3. Написать отчет по выполненной работе.

## Ход работы

### Этап 1: Подготовка

Перешел в репозиторий [OSTIS/NIKA](https://github.com/ostis-apps/nika) и изучил README.md файл с инструкциями.

Для запуска проекта необходимо установить Docker. Установил Docker Desktop с официального сайта.

### Этап 2: Клонирование репозитория

```bash
git clone https://github.com/ostis-apps/nika.git
cd nika
git submodule update --init --recursive
```

### Этап 3: Сборка и запуск

```bash
docker compose pull
docker compose up --no-build
```

После успешного запуска проект доступен по адресу: http://localhost:8000

### Этап 4: Демонстрация работы

Проект NIKA успешно запущен и продемонстрирован преподавателю.

## Вывод

В ходе выполнения лабораторной работы изучил проект NIKA, научился работать с Docker и успешно запустил проект на локальной машине.

