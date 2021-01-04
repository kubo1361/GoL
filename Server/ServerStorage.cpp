//
// Created by Eternal on 03/01/2021.
//

#include "ServerStorage.h"

ServerStorage::ServerStorage() {
    if(!fs::exists(this->file)) {
        ofstream(this->file);
    }

    ifstream readFile(this->file);
    string fileLine;
    string partsOfPattern[2];
    while (getline (readFile, fileLine)) {
        stringstream  splitLine(fileLine);
        string part;
        for (int i = 0; i < 2; ++i) {
            getline(splitLine,part,';');
            partsOfPattern[i] = part;
        }
        this->patterns.insert(pair<string, string>(partsOfPattern[0], partsOfPattern[1]));
    }
    readFile.close();
}

ServerStorage::~ServerStorage() {
    ofstream writeFile(this->file);

    for(auto kv : this->patterns) {
        writeFile << kv.first << ";" << kv.second << endl;
    }

    writeFile.close();
}

string ServerStorage::getPatternNames() {
    string names;
    if (this->patterns.size() == 0) {
        return "";
    } else {
        for (auto kv : this->patterns) {
            names += ";" + kv.first;
        }
        return names;
    }
}

string ServerStorage::getPattern(string argName) {
    return this->patterns.at(argName);
}

void ServerStorage::addPattern(string argName, string argPattern) {
    this->patterns.insert(pair<string, string>(argName, argPattern));
}

void ServerStorage::removePattern(string argName) {
    this->patterns.erase(argName);
}
