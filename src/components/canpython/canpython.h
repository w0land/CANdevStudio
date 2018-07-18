#ifndef CANPYTHON_H_5RHVUNKL
#define CANPYTHON_H_5RHVUNKL

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtCore/QScopedPointer>
#include <QtSerialBus/QCanBusFrame>

#include <componentinterface.h>
#include <context.h>
#include <memory>

class QWidget;
class QTextEdit;
class QPushButton;

class CanPython : public QObject, public ComponentInterface {
    Q_OBJECT

public:
    CanPython();
    QWidget* mainWidget() override;
    void setConfig(const QJsonObject&) override {}
    void setConfig(const QObject&) override {}
    QJsonObject getConfig() const override
    {
        return QJsonObject{};
    }
    std::shared_ptr<QObject> getQConfig() const override;
    void configChanged() override {}

    bool mainWidgetDocked() const override
    {
        return true;
    }
    ComponentInterface::ComponentProperties getSupportedProperties() const override
    {
        return ComponentInterface::ComponentProperties{};
    }

signals:
    void mainWidgetDockToggled(QWidget* widget) override;
    // void txFrameOut(const QCanBusFrame& frame);
    // void rxFrameOut(const QCanBusFrame& frame);

public slots:
    // void txFrameIn(const QCanBusFrame& frame);
    // void rxFrameIn(const QCanBusFrame& frame);
    void stopSimulation() override {}
    void startSimulation() override {}

private:
    QWidget* _mainWidget;

    std::map<QString, QVariant> _props;
    ComponentInterface::ComponentProperties _supportedProps = { { "name", { QVariant::String, true } } };

    QPointer<QWidget> _pytonEditWidget;
    QTextEdit* _editor;
    std::array<QPushButton*, 3> _bottomButtons;
};

#endif /* end of include guard: CANPYTHON_H_5RHVUNKL */
