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

Tree ID3::classification(Training tr) {
    //create root tree
    Tree root;
    if (tr.isAllYes()) {
        //single root node label yes
        root.setData("yes");

    } else if (tr.isAllNo()) {
        //single root node label no
        root.setData("no");
    } else if (tr.getNumberAttr()==0) {
        int numYes = 0;
        int numNo = 0;
        for (int i=0; i<tr.getN(); i++) {
            if (tr.getAttributeValue(i+1, tr.getTargetAttribute())=="yes") {
                numYes++;
            } else if (tr.getAttributeValue(i+1, tr.getTargetAttribute())=="no") {
                numNo++;
            }
        }
        if (numYes>=numNo) {
            //label yes
            root.setData("yes");
        } else {
            //label no
            root.setData("no");
        }        
    } else {
        string bestAttr="";
        double gainBestAttr = 0;
        double gainConsiderAttr = 0;
        for (int i=0; i<tr.getNumberAttr(); i++) {
            string considerAttr = tr.getAttribute(i+1);
            
            double numYes = tr.countNumYes();
            double numNo = tr.countNumNo();
            
            double sunYes = tr.countSunYes();
            double sunNo = tr.countSunNo();
            double overYes = tr.countOverYes();
            double overNo = tr.countOverNo();
            double rainYes = tr.countRainYes();
            double rainNo = tr.countRainNo();
            
            double hotYes = tr.countHotYes();
            double hotNo = tr.countHotNo();
            double mildYes = tr.countMildYes();
            double mildNo = tr.countMildNo();
            double coolYes = tr.countCoolYes();
            double coolNo = tr.countCoolNo();
            
            double highYes = tr.countHighYes();
            double highNo = tr.countHighNo();
            double normalYes = tr.countNormalYes();
            double normalNo =  tr.countNormalNo();
            
            double strongYes = tr.countStrongYes();
            double strongNo = tr.countStrongNo();
            double weakYes = tr.countWeakYes();
            double weakNo = tr.countWeakNo();
            
            if (considerAttr=="outlook") {
                gainConsiderAttr = gainOutlook(numYes, numNo, sunYes, sunNo, overYes, overNo, rainYes, rainNo);
            } else if (considerAttr=="temperature") {
                gainConsiderAttr = gainTemperature(numYes, numNo, hotYes, hotNo, mildYes, mildNo, coolYes, coolNo);
            } else if (considerAttr=="humidity") {
                gainHumidity(numYes, numNo, highYes, highNo, normalYes, normalNo);
            } else if (considerAttr=="wind") {
                gainWind(numYes, numNo, strongYes, strongNo, weakYes, weakNo);
            }
            
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
        
        //root << bestAttr
        root.setData(bestAttr);
        cout << bestAttr << endl;
                
        if (bestAttr=="outlook") {
            //add branch sunny
            root.setLeftBranch("sunny");
            Training tr1 = tr;
            for (int i=0; i<tr1.getN(); i++) {
                if (tr1.getAttributeValue(i+1, "outlook")!="sunny") {
                    tr1.deleteInstance(i+1);
                }
            }
            tr1.deleteAttribute("outlook");
            if (tr1.getN()==0) {
                int labelYes = 0;
                int labelNo = 0;
                for (int i=0; i<tr1.getN(); i++) {
                    if (tr1.getAttributeValue(i+1, tr1.getTargetAttribute())=="yes") {
                        labelYes++;
                    } else if (tr1.getAttributeValue(i+1, tr1.getTargetAttribute())=="no") {
                        labelNo++;
                    }
                }
                if (labelYes>labelNo) {
                    //label yes
                    root.getLeft()->setData("yes");
                } else {
                    //label no
                    root.getLeft()->setData("no");
                }
            } else {
                root.setLeft(classification(tr1));
            }
            //add branch overcast
            root.setCenterBranch("overcast");
            Training tr2 = tr;
            for (int i=0; i<tr2.getN(); i++) {
                if (tr2.getAttributeValue(i+1, "outlook")!="overcast") {
                    tr2.deleteInstance(i+1);
                }
            }
            tr2.deleteAttribute("outlook");
            if (tr2.getN()==0) {
                int labelYes = 0;
                int labelNo = 0;
                for (int i=0; i<tr2.getN(); i++) {
                    if (tr2.getAttributeValue(i+1, tr2.getTargetAttribute())=="yes") {
                        labelYes++;
                    } else if (tr2.getAttributeValue(i+1, tr2.getTargetAttribute())=="no") {
                        labelNo++;
                    }
                }
                if (labelYes>labelNo) {
                    //label yes
                    root.getCenter()->setData("yes");
                } else {
                    //label no
                    root.getCenter()->setData("no");
                }
            } else {
                root.setCenter(classification(tr2));
            }
            //add branch rain
            root.setRightBranch("rain");
            Training tr3 = tr;
            for (int i=0; i<tr3.getN(); i++) {
                if (tr3.getAttributeValue(i+1, "outlook")!="rain") {
                    tr3.deleteInstance(i+1);
                }
            }
            tr3.deleteAttribute("outlook");
            if (tr3.getN()==0) {
                int labelYes = 0;
                int labelNo = 0;
                for (int i=0; i<tr3.getN(); i++) {
                    if (tr3.getAttributeValue(i+1, tr3.getTargetAttribute())=="yes") {
                        labelYes++;
                    } else if (tr3.getAttributeValue(i+1, tr3.getTargetAttribute())=="no") {
                        labelNo++;
                    }
                }
                if (labelYes>labelNo) {
                    //label yes
                    root.getRight()->setData("yes");
                } else {
                    //label no
                    root.getRight()->setData("no");
                }
            } else {
                root.setRight(classification(tr3));
            }
        } else if (bestAttr=="temperature") {
            //add branch hot
            root.setLeftBranch("hot");
            Training tr1 = tr;
            for (int i=0; i<tr1.getN(); i++) {
                if (tr1.getAttributeValue(i+1, "temperature")!="hot") {
                    tr1.deleteInstance(i+1);
                }
            }
            tr1.deleteAttribute("temperature");
            if (tr1.getN()==0) {
                int labelYes = 0;
                int labelNo = 0;
                for (int i=0; i<tr1.getN(); i++) {
                    if (tr1.getAttributeValue(i+1, tr1.getTargetAttribute())=="yes") {
                        labelYes++;
                    } else if (tr1.getAttributeValue(i+1, tr1.getTargetAttribute())=="no") {
                        labelNo++;
                    }
                }
                if (labelYes>labelNo) {
                    //label yes
                    root.getLeft()->setData("yes");
                } else {
                    //label no
                    root.getLeft()->setData("no");
                }
            } else {
                root.setLeft(classification(tr1));
            }
            
            //add branch mild
            root.setCenterBranch("mild");
            Training tr2 = tr;
            for (int i=0; i<tr2.getN(); i++) {
                if (tr2.getAttributeValue(i+1, "temperature")!="mild") {
                    tr2.deleteInstance(i+1);
                }
            }
            tr2.deleteAttribute("temperature");
            if (tr2.getN()==0) {
                int labelYes = 0;
                int labelNo = 0;
                for (int i=0; i<tr2.getN(); i++) {
                    if (tr2.getAttributeValue(i+1, tr2.getTargetAttribute())=="yes") {
                        labelYes++;
                    } else if (tr2.getAttributeValue(i+1, tr2.getTargetAttribute())=="no") {
                        labelNo++;
                    }
                }
                if (labelYes>labelNo) {
                    //label yes
                    root.getCenter()->setData("yes");
                } else {
                    //label no
                    root.getCenter()->setData("no");
                }
            } else {
                root.setCenter(classification(tr2));
            }
            
            //add branch cool
            root.setRightBranch("cool");
            Training tr3 = tr;
            for (int i=0; i<tr3.getN(); i++) {
                if (tr3.getAttributeValue(i+1, "temperature")!="cool") {
                    tr3.deleteInstance(i+1);
                }
            }
            tr3.deleteAttribute("temperature");
            if (tr3.getN()==0) {
                int labelYes = 0;
                int labelNo = 0;
                for (int i=0; i<tr3.getN(); i++) {
                    if (tr3.getAttributeValue(i+1, tr3.getTargetAttribute())=="yes") {
                        labelYes++;
                    } else if (tr3.getAttributeValue(i+1, tr3.getTargetAttribute())=="no") {
                        labelNo++;
                    }
                }
                if (labelYes>labelNo) {
                    //label yes
                    root.getRight()->setData("yes");
                } else {
                    //label no
                    root.getRight()->setData("no");
                }
            } else {
                root.setRight(classification(tr3));
            }
            
        } else if (bestAttr=="humidity") {
            //add branch high
            root.setLeftBranch("high");
            Training tr1 = tr;
            for (int i=0; i<tr1.getN(); i++) {
                if (tr1.getAttributeValue(i+1, "humidity")!="high") {
                    tr1.deleteInstance(i+1);
                }
            }
            tr1.deleteAttribute("humidity");
            if (tr1.getN()==0) {
                int labelYes = 0;
                int labelNo = 0;
                for (int i=0; i<tr1.getN(); i++) {
                    if (tr1.getAttributeValue(i+1, tr1.getTargetAttribute())=="yes") {
                        labelYes++;
                    } else if (tr1.getAttributeValue(i+1, tr1.getTargetAttribute())=="no") {
                        labelNo++;
                    }
                }
                if (labelYes>labelNo) {
                    //label yes
                    root.getLeft()->setData("yes");
                } else {
                    //label no
                    root.getLeft()->setData("no");
                }
            } else {
                root.setLeft(classification(tr1));
            }
            
            //add branch normal
            root.setRightBranch("normal");
            Training tr2 = tr;
            for (int i=0; i<tr2.getN(); i++) {
                if (tr2.getAttributeValue(i+1, "humidity")!="normal") {
                    tr2.deleteInstance(i+1);
                }
            }
            tr2.deleteAttribute("humidity");
            if (tr2.getN()==0) {
                int labelYes = 0;
                int labelNo = 0;
                for (int i=0; i<tr2.getN(); i++) {
                    if (tr2.getAttributeValue(i+1, tr2.getTargetAttribute())=="yes") {
                        labelYes++;
                    } else if (tr2.getAttributeValue(i+1, tr2.getTargetAttribute())=="no") {
                        labelNo++;
                    }
                }
                if (labelYes>labelNo) {
                    //label yes
                    root.getRight()->setData("yes");
                } else {
                    //label no
                    root.getRight()->setData("no");
                }
            } else {
                root.setRight(classification(tr2));
            }
            
        } else if (bestAttr=="wind") {
            //add branch strong
            root.setLeftBranch("strong");
            Training tr1 = tr;
            for (int i=0; i<tr1.getN(); i++) {
                if (tr1.getAttributeValue(i+1, "wind")!="strong") {
                    tr1.deleteInstance(i+1);
                }
            }
            tr1.deleteAttribute("wind");
            if (tr1.getN()==0) {
                int labelYes = 0;
                int labelNo = 0;
                for (int i=0; i<tr1.getN(); i++) {
                    if (tr1.getAttributeValue(i+1, tr1.getTargetAttribute())=="yes") {
                        labelYes++;
                    } else if (tr1.getAttributeValue(i+1, tr1.getTargetAttribute())=="no") {
                        labelNo++;
                    }
                }
                if (labelYes>labelNo) {
                    //label yes
                    root.getLeft()->setData("yes");
                } else {
                    //label no
                    root.getLeft()->setData("no");
                }
            } else {
                root.setLeft(classification(tr1));
            }
            
            //add branch weak
            root.setRightBranch("weak");
            Training tr2 = tr;
            for (int i=0; i<tr2.getN(); i++) {
                if (tr2.getAttributeValue(i+1, "wind")!="weak") {
                    tr2.deleteInstance(i+1);
                }
            }
            tr2.deleteAttribute("wind");
            if (tr2.getN()==0) {
                int labelYes = 0;
                int labelNo = 0;
                for (int i=0; i<tr2.getN(); i++) {
                    if (tr2.getAttributeValue(i+1, tr2.getTargetAttribute())=="yes") {
                        labelYes++;
                    } else if (tr2.getAttributeValue(i+1, tr2.getTargetAttribute())=="no") {
                        labelNo++;
                    }
                }
                if (labelYes>labelNo) {
                    //label yes
                    root.getRight()->setData("yes");
                } else {
                    //label no
                    root.getRight()->setData("no");
                }
            } else {
                root.setRight(classification(tr2));
            }
            
        }
    }
    return root;
}

double ID3::entropy(double numYes, double numNo) {
    double proportionYes = numYes/(numYes+numNo);
    double proportionNo = numNo/(numYes+numNo);
    if (proportionYes==0) {
        return - (proportionNo*log2(proportionNo));
    } else if (proportionNo==0) {
        return - (proportionYes*log2(proportionYes));
    } else if (proportionYes==0 && proportionNo==0) {
        return 0;
    } else {
        return (-(proportionYes*log2(proportionYes)) - (proportionNo*log2(proportionNo)));
    }
}

double ID3::gainOutlook(double numYes, double numNo, double sunYes, double sunNo, double overYes, double overNo, double rainYes, double rainNo) {
    double s = entropy(numYes, numNo);
    
    double proportionSun = (sunYes+sunNo)/(numYes+numNo);
    double proportionOver = (overYes+overNo)/(numYes+numNo);
    double proportionRain = (rainYes+rainNo)/(numYes+numNo);
    
    double proportionSunYes = sunYes/(sunYes+sunNo);
    double proportionSunNo = sunNo/(sunYes+sunNo);
    double proportionOverYes = overYes/(overYes+overNo);
    double proportionOverNo = overNo/(overYes+overNo);
    double proportionRainYes = rainYes/(rainYes+rainNo);
    double proportionRainNo = rainNo/(rainYes+rainNo);
    
    return (s - (proportionSun*entropy(proportionSunYes, proportionSunNo)) - (proportionOver*entropy(proportionOverYes, proportionOverNo)) - (proportionRain*entropy(proportionRainYes, proportionRainNo)));
}

double ID3::gainTemperature(double numYes, double numNo, double hotYes, double hotNo, double mildYes, double mildNo, double coolYes, double coolNo) {
    double s = entropy(numYes, numNo);
    
    double proportionHot = (hotYes+hotNo)/(numYes+numNo);
    double proportionMild = (mildYes+mildNo)/(numYes+numNo);
    double proportionCool = (coolYes+coolNo)/(numYes+numNo);
    
    double proportionHotYes = hotYes/(hotYes+hotNo);
    double proportionHotNo = hotNo/(hotYes+hotNo);
    double proportionMildYes = mildYes/(mildYes+mildNo);
    double proportionMildNo = mildNo/(mildYes+mildNo);
    double proportionCoolYes = coolYes/(coolYes+coolNo);
    double proportionCoolNo = coolNo/(coolYes+coolNo);
    
    return (s - (proportionHot*entropy(proportionHotYes, proportionHotNo)) - (proportionMild*entropy(proportionMildYes, proportionMildNo)) - (proportionCool*entropy(proportionCoolYes, proportionCoolNo)));
}

double ID3::gainHumidity(double numYes, double numNo, double highYes, double highNo, double normalYes, double normalNo) {
    double s = entropy(numYes, numNo);
    
    double proportionHigh = (highYes+highNo)/(numYes+numNo);
    double proportionNormal = (normalYes+normalNo)/(numYes+numNo);
    
    double proportionHighYes = highYes/(highYes+highNo);
    double proportionHighNo = highNo/(highYes+highNo);
    double proportionNormalYes = normalYes/(normalYes+normalNo);
    double proportionNormalNo = normalNo/(normalYes+normalNo);
    
    return (s - (proportionHigh*entropy(proportionHighYes, proportionHighNo)) - (proportionNormal*entropy(proportionNormalYes, proportionNormalNo)));
}

double ID3::gainWind(double numYes, double numNo, double strongYes, double strongNo, double weakYes, double weakNo) {
    double s = entropy(numYes, numNo);
    
    double proportionStrong = (strongYes+strongNo)/(numYes+numNo);
    double proportionWeak = (weakYes+weakNo)/(numYes+numNo);
    
    double proportionStrongYes = strongYes/(strongYes+strongNo);
    double proportionStrongNo = strongNo/(strongYes+strongNo);
    double proportionWeakYes = weakYes/(weakYes+weakNo);
    double proportionWeakNo = weakNo/(weakYes+weakNo);
    
    return (s - (proportionStrong*entropy(proportionStrongYes, proportionStrongNo)) - (proportionWeak*entropy(proportionWeakYes, proportionWeakNo)));
}




