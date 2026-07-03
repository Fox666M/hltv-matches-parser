#pragma once
#include <iostream>
#include <string>

class DatValue
{
public:
    virtual std::ostream& print(std::ostream& os) const = 0;
    virtual DatValue* GetCopy() const = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const DatValue& tmp){
        return tmp.print(os);
    }
    
    virtual ~DatValue() {}
};