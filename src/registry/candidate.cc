#include <rime/candidate.h>
#include <rime/gear/translator_commons.h>

#include "qjs_registry.h"


namespace rime {
namespace quickjs {

template<typename X, typename Y>
inline bool is(Y* ptr) {
    return bool(dynamic_cast<X*>(ptr));
}

static auto getGenuineCandidate(an<Candidate> cand) {
    return Candidate::GetGenuineCandidate(cand);
}

static auto getGenuineCandidates(an<Candidate> cand) {
    return Candidate::GetGenuineCandidates(cand);
}

void registerCandidate(Module& module) {
    module.class_<Candidate>("Candidate")
        .property<&Candidate::type, &Candidate::set_type>("type")
        .property<&Candidate::start, &Candidate::set_start>("start")
        .property<&Candidate::end, &Candidate::set_end>("end")
        .property<&Candidate::quality, &Candidate::set_quality>("quality")
        .property<&Candidate::text>("text")
        .property<&Candidate::comment>("comment")
        .property<&Candidate::preedit>("preedit")
        .fun<&is<Phrase, Candidate>>("isPhrase")
        .fun<&is<Sentence, Candidate>>("isSentence")
        .fun<&is<SimpleCandidate, Candidate>>("isSimple")
        .fun<&is<ShadowCandidate, Candidate>>("isShadow")
        .fun<&is<UniquifiedCandidate, Candidate>>("isUniquified");
        // .static_fun<&getGenuineCandidate>("getGenuineCandidate")
        // .static_fun<&getGenuineCandidates>("getGenuineCandidates");
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
        .property<&ShadowCandidate::item>("item");
    module.class_<UniquifiedCandidate>("UniquifiedCandidate")
        .base<Candidate>()
        .constructor<const an<Candidate>&, const string&, const string&, const string&>()
        .constructor<const an<Candidate>&, const string&, const string&>()
        .constructor<const an<Candidate>&, const string&>()
        .fun<&UniquifiedCandidate::Append>("append");
}

}
}
