#ifndef VALIDATORYAOD_H
#define VALIDATORYAOD_H

#include <iostream>
#include <algorithm>
#include "element.h"
#include "shell.h"
#include "listofvalues.h"
#include "exception.h"
#include "keywordsdescription.h"

/* Класс ValidatorYaOD позволяет определить корректность
   описания объектов структуры и их взаимосвязи. */

class ValidatorYaOD {

    ValidatorYaOD() = default;
    virtual ~ValidatorYaOD() = default;

    static bool inGroupValidate(std::vector<std::string> keywords, const std::string& keyword);

public:

    static void validateElement(const Element& element);
    static void validateShell(const Shell& shell);
    static void validateListOfValues(const ListOfValues& listOfValues);
    static void validateAttribute(const Attribute& attribute);
};

#endif // VALIDATORYAOD_H
