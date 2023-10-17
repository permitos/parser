#ifndef ELEMENT_H
#define ELEMENT_H

#include "object.h"
#include <attribute.h>

/*  Класс Element используется для определения численного значения объеектов
 *  а в некоторых случаях, и для определения структуры инициализируемого экземпляра класса Shell.
 *  Данный класс является непосредственной частью связанного с ним Shell'a. */

class Element: virtual public Object {

    std::string _name;
    std::vector<std::string> _parameters;
    std::vector<ATTRIBUTE_PTR> _attributes;

public:

    Element();
    explicit Element(const std::string keyword,
                     const std::string name,
                     const std::vector<std::string> parameters,
                     const std::vector<ATTRIBUTE_PTR> attribute);
    Element(const Element& element);
    virtual ~Element();

    Element& operator = (const Element& element) {

        _name = element.getName();
        _parameters = element.getParameters();
        _attributes = element.getAttributes();

        return *this;
    }

    void setName(const std::string name);
    void setParameters(const std::vector<std::string> parameters);
    void setAttributes(const std::vector<ATTRIBUTE_PTR> attributes);

    std::string getName() const override;
    std::string getParameter(const int index) const;
    std::vector<std::string> getParameters() const override;
    std::vector<ATTRIBUTE_PTR> getAttributes() const;
};

typedef std::shared_ptr<Element> ELEMENT_PTR;

#endif // ELEMENT_H
