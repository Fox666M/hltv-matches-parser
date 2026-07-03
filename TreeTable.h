#pragma once
#include "Table.h"

class TreeTable : public Table {
public:
    TreeTable() {}
    virtual bool IsFull() const override { return false; }
    virtual DatValue* FindRecord(std::string key) override { return nullptr; }
    virtual void InsertRecord(std::string key, DatValue* value) override {}
    virtual void DelRecord(std::string key) override {}
    virtual void Clear() override {}
    virtual bool Reset() override { return true; }
    virtual bool IsTabEnd() override { return true; }
    virtual bool GoNext() override { return true; }
    virtual std::string GetKey() const override { return ""; }
    virtual DatValue* GetValue() const override { return nullptr; }
};