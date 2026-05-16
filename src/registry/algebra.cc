#include "rime/algo/algebra.h"
#include "qjs_registry.h"

namespace rime {
namespace quickjs {

std::optional<string> projectionApply(Projection* self) {
    string value;
    if (self->Apply(&value)) {
        return value;
    }
    return std::nullopt;
}

void registerAlgebra(Module& module) {
    module.class_<Projection>("Projection")
        .constructor<>()
        .fun<&Projection::Load>("load")
        .fun<&projectionApply>("apply");
}

}
}