#include <rime/key_event.h>

#include "qjs_registry.h"


namespace rime {
namespace quickjs {

void registerKeyEvent(Module &module) {
    module.class_<KeyEvent>("KeyEvent")
        .constructor<>()
        .constructor<int, int>()
        .constructor<const string&>()
        .property<constOverload<>(&KeyEvent::keycode), overload<int>(&KeyEvent::keycode)>("keycode")
        .property<constOverload<>(&KeyEvent::modifier), overload<int>(&KeyEvent::modifier)>("modifier")
        .fun<&KeyEvent::shift>("shift")
        .fun<&KeyEvent::ctrl>("ctrl")
        .fun<&KeyEvent::alt>("alt")
        .fun<&KeyEvent::caps>("caps")
        .fun<&KeyEvent::super>("super")
        .fun<&KeyEvent::release>("release")
        .fun<&KeyEvent::repr>("repr")
        .fun<&KeyEvent::Parse>("parse");

    module.class_<KeySequence>("KeySequence")
        .constructor<>()
        .constructor<const string&>()
        .fun<&KeySequence::repr>("repr")
        .fun<&KeySequence::Parse>("parse");
}

}
}
