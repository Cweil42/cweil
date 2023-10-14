cmake_minimum_required(VERSION 3.14)
project(S20-PA01-Sorting)
set (EXE_NAME Sorting)
##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....
set (input01 "input.txt")
#
##########################################
# Copy data files to build dir
foreach(file IN LISTS input01)
    configure_file(${file} ${file} COPYONLY)
endforeach()
set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME} main.cpp DSvector.h DSString.h DSString.cpp)