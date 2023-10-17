#include "yaodparser.h"

YaODParser::YaODParser() {}

YaODParser::YaODParser(const FileManager fileManager): _fileManager(fileManager) {

    _fileManager.openFile();
    _yaodStructure = std::make_shared<YaODStructure>(YaODStructure());
}

YaODParser::YaODParser(const YaODParser& yaodParser): _fileManager(yaodParser.getFileManager()) {

    _fileManager.openFile();
    _yaodStructure = yaodParser.getYaODStructure();
}

YaODParser::~YaODParser() {}

void YaODParser::initializeYaOD() {

    std::string stringDDL = ParserStringDDL::EMPTY_STRING;

    while(_fileManager.isNotEndOfFile() && _fileManager.getline(stringDDL)) {

        if(ParserStringDDL::checkOpenMultilineComments(stringDDL))
            getFullStringMultilineComments(stringDDL);

        removeUnnecessaryInformation(stringDDL);

        if(stringDDL.empty())
            continue;

        else if(stringDDL.find(ParserStringDDL::END_STRING) == ParserStringDDL::NOT_FOUND)
            getFullStringDDL(stringDDL);

        analyzeStringDDL(stringDDL);
    }
}

void YaODParser::removeUnnecessaryInformation(std::string &str) {

    ParserStringDDL::removeComments(str);
    ParserStringDDL::removeSpaceBefore(str);
}

void YaODParser::getFullStringMultilineComments(std::string &str) {

    while(_fileManager.isNotEndOfFile() && !ParserStringDDL::checkCloseMultilineComments(str)) {

        std::string nextStringDDL = ParserStringDDL::EMPTY_STRING;
        _fileManager.getline(nextStringDDL);
        str += " " + nextStringDDL;
    }
}

void YaODParser::getFullStringDDL(std::string &str) {

    while(_fileManager.isNotEndOfFile() &&
          str.find(ParserStringDDL::END_STRING) == ParserStringDDL::NOT_FOUND) {

        if(str.empty()) continue;

        std::string nextStringDDL = ParserStringDDL::EMPTY_STRING;

        _fileManager.getline(nextStringDDL);

        removeUnnecessaryInformation(nextStringDDL);

        if(nextStringDDL.empty()) continue;

        str += " " + nextStringDDL;
    }
}

void YaODParser::analyzeStringDDL(std::string &stringDDL) {

    std::string keyword = ParserStringDDL::getWord(stringDDL);

    if(keyword == "END")
        upLevelStructure();

    else if(ELEMENT_PTR element = defineObject<Element>(keyword, KeywordDescription::ELEMENTS))
        initializeElement(element, keyword, stringDDL);

    else if(SHELL_PTR shell = defineObject<Shell>(keyword, KeywordDescription::SHELLS))
        initializeShell(shell, keyword, stringDDL);

    else if(LISTOFVALUES_PTR listOfValues = defineObject<ListOfValues>(keyword, KeywordDescription::LIST_OF_VALUES))
        initializeListOfValues(listOfValues, keyword, stringDDL);

    else
        throw YaODStringDDLException(stringDDL);
}

void YaODParser::upLevelStructure() {

    _yaodStructure = _yaodStructure->getShellStructure();
}

template <class object>
std::shared_ptr<object> YaODParser::defineObject(const std::string& keyword, std::vector<std::string> keywords) {

    std::vector<std::string>::iterator iter = std::find(keywords.begin(),
                                                        keywords.end(),
                                                        keyword);

    return (iter != keywords.end()) ? std::make_shared<object>(object()) : nullptr;
}

void YaODParser::initializeElement(ELEMENT_PTR element, const std::string &keyword, std::string &stringDDL) {

    element->setKeyword(keyword);
    element->setParameters(ParserStringDDL::getParameters(stringDDL));
    element->setName(ParserStringDDL::getWord(stringDDL));
    element->setAttributes(getAttributes(stringDDL));

    ValidatorYaOD::validateElement(*element);

    initializationObject(element);
}

void YaODParser::initializeShell(SHELL_PTR shell, const std::string &keyword, std::string &stringDDL) {

    shell->setKeyword(keyword);

    std::vector<std::string> parameters = ParserStringDDL::getParameters(stringDDL);

    if(!parameters.empty())
        shell->setParameter(parameters[0]);

    shell->setName(ParserStringDDL::getWord(stringDDL));

    ValidatorYaOD::validateShell(*shell);

    initializationObject(shell);
}

