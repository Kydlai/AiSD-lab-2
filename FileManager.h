#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class FileManager {
private:
    std::string fileName;
    int count = -1;
    bool lastWasWrite = false;

public:
    std::fstream stream;

    void openFile();
    FileManager();
    void setStream();
    void setFileName(std::string name);
    std::string getFileName();
    void reopenStream();
    void reopenStream(std::string name);
    std::string read();
    void write(std::string data);
    int countLines();
    void deleteLastLines(int n);
    void clearFile();
};