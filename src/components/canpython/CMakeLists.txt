find_package(Boost COMPONENTS python3)
find_package(PythonLibs REQUIRED)
find_package(Qt5QuickWidgets REQUIRED)

if( NOT Boost_FOUND OR NOT PYTHONLIBS_FOUND)
    message(STATUS "CanPython plugin cannot be loaded")
    return()
endif()

set(COMPONENT_NAME canpython)

set(SRC
    canpython.cpp
    canpythonmodel.cpp
    pythonmodule.cpp
)

#python_add_module(can-python  pythonmodule.cpp)
#target_include_directories(can-python PRIVATE ${PYTHON_INCLUDE_DIRS})

add_library(${COMPONENT_NAME} ${SRC})
target_link_libraries(${COMPONENT_NAME} cds-common Boost::python3 ${PYTHON_LIBRARIES} Qt5::QuickWidgets)
target_include_directories(${COMPONENT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE ${PYTHON_INCLUDE_DIRS})