void YaODParser::initializeListOfValues(LISTOFVALUES_PTR listOfValues, const std::string &keyword, std::string &stringDDL) {

    listOfValues->setKeyword(keyword);
    listOfValues->setName(ParserStringDDL::getWord(stringDDL));

    std::vector<std::string> enumeration = ParserStringDDL::getEnumeration(stringDDL);

    if(enumeration.size() > 1) {

        listOfValues->setEnumeration(enumeration);
        initializationObject(listOfValues);

        return;
    }

    listOfValues->setInitializeValue(enumeration[0]);
    listOfValues->setStep(ParserStringDDL::getParameters(stringDDL)[0]);
    listOfValues->setNumberOfMembers(ParserStringDDL::getWord(stringDDL));

    ValidatorYaOD::validateListOfValues(*listOfValues);

    initializationObject(listOfValues);
}

std::vector<ATTRIBUTE_PTR> YaODParser::getAttributes(std::string& stringDDL) {

    std::vector<ATTRIBUTE_PTR> attributes;

    while(true) {

        if(ATTRIBUTE_PTR attribute = getAttribute(stringDDL))
            attributes.push_back(attribute);
        else
            break;
    }

    return attributes;
}

ATTRIBUTE_PTR YaODParser::getAttribute(std::string& stringDDL) {

    ParserStringDDL::removeSpaceBefore(stringDDL);

    if(stringDDL[0] == ParserStringDDL::END_STRING)
        return nullptr;

    else {

        ATTRIBUTE_PTR attribute = std::make_shared<Attribute>(Attribute());

        attribute->setName(ParserStringDDL::getWord(stringDDL));
        attribute->setParameters(ParserStringDDL::getParameters(stringDDL));

        ValidatorYaOD::validateAttribute(*attribute);

        return attribute;
    }
}

void YaODParser::initializationObject(OBJECT_PTR object) {

    YAOD_PTR newYaODStructure = std::make_shared<YaODStructure>(YaODStructure());
    newYaODStructure->setObject(object);

    OBJECT_PTR currentObject = _yaodStructure->getObject();

    if(std::dynamic_pointer_cast<Element>(currentObject))
        initializationIfCurrentIsElement(newYaODStructure);

    else if(std::dynamic_pointer_cast<Shell>(currentObject))
        initializationIfCurrentIsShell(newYaODStructure);

    else if(std::dynamic_pointer_cast<ListOfValues>(currentObject))
        initializationIfCurrentIsListOfValue(newYaODStructure);

    else
        initializationIfCurrentIsNotInitialized(newYaODStructure);

    _yaodStructure = newYaODStructure;
}

void YaODParser::initializationIfCurrentIsElement(YAOD_PTR newYaODStructure) {

    initializationIfCurrentIsSimple(newYaODStructure);
}

void YaODParser::initializationIfCurrentIsShell(YAOD_PTR newYaODStructure) {

    if(_yaodStructure->getInsideStructure()) {

        newYaODStructure->setPrevStructure(_yaodStructure);
        newYaODStructure->setShellStructure(_yaodStructure->getShellStructure());

        _yaodStructure->setPostStructure(newYaODStructure);
    }

    else {

        _yaodStructure->setInsideStructure(newYaODStructure);

        newYaODStructure->setPrevStructure(nullptr);
        newYaODStructure->setShellStructure(_yaodStructure);
    }
}

void YaODParser::initializationIfCurrentIsListOfValue(YAOD_PTR newYaODStructure) {

    initializationIfCurrentIsSimple(newYaODStructure);
}

void YaODParser::initializationIfCurrentIsSimple(YAOD_PTR newYaODStructure) {

    newYaODStructure->setPrevStructure(_yaodStructure);
    newYaODStructure->setShellStructure(_yaodStructure->getShellStructure());

    _yaodStructure->setPostStructure(newYaODStructure);
}

void YaODParser::initializationIfCurrentIsNotInitialized(YAOD_PTR newYaODStructure) {

    _yaodStructure = newYaODStructure;
}

YAOD_PTR YaODParser::getYaODStructure() const { return _yaodStructure; }
FileManager YaODParser::getFileManager() const { return _fileManager; }

void YaODParser::setYaODStructure(const YAOD_PTR yaodStructure) { _yaodStructure = yaodStructure; }
void YaODParser::setFileManager(const FileManager fileManager) { _fileManager = fileManager; }

