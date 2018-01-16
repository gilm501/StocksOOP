//
//  mainOperations.cpp
//  Borsa
//
//  Created by Gil Maman on 8/22/16.
//  Copyright © 2016 Gil Maman. All rights reserved.
//

#include "mainOperations.hpp"

//----DATE handler

//DATE
//overide input
istream& operator>>(istream& data,Date& userDate) {
    
    //get data
    int day,month,year;
    
    cout << "Create New Date:" << endl;
    
    cout << "enter day(dd)" << endl;
    data >> day;
    
    cout << "enter month(mm)" << endl;
    data >> month;
    
    cout << "enter year(yyyy)" << endl;
    data >> year;
    
    //check if valid
    if(day < 1 || day > 31 || month < 1 || month > 12 || year > 2050 || year < 2016)
        throw invalidDateException("Invalid date");
    
    userDate = Date(day,month,year);
    
    return data;
}

//-------------------------------STOCKS HANDLERS

//OPERATORS
ostream& operator<<(ostream& data, SecurityPaper* currentStock) {
    return (*currentStock).print(data);
}


//CREATE OBJECTS

SecurityPaper* mainOperations::createDefaultPaper(Company* userCompany) {
    SecurityPaper* returnVal = nullptr;
    
    if(userCompany->getCompanyType() == companyType::PRIVATE) {
        Share* companyShare = new Share(userCompany->returnName(),userCompany->getShareValue());
        
        returnVal = companyShare;
        
        stocksList.push_back(companyShare);
    }
    if(userCompany->getCompanyType() == companyType::COMPANYGOVERMENT) {
        //default share
        BondPaper* newShare = new BondPaper(userCompany->returnName(),2,Date(1,1,2017),userCompany->getShareValue());
        
        returnVal = newShare;
        
        stocksList.push_back(newShare);
        
    }
    if(userCompany->getCompanyType() == companyType::BODYGOVERMENT) {
        //default GovermentShare
        GovermentShare* newShare = new GovermentShare(userCompany->returnName(),2,Date(1,1,2017),true,userCompany->getShareValue());
        
        returnVal = newShare;
        
        stocksList.push_back(newShare);
    }
    
    return returnVal;
}

void mainOperations::createNewStock(Company* userCompany) {
    //ask to create new
    if(userCompany == nullptr) {
        cout << "would you like to create one? (y/n)";
        char input;
        cin >> input;
        
        
        if(input == 'y') {
            try {
                this->createNewCompany();
                cout << "create new company succefully" << endl;
            }catch(exception& error) {
                cout << error.what();
            }
            
            cout << "Buy Stocks: "<<endl;
            userCompany = this->returnCompanyWithName();
        }else
            return;
    }
    
    int numSharesLeft = userCompany->getSharesLeft();
    
    //ask if he wants to buy new shares
    if(numSharesLeft != 0) {
        cout << "enter how many shares you would like to buy: (" << numSharesLeft << " left)";
        int buyShares = 0;
        
        cin >> buyShares;
        
        if(buyShares < 0 || buyShares > numSharesLeft) {
            throw invalidOpException("cannot buy more shares then possible");
        }
        
        //buy shares
        
        //update company object
        userCompany->changeCompanyNumShares(numSharesLeft-buyShares);
        
        SecurityPaper * currentPaper =this->getSecurityPaper(userCompany->returnName());
        //if exists
        
        //create new -> get stock class
        if(currentPaper == nullptr) {
            currentPaper = this->createDefaultPaper(userCompany);
        }
        
        currentPaper->buyNew(buyShares,userCompany->getSharesLeft() + buyShares + currentPaper->returnNumPapers());
        
        cout << "Stock bought succefully" << endl;
        
    } else { // no left shares
        throw invalidOpException("no shares for this company is left");
    }
}

void mainOperations::createNewStock() {
    cout << "Enter company that you would like to buy shares";
    Company* userCompany = this->returnCompanyWithName();
    
    this->createNewStock(userCompany);
    
}


//SELL DELETE OBJECTS

void mainOperations::deleteStock(int index) {
    this->stocksList.erase(this->stocksList.begin() + index);
}

