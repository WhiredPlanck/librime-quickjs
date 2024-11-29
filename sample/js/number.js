import { numberToChinese } from "./utils/chinese-number.js"

export function* numberTranslator(env, input, seg) {
    if (input.startsWith("/")) {
        let n = input.substring(1)
        if (!Number.isNaN(parseInt(n))) {
            let chineseNum = numberToChinese(n)
            yield new SimpleCandidate("number", seg.start, seg.end, chineseNum, "大写")
        }
    }
}
