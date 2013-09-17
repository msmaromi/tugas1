//
//  id3.h
//  
//
//  Created by Muhammad S Maromi on 9/9/13.
//
//

#ifndef ____id3__
#define ____id3__

#include <iostream>
#include "training.h"
#include "tree.h"

using namespace std;

class ID3 {
public:
    ID3();
    ID3(Training);
    
    void classification(Training, Tree*);
    double entropy(Training);
    double informationGain(Training, string);
    double countYes(Training);
    double countNo(Training);
    
private:
    Tree *root;
    
};

#endif /* defined(____id3__) */