void mainOperations::sellUserStock( SecurityPaper * currentPaper,Company* currentCompany) {
    //ask to create new
    if(currentPaper == nullptr) {
        throw( "You dont own stocks for this company");
    } else {
        int userShares = currentPaper->returnNumPapers();
        
        cout << "enter how many shares you would like to sell: (you have: " << userShares << ")";
        
        int sellShares = 0;
        cin >> sellShares;
        
        if(sellShares < 0 || sellShares > userShares) {
            throw invalidOpException("cannot sell more shares then you have");
        }
        
        //add to company
        currentCompany->changeCompanyNumShares(currentCompany->getSharesLeft() + sellShares);
        
        //sell shares
        
        //if selles all shares
        if (sellShares == userShares) {
            //remove from vector
            int i=this->returnIndexForPaper(currentPaper);
            
            //delete currentPaper;
            
            this->deleteStock(i);
            
        } else {
            currentPaper->sell(sellShares,currentCompany->getSharesLeft() - sellShares+ currentPaper->returnNumPapers());
        }
        
        
        cout << "Stock selled succefully" << endl;
        
    }
}

void mainOperations::sellUserStock() {
    cout << "Enter company that you would like to sell shares:"<<endl;
    
    string name = "";
    
    cin >> name;
    
    SecurityPaper * currentPaper =this->getSecurityPaper(name);
    Company* currentCompany = returnCompanyWithName(name);
    
    try {
        this->sellUserStock(currentPaper, currentCompany);
    }catch(exception& error) {
        cout << error.what() << endl;
    }
}


//GETTERS

SecurityPaper* mainOperations::getSecurityPaper(const string name) {
    for(int i=0; i < this->stocksList.size(); i++) {
        if((*this->stocksList[i]).returnName() == name) {
            return this->stocksList[i];
        }
    }
    
    return nullptr;
}

int mainOperations::returnIndexForPaper(SecurityPaper* paper) {
    vector<SecurityPaper*>::iterator foundPaper = find(stocksList.begin(), stocksList.end()-1, paper);
    
    if(foundPaper == stocksList.end())
        return 0;
    
    return static_cast<int>(distance(stocksList.begin(), foundPaper));
}

int mainOperations::totalStocksValue(){
    int counter = 0;
    
    for(int i =0; i < stocksList.size();i++) {
        counter += stocksList[i]->returnStockVal();
    }
    
    return counter;
}


//ACTIONS


void mainOperations::changeStockRibit() {
    string name = "";
    cout << "Enter company that you would like to view";
    cin >> name;
    
    try {
        this->changeStockRibit(name);
    }catch(exception& error) {
        cout << error.what() << endl;
    }
}

void mainOperations::changeStockRibit(string name) {
    SecurityPaper* currentPaper = this->getSecurityPaper(name);
    
    if(currentPaper == nullptr) {
        throw invalidOpException("stock does not exist");
    } else if (typeid(currentPaper) == typeid(Share)) {
        throw("Cannot change intrest for Regualr share");
    }
    
    int ribit = 0;
    cout << "Enter new intrest";
    cin >> ribit;
    
    currentPaper->updateIntrest(ribit);
}

void mainOperations::changeStockDate(string name) {
    
    SecurityPaper* currentPaper = this->getSecurityPaper(name);
    
    if(currentPaper == nullptr) {
        throw invalidOpException("stock does not exist");
    } else if (typeid(currentPaper) == typeid(Share)) {
        throw invalidOpException("Cannot change date for Regualr share");
    }
    
    try {
        Date newDate;
        cin >> newDate;
        
        currentPaper->updateDate(newDate);
        
    }catch(exception& errorInfo) {
        cout << errorInfo.what();
    }
}

void mainOperations::changeStockDate() {
    string name = "";
    cout << "Enter company that you would like to view";
    
    cin >> name;
    
    this->changeStockDate(name);
   
}

void mainOperations::addOneYear() {
    for(int i =0; i < stocksList.size();i++) {
        //add one year
        stocksList[i]->addYears(1);
    }
}

//PRINT

