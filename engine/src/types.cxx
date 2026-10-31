#include "types.hxx"


bool matches_type(const N_db::Value& val, DataType type) {
    switch (type) {
        case DataType::Integer:
            return std::holds_alternative<N_db::Integer>(val);
        case DataType::Real:
            return std::holds_alternative<N_db::Real>(val);
        case DataType::Text:
            return std::holds_alternative<N_db::Text>(val);
        case DataType::Boolean:
            return std::holds_alternative<N_db::Boolean>(val);
    }
    return false;
}