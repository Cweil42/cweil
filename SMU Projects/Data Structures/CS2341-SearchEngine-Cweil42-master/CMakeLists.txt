cmake_minimum_required(VERSION 3.14)
project(SearchEngine)
set (EXE_NAME SearchEngine)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....
# if you need more, add them here and in the foreach stmt below.

#
##########################################
set (input01 "StopWords.txt")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME} main.cpp TreeNode.h AVLTree.h Parser.h Parser.cpp wordIndexes.h wordIndexes.cpp porter2_stemmer.cpp porter2_stemmer.h Processor.h interface.h Processor.cpp interface.cpp hashNode.h hashMap.h fileRank.h fileRank.cpp)
