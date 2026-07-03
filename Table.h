#pragma once
#include <iostream>
#include "DatValue.h"

class Table {
protected:
    size_t _dataCount;
    size_t _efecincy;
public:
    Table() : _dataCount(0), _efecincy(0) {}
    virtual ~Table() {}

    size_t GetDataCount() const { return _dataCount; }
    size_t GetEfecincy() const { return _efecincy; }
    bool IsEmpty() const { return _dataCount == 0; }

    virtual bool IsFull() const = 0;
    virtual DatValue* FindRecord(std::string key) = 0;
    virtual void InsertRecord(std::string key, DatValue* value) = 0;
    virtual void DelRecord(std::string key) = 0;

    virtual void Clear() = 0;
    virtual bool Reset() = 0;
    virtual bool IsTabEnd() = 0;
    virtual bool GoNext() = 0;

    virtual std::string GetKey() const = 0;
    virtual DatValue* GetValue() const = 0;

    friend std::ostream& operator<<(std::ostream& os, Table& T) {
        for (T.Reset(); !T.IsTabEnd(); T.GoNext()) {
            os << T.GetKey() << "   |   " << *(T.GetValue()) << std::endl;
        }
        return os;
    }

    friend class SortTable;
};