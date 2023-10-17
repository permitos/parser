#include "dataparser.h"

DataParser::DataParser(): ENCODING_TYPE(0), _yaodStructure(nullptr) {}

DataParser::DataParser(const FileManager fileManager,
                       const int encodingType,
                       YAOD_PTR yaodStructure):
    _fileManager(fileManager), ENCODING_TYPE(encodingType), _yaodStructure(yaodStructure) {

    _fileManager.openFile();
}

DataParser::DataParser(const DataParser &dataParser):
    _fileManager(dataParser.getFileManager()),
    ENCODING_TYPE(dataParser.getEncodingType()),
    _yaodStructure(dataParser.getYaODStructure()) {

    _fileManager.openFile();
}

DataParser::~DataParser() {}

void DataParser::startProcessData() {

    processShell(_yaodStructure->getInsideStructure());
}

void DataParser::processShell(YAOD_PTR shell) {

    std::string groupKeyword = shell->getObject()->getKeyword();

    if(groupKeyword == "RECORDS")
        processRecords(shell);

    else if(groupKeyword == "RECORD")
        processRecord(shell);

    else if(groupKeyword == "GRE")
        processGRE(shell);

    else if(groupKeyword == "GRP")
        processGRP(shell);

    else if (groupKeyword == "GRV" || groupKeyword == "GRK")
        processGRV_GRK(shell);

    // else -> error (exception)
}

void DataParser::processRecords(YAOD_PTR records) {

    while(_fileManager.getPeek() != EOF) {

        YAOD_PTR ptrStartHeaderRecord = records->getInsideStructure();
        YAOD_PTR ptrEndHeaderRecord = ptrStartHeaderRecord;

        while(std::dynamic_pointer_cast<Element>(ptrEndHeaderRecord->getObject())) {

            processElement(ptrEndHeaderRecord);
            ptrEndHeaderRecord = ptrEndHeaderRecord->getPostStructure();
        }

        ptrEndHeaderRecord = ptrEndHeaderRecord->getPrevStructure();

        std::vector<ELEMENT_PTR> elements = getDefiningElements(records, "MRC");

        std::string valueOfMRC = getValueOfParameterElement(getDefiningElements(records, "MRC")[0]);
        processRBODY(ptrEndHeaderRecord->getPostStructure(), valueOfMRC);
    }
}

void DataParser::processElement(YAOD_PTR element) {

    ELEMENT_PTR el = std::dynamic_pointer_cast<Element>(element->getObject());

    if(checkNonInitializedElements(el)) {

        std::string rawData = readValueOfElement(el);
        convertAccordingToGivenConversionWay(el, rawData);
    }
}

std::string DataParser::getValueOfParameterElement(ELEMENT_PTR element) {

    return _valueElements[element->getKeyword() + " " + element->getName()];
}

std::vector<ELEMENT_PTR> DataParser::getDefiningElements(YAOD_PTR shell, std::string keywordElement) const {

    YAOD_PTR inShell = shell->getInsideStructure();
    std::vector<ELEMENT_PTR> elements;

    while(inShell) {

        if(ELEMENT_PTR el = std::dynamic_pointer_cast<Element>(inShell->getObject())) {

            if(el->getKeyword() == keywordElement)
                elements.push_back(el);
        }

        inShell = inShell->getPostStructure();
    }

    return elements;
}

void DataParser::processElementOrShell(YAOD_PTR shell_element) {

    while(shell_element) {

        OBJECT_PTR object = shell_element->getObject();

        if(std::dynamic_pointer_cast<Element>(object))
            processElement(shell_element);

        else if(std::dynamic_pointer_cast<Shell>(object))
            processShell(shell_element);

        if(!shell_element->getPostStructure()) {

            upLevelStruct(shell_element);
            break;
        }
        else
            shell_element = shell_element->getPostStructure();
    }
}

void DataParser::upLevelStruct(YAOD_PTR yaodStructure) {

    yaodStructure = yaodStructure->getShellStructure();
}

void DataParser::processRBODY(YAOD_PTR rbody, std::string valueMRC) {

    for(YAOD_PTR rbodyCurrent = rbody;
        rbodyCurrent != nullptr;
        rbodyCurrent = rbodyCurrent->getPostStructure()) {

        if(SHELL_PTR shell = std::dynamic_pointer_cast<Shell>(rbodyCurrent->getObject())) {

            if(shell->getParameter() == valueMRC) {

                processElementOrShell(rbodyCurrent->getInsideStructure());
                break;
            }
        }
    }
}

void DataParser::processRecord(YAOD_PTR record) {

    while(_fileManager.getPeek() != EOF)
        processElementOrShell(record);
}

void DataParser::processGRE(YAOD_PTR gre) {

    processElementOrShell(gre->getInsideStructure());
}

void DataParser::processGRP(YAOD_PTR grp) {

    std::vector<ELEMENT_PTR> INDs = getDefiningElements(grp, "IND");
    int totalNumberOfCopies = 1;

    for(ELEMENT_PTR IND: INDs)
        totalNumberOfCopies *= std::stoi(IND->getParameter(0));

    for(int i = 0; i < totalNumberOfCopies; ++i)
        processElementOrShell(grp->getInsideStructure());
}

