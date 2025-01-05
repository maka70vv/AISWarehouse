cmake_minimum_required(VERSION 3.28)
project(AISWarehouseCPP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(/usr/include/postgresql)  # Указываем путь к заголовочным файлам PostgreSQL

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Sql  # Добавляем модуль SQL
        REQUIRED)

add_executable(AISWarehouseCPP main.cpp
        MainWindow.h
        MainWindow.cpp
        DatabaseManager.h
        DatabaseManager.cpp
        AuthDialog.h
        AuthDialog.cpp)

# Подключаем библиотеки PostgreSQL и Qt
target_link_libraries(AISWarehouseCPP
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql  # Подключаем Qt SQL
        pq  # PostgreSQL library
)
