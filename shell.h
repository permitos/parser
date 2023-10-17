#ifndef SHELL_H
#define SHELL_H

#include "object.h"

/*  Класс Shell нужен для определения последовательности и количества хранимых
 *  экземпляров класса Element и других, включенных в него, Shell'ов. */

class Shell: virtual public Object {

    std::string _name;
    std::string _parameter;

public:

    Shell();
    explicit Shell(const std::string keyword, const std::string name, const std::string parameter);
    Shell(const Shell& shell);
    virtual ~Shell();

    Shell& operator = (const Shell& shell) {

        _name = shell.getName();
        _parameter = shell.getParameter();

        return *this;
    }

    std::string getName() const override;
    std::vector<std::string> getParameters() const override;
    std::string getParameter() const;

    void setName(const std::string name);
    void setParameter(const std::string parameter);
};

typedef std::shared_ptr<Shell> SHELL_PTR;

#endif // SHELL_H
