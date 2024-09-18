cmake_minimum_required(VERSION 3.28.0)
project(T_PROG_1 VERSION 0.1.6 LANGUAGES C)

# каталоги
set(LIB_DIR "LIB")
set(SRC_DIR "SRC")

# источники
set(SRC_FILES
    ${SRC_DIR}/main.c
)

# генерация файла версии
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/LIB/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/LIB/version.h
    @ONLY
)

# настройка библиотек
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

# пути к заголовочным файлам и библиотекам
include_directories(${LIB_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR}/LIB)
include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

# фаги компиляции для библиотек
add_definitions(${GTK4_CFLAGS_OTHER})

# исполняемый файл
add_executable(${PROJECT_NAME} ${SRC_FILES})

# линк с библеотеками
target_link_libraries(${PROJECT_NAME} ${GTK4_LIBRARIES})