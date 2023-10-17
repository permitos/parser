#include "keywordsdescription.h"

const std::vector<std::string> KeywordDescription::ELEMENTS = {"MIT", "CHA", "KEY", "LNG", "MRC", "IND", "CNT", "REF"};
const std::vector<std::string> KeywordDescription::SHELLS = {"GRE", "GRP", "GRV", "GRR", "GRK", "RECORD", "RECORDS", "FAMILY", "RBODY", "LGRR"};
const std::vector<std::string> KeywordDescription::CONVERSATION_METHOD = {"S", "D", "L", "T"};
const std::vector<std::string> KeywordDescription::FORMAT_PRINT = {"PF", "PA", "PC"};
const std::vector<std::string> KeywordDescription::FORMAT_STORAGE_BINARY = {"B", "L", "FC", "BI", "BN", "BP"};
const std::vector<std::string> KeywordDescription::FORMAT_STORAGE_NOT_BINARY = {"F", "A", "FA", "AA", "AS"};
const std::vector<std::string> KeywordDescription::LIST_OF_VALUES = {"LSTO", "LNAT"};
const std::vector<std::string> KeywordDescription::NON_INITIALIZED_ELEMENTS = {"IND"};
const std::vector<std::string> KeywordDescription::ATTRIBUTE_WITHOUT_PARAMETERS = {"NA"};
const std::vector<std::string> KeywordDescription::ELEMENTS_WITHOUT_ATTRIBUTES = {"IND"};
const std::vector<std::string> KeywordDescription::ELEMENTS_WITH_PARAMETERS = {"KEY", "IND", "MRC", "CHA"};
const std::vector<std::string> KeywordDescription::SHELLS_WITHOUT_NAME = {"RECORDS"};
const std::vector<std::string> KeywordDescription::SHELLS_WITH_PARAMETERS = {"GRK", "GRV", "GRR"};

bool KeywordDescription::checkKeyword(std::vector<std::string> keywords, const std::string keyword) {

    return (std::find(keywords.begin(), keywords.end(), keyword) != keywords.end()) ? true : false;
}
