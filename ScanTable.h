#pragma once
#include "ArrayTable.h"

class ScanTable : public ArrayTable {
public:
    ScanTable(size_t size = 100) : ArrayTable(size) {}
    
    virtual DatValue* FindRecord(std::string key) override {
        size_t i = 0;
        for (i = 0; i < _dataCount; i++) {
            if (_records[i]->GetKey() == key) break;
        }
        _efecincy = i;
        if (i < _dataCount) { 
            _curPos = i;
            return _records[i]->GetValue();
        }
        return nullptr;
    }

    virtual void InsertRecord(std::string key, DatValue* value) override {
        if (IsFull()) return;
        _records[_dataCount] = new TabRecord(key, value);
        _dataCount++;
    }

    virtual void DelRecord(std::string key) override {
        if (IsEmpty()) return;
        if (FindRecord(key) == nullptr) return;
        
        delete _records[_curPos];

        for (size_t i = _curPos; i < _dataCount - 1; i++) {
            _records[i] = _records[i+1];
        }
        _records[_dataCount - 1] = nullptr;
        _dataCount--;
    }
};