#ifndef PRINTYAOD_H
#define PRINTYAOD_H

#include "yaodstructure.h"
#include "element.h"
#include "shell.h"
#include "listofvalues.h"

/* Класс PrintYaODConsole позволяет вывести ЯОД описание в консоль. */

class PrintYaodConsole {

    static void printElement(const Element& element);
    static void printShell(const Shell& shell);
    static void printListOfValues(const ListOfValues& listOfValues);
    static void printParameters(std::vector<std::string> parameters);

    static YAOD_PTR printIfElement(YAOD_PTR yaodStructure);
    static YAOD_PTR printIfShell(YAOD_PTR yaodStructure);
    static YAOD_PTR printIfListOfValues(YAOD_PTR yaodStructure);

    PrintYaodConsole() = default;
    virtual ~PrintYaodConsole() = default;

public:

    static YAOD_PTR update(YAOD_PTR yaodStructure);
    static void printYaODToConsole(YAOD_PTR yaodStructure);
};

#endif // PRINTYAOD_H
