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

/*double trainingAccuracy(ID3 id3, Training tr) {
    Tree t = id3.classification(tr);
    double numberAccurate = 0;
    for (int i=0; i<tr.getN(); i++) {        
        //tr.getAttributeValue(i+1, tr.getAttribute(t.getData()));
    }
}*/


int main() {
    string namaFile;
    cout << "masukkan file arff..." << endl;
    
    cin >> namaFile;
    Training tr(namaFile);
    
    ID3 learner;
    /*Training tr1 = tr;
    int j = 0;
    while (j<tr1.getNumberData()) {
        if (tr1.getDataValue(j, "outlook")!="rain") {
            tr1.deleteInstance(j);
        } else {
            j++;
        }
    }
    tr1.deleteAttribute("outlook");

    cout << learner.informationGain(tr1, "wind") << endl;
    cout << learner.informationGain(tr1, "temperature") << endl;
    cout << learner.informationGain(tr1, "humidity") << endl;
    
    /*Training tr2 = tr1;
    j = 0;
    while (j<tr2.getNumberData()) {
        if (tr2.getDataValue(j, "humidity")!="high") {
            tr2.deleteInstance(j);
        } else {
            j++;
        }
    }
    tr2.deleteAttribute("humidity");
    
    Tree t1 = learner.classification(tr2);    
    cout << t1.getData() << endl;
    //cout << t.getCenterBranch() << endl;
    //cout << t.getLeft()->getData() << endl;*/
    
    Tree *t = new Tree();
    learner.classification(tr, t);
    cout << "================" << endl; 
    //cout << t.getRightBranch() << endl;
    /*cout << t->getLeft()->getCenter()->getData() << endl;
    cout << t->getCenter()->getData() << endl;
    cout << t->getRight()->getData() << endl;
    //cout << t.getCenterBranch() << endl; */
    t->printTree();
    
    /*Tree tree1;
    Tree *t1 = new Tree("no");
        tree1.addTree(*t1);
    t1 = new Tree("yes");
    tree1.addTree(*t1);
    Tree t3("yes");
    tree1.setData("root");    
    cout << tree1.getData() << endl;
    cout << tree1.getLeft()->getData() << endl;
    cout << tree1.getCenter()->getData() << endl;
    
    /*Tree tree2("superroot");
    tree2.addTree(tree1);
    cout << tree2.getData() << endl;
    cout << tree2.getLeft()->getData() << endl;
    cout << tree2.getLeft()->getCenter()->getData() << endl;
    
    /*tree1.addBranch("cabang1");
    tree1.addBranch("cabang2");
    cout << tree1.getLeftBranch() << endl;
    cout << tree1.getCenterBranch() << endl;*/
}



