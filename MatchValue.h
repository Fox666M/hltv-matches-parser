#pragma once
#include "DatValue.h"
#include <string>
#include <iostream>

class MatchValue : public DatValue {
public:
    std::string date, team1, team2, score;

    MatchValue(std::string d, std::string t1, std::string t2, std::string s)
        : date(d), team1(t1), team2(t2), score(s) {}

    virtual DatValue* GetCopy() const override { 
        return new MatchValue(*this); 
    }

    virtual std::ostream& print(std::ostream& os) const override {
        return os << date << " " << team1 << " vs " << team2;
    }

};