//
//  invalidDateException.hpp
//  Borsa
//
//  Created by Gil Maman on 8/31/16.
//  Copyright © 2016 Gil Maman. All rights reserved.
//

#ifndef invalidDateException_hpp
#define invalidDateException_hpp

#include <iostream>
#include <exception>

using namespace std;

class invalidDateException : public exception {
private:
    const char* error;
    
public:
    invalidDateException(const char* error) : error(error){};
    
    virtual const char* what() const throw() {
        return error;
    }
    
};
#endif /* invalidDateException_hpp */
