#include "db.hxx"

Database::Database(const std::string& name, const std::vector<Column>& columns) {
    create_table(name, columns); // nice
}

void Database::create_table(const std::string& name, const std::vector<Column>& columns) {
    /* what i did */
    // tables[name] = {std::move(name), std::move(columns)};

    /* what AI did: */
    auto [it, inserted] = tables.try_emplace(name, Table{name, std::move(columns)});

    if(!inserted) {
        throw std::invalid_argument("table with name " + name + " already exists");
    }
    /* honestly better but I'd have improved over time anyway */
}

void Database::pprint_table(const std::string& name) {
    auto it = tables.find(name);
    if (it == tables.end()) {
        throw std::invalid_argument("table with name " + name + " does not exist, is this a typo?");
    }

    const Table& t = it->second;
    std::size_t row_count = 0;
    std::vector<std::size_t> widths;
    std::vector<std::vector<std::string>> cells;

    auto render_value = [](const N_db::Value& value) -> std::string {
        return std::visit([](const auto& item) -> std::string {
            using T = std::decay_t<decltype(item)>;
            if constexpr (std::is_same_v<T, std::monostate>) {
                return "NULL";
            } else if constexpr (std::is_same_v<T, N_db::Boolean>) {
                return item ? "true" : "false";
            } else {
                std::ostringstream out;
                out << item;
                return out.str();
            }
        }, value);
    };

    for (const Column& column : t.columns) {
        std::size_t width = column.name.size();
        std::vector<std::string> rendered;
        rendered.reserve(column.values.size());
        for (const N_db::Value& value : column.values) {
            rendered.push_back(render_value(value));
            width = std::max(width, rendered.back().size());
        }
        row_count = std::max(row_count, rendered.size());
        widths.push_back(std::max(width, std::size_t{4}));
        cells.push_back(std::move(rendered));
    }

    std::cout << t.name << " (" << row_count << (row_count == 1 ? " row)\n" : " rows)\n");
    if (t.columns.empty()) {
        std::cout << "  (no columns)\n\n";
        return;
    }

    auto border = [&](const char* left, const char* join, const char* right) {
        std::cout << left;
        for (std::size_t col = 0; col < widths.size(); ++col) {
            for (std::size_t i = 0; i < widths[col] + 2; ++i) {
                std::cout << "─";
            }
            std::cout << (col + 1 == widths.size() ? right : join);
        }
        std::cout << '\n';
    };

    auto print_cell = [](const std::string& text, std::size_t width, bool right_align) {
        const std::string padding(width - text.size(), ' ');
        std::cout << ' ';
        if (right_align) std::cout << padding;
        std::cout << text;
        if (!right_align) std::cout << padding;
        std::cout << " │";
    };

    border("┌", "┬", "┐");
    std::cout << "│";
    for (std::size_t col = 0; col < t.columns.size(); ++col) {
        print_cell(t.columns[col].name, widths[col], false);
    }
    std::cout << '\n';
    border("├", "┼", "┤");

    for (std::size_t row = 0; row < row_count; ++row) {
        std::cout << "│";
        for (std::size_t col = 0; col < t.columns.size(); ++col) {
            const std::string value = row < cells[col].size() ? cells[col][row] : "NULL";
            const DataType type = t.columns[col].type;
            const bool right_align = type == DataType::Integer || type == DataType::Real;
            print_cell(value, widths[col], right_align);
        }
        std::cout << '\n';
    }

    border("└", "┴", "┘");
    std::cout << '\n';
}

void Database::insert_row(const std::string& name, const std::vector<N_db::Value>& row) {

    auto it = tables.find(name);
    if (it == tables.end()) {
        throw(std::invalid_argument("ERROR in INSERTION: table with name: " + name + "does not exist"));
    }

    Table& t = it->second;

    if (row.size() < t.columns.size()) {
        throw std::invalid_argument("expected at least " + std::to_string(t.columns.size()) + " values, but got " + std::to_string(row.size()));
    }

    for (std::size_t i = 0; i < row.size(); ++i) {
        if (!matches_type(row[i], t.columns[i].type)) {
            throw std::invalid_argument("expected type " + std::to_string(static_cast<int>(t.columns[i].type)) + " for column " + t.columns[i].name + ", but got " + std::to_string(static_cast<int>(row[i].index())));
        }
    }

    std::size_t appended = 0;

    try {
        for (std::size_t i = 0; i < t.columns.size(); ++i) {
            const N_db::Value& val = row[i];
            t.columns[i].values.push_back(val);
            ++appended;
        }
    } catch (...) {
        // revert if something goes wrong
        for (std::size_t i = 0; i < appended; ++i) {
            t.columns[i].values.pop_back();
        }
        throw;
    }
    /* pseudo so i understand later:
        first we check row.size() >= t.columns.size() to make sure we have enough values to insert into each column
        Then we iterate over the row and check that each value matches the type of the corresponding column

        Then we iterate over the columns and insert the values into the column
    
    */
}