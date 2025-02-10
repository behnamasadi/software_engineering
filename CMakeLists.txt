cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(software_engineering)

if(NOT "${CMAKE_GENERATOR}" STREQUAL "Ninja Multi-Config")
    # message(WARNING "It's recommended to use -G \"Ninja Multi-Config\" for this project.")
    # OR, if you want to force-stop the configuration:
    message(FATAL_ERROR "Please use -G \"Ninja Multi-Config\" for this project.")
endif()

set(CMAKE_CXX_STANDARD 20) # Replace 20 with the version number of the latest C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message("using Visual Studio C++")

    # set warning level into errors
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    endif()
endif()

message("CMAKE_CXX_COMPILER_VERSION: " ${CMAKE_CXX_COMPILER_VERSION})

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

# ########################################### Software Architectural Patterns ############################################
add_subdirectory(SoftwareArchitecturalPatterns/)

# ########################################### Clean Code############################################
add_subdirectory(CleanCode/)

# ########################################### Refactoring ############################################
add_subdirectory(Refactoring/)

MESSAGE(${CMAKE_CURRENT_SOURCE_DIR})

IF(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/sandbox")
        ADD_SUBDIRECTORY(sandbox)
ENDIF()
