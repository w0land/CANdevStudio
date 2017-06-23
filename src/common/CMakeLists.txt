find_package(Threads REQUIRED)

add_library(cds-common config.cpp)
target_include_directories(cds-common INTERFACE ${CMAKE_SOURCE_DIR}/src/common)
target_link_libraries(cds-common PUBLIC spdlog ${CMAKE_THREAD_LIBS_INIT} Qt5::Core)
