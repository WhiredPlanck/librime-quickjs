#include <rime/config.h>
#include <optional>

#include "qjs_registry.h"
#include "rime/config/config_types.h"

namespace rime {
namespace quickjs {

template <typename T, bool (Config::*method)(const string&, T*)>
std::optional<T> configGetter(Config* c, const string& path) {
    T val;
    if ((c->*method)(path, &val)) {
        return val;
    }
    return std::nullopt;
}

template <typename T, bool (ConfigValue::*method)(T*) const>
std::optional<T> configValueGetter(ConfigValue* v) {
    T val;
    if ((v->*method)(&val)) {
        return val;
    }
    return std::nullopt;
}

auto configMapKeys(ConfigMap* m) {
    vector<string> keys;
    for (const auto& pair : *m) {
        keys.emplace_back(pair.first);
    }   
    return keys;
}

template <typename R>
auto castItemTo(ConfigItem* item) {
    return dynamic_cast<R*>(item);
}


void registerConfig(Module& module) {
    module.class_<Config>("Config")
        .constructor<>()
        .fun<&Config::LoadFromFile>("loadFromFile")
        .fun<&Config::SaveToFile>("savaToFile")
        .fun<&Config::IsNull>("isNull")
        .fun<&Config::IsValue>("isValue")
        .fun<&Config::IsList>("isList")
        .fun<&Config::IsMap>("isMap")
        .fun<&configGetter<bool, &Config::GetBool>>("getBool")
        .fun<&configGetter<int, &Config::GetInt>>("getInt")
        .fun<&configGetter<double, &Config::GetDouble>>("getDouble")
        .fun<&configGetter<string, &Config::GetString>>("getString")
        .fun<overload<const string&>(&Config::GetItem)>("getItem")
        .fun<&Config::GetValue>("getValue")
        .fun<&Config::GetList>("getList")
        .fun<&Config::GetMap>("getMap")
        .fun<&Config::GetListSize>("getListSize")
        
        .fun<&Config::SetBool>("setBool")
        .fun<&Config::SetInt>("setInt")
        .fun<&Config::SetDouble>("setDouble")
        .fun<overload<const string&, const string&>(&Config::SetString)>("setString")
        .fun<overload<const string&, an<ConfigItem>>(&Config::SetItem)>("setItem");

    module.class_<ConfigItem>("ConfigItem")
        .fun("kNull", ConfigItem::kNull)
        .fun("kScalar", ConfigItem::kScalar)
        .fun("kList", ConfigItem::kList)
        .fun("kMap", ConfigItem::kMap)
        .property<&ConfigItem::type>("type")
        .fun<&ConfigItem::empty>("empty")
        .fun<&castItemTo<ConfigValue>>("getValue")
        .fun<&castItemTo<ConfigList>>("getList")
        .fun<&castItemTo<ConfigMap>>("getMap");
    
    module.class_<ConfigValue>("ConfigValue")
        .base<ConfigItem>()
        .fun<&configValueGetter<bool, &ConfigValue::GetBool>>("getBool")
        .fun<&configValueGetter<int, &ConfigValue::GetInt>>("getInt")
        .fun<&configValueGetter<double, &ConfigValue::GetDouble>>("getDouble")
        .fun<&configValueGetter<string, &ConfigValue::GetString>>("getString")
        .fun<&ConfigValue::SetBool>("setBool")
        .fun<&ConfigValue::SetInt>("setInt")
        .fun<&ConfigValue::SetDouble>("setDouble")
        .fun<overload<const string&>(&ConfigValue::SetString)>("setString");

    module.class_<ConfigList>("ConfigList")
        .base<ConfigItem>()
        .constructor<>()
        .property<&ConfigList::size>("size")
        .fun<&ConfigList::GetAt>("getAt")
        .fun<&ConfigList::GetValueAt>("getValueAt")
        .fun<&ConfigList::SetAt>("setAt")
        .fun<&ConfigList::Append>("append");

    module.class_<ConfigMap>("ConfigMap")
        .base<ConfigItem>()
        .constructor<>()
        .fun<&ConfigMap::Get>("get")
        .fun<&ConfigMap::GetValue>("getValue")
        .fun<&ConfigMap::HasKey>("hasKey")
        .fun<&ConfigMap::Set>("set")
        .fun<&configMapKeys>("keys");
}

}
}
