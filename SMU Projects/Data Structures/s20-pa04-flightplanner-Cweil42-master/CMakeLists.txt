cmake_minimum_required(VERSION 3.14)
project(S20-PA04-FlightPlanner)
set (EXE_NAME FlightPlanner)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "flightData.txt")
set (input02 "requestedFlight.txt")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 17)
add_executable(${EXE_NAME} main.cpp LinkedList.h ListNode.h DSvector.h DSstack.h tests.cpp AdjacencyList.h AdjacencyList.cpp DSString.cpp DSString.h flightData.h flightData.cpp sourceCity.h sourceCity.cpp requestedFlights.h requestedFlights.cpp)
