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
    Training(const Training&);
    ~Training();
    
    string getAttribute(int);
    string getTargetAttribute();
    string getAttributeValue(int, string);
    int getNumberAttr();
    int getN();
    bool isAllYes();
    bool isAllNo();
    
    void deleteAttribute(string);
    void deleteInstance(int);
    
    double countNumYes();
    double countNumNo();
    
    double countSunYes();
    double countSunNo();
    double countOverYes();
    double countOverNo();
    double countRainYes();
    double countRainNo();
    
    double countHotYes();
    double countHotNo();
    double countMildYes();
    double countMildNo();
    double countCoolYes();
    double countCoolNo();
    
    double countHighYes();
    double countHighNo();
    double countNormalYes();
    double countNormalNo();
    
    double countStrongYes();
    double countStrongNo();
    double countWeakYes();
    double countWeakNo();
    
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
