#ifndef CANPYTHONPLUGIN_H_UTAWJIZ0
#define CANPYTHONPLUGIN_H_UTAWJIZ0

#include "plugin_type.h"
#include "canpythonmodel.h"

struct CANPytonPlugin {
    using Model = CanPythonModel;
    static constexpr const char* name = "CanPython";
    using PluginType = CANRawPlugin;
};


#endif /* end of include guard: CANPYTHONPLUGIN_H_UTAWJIZ0 */
