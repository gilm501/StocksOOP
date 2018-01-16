//
//  mergeException.hpp
//  Borsa
//
//  Created by Gil Maman on 8/31/16.
//  Copyright © 2016 Gil Maman. All rights reserved.
//

#ifndef invalidOpException_hpp
#define invalidOpException_hpp

#include <iostream>
#include <exception>

using namespace std;

class invalidOpException : public exception {
private:
    const char* error;
    
public:
    invalidOpException(const char* error) : error(error){};
    
    virtual const char* what() const throw() {
        return error;
    }

};

#endif /* mergeException_hpp */
