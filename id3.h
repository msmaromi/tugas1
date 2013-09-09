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

using namespace std;

class ID3 {
public:
    ID3(Training);
    
    void classification(Training);
    void entropyTotal();
    
private:
    Tree  tr;
    
}

#endif /* defined(____id3__) */
