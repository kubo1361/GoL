//
// Created by Eternal on 03/01/2021.
//

#ifndef SERVER_SERVERSTORAGE_H
#define SERVER_SERVERSTORAGE_H

#include <unordered_map>
#include <string.h>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;
using namespace std;

class ServerStorage {
private:
    string file = "patterns.txt";
    unordered_map<string, string> patterns;
public:
    ServerStorage();
    ~ServerStorage();

    string getPatternNames();
    string getPattern(string argName);
    void addPattern(string argName, string argPattern);
    void removePattern(string argName);
};


#endif //SERVER_SERVERSTORAGE_H
