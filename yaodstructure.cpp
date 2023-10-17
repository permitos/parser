#include "yaodstructure.h"

YaODStructure::YaODStructure() {}

YaODStructure::YaODStructure(const std::shared_ptr<Object> object):
    _object(object),
    _prevStructure(nullptr),
    _postStructure(nullptr),
    _shellStructure(nullptr),
    _insideStructure(nullptr) {}

YaODStructure::YaODStructure(const YaODStructure &yaodStructure):
    _object(yaodStructure.getObject()),
    _prevStructure(yaodStructure.getPrevStructure()),
    _postStructure(yaodStructure.getPostStructure()),
    _shellStructure(yaodStructure.getShellStructure()),
    _insideStructure(yaodStructure.getInsideStructure()) {}

YaODStructure::~YaODStructure() {}

void YaODStructure::setObject(const std::shared_ptr<Object> object) { _object = object; }

void YaODStructure::setPrevStructure(const std::shared_ptr<YaODStructure> prevStructure) { _prevStructure = prevStructure; }

void YaODStructure::setPostStructure(const std::shared_ptr<YaODStructure> postStructure) { _postStructure = postStructure; }

void YaODStructure::setShellStructure(const std::shared_ptr<YaODStructure> shellStructure) { _shellStructure = shellStructure; }

void YaODStructure::setInsideStructure(const std::shared_ptr<YaODStructure> insideStructure) { _insideStructure = insideStructure; }

std::shared_ptr<Object> YaODStructure::getObject() const { return _object; }

std::shared_ptr<YaODStructure> YaODStructure::getPrevStructure() const { return _prevStructure; }

std::shared_ptr<YaODStructure> YaODStructure::getPostStructure() const { return _postStructure; }

std::shared_ptr<YaODStructure> YaODStructure::getShellStructure() const { return _shellStructure; }

std::shared_ptr<YaODStructure> YaODStructure::getInsideStructure() const { return _insideStructure; }
