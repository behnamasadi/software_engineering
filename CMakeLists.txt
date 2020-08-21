cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
set(CMAKE_BUILD_TYPE DEBUG)
project(design_pattern)




#C++ 14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#Finding Memory leaking, Stack and Heap overflow
#set(CMAKE_CXX_FLAGS "-fsanitize=address ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "-fno-omit-frame-pointer ${CMAKE_CXX_FLAGS}")

#Finding Memory leaking, Stack and Heap overflow
#set(CMAKE_CXX_FLAGS "-fsanitize=address ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "-fno-omit-frame-pointer ${CMAKE_CXX_FLAGS}")

############################################UML Class Diagram Explained With C++ samples############################################

add_executable(class_diagram UML/src/class_diagram.cpp)
target_link_libraries(class_diagram)

############################################ Creational ############################################

add_executable(singleton_before_after src/Creational/Singleton/singleton_before_after.cpp)
target_link_libraries(singleton_before_after)

add_executable(factory_method_before_and_after src/Creational/FactoryMethod/factory_method_before_and_after.cpp)
target_link_libraries(factory_method_before_and_after)

add_executable(vehicle_factory_method src/Creational/FactoryMethod/vehicle_factory_method.cpp)
target_link_libraries(vehicle_factory_method)

add_executable(gui_factory src/Creational/FactoryMethod/guiFactory.cpp)
target_link_libraries(gui_factory)

add_executable(abstract_factory_method src/Creational/AbstractFactoryMethod/main.cpp)
target_link_libraries(abstract_factory_method)

add_executable(abstract_factory_method_before_after src/Creational/AbstractFactoryMethod/abstract_factory_method_before_after.cpp)
target_link_libraries(abstract_factory_method_before_after)

add_executable(gui_abstract_factory src/Creational/AbstractFactoryMethod/gui_abstract_factory.cpp)
target_link_libraries(gui_abstract_factory)

add_executable(car_abstract_factory src/Creational/AbstractFactoryMethod/car_abstract_factory.cpp)
target_link_libraries(car_abstract_factory)


############################################ Structural ############################################


add_executable(bridge src/Structural/Bridge/main.cpp)
target_link_libraries(bridge)

add_executable(tennis_decorator src/Structural/Decorator/tennis_decorator.cpp)
target_link_libraries(tennis_decorator)

add_executable(ice_cream_decorator src/Structural/Decorator/ice_cream_decorator.cpp)
target_link_libraries(ice_cream_decorator)

add_executable(proxy_before_and_after src/Structural/Proxy/before_and_after.cpp)
target_link_libraries(proxy_before_and_after)

add_executable(protection_proxy src/Structural/Proxy/protection_proxy.cpp)
target_link_libraries(protection_proxy)

add_executable(adapter src/Structural/Adapter/main.cpp)
target_link_libraries(adapter)

add_executable(external_polymorphism src/Structural/Adapter/external_polymorphism.cpp)
target_link_libraries(external_polymorphism)

add_executable(facade src/Structural/Facade/main.cpp)
target_link_libraries(facade)

add_executable(remote_dvd_tv src/Structural/Bridge/remote_dvd_tv.cpp)
target_link_libraries(remote_dvd_tv)

add_executable(vehicle_bridge src/Structural/Bridge/vehicle.cpp)
target_link_libraries(vehicle_bridge)

add_executable(time_bridge src/Structural/Bridge/time.cpp)
target_link_libraries(time_bridge)

add_executable(flyweight_counter_strike src/Structural/Flyweight/flyweight_counter_strike.cpp)
target_link_libraries(flyweight_counter_strike)


############################################ Behavioral ############################################
add_executable(notification_iterator src/Behavioral/Iterator/notification_iterator.cpp)
target_link_libraries(notification_iterator)

add_executable(observer src/Behavioral/Observer/main.cpp)
target_link_libraries(observer)

add_executable(clock_timer src/Behavioral/Observer/clocktimer.cpp)
target_link_libraries(clock_timer)

add_executable(light_on_command src/Behavioral/Command/LightOnCommand.cpp)
target_link_libraries(light_on_command)


add_executable(command src/Behavioral/Command/main.cpp)
target_link_libraries(command)

add_executable(template_method_order src/Behavioral/TemplateMethod/template_method_order.cpp)
target_link_libraries(template_method_order)

add_executable(template_method src/Behavioral/TemplateMethod/template_method.cpp)
target_link_libraries(template_method)

add_executable(machine_on_off_state src/Behavioral/State/machine_on_off_state.cpp)
target_link_libraries(machine_on_off_state)

add_executable(music_player_state src/Behavioral/State/music_player_state.cpp)
target_link_libraries(music_player_state)

add_executable(chain_of_responsibility src/Behavioral/ChainOfResponsibility/main.cpp)
target_link_libraries(chain_of_responsibility)

add_executable(photo_processor src/Behavioral/ChainOfResponsibility/photoProcessor.cpp)
target_link_libraries(photo_processor)

add_executable(iterator src/Behavioral/Iterator/main.cpp)
target_link_libraries(iterator)

add_executable(mediator_before_after src/Behavioral/Mediator/mediator_before_after.cpp)
target_link_libraries(mediator_before_after)

add_executable(airport_mediator_traffic_pattern src/Behavioral/Mediator/airport_mediator_traffic_pattern.cpp)
target_link_libraries(airport_mediator_traffic_pattern)

add_executable(chat_room_mediator src/Behavioral/Mediator/chat_room_mediator.cpp)
target_link_libraries(chat_room_mediator)

add_executable(null_object src/Behavioral/NullObject/null_object.cpp)
target_link_libraries(null_object)

add_executable(robot src/Behavioral/Strategy/robot.cpp)
target_link_libraries(robot)

add_executable(billing_strategy src/Behavioral/Strategy/billing_strategy.cpp)
target_link_libraries(billing_strategy)

add_executable(memento src/Behavioral/Memento/main.cpp)
target_link_libraries(memento)

add_executable(shopping_item_visitor src/Behavioral/Visitor/shopping_item_visitor.cpp)
target_link_libraries(shopping_item_visitor)

add_executable(file_visitor src/Behavioral/Visitor/file_visitor.cpp)
target_link_libraries(file_visitor)

add_executable(car_visitor src/Behavioral/Visitor/car_visitor.cpp)
target_link_libraries(car_visitor)

add_executable(expression_printer src/Behavioral/Visitor/expression_printer.cpp)
target_link_libraries(expression_printer)

add_executable(stock_visitor src/Behavioral/Visitor/stock_visitor.cpp)
target_link_libraries(stock_visitor)


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

add_executable(clean_code Clean_Code/main.cpp)
target_link_libraries(clean_code)

############################################ Refactoring ############################################

add_executable(feature_envy Refactoring/Couplers/Feature_Envy/feature_envy.cpp)
target_link_libraries(feature_envy)

add_executable(message_chains Refactoring/Couplers/Message_Chains/message_chains.cpp)
target_link_libraries(message_chains)

add_executable(primitive_obsession Refactoring/Bloaters/Primitive_Obsession/primitive_obsession.cpp)
target_link_libraries(primitive_obsession)
