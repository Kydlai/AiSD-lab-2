#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <format>

class FileManager {
private:
    std::string fileName;

    void openFile();

public:
    std::fstream stream;

    void setStream();
    void setFileName(std::string name);
    std::string getFileName();
    void reopenStream();
    void reopenStream(std::string name);
    std::string read();
    void write(std::string data);
    
};