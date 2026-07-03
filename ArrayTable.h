#pragma once
#include "Table.h"
#include "TabRecord.h"

using Record = TabRecord*;
enum Position { first, current, last };

class ArrayTable : public Table {
protected:  
    Record* _records;
    size_t _tabSize;
    size_t _curPos;
public: 
    ArrayTable(size_t size = 100) {
        _records = new Record[size];
        _tabSize = size;
        _curPos = 0;
        _dataCount = 0;
        for (size_t i = 0; i < _tabSize; i++) {
            _records[i] = nullptr;
        }
    }

    ~ArrayTable() {
        for (size_t i = 0; i < _dataCount; i++) {
            delete _records[i];
        }
        delete[] _records;
    }

    virtual bool IsFull() const override { return _dataCount >= _tabSize; }
    size_t GetTabSize() const { return _tabSize; }

    virtual std::string GetKey(Position p) const {
        if (IsEmpty()) return "";
        switch (p) {
            case Position::first: return _records[0]->GetKey();
            case Position::last: return _records[_dataCount - 1]->GetKey();
            default: return _records[_curPos]->GetKey();
        }
    }

    virtual void Clear() override {
        for (size_t i = 0; i < _dataCount; i++) {
            delete _records[i];
            _records[i] = nullptr;
        }
        _dataCount = 0;
        _curPos = 0;
    }

    virtual DatValue* GetValue(Position p) const {
        if (IsEmpty()) return nullptr;
        switch (p) {
            case Position::first: return _records[0]->GetValue();
            case Position::last: return _records[_dataCount - 1]->GetValue();
            default: return _records[_curPos]->GetValue();
        }
    }

    virtual std::string GetKey() const override { return GetKey(Position::current); }
    virtual DatValue* GetValue() const override { return GetValue(Position::current); }

    virtual bool Reset() override {
        _curPos = 0;
        return IsTabEnd();
    }

    virtual bool IsTabEnd() override { return _curPos >= _dataCount; }

    virtual bool GoNext() override {
        if (!IsTabEnd()) _curPos++;
        return IsTabEnd();
    }

    size_t GetCurPos() const { return _curPos; }

    virtual bool SetCurPos(size_t pos) {
        if (pos < _dataCount) _curPos = pos;
        else _curPos = 0;
        return IsTabEnd();
    }
};