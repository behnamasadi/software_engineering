# ########################################### Creational ############################################

# ##################### (1) Abstract Factory ###########################

add_executable(gui_abstract_factory src/Creational/AbstractFactoryMethod/gui_abstract_factory.cpp)
target_link_libraries(gui_abstract_factory)

add_executable(simple_gui_abstract_factory src/Creational/AbstractFactoryMethod/simple_gui_abstract_factory.cpp)
target_link_libraries(simple_gui_abstract_factory)

add_executable(shape_abstract_factory src/Creational/AbstractFactoryMethod/shape_abstract_factory.cpp)
target_link_libraries(shape_abstract_factory)

add_executable(car_abstract_factory src/Creational/AbstractFactoryMethod/car_abstract_factory.cpp)
target_link_libraries(car_abstract_factory)

# ##################### (2) Builder ###########################
add_executable(pizza_builder src/Creational/Builder/pizza_builder.cpp)
target_link_libraries(pizza_builder)

add_executable(airplane_builder src/Creational/Builder/airplane_builder.cpp)
target_link_libraries(airplane_builder)

# ##################### (3) Factory Method ###########################
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

add_executable(factory_method_conceptual src/Creational/FactoryMethod/factory_method_conceptual.cpp)
target_link_libraries(factory_method_conceptual)

# ##################### (4) Prototype ###########################
add_executable(prototype src/Creational/Prototype/prototype.cpp)
target_link_libraries(prototype)

add_executable(bullet_prototype src/Creational/Prototype/bullet_prototype.cpp)
target_link_libraries(bullet_prototype)

# ##################### (5) Singleton ###########################
add_executable(singleton_before_after src/Creational/Singleton/singleton_before_after.cpp)
target_link_libraries(singleton_before_after)

add_executable(logger_singletone src/Creational/Singleton/logger_singletone.cpp)
target_link_libraries(logger_singletone)

add_executable(naive_singleton src/Creational/Singleton/naive_singleton.cpp)
target_link_libraries(naive_singleton -pthread)


# ##################### (6) ObjectPool ###########################
add_executable(expensive_object src/Creational/ObjectPool/expensive_object.cpp)
target_link_libraries(expensive_object )

add_executable(thread_safe_object_pool src/Creational/ObjectPool/thread_safe_object_pool.cpp)
target_link_libraries(thread_safe_object_pool )


# ########################################### Structural ############################################

# ##################### (1) Adapter ###########################
add_executable(legecy_rectangle src/Structural/Adapter/legecy_rectangle.cpp)
target_link_libraries(legecy_rectangle)

add_executable(external_polymorphism src/Structural/Adapter/external_polymorphism.cpp)
target_link_libraries(external_polymorphism)

# ##################### (2) Bridge ###########################
add_executable(bridge src/Structural/Bridge/main.cpp)
target_link_libraries(bridge)

add_executable(remote_dvd_tv src/Structural/Bridge/remote_dvd_tv.cpp)
target_link_libraries(remote_dvd_tv)

add_executable(vehicle_bridge src/Structural/Bridge/vehicle.cpp)
target_link_libraries(vehicle_bridge)

add_executable(time_bridge src/Structural/Bridge/time.cpp)
target_link_libraries(time_bridge)

add_executable(drawingAPI_bridge src/Structural/Bridge/drawingAPI_bridge.cpp)
target_link_libraries(drawingAPI_bridge)

# ##################### (3) Composite ###########################
add_executable(graph_composite src/Structural/Composite/graph_composite.cpp)
target_link_libraries(graph_composite)

add_executable(neural_network src/Structural/Composite/neural_network.cpp)
target_link_libraries(neural_network)

# ##################### (4) Decorator ###########################
add_executable(tennis_decorator src/Structural/Decorator/tennis_decorator.cpp)
target_link_libraries(tennis_decorator)

add_executable(ice_cream_decorator src/Structural/Decorator/ice_cream_decorator.cpp)
target_link_libraries(ice_cream_decorator)

add_executable(customized_car_decorater src/Structural/Decorator/customized_car_decorater.cpp)
target_link_libraries(customized_car_decorater)

add_executable(logger_decorater src/Structural/Decorator/logger_decorater.cpp)
target_link_libraries(logger_decorater)

# ##################### (5) Facade ###########################
add_executable(facade src/Structural/Facade/main.cpp)
target_link_libraries(facade)

# ##################### (6) Flyweight ###########################
add_executable(flyweight_counter_strike src/Structural/Flyweight/flyweight_counter_strike.cpp)
target_link_libraries(flyweight_counter_strike)

add_executable(flyweight_millions_of_tree src/Structural/Flyweight/flyweight_millions_of_tree.cpp)
target_link_libraries(flyweight_millions_of_tree)

add_executable(flyweight_conceptual src/Structural/Flyweight/flyweight_conceptual.cpp)
target_link_libraries(flyweight_conceptual)

