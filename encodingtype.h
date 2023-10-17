#ifndef ENCODINGTYPE_H
#define ENCODINGTYPE_H

#include <iostream>
#include <map>

/* EncodingType класс, в котором описаны различные совместимые кодировки.
 * Передав значение кода символа и выбрав в классе нужную кодировку,
 * посредством соответствующего метода, можно получить значение символа в новой кодировке.*/

class EncodingType {

    static const std::map <int, char> _CP866;
    static const std::map <int, char> _KOI8;

    EncodingType() = default;
    virtual ~EncodingType() = default;

public:

    enum codingType{KOI8 = 1, CP866};

    static char getSymbolFromCP866(const int numCoding);
    static char getSymbolFromKOI8(const int numCoding);
};

#endif // ENCODINGTYPE_H
