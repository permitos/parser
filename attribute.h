#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <iostream>
#include <memory>
#include <vector>

/*  Класс Attribute предназначен для хранения атрибутивной
 *  информации элементов (класс Element). */

class Attribute {

    std::string _name;
    std::vector<std::string> _parameters;

public:

    Attribute();
    explicit Attribute(const std::string _name, const std::vector<std::string> parameters);
    Attribute(const Attribute& attribute);
    virtual ~Attribute();

    Attribute& operator = (const Attribute& attribute) {

        _name = attribute.getName();
        _parameters = attribute.getParameters();

        return *this;
    }

    void setName(const std::string name);
    void setParameters(const std::vector<std::string> parameters);

    std::string getName() const;
    std::vector<std::string> getParameters() const;
    std::string getParameter(const int index) const;
};

typedef std::shared_ptr<Attribute> ATTRIBUTE_PTR;

#endif // ATTRIBUTE_H
