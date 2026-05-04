#include <rime/config.h>
#include <optional>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

#define GETTER_ALIAS(R, N, F) \
static std::optional<R> N(Config * c, const string& path) { \
    R value;                                              \
    if (c->F(path, &value)) {                             \
        return value;                                     \
    } else {                                              \
        return std::nullopt;                              \
    }                                                     \
}

#define GETTER_ALIAS2(R, N, F) \
static std::optional<R> N(ConfigValue * v) { \
    R value;                                              \
    if (v->F(&value)) {                                  \
        return value;                                     \
    } else {                                              \
        return std::nullopt;                              \
    }                                                     \
}

struct ConfigAlias {
    GETTER_ALIAS(bool, getBool, GetBool)
    GETTER_ALIAS(int, getInt, GetInt)
    GETTER_ALIAS(double, getDouble, GetDouble)
    GETTER_ALIAS(string, getString, GetString)

    static an<ConfigItem> getItem(Config * config, const string& path) {
        return config->GetItem(path);
    }
};

struct ConfigItemAlias {
    static string type(ConfigItem * item) {
        switch (item->type()) {
            case ConfigItem::kNull: return "kNull";
            case ConfigItem::kScalar: return "kScalar";
            case ConfigItem::kList: return "kList";
            case ConfigItem::kMap: return "kMap";
        }
    }
};

struct ConfigValueAlias {
    GETTER_ALIAS2(bool, getBool, GetBool)
    GETTER_ALIAS2(int, getInt, GetInt)
    GETTER_ALIAS2(double, getDouble, GetDouble)
    GETTER_ALIAS2(string, getString, GetString)
};

struct ConfigMapAlias {
    static size_t size(ConfigMap * m) {
        size_t count = 0;
        for (auto it : *m) {
            ++count;
        }
        return count;
    }

    static vector<string> keys(ConfigMap * m) {
        vector<string> keys;
        for (auto [k, _] : *m) {
            keys.emplace_back(k);
        }
        return std::move(keys);
    }
};

void registerConfig(Module& module) {
    module.class_<Config>("Config")
        .fun<&Config::IsNull>("isNull")
        .fun<&Config::IsValue>("isValue")
        .fun<&Config::IsList>("isList")
        .fun<&Config::IsMap>("isMap")
        .fun<&ConfigAlias::getBool>("getBool")
        .fun<&ConfigAlias::getInt>("getInt")
        .fun<&ConfigAlias::getDouble>("getDouble")
        .fun<&ConfigAlias::getString>("getString")
        .fun<&ConfigAlias::getItem>("getItem")
        .fun<&Config::GetValue>("getValue")
        .fun<&Config::GetList>("getList")
        .fun<&Config::GetMap>("getMap")
        .fun<&Config::GetListSize>("getListSize");

    module.class_<ConfigItem>("ConfigItem")
        .property<&ConfigItemAlias::type>("type");
    
    module.class_<ConfigValue>("ConfigValue")
        .base<ConfigItem>()
        .fun<&ConfigValueAlias::getBool>("getBool")
        .fun<&ConfigValueAlias::getInt>("getInt")
        .fun<&ConfigValueAlias::getDouble>("getDouble")
        .fun<&ConfigValueAlias::getString>("getString");

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
        .fun<&ConfigMapAlias::size>("size")
        .fun<&ConfigMapAlias::keys>("keys");
}

}
}
