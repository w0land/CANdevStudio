#include <candevice/candevice.h>
#define CATCH_CONFIG_RUNNER
#include <fakeit.hpp>

#include "testhelpers.hpp"

int main(int argc, char *argv[])
{
    test_setupLogger();
    return Catch::Session().run(argc, argv);
}
