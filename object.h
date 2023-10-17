#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <memory>

/* Класс Object является обобщающей (корневой) сущностью для объектов,
 * представляющих собой носитель информации о собственных свойствах.*/

class Object {

    std::string _keyword;

public:

    virtual std::string getName() const = 0;
    virtual std::vector<std::string> getParameters() const = 0;

    Object();
    explicit Object(const std::string keyword);
    Object(const Object& object);
    virtual ~Object();

    Object& operator = (const Object& object) {

        _keyword = object.getKeyword();
        return *this;
    }

    void setKeyword(const std::string keyword);
    std::string getKeyword() const;
};

typedef std::shared_ptr<Object> OBJECT_PTR;

#endif // OBJECT_H
