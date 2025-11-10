cmake_minimum_required(VERSION 3.22.1)
project("snxyjde")

set(DOBBY_DIR "C:/Users/rayyi/Desktop/Dobby")

add_subdirectory(${DOBBY_DIR} dobby)

#add_library(${CMAKE_PROJECT_NAME} SHARED xdd.cpp)
#target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${DOBBY_DIR}/include)
#target_link_libraries(${CMAKE_PROJECT_NAME} android log dobby)

add_library(myde SHARED myde.cpp)
target_include_directories(myde PRIVATE ${DOBBY_DIR}/include)
target_link_libraries(myde android log dobby)