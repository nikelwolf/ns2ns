#pragma once

#include <iostream>
#include <cmath>
#include <algorithm>

#include <QObject>
#include <QHash>

class RadixConverter: public QObject {
    Q_OBJECT
public:
    explicit RadixConverter(QObject *parent = nullptr);
    virtual ~RadixConverter();

public slots:
    QString convertButtonClicked(const QString& number, ulong from, ulong to);

private:
    QHash<QChar, ulong> radixMap;

    bool isNumberWithRadixValid(const QString& number, ulong radix);

    QChar getWrongLiteralFromNumber(const QString& number, ulong radix);

    QString toDecimalByGornerScheme(const QString& number, ulong from);

    QString fromDecimalToBase(const QString& number, ulong to);

    QString convertNumberToAnotherRadix(const QString& number, ulong from, ulong to);

    QHash<QChar, ulong> initRadixMap();
};
