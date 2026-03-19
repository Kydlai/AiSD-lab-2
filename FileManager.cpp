#include "FileManager.h"

using namespace std;

FileManager::FileManager() {
    fileName = "b.txt";
    openFile();
}

void FileManager::openFile() {
    stream = fstream(fileName, std::ios::in | std::ios::out);
    if (!stream.is_open())
        throw runtime_error("Файл " + fileName + " отсутствует либо нет прав на его чтение");
    return;
}

void FileManager::setFileName(string name) {
    fileName = name;
    return;
}

string FileManager::getFileName() {
    return fileName;
}

void FileManager::reopenStream() {
    reopenStream(fileName);
    return;
}

void FileManager::reopenStream(string name) {
    setFileName(name);
    stream.close();
    openFile();
    return;
}

string FileManager::read() {
    stream.seekp(0);
    string data;
    if (!stream.eof())
        getline(stream, data);
    else 
        throw runtime_error("Конец файла");
    return data;
}

void FileManager::write(string data) {
    stream.seekp(0);
    stream << data;
    return;
}

