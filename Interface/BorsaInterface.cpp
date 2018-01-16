//
//  borsaInterface.cpp
//  Borsa
//
//  Created by Gil Maman on 9/10/16.
//  Copyright © 2016 Gil Maman. All rights reserved.
//

#include "BorsaInterface.hpp"


void BorsaInterface::startMenu() {
    //print menu
    cout << endl << "-----------------------";
    cout << endl<< "Enter number for operation:" << endl;
    cout << "1: Company menu" <<endl;
    cout << "2: shares menu" << endl;
    
    cout <<endl<< "-1: quit" << endl;
    cout <<"-----------------------" << endl;
    
    //get user selection
    int userSelection;
    cin >> userSelection;
    
    //go to currect menu
    switch(userSelection){
            //company menu
        case (1):
            startCompanyMenu();
            break;
            
            //shares menu
        case (2):
            startStocksMenu();
            break;
            //quit app
        case(-1):
            cout << "thanks for using our app" << endl;
            return;
            break;
        default:
            startMenu();
            break;
    }
}


//-----------------------STOCKS


//SPECIFIC STOCK handler

void BorsaInterface::startSpecificStocksMenu(Company* currentCompany,SecurityPaper* currentPaper) {
    int userStocks = (currentPaper == nullptr) ? 0 : currentPaper->returnNumPapers();
    
    //print menu
    cout << endl << "-----------------------";
    cout << endl << currentCompany->returnName() << " for operations(you have "<< userStocks <<" Stocks, "<< currentCompany->getSharesLeft() <<" Left):" << endl;
    cout << "1: Buy new מניות/אגרות חוב" <<endl;
    cout << "2: sell מניות / אגרות חוב" << endl;
    cout << "3: print stock" << endl;
   
    if(currentCompany->getCompanyType() == companyType::BODYGOVERMENT || currentCompany->getCompanyType() == companyType::COMPANYGOVERMENT) {
        cout << "4: change end date" << endl;
        cout << "5: change intrest" << endl;
    }
    
    if(currentCompany->getCompanyType() == companyType::BODYGOVERMENT)
        cout << "6: change can treade" << endl;
    
    
    cout <<endl<< "-1: back" << endl;
    cout << "-2: quit" << endl;
    cout << "-----------------------" << endl;
    
    //get user selection
    int userSelection;
    cin >> userSelection;
    
    //currect option
    switch(userSelection){
            //buy stock
        case (1):
            try {
                appData.createNewStock(currentCompany);
            }catch(exception& error) {
                cout << error.what() << endl;
            }
            //get new paper
            currentPaper = appData.getSecurityPaper(currentCompany->returnName());
            
            startSpecificStocksMenu(currentCompany, currentPaper);
            break;
            //sell stock
        case (2):
            try {
                appData.sellUserStock(currentPaper, currentCompany);
            }catch(exception& error) {
                cout << error.what() << endl;
            }
            
            currentPaper = appData.getSecurityPaper(currentCompany->returnName());
            
            if(currentPaper != nullptr)
                startSpecificStocksMenu(currentCompany, currentPaper);
            else
                startStocksMenu();
            break;
            
            //print specific data
        case(3):{
            appData.printSpecificStock(currentCompany->returnName());
            
            startSpecificStocksMenu(currentCompany, currentPaper);
        }break;
            //change specific stock date
        case(4):
            try {
                appData.changeStockDate(currentCompany->returnName());
            }catch(exception& error) {
                cout << error.what() << endl;
            }
            
            cout << "updated user date";
            
            startSpecificStocksMenu(currentCompany, currentPaper);
            break;
            //change intrest
        case(5):
            try {
                appData.changeStockRibit(currentCompany->returnName());
            }catch(exception& error) {
                cout << error.what() << endl;
            }
            
            cout << "updated new intrest";
            startSpecificStocksMenu(currentCompany, currentPaper);
            break;
            
            
        case(6):{
            char canTrade;
            bool canTradeBool;
            
            cout << "Can trade share (y/n)";
            
            cin >> canTrade;
            
            if(canTrade == 'y')
                canTradeBool = true;
            else
                canTradeBool = false;
            
            
            currentPaper->updateCanTrade(canTradeBool);
            
            cout << "can trade has changed succefully" << endl;
            
            startSpecificStocksMenu(currentCompany, currentPaper);
        }break;
            
            //go back
        case(-1):
        {
            startStocksMenu();
            break;
        }
            //quit app
        case(-2):
            cout << "thanks for using our app" << endl;
            return;
            break;
        default:
            startStocksMenu();
            break;
    }
    
}


