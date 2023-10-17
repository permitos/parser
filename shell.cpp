#include "shell.h"

Shell::Shell(): Object(), _name(""), _parameter("") {}

Shell::Shell(const std::string keyword, const std::string name, const std::string parameter):
    Object(keyword), _name(name), _parameter(parameter) {}

Shell::Shell(const Shell &shell):
    Object(shell), _name(shell.getName()), _parameter(shell.getParameter()) {}

Shell::~Shell() {}

std::string Shell::getName() const { return _name; }

std::vector<std::string> Shell::getParameters() const { return {getParameter()}; }

std::string Shell::getParameter() const { return _parameter; }

void Shell::setName(const std::string name) { _name = name; }

void Shell::setParameter(const std::string parameter) { _parameter = parameter; }
