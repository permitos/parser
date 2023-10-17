#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>

struct MessageException {
    MessageException() {}
    virtual ~MessageException() {}
    virtual std::string getErrorMessage() const = 0;
};

struct FileOpenException: public MessageException {
    std::string _fileName = "None";
    FileOpenException(const std::string fileName): _fileName(fileName) {}
    virtual ~FileOpenException() {}
    std::string getErrorMessage() const override { return "Unable to find file named: " + _fileName; }
};

struct YaODStringDDLException: public MessageException {
    std::string _stringDDL = "None";
    YaODStringDDLException(const std::string stringDDL): _stringDDL(stringDDL) {}
    virtual ~YaODStringDDLException() {}
    std::string getErrorMessage() const override { return "DDL error in this line: " + _stringDDL; }
};

struct YaODObjectException: public MessageException {
    std::string _messageError = "None";
    YaODObjectException(const std::string messageError): _messageError(messageError) {}
    virtual ~YaODObjectException() {}
    std::string getErrorMessage() const override { return _messageError; }
};

#endif // EXCEPTION_H
