cmake_minimum_required(VERSION 3.0.0)
project(miniBaza-PP2 VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)

add_executable(miniBaza-PP2
    src/main.c
    src/DB.c
    src/Menu.c
    src/MainMenu.c
    src/About.c
    src/Overview.c
    src/Sort.c
    include/DB.h
    include/IDE.h
    include/Menu.h
    include/MainMenu.h
    include/About.h
    include/Overview.h
    include/Sort.h
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
