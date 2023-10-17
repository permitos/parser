#include "printyaod.h"

void PrintYaodConsole::printYaODToConsole(YAOD_PTR yaodStructure) {

    yaodStructure = update(yaodStructure);

    yaodStructure = yaodStructure->getInsideStructure();

    while(yaodStructure) {

        OBJECT_PTR object = yaodStructure->getObject();

        if(std::dynamic_pointer_cast<Element>(object))
            yaodStructure = printIfElement(yaodStructure);

        else if(std::dynamic_pointer_cast<Shell>(object))
            yaodStructure = printIfShell(yaodStructure);

        else if(std::dynamic_pointer_cast<ListOfValues>(object))
            yaodStructure = printIfListOfValues(yaodStructure);
    }
}

YAOD_PTR PrintYaodConsole::update(YAOD_PTR yaodStructure) {

    while(true) {

        if(yaodStructure->getShellStructure())
            yaodStructure = yaodStructure->getShellStructure();
        else
            break;
    }

    return yaodStructure;
}

YAOD_PTR PrintYaodConsole::printIfElement(YAOD_PTR yaodStructure) {

    printElement(*(std::dynamic_pointer_cast<Element>(yaodStructure->getObject())));

    if(yaodStructure->getPostStructure())
        yaodStructure = yaodStructure->getPostStructure();

    else {

        yaodStructure = yaodStructure->getShellStructure();

        while(!yaodStructure->getPostStructure()) {

            if(!yaodStructure->getShellStructure())
                return nullptr;

            yaodStructure = yaodStructure->getShellStructure();
        }

        yaodStructure = yaodStructure->getPostStructure();
    }

    return yaodStructure;
}

YAOD_PTR PrintYaodConsole::printIfShell(YAOD_PTR yaodStructure) {

    printShell(*(std::dynamic_pointer_cast<Shell>(yaodStructure->getObject())));
    return yaodStructure->getInsideStructure();
}

YAOD_PTR PrintYaodConsole::printIfListOfValues(YAOD_PTR yaodStructure) {

    printListOfValues(*(std::dynamic_pointer_cast<ListOfValues>(yaodStructure->getObject())));
    return yaodStructure->getPostStructure();
}

void PrintYaodConsole::printElement(const Element& element) {

    std::cout << element.getKeyword() << " " << element.getName() << " ";

    if(!element.getParameters().empty())
        printParameters(element.getParameters());

    if(!element.getAttributes().empty()) {

        for(ATTRIBUTE_PTR attribute: element.getAttributes()) {

            std::cout << attribute->getName() << " ";

            if(!attribute->getParameters().empty())
                printParameters(attribute->getParameters());
        }
    }

    std::cout << ";" << std::endl;
}

void PrintYaodConsole::printParameters(std::vector<std::string> parameters) {

    std::cout << " ( ";

    for(std::string parameter: parameters)
        std::cout << parameter << " ";

    std::cout << ") ";
}

void PrintYaodConsole::printShell(const Shell& shell) {

    std::cout << shell.getKeyword() << " ";

    if(!shell.getName().empty())
        std::cout << " ( " << shell.getParameter() << " ) ";

    std::cout << shell.getName() << ";" << std::endl;
}

void PrintYaodConsole::printListOfValues(const ListOfValues& listOfValues) {

    std::cout << listOfValues.getKeyword() << " " << listOfValues.getName() << " ";

    if(!listOfValues.getEnumeration().empty()) {

        for(std::string element: listOfValues.getEnumeration())
            std::cout << element << " ";

        std::cout << ";" << std::endl;
    }

    else {

        std::cout << listOfValues.getInitializeValue() <<
                     " ( " << listOfValues.getStep() << " ) " <<
                     listOfValues.getNumberOfMembers() << ";" << std::endl;
    }
}




