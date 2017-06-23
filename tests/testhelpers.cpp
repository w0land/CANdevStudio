#include "testhelpers.hpp"

std::shared_ptr<spdlog::logger> kDefaultLogger;
void test_setupLogger()
{
    bool haveDebug = std::getenv("CDS_DEBUG") != nullptr;
    kDefaultLogger = spdlog::stdout_color_mt("cds");
    kDefaultLogger->set_level(haveDebug ? spdlog::level::debug : spdlog::level::off);
}
