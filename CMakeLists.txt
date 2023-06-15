cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_BUILD_TYPE Debug)
project(software_engineering)

# C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Finding Memory leaking, Stack and Heap overflow
# set(CMAKE_CXX_FLAGS "-fsanitize=address ${CMAKE_CXX_FLAGS}")
# set(CMAKE_CXX_FLAGS "-fno-omit-frame-pointer ${CMAKE_CXX_FLAGS}")

# Finding Memory leaking, Stack and Heap overflow
# set(CMAKE_CXX_FLAGS "-fsanitize=address ${CMAKE_CXX_FLAGS}")
# set(CMAKE_CXX_FLAGS "-fno-omit-frame-pointer ${CMAKE_CXX_FLAGS}")

# ###########################################UML Class Diagram Explained With C++ samples############################################
add_subdirectory(UML/)

# ########################################### Design Patern ############################################
add_subdirectory(DesignPatern/)

# ########################################### SOLID ############################################
add_subdirectory(SOLID/)

# ########################################### Rule Of Three Five Zero############################################
add_subdirectory(RuleOfThreeFiveZero/)

# ########################################### Model View Controller############################################
add_subdirectory(ModelViewController/)

# ########################################### Clean Code############################################
add_subdirectory(CleanCode/)

# ########################################### Refactoring ############################################
add_subdirectory(Refactoring/)

MESSAGE(${CMAKE_CURRENT_SOURCE_DIR})

IF(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sandbox")
        ADD_SUBDIRECTORY(sandbox)
ENDIF()
