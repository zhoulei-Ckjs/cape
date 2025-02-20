cmake_minimum_required(VERSION 3.16)
project(dog)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/ SRC)

add_executable(${PROJECT_NAME} main.cpp ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/
)

target_link_libraries(${PROJECT_NAME} cpprest pthread ${OPENSSL_LIBRARIES})