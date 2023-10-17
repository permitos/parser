#include "element.h"

Element::Element(): Object(), _name("") {}

Element::Element(const std::string keyword,
                 const std::string name,
                 const std::vector<std::string> parameters,
                 const std::vector<std::shared_ptr<Attribute> > attribute):
    Object(keyword), _name(name), _parameters(parameters), _attributes(attribute) {}

Element::Element(const Element &element):
    Object(element), _name(element.getName()), _parameters(element.getParameters()), _attributes(element.getAttributes()) {}

Element::~Element() {}

void Element::setName(const std::string name) { _name = name; }

void Element::setAttributes(const std::vector<std::shared_ptr<Attribute> > attributes) { _attributes = attributes; }

void Element::setParameters(const std::vector<std::string> parameters) { _parameters = parameters; }

std::string Element::getName() const { return _name; }

std::string Element::getParameter(const int index) const { return _parameters[index]; }

std::vector<std::string> Element::getParameters() const { return _parameters; }

std::vector<std::shared_ptr<Attribute>> Element::getAttributes() const { return _attributes; }
