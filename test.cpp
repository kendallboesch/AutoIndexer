#include "catch.hpp"
#include "DSString.h"


TEST_CASE("DSString Test", "[DSString]")
{
    DSString b("Boesch");
    DSString s = "Southern";
    DSString m = "Methodist";
    DSString u = "University";
    DSString pr = "Peruna";
    DSString t;
    DSString k(7);
    k = "Kendall";
    DSString un(u);
    char* l = "Computer Science";
    DSString ls(l);
    DSString x;
    x = s;
    DSString hl = "hello";
    DSString hu = "HELLO";
    pr = "Mustangs";
    DSString catTest1 = hl + hu;
    DSString catTest2 = s + m;
    DSString catTest3 = hu + " ";
    DSString catTest4 = s + " " + m + " " + u;
    DSString compTest2 = hu + hl;
    char* compTest3 = l;

    SECTION("CONSTRUCTORS & ASSIGNMENT OPERATORS ")
    {
        REQUIRE(b == "Boesch");
        REQUIRE(s == "Southern");
        REQUIRE(m == "Methodist");
        REQUIRE(un == "University");
        REQUIRE(k == "Kendall");
        REQUIRE(ls == "Computer Science");
        REQUIRE(x == "Southern");
        REQUIRE_FALSE(pr == "Peruna");
        REQUIRE(pr == "Mustangs");
    }
    SECTION("CONCATENATION OPERATOR")
    {
        REQUIRE(catTest1 == "helloHELLO");
        REQUIRE(catTest2 == "SouthernMethodist");
        REQUIRE(catTest3 == "HELLO ");
        REQUIRE(catTest4 == "Southern Methodist University");
    }
//    SECTION("COMPARISON OPERATORS")
//    {
//        REQUIRE_FALSE(hl == hu);
//        REQUIRE(hl > hu);
//        REQUIRE_FALSE(compTest2 == catTest1);
//        REQUIRE_FALSE(compTest2 > catTest1);
//        REQUIRE(catTest1 > compTest2);
//        REQUIRE(catTest4 > compTest3);
//    }
//    SECTION("INDEX OPERATOR")
//    {
//        REQUIRE(k[6] == 'l');
//        REQUIRE(b[4] == 'c');
//        REQUIRE(ls[0] == 'C');
//        REQUIRE_FALSE(ls[0] == 'c');
//        REQUIRE(pr[0] == m[0]);
//    }
//    SECTION("SUBSTRING - 2 PARAMETER")
//    {
//        REQUIRE(s.substring(0, 5) == "South");
//        REQUIRE(catTest4.substring(9, 9)== "Methodist");
//        REQUIRE(hu.substring(4,1) == "O");
//    }
//    SECTION("SUBSTING - 1 PARAMETER")
//    {
//        REQUIRE(catTest2.substring(8) == "Methodist");
//        REQUIRE(pr.substring(1) == "ustangs");
//        REQUIRE(k.substring(6) == "l");
//    }
//    SECTION("GET LENGTH")
//    {
//        REQUIRE(k.getLength() == 7);
//        REQUIRE(catTest4.getLength() == 29);
//        REQUIRE((hu.substring(4,1)).getLength() == 1);
//    }
//    SECTION("INDEX OF")
//    {
//        REQUIRE(hu.indexOf('O') == 4);
//        REQUIRE(k.indexOf('K') == 0);
//        REQUIRE(catTest4.indexOf(' ') == 8);
//        REQUIRE(u.indexOf('u') == -1);
//    }
//    SECTION("CONTAINS TEST")
//    {
//        REQUIRE(hl.contains("hello"));
//        REQUIRE(k.contains("all"));
//        REQUIRE_FALSE(s.contains("south"));
//        REQUIRE(s.contains("South"));
//        REQUIRE_FALSE(m.contains("meth"));
//        REQUIRE(catTest4.contains(s.c_str()));
//    }
//    SECTION("TO LOWER TEST")
//    {
//        DSString up = "KENDALL";
//        up.makeLower();
//        DSString lower;
//        hu.makeLower();
//        DSString nums = "1234";
//        nums.makeLower();
//
//      REQUIRE(hu == hl);
//      REQUIRE(up == "kendall");
//      REQUIRE(nums == "1234");
//
//
//    }

}