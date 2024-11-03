#pragma once

#include <rime/candidate.h>

#include "lib/quickjspp.hpp"

using namespace rime;

using Module = qjs::Context::Module;

namespace JSCandidate {

inline void Register(Module& module) {
    module.class_<SimpleCandidate>("SimpleCandidate")
        .constructor<const string&, size_t, size_t, const string&, const string&, const string&>()
        // .property<&SimpleCandidate::type, &SimpleCandidate::set_type>("type")
        // .property<&SimpleCandidate::start, &SimpleCandidate::set_start>("start")
        // .property<&SimpleCandidate::end, &SimpleCandidate::set_end>("end")
        .property<&SimpleCandidate::quality, &SimpleCandidate::set_quality>("quality");
        // .property<&SimpleCandidate::text, &SimpleCandidate::set_text>("text")
        // .property<&SimpleCandidate::comment, &SimpleCandidate::set_comment>("comment")
        // .property<&SimpleCandidate::preedit, &SimpleCandidate::set_preedit>("preedit");
}

} // namespace JSCandidate
