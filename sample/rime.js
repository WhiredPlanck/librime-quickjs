import { dateTranslator } from "./js/date.js"
import { timeTranslator } from "./js/time.js"
import { numberTranslator } from "./js/number.js"

globalThis.qjsModules = {
    date_translator: dateTranslator,
    time_translator: timeTranslator,
    number_translator: numberTranslator
}
