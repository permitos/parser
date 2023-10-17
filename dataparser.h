#ifndef DATAPARSER_H
#define DATAPARSER_H

#include "filemanager.h"
#include "yaodstructure.h"
#include "shell.h"
#include "element.h"
#include "listofvalues.h"
#include "keywordsdescription.h"
#include "parserstringddl.h"
#include "encodingtype.h"
#include <sstream>
#include <bitset>
#include <map>

class DataParser {

    FileManager _fileManager;
    unsigned short ENCODING_TYPE;
    YAOD_PTR _yaodStructure;
    std::map <std::string, std::string> _valueElements;

    std::vector<ELEMENT_PTR> getDefiningElements(YAOD_PTR shell, std::string keywordElement) const;
    ELEMENT_PTR getElementAsParameter(std::vector<ELEMENT_PTR> elements, std::string nameElement) const;
    bool checkNonInitializedElements(ELEMENT_PTR element) const;

    void processShell(YAOD_PTR shell);
    void processRecord(YAOD_PTR record);
    void processRBODY(YAOD_PTR rbody, std::string valueMRC);
    void processRecords(YAOD_PTR records);
    void processGRE(YAOD_PTR gre);
    void processGRP(YAOD_PTR grp);
    void processGRV_GRK(YAOD_PTR grv_grk);
    void processGRR(YAOD_PTR grr);

    void processElementOrShell(YAOD_PTR shell_element);

    void processElement(YAOD_PTR element);

    void processInShell(YAOD_PTR shell);

    std::string getValueOfParameterElement(ELEMENT_PTR element);

    void upLevelStruct(YAOD_PTR yaodStructure);
    bool checkNaNValue(std::string value);

    ATTRIBUTE_PTR findAttributeFormatStorage(std::vector<ATTRIBUTE_PTR> attributes);

    const char* readDataFromFile(const int numberBytes);
    std::string readDataFromNotBinaryFile(std::string parameterAttribute);
    std::string readDataFromBinaryFile(std::string parameterAttribute);
    std::string readData(std::vector<ATTRIBUTE_PTR> attributes);
    std::string readValueOfElement(ELEMENT_PTR element);

    void convertAccordingToGivenConversionWay(ELEMENT_PTR element, std::string value);
    std::shared_ptr<Attribute> getAttributeWithConvertWay(ELEMENT_PTR element);

public:

    void startProcessData();

    DataParser();
    explicit DataParser(const FileManager fileManager,
               const int encodingType,
               YAOD_PTR yaodStructure);
    DataParser(const DataParser& dataParser);
    ~DataParser();

    DataParser& operator = (const DataParser& dataParser) {

        _fileManager = dataParser.getFileManager();
        _yaodStructure = dataParser.getYaODStructure();
        ENCODING_TYPE = dataParser.getEncodingType();
        _valueElements = dataParser.getValueElements();

        return *this;
    }

    YAOD_PTR getYaODStructure() const;
    FileManager getFileManager() const;
    unsigned short getEncodingType() const;
    std::map<std::string, std::string> getValueElements() const;

    void setYaODStructure(const YAOD_PTR yaodStructure);
    void setFileManager(const FileManager fileManager);
    void setEncodingType(const int encodingType);
    void setValueElements(const std::map<std::string, std::string> valueElements);
};

#endif // DATAPARSER_H
