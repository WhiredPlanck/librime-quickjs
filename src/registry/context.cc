#include <rime/context.h>
#include <rime/candidate.h>
#include <rime/composition.h>
#include <rime/key_event.h>

#include "qjs_registry.h"
#include "signal.h"

namespace rime {
namespace quickjs {

void registerContext(Module& module) {
    module.class_<Context>("Context")
        .fun<&Context::Commit>("commit")
        .fun<&Context::GetCommitText>("getCommitText")
        .fun<&Context::GetScriptText>("getScriptText")
        .fun<&Context::GetPreedit>("getPreedit")
        .fun<&Context::IsComposing>("isComposing")
        .fun<&Context::HasMenu>("hasMenu")
        .fun<&Context::GetSelectedCandidate>("getSelectedCandidate")
        .fun<overload<const string&>(&Context::PushInput)>("pushInput")
        .fun<&Context::PopInput>("popInput")
        .fun<&Context::DeleteInput>("deleteInput")
        .fun<&Context::Clear>("clear")
        .fun<&Context::Select>("select")
        .fun<&Context::Highlight>("highlight")
        .fun<&Context::ConfirmCurrentSelection>("confirmCurrentSelection")
        .fun<&Context::DeleteCurrentSelection>("deleteCurrentSelection")
        .fun<&Context::ConfirmPreviousSelection>("confirmPreviousSelection")
        .fun<&Context::ReopenPreviousSelection>("reopenPreviousSelection")
        .fun<&Context::ReopenPreviousSegment>("reopenPreviousSegment")
        .fun<&Context::ClearPreviousSegment>("clearPreviousSegment")
        .fun<&Context::ClearNonConfirmedComposition>("clearNonConfirmedComposition")
        .fun<&Context::RefreshNonConfirmedComposition>("refreshNonConfirmedComposition")
        .property<&Context::input>("input")
        .property<&Context::caret_pos>("caretPos")
        .property<nonConstOverload<>(&Context::composition), &Context::set_composition>("composition")
        .property<nonConstOverload<>(&Context::commit_history)>("commitHistory")
        
        .fun<&Context::get_option>("getOption")
        .fun<&Context::set_option>("setOption")
        .fun<&Context::get_property>("getProperty")
        .fun<&Context::set_property>("setProperty")
        .fun<&Context::ClearTransientOptions>("clearTransientOptions")
        
        .property<&Context::commit_notifier>("commitNotifier")
        .property<&Context::select_notifier>("selectNotifier")
        .property<&Context::update_notifier>("updateNotifier")
        .property<&Context::delete_notifier>("deleteNotifier")
        .property<&Context::abort_notifier>("abortNotifier")
        .property<&Context::option_update_notifier>("optionUpdateNotifier")
        .property<&Context::property_update_notifier>("propertyUpdateNotifier")
        .property<&Context::unhandled_key_notifier>("unhandledKeyNotifier");
}

}
}