<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">"Брестский Государственный технический университет"</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №4</p>
<p align="center">По дисциплине "Общая теория интеллектуальных систем"</p>
<p align="center">Тема: "Работа с проектом NIKA"</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-27</p>
<p align="right">Степанюк И.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

## Задание
1. Изучить [руководство NIKA](https://github.com/ostis-apps/nika)
2. Запустить проект на локальной машине
3. Написать отчет

## Ход работы

### Установка Docker
Установлен Docker Desktop с [официального сайта](https://docs.docker.com/)

Для Windows установлен WSL:
```
wsl --install
```

### Настройка длинных путей
В реестре Windows: `HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\FileSystem`
Параметр `LongPathsEnabled` = 1

Git настройка:
```
git config --global core.longpaths true
```

### Клонирование NIKA
```
git clone -c core.longpaths=true https://github.com/ostis-apps/nika
cd nika
git submodule update --init --recursive
git checkout 69858165c3b5fb26ca783950c74bfe7bddd64a00
```

### Запуск
```
docker compose pull
docker compose up --no-build
```

Доступные адреса:
- sc-web: `localhost:8000`
- dialogue UI: `localhost:3033`
