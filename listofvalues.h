#ifndef LISTOFVALUES_H
#define LISTOFVALUES_H

#include "object.h"

/*  Класс ListOfValues является дополнительной сущностью для более корректного
 *  (структурированного) представления ЯОД описания.
 *  Данный класс взаимодействует напрямую с классом Element,
 *  при этом является непосредственной частью связанного с ним Shell'а. */

class ListOfValues: virtual public Object {

    std::string _name;
    std::vector<std::string> _enumeration;
    std::string _initializeValue;
    std::string _step;
    std::string _numberOfMembers;

public:

    ListOfValues();
    explicit ListOfValues(const std::string keyword, const std::string name,
                          const std::vector<std::string> enumeration);
    explicit ListOfValues(const std::string keyword, const std::string name,
                          const std::string initializeValue, const std::string step, const std::string numberOfMembers);
    ListOfValues(const ListOfValues& listOfValues);
    virtual ~ListOfValues();

    ListOfValues& operator = (const ListOfValues& listOfValues) {

        _name = listOfValues.getName();
        _enumeration = listOfValues.getEnumeration();
        _initializeValue = listOfValues.getInitializeValue();
        _step = listOfValues.getStep();
        _numberOfMembers = listOfValues.getNumberOfMembers();

        return *this;
    }

    void setName(const std::string name);
    void setEnumeration(const std::vector<std::string> enumeration);
    void setInitializeValue(const std::string initializeValue);
    void setStep(const std::string step);
    void setNumberOfMembers(const std::string numberOfMembers);

    std::string getName() const override;
    std::vector<std::string> getParameters() const override;
    std::vector<std::string> getEnumeration() const;
    std::string getInitializeValue() const;
    std::string getStep() const;
    std::string getNumberOfMembers() const;
};

typedef std::shared_ptr<ListOfValues> LISTOFVALUES_PTR;

#endif // LISTOFVALUES_H
