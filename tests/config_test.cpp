#define CATCH_CONFIG_RUNNER
#include "config.hpp"
#include "testhelpers.hpp"
#include <catch.hpp>

#include <QDir>

TEST_CASE("Config with path that can't be created", "[config]") { CHECK_THROWS(cds::Config { "/" }); }
TEST_CASE("Config with current dir", "[config]")
{
    auto d = QDir::current();
    cds::Config c{ d.absolutePath().toStdString() };

    CHECK(QFile::exists(d.absolutePath() + "/config"));
}

int main(int argc, char* argv[])
{
    test_setupLogger();
    return Catch::Session().run(argc, argv);
}
