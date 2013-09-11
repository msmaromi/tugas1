//
//  robolearn.cpp
//  
//
//  Created by Muhammad S Maromi on 9/7/13.
//
//

#include "training.h"
#include "id3.h"
using namespace std;

int main() {
    string namaFile;
    cout << "masukkan file arff..." << endl;
    
    cin >> namaFile;
    Training tr1 = Training(namaFile);
    /*cout << tr1.getAttribute(4) << endl;
    cout << tr1.getTargetAttribute() << endl;
    cout << tr1.getAttributeValue(1, "humidity") << endl;*/
    
    ID3 learner;
    /*cout << learner.entropy(9,5) << endl;
    cout << learner.gainOutlook(9, 5, 2, 3, 4, 0, 3, 2) << endl;
    cout << learner.gainTemperature(9, 5, 2, 2, 4, 2, 3, 1) << endl;
    cout << learner.gainHumidity(9, 5, 3, 4, 6, 1) << endl;
    cout << learner.gainWind(9, 5, 3, 3, 6, 2) << endl;*/
    
    Tree result;
    result = learner.classification(tr1);    
    //result.printTree();
    cout << endl;
}