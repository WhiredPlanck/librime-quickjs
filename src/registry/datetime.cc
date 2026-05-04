#include "extend/datetime.hpp"

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

void registerDatetime(Module& module) {
    module.class_<Datetime>("Datetime")
        .constructor<>()
        .static_fun<&Datetime::format>("format")
        .static_fun<&Datetime::formatTime>("formatTime");
}

}
}