#pragma once
#include "DatValue.h"

class TabRecord : public DatValue
{
protected:
    std::string _key;
    DatValue* _pValue;
public:
    TabRecord() : _key(""), _pValue(nullptr) {}
    TabRecord(std::string key, DatValue* pValue) : _key(key), _pValue(pValue) {}
    
    TabRecord(const TabRecord& other) {
        _key = other._key;
        _pValue = other._pValue ? other._pValue->GetCopy() : nullptr;
    }

    ~TabRecord() {
        delete _pValue;
    }

    TabRecord& operator=(const TabRecord& tmp) {
        if (this != &tmp) {
            _key = tmp._key;
            delete _pValue;
            _pValue = tmp._pValue ? tmp._pValue->GetCopy() : nullptr;
        }
        return *this;
    }

    DatValue* const GetValue() const { return _pValue; }
    std::string GetKey() const { return _key; }

    virtual DatValue* GetCopy() const override {
        return new TabRecord(*this);
    }

    virtual bool operator==(const TabRecord& tmp) const { return this->_key == tmp._key; }
    virtual bool operator>(const TabRecord& tmp) const { return this->_key > tmp._key; }
    virtual bool operator<(const TabRecord& tmp) const { return this->_key < tmp._key; }

    virtual std::ostream& print(std::ostream& os) const override {
        os << "KEY: " << this->_key << " | VALUE: ";
        if (_pValue) os << *(_pValue);
        else os << "NULL";
        return os << std::endl;
    }

    friend class ScanTable;
};