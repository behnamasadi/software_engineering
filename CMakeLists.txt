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


############################################UML Class Diagram Explained With C++ samples############################################

ADD_EXECUTABLE(UML_class_diagram_explanation_samples src/UML/UML_class_diagram_explanation_samples.cpp)
TARGET_LINK_LIBRARIES(UML_class_diagram_explanation_samples)

#Finding Memory leaking, Stack and Heap overflow
#set(CMAKE_CXX_FLAGS "-fsanitize=address ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "-fno-omit-frame-pointer ${CMAKE_CXX_FLAGS}")


#ADD_EXECUTABLE(main  src/main.cpp )
#TARGET_LINK_LIBRARIES(main)
#/home/behnam/workspace/design_pattern/src/Structural/Decorator


#ADD_EXECUTABLE(dependency_injection  src/dependency_injection/dependency_injection.cpp)
#TARGET_LINK_LIBRARIES(dependency_injection)

#ADD_EXECUTABLE(simple_dependency_injection src/dependency_injection/simple_dependency_injection.cpp )
#TARGET_LINK_LIBRARIES(simple_dependency_injection)



############################################Structural############################################

ADD_EXECUTABLE(decorator src/Structural/Decorator/main.cpp
    src/Structural/Decorator/ballPack.hpp
    src/Structural/Decorator/coaching.hpp
    src/Structural/Decorator/rackets.hpp
    src/Structural/Decorator/tennisDecorator.hpp
    src/Structural/Decorator/courtBooking.hpp
    src/Structural/Decorator/clayCourtBooking.hpp
    src/Structural/Decorator/courtBooking.hpp
    src/Structural/Decorator/grassCourtBooking.hpp
    src/Structural/Decorator/hardCourtBooking.hpp)
TARGET_LINK_LIBRARIES(decorator)

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



############################################Behavioral############################################
ADD_EXECUTABLE(observer src/Behavioral/Observer/main.cpp)
TARGET_LINK_LIBRARIES(observer)

ADD_EXECUTABLE(light_on_command src/Behavioral/Command/LightOnCommand.cpp)
TARGET_LINK_LIBRARIES(light_on_command)


ADD_EXECUTABLE(command src/Behavioral/Command/main.cpp)
TARGET_LINK_LIBRARIES(command)

ADD_EXECUTABLE(template_method_before_and_after src/Behavioral/TemplateMethod/template_method_before_and_after.cpp)
TARGET_LINK_LIBRARIES(template_method_before_and_after)

ADD_EXECUTABLE(template_method src/Behavioral/TemplateMethod/template_method.cpp)
TARGET_LINK_LIBRARIES(template_method)


ADD_EXECUTABLE(state src/Behavioral/State/main.cpp)
TARGET_LINK_LIBRARIES(state)

ADD_EXECUTABLE(music_player_app
    src/Behavioral/State/music_player_app.cpp
    src/Behavioral/State/musicPlayer.cpp
    src/Behavioral/State/musicPlayerState.cpp
    src/Behavioral/State/pausedState.cpp
    src/Behavioral/State/playingState.cpp
    src/Behavioral/State/stoppedState.cpp
    )
TARGET_LINK_LIBRARIES(music_player_app)

ADD_EXECUTABLE(chain_of_responsibility src/Behavioral/ChainOfResponsibility/main.cpp)
TARGET_LINK_LIBRARIES(chain_of_responsibility)

ADD_EXECUTABLE(photo_processor src/Behavioral/ChainOfResponsibility/photoProcessor.cpp)
TARGET_LINK_LIBRARIES(photo_processor)

ADD_EXECUTABLE(iterator src/Behavioral/Iterator/main.cpp)
TARGET_LINK_LIBRARIES(iterator)

ADD_EXECUTABLE(mediator_before_after src/Behavioral/Mediator/mediator_before_after.cpp)
TARGET_LINK_LIBRARIES(mediator_before_after)

ADD_EXECUTABLE(robot src/Behavioral/Strategy/robot.cpp)
TARGET_LINK_LIBRARIES(robot)

ADD_EXECUTABLE(memento src/Behavioral/Memento/main.cpp)
TARGET_LINK_LIBRARIES(memento)


############################################Creational############################################

ADD_EXECUTABLE(singleton_before_after src/Creational/Singleton/singleton_before_after.cpp)
TARGET_LINK_LIBRARIES(singleton_before_after)


ADD_EXECUTABLE(factory_method_before_and_after src/Creational/FactoryMethod/factory_method_before_and_after.cpp)
TARGET_LINK_LIBRARIES(factory_method_before_and_after)


ADD_EXECUTABLE(factory_method src/Creational/FactoryMethod/main.cpp)
TARGET_LINK_LIBRARIES(factory_method)

ADD_EXECUTABLE(gui_factory src/Creational/FactoryMethod/guiFactory.cpp)
TARGET_LINK_LIBRARIES(gui_factory)

ADD_EXECUTABLE(abstract_factory_method src/Creational/AbstractFactoryMethod/main.cpp)
TARGET_LINK_LIBRARIES(abstract_factory_method)

ADD_EXECUTABLE(abstract_factory_method_before_after src/Creational/AbstractFactoryMethod/abstract_factory_method_before_after.cpp)
TARGET_LINK_LIBRARIES(abstract_factory_method_before_after)


ADD_EXECUTABLE(dependency_injection src/DependencyInjection/dependency_injection.cpp)
TARGET_LINK_LIBRARIES(dependency_injection)


