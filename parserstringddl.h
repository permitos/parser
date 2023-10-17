/*   The class "ParserStringDDL" is designed to split a string
 *   with a description into its syntactic tokens.
 *
 *   This class has definitions of exclusively static variables and functions.
 *   Variables describe the basic syntactic tokens defined for most widely known
 *   languages and libraries. Class methods provide the ability to operate on
 *   the syntactic objects of the library string, as well as the string itself.
 *
 *   Within the scope of a description, there are only three syntactic entities:
 *   a special word, parameters, and enums.
 *
 *   A special word is a word that describes a property of an object:
 *   belonging to a class (elements, groups, lists, etc.),
 *   name, storage and printing formats, etc.
 *
 *   Parameters are a collection of syntactic objects that provide
 *   additional information about the object itself.
 *   This is usually either a reference to an element or a numeric representation.
 *
 *   Enumerations are a collection of syntactic elements that provide
 *   additional information about the order in which data is presented.
 */

#ifndef PARSERSTRINGDDL_H
#define PARSERSTRINGDDL_H

#include <iostream>
#include <vector>
#include <cctype>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

class ParserStringDDL {

    enum OBJECTS {WORD, PARAMETERS, ENUMERATION} objects;

    static std::string getSubstringWithParameters(std::string& str);
    static bool checkIsWord(std::string& str);
    static bool checkIsParameter(std::string& str);
    static bool checkIsElementOfEnumeration(std::string& str);
    static bool checkIsValid(std::string& str, OBJECTS object);
    static std::string getSubStringWord(std::string& str, OBJECTS object);
    static void removeAllSpaces(std::string& str);
    static std::vector<std::string> retrievingParameters(std::string& str, OBJECTS object);

    ParserStringDDL() = default;
    virtual ~ParserStringDDL() = default;

public:

    static const char END_STRING = ';';
    static const char COMMA = ',';
    static const char SPACE = ' ';
    static const char OPEN_BRACKET = '(';
    static const char CLOSING_BRACKET = ')';
    static const int TABULATION = 9;
    static const int CURRENT_SYMBOL = 0;
    static const size_t NOT_FOUND = -1;
    static const std::string DOUBLE_SLASH;
    static const std::string OPEN_COMMENT;
    static const std::string CLOSE_COMMENT;
    static const std::string EMPTY_STRING;

    static void removeSpaceBefore(std::string& str);
    static void removeComments(std::string& str);
    static bool checkOpenMultilineComments(const std::string& str);
    static bool checkCloseMultilineComments(const std::string& str);

    static std::string getWord(std::string& str);
    static std::vector<std::string> getParameters(std::string& str);
    static std::vector<std::string> getEnumeration(std::string& str);
};

#endif // PARSERSTRINGDDL_H
