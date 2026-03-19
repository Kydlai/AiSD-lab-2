#include "FileManager.h"

using namespace std;

FileManager::FileManager() {
    fileName = "b.txt";
}

void FileManager::openFile() {
    stream = fstream(fileName, ios::in | ios::out);
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
    string oldFileName = fileName;
    setFileName(name);
    stream.close();
    try {
        openFile();
    } catch (const exception& e) {
        fileName = oldFileName;
        openFile();
        throw;
    }
    return;
}

string FileManager::read() {
    if(lastWasWrite){
        //cout << "read_pointer = 0\n";
        stream.seekg(0);
        lastWasWrite = !lastWasWrite;
    }
    string data;
    if (!stream.eof())
        getline(stream, data);
    else 
        throw runtime_error("Конец файла");
    //cout << "Прочитана строка \"" << data << "\"\n";
    return data;
}

void FileManager::write(string data) {
    if(!lastWasWrite){
        //cout << "write_pointer = 0\n";
        stream.seekp(0);
        lastWasWrite = !lastWasWrite;
    }
    stream << data;
    //cout << "Записана строка \"" << data << "\"\n";
    return;
}

int FileManager::countLines() { // Осторожно: обнуляет указатель чтения
    if (count == -1){
        stream.seekg(0);
        int n = 0;
        string data;
        while(getline(stream, data))
            n++;
        reopenStream();
        count = n;
        return n;
    } else return count;
}

void FileManager::deleteLastLines(int n){
    vector<string> lines(count - n);
    for(int i = 0; i < count - n; ++i)
        lines[i] = read();
    clearFile();
    for(int i = 0; i < count - n; ++i)
        write(lines[i] + "\n");
}

void FileManager::clearFile() {
    stream.close();
    stream = fstream(fileName, ios::in | ios::out | ios::trunc);
    return;
}

