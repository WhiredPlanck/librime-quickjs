#pragma once

#include <rime/candidate.h>

#include "lib/quickjspp.hpp"

using namespace rime;

using Module = qjs::Context::Module;

namespace JSCandidate {

inline void Register(Module& module) {
    module.class_<Candidate>("Candidate")
        .property<&Candidate::type, &Candidate::set_type>("type")
        .property<&Candidate::start, &Candidate::set_start>("start")
        .property<&Candidate::end, &Candidate::set_end>("end")
        .property<&Candidate::quality, &Candidate::set_quality>("quality")
        .property<&Candidate::text>("text")
        .static_fun<&Candidate::GetGenuineCandidate>("getGenuineCandidate")
        .static_fun<&Candidate::GetGenuineCandidates>("getGenuineCandidates");
    module.class_<SimpleCandidate>("SimpleCandidate")
        .base<Candidate>()
        .constructor<const string&, size_t, size_t, const string&, const string&, const string&>()
        .constructor<const string&, size_t, size_t, const string&, const string&>()
        .constructor<const string&, size_t, size_t, const string&>()
        .property<&SimpleCandidate::text, &SimpleCandidate::set_text>("text")
        .property<&SimpleCandidate::comment, &SimpleCandidate::set_comment>("comment")
        .property<&SimpleCandidate::preedit, &SimpleCandidate::set_preedit>("preedit");
    module.class_<ShadowCandidate>("ShadowCandidate")
        .base<Candidate>()
        .constructor<const an<Candidate>&, const string&, const string&, const string&, bool>()
        .constructor<const an<Candidate>&, const string&, const string&, const string&>()
        .constructor<const an<Candidate>&, const string&, const string&>()
        .constructor<const an<Candidate>&, const string&>()
        .property<&ShadowCandidate::text>("text")
        .property<&ShadowCandidate::comment>("comment")
        .property<&ShadowCandidate::preedit>("preedit")
        .property<&ShadowCandidate::item>("item");
    module.class_<UniquifiedCandidate>("UniquifiedCandidate")
        .base<Candidate>()
        .constructor<const an<Candidate>&, const string&, const string&, const string&>()
        .constructor<const an<Candidate>&, const string&, const string&>()
        .constructor<const an<Candidate>&, const string&>()
        .property<&UniquifiedCandidate::text>("text")
        .property<&UniquifiedCandidate::comment>("comment")
        .property<&UniquifiedCandidate::preedit>("preedit")
        .fun<&UniquifiedCandidate::Append>("append");
}

} // namespace JSCandidate
