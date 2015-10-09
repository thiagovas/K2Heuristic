#ifndef _cExceptions_hpp
#define _cExceptions_hpp

#include <exception>

class nullGraphException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "The Graph received is null.";
    }
} nullGraphException;

#endif
