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

ADD_EXECUTABLE(UML_class_diagram_explanation_samples UML/UML_class_diagram_explanation_samples.cpp)
TARGET_LINK_LIBRARIES(UML_class_diagram_explanation_samples)

############################################Creational############################################

ADD_EXECUTABLE(singleton_before_after src/Creational/Singleton/singleton_before_after.cpp)
TARGET_LINK_LIBRARIES(singleton_before_after)

ADD_EXECUTABLE(factory_method_before_and_after src/Creational/FactoryMethod/factory_method_before_and_after.cpp)
TARGET_LINK_LIBRARIES(factory_method_before_and_after)

ADD_EXECUTABLE(vehicle_factory_method src/Creational/FactoryMethod/vehicle_factory_method.cpp)
TARGET_LINK_LIBRARIES(vehicle_factory_method)

ADD_EXECUTABLE(gui_factory src/Creational/FactoryMethod/guiFactory.cpp)
TARGET_LINK_LIBRARIES(gui_factory)

ADD_EXECUTABLE(abstract_factory_method src/Creational/AbstractFactoryMethod/main.cpp)
TARGET_LINK_LIBRARIES(abstract_factory_method)

ADD_EXECUTABLE(abstract_factory_method_before_after src/Creational/AbstractFactoryMethod/abstract_factory_method_before_after.cpp)
TARGET_LINK_LIBRARIES(abstract_factory_method_before_after)

ADD_EXECUTABLE(gui_abstract_factory src/Creational/AbstractFactoryMethod/gui_abstract_factory.cpp)
TARGET_LINK_LIBRARIES(gui_abstract_factory)

ADD_EXECUTABLE(car_abstract_factory src/Creational/AbstractFactoryMethod/car_abstract_factory.cpp)
TARGET_LINK_LIBRARIES(car_abstract_factory)


############################################Structural############################################


ADD_EXECUTABLE(bridge src/Structural/Bridge/main.cpp)
TARGET_LINK_LIBRARIES(bridge)

ADD_EXECUTABLE(tennis_decorator src/Structural/Decorator/tennis_decorator.cpp)
TARGET_LINK_LIBRARIES(tennis_decorator)

ADD_EXECUTABLE(ice_cream_decorator src/Structural/Decorator/ice_cream_decorator.cpp)
TARGET_LINK_LIBRARIES(ice_cream_decorator)

ADD_EXECUTABLE(proxy_before_and_after src/Structural/Proxy/before_and_after.cpp)
TARGET_LINK_LIBRARIES(proxy_before_and_after)

ADD_EXECUTABLE(protection_proxy src/Structural/Proxy/protection_proxy.cpp)
TARGET_LINK_LIBRARIES(protection_proxy)

ADD_EXECUTABLE(adapter src/Structural/Adapter/main.cpp)
TARGET_LINK_LIBRARIES(adapter)

ADD_EXECUTABLE(external_polymorphism src/Structural/Adapter/external_polymorphism.cpp)
TARGET_LINK_LIBRARIES(external_polymorphism)

ADD_EXECUTABLE(facade src/Structural/Facade/main.cpp)
TARGET_LINK_LIBRARIES(facade)

ADD_EXECUTABLE(remote_dvd_tv src/Structural/Bridge/remote_dvd_tv.cpp)
TARGET_LINK_LIBRARIES(remote_dvd_tv)

ADD_EXECUTABLE(vehicle_bridge src/Structural/Bridge/vehicle.cpp)
TARGET_LINK_LIBRARIES(vehicle_bridge)

ADD_EXECUTABLE(time_bridge src/Structural/Bridge/time.cpp)
TARGET_LINK_LIBRARIES(time_bridge)

ADD_EXECUTABLE(flyweight_counter_strike src/Structural/Flyweight/flyweight_counter_strike.cpp)
TARGET_LINK_LIBRARIES(flyweight_counter_strike)


############################################Behavioral############################################
ADD_EXECUTABLE(notification_iterator src/Behavioral/Iterator/notification_iterator.cpp)
TARGET_LINK_LIBRARIES(notification_iterator)

ADD_EXECUTABLE(observer src/Behavioral/Observer/main.cpp)
TARGET_LINK_LIBRARIES(observer)

ADD_EXECUTABLE(clock_timer src/Behavioral/Observer/clocktimer.cpp)
TARGET_LINK_LIBRARIES(clock_timer)

ADD_EXECUTABLE(light_on_command src/Behavioral/Command/LightOnCommand.cpp)
TARGET_LINK_LIBRARIES(light_on_command)


ADD_EXECUTABLE(command src/Behavioral/Command/main.cpp)
TARGET_LINK_LIBRARIES(command)

ADD_EXECUTABLE(template_method_order src/Behavioral/TemplateMethod/template_method_order.cpp)
TARGET_LINK_LIBRARIES(template_method_order)

ADD_EXECUTABLE(template_method src/Behavioral/TemplateMethod/template_method.cpp)
TARGET_LINK_LIBRARIES(template_method)

ADD_EXECUTABLE(machine_on_off_state src/Behavioral/State/machine_on_off_state.cpp)
TARGET_LINK_LIBRARIES(machine_on_off_state)

ADD_EXECUTABLE(music_player_state src/Behavioral/State/music_player_state.cpp)
TARGET_LINK_LIBRARIES(music_player_state)

ADD_EXECUTABLE(chain_of_responsibility src/Behavioral/ChainOfResponsibility/main.cpp)
TARGET_LINK_LIBRARIES(chain_of_responsibility)

