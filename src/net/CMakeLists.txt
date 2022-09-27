add_library(net Connection.cpp ConnectionListener.cpp ConnectionManager.cpp DatagramListener.cpp)



target_include_directories(net PUBLIC ${Boost_INCLUDE_DIRS}) 
target_link_libraries(net ${Boost_LIBRARIES})