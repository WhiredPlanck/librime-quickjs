#include <rime/config.h>
#include <optional>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

template<typename T>
auto makeConfigGetter(bool (Config::*method)(const string&, T*)) {
    return [method](Config* c, const std::string& path) -> std::optional<T> {
        T val;
        if ((c->*method)(path, &val)) {
            return val;
        }
        return std::nullopt;
    };
}

template<typename T>
auto makeConfigValueGetter(bool (ConfigValue::*method)(T*) const) {
    return [method](ConfigValue* v) -> std::optional<T> {
        T val;
        if ((v->*method)(&val)) {
            return val;
        }
        return std::nullopt;
    };
}

void registerConfig(Module& module) {
    module.class_<Config>("Config")
        .fun<&Config::IsNull>("isNull")
        .fun<&Config::IsValue>("isValue")
        .fun<&Config::IsList>("isList")
        .fun<&Config::IsMap>("isMap")
        .fun("getBool", makeConfigGetter(&Config::GetBool))
        .fun("getInt", makeConfigGetter(&Config::GetInt))
        .fun("getDouble", makeConfigGetter(&Config::GetDouble))
        .fun("getString", makeConfigGetter(&Config::GetString))
        .fun("getItem", [](Config * config, const string& path) {
            return config->GetItem(path);
        })
        .fun<&Config::GetValue>("getValue")
        .fun<&Config::GetList>("getList")
        .fun<&Config::GetMap>("getMap")
        .fun<&Config::GetListSize>("getListSize");

    module.class_<ConfigItem>("ConfigItem")
        .property<&ConfigItem::type>("type");
    
    module.class_<ConfigValue>("ConfigValue")
        .base<ConfigItem>()
        .fun("getBool", makeConfigValueGetter(&ConfigValue::GetBool))
        .fun("getInt", makeConfigValueGetter(&ConfigValue::GetInt))
        .fun("getDouble", makeConfigValueGetter(&ConfigValue::GetDouble))
        .fun("getString", makeConfigValueGetter(&ConfigValue::GetString));

    module.class_<ConfigList>("ConfigList")
        .base<ConfigItem>()
        .fun<&ConfigList::GetAt>("getAt")
        .fun<&ConfigList::GetValueAt>("getValueAt")
        .fun<&ConfigList::size>("size")
        .fun<&ConfigList::empty>("empty");

    module.class_<ConfigMap>("ConfigMap")
        .base<ConfigItem>()
        .fun<&ConfigMap::Get>("get")
        .fun<&ConfigMap::GetValue>("getValue")
        .fun<&ConfigMap::HasKey>("hasKey")
        .fun<&ConfigMap::empty>("empty")
        .fun("keys", [](ConfigMap * m) {
            vector<string> keys;
            for (const auto& pair : *m) {
                keys.emplace_back(pair.first);
            }   
            return keys;
        });
}

}
}
