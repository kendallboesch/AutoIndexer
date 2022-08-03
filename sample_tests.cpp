////
//// Created by MARK FONTENOT on 9/14/21.
////
//
///**
// * This file contains some simple tests.
// *
// * DO NOT add the #define CATCH_CONFIG_RUNNER to this file.
// * It is already in catch_setup.cpp
// *
// * Note that you can have more than one cpp file with tests in them.
// * For example, you could have a test file for your DSString and a
// * separate one for your DSVector.
// */
//
//#include "catch.hpp"
//
//TEST_CASE("Testing Tests", "[multiplication]") {
//    REQUIRE((2 * 2) == 4);
//    REQUIRE((1 * 5) == 5);
//}
#include "catch.hpp"
#include "DSString.h"
#include "DSVector.h"


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
    SECTION("COMPARISON OPERATORS")
    {
        REQUIRE_FALSE(hl == hu);
        REQUIRE(hl > hu);
        REQUIRE_FALSE(compTest2 == catTest1);
        REQUIRE_FALSE(compTest2 > catTest1);
        REQUIRE(catTest1 > compTest2);
        REQUIRE(catTest4 > compTest3);
    }
    SECTION("INDEX OPERATOR")
    {
        REQUIRE(k[6] == 'l');
        REQUIRE(b[4] == 'c');
        REQUIRE(ls[0] == 'C');
        REQUIRE_FALSE(ls[0] == 'c');
        REQUIRE(pr[0] == m[0]);
    }
    SECTION("SUBSTRING - 2 PARAMETER")
    {
        REQUIRE(s.substring(0, 5) == "South");
        REQUIRE(catTest4.substring(9, 9)== "Methodist");
        REQUIRE(hu.substring(4,1) == "O");
    }
    SECTION("SUBSTING - 1 PARAMETER")
    {
        REQUIRE(catTest2.substring(8) == "Methodist");
        REQUIRE(pr.substring(1) == "ustangs");
        REQUIRE(k.substring(6) == "l");
    }
    SECTION("GET LENGTH")
    {
        REQUIRE(k.getLength() == 7);
        REQUIRE(catTest4.getLength() == 29);
        REQUIRE((hu.substring(4,1)).getLength() == 1);
    }
    SECTION("INDEX OF")
    {
        REQUIRE(hu.indexOf('O') == 4);
        REQUIRE(k.indexOf('K') == 0);
        REQUIRE(catTest4.indexOf(' ') == 8);
        REQUIRE(u.indexOf('u') == -1);
    }
    SECTION("CONTAINS TEST")
    {
        REQUIRE(hl.contains("hello"));
        REQUIRE(k.contains("all"));
        REQUIRE_FALSE(s.contains("south"));
        REQUIRE(s.contains("South"));
        REQUIRE_FALSE(m.contains("meth"));
        REQUIRE(catTest4.contains(s.c_str()));
    }
    SECTION("TO LOWER TEST")
    {
        DSString up = "KENDALL";
        up.makeLower();
        DSString lower;
        hu.makeLower();
        DSString nums = "1234";
        nums.makeLower();

      REQUIRE(hu == hl);
      REQUIRE(up == "kendall");
      REQUIRE(nums == "1234");

    }
    SECTION("TO INT TEST")
    {
        int n1 = 1;
        int n2 = 2;
        int n3 = 3;
        int n4 = 4;
        int n7 = 7;
        int n12 = 12;
        int n90 = 90;

        DSString nums = "1234567890";
        int numsAsInt = nums.substring(0,4).toInt();
        REQUIRE(numsAsInt == 1234);
      //  int
        REQUIRE(nums.substring(8).toInt() == 90);
    }
    SECTION("OVERLOADED NOT EQUAL TO OPERATOR")
    {
        DSString a = "Computer";
        DSString a2 = "Computer";
        DSString b = "Science";
        DSString c = "science";

        REQUIRE(a != b);
        REQUIRE(b != c);
        REQUIRE(a != a2);

    }
}
TEST_CASE("DSVector")
{
    SECTION("CONSTRUCTTORS")
    {
        DSVector<int> a;
        REQUIRE(a.getSize() == 0);
        for(int i = 0; i < 10; i++)
        {
            if(i % 3 == 2)
            {
                a.push_back(i);
            }
        }
        REQUIRE_FALSE(a.getSize() ==0);
        REQUIRE(a.getSize() > 0);

        DSVector<int>b(a);
        REQUIRE(b.getSize() > 0);
        DSVector<int>c = b;
        REQUIRE(c.getSize() > 0);
        REQUIRE(a == b);
        REQUIRE(b == c);

    }
    SECTION("TESTING GET SIZE")
    {
        DSVector<int> n;
        DSVector<DSString> s;
        DSVector<double> d;

        n.push_back(7);
        s.push_back("Kendall");
        d.push_back(.07);

        REQUIRE_FALSE(n.getSize() == 0);
        REQUIRE(s.getSize() == 1);
        REQUIRE_FALSE(d.getSize() == 2);
        REQUIRE(d.getSize() == 1);

        // 50 tests
    }
    SECTION("PUSH_BACK && INDEX OPERATOR TEST")
    {
        DSVector<int> nums;
        int arr[] = {1,2,3,4,5, 7};
        for(int i = 0; i < 7; i++)
        {
            nums.push_back(arr[i]);
        }
        REQUIRE(nums[0] == 1);
        REQUIRE(nums[3] == 4);
        REQUIRE(nums[5] == 7);
        // 53 tests
    }
    SECTION("AUTO ADJUST TEST")
    {
        DSVector<char> alphaNumerals;
        REQUIRE(alphaNumerals.getCap() == 10);
        REQUIRE(alphaNumerals.getSize() == 0);
        REQUIRE(alphaNumerals.getAvailable() == 10);
        // 56 tests
        char alphanumericChars[] = "123456789abcdefghijklmnopqrstuvwxyz";
        for(int i = 0; i < 15; i++)
        {
            alphaNumerals.push_back(alphanumericChars[i]);
        }
        cout << "get cap start" << endl;
        REQUIRE_FALSE(alphaNumerals.getCap() == 10);
        REQUIRE(alphaNumerals.getCap() == 20);
      //  cout << "capacity: " << alphaNumerals.getCap() << endl;
      //  cout <<"get siuze start" << endl;
        REQUIRE_FALSE(alphaNumerals.getSize() == 0);
        REQUIRE(alphaNumerals.getSize() > 10);
        REQUIRE(alphaNumerals.getSize() < 20);
        for(int i = 0; i < 10; i++)
        {
            alphaNumerals.push_back(alphanumericChars[i]);
        }
        REQUIRE_FALSE(alphaNumerals.getCap() == 20);
        REQUIRE(alphaNumerals.getCap() > 20);
        REQUIRE(alphaNumerals.getCap() == 40);

        for(int i = 0; i < 40; i++)
        {
            alphaNumerals.push_back(alphanumericChars[i]);
        }
        REQUIRE(alphaNumerals.getCap() == 80);
    }
    SECTION("PUSH_FRONT")
    {
        DSVector<DSString> name;
        name.push_front("Boesch");
        name.push_front("Reese");
        name.push_front("Kendall");

        REQUIRE(name[0] == "Kendall");
        REQUIRE(name[1] == "Reese");
        REQUIRE(name[2] == "Boesch");
    }
    SECTION("INSERT AT")
    {

        DSVector<int> nums;
        nums.push_back(0);
        nums.push_back(1);
        nums.push_back(2);
        nums.push_back(3);
        nums.push_back(5);
        nums.push_back(6);
        nums.push_back(7);

        REQUIRE(nums[0] == 0);

        REQUIRE(nums[4] == 5);
        REQUIRE(nums.getSize() == 7);
        nums.insertAt(4, 4);

        REQUIRE_FALSE(nums[4] == 5);
        REQUIRE(nums[4] == 4);
        REQUIRE_FALSE(nums.getSize() == 7);
        REQUIRE(nums.getSize() == 8);
        nums.insertAt(7, 2);

        REQUIRE(nums[2] == 7);
        REQUIRE(nums.getSize() == 9);
        REQUIRE(nums[1] == 1);
        REQUIRE(nums[3] == 2);

        nums.insertAt(10, 0);
        REQUIRE(nums[0] == 10);
        REQUIRE(nums[9] == 7);

        nums.insertAt(4, 10);
        REQUIRE(nums[10] == 4);
        REQUIRE(nums[9] == 7);

        nums.insertAt(2, 1000);
        REQUIRE(nums[11] == 2);
    }

    SECTION("REMOVE")
    {
        DSVector<char> rt;
        rt.push_back('c');
        rt.push_back('s');
        rt.push_back('2');
        rt.push_back('3');
        rt.push_back('x');
        rt.push_back('4');
        rt.push_back('1');

        REQUIRE(rt[4] == 'x');
        REQUIRE(rt.getSize() == 7);
        REQUIRE(rt.getAvailable() == 3);

        rt.remove(4);
        REQUIRE(rt[4] == '4');
        REQUIRE(rt.getSize() == 6);
        REQUIRE(rt.getAvailable() == 4);

        rt.remove(0);
        REQUIRE(rt[0] == 's');
        REQUIRE(rt.getSize() == 5);
        REQUIRE(rt.getAvailable() == 5);

        rt.remove(4);
        REQUIRE(rt[3] == '4');

    }
//    SECTION("CONCATENATION OP")
//    {
//        DSVector<DSString> a;
//        DSVector<DSString> b;
//        DSVector<DSString> concat;
//        DSVector<DSString> check;
//        a.push_back("Southern");
//        check.push_back("Southern");
//        a.push_back("Methodist");
//        check.push_back("Methodist");
//        a.push_back("University");
//        check.push_back("University");
//        b.push_back("Dallas");
//        check.push_back("Dallas");
//        b.push_back("Texas");
//        check.push_back("Texas");
//
//        concat = a + b;
//
//       // REQUIRE(concat == check);
//
//    }

    SECTION("EMPTY")
    {
       DSVector<int> nums;
       nums.push_back(1);
       nums.push_back(2);
       nums.push_back(3);
       nums.push_back(4);

       REQUIRE(nums.getSize() == 4);
       REQUIRE(nums[2] == 3);
       REQUIRE(nums[0] == 1);

       nums.empty();

       REQUIRE(nums.getSize() == 0);
       REQUIRE_THROWS(nums[2] == NULL);
       REQUIRE_THROWS(nums[0] == NULL);
    }
    SECTION("SEARCH TEST")
    {
        DSVector<DSString> names;
        names.push_back("Kendall");
        names.push_back("Michael");
        names.push_back("Thomas");
        names.push_back("Terri");

        REQUIRE(names.search("Michael") == 1);
        REQUIRE(names.search("Bodee") == -1);
        REQUIRE_FALSE(names.search("thomas") == 2);
    }
    SECTION("SORT TEST - TODO")
    {
        DSVector<int> ints;
        DSVector<int> inInts;
        DSVector<DSString> strings;
        DSVector<DSString> inStrings;

       int nums[] = {7, 2, 0, 12, 4};
       for(int i = 0; i < 5; i++)
       {
           ints.push_back(nums[i]);
       }

       DSString strs[] = {"boesch", "alan", "zoe", "Dallas", "Texas"};
       for(int ii = 0; ii < 3; ii++)
       {
           strings.push_back(strs[ii]);
       }

       REQUIRE(ints.begin() == 7);
       REQUIRE(ints.end() == 4);
       REQUIRE(ints[2] == 0);
    }
    SECTION("SWAP TEST")
    {
        DSVector<int> n;
        for(int i = 0; i < 10; i++)
        {
            n.push_back(i);
        }

        REQUIRE(n[0] == 0);
        REQUIRE(n[7] == 7);

        swap(n[0], n[7]);

        REQUIRE_FALSE(n[0] == 0);
        REQUIRE_FALSE(n[7] == 7);

        REQUIRE(n[0] == 7);
        REQUIRE(n[7] == 0);

        DSVector<DSString> strtst;
        strtst.push_back("Alpha");
        strtst.push_back("Beta");
        strtst.push_back("Gamma");
        strtst.push_back("Delta");
        strtst.push_back("Epsilon");

        REQUIRE(strtst[1] == "Beta");
        REQUIRE(strtst[4] == "Epsilon");

        swap(strtst[4], strtst[1]);

        REQUIRE(strtst[1] == "Epsilon");
        REQUIRE(strtst[4] == "Beta");

    }
    SECTION("AUTOADJUST 2 TEST ")
    {

    }


}
