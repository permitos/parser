#ifndef YAODSTRUCTURE_H
#define YAODSTRUCTURE_H

#include "object.h"
#include <memory>

class YaODStructure {

    std::shared_ptr<Object> _object;

    std::shared_ptr<YaODStructure> _prevStructure;
    std::shared_ptr<YaODStructure> _postStructure;
    std::shared_ptr<YaODStructure> _shellStructure;
    std::shared_ptr<YaODStructure> _insideStructure;

public:

    YaODStructure();
    explicit YaODStructure(const std::shared_ptr<Object> object);
    YaODStructure(const YaODStructure& yaodStructure);
    virtual ~YaODStructure();

    std::shared_ptr<Object> getObject() const;
    void setObject(const std::shared_ptr<Object> object);

    std::shared_ptr<YaODStructure> getPrevStructure() const;
    std::shared_ptr<YaODStructure> getPostStructure() const;
    std::shared_ptr<YaODStructure> getShellStructure() const;
    std::shared_ptr<YaODStructure> getInsideStructure() const;

    void setPrevStructure(const std::shared_ptr<YaODStructure> prevStructure);
    void setPostStructure(const std::shared_ptr<YaODStructure> postStructure);
    void setShellStructure(const std::shared_ptr<YaODStructure> shellStructure);
    void setInsideStructure(const std::shared_ptr<YaODStructure> insideStructure);

    // use iterator traits

    YaODStructure& operator = (const YaODStructure& yaodStructure) {

        _object = yaodStructure.getObject();
        _prevStructure = yaodStructure.getPrevStructure();
        _postStructure = yaodStructure.getPostStructure();
        _shellStructure = yaodStructure.getShellStructure();
        _insideStructure = yaodStructure.getInsideStructure();

        return *this;
    }

    YaODStructure& operator++() {

        *this = *(this->getPostStructure());
        return *this;
    }

    YaODStructure operator++(int) {

        YaODStructure oldYaOD = *this;
        operator++();
        return oldYaOD;
    }

    YaODStructure& operator--() {

        *this = *(this->getPrevStructure());
        return *this;
    }

    YaODStructure operator--(int) {

        YaODStructure oldYaOD = *this;
        operator--();
        return oldYaOD;
    }
};

typedef std::shared_ptr<YaODStructure> YAOD_PTR;

#endif // YAODSTRUCTURE_H
