#include "validatoryaod.h"

bool ValidatorYaOD::inGroupValidate(std::vector<std::string> keywords, const std::string &keyword) {

    return (std::find(keywords.begin(), keywords.end(), keyword)
                      != keywords.end()) ? true : false;
}

void ValidatorYaOD::validateElement(const Element &element) {

    if(element.getName().empty())
        throw YaODObjectException("[From VALIDATOR]: The element with the \'" +
                                  element.getKeyword() +
                                  "\' keyword does not have a name!");

    if(element.getParameters().empty()) {

        if(inGroupValidate(KeywordDescription::ELEMENTS_WITH_PARAMETERS, element.getKeyword()))
            throw YaODObjectException("[From VALIDATOR]: The element \'" +
                                      element.getKeyword() + " " + element.getName() +
                                      "\' does not have parameters!");

    }

    if(element.getAttributes().empty()) {

        if(!inGroupValidate(KeywordDescription::ELEMENTS_WITHOUT_ATTRIBUTES, element.getKeyword()))
                throw YaODObjectException("[From VALIDATOR]: The element \'" +
                                          element.getKeyword() + " " + element.getName() +
                                          "\' does not have attributes!");
    }
}

void ValidatorYaOD::validateShell(const Shell &shell) {

    if(shell.getName().empty()) {

        if(!inGroupValidate(KeywordDescription::SHELLS_WITHOUT_NAME, shell.getKeyword()))
            throw YaODObjectException("[From VALIDATOR]: The shell with the \'" +
                                      shell.getKeyword() +
                                      "\' keyword does not have a name!");
    }

    if(shell.getParameter().empty()) {

        if(inGroupValidate(KeywordDescription::SHELLS_WITH_PARAMETERS, shell.getKeyword()))
            throw YaODObjectException("[From VALIDATOR]: The shell with the \'" +
                                      shell.getKeyword() + " " + shell.getName() +
                                      "\' keyword does not have a parameter!");
    }
}

void ValidatorYaOD::validateListOfValues(const ListOfValues &listOfValues) {

    if(listOfValues.getName().empty())
        throw YaODObjectException("[From VALIDATOR]: The list of values with the \'" +
                                  listOfValues.getKeyword() +
                                  "\' keyword does not have a name!");

    if(listOfValues.getEnumeration().empty()) {

        std::string fullNameList = listOfValues.getKeyword() + " " + listOfValues.getName();

        if(listOfValues.getInitializeValue().empty())
            throw YaODObjectException("[From VALIDATOR]: The list of values \'" +
                                      fullNameList +
                                      "\' does not have a initialize value!");

        if(listOfValues.getStep().empty())
            throw YaODObjectException("[From VALIDATOR]: The list of values \'" +
                                      fullNameList +
                                      "\' does not have a step!");

        if(listOfValues.getNumberOfMembers().empty())
            throw YaODObjectException("[From VALIDATOR]: The list of values \'" +
                                      fullNameList +
                                      "\' does not have number of members!");
    }
}

void ValidatorYaOD::validateAttribute(const Attribute &attribute) {

    if(attribute.getName().empty())
        throw YaODObjectException("[From VALIDATOR]: The attribute does not have a name.");

    if(attribute.getParameters().empty()) {

        if(!inGroupValidate(KeywordDescription::ATTRIBUTE_WITHOUT_PARAMETERS, attribute.getName()))
            throw YaODObjectException("[From VALIDATOR]: The attribute does not have parameters.");
    }
}
