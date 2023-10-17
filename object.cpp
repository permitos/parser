#include "object.h"

Object::Object(): _keyword("") {}

Object::Object(const std::string keyword): _keyword(keyword) {}

Object::Object(const Object &object): _keyword(object.getKeyword()) {}

Object::~Object() {}

void Object::setKeyword(const std::string keyword) { _keyword = keyword; }

std::string Object::getKeyword() const { return _keyword; }
