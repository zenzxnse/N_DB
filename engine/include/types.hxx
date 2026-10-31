#pragma once

#include <value.hxx>
#include <vector>
#include <type_traits>

enum struct DataType
{
    Integer,
    Real,
    Text,
    Boolean
};

// OLAP
struct Column {
    std::string name;
    DataType type;
    std::vector<N_db::Value> values; // please imagine vertical
};

struct Table {
    std::string name;
    std::vector<Column> columns;
};

bool matches_type(const N_db::Value& val, DataType type);