void DataParser::processGRV_GRK(YAOD_PTR grv_grk) {

    std::vector<ELEMENT_PTR> CNTs = getDefiningElements(grv_grk->getShellStructure(), "CNT");
    std::string nameParameter = grv_grk->getObject()->getParameters()[0];
    ELEMENT_PTR CNT = getElementAsParameter(CNTs, nameParameter);

    for(int i = 0; i < std::stoi(getValueOfParameterElement(CNT)); ++i)
        processElementOrShell(grv_grk->getInsideStructure());
}

ELEMENT_PTR DataParser::getElementAsParameter(std::vector<ELEMENT_PTR> elements, std::string nameElement) const {

    for(ELEMENT_PTR element: elements) {

        if(element->getName() == nameElement)
            return element;
    }

    return nullptr;
}

bool DataParser::checkNonInitializedElements(ELEMENT_PTR element) const {

    return !KeywordDescription::checkKeyword(KeywordDescription::NON_INITIALIZED_ELEMENTS, element->getKeyword());
}

std::string DataParser::readValueOfElement(ELEMENT_PTR element) {

    for(ATTRIBUTE_PTR attribute: element->getAttributes()) {

        std::string parameter = attribute->getParameter(0);

        if(KeywordDescription::checkKeyword(KeywordDescription::FORMAT_STORAGE_BINARY, attribute->getName()))
            return readDataFromBinaryFile(parameter);

        else if(KeywordDescription::checkKeyword(KeywordDescription::FORMAT_STORAGE_NOT_BINARY, attribute->getName()))
            return readDataFromNotBinaryFile(parameter);
    }

    return ParserStringDDL::EMPTY_STRING;
}

std::string DataParser::readDataFromBinaryFile(std::string parameterAttribute) {

    const int numberOfBytes = std::stoi(parameterAttribute);
    const char* buffer = readDataFromFile(numberOfBytes);

    std::string hexString;
    int decimal;
    std::stringstream ss;

    for(int i = 0; i < numberOfBytes; ++i) {

        ss << std::hex << ((int) (unsigned char) buffer[i]);
        hexString += ss.str();
        ss.str("");
    }

    delete [] buffer;

    ss << hexString;
    ss >> std::hex >> decimal;

    return std::to_string(decimal);
}

std::string DataParser::readDataFromNotBinaryFile(std::string parameterAttribute) {

    const int numberOfBytes = std::stoi(parameterAttribute);
    const char* buffer = readDataFromFile(numberOfBytes);
    std::string strConvert;

    for(int i = 0; i < numberOfBytes; ++i) {

        if(ENCODING_TYPE == EncodingType::KOI8)
            strConvert += EncodingType::getSymbolFromKOI8((int) (unsigned char) buffer[i]);

        else if(ENCODING_TYPE == EncodingType::CP866)
            strConvert += EncodingType::getSymbolFromCP866((int) (unsigned char) buffer[i]);
    }

    delete [] buffer;

    return strConvert;
}

const char* DataParser::readDataFromFile(const int numberBytes) {

    char* buffer = new char[numberBytes];
    buffer[numberBytes] = '\0';

    _fileManager.readFile(buffer, numberBytes);

    return buffer;
}

void DataParser::convertAccordingToGivenConversionWay(ELEMENT_PTR element, std::string value) {

    ATTRIBUTE_PTR attribute = getAttributeWithConvertWay(element);
    std::string nameElement = element->getKeyword() + " " + element->getName();

    if(checkNaNValue(value)) {

        _valueElements[nameElement] = "NaN";
        return;
    }

    if(attribute) {

        const int FIRST_PARAMETER = 0;
        const int SECOND_PARAMETER = 1;

        const int valueOfElement = std::stoi(value);

        if(attribute->getName() == "S")
            _valueElements[nameElement] = std::to_string(
                                          std::stof(attribute->getParameter(FIRST_PARAMETER)) * valueOfElement
                                          + std::stof(attribute->getParameter(SECOND_PARAMETER))
                                          );

        else if(attribute->getName() == "D")
            _valueElements[nameElement] = std::to_string(
                                          valueOfElement * pow(10, (-1)) * std::stoi(attribute->getParameter(FIRST_PARAMETER))
                                          );

        else if(attribute->getName() == "L") {
            // in developing
        }

        else if(attribute->getName() == "T") {
            // in developing
        }
    }
    else
        _valueElements[nameElement] = value;
}

ATTRIBUTE_PTR DataParser::getAttributeWithConvertWay(ELEMENT_PTR element) {

    for(ATTRIBUTE_PTR attribute: element->getAttributes()) {

        if(KeywordDescription::checkKeyword(KeywordDescription::CONVERSATION_METHOD, attribute->getName()))
            return attribute;
    }

    return nullptr;
}

bool DataParser::checkNaNValue(std::string value) {

    ParserStringDDL::removeSpaceBefore(value);
    return (value.empty()) ? true : false;
}

FileManager DataParser::getFileManager() const { return _fileManager; }
unsigned short DataParser::getEncodingType() const { return ENCODING_TYPE; }
std::shared_ptr<YaODStructure> DataParser::getYaODStructure() const { return _yaodStructure; }
std::map<std::string, std::string> DataParser::getValueElements() const { return _valueElements; }

void DataParser::setFileManager(const FileManager fileManager) { _fileManager = fileManager; }
void DataParser::setEncodingType(const int encodingType) { ENCODING_TYPE = encodingType; }
void DataParser::setYaODStructure(const YAOD_PTR yaodStructure) { _yaodStructure = yaodStructure; }
void DataParser::setValueElements(const std::map<std::string, std::string> valueElements) { _valueElements = valueElements; }







