//
//  companyTypes.hpp
//  Borsa
//
//  Created by Gil Maman on 8/30/16.
//  Copyright © 2016 Gil Maman. All rights reserved.
//

#ifndef companyType_hpp
#define companyType_hpp

#include <iostream>
#include <string>

using namespace std;

//company types
enum class companyType {
    PRIVATE,
    BODYGOVERMENT,
    COMPANYGOVERMENT
};


class Company {
private:
    string name;
    string inDepartment;
    companyType type;
    
    double shareValue;
    int numShares;
    
public:
    
    //constructers
    Company();
    
    Company(const string name, const string inDepartment, const companyType type,const double shareValue,const int numShares) :name(name),inDepartment(inDepartment),type(type),shareValue(shareValue),numShares(numShares) {}
    
    //getters
    
    inline const string returnName() {
        return this->name;
    }
    
    inline int getSharesLeft() {
        return this->numShares;
    };
    
    inline double getShareValue() {
        return this->shareValue;
    };
    
    inline const companyType getCompanyType() const {return this->type;}
    
    //overall changes:
    void changeCompanyName(const string newName) {
        this->name = newName;
    }
    
    void changeCompanyShareValue(const double shareValue) {
        this->shareValue = shareValue;
    }
    
    void changeCompanyNumShares(const int numShares) {
        this->numShares = numShares;
    }
    
    //operators
    
    void operator+=(Company* mergeCompany) {
        this->name = this->name + "&" + mergeCompany->returnName();
        this->inDepartment = this->inDepartment + "&" + mergeCompany->inDepartment;
        this->shareValue = (this->shareValue + mergeCompany->shareValue) / 2;
        this->numShares += mergeCompany->numShares;
    }
    
    //internal changes
    //Company& mergeCompanys(const Company& secondCompany);
    
    //print current company
    ostream& print(ostream& data) const;
    
};


#endif /* companyType_hpp */
