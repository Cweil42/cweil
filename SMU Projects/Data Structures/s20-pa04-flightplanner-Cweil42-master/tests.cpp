#include "catch.hpp"

#include "DSString.h"
#include <cstring>
#include "DSvector.h"
#include <vector>
#include "LinkedList.h"
#include "DSstack.h"

TEST_CASE("Stack class", "[stack]"){
    DSstack<int> data;
    data.push(3);
    data.push(4);
    data.push(5);

    SECTION("Is Empty"){
        REQUIRE(data.isEmpty() == false);
        data.pop();
        REQUIRE(data.isEmpty() == false);
        data.pop();
        REQUIRE(data.isEmpty() == false);
        data.pop();
        REQUIRE(data.isEmpty() == true);
    }

    SECTION("Peek"){
        REQUIRE(data.peek() == 5);
        data.push(4);
        REQUIRE(data.peek() == 4);
        data.pop();
        data.pop();
        data.pop();
        data.pop();
        //REQUIRE(data.peek() == nullptr);
    }

    SECTION("Push"){
        data.push(1);
        REQUIRE(data.peek() == 1);
        data.push(2);
        REQUIRE(data.peek() == 2);
        data.push(3);
        REQUIRE(data.peek() == 3);
    }

    SECTION("Pop"){
        data.pop();
        REQUIRE(data.peek() == 4);
        data.pop();
        REQUIRE(data.peek() == 3);
    }

    SECTION("Search"){
        REQUIRE(data.search(3) == true);
        REQUIRE(data.search(6) == false);
    }
}

TEST_CASE("LinkedList class", "[LinkList]"){
    LinkedList<int> link;
    link.insertAtEnd(3);
    link.insertAtEnd(4);
    link.insertAtEnd(5);

    SECTION("Copy Constructor"){
        LinkedList<int> listy(link);
        REQUIRE(listy.getData(listy.getHead()) == 3);
        REQUIRE(listy.getData(listy.getTail()) == 5);
        link.remove(5);
        REQUIRE(listy.getData(listy.getTail()) == 5);
    }

    SECTION("Insert at End"){
        REQUIRE(link.getData(link.getHead()) == 3);
        REQUIRE(link.getData(link.getTail()) == 5);
    }

    SECTION("Insert at Front"){
        link.insertAtFront(2);
        REQUIRE(link.getData(link.getHead()) == 2);
        link.insertAtFront(1);
        REQUIRE(link.getData(link.getHead()) == 1);
    }

    SECTION("Remove"){
        link.remove(3);
        REQUIRE(link.getData(link.getHead()) == 4);
        link.remove(5);
        REQUIRE(link.getData(link.getHead()) == 4);
    }

    SECTION("Get Size"){
        REQUIRE(link.getSize() == 3);
        link.insertAtEnd(6);
        REQUIRE(link.getSize() == 4);
        link.insertAtEnd(7);
        REQUIRE(link.getSize() == 5);
    }

    SECTION("Copy Constructor"){

        REQUIRE(link.getSize() == 3);
        link.insertAtEnd(6);
        REQUIRE(link.getSize() == 4);
        link.insertAtEnd(7);
        REQUIRE(link.getSize() == 5);
    }

    SECTION("Remove Tail"){
        link.removeTail();
        REQUIRE(link.getTail()->getData() == 4);
        link.removeTail();
        REQUIRE(link.getTail()->getData() == 3);
        link.removeTail();
        REQUIRE(link.getTail() == nullptr);
        link.removeTail();
        REQUIRE(link.getTail() == nullptr);
    }
}


