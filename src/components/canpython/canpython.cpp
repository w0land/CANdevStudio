#include "canpython.h"
#include "pythonmodule.h"

#include <confighelpers.h>

#include <QtCore/QtDebug>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#pragma push_macro("slots")
#undef slots
#include "Python.h"
#include <boost/python.hpp>
#pragma pop_macro("slots")

extern "C" PyObject* PyInit_can();

namespace {
const QString defaultPythonPreambule = R"(import can;
)";
} // namespace

CanPython::CanPython()
    : _pytonEditWidget(new QWidget)
    , _editor(new QTextEdit)
    , _bottomButtons({ new QPushButton{ "OK" }, new QPushButton{ "Cancel" }, new QPushButton{ "test" } })
{

    // setupUI
    //
    _editor->setText(defaultPythonPreambule);
    auto mainL = new QVBoxLayout;

    auto buttomL = new QHBoxLayout;
    auto buttomW = new QWidget;

    for (auto* p : _bottomButtons) {
        buttomL->addWidget(p);
    }

    buttomW->setLayout(buttomL);

    mainL->addWidget(_editor);
    mainL->addWidget(buttomW);

    _pytonEditWidget->setLayout(mainL);

    connect(std::get<2>(_bottomButtons), &QPushButton::pressed, [this]() {
        using namespace boost::python;
        qDebug() << "Testing python";
        qDebug() << _editor->toPlainText();
        try {
            PyImport_AppendInittab("can", &PyInit_can);
            Py_Initialize();
            object main_module((handle<>(borrowed(PyImport_AddModule("__main__")))));
            object main_namespace = main_module.attr("__dict__");

            handle<> ret(PyRun_String(
                _editor->toPlainText().toLatin1().data(), Py_file_input, main_namespace.ptr(), main_namespace.ptr()));

            PyObject* ex = PyErr_Occurred();

            if (ex) {
                qWarning() << PyBytes_AS_STRING(PyUnicode_AsEncodedString(ex, "utf-8", "~E~"));
            }

            if (!ret) {
                qWarning() << std::string(extract<std::string>(str(ret))).c_str();
            }

            std::get<2>(_bottomButtons)->setIcon(QIcon::fromTheme("face-cool"));

        } catch (boost::python::error_already_set&) {
            PyErr_Print();
        }
    });

    std::transform(_supportedProps.begin(), _supportedProps.end(), std::inserter(_props, _props.end()),
        [](const auto& v) { return std::make_pair(v.first, QVariant{}); });
}

QWidget* CanPython::mainWidget()
{
    return _pytonEditWidget.data();
}

std::shared_ptr<QObject> CanPython::getQConfig() const
{
    return configHelpers::getQConfig(getSupportedProperties(), _props);
}
