add_library(net Connection.cpp EndPoint.cpp Listener.cpp)

set(BOOST_ROOT "C:/Users/seanf/Desktop/Programming/boost_1_79_0") # either set it here or from the command line  
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED) # header only libraries must not be added here

target_include_directories(net PUBLIC ${Boost_INCLUDE_DIRS}) 
target_link_libraries(net ${Boost_LIBRARIES})