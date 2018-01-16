//
//  companyTypes.cpp
//  Borsa
//
//  Created by Gil Maman on 8/30/16.
//  Copyright © 2016 Gil Maman. All rights reserved.
//

#include "companyType.hpp"

//print current company
ostream& Company::print(ostream& data) const {
    data << "Name: " << this->name << endl;
    data << "inDepartment: " << this->inDepartment << endl;
    data << "shareValue: " << this->shareValue << endl;
    data << "numShares: " << this->numShares << endl;
    
    //decide on type
    string type = "private";
    if(this->type == companyType::BODYGOVERMENT)
        type = "body goverment";
    else if(this->type == companyType::COMPANYGOVERMENT)
        type = "company goverment";
    
    data << "company type: " << type << endl;
    
    return data;
}