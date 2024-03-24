cmake_minimum_required(VERSION 3.10)

project(StudentInterface)

set(SOURCE_EXE student_run.cpp)

set(SOURCE_LIB source/service_functions.cpp
      	source/start_functions.cpp 
      	source/basic_functions.cpp)

add_library(include STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main include)
