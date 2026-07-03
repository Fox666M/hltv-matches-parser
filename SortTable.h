#pragma once
#include "ScanTable.h"
#include <algorithm> // Для std::sort

enum Sortmethod { Insert, Merge, Quick };

class SortTable : public ScanTable {
protected:
    Sortmethod _method;

public:
    SortTable(Sortmethod sm, size_t size = 100) : ScanTable(size), _method(sm) {}

    // Реализация вставки с учетом сортировки (вставляем в конец и сортируем)
    virtual void InsertRecord(std::string key, DatValue* value) override {
        if (IsFull()) return;
        _records[_dataCount] = new TabRecord(key, value);
        _dataCount++;
        SortData(); // Сортируем после каждой вставки
    }

    // Простейшая сортировка вставками (InsertSort)
    void SortData() {
        for (size_t i = 1; i < _dataCount; i++) {
            Record temp = _records[i];
            int j = i - 1;
            while (j >= 0 && *(_records[j]) > *temp) {
                _records[j + 1] = _records[j];
                j--;
            }
            _records[j + 1] = temp;
        }
    }

    virtual DatValue* FindRecord(std::string key) override {
        // Тут можно сделать бинарный поиск, так как массив отсортирован
        // Но пока оставь стандартный из ScanTable, если лень писать
        return ScanTable::FindRecord(key);
    }
    
    virtual void DelRecord(std::string key) override {
        ScanTable::DelRecord(key);
    }
};