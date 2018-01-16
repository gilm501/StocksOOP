//
//  stockTypes.cpp
//  Borsa
//
//  Created by Gil Maman on 8/30/16.
//  Copyright © 2016 Gil Maman. All rights reserved.
//

#include "stockTypes.hpp"

//SECURITY PAPER
ostream& operator<<(ostream& data, Date userDate) {
    return userDate.print(data);
}

ostream& SecurityPaper::print(ostream& currentData) const {
    currentData << "Company Name:" << this->companyName << endl;
    currentData << "num Paper: " << this->numOfPaper << endl;
    currentData <<"one value: " << this->oneValue << endl;
    
    return currentData;
}


//BOND PAPER
ostream& BondPaper::print(ostream& currentData) const {
    
    ostream& newData = SecurityPaper::print(currentData);
    newData << "yearlyInterest : " << this->yearlyInterest << endl;
    newData << "need To Pay in date : " << this->neadToPay;
    
    return newData;
}


//SHARE PAPER
ostream& Share::print(ostream& currentData) const {
    
    ostream& newData = SecurityPaper::print(currentData);
    newData << "Percent Company : " << this->percentCompany << endl;
    
    return newData;
}

//GOVERMENT SHARE

ostream& GovermentShare::print(ostream& currentData) const {
    
    string canTrade = (this->canTrade) ? " true" : "false";
    
    ostream& newData = BondPaper::print(currentData);
    newData << endl << "Can trade: " << canTrade << endl;
    newData << "Percent Company : " << this->percentCompany << endl;
    
    return newData;
}