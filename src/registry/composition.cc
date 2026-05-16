#include "rime/composition.h"
#include "qjs_registry.h"
#include "rime/segmentation.h"

namespace rime {
namespace quickjs {

void registerComposition(Module &module) {
    module.class_<Preedit>("Preedit")
        .fun<&Preedit::text>("text")
        .fun<&Preedit::caret_pos>("caretPos")
        .fun<&Preedit::sel_start>("selStart")
        .fun<&Preedit::sel_end>("selEnd");

    module.class_<Composition>("Composition")
        .base<Segmentation>()
        .fun<&Composition::HasFinishedComposition>("hasFinishedComposition")
        .fun<&Composition::GetPreedit>("getPreedit")
        .fun<&Composition::GetPrompt>("getPrompt")
        .fun<&Composition::GetCommitText>("getCommitText")
        .fun<&Composition::GetScriptText>("getScriptText")
        .fun<&Composition::GetDebugText>("getDebugText")
        .fun<&Composition::GetTextBefore>("getTextBefore");
}

}
}