//GENERAL STOCKS
void BorsaInterface::startStocksMenu() {
    //print menu
    cout << endl << "-----------------------";
    cout << endl << "Hello There, enter char for stocks operations:" << endl;
    cout << "1: specific company shares operations" << endl;
    cout << "2: add one year to all אגרות חוב" << endl;
    cout << "3: calculate value of all stocks in system" << endl;
    cout << "4: print all stocks" << endl;
    
    cout <<endl<< "-1: back" << endl;
    cout << "-2: quit" << endl;
    cout << "-----------------------" << endl;
    
    //get user selection
    int userSelection;
    cin >> userSelection;
    
    //currect option
    switch(userSelection){
            //specific stock operation
        case (1):{
            string companyName = "";
            cout << "enter company name:";
            
            cin >> companyName;
            
    
            Company* curentCompany = appData.returnCompanyWithName(companyName);
            SecurityPaper* currentPaper = appData.getSecurityPaper(companyName);
            
            if(curentCompany == nullptr) {
                cout << "Company not found" << endl;
     
                startStocksMenu();
            }
            else
                startSpecificStocksMenu(curentCompany,currentPaper);
            
        }break;
            //add one year to all
        case(2):
            appData.addOneYear();
            
            cout << "added one year to all איגרות חוב" << endl;
            
            startStocksMenu();
            break;
            //calculate all values
        case(3):
            
            cout << "total value of stocks: " << appData.totalStocksValue();
            
            startStocksMenu();
            break;
            //print all stocks
        case(4):{
            try {
                appData.printAllStocks();
            }catch(exception& error) {
                cout << error.what() << endl;
            }
            
            startStocksMenu();
        }break;
            //go back
        case(-1):
        {
            startMenu();
            break;
        }
            //quit app
        case(-2):
            cout << "thanks for using our app" << endl;
            return;
            break;
        default:
            startCompanyMenu();
            break;
    }
}

//----------------------- COMPANYS

//COMPANY APP USAGE
void BorsaInterface::startCompanyMenu() {
    //print menu
    cout << endl << "-----------------------";
    cout << endl << "Hello There, enter char for main company operations:" << endl;
    cout << "1: create new company" <<endl;
    cout << "2: delete existing company" << endl;
    cout << "3: print specific company" << endl;
    cout << "4: print all companys" << endl;
    cout << "5: specific company more operations" << endl;
    cout <<endl<< "-1: back" << endl;
    cout << "-2: quit" << endl;
    cout << "-----------------------" << endl;
    
    //get user selection
    int userSelection;
    cin >> userSelection;
    
    //currect option
    switch(userSelection){
            //create new menu
        case (1):
            try {
                appData.createNewCompany();
                cout << "create new company succefully" << endl;
            }catch(exception& error) {
                cout << error.what();
            }
            
            startCompanyMenu();
            break;
            
            //delete existing company
        case (2):

            appData.deleteSpecificCompany();
            startCompanyMenu();
            break;
            
            //print specific company
        case(3):
            appData.printSpecificCompany();
            startCompanyMenu();
            break;
            //print all companys
        case(4):
            try {
                appData.printCompanys();
                startCompanyMenu();
            }catch(exception& err) {
                cout << err.what() << endl;
            }
    
            break;
            //speicifc info
        case(5):{
            Company* currentCompany =appData.returnCompanyWithName();
            
            if(currentCompany != nullptr) //if found
                startSpecificCompanyMenu(currentCompany);
            else {
                cout << "would you like to create the company? (y/n)";
                
                char input;
                cin >> input;
                
                if(input == 'y')
                    appData.createNewCompany();
                
                startCompanyMenu();
            }
        }break;
            //go back
        case(-1):
        {
            startMenu();
            break;
        }
            //quit app
        case(-2):
            cout << "thanks for using our app" << endl;
            return;
            break;
        default:
            startCompanyMenu();
            break;
    }
}

