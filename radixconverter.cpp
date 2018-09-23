#include "radixconverter.h"

using namespace std;

RadixConverter::RadixConverter(QObject *parent):
    QObject(parent), radixMap{initRadixMap()} {

}

RadixConverter::~RadixConverter() {

}

QString RadixConverter::convertButtonClicked(const QString& number, ulong from, ulong to) {
    if (!isNumberWithRadixValid(number, from)) {
        QChar literal = getWrongLiteralFromNumber(number, from);
        return QString("Invalid literal '%1' for number '%2' with base '%3' at position %4").arg(
                literal,
                number,
                QString::number(from),
                QString::number(number.indexOf(literal) + 1)
            );
    }
    return convertNumberToAnotherRadix(number, from, to);
}

bool RadixConverter::isNumberWithRadixValid(const QString& number, ulong radix) {
    for (QChar c: number) {
        if (radixMap[c] > radix) {
            return false;
        }
    }

    return true;
}

QChar RadixConverter::getWrongLiteralFromNumber(const QString& number, ulong radix) {
    for (QChar c: number) {
        if (radixMap[c] > radix) {
            return c;
        }
    }
    throw runtime_error{"there's no wrong literal in number"};
}

QString RadixConverter::toDecimalByGornerScheme(const QString& number, ulong from) {
    ulong result = 0;
    for (int i = number.length() - 1; i >= 0; i--) {
        ulong digit = radixMap[number[number.length() - i - 1]] - 1;
        result += digit * pow(from, i);
    }
    return QString::number(result);
}

QString RadixConverter::fromDecimalToBase(const QString& number, ulong to) {
    ulong num = number.toULong(), mod;
    QString resultString;
    while (num != 0) {
        mod = num%to;
        num /= to;
        resultString.append(radixMap.key(mod + 1));
    }
    reverse(resultString.begin(), resultString.end());
    return resultString;
}

QString RadixConverter::convertNumberToAnotherRadix(const QString& number, ulong from, ulong to) {
    return fromDecimalToBase(toDecimalByGornerScheme(number, from), to);
}

QHash<QChar, ulong> RadixConverter::initRadixMap() {
    return QHash<QChar, ulong>{
        {'0', 1},
        {'1', 2},
        {'2', 3},
        {'3', 4},
        {'4', 5},
        {'5', 6},
        {'6', 7},
        {'7', 8},
        {'8', 9},
        {'9', 10},
        {'a', 11},
        {'A', 11},
        {'b', 12},
        {'B', 12},
        {'c', 13},
        {'C', 13},
        {'d', 14},
        {'D', 14},
        {'e', 15},
        {'E', 15},
        {'f', 16},
        {'F', 16}
    };
}
