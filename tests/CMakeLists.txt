add_executable(tests main.cpp)

target_include_directories(tests PUBLIC "${OpenMX_SOURCE_DIR}/src")
target_link_libraries(tests PUBLIC io)

include(CTest)

add_subdirectory(io)