void mainOperations::printSpecificStock() {
    string name = "";
    cout << "Enter company that you would like to view";
    
    this->printSpecificStock(name);
    
}

void mainOperations::printSpecificStock(string name) {
    SecurityPaper* currentPaper = this->getSecurityPaper(name);
    
    if(currentPaper == nullptr)
        cout << "Paper doesent exist";
    else
        cout << currentPaper;
}


void mainOperations::printAllStocks() const{
    if(this->stocksList.size() == 0) {
        throw invalidOpException("No Stocks");
    }
    
    cout << "stocks:" << endl;
    for(int i=0; i < this->stocksList.size(); i++) {
        cout << i+1 << "." << this->stocksList[i] << endl;
    }
    
}

//-------------------------------COMPANY HANDLERS


// PRINT OPERATOR
ostream& operator<<(ostream& data, const Company& currentCompany) {
    return currentCompany.print(data);
}

//SPECIFIC COMPANY HANDLER
Company* mainOperations::returnCompanyWithName() {
    string name = "";
    cout << "enter company name: " << endl;
    cin >> name;
    
    Company * currentCompany = this->returnCompanyWithName(name);
    
   if(currentCompany == nullptr)
       cout << "company not found" << endl;
    
    return currentCompany;
}

Company* mainOperations::returnCompanyWithName(string name) {
    for(int i=0; i < this->companyList.size(); i++) {
        if(this->companyList[i].returnName() == name) {
            return &this->companyList[i];
        }
    }
    return nullptr;
}

//PRINTERS

void mainOperations::printCompanys() {
    if(this->companyList.size() == 0) {
        throw invalidOpException("No companies");
    }
    
    cout << "Companys: " << endl;
    for(int i=0; i < this->companyList.size(); i++) {
        cout << i+1 << "." << endl;
        cout << companyList[i];
    }
    
}

void mainOperations::printCompanyData(Company data) {
    cout << data;
}


void mainOperations::printSpecificCompany() {
    
    try {
        string name = "";
        cout << "enter company name to get data: " << endl;
        cin >> name;
        
        for(int i=0; i < this->companyList.size(); i++) {
            if(this->companyList[i].returnName() == name) {
                cout << companyList[i];
                
                return;
            }
        }
        
        throw invalidOpException("company not found");
    }catch(exception& err) {
        cout << err.what() << endl;
    }
}

//DELETE


void mainOperations::deleteSpecificCompany() {
    
    try {
        string name = "";
        cout << "enter company to delete: " << endl;
        cin >> name;
        
        if(!this->deleteSpecificCompany(name))
            throw invalidOpException("company not found");
        else
            cout << "company"<<name<<" deleted succefully" << endl;
        
    }catch(exception& err) {
        cout << err.what() << endl;
    }
}

bool mainOperations::deleteSpecificCompany(string name) {
    for(int i=0; i < this->companyList.size(); i++) {
        if(this->companyList[i].returnName() == name) {
            
            vector<Company>::iterator deleteComp = this->companyList.begin();
            deleteComp += i;
            
            this->companyList.erase(deleteComp);
            
            return true;
        }
    }
    
    return false;
}

//CREATE

void mainOperations::createNewCompany() {
    
    //ask for data
    string name = "";
    string inDepartment = "";
    int enteredType = 0;
    
    double shareValue = 0;
    int numShares = 0;
    
    cout << "creating new company:" << endl;
    cout << "enter company name : " << endl;
    cin >> name;
    
    //check if exists
    if(this->returnCompanyWithName(name) != nullptr) {
        throw invalidOpException("Cannot create company with existing name");
    }
    
    
    cout << "enter company department : " << endl;
    cin >> inDepartment;
    
    cout << "enter type(0= private, 1=body goverment, 2 = company goverment:) " << endl;
    cin >> enteredType;
    
    cout << "share value : " << endl;
    cin >> shareValue;
    
    cout << "num shares : " << endl;
    cin >> numShares;
    
    //create new company
    companyType type = static_cast<companyType>(enteredType);
    
    Company newCompany(name,inDepartment,type,shareValue,numShares);
    
    companyList.push_back(newCompany);
    
}