TEST_CASE("Vector class", "[vector]"){

    DSvector<int> one;
    one.push_back(2);
    one.push_back(5);
    one.push_back(1);
    one.push_back(4);
    one.push_back(3);

    DSvector<int> two;
    two.push_back(6);
    two.push_back(8);
    two.push_back(9);
    two.push_back(7);
    two.push_back(10);

    SECTION("[] operator"){
        REQUIRE(one[0] == 2);
        REQUIRE(one[1] == 5);
        REQUIRE(two[2] == 9);
        REQUIRE(two[3] == 7);
        REQUIRE(!(one[4] == one[3]));
    }

    SECTION("Resize"){
        int size = one.getSize();
        one.resize();
        REQUIRE(one.getSize() == size);
        size = two.getSize();
        two.resize();
        REQUIRE(two.getSize() == size);
    }

    SECTION("Pushback function"){
        one.push_back(10);
        REQUIRE(one[one.getSize()-1] == 10);
        two.push_back(20);
        REQUIRE(two[two.getSize()-1] == 20);
    }

    SECTION("Sort function"){
        one.sort();
        REQUIRE(one[0] == 1);
        REQUIRE(one[1] == 2);
        REQUIRE(one[2] == 3);
        REQUIRE(one[3] == 4);
        REQUIRE(one[4] == 5);
        two.sort();
        REQUIRE(two[0] == 6);
        REQUIRE(two[1] == 7);
        REQUIRE(two[2] == 8);
        REQUIRE(two[3] == 9);
        REQUIRE(two[4] == 10);
    }

    SECTION("= operator"){
        DSvector<int> test;
        test.push_back(6);
        test.push_back(7);
        test.push_back(8);
        test.push_back(9);
        test.push_back(10);
        one = test;
        REQUIRE(one[0] == 6);
        REQUIRE(one[1] == 7);
        REQUIRE(one[2] == 8);
        REQUIRE(one[3] == 9);
        REQUIRE(one[4] == 10);

    }
}

TEST_CASE("String class", "[string]"){

    DSString s[10];
    s[0] = DSString("testString");
    s[1] = DSString("a test string");
    s[2] = DSString("");
    s[3] = DSString("THIS IS AN UPPERCASE STRING");
    s[4] = DSString("this is an uppercase string");
    s[5] = DSString("\n");
    s[6] = DSString("");
    s[7] = DSString("  split  split  split  ");
    s[8] = DSString("                          ");
    s[9] = DSString("testString");

    SECTION("Equality operators"){
        REQUIRE(s[0] == DSString("testString"));
        REQUIRE(s[0] == s[9]);
        REQUIRE(s[2] == "");
        REQUIRE(s[1] == "a test string");
        REQUIRE(!(s[3] == s[4]));
    }

    SECTION("Assignment operators"){
        DSString str;
        str = "a test string";
        REQUIRE(str == s[1]);
        str = DSString("testString");
        REQUIRE(str == s[0]);
        str = "";
        REQUIRE(str == s[6]);
        str = DSString("\n");
        REQUIRE(str == s[5]);
    }

    SECTION("Addition operator"){
        REQUIRE(DSString("testStringtestString") == s[0]+s[9]);
        REQUIRE(s[6] + s[6] == "");
        REQUIRE(s[5] + s[6] == DSString
                ("\n"));
        REQUIRE(s[0] + s[1] + s[2] == "testStringa test string");
    }

    SECTION("Greater than operator"){
        REQUIRE(s[0] > s[1]);
        REQUIRE(s[4] > s[3]);
        REQUIRE(s[9] > s[6]);
        REQUIRE(s[7] > s[6]);
    }

    SECTION("[] Operator"){
        REQUIRE(s[0][1] == 'e');
        REQUIRE(s[4][4] == ' ');
        REQUIRE(s[6][0] == 0);
    }

    SECTION("getLength function"){
        REQUIRE(s[9].getLength() == 10);
        REQUIRE(s[2].getLength() == 0);
        REQUIRE(s[8].getLength() == 26);
        REQUIRE(s[3].getLength() == 27);
    }

    SECTION("Substring function"){
        REQUIRE(s[0].substring(0, 5) == "testS");
        REQUIRE(s[4].substring(0, 4) == "this");
        REQUIRE(s[4].substring(1, 3) == "his");
        REQUIRE(s[4].substring(1, 1) == "h");
        REQUIRE(s[0].substring(1, 4) == "estS");
        REQUIRE(s[0].substring(4, 1) == "S");
    }

    SECTION("c_str function"){
        REQUIRE(strcmp(s[0].c_str(), "testString") == 0);
        REQUIRE(strcmp(s[9].c_str(), s[0].c_str()) == 0);
        REQUIRE(strcmp(s[2].c_str(), "") == 0);
    }

}


