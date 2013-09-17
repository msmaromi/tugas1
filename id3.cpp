//
//  id3.cpp
//  
//
//  Created by Muhammad S Maromi on 9/9/13.
//
//

#include "id3.h"
#include "tree.h"
#include <cmath>

ID3::ID3() {

}

ID3::ID3(Training) {
    
}

void ID3::classification(Training tr, Tree *root) {
    //create root tree
    if (tr.isAllYes()) {
        //single root node label yes
        root->setData("yes");

    } else if (tr.isAllNo()) {
        //single root node label no
        root->setData("no");
    } else if (tr.getNumberAttribute()==0) {
        int numYes = 0;
        int numNo = 0;
        for (int i=0; i<tr.getNumberData(); i++) {
            if (tr.getDataValue(i, tr.getTargetAttribute())=="yes") {
                numYes++;
            } else if (tr.getDataValue(i, tr.getTargetAttribute())=="no") {
                numNo++;
            }
        }
        if (numYes>=numNo) {
            //label yes
            root->setData("yes");
        } else {
            //label no
            root->setData("no");
        }        
    } else {
        string bestAttr="";
        double gainBestAttr = 0;
        double gainConsiderAttr = 0;
        for (int i=0; i<tr.getNumberAttribute(); i++) {
            string considerAttr = tr.getAttribute(i);
            gainConsiderAttr = informationGain(tr, considerAttr);            
            if (bestAttr=="") {
                bestAttr = considerAttr;
                gainBestAttr = gainConsiderAttr;
            } else {
                if (gainBestAttr<gainConsiderAttr) {
                    bestAttr = considerAttr;
                    gainBestAttr = gainConsiderAttr;
                }
            }
        }
        root->setData(bestAttr);
        vector<string> attributeValues = tr.getAttributeValues(bestAttr);
        for (int i=0; i<attributeValues.size(); i++) {
            //add branch
            root->addBranch(attributeValues[i]);
            Training *tr1 = new Training(tr);
            int j = 0;
            while (j<tr1->getNumberData()) {
                if (tr1->getDataValue(j, bestAttr)!=attributeValues[i]) {
                    tr1->deleteInstance(j);
                } else {
                    j++;
                }
            }
            tr1->deleteAttribute(bestAttr);           
            if (tr1->getNumberData()>0) {
                Tree *tree = new Tree();
                classification(*tr1, tree);
                root->addTree(tree);
            } else {
                int numYes = 0;
                int numNo = 0;
                for (int i=0; i<tr1->getNumberData(); i++) {
                    if (tr1->getDataValue(i, tr1->getTargetAttribute())=="yes") {
                        numYes++;
                    } else if (tr1->getDataValue(i, tr1->getTargetAttribute())=="no") {
                        numNo++;
                    }
                }
                if (numYes>=numNo) {
                    //label yes
                    Tree *tree = new Tree("yes");
                    root->addTree(tree);
                } else {
                    //label no
                    Tree *tree = new Tree("no");
                    root->addTree(tree);
                }
            }
        }        
    }    
}

double ID3::entropy(Training tr) {
    double proportionYes;
    double proportionNo;
    if (tr.getNumberData()>0) {
        proportionYes = countYes(tr)/tr.getNumberData();
        proportionNo = countNo(tr)/tr.getNumberData();
    } else {
        proportionYes = 0;
        proportionNo = 0;
    }
    if (proportionYes==0 && proportionNo>0) {
        return - (proportionNo*log2(proportionNo));
    } else if (proportionNo==0 && proportionYes>0) {
        return - (proportionYes*log2(proportionYes));
    } else if (proportionYes==0 && proportionNo==0) {
        return 0;
    } else {
        return (-(proportionYes*log2(proportionYes)) - (proportionNo*log2(proportionNo)));
    }
}

double ID3::informationGain(Training tr, string attr) {
    double s = entropy(tr);
    double result = s;
    vector<string> attributeValues = tr.getAttributeValues(attr);
    for (int i=0; i<attributeValues.size(); i++) {
        string attributeValue = attributeValues[i];
        double countAttributeValue = 0;        
        for (int j=0; j<tr.getNumberData(); j++) {           
            if (tr.getDataValue(j, attr)==attributeValue) {
                countAttributeValue++;               
            }
        }
        
        Training tr1 = tr;
        int j = 0;
        while (j<tr1.getNumberData()) {
            if (tr1.getDataValue(j, attr)!=attributeValue) {
                tr1.deleteInstance(j);
            } else {
                j++;
            }
        }
        double proportionAttribute = countAttributeValue/tr.getNumberData();
        result = result - (proportionAttribute*entropy(tr1));
    }
    return result;
}

double ID3::countYes(Training tr) {
    double count = 0;
    for (int i=0; i<tr.getNumberData(); i++) {
        if (tr.getDataValue(i, tr.getTargetAttribute())=="yes") {
            count++;
        }
    }
    return count;
}

double ID3::countNo(Training tr) {
    double count = 0;
    count = tr.getNumberData() - countYes(tr);
    return count;
}
