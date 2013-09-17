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
#include <vector>

using namespace std;

class Training {
public:
    Training();
    Training(string);
    Training(Training&);
    ~Training();
    
    vector<string> getAttributeValues(string);
    string getTargetAttribute();
    string getDataValue(int, string);
    vector< map<string, string> > getDataVector();
    
    string getAttribute(int);
    int getNumberAttribute();
    int getNumberData();
    bool isAllYes();
    bool isAllNo();
    
    void deleteAttribute(string);
    void deleteInstance(int);
    
    
private:
    map<string, vector<string> > attribute;
    vector<string> attributeIndex;
    string targetAttribute;
    vector< map<string, string> > data;   
    
    void extractFile(string);
    void extractAttribute();
};

#endif /* defined(____training__) */
