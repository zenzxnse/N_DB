#include "db.hxx"

#include <iostream>

int main()
{
    Database db("team A", {{"name", DataType::Text}, {"age", DataType::Integer}, {"height", DataType::Real}});

    db.create_table("team B", {{"name", DataType::Text}, {"age", DataType::Integer}, {"height", DataType::Real}});
    db.insert_row("team A", {N_db::Text{"Alice"}, N_db::Integer{25}, N_db::Real{1.72}});
    db.insert_row("team A", {N_db::Text{"Gemma"}, N_db::Integer{24}, N_db::Real{1.68}});
    db.insert_row("team A", {N_db::Text{"Kayla"}, N_db::Integer{25}, N_db::Real{1.65}});
    db.pprint_table("team A");
    db.insert_row("team B", {N_db::Text{"Max"}, N_db::Integer{28}, N_db::Real{1.87}});
    db.insert_row("team B", {N_db::Text{"George"}, N_db::Integer{24}, N_db::Real{1.78}});
    db.pprint_table("team B");

    return 0;
}
