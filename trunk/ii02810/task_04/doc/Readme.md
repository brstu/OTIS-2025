<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №4</p>
<p align="center">По дисциплине “Общая теория интеллектуальных систем”</p>
<p align="center">Тема: “Работа с проектом "NIKA" (Intelligent Knowledge-driven Assistant)”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 2 курса</p>
<p align="right">Группы ИИ-28</p>
<p align="right">Каневега К.А.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Работа с проектом **"NIKA"** (Intelligent Knowledge-driven Assistant) #

1.Изучить документацию к Nike
2.Запустить на своем устройстве.
3.Написать отчет.

# Условия #

Все выполняется на Windows 11 Pro 25H2

# Выполнение работы #

Для начала идем в интересующий нас репозиторий [OSTIS/NIKA](https://github.com/ostis-apps/nika).

Здесь нас интересуют необходимые требования: **Requirements**. Там сказано установить **Docker**. Делаем.
<br>
![Docker](images/4.2.png)
<br>
При запуске уcтановщика нам скажут установить WSL. Решаем при помощи cmd и команды wsl --install
<br>
![WSL](images/4.1.png)
<br>
Перезагружаемся.

После перезагрузки, лезем в Редактор Реестра, там нужно найти файл LongPathsEnabled, меняем его значение на 1.
<br>
![Редактор Реестра](images/4.3.png)
<br>
Далее лезем в Git. Запускаем cmd и вписываем одну из команд `git config --system core.longpaths true` либо `git config --global core.longpaths true`.

Снова Перезагрузка.

С подготовкой закончили, начинаем "играться" с Nik-ой.

Начинаем с установки Nik-и.

Вводим следующие команды в cmd:

`git clone -c core.longpaths=true -c core.autocrlf=true https://github.com/ostis-apps/nika`
`cd nika`
`git submodule update --init --recursive`
<br>
![cmd](images/4.4.png)
<br>
<br>
![cmd](images/4.5.png)
<br>
Так как, в репозитории Nik-и не хватает контейнера ostis/nika:0.2.0 на DockerHub, то нам, к величайшему сожалению, придется работать с версией 0.1.0.

Для этого вводим следующую команду:

`git checkout 69858165c3b5fb26ca783950c74bfe7bddd64a00`
<br>
![cmd](images/4.6.png)
<br>
После этого нас ждёт лишь прекрасный запуск Nik-и.

Для того запускаем наш Docker.

Заходим в наш любимый cmd и пишем две следующие команды:
`docker desktop start` и `docker compose pull`
<br>
![cmd](images/4.7.png)
<br>

Далее нужно запустить проект. Пишем в cmd следующее:
`docker compose up --no-build`
<br>
![cmd](images/4.8.png)
<br>
Там будет много сообщений, не пугаемся.
После сообщений:
<br>
![cmd](images/4.9.png)
<br>

Можно проверять работу. Заходим на любой сайт, который доступен.
<br>
![Site](images/4.10.png)
<br>

**ЕСЛИ**, у вас как у меня ничего не работало **ИЛИ** Ника не отвечала, делаем следующее, удаляем в Docker все в Containers и Images.
И делаем всё с шага, когда мы клонировали репозиторий Ники, но после команды 
`git checkout 69858165c3b5fb26ca783950c74bfe7bddd64a00` повторяем команду `git submodule update --init --recursive` 
Далее без изменений. 
Как понять что все удастся и запустится? 

После команды `docker compose up --no-build` у вас начнется запуск, если в строчках с nika-problem-solver в [ ] число больше 1000, значит вас можно поздравить!
<br>
![Solve](images/4.11.png)
<br>
