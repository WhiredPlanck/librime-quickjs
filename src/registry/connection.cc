#include <rime/common.h>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

void registerConnection(Module& module) {
    module.class_<boost::signals2::connection>("Connection")
        .fun<&boost::signals2::connection::disconnect>("disconnect");
}

}
}