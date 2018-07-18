#ifndef CANPYTHONMODEL_H_VH7ABO2C
#define CANPYTHONMODEL_H_VH7ABO2C

#include "canpython.h"
#include "componentmodel.h"
#include "nodepainter.h"

class CanPythonModel : public ComponentModel<CanPython, CanPythonModel> {
    Q_OBJECT
public:
    CanPythonModel();
    unsigned int nPorts(QtNodes::PortType portType) const override
    {
        Q_UNUSED(portType);

        return 1;
    }
    QtNodes::NodeDataType dataType(QtNodes::PortType portType, QtNodes::PortIndex portIndex) const override
    {
        Q_UNUSED(portType);
        Q_UNUSED(portIndex);

        return QtNodes::NodeDataType{};
    }

    std::shared_ptr<QtNodes::NodeData> outData(QtNodes::PortIndex port) override
    {
        Q_UNUSED(port);
        return std::shared_ptr<QtNodes::NodeData>();
    }

    void setInData(std::shared_ptr<QtNodes::NodeData> nodeData, QtNodes::PortIndex port) override
    {
        Q_UNUSED(nodeData);
        Q_UNUSED(port);
    }

    QtNodes::NodePainterDelegate* painterDelegate() const override
    {
        return static_cast<QtNodes::NodePainterDelegate*>(const_cast<NodePainter*>(&_painter));
    }

    static QColor headerColor()
    {
        return QColor(144, 187, 62);
    }

public slots:
    void filteredTx(const QCanBusFrame& frame)
    {
        Q_UNUSED(frame);
    }

    void filteredRx(const QCanBusFrame& frame)
    {
        Q_UNUSED(frame);
    }

signals:
    void filterTx(const QCanBusFrame& frame);
    void filterRx(const QCanBusFrame& frame);
    void requestRedraw();

private:
    NodePainter _painter;
};

#endif /* end of include guard: CANPYTHONMODEL_H_VH7ABO2C */
