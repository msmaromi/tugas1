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
#include <map>
#include <string>

using namespace std;

class Training {
public:
    Training(string);
    ~Training();
    
private:
    map<string, string> * data;
    int N;
    void extractFile(string);
};

#endif /* defined(____training__) */
