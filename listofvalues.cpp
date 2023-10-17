#include "listofvalues.h"

ListOfValues::ListOfValues():
    Object(), _name(""), _initializeValue(""), _step(""), _numberOfMembers("") {}

ListOfValues::ListOfValues(const std::string keyword,
                           const std::string name,
                           const std::vector<std::string> enumeration):
    Object(keyword), _name(name), _enumeration(enumeration), _initializeValue(""), _step(""), _numberOfMembers("") {}

ListOfValues::ListOfValues(const std::string keyword,
                           const std::string name,
                           const std::string initializeValue,
                           const std::string step,
                           const std::string numberOfMembers):
    Object(keyword), _name(name), _initializeValue(initializeValue), _step(step), _numberOfMembers(numberOfMembers) {}

ListOfValues::ListOfValues(const ListOfValues &listOfValues):
    Object(listOfValues.getKeyword()),
    _name(listOfValues.getName()),
    _enumeration(listOfValues.getEnumeration()),
    _initializeValue(listOfValues.getInitializeValue()),
    _step(listOfValues.getStep()),
    _numberOfMembers(listOfValues.getNumberOfMembers()) {}

ListOfValues::~ListOfValues() {}

std::string ListOfValues::getName() const { return _name; }

std::vector<std::string> ListOfValues::getParameters() const { return {}; }

std::vector<std::string> ListOfValues::getEnumeration() const { return _enumeration; }

std::string ListOfValues::getInitializeValue() const { return _initializeValue; }

std::string ListOfValues::getStep() const { return _step; }

std::string ListOfValues::getNumberOfMembers() const { return _numberOfMembers; }

void ListOfValues::setName(const std::string name) { _name = name; }

void ListOfValues::setInitializeValue(const std::string initializeValue) { _initializeValue = initializeValue; }

void ListOfValues::setStep(const std::string step) { _step = step; }

void ListOfValues::setNumberOfMembers(const std::string numberOfMembers) { _numberOfMembers = numberOfMembers; }

void ListOfValues::setEnumeration(const std::vector<std::string> enumeration) { _enumeration = enumeration; }
