#ifndef YAODPARSER_H
#define YAODPARSER_H

#include "yaodstructure.h"
#include "attribute.h"
#include "parserstringddl.h"
#include "keywordsdescription.h"
#include "validatoryaod.h"
#include "filemanager.h"

class YaODParser {

    FileManager _fileManager;
    YAOD_PTR _yaodStructure;

    void analyzeStringDDL(std::string& stringDDL);
    void removeUnnecessaryInformation(std::string& str);
    void getFullStringDDL(std::string& str);
    void getFullStringMultilineComments(std::string& str);

    template <class object>
    std::shared_ptr<object> defineObject(const std::string& keyword, std::vector<std::string> keywords);

    ATTRIBUTE_PTR getAttribute(std::string& stringDDL);
    std::vector<ATTRIBUTE_PTR> getAttributes(std::string& stringDDL);

    void initializationObject(OBJECT_PTR object);
    void initializationIfCurrentIsShell(YAOD_PTR newYaODStructure);
    void initializationIfCurrentIsElement(YAOD_PTR newYaODStructure);
    void initializationIfCurrentIsListOfValue(YAOD_PTR newYaODStructure);
    void initializationIfCurrentIsSimple(YAOD_PTR newYaODStructure);
    void initializationIfCurrentIsNotInitialized(YAOD_PTR newYaODStructure);

    void upLevelStructure();
    void initializeElement(ELEMENT_PTR element, const std::string& keyword, std::string& stringDDL);
    void initializeShell(SHELL_PTR shell, const std::string& keyword, std::string& stringDDL);
    void initializeListOfValues(LISTOFVALUES_PTR listOfValues, const std::string& keyword, std::string& stringDDL);

public:

    void initializeYaOD();

    YaODParser();
    explicit YaODParser(const FileManager fileManager);
    YaODParser(const YaODParser &yaodParser);
    ~YaODParser();

    YaODParser& operator = (const YaODParser& yaodParser) {

        _fileManager = yaodParser.getFileManager();
        _yaodStructure = yaodParser.getYaODStructure();

        return *this;
    }

    YAOD_PTR getYaODStructure() const;
    FileManager getFileManager() const;

    void setYaODStructure(const YAOD_PTR yaodStructure);
    void setFileManager(const FileManager fileManager);
};

#endif // YAODPARSER_H
