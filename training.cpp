//
//  training.cpp
//  
//
//  Created by Muhammad S Maromi on 9/7/13.
//
//

#include "training.h"

Training::Training() {
    
}

Training::Training(string file) {
    targetAttribute = "playtennis";
    extractAttribute();
    extractFile(file);
}

Training::Training(Training& tr) {
    targetAttribute = tr.targetAttribute;
    for (map<string, vector<string> >::const_iterator it=tr.attribute.begin(); it!=tr.attribute.end(); it++) {
        for (int i=0; i<it->second.size(); i++) {
            attribute[it->first].push_back(it->second[i]);
        }
    }
    for (int j=0; j<tr.getNumberData(); j++) {
        map<string, string> content;
        for (map<string, vector<string> >::const_iterator it=attribute.begin(); it!=attribute.end(); it++) {
                content[it->first] = (tr.data)[j][it->first];            
        }
        content[targetAttribute] = (tr.data)[j][targetAttribute];
        data.push_back(content);
    }
    for (int i=0; i<tr.getNumberAttribute(); i++) {
        attributeIndex.push_back(tr.getAttribute(i));
    }
}

Training::~Training() {
    
}

void Training::extractFile(string file) {
    //initiate data
    bool startRecord = false;
    string strLine;
    ifstream readFile;
    readFile.open(file.c_str());
    if (readFile.is_open()) {
        while (!readFile.eof()) {
            getline(readFile, strLine);
            if (startRecord == true) {
                //record
                char * token;
                char * cstr = new char[strLine.length()+1];
                strcpy(cstr, strLine.c_str());
                token = strtok(cstr, ",");
                int x = 0;
                map<string, string> content;
                while (token!=NULL) {
                    string tokenStr(token);
                    if (tokenStr!="yes" && tokenStr!="no") {
                        content[getAttribute(x)] = tokenStr;
                    } else {
                        content[targetAttribute] = tokenStr;
                    }
                    token = strtok(NULL, ",");
                    x++;
                }
                data.push_back(content);
            }
            if (strLine == "@DATA") {
                startRecord = true;
            }
        }
    }
}

void Training::extractAttribute() {
    attribute["outlook"].push_back("sunny");
    attribute["outlook"].push_back("overcast");
    attribute["outlook"].push_back("rain");
    attribute["temperature"].push_back("hot");
    attribute["temperature"].push_back("mild");
    attribute["temperature"].push_back("cool");
    attribute["humidity"].push_back("high");
    attribute["humidity"].push_back("normal");
    attribute["wind"].push_back("strong");
    attribute["wind"].push_back("weak");
    
    attributeIndex.push_back("outlook");
    attributeIndex.push_back("temperature");
    attributeIndex.push_back("humidity");
    attributeIndex.push_back("wind");
}

vector<string> Training::getAttributeValues(string attr){
    return attribute[attr];
}

string Training::getTargetAttribute() {
    return targetAttribute;
}

string Training::getDataValue(int i, string attr) {
    if (i<getNumberData()) {
        return data[i][attr];
    }
}

vector< map<string, string> > Training::getDataVector() {
    return data;
}

string Training::getAttribute(int index) {  
    return attributeIndex[index];
}

int Training::getNumberAttribute() {
    return attributeIndex.size();
}

int Training::getNumberData() {
    return data.size();
}

bool Training::isAllYes() {
    for (int i=0; i<getNumberData(); i++) {
        if (getDataValue(i, getTargetAttribute())=="no") {
            return false;
        }
    }
    return true;
}

bool Training::isAllNo() {
    for (int i=0; i<getNumberData(); i++) {
        if (getDataValue(i, getTargetAttribute())=="yes") {
            return false;
        }
    }
    return true;
}

void Training::deleteAttribute(string attr) {
    attribute.erase(attr);
    int found = 0;
    while (attributeIndex[found]!=attr) {
        found++;
    }
    attributeIndex.erase(attributeIndex.begin()+found);
}

void Training::deleteInstance(int index) {
    data.erase(data.begin()+index);
}






