import { SimpleCandidate, Datetime } from "rime-qjs"

export function* dateTranslator(env, input, seg) {
    if (input == "date") {
        yield new SimpleCandidate("date", seg.start, seg.end, Datetime.format("%Y年%m月%d日"), "日期")
        yield new SimpleCandidate("date", seg.start, seg.end, Datetime.format("%Y-%m-%d"), "日期")
    }
}
