#include "mazefile.h"

#include <fstream>

bool MazeFile::getMazeDataFromFile(std::string fileName,
                                   std::vector<std::vector<std::pair<bool, bool> > > *data) {
    bool res = false;
    std::ifstream fin(fileName);
    std::string s;
    if (fin.is_open()) {
        std::string line;
        int rows = -1, cols = -1;
        std::getline(fin, line);
        size_t bufSize_t;
        rows = std::stoi(line, &bufSize_t);
        line.erase(0, bufSize_t);
        cols = std::stoi(line, &bufSize_t);
        if (rows > 0 && cols > 0) {
            res = true;
            try {
                int a;
                for (int i = 0; i < rows && res; i++) {
                    data->push_back(std::vector<std::pair<bool, bool> >());
                    std::getline(fin, line);
                    for (int j = 0; j < cols && res; j++) {
                        a = std::stoi(line, &bufSize_t);
                        line.erase(0, bufSize_t);
                        data->at(i).push_back(std::pair<bool, bool>(a, 0));
                    }
                }
                std::getline(fin, line);
                for (int i = 0; i < rows && res; i++) {
                    std::getline(fin, line);
                    for (int j = 0; j < cols && res; j++) {
                        a = std::stoi(line, &bufSize_t);
                        line.erase(0, bufSize_t);
                        data->at(i).at(j).second = a;
                    }
                }
            } catch (std::exception& e) {
                res = false;
            }
        }
        fin.close();
    }
    return res;
}



void MazeFile::setMazeInFile(std::string fileName,
                             const std::vector<std::vector<std::pair<bool, bool> > > &vectorForWrite) {
    std::ofstream fout(fileName);
    fout << vectorForWrite.size() << " " << vectorForWrite.at(0).size() << std::endl;
    for (size_t i = 0; i < vectorForWrite.size(); i++) {
        for (size_t j = 0; j < vectorForWrite.at(i).size(); j++) {
            fout << vectorForWrite.at(i).at(j).first << " ";
        }
        fout << std::endl;
    }
    fout << std::endl;
    for (size_t i = 0; i < vectorForWrite.size(); i++) {
        for (size_t j = 0; j < vectorForWrite.at(i).size(); j++) {
            fout << vectorForWrite.at(i).at(j).second << " ";
        }
        fout << std::endl;
    }
    fout.close();
}
