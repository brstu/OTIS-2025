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
<p align="right">Клименко М.С.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

# Работа с проектом **"NIKA"** (Intelligent Knowledge-driven Assistant) #

1. Изучить [руководство](https://github.com/ostis-apps/nika).

2. Запустить данный проект на локальной машине (домашний персональный компьютер, ноутбук, рабочая машина в аудитории и т.п.). Продемонстрировать работу проекта преподавателю.

3. Написать отчет по выполненной работе в .md формате (readme.md) и с помощью pull request разместить его в следующем каталоге: trunk\ii0xxyy\task_04\doc.

# Ход работы 

## Введение
В данной лабораторной работе мы познакомимся с таким проектом как **NIKA** , а также с приложением **Docker Desktop**, которое позволит нам работать с **NIKA**.

### Установка NIKA 0.1.0
 Перейдя в репозиторий [OSTIS/NIKA](https://github.com/ostis-apps/nika), снизу можно увидеть README.md файл с инструкциями по установке, настройке и запуске проекта **NIKA**.

![README.md NIKA](imgs/1.png)

В разделе **Requirements** можно узнать о требуемых утилитах, таких как **Docker**, для работы NIKA.
Перейдя по гиперссылке [Dockers](https://docs.docker.com/), мы попадаем на официальный сайт, с которого можно установить **Docker Desktop**
Для работы данного приложения уже требуется установка **WSL** (Windows Subsystem for Linux), устанавливаем, используя данную команду:

`wsl --install`

Перезагружаемся. Теперь **Docker Desktop** запустился без ошибок:
![Dockers Desktop main window](imgs/2.png)

Теперь берём список команд с README репозитория NIKA и выполняем их в командной строке (перед этим перейдите в свой локальный репозиторий!):
`git clone -c core.longpaths=true -c core.autocrlf=true https://github.com/ostis-apps/nika`
`cd nika`
`git submodule update --init --recursive`
`docker compose pull`
![Commands NIKA](imgs/3.png)

### Ошибки
В простом деле сто процентов будет какой-нибудь подвох и в этот раз без исключений.

#### Как решить банальные ошибки при установке NIKA:

#### Ошибка №1 : "Filename too long"
Для устранения данной ошибки:
##### 1) Переходим в редактор реестра (WIN+R - regedit) по пути Компьютер\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\FileSystem
![reg LPE](imgs/4.png)
Кликаем на файл LongPathsEnabled и пишем в поле "значение" 1.
##### 2) Заходим в командную строку и пишем:
`git config --local core.longpaths true`
После чего ошибка чудесным образом исчезнет.

#### Ошибка №2 : "01.12.2025 Когда обновление?"
После попытки выполнить команду `docker compose pull` у вас выскочит ошибка, о нехватке контейнера ostis/nika:0.2.2 на DockerHub.
Поэтому придётся пользоваться старой версией **NIKA** и вот как на неё переключится:
##### 1) В главном репозитории NIKA перейти во вкладку коммитов.
![NIKA COMMITS](imgs/5.png)
##### 2) Долистать до данного коммита и скопировать его SHA.
![Right commit](imgs/6.png)
##### 3) Откатится до версии 0.1.0.
Выполните команду:
`git checkout 69858165c3b5fb26ca783950c74bfe7bddd64a00`
Вы могли просто выполнить этот шаг, зато теперь знаете как найти и откатится до нужной версии с помощью github :).

##### И ТОЛЬКО ПОСЛЕ этого выполните:
`git submodule update --init --recursive`
Если вы этого не сделали, то всё сносим и заново вписываем установочные команды.

Всё. Теперь ошибка не должна появлятся.

## Запуск NIKA
Запустив утилиту **Docker Desktop** и перейдя в папку с проектом **NIKA** в командной строке, там же пишем:
`docker compose pull`
После чего в **Docker Desktop** во вкладке **Images** должны появится следующие файлы:
![Images Docker Desktop](imgs/7.png)
Теперь в командной строке выполняем:
`docker compose up --no-build`

Вот так должна выглядеть вкладка **Containers** в **Docker Desktop** после этой команды.
![Containers DD](imgs/8.png)

Теперь при вводе в браузер **localhost:8000** нам будет доступна база знаний **NIKA**.
![SC-WEB](imgs/9.png)

А при вводе **localhost:3033** — веб-интерфейс проекта.
![Web UI](imgs/10.png)
