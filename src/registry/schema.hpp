#pragma once

#include "lib/quickjspp.hpp"
#include "rime/schema.h"

using namespace rime;

using Module = qjs::Context::Module;

namespace JSSchema {

inline void Register(Module& module) {
    module.class_<Schema>("Schema")
        .property<&Schema::schema_id>("schemaId")
        .property<&Schema::schema_name>("schemaName")
        .fun<&Schema::config>("config");
}

} // namespace JSSchema