#pragma once

#include "types.hxx"

#include <unordered_map>
#include <stdexcept>
#include <string>

#include <iostream>
#include <algorithm>
#include <sstream>

class Database {
public:
    std::unordered_map<std::string, Table> tables;
    explicit Database(const std::string& name, const std::vector<Column>& columns);
    Database() = default;

    void create_table(const std::string& name, const std::vector<Column>& columns);
    void pprint_table(const std::string& name);
    /* 
    how should I approach this?
    maybe I can have a vector of columns and a vector of rows.
    Then I can just iterate over the vector of rows and insert them into the vector of columns.
    */
    void insert_row(const std::string& name, const std::vector<N_db::Value>& row);
};


