#pragma once

#include <variant>
#include <string>
#include <cstdint>

namespace N_db {
    using Integer = std::int64_t;
    using Real = double;
    using Text = std::string;
    using Boolean = bool;

    using Value = std::variant<
        std::monostate, // null
        Integer,
        Real,
        Text,
        Boolean
    >;

    inline constexpr Value null{std::monostate{}};
}

