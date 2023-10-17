#include "filemanager.h"

FileManager::FileManager(): _fileName("") {}

FileManager::FileManager(const std::string fileName):
    _fileName(fileName) {
}

FileManager::FileManager(const FileManager &fileManager):
    _fileName(fileManager.getFileName()) {
}

FileManager::~FileManager() { if(_infile.is_open()) _infile.close(); }

void FileManager::openFile() {

    _infile.open(_fileName, std::ios::binary);
    if(!_infile) throw FileOpenException(_fileName);
}

bool FileManager::isNotEndOfFile() { return _infile.peek() != EOF; }

bool FileManager::getline(std::string &str) { return static_cast<bool>(std::getline(_infile, str)); }
int FileManager::getPeek() { return _infile.peek(); }
void FileManager::readFile(char *str, const int size) { _infile.read(str, size); }

std::string FileManager::getFileName() const { return _fileName; }
void FileManager::setFileName(const std::string fileName) { _fileName = fileName; }
