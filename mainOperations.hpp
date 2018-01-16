//
//  mainOperations.hpp
//  Borsa
//
//  Created by Gil Maman on 8/22/16.
//  Copyright © 2016 Gil Maman. All rights reserved.
//

#ifndef mainOperations_hpp
#define mainOperations_hpp

#include <iostream>
#include <vector>
#include <algorithm>

#include "companyType.hpp"
#include "stockTypes.hpp"

#include "invalidOpException.hpp"
#include "invalidDateException.hpp"

class mainOperations {
private:
    vector<Company> companyList;
    vector<SecurityPaper*> stocksList;
    
public:
    //destrocter
    ~mainOperations() {
        for(int i=0; i<stocksList.size();i++)
            delete stocksList[i];
    }
    
    
     //-------------------------------STOCKS HANDLERS
    
    //create objects
    
    void createNewStock();
    void createNewStock(Company* userCompany);
    
    SecurityPaper* createDefaultPaper(Company* byCompany);

    //sell/delete
    void sellUserStock();
    void sellUserStock( SecurityPaper * currentPaper,Company* userCompany);

    void deleteStock(int index);
    
    //getters
    SecurityPaper* getSecurityPaper(const string name);
    int returnIndexForPaper(SecurityPaper* paper);
    int totalStocksValue();
    
    //print
    void printAllStocks() const;
    void printSpecificStock();
    void printSpecificStock(string name);
    
    
    //actions
    void changeStockRibit();
    void changeStockRibit(string name);
    
    void changeStockDate();
    void changeStockDate(string name);

    void addOneYear();
    

    
    //-------------------------------COMPANY HANDLERS
    
    //SPECIFIC COMPANY HANDLER
    
    //getters
    Company* returnCompanyWithName();
    Company* returnCompanyWithName(string name);
    
    //COMPANYS HANDLER
    
    //printers
    void printCompanys();
    void printCompanyData(Company data);
    void printSpecificCompany();
    
    //deletes specific company by name
    void deleteSpecificCompany();
    bool deleteSpecificCompany(string name);
    
    //ask for data and create new company
    void createNewCompany();
    
};


#endif /* mainOperations_hpp */
