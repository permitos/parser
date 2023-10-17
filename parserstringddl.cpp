#include "parserstringddl.h"

const std::string ParserStringDDL::DOUBLE_SLASH = "//";
const std::string ParserStringDDL::OPEN_COMMENT = "/*";
const std::string ParserStringDDL::CLOSE_COMMENT = "*/";
const std::string ParserStringDDL::EMPTY_STRING = "";

void ParserStringDDL::removeComments(std::string& str) {

    boost::regex regexComments("//(.*)|/\\*(.*)\\*/");

    boost::sregex_token_iterator iterComments(str.begin(), str.end(), regexComments, 0);
    boost::sregex_token_iterator end;

    while(iterComments != end) {

        str.erase(str.find(*iterComments), (*iterComments).length());
        ++iterComments;
    }
}

void ParserStringDDL::removeSpaceBefore(std::string& str) {

    boost::algorithm::trim_left(str);
}

std::string ParserStringDDL::getWord(std::string& str) {

    removeSpaceBefore(str);

    return getSubStringWord(str, WORD);
}

std::string ParserStringDDL::getSubStringWord(std::string &str, OBJECTS object) {

    std::string element = EMPTY_STRING;

    if(!checkIsValid(str, object)) return element;

    boost::regex regexWord("\\s|\\(|\\)|;|,");
    boost::sregex_token_iterator iterWord(str.begin(), str.end(), regexWord, 0);
    size_t strPosition = str.find(*iterWord);

    element = str.substr(CURRENT_SYMBOL, strPosition);
    str.erase(CURRENT_SYMBOL, strPosition);

    return element;
}

bool ParserStringDDL::checkIsValid(std::string &str, OBJECTS object) {

    switch(object) {

        case WORD:
            if(!checkIsWord(str)) return false;
            break;

        case PARAMETERS:
            if(!checkIsParameter(str)) return false;
            break;

        case ENUMERATION:
            if(!checkIsElementOfEnumeration(str)) return false;
            break;
    }

    return true;
}

bool ParserStringDDL::checkIsElementOfEnumeration(std::string &str) {

    return (str[CURRENT_SYMBOL] == OPEN_BRACKET
            || str[CURRENT_SYMBOL] == CLOSING_BRACKET) ? false : true;
}

bool ParserStringDDL::checkIsParameter(std::string &str) {

    return (str[CURRENT_SYMBOL] == END_STRING
            || str[CURRENT_SYMBOL] == OPEN_BRACKET) ? false : true;
}

bool ParserStringDDL::checkIsWord(std::string &str) {

    return (str[CURRENT_SYMBOL] == OPEN_BRACKET
            || str[CURRENT_SYMBOL] == END_STRING
            || str[CURRENT_SYMBOL] == COMMA
            || str[CURRENT_SYMBOL] == CLOSING_BRACKET) ? false : true;
}

std::vector<std::string> ParserStringDDL::getParameters(std::string &str) {

    removeSpaceBefore(str);

    std::string subStr = getSubstringWithParameters(str);

    return retrievingParameters(subStr, PARAMETERS);
}

std::string ParserStringDDL::getSubstringWithParameters(std::string &str) {

    if(str[CURRENT_SYMBOL] == OPEN_BRACKET) {

        size_t bracketClosePos = str.find(CLOSING_BRACKET);

        if(bracketClosePos != std::string::npos) {

            std::string substring = str.substr(1, bracketClosePos);
            str.erase(CURRENT_SYMBOL, bracketClosePos + 1);

            return substring;
        }
        else
            return EMPTY_STRING;
    }
    else
        return EMPTY_STRING;
}

std::vector<std::string> ParserStringDDL::retrievingParameters(std::string &str, OBJECTS object) {

    std::vector<std::string> parameters;

    removeAllSpaces(str);

    while(!str.empty()) {

        std::string parameter = getSubStringWord(str, object);

        if(parameter == EMPTY_STRING)
            break;
        else
            parameters.push_back(parameter);

        if(!checkIsValid(str, object)) break;

        str.erase(CURRENT_SYMBOL, 1);
    }

    return parameters;
}

std::vector<std::string> ParserStringDDL::getEnumeration(std::string &str) {

    removeSpaceBefore(str);

    return retrievingParameters(str, ENUMERATION);
}

void ParserStringDDL::removeAllSpaces(std::string &str) {

    str.erase(std::remove_if(str.begin(), str.end(),::isspace), str.end());
}

bool ParserStringDDL::checkOpenMultilineComments(const std::string &str) {

    return (str.find(OPEN_COMMENT) != NOT_FOUND) ? true : false;
}

bool ParserStringDDL::checkCloseMultilineComments(const std::string &str) {

    return (str.find(CLOSE_COMMENT) != NOT_FOUND) ? true : false;
}
