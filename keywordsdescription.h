#ifndef KEYWORDSDESCRIPTION_H
#define KEYWORDSDESCRIPTION_H

#include <iostream>
#include <vector>
#include <algorithm>

/* KeywordDescription класс, в котором описаны все используемые
 *  в предметной области ключевые слова. */

class KeywordDescription {

    KeywordDescription() = default;
    virtual ~KeywordDescription() = default;

public:

    static const std::vector<std::string> ELEMENTS;
    static const std::vector<std::string> SHELLS;
    static const std::vector<std::string> LIST_OF_VALUES;
    static const std::vector<std::string> FORMAT_STORAGE_BINARY;
    static const std::vector<std::string> FORMAT_STORAGE_NOT_BINARY;
    static const std::vector<std::string> FORMAT_PRINT;
    static const std::vector<std::string> CONVERSATION_METHOD;
    static const std::vector<std::string> NON_INITIALIZED_ELEMENTS;
    static const std::vector<std::string> SHELLS_WITHOUT_NAME;
    static const std::vector<std::string> SHELLS_WITH_PARAMETERS;
    static const std::vector<std::string> ELEMENTS_WITH_PARAMETERS;
    static const std::vector<std::string> ELEMENTS_WITHOUT_ATTRIBUTES;
    static const std::vector<std::string> ATTRIBUTE_WITHOUT_PARAMETERS;

    static bool checkKeyword(std::vector<std::string> keywords, const std::string keyword);
};

#endif // KEYWORDSDESCRIPTION_H
