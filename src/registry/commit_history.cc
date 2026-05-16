#include <rime/commit_history.h>
#include <rime/composition.h>
#include <rime/key_event.h>

#include "qjs_registry.h"

namespace rime {
namespace quickjs {

CommitRecord* commitHistoryBack(CommitHistory* self) {
    if (self->empty()) return nullptr;
    return &self->back();
}

void registerCommitHistory(Module& module) {
    module.class_<CommitRecord>("CommitRecord")
        .fun<&CommitRecord::type>("type")
        .fun<&CommitRecord::text>("text");
    
    module.class_<CommitHistory>("CommitHistory")
        .property<&CommitHistory::size>("size")
        .fun<overload<const CommitRecord&>(&CommitHistory::Push)>("pushRecord")
        .fun<overload<const KeyEvent&>(&CommitHistory::Push)>("pushKeyEvent")
        .fun<overload<const Composition&, const string&>(&CommitHistory::Push)>("pushCompositionOrInput")
        .fun<&commitHistoryBack>("back")
        .fun<&CommitHistory::repr>("repr")
        .fun<&CommitHistory::latest_text>("latestText")
        .fun<&CommitHistory::empty>("empty")
        .fun<&CommitHistory::clear>("clear")
        .fun<&CommitHistory::pop_back>("popBack");
}

}
}