cmake_minimum_required(VERSION 3.31)
project(Projeto_AE2 C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

add_executable(${PROJECT_NAME} src/main.c
        src/TelaInicio.c
        src/TelaGame.c
        src/TelaTutorial.c
        include/main.h
        include/TelaInicio.h
        include/TelaTutorial.h
        include/TelaGame.h)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${GTK_CFLAGS})