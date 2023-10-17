#include "attribute.h"

Attribute::Attribute(): _name("") {}

Attribute::Attribute(const std::string name, const std::vector<std::string> parameters):
    _name(name), _parameters(parameters) {}

Attribute::Attribute(const Attribute &attribute):
    _name(attribute.getName()), _parameters(attribute.getParameters()) {}

Attribute::~Attribute() {}

void Attribute::setName(const std::string name) { _name = name; }

void Attribute::setParameters(const std::vector<std::string> parameters) { _parameters = parameters; }

std::string Attribute::getParameter(const int index) const { return _parameters[index]; }

std::string Attribute::getName() const { return _name; }

std::vector<std::string> Attribute::getParameters() const { return _parameters; }
