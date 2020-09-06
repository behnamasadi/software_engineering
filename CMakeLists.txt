cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_BUILD_TYPE DEBUG)
project(design_pattern)




#C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#Finding Memory leaking, Stack and Heap overflow
#set(CMAKE_CXX_FLAGS "-fsanitize=address ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "-fno-omit-frame-pointer ${CMAKE_CXX_FLAGS}")

#Finding Memory leaking, Stack and Heap overflow
#set(CMAKE_CXX_FLAGS "-fsanitize=address ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "-fno-omit-frame-pointer ${CMAKE_CXX_FLAGS}")

############################################UML Class Diagram Explained With C++ samples############################################

add_executable(class_diagram UML/StructureDiagrams/ClassDiagram/src/class_diagram.cpp)
target_link_libraries(class_diagram)

add_subdirectory(DesignPatern/)

############################################ SOLID ############################################
add_executable(single_responsibility_principle SOLID/SingleResponsibilityPrinciple/single_responsibility_principle.cpp)
target_link_libraries(single_responsibility_principle)

add_executable(open_closed_principle SOLID/OpenClosedPrinciple/open_closed_principle.cpp)
target_link_libraries(open_closed_principle)

add_executable(liskov_substitution_principle SOLID/LiskovSubstitutionPrinciple/liskov_substitution_principle.cpp)
target_link_libraries(liskov_substitution_principle)

add_executable(interface_segregation_principle SOLID/InterfaceSegregationPrinciple/interface_segregation_principle.cpp)
target_link_libraries(interface_segregation_principle)

add_executable(dependency_injection_car_enginge SOLID/DependencyInjection/dependency_injection_car_enginge.cpp)
target_link_libraries(dependency_injection_car_enginge)

add_executable(dependency_inversion_principle SOLID/DependencyInjection/dependency_inversion_principle.cpp)
target_link_libraries(dependency_inversion_principle)

############################################ Rule Of Three Five Zero############################################

add_executable(rule_of_five RuleOfThreeFiveZero/rule_of_five.cpp)
target_link_libraries(rule_of_five)

add_executable(rule_of_three RuleOfThreeFiveZero/rule_of_three.cpp)
target_link_libraries(rule_of_three)

add_executable(rule_of_zero RuleOfThreeFiveZero/rule_of_zero.cpp)
target_link_libraries(rule_of_zero)

############################################ Model View Controller############################################
add_executable(student_model_view_controller ModelViewController/student_model_view_controller.cpp)
target_link_libraries(student_model_view_controller)


############################################ Clean Code############################################

add_executable(cleancode CleanCode/main.cpp)
target_link_libraries(cleancode)

############################################ Refactoring ############################################

add_executable(feature_envy Refactoring/Couplers/Feature_Envy/feature_envy.cpp)
target_link_libraries(feature_envy)

add_executable(message_chains Refactoring/Couplers/Message_Chains/message_chains.cpp)
target_link_libraries(message_chains)

add_executable(primitive_obsession Refactoring/Bloaters/Primitive_Obsession/primitive_obsession.cpp)
target_link_libraries(primitive_obsession)


add_executable(temp DesignPatern/src/temp.cpp)
target_link_libraries(temp)
