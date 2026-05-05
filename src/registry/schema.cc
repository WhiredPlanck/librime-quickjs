#include <rime/schema.h>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

void registerSchema(Module& module) {
    module.class_<Schema>("Schema")
        .property<&Schema::schema_id>("schemaId")
        .property<&Schema::schema_name>("schemaName")
        .property<&Schema::config>("config");
}

}
}
