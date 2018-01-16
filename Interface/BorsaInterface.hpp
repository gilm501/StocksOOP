//
//  borsaInterface.hpp
//  Borsa
//
//  Created by Gil Maman on 9/10/16.
//  Copyright © 2016 Gil Maman. All rights reserved.
//

#ifndef borsaInterface_hpp
#define borsaInterface_hpp

#include <stdio.h>
#include "mainOperations.hpp"

#include "invalidOpException.hpp"
#include "invalidDateException.hpp"

class BorsaInterface {
    mainOperations appData;
    
    void startStocksMenu();
    void startSpecificStocksMenu();
    void startSpecificStocksMenu(Company* currentCompany,SecurityPaper* currentPaper);
    void startCompanyMenu();
    void startSpecificCompanyMenu(Company* currentCompany);
    
public:
    //decalre functions
    void startMenu();
};


#endif /* borsaInterface_hpp */
