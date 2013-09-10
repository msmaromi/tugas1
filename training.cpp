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

Training::Training(const Training& tr) {
    numberAttr = tr.numberAttr;
    N = tr.N;
    targetAttribute = tr.targetAttribute;
    attribute = new string[numberAttr];
    for (int i=0; i<numberAttr; i++) {
        attribute[i] = tr.attribute[i];
    }
    data = new map<string, string>[N];
    for (int j=0; j<N; j++) {
        data[j]["outlook"] = tr.data[j]["outlook"];
        data[j]["temperature"] = tr.data[j]["temperature"];
        data[j]["humidity"] = tr.data[j]["humidity"];
        data[j]["wind"] = tr.data[j]["wind"];
        data[j][targetAttribute] = tr.data[j][targetAttribute];
    }    
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

int Training::getNumberAttr() {
    return numberAttr;
}

int Training::getN() {
    return N;
}

bool Training::isAllYes() {
    for (int i=0; i<N; i++) {
        if (getAttributeValue(i+1, getTargetAttribute())=="no") {
            return false;
        }
    }
    return true;
}

bool Training::isAllNo() {
    for (int i=0; i<N; i++) {
        if (getAttributeValue(i+1, getTargetAttribute())=="yes") {
            return false;
        }
    }
    return true;
}

void Training::deleteAttribute(string attr) {
    int j=0;
    for (int i=0; i<numberAttr; i++) {
        if (attribute[i]!=attr) {
            attribute[j] = attribute[i];
            j++;
        }
    }
    numberAttr = numberAttr - 1;
}

void Training::deleteInstance(int index) {
    int j = 0;
    for (int i=0; i<getN(); i++) {
        if ((index-1)!=i) {
            data[j]["outlook"] = data[i]["outlook"];
            data[j]["temperature"] = data[i]["temperature"];
            data[j]["humidity"] = data[i]["humidity"];
            data[j]["wind"] = data[i]["wind"];
            data[j][targetAttribute] = data[i][targetAttribute];
            j++;
        }
    }
    N = N - 1;
}

double Training::countNumYes() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, getTargetAttribute())=="yes") {
            count++;
        }
    }
    return count;
}

double Training::countNumNo() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, getTargetAttribute())=="no") {
            count++;
        }
    }
    return count;
}

double Training::countSunYes() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "outlook")=="sunny") {
            if (getAttributeValue(i+1, getTargetAttribute())=="yes") {
                count++;
            }
        }
    }
}

double Training::countSunNo() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "outlook")=="sunny") {
            if (getAttributeValue(i+1, getTargetAttribute())=="no") {
                count++;
            }
        }
    }
}

double Training::countOverYes() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "outlook")=="overcast") {
            if (getAttributeValue(i+1, getTargetAttribute())=="yes") {
                count++;
            }
        }
    }
}

double Training::countOverNo() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "outlook")=="overcast") {
            if (getAttributeValue(i+1, getTargetAttribute())=="no") {
                count++;
            }
        }
    }
}

double Training::countRainYes() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "outlook")=="rain") {
            if (getAttributeValue(i+1, getTargetAttribute())=="yes") {
                count++;
            }
        }
    }
}

double Training::countRainNo() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "outlook")=="rain") {
            if (getAttributeValue(i+1, getTargetAttribute())=="no") {
                count++;
            }
        }
    }
}

double Training::countHotYes() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "temperature")=="hot") {
            if (getAttributeValue(i+1, getTargetAttribute())=="yes") {
                count++;
            }
        }
    }
}

double Training::countHotNo() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "temperature")=="hot") {
            if (getAttributeValue(i+1, getTargetAttribute())=="no") {
                count++;
            }
        }
    }
}

double Training::countMildYes() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "temperature")=="mild") {
            if (getAttributeValue(i+1, getTargetAttribute())=="yes") {
                count++;
            }
        }
    }
}

double Training::countMildNo() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "temperature")=="mild") {
            if (getAttributeValue(i+1, getTargetAttribute())=="no") {
                count++;
            }
        }
    }
}

double Training::countCoolYes() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "temperature")=="cool") {
            if (getAttributeValue(i+1, getTargetAttribute())=="yes") {
                count++;
            }
        }
    }
}

double Training::countCoolNo() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "temperature")=="cool") {
            if (getAttributeValue(i+1, getTargetAttribute())=="no") {
                count++;
            }
        }
    }
}

double Training::countHighYes() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "humidity")=="high") {
            if (getAttributeValue(i+1, getTargetAttribute())=="yes") {
                count++;
            }
        }
    }
}

double Training::countHighNo() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "humidity")=="high") {
            if (getAttributeValue(i+1, getTargetAttribute())=="no") {
                count++;
            }
        }
    }
}

double Training::countNormalYes() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "humidity")=="normal") {
            if (getAttributeValue(i+1, getTargetAttribute())=="yes") {
                count++;
            }
        }
    }
}

double Training::countNormalNo() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "humidity")=="normal") {
            if (getAttributeValue(i+1, getTargetAttribute())=="no") {
                count++;
            }
        }
    }
}

double Training::countStrongYes() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "wind")=="strong") {
            if (getAttributeValue(i+1, getTargetAttribute())=="yes") {
                count++;
            }
        }
    }
}

double Training::countStrongNo() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "wind")=="strong") {
            if (getAttributeValue(i+1, getTargetAttribute())=="no") {
                count++;
            }
        }
    }
}

double Training::countWeakYes() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "wind")=="weak") {
            if (getAttributeValue(i+1, getTargetAttribute())=="yes") {
                count++;
            }
        }
    }
}

double Training::countWeakNo() {
    double count = 0;
    for (int i=0; i<getN(); i++) {
        if (getAttributeValue(i+1, "wind")=="weak") {
            if (getAttributeValue(i+1, getTargetAttribute())=="no") {
                count++;
            }
        }
    }
}





