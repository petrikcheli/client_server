cmake_minimum_required(VERSION 3.5)

project(client_stepik LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(client_stepik main.cpp)

include(GNUInstallDirs)
install(TARGETS client_stepik
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