# ##################### (7) Proxy ###########################
add_executable(proxy_before_and_after src/Structural/Proxy/before_and_after.cpp)
target_link_libraries(proxy_before_and_after)

add_executable(protection_proxy src/Structural/Proxy/protection_proxy.cpp)
target_link_libraries(protection_proxy)

# ##################### (8) Curiously Recurring Template ###########################
# ##################### (9) Interface-based Programming (IBP) ###########################
# ##################### (10) Private Class Data ###########################

# ########################################### Behavioral ############################################

# ##################### (1) Chain Of Responsibility ###########################
add_executable(chain_of_responsibility_handler src/Behavioral/ChainOfResponsibility/chain_of_responsibility_handler.cpp)
target_link_libraries(chain_of_responsibility_handler)

add_executable(photo_processor src/Behavioral/ChainOfResponsibility/photo_processor.cpp)
target_link_libraries(photo_processor)

add_executable(ATM_chain_of_responsibility src/Behavioral/ChainOfResponsibility/ATM_chain_of_responsibility.cpp)
target_link_libraries(ATM_chain_of_responsibility)


# ##################### (2) Command ###########################
add_executable(light_on_command src/Behavioral/Command/LightOnCommand.cpp)
target_link_libraries(light_on_command)

add_executable(light_on_command_template_based src/Behavioral/Command/light_on_command_template_based.cpp)
target_link_libraries(light_on_command_template_based)

add_executable(giant_command src/Behavioral/Command/giant_command.cpp)
target_link_libraries(giant_command)

# ##################### (3) Interpreter ###########################
add_executable(math_expression_interpreter src/Behavioral/Interpreter/math_expression_interpreter.cpp)
target_link_libraries(math_expression_interpreter)

add_executable(robot_command_interpreter src/Behavioral/Interpreter/robot_command_interpreter.cpp)
target_link_libraries(robot_command_interpreter)


# ##################### (4) Iterator ###########################
add_executable(iterator_design_pattern src/Behavioral/Iterator/iterator_design_pattern.cpp)
target_link_libraries(iterator_design_pattern)

# ##################### (5) Mediator ###########################


add_executable(air_traffic_control src/Behavioral/Mediator/air_traffic_control.cpp)
target_link_libraries(air_traffic_control)

add_executable(chat_room_mediator src/Behavioral/Mediator/chat_room_mediator.cpp)
target_link_libraries(chat_room_mediator)

# ##################### (6) Memento ###########################
add_executable(notepad_memento src/Behavioral/Memento/notepad_memento.cpp)
target_link_libraries(notepad_memento)

# ##################### (7) NullObject ###########################
add_executable(binary_tree_null_object src/Behavioral/NullObject/binary_tree_null_object.cpp)
target_link_libraries(binary_tree_null_object)

add_executable(animal_null_object src/Behavioral/NullObject/animal_null_object.cpp)
target_link_libraries(animal_null_object)

add_executable(ball_screen_saver_null_object src/Behavioral/NullObject/ball_screen_saver_null_object.cpp)
target_link_libraries(ball_screen_saver_null_object)

# ##################### (8) Observer ###########################
add_executable(weather_station_observer src/Behavioral/Observer/weather_station_observer.cpp)
target_link_libraries(weather_station_observer)

add_executable(clocktimer src/Behavioral/Observer/clocktimer.cpp)
target_link_libraries(clocktimer)

add_executable(car_observer src/Behavioral/Observer/car_observer.cpp)
target_link_libraries(car_observer)



add_executable(chat_room_observer src/Behavioral/Observer/chat_room_observer.cpp)
target_link_libraries(chat_room_observer)

# ##################### (9) State ###########################
add_executable(machine_on_off_state src/Behavioral/State/machine_on_off_state.cpp)
target_link_libraries(machine_on_off_state)

add_executable(music_player_state src/Behavioral/State/music_player_state.cpp)
target_link_libraries(music_player_state)

# ##################### (10) Strategy ###########################
add_executable(robot src/Behavioral/Strategy/robot.cpp)
target_link_libraries(robot)

add_executable(billing_strategy src/Behavioral/Strategy/billing_strategy.cpp)
target_link_libraries(billing_strategy)

add_executable(conceptual_strategy src/Behavioral/Strategy/conceptual_strategy.cpp)
target_link_libraries(conceptual_strategy)


# ##################### (11) TemplateMethod ###########################
add_executable(template_method_order src/Behavioral/TemplateMethod/template_method_order.cpp)
target_link_libraries(template_method_order)

add_executable(template_method src/Behavioral/TemplateMethod/template_method.cpp)
target_link_libraries(template_method)

# ##################### (12) Visitor ###########################
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

add_executable(document_visitor src/Behavioral/Visitor/document_visitor.cpp)
target_link_libraries(document_visitor)

add_executable(color_visitor src/Behavioral/Visitor/color_visitor.cpp)
target_link_libraries(color_visitor)
