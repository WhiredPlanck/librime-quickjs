#include <rime/menu.h>
#include <rime/translation.h>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

void registerMenu(Module& module) {
    module.class_<Menu>("Menu")
        .constructor<>()
        .fun<&Menu::AddTranslation>("addTranslation")
        .fun<&Menu::Prepare>("prepare")
        .fun<&Menu::GetCandidateAt>("getCandidateAt")
        .property<&Menu::candidate_count>("candidateCount")
        .fun<&Menu::empty>("empty");
}

}
}