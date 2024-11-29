import { SimpleCandidate, Datetime } from "rime-qjs"

export function* timeTranslator(env, input, seg) {
    if (input == "time") {
        yield new SimpleCandidate("time", seg.start, seg.end, Datetime.format("%H:%M:%S"), "时间")
    }
}
