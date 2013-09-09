//
//  robolearn.cpp
//  
//
//  Created by Muhammad S Maromi on 9/7/13.
//
//

#include "training.h"
using namespace std;

int main() {
    string namaFile;
    cout << "masukkan file arff..." << endl;
    
    cin >> namaFile;
    Training tr1 = Training(namaFile);
    cout << tr1.getAttribute(4) << endl;
    cout << tr1.getTargetAttribute() << endl;
    cout << tr1.getAttributeValue(1, "humidity") << endl;
}