ADD_EXECUTABLE(photo_processor src/Behavioral/ChainOfResponsibility/photoProcessor.cpp)
TARGET_LINK_LIBRARIES(photo_processor)

ADD_EXECUTABLE(iterator src/Behavioral/Iterator/main.cpp)
TARGET_LINK_LIBRARIES(iterator)

ADD_EXECUTABLE(mediator_before_after src/Behavioral/Mediator/mediator_before_after.cpp)
TARGET_LINK_LIBRARIES(mediator_before_after)

ADD_EXECUTABLE(airport_mediator_traffic_pattern src/Behavioral/Mediator/airport_mediator_traffic_pattern.cpp)
TARGET_LINK_LIBRARIES(airport_mediator_traffic_pattern)

ADD_EXECUTABLE(chat_room_mediator src/Behavioral/Mediator/chat_room_mediator.cpp)
TARGET_LINK_LIBRARIES(chat_room_mediator)

ADD_EXECUTABLE(null_object src/Behavioral/NullObject/null_object.cpp)
TARGET_LINK_LIBRARIES(null_object)

ADD_EXECUTABLE(robot src/Behavioral/Strategy/robot.cpp)
TARGET_LINK_LIBRARIES(robot)

ADD_EXECUTABLE(billing_strategy src/Behavioral/Strategy/billing_strategy.cpp)
TARGET_LINK_LIBRARIES(billing_strategy)

ADD_EXECUTABLE(memento src/Behavioral/Memento/main.cpp)
TARGET_LINK_LIBRARIES(memento)

ADD_EXECUTABLE(shopping_item_visitor src/Behavioral/Visitor/shopping_item_visitor.cpp)
TARGET_LINK_LIBRARIES(shopping_item_visitor)

ADD_EXECUTABLE(file_visitor src/Behavioral/Visitor/file_visitor.cpp)
TARGET_LINK_LIBRARIES(file_visitor)

ADD_EXECUTABLE(car_visitor src/Behavioral/Visitor/car_visitor.cpp)
TARGET_LINK_LIBRARIES(car_visitor)

ADD_EXECUTABLE(expression_printer src/Behavioral/Visitor/expression_printer.cpp)
TARGET_LINK_LIBRARIES(expression_printer)

ADD_EXECUTABLE(stock_visitor src/Behavioral/Visitor/stock_visitor.cpp)
TARGET_LINK_LIBRARIES(stock_visitor)


############################################SOLID############################################
ADD_EXECUTABLE(single_responsibility_principle SOLID/SingleResponsibilityPrinciple/single_responsibility_principle.cpp)
TARGET_LINK_LIBRARIES(single_responsibility_principle)

ADD_EXECUTABLE(open_closed_principle SOLID/OpenClosedPrinciple/open_closed_principle.cpp)
TARGET_LINK_LIBRARIES(open_closed_principle)

ADD_EXECUTABLE(liskov_substitution_principle SOLID/LiskovSubstitutionPrinciple/liskov_substitution_principle.cpp)
TARGET_LINK_LIBRARIES(liskov_substitution_principle)

ADD_EXECUTABLE(interface_segregation_principle SOLID/InterfaceSegregationPrinciple/interface_segregation_principle.cpp)
TARGET_LINK_LIBRARIES(interface_segregation_principle)

ADD_EXECUTABLE(dependency_injection_car_enginge SOLID/DependencyInjection/dependency_injection_car_enginge.cpp)
TARGET_LINK_LIBRARIES(dependency_injection_car_enginge)

ADD_EXECUTABLE(dependency_inversion_principle SOLID/DependencyInjection/dependency_inversion_principle.cpp)
TARGET_LINK_LIBRARIES(dependency_inversion_principle)

############################################Rule Of Three Five Zero############################################

ADD_EXECUTABLE(rule_of_five RuleOfThreeFiveZero/rule_of_five.cpp)
TARGET_LINK_LIBRARIES(rule_of_five)

ADD_EXECUTABLE(rule_of_three RuleOfThreeFiveZero/rule_of_three.cpp)
TARGET_LINK_LIBRARIES(rule_of_three)

ADD_EXECUTABLE(rule_of_zero RuleOfThreeFiveZero/rule_of_zero.cpp)
TARGET_LINK_LIBRARIES(rule_of_zero)

############################################Model View Controller############################################
ADD_EXECUTABLE(student_model_view_controller ModelViewController/student_model_view_controller.cpp)
TARGET_LINK_LIBRARIES(student_model_view_controller)


############################################Clean Code############################################

ADD_EXECUTABLE(clean_code Clean_Code/main.cpp)
TARGET_LINK_LIBRARIES(clean_code)

############################################ Refactoring ############################################

ADD_EXECUTABLE(refactoring Refactoring/main.cpp)
TARGET_LINK_LIBRARIES(refactoring)

ADD_EXECUTABLE(feature_envy Refactoring/Couplers/Feature_Envy/feature_envy.cpp)
TARGET_LINK_LIBRARIES(feature_envy)

ADD_EXECUTABLE(message_chains Refactoring/Couplers/Message_Chains/message_chains.cpp)
TARGET_LINK_LIBRARIES(message_chains)

ADD_EXECUTABLE(primitive_obsession Refactoring/Bloaters/Primitive_Obsession/primitive_obsession.cpp)
TARGET_LINK_LIBRARIES(primitive_obsession)

