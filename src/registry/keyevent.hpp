#pragma once

#include "lib/quickjspp.hpp"
#include "rime/key_event.h"

using namespace rime;

using Module = qjs::Context::Module;

namespace JSKeyEvent {

struct KeyEventAlias {
    static int getKeycode(KeyEvent * ke) { return ke->keycode(); }
    static int getModifier(KeyEvent * ke) { return ke->modifier(); }
};

inline void Register(Module &module) {
    module.class_<KeyEvent>("KeyEvent")
        .constructor<>()
        .constructor<int, int>()
        .property<&KeyEventAlias::getKeycode>("keycode")
        .property<&KeyEventAlias::getModifier>("modifier")
        .fun<&KeyEvent::shift>("shift")
        .fun<&KeyEvent::ctrl>("ctrl")
        .fun<&KeyEvent::alt>("alt")
        .fun<&KeyEvent::caps>("caps")
        .fun<&KeyEvent::super>("super")
        .fun<&KeyEvent::release>("release")
        .fun<&KeyEvent::repr>("repr")
        .fun<&KeyEvent::Parse>("parse");
}

} // namespace JSKeyEvent

