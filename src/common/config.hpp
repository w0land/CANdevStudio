#ifndef CONFIG_HPP_7LTAQHQB
#define CONFIG_HPP_7LTAQHQB

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <string>

namespace cds {
struct Config {
    Config(const std::string& path = "");
    void save();

private:
    const std::string _path;
    const QJsonObject _rootObject;
};
};

#endif /* end of include guard: CONFIG_HPP_7LTAQHQB */
