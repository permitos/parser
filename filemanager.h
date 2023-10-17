#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include "exception.h"

/* Класс FileManager позволяет взаимодействовать
 * с дескрипторами файлов. */

class FileManager {

    std::string _fileName;
    std::ifstream _infile;

public:

    void openFile();
    bool isNotEndOfFile();

    bool getline(std::string &str);
    int getPeek();
    void readFile(char* str, const int size);

    FileManager();
    explicit FileManager(const std::string fileName);
    FileManager(const FileManager& fileManager);
    virtual ~FileManager();

    std::string  getFileName() const;
    void setFileName(const std::string fileName);

    FileManager& operator = (const FileManager& fileManager) {

        _fileName = fileManager.getFileName();
        return *this;
    }
};

#endif // FILEMANAGER_H
