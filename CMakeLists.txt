cmake_minimum_required(VERSION 3.16)
project(keeper)

add_subdirectory(test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
set(CMAKE_EXE_LINKER_FLAGS "-static")

find_package(OpenSSL REQUIRED)
message(STATUS "OpenSSL version: ${OPENSSL_VERSION}")
find_package(cpprestsdk REQUIRED)
find_package(ZLIB REQUIRED)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/ SRC)

add_executable(${PROJECT_NAME} main.cpp ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/
)

target_link_libraries(${PROJECT_NAME} cpprest pthread ${OPENSSL_LIBRARIES} ZLIB::ZLIB)