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
    //count N & numberAttr
    N = 0;
    numberAttr = 0;
    bool startCount = false;
    string strLine;
    ifstream readFile;
    readFile.open(file.c_str());
    if (readFile.is_open()) {
        while (!readFile.eof()) {
            getline(readFile, strLine);
            if (startCount==true) {
                N++;
            }
            if (strLine.find("@ATTRIBUTE")!=string::npos) {
                numberAttr++;
            }
            if (strLine=="@DATA") {
                startCount = true;
            }
        }
    }
    extractAttribute(file);
    extractFile(file);
}

Training& Training::operator=(const Training& tr) {
    targetAttribute = tr.targetAttribute;
    
    return *this;
}

Training::~Training() {
    
}

void Training::extractFile(string file) {
    //initiate data
    data = new map<string, string>[N];
    bool startRecord = false;
    string strLine;
    ifstream readFile;
    readFile.open(file.c_str());
    if (readFile.is_open()) {
        int i = 0;
        while (!readFile.eof()) {
            getline(readFile, strLine);
            if (startRecord == true) {
                //record
                char * token;
                char * cstr = new char[strLine.length()+1];
                strcpy(cstr, strLine.c_str());
                token = strtok(cstr, ",");
                int x = 0;
                while (token!=NULL) {
                    
                    data[i][attribute[x]] = token;
                    /*cout << token;
                    cout << attribute[x];
                    cout <<data[i][attribute[x]] << endl;*/
                   
                    token = strtok(NULL, ",");
                    x++;
                }
                i++;
            }
            if (strLine == "@DATA") {
                startRecord = true;
            }
        }
    }
}

void Training::extractAttribute(string file) {
    attribute = new string[numberAttr];
    string strLine;
    ifstream readFile;
    readFile.open(file.c_str());
    if (readFile.is_open()) {
        int i = 0;
        while (!readFile.eof()) {
            getline(readFile, strLine);
            if (strLine.find("@RELATION")!=string::npos) {
                targetAttribute = strLine.substr(10);
            } else if (strLine.find("@ATTRIBUTE")!=string::npos) {
                if (strLine.find("class")!=string::npos) {
                    attribute[i] = targetAttribute;
                } else {
                    attribute[i] = strLine.substr(11, strLine.length()-18);
                }
                i++;
            }
        }
    }
}

string Training::getAttribute(int i){
    if (i<=numberAttr) {
        return attribute[i-1];
    }
}

string Training::getTargetAttribute() {
    return targetAttribute;
}

string Training::getAttributeValue(int i, string attr) {
    if (i<=N) {
        return data[i-1][attr];
    }
}

bool Training::isAllYes() {
    for (int i=0; i<N; i++) {
        if (getAttributeValue(i+1, getTargetAttribute())) {
            <#statements#>
        }
    }
}
