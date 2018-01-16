//
//  stockTypes.hpp
//  Borsa
//
//  Created by Gil Maman on 8/30/16.
//  Copyright © 2016 Gil Maman. All rights reserved.
//

#ifndef stockTypes_hpp
#define stockTypes_hpp

#include <iostream>
#include <string>

using namespace std;

//-------------------HELPER CLASSESS

//-------------------Date
class Date{
private:
    int day;
    int month;
    int year;
public:
    
    //constructers
    Date(const Date& userDate) {
        this->day = userDate.day;
        this->month = userDate.month;
        this->year = userDate.year;
    }
    
    Date(const int day, const int month, const int year) {
        this->day = day;
        this->month = month;
        this->year = year;
    };
    
    
    //default day
    Date() {
        this->day = 1;
        this->month = 1;
        this->year = 2000;
    }
    
    //setters
    void addYear(const int numYears) {
        this->year += numYears;
    }
    
    
    //print
    ostream& print(ostream& data) {
        data << this->day << "." << this->month << "." << this->year;
        return data;
    }
    
    //operators
    bool operator<(const Date& secondDate) {
        if(this->year < secondDate.year) {
            return true;
        }else if (this->year == secondDate.year) {
            if(this->month < secondDate.month) {
                return true;
            }else if (this->month == secondDate.month) {
                if(this->day < secondDate.day) {
                    return true;
                }
                
                return false;
            }
            return false;
        }
        return false;
    }
    
    void operator=(const Date& userDate) {
        this->day = userDate.day;
        this->month = userDate.month;
        this->year = userDate.year;
    }
    
};

//-----------------STOCKS



//secuirty paper top class

class Paper {
    
protected:
//properties
    string companyName; //goverment/company name
    int numOfPaper;
    int oneValue;

public:
//methods
    
    //buy
    virtual void buyNew(const int numOfShares,const int totalCompanyShares) =0;
    virtual void sell(const int numOfShares,const int totalCompanyShares) = 0;
    
    //print
    virtual ostream& print(ostream& currentData) const = 0;
    
    
    virtual ~Paper() {
        
    }
};

class SecurityPaper : public Paper{

public:
    
    //constructers
    SecurityPaper() {
        this->numOfPaper = 0;
        this->oneValue = 0;
    }
    
    SecurityPaper(const string name, const int oneValue) {
        this->companyName = name;
        this->numOfPaper = 0;
        this->oneValue = oneValue;
    }
    
    SecurityPaper(const int numOfPaper, const int oneValue) {
        this->numOfPaper = numOfPaper;
        this->oneValue = oneValue;
    }

    
    //actions
    virtual void buyNew(const int numOfShares,const int totalCompanyShares) {
        this->numOfPaper += numOfShares;
    }
    
    virtual void sell(const int numOfShares,const int totalCompanyShares) {
        this->numOfPaper -= numOfShares;
    }
    
    void changeOneValue(const int oneValue) {
        this->oneValue = oneValue;
    }
    
    
    //getters
    inline string returnName() const {return this->companyName;}
    
    inline int returnStockVal() const{
        return numOfPaper * oneValue;
    };
    
    inline int returnOneValue() const{
        return oneValue;
    };
    
    
    inline int returnNumPapers() const {
        return this->numOfPaper;
    };
    
    
    //print
    virtual ostream& print(ostream& currentData) const;
    
    
    //virtual functions
    virtual void addYears(int years) {}
    virtual void updateIntrest(const double newInterest){};
    virtual void updateDate(const Date newDate){};
    virtual void updateCanTrade(const bool canTrade){};
    
    //operators
    virtual SecurityPaper* operator+=(SecurityPaper* mergePaper) {
        this->companyName = this->companyName + "&" + mergePaper->returnName();
        this->oneValue = (this->oneValue + mergePaper->returnOneValue()) / 2;
        this->numOfPaper += mergePaper->returnNumPapers();
        
        return this;
    };
 
};


//share sub class
class Share : public virtual SecurityPaper {
protected:
    double percentCompany;
    
public:

     //constructers
    Share(const string companyName, const int oneValue) : SecurityPaper(companyName,oneValue) {
    };
    
    
    //actions
    
