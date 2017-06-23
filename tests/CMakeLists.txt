macro(cds_add_test name)
    string(TOLOWER ${name} ${name}_lower)
    add_executable(${${name}_lower}_test ${${name}_lower}_test.cpp)
    target_compile_options(${${name}_lower}_test PRIVATE $<$<CXX_COMPILER_ID:GNU>:-fno-devirtualize>)
    target_link_libraries(${${name}_lower}_test candevice Qt5::Core Qt5::SerialBus testhelpers)
    add_test(NAME ${name}Test COMMAND ${${name}_lower}_test)
endmacro()

include_directories(${CMAKE_SOURCE_DIR}/3rdParty/fakeit/single_header/catch)
include_directories(${CMAKE_SOURCE_DIR}/3rdParty/fakeit/config/catch)
include_directories(${CMAKE_SOURCE_DIR}/src/components)

add_library(testhelpers testhelpers.cpp)
target_link_libraries(testhelpers cds-common)

cds_add_test(Example)
cds_add_test(CanDevice)
cds_add_test(Config)
