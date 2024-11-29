const digits = ["零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"]
const units = ["", "拾", "佰", "仟"]
const bigUnits = ["", "万", "亿"]

export function numberToChinese(num) {
    let str = ""
    let unitPos = 0
    let bigUnitPos = 0
    let zero = true
    while (num > 0) {
        let digit = num % 10;
        if (digit === 0) {
            if (!zero) {
                zero = true;
                str = digits[digit] + str
            }
        } else {
            zero = false;
            str = digits[digit] + units[unitPos % 4] + str
        }
        unitPos++;
        if (unitPos % 4 === 0) {
            bigUnitPos++
            str = bigUnits[bigUnitPos] + str
        }
        num = Math.floor(num / 10)
    }
    return str
}