    virtual void buyNew(const int numOfShares,const int totalCompanyShares) {
        SecurityPaper::buyNew(numOfShares, totalCompanyShares);
        
        this->percentCompany = (static_cast<double>(this->numOfPaper) / static_cast<double>(totalCompanyShares))*100;
    }
    
    virtual void sell(const int numOfShares,const int totalCompanyShares) {
        SecurityPaper::sell(numOfShares,totalCompanyShares);
        
        this->percentCompany = (static_cast<double>(this->numOfPaper) / static_cast<double>(totalCompanyShares) )*100;
    }
    
    
    //getters
    
    inline const double getPercentCompany() const {
        return this->percentCompany;
    };
    
    //operators
    virtual Share* operator+=(Share* mergePaper) {
        SecurityPaper::operator+=(mergePaper);
        
        double totalShares = (static_cast<double>(100)/this->percentCompany)*static_cast<double>(this->returnOneValue());
        
        this->percentCompany = (static_cast<double>(this->numOfPaper + mergePaper->returnNumPapers()) / totalShares)*100;
        
        return this;
    };
    
    //print
    virtual ostream& print(ostream& currentData) const;
    
};



class BondPaper : public virtual SecurityPaper{
protected:
    double yearlyInterest;
    Date neadToPay;
    
public:
    //constructers
    BondPaper(const string companyName,const double yearlyInterest,const Date needToPay,const int oneValue) : neadToPay(needToPay),SecurityPaper(companyName,oneValue) {
        this->yearlyInterest = yearlyInterest;
    };
    
  
    //operators
    virtual BondPaper* operator+=(BondPaper* mergePaper) {
        SecurityPaper::operator+=(mergePaper);
        
        this->yearlyInterest = (this->yearlyInterest + mergePaper->yearlyInterest) / 2;
        
        //get earliest date
        if(mergePaper->neadToPay < this->neadToPay)
            this->neadToPay = mergePaper->neadToPay;
        
        return this;
    };
    
    //actions
    virtual void addYears(int years) {
        this->neadToPay.addYear(years);
    }
    
    void updateIntrest(const double newInterest) {
        this->yearlyInterest = newInterest;
    }
    
    virtual void updateDate(const Date newDate){
        this->neadToPay = newDate;
    };
    
    //print
    virtual ostream& print(ostream& currentData) const;
    
};



class GovermentShare : public BondPaper, public Share {
private:
    bool canTrade;
    
public:
    
    //constructers
    GovermentShare(const string companyName,const double yearlyInterest,const Date needToPay, const bool canTrade,const int oneValue) : BondPaper(companyName,yearlyInterest,needToPay,oneValue), Share(companyName,oneValue),SecurityPaper(companyName,oneValue){
        
        this->canTrade = canTrade;
    };
    
    
    //actions
    virtual void buyNew(const int numOfShares,const int totalCompanyShares) {
        SecurityPaper::buyNew(numOfShares, totalCompanyShares);
        
        this->percentCompany = (static_cast<double>(this->numOfPaper) / static_cast<double>(totalCompanyShares))*100;
    }
    
    virtual void sell(const int numOfShares,const int totalCompanyShares) {

        SecurityPaper::sell(numOfShares,totalCompanyShares);
        
        this->percentCompany = (static_cast<double>(this->numOfPaper) / static_cast<double>(totalCompanyShares))*100;
    }
    
    virtual void addYears(int years) {
        this->neadToPay.addYear(years);
    }
    
    virtual void updateCanTrade(const bool canTrade){
        this->canTrade = canTrade;
    }
    
    //operators
    virtual GovermentShare* operator+=(GovermentShare* mergePaper) {
        BondPaper::operator+=(mergePaper);
        
        int totalShares = (100/this->percentCompany)*this->returnOneValue();
        this->percentCompany = (static_cast<double>(this->numOfPaper + mergePaper->returnNumPapers()) / static_cast<double>(totalShares) )*100;
        
        
        //set can trade of company
        //atleast one false -> false else true
        if(this->canTrade == false || mergePaper->canTrade == false)
            this->canTrade = false;
        else
            this->canTrade = true;
        
        return this;
    };
    
   
    
    //print
    virtual ostream& print(ostream& currentData) const;

    
};


#endif /* stockTypes_hpp */
