#include "cavefile.h"
#include <fstream>


bool Cavefile::getDataFromFile(std::string filename, std::vector<std::vector<bool>>* data) {
    bool res = false;
    std::ifstream fin(filename);
    std::vector<std::vector<bool>> newdata;
    if (fin.is_open()) {
        int rows, cols;
        getSizeFromFile(&fin, &rows, &cols);
        if (rows > 0 && cols > 0) {
            res = true;
            try {
                std::string line;
                size_t bufSize_t;
                for (int i = 0; i < rows && res; i++) {
                    newdata.push_back(std::vector<bool>());
                    std::getline(fin, line);
                    for (int j = 0; j < cols && res; j++) {
                        newdata.at(i).push_back(std::stoi(line, &bufSize_t));
                        line.erase(0, bufSize_t);
                    }
                }
                data->swap(newdata);
            } catch (std::exception& e) {
                res = false;
            }
        }
        fin.close();
    }
    return res;
}



void Cavefile::setInFile(std::string filename, const std::vector<std::vector<bool>>& data) {
    std::ofstream fout(filename);
    fout << data.size() << " " << data.at(0).size() << std::endl;
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data.at(i).size(); j++) {
            fout << data.at(i).at(j) << " ";
        }
        fout << std::endl;
    }
    fout.close();
}

void Cavefile::getSizeFromFile(std::ifstream* fin, int* rows, int* cols) {
    std::string line;
    if (fin->is_open()) {
        try {
            std::getline(*fin, line);
            size_t bufSize_t;
            *cols = std::stoi(line, &bufSize_t);
            line.erase(0, bufSize_t);
            *rows = std::stoi(line, &bufSize_t);
        } catch (std::exception& e) {
            *rows = -1;
            *cols = -1;
        }
    }
}
