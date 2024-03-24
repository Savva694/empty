cmake_minimum_required(VERSION 3.10)

project(RunServer)

set(SOURCE_EXE server_run.cpp)

set(SOURCE_LIB source/server.cpp
      	source/teacher_info.cpp 
      	source/student_info.cpp
		source/session.cpp 
		source/subject.cpp 
		source/exam.cpp
       	source/date.cpp)

add_library(include STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main include)
