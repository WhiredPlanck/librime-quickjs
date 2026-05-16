#include <rime/schema.h>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

void registerSchema(Module& module) {
    module.class_<Schema>("Schema")
        .constructor<const string&>()
        .property<&Schema::schema_id>("schemaId")
        .property<&Schema::schema_name>("schemaName")
        .property<&Schema::config>("config")
        .property<&Schema::page_size>("pageSize")
        .property<&Schema::select_keys, &Schema::set_select_keys>("selectKeys");
}

}
}
