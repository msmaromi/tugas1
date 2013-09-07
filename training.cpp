//
//  training.cpp
//  
//
//  Created by Muhammad S Maromi on 9/7/13.
//
//

#include "training.h"

Training::Training(string file) {
    extractFile(file);
}

Training::~Training() {
    
}

void Training::extractFile(string file) {
    bool startRecord = false;
    string strLine;
    ifstream readFile;
    readFile.open(file);
    if (readFile.open()) {
        while (!readFile.eof()) {
            readFile >> strLine;
            if (startRecord == true) {
                //record
                
            }
            if (readFile == "@DATA") {
                startRecord = true;
            }
        }
    }
}