//SPECIFIC COMPANY APP USAGE
void BorsaInterface::startSpecificCompanyMenu(Company* currentCompany) {
    //print menu
    cout << endl << "-----------------------";
    cout << endl << "enter number for "<< currentCompany->returnName() <<" operations:" << endl;
    cout << "1: change company name" <<endl;
    cout << "2: change company share value" << endl;
    cout << "3: change company number of shares" << endl;
    cout << "4: print company data" << endl;
    cout << "5: Merge Company" << endl;
    cout << endl<<"-1: back" << endl;
    cout << "-2: quit" << endl;
    cout << "-----------------------" << endl;
    
    //get user selection
    int userSelection;
    cin >> userSelection;
    
    //currect option
    switch(userSelection){
            //change name
        case(1): {
            string newName = "";
            cout << "Enter new name:(-1 to stop)" << endl;
            cin >> newName;
            
            if(newName != "-1") {
                currentCompany->changeCompanyName(newName);
                cout << "Succefully changed name" << endl;
            }
            
            
            startSpecificCompanyMenu(currentCompany);
        }break;
            //change share value
        case(2):{
            double newValue = 0;
            cout << "Enter new share value:(-1 to stop)" << endl;
            cin >> newValue;
            
            if(newValue != -1) {
                //change company share value
                currentCompany->changeCompanyShareValue(newValue);
                
                //change stocks value
                SecurityPaper* companyPaper = appData.getSecurityPaper(currentCompany->returnName());
                if(companyPaper != nullptr)
                    companyPaper->changeOneValue(newValue);
                
                
                cout << "Succefully changed share value" << endl;
            }
            
            startSpecificCompanyMenu(currentCompany);
        }break;
            //change company number of shares
        case(3):{
            int numOfShares = 0;
            cout << "Enter new num of shares:(-1 to stop)" << endl;
            cin >> numOfShares;
            
            try {
                if(numOfShares == -1) {
                    throw;
                }
                
                SecurityPaper* companyPaper = appData.getSecurityPaper(currentCompany->returnName());
                //check if possible
                if(companyPaper != nullptr && companyPaper->returnNumPapers() > numOfShares) {
                    throw  invalidOpException("cannot lower num of papers then bought");
                }
                
                currentCompany->changeCompanyShareValue(numOfShares);
                
                //change stocks percentage
                if(companyPaper != nullptr)
                    companyPaper->buyNew(0, numOfShares);
                
                
                cout << "Succefully changed number of shares" << endl;
            }catch(exception& error) {
                cout << error.what();
                
                startSpecificCompanyMenu(currentCompany);
            }catch(...) {
                startSpecificCompanyMenu(currentCompany);
            }
            
        }break;
            //print data
        case(4):{
            appData.printCompanyData(*currentCompany);
            
            startSpecificCompanyMenu(currentCompany);
        }break;
            //merge company
        case(5):{
            //get company
            string mergeWithCompany = "";
            
            cout << "Enter company to merge with:" <<endl;
            
            cin >> mergeWithCompany;
            
            
            try {
                Company * mergeCompany = appData.returnCompanyWithName(mergeWithCompany);
                
                //if company does not exist
                if(mergeCompany == nullptr)
                    throw invalidOpException("Company does not exist");
                
                if(mergeCompany->getCompanyType() != currentCompany->getCompanyType())
                    throw invalidOpException("Cannot merge companys with diffrent type");
                
                
                //change stocks
                SecurityPaper* firstPaper = appData.getSecurityPaper(currentCompany->returnName());
                SecurityPaper* secondPaper = appData.getSecurityPaper(mergeCompany->returnName());
                
                //create default if not created
                if (firstPaper == nullptr) {
                    firstPaper = appData.createDefaultPaper(currentCompany);
                }
                
                if (secondPaper == nullptr) {
                    secondPaper = appData.createDefaultPaper(mergeCompany);
                }
                
                //change company
                *currentCompany += mergeCompany;
                *firstPaper += secondPaper;
                
                //remove second company
                appData.deleteSpecificCompany(mergeCompany->returnName());
                
                
                //remove second paper
                int index = appData.returnIndexForPaper(secondPaper);
                appData.deleteStock(index);
                
            }catch(exception& errorInfo) {
                cout << errorInfo.what();
            }
            
            
            startSpecificCompanyMenu(currentCompany);
        }break;
            //back
        case(-1):
            startCompanyMenu();
            break;
            //quit app
        case(-2):
            cout << "thanks for using our app" << endl;
            return;
            break;
            
        default:
            startCompanyMenu();
            break;
    }
}