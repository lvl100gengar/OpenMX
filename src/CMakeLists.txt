set(wxWidgets_ROOT_DIR "C:/Users/seanf/Desktop/Programming/wxWidgets/3.1.7")
set(wxWidgets_LIB_DIR "C:/Users/seanf/Desktop/Programming/wxWidgets/3.1.7/lib/vc14x_x64_dll")
set(wxWidgets_CONFIGURATION "mswud")

add_compile_definitions("_WIN32_WINNT=0x0600")

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})



set(BOOST_ROOT "C:/Users/seanf/Desktop/Programming/boost_1_80_0") # either set it here or from the command line  
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED) # header only libraries must not be added here




add_executable(main WIN32 main.cpp)

target_include_directories(main PUBLIC ${Boost_INCLUDE_DIRS}) 
target_link_libraries(main ${Boost_LIBRARIES})
target_link_directories(main PUBLIC "C:/Users/seanf/Desktop/Programming/boost_1_80_0/stage/lib")

target_link_libraries(main ${wxWidgets_LIBRARIES})

add_subdirectory(io)
add_subdirectory(ui)
add_subdirectory(net)
add_subdirectory(protocol)
target_link_libraries(main ui io net protocol)