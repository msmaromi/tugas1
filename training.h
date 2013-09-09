//
//  training.h
//  
//
//  Created by Muhammad S Maromi on 9/7/13.
//
//

#ifndef ____training__
#define ____training__

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

class Training {
public:
    Training();
    Training(string);
    Training& operator=(const Training&);
    ~Training();
    
    string getAttribute(int);
    string getTargetAttribute();
    string getAttributeValue(int, string);
    bool isAllYes();
    bool isAllNo();
    
private:
    string * attribute;
    string targetAttribute;
    map<string, string> * data;
    int N; //jumlah training data
    int numberAttr;
    void extractFile(string);
    void extractAttribute(string);
};

#endif /* defined(____training__) */
