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

############################################ Creational ############################################




###################### (1) Abstract Factory ###########################

add_executable(gui_abstract_factory src/Creational/AbstractFactoryMethod/gui_abstract_factory.cpp)
target_link_libraries(gui_abstract_factory)

add_executable(simple_gui_abstract_factory src/Creational/AbstractFactoryMethod/simple_gui_abstract_factory.cpp)
target_link_libraries(simple_gui_abstract_factory)

add_executable(shape_abstract_factory src/Creational/AbstractFactoryMethod/shape_abstract_factory.cpp)
target_link_libraries(shape_abstract_factory)

add_executable(car_abstract_factory src/Creational/AbstractFactoryMethod/car_abstract_factory.cpp)
target_link_libraries(car_abstract_factory)

add_executable(maze_abstract_factory src/Creational/AbstractFactoryMethod/maze_abstract_factory.cpp)
target_link_libraries(maze_abstract_factory)

###################### (2) Builder ###########################

add_executable(pizza_builder src/Creational/Builder/pizza_builder.cpp)
target_link_libraries(pizza_builder)

add_executable(airplane_builder src/Creational/Builder/airplane_builder.cpp)
target_link_libraries(airplane_builder)

###################### (3) Factory Method ###########################

add_executable(ai_agent_factory_method src/Creational/FactoryMethod/ai_agent_factory_method.cpp)
target_link_libraries(ai_agent_factory_method)

add_executable(computer_factory_method src/Creational/FactoryMethod/computer_factory_method.cpp)
target_link_libraries(computer_factory_method)

add_executable(gui_factory_method src/Creational/FactoryMethod/gui_factory_method.cpp)
target_link_libraries(gui_factory_method)

add_executable(vehicle_factory_method src/Creational/FactoryMethod/vehicle_factory_method.cpp)
target_link_libraries(vehicle_factory_method)

add_executable(frameworks_factory_method src/Creational/FactoryMethod/frameworks_factory_method.cpp)
target_link_libraries(frameworks_factory_method)

add_executable(parameterized_factory_methods src/Creational/FactoryMethod/parameterized_factory_methods.cpp)
target_link_libraries(parameterized_factory_methods)


###################### (4) Prototype ###########################

add_executable(prototype src/Creational/Prototype/prototype.cpp)
target_link_libraries(prototype)

add_executable(bullet_prototype src/Creational/Prototype/bullet_prototype.cpp)
target_link_libraries(bullet_prototype)



###################### (5) Singleton ###########################

add_executable(singleton_before_after src/Creational/Singleton/singleton_before_after.cpp)
target_link_libraries(singleton_before_after)

add_executable(logger_singletone src/Creational/Singleton/logger_singletone.cpp)
target_link_libraries(logger_singletone)

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

###################### (1) Chain Of Responsibility ###########################
add_executable(chain_of_responsibility src/Behavioral/ChainOfResponsibility/main.cpp)
target_link_libraries(chain_of_responsibility)

add_executable(photo_processor src/Behavioral/ChainOfResponsibility/photoProcessor.cpp)
target_link_libraries(photo_processor)
###################### (2) Command ###########################

add_executable(light_on_command src/Behavioral/Command/LightOnCommand.cpp)
target_link_libraries(light_on_command)

add_executable(command src/Behavioral/Command/main.cpp)
target_link_libraries(command)

###################### (3) Iterator ###########################
add_executable(notification_iterator src/Behavioral/Iterator/notification_iterator.cpp)
target_link_libraries(notification_iterator)

add_executable(iterator src/Behavioral/Iterator/main.cpp)
target_link_libraries(iterator)

###################### (4) Mediator ###########################


add_executable(mediator_before_after src/Behavioral/Mediator/mediator_before_after.cpp)
target_link_libraries(mediator_before_after)

add_executable(airport_mediator_traffic_pattern src/Behavioral/Mediator/airport_mediator_traffic_pattern.cpp)
target_link_libraries(airport_mediator_traffic_pattern)

add_executable(chat_room_mediator src/Behavioral/Mediator/chat_room_mediator.cpp)
target_link_libraries(chat_room_mediator)


###################### (5) Memento ###########################

add_executable(memento src/Behavioral/Memento/main.cpp)
target_link_libraries(memento)

###################### (6) NullObject ###########################

add_executable(null_object src/Behavioral/NullObject/null_object.cpp)
target_link_libraries(null_object)

###################### (7) Observer ###########################

add_executable(observer src/Behavioral/Observer/main.cpp)
target_link_libraries(observer)

add_executable(clocktimer src/Behavioral/Observer/clocktimer.cpp)
target_link_libraries(clocktimer)

add_executable(car_observer src/Behavioral/Observer/car_observer.cpp)
target_link_libraries(car_observer)

add_executable(rocket_observer src/Behavioral/Observer/rocket_observer.cpp)
target_link_libraries(rocket_observer)


###################### (8) State ###########################
add_executable(machine_on_off_state src/Behavioral/State/machine_on_off_state.cpp)
target_link_libraries(machine_on_off_state)

add_executable(music_player_state src/Behavioral/State/music_player_state.cpp)
target_link_libraries(music_player_state)
###################### (9) Strategy ###########################

add_executable(robot src/Behavioral/Strategy/robot.cpp)
target_link_libraries(robot)

add_executable(billing_strategy src/Behavioral/Strategy/billing_strategy.cpp)
target_link_libraries(billing_strategy)

###################### (10) TemplateMethod ###########################
add_executable(template_method_order src/Behavioral/TemplateMethod/template_method_order.cpp)
target_link_libraries(template_method_order)

add_executable(template_method src/Behavioral/TemplateMethod/template_method.cpp)
target_link_libraries(template_method)
###################### (11) Visitor ###########################
add_executable(expression_printer src/Behavioral/Visitor/expression_printer.cpp)
target_link_libraries(expression_printer)

add_executable(stock_visitor src/Behavioral/Visitor/stock_visitor.cpp)
target_link_libraries(stock_visitor)

add_executable(shopping_item_visitor src/Behavioral/Visitor/shopping_item_visitor.cpp)
target_link_libraries(shopping_item_visitor)

add_executable(file_visitor src/Behavioral/Visitor/file_visitor.cpp)
target_link_libraries(file_visitor)

add_executable(car_visitor src/Behavioral/Visitor/car_visitor.cpp)
target_link_libraries(car_visitor)

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
