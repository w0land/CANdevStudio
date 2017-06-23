
#include <candevice/candevice.h>
#define CATCH_CONFIG_RUNNER
#include <fakeit.hpp>

#include "candeviceinterface.hpp"
#include "canfactory.hpp"

#include "log.hpp"
#include "testhelpers.hpp"

QString operator"" _qs(const char* p, long unsigned int size) { return QString::fromLatin1(p, size); }

TEST_CASE("Initialization failed", "[candevice]")
{
    using namespace fakeit;
    fakeit::Mock<CanFactoryInterface> factoryMock;
    fakeit::When(Method(factoryMock, create)).Return(nullptr);
    CanDevice canDevice{ factoryMock.get() };
    CHECK(canDevice.init("", "") == false);
}

TEST_CASE("Initialization succedded", "[candevice]")
{
    using namespace fakeit;
    fakeit::Mock<CanFactoryInterface> factoryMock;
    fakeit::Mock<CanDeviceInterface> deviceMock;

    const auto backend = "this is a test backend"_qs;
    const auto iface = "this is a test iface"_qs;

    Fake(Dtor(deviceMock));
    When(Method(deviceMock, framesWritten)).Do([](const auto& cb) { cb(100); });
    Fake(Method(deviceMock, framesReceived));
    Fake(Method(deviceMock, errorOccurred));

    When(Method(factoryMock, create).Using(Eq(backend), Eq(iface))).Return(&(deviceMock.get()));
    CanDevice canDevice{ factoryMock.get() };
    CHECK(canDevice.init(backend, iface) == true);
}

int main(int argc, char* argv[])
{
    test_setupLogger();
    cds_debug("Staring unit tests");
    return Catch::Session().run(argc, argv);
}
