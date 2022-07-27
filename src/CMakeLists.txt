set(wxWidgets_ROOT_DIR "C:/Users/seanf/Desktop/Programming/wxWidgets/3.1.7")
set(wxWidgets_LIB_DIR "C:/Users/seanf/Desktop/Programming/wxWidgets/3.1.7/lib/vc14x_x64_dll")
set(wxWidgets_CONFIGURATION "mswud")

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
add_executable(main WIN32 main.cpp)
target_link_libraries(main ${wxWidgets_LIBRARIES})

add_subdirectory(io)
add_subdirectory(ui)
add_subdirectory(net)
add_subdirectory(protocol)
target_link_libraries(main ui io net protocol)