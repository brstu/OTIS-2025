<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №4</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Работа с проектом "NIKA" (Intelligent Knowledge-driven Assistant)”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Любовицкий Н.Н.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Работа с проектом **"NIKA"** (Intelligent Knowledge-driven Assistant)

1. Изучить [руководство](https://github.com/ostis-apps/nika).

2. Запустить данный проект на локальной машине (домашний персональный компьютер, ноутбук, рабочая машина в аудитории и т.п.). Продемонстрировать работу проекта преподавателю.

3. Написать отчет по выполненной работе в .md формате (readme.md) и с помощью pull request разместить его в следующем каталоге: trunk\ii0xxyy\task_04\doc.

# Ход работы

## Введение

Данная лабораторная работа рассчитана на то, чтобы закрепить знания работы с Git, GitHub. Также она позволяет нам
научиться использовать новые технологии, такую, как Docker, который позволит нам собрать и запустить проект NIKA на нашей
локальной машине, а также уметь применять нестандартные решения.

Данный отчет содержит подробное решение, которое могу предоставить, по запуску проекта NIKA на локальной машине, используя Docker.

### Этап 1 [ Общая Подготовка ]

Переходим [OSTIS/NIKA](https://github.com/ostis-apps/nika).
Снизу можно увидеть README.md
<br>
![NIKA README.md](img/1.png)
<br>
Устанавливаем Docker [https://docs.docker.com/](https://docs.docker.com/).
После установки у нас появляется приложение **Docker Desktop**.
При первом запуске данной программы появилось окно, которое требовало установки **WSL**(Windows Subsystem for Linux):
<br>
![WSL Required](img/2.png)
<br>
Эту проблему решаем вводом в консоль(cmd) командой: `wsl --install`
<br>
![WSL Installation CMD](img/3.png)

Перезагружаемся. После перезагрузки Docker Desktop запустился так, как полагается:
<br>
![WSL Welcome Window](img/4.png)

### 1) В реестре

1. Открыть реестр (`Win + R` и написать `regedit`) <br>
2. Перейти по пути `HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\FileSystem`<br>
3. Найти параметр `LongPathsEnabled` и установить значение на 1.
<br>
![regedit](img/regedit.png)

### 2) Git

- Запустить cmd
- Ввести команду: `git config --system core.longpaths true` либо `git config --global core.longpaths true`

### 3) Перезагрузиться

## Этап 2 [ Установка NIKA 0.1.0 с GitHub ]

Команды в cmd:

```
git clone -c core.longpaths=true -c core.autocrlf=true https://github.com/ostis-apps/nika
cd nika
git submodule update --init --recursive
```

В момент выполнения лабораторной (на 14.11.2025) не хватает контейнера ostis/nika:0.2.0 на DockerHub.
Соответственно нам не удастся запустить проект на последней (на момент выполнения) версии.
Значит нам остается перейти на предыдущую версию (0.1.0).
Для этого введем команду:

```
git checkout 69858165c3b5fb26ca783950c74bfe7bddd64a00
git submodule update --init --recursive
```

![commit hash](img/commit.png)

Этот хеш содержит стабильную версию всех контейнеров для версии проекта 0.1.0.

Отлично, теперь перейдем к заключительному этапу - запуску проекта на локальной машине.

## Этап 3 [ Запуск NIKA ]

Запустим Docker Desktop:
`docker desktop start`

Получим контейнеры с **DockerHub**: `docker compose pull`<br>
После выполненной команды получились следующие контейнеры:
<br>
![regedit](img/docker-containers.png)
<br>
Запустим проект: `docker compose up --no-build`<br>
Ожидаем некоторое время, когда в консоли появиться сообщение/текст в конце:
<br>
![cmd's output](img/cmd-output.png)
<br>
После этого, можно открыть браузер и ввести, в зависимости от того, что Вам хочется просмотреть, URL:

### sc-web - `localhost:8000`

![sc-web](img/web-sc.png)

### dialogue web UI - `localhost:3033`

![dialogue web UI](img/ui.png)
