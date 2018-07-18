#include "pythonmodule.h"

#include <boost/python.hpp>

BOOST_PYTHON_MODULE(can)
{
    using namespace boost::python;
    class_<CanPythonModule>("CanModule").def("setPorts", &CanPythonModule::setPorts);
}
