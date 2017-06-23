#define CATCH_CONFIG_RUNNER
#include "config.hpp"
#include "testhelpers.hpp"
#include <catch.hpp>

#include <QDir>

TEST_CASE("Config with path that can't be created", "[config]") { CHECK_THROWS(cds::Config{ "/" }); }
TEST_CASE("Non existent config with current dir", "[config]")
{
    auto d = QDir::current();
    cds::Config c{ d.absolutePath().toStdString() };
    CHECK(QFile::exists(d.absolutePath() + "/config"));
    CHECK(QFile::remove(d.absolutePath() + "/config"));
}

struct ValidConfigFileTest {
    ValidConfigFileTest()
        : _cfg([]() -> std::string {
            const std::string f = QDir::current().absolutePath().toStdString() + "/config";
            create_file(f, "{}");
        }())
    {
    }

    cds::Config _cfg;
};

int main(int argc, char* argv[])
{
    test_setupLogger();
    return Catch::Session().run(argc, argv);
}
