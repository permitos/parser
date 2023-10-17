#include "yaodparser.h"
#include "dataparser.h"
#include "printyaod.h"
#include <windows.h>

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {

        FileManager fileManagerYaOD("D:\\Projects\\temp\\REKACUTK.ddl");
        FileManager fileManagerData("D:\\Projects\\temp\\Ru01342.6");

        YaODParser yaodParser(fileManagerYaOD);
        yaodParser.initializeYaOD();

        YAOD_PTR yaodStructure = yaodParser.getYaODStructure();

        PrintYaodConsole::printYaODToConsole(yaodStructure);
        yaodStructure = PrintYaodConsole::update(yaodStructure);

        DataParser dataParser(fileManagerData, EncodingType::CP866, yaodStructure);
        dataParser.startProcessData();

    } catch (const FileOpenException& ex) {

        std::cout << ex.getErrorMessage() << std::endl;
        return 1;

    } catch (const YaODStringDDLException& ex) {

        std::cout << ex.getErrorMessage() << std::endl;
        return 1;

    } catch (const YaODObjectException& ex) {

        std::cout << ex.getErrorMessage() << std::endl;
        return 1;
    }

    std::cout << "\nFinish programm" << std::endl;

    return 0;
}
