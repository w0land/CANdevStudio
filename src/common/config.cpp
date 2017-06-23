#include "config.hpp"
#include "log.hpp"

#include <algorithm>
#include <vector>

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>

namespace cds {

namespace {
    const std::vector<std::string> defaultPaths{ { QDir::homePath().toStdString() + "/.config/cds/" } };
    std::string figureOutPath(const std::string& defDirPath)
    {
        std::vector<std::string> paths;
        if (!defDirPath.empty())
            paths.push_back(defDirPath);

        std::copy(defaultPaths.begin(), defaultPaths.end(), std::back_inserter(paths));

        auto pathIter = std::find_if(paths.begin(), paths.end(), [](const auto& a) {
            const QDir f{ QString::fromStdString(a) };
            return f.exists() && f.isReadable();
        });

        // return default home path!
        if (pathIter == paths.end()) {
            return defaultPaths[0] + "/config";
        }

        return *pathIter + "/config";
    }

    QJsonDocument loadJson(const std::string& path)
    {
        QFile docFile{ QString::fromStdString(path) };

        if (!docFile.exists() || !docFile.isReadable())
            return QJsonDocument{};

        cds_debug("Loading json from {}", docFile.fileName());
        return QJsonDocument::fromBinaryData(docFile.readAll());
    }
}

Config::Config(const std::string& dirPath)
    : _path(figureOutPath(dirPath))
    , _rootObject(loadJson(_path).object())
{
    QFileInfo possibleDir{ QString::fromStdString(_path) };
    if (!possibleDir.exists()) {
        cds_debug("File {} and directory {} does not exists, try to create {}", possibleDir.absoluteFilePath(),
            possibleDir.absoluteDir().path(), possibleDir.absoluteDir().path());
        auto d = possibleDir.absoluteDir();
        if (!d.mkpath("a")) {
            throw std::runtime_error(fmt::format("Unable to create {}", d.path()));
        }
        save();
    }

    cds_info("Config: File loaded {}, json {}", _path.empty() ? "EMPTY" : _path,
        _rootObject.isEmpty() ? "invalid" : "valid");
}

void Config::save()
{
    cds_debug("Saving json under {}", _path);
    if (_path.empty())
        return;

    QFile file{ QString::fromStdString(_path) };
    file.open(QIODevice::ReadWrite);
    file.write(QJsonDocument{ _rootObject }.toJson());
}
}
