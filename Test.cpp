#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <algorithm>
using namespace std;
using namespace ariel;

const std::string testFile = "./unit_test.txt";

// TEST_CASE("check all units from text are exist"){
//     CHECK_NOTHROW();
//     CHECK_NOTHROW();
//     CHECK_NOTHROW();
//     CHECK_NOTHROW();
//     CHECK_NOTHROW();
//     CHECK_NOTHROW();
//     CHECK_NOTHROW();
//     CHECK_NOTHROW();
//     CHECK_NOTHROW();
//     CHECK_NOTHROW();
// }

//------------arithmetic operators----------------//
TEST_CASE("Operator +"){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);
    
    //Correct conversions
    CHECK((NumberWithUnits(1,"km")+NumberWithUnits(1,"km"))==NumberWithUnits(2,"km"));
    CHECK((NumberWithUnits(1,"km")+NumberWithUnits(1,"m"))==NumberWithUnits(1.001,"km"));
    CHECK((NumberWithUnits(1,"m")+NumberWithUnits(1,"km"))==NumberWithUnits(1001,"m"));
    CHECK((NumberWithUnits(1,"m")+NumberWithUnits(1,"cm"))==NumberWithUnits(1.01,"m"));
    CHECK((NumberWithUnits(1,"km")+NumberWithUnits(1,"cm"))==NumberWithUnits(1.00001,"km"));
    CHECK((NumberWithUnits(1,"cm")+NumberWithUnits(1,"km"))==NumberWithUnits(100001,"cm"));

    //Incorrect conversions
    CHECK_THROWS(NumberWithUnits(1,"day")+NumberWithUnits(1,"ILS"));
    CHECK_THROWS(NumberWithUnits(1,"min")+NumberWithUnits(1,"km"));

    //Units do not exist
    CHECK_THROWS(NumberWithUnits(1,"kg")+NumberWithUnits(1,"g"));
    CHECK_THROWS(NumberWithUnits(1,"year")+NumberWithUnits(1,"week"));
}
TEST_CASE("Operator +="){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);

    NumberWithUnits km{1,"km"};
    NumberWithUnits m{1,"m"};
    NumberWithUnits cm{1,"cm"};
    NumberWithUnits day{1,"day"};

    //Correct conversions
    CHECK((km+=km)==NumberWithUnits{2,"km"});
    CHECK((km+=m)==NumberWithUnits{2.001,"km"});
    CHECK((m+=km)==NumberWithUnits{2002,"m"});
    CHECK((m+=cm)==NumberWithUnits{2002.01,"m"});
    CHECK((km+=cm)==NumberWithUnits{2.00101,"km"});
    CHECK((cm+=km)==NumberWithUnits{200102,"cm"});

    //Incorrect conversions
    CHECK_THROWS(day+=NumberWithUnits{1,"ILS"});
    CHECK_THROWS(m+=NumberWithUnits{1,"min"});

    //Units do not exist
    CHECK_THROWS(km+=NumberWithUnits{1,"g"});
    CHECK_THROWS(day+=NumberWithUnits{1,"week"});
}
TEST_CASE("Operator + unari"){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);

    NumberWithUnits possitive(1,"hour");
            CHECK((+possitive).getValue()==1);
            CHECK((+possitive).getType()=="hour");
    NumberWithUnits negative(-1,"hour");
            CHECK((+negative).getValue()==1);
            CHECK((+negative).getType()=="hour");
}
TEST_CASE("Operator -"){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);

    //Correct conversions
    CHECK((NumberWithUnits(400,"day")-NumberWithUnits(1,"year"))==NumberWithUnits(35,"day"));
    CHECK((NumberWithUnits(60,"min")-NumberWithUnits(1,"hour"))==NumberWithUnits(0,"min"));
    CHECK((NumberWithUnits(2000,"min")-NumberWithUnits(1,"day"))==NumberWithUnits(560,"min"));
    CHECK((NumberWithUnits(120000,"sec")-NumberWithUnits(1,"day"))==NumberWithUnits(33600,"sec"));

    //Incorrect conversions
    CHECK_THROWS(NumberWithUnits(1,"day")-NumberWithUnits(1,"ILS"));
    CHECK_THROWS(NumberWithUnits(1,"min")-NumberWithUnits(1,"km"));

    //Units do not exist
    CHECK_THROWS(NumberWithUnits(1,"kg")-NumberWithUnits(1,"g"));
    CHECK_THROWS(NumberWithUnits(1,"year")-NumberWithUnits(1,"week"));

}
// TEST_CASE("Operator -="){
//     ifstream unitsFile{testFile};
//     NumberWithUnits::read_units(unitsFile);

//     //Correct conversions
//     CHECK((NumberWithUnits(400,"day")-=NumberWithUnits(1,"year"))==NumberWithUnits(35,"day"));
//     CHECK((NumberWithUnits(60,"min")-=NumberWithUnits(1,"hour"))==NumberWithUnits(0,"min"));
//     CHECK((NumberWithUnits(2000,"min")-=NumberWithUnits(1,"day"))==NumberWithUnits(560,"min"));
//     CHECK((NumberWithUnits(120000,"sec")-=NumberWithUnits(1,"day"))==NumberWithUnits(33600,"sec"));

//     //Incorrect conversions
//     CHECK_THROWS(NumberWithUnits(1,"day")-=NumberWithUnits(1,"ILS"));
//     CHECK_THROWS(NumberWithUnits(1,"min")-=NumberWithUnits(1,"km"));

//     //Units do not exist
//     CHECK_THROWS_MESSAGE(NumberWithUnits(1,"kg")-=NumberWithUnits(1,"g"));
//     CHECK_THROWS_MESSAGE(NumberWithUnits(1,"year")-=NumberWithUnits(1,"week"));
// }
TEST_CASE("Operator - unari"){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);

    NumberWithUnits possitive(1,"hour");
        CHECK((-possitive).getValue()==-1);
    NumberWithUnits negative(-1,"hour");
        CHECK((-negative).getValue()==1);
}

TEST_CASE("Operator *"){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);
    double num=3;
    NumberWithUnits n(2, "EUR");

    //from left
     NumberWithUnits left = num* n;
     CHECK((left.getValue() == 6 && left.getType() == "EUR" && n.getValue() == 2));

    //from right
    NumberWithUnits right = n*num;
    CHECK((right.getValue() == 6 && right.getType() == "EUR" && n.getValue() == 2));
}

TEST_CASE("Operator *="){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);
    double num=3;
    NumberWithUnits n(2, "USD");

    //num from right
    n*=num;
    CHECK((n.getValue() == 6 && n.getType() == "USD"));

    //num from left
    num*=n;
    CHECK((n.getValue() == 6 && n.getType() == "USD"));
}

// ---------------boolean operators------------------------------//
TEST_CASE("Operator <"){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);

    CHECK_FALSE(NumberWithUnits(10,"km")<NumberWithUnits(10,"km"));
    CHECK_FALSE(NumberWithUnits(2,"m")<NumberWithUnits(2,"m"));
    CHECK_FALSE(NumberWithUnits(5,"km")<NumberWithUnits(4500,"m"));
    CHECK_FALSE(NumberWithUnits(1000,"m")<NumberWithUnits(1,"km"));
    CHECK_FALSE(NumberWithUnits{200000,"cm"}<NumberWithUnits{1,"km"});

    CHECK(NumberWithUnits(3,"km")<NumberWithUnits(6000,"m"));
    CHECK(NumberWithUnits(2,"kg")<NumberWithUnits(4,"kg"));
    CHECK(NumberWithUnits(1,"cm")<NumberWithUnits(1,"m"));

}

TEST_CASE("Operator <="){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);

    CHECK_FALSE(NumberWithUnits(2,"m")<=NumberWithUnits(2,"m"));
    CHECK_FALSE(NumberWithUnits(5,"km")<=NumberWithUnits(4500,"m"));
    CHECK_FALSE(NumberWithUnits(200000,"cm")<=NumberWithUnits(1,"km"));

    CHECK(NumberWithUnits(10,"km")<=NumberWithUnits(10,"km"));
    CHECK(NumberWithUnits(5,"km")<=NumberWithUnits(6,"km"));
    CHECK(NumberWithUnits(5,"km")<=NumberWithUnits(6000,"m"));
    CHECK(NumberWithUnits(1000,"m")<=NumberWithUnits(1,"km"));
}

TEST_CASE("Operator >"){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);

    CHECK(NumberWithUnits(5,"km")>NumberWithUnits(4500,"m"));
    CHECK(NumberWithUnits(200000,"cm")>NumberWithUnits(1,"km"));
    CHECK(NumberWithUnits(3,"m")>NumberWithUnits(2,"m"));
    CHECK(NumberWithUnits(7,"km")>NumberWithUnits(6000,"m"));

    CHECK_FALSE(NumberWithUnits(10,"km")>NumberWithUnits(10,"km"));
    CHECK_FALSE(NumberWithUnits(2,"km")>NumberWithUnits(6000,"m"));
    CHECK_FALSE(NumberWithUnits(1000,"m")>NumberWithUnits(1,"km"));


}
TEST_CASE("Operator >="){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);

    CHECK(NumberWithUnits(10,"km")>=NumberWithUnits(10,"km"));
    CHECK(NumberWithUnits(1000,"m")>=NumberWithUnits(1,"km"));
    CHECK(NumberWithUnits(200000,"cm")>=NumberWithUnits(1,"km"));
    CHECK(NumberWithUnits(3,"m")>=NumberWithUnits(2,"m"));
    CHECK(NumberWithUnits(7,"km")>=NumberWithUnits(6000,"m"));
    CHECK(NumberWithUnits(5,"km")>=NumberWithUnits(4500,"m"));

    CHECK_FALSE(NumberWithUnits(5,"km")>=NumberWithUnits(6,"km"));
    CHECK_FALSE(NumberWithUnits(2,"km")>=NumberWithUnits(6000,"m"));

}

TEST_CASE("Operator =="){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);
    CHECK_EQ(NumberWithUnits(1, "km") , NumberWithUnits(1000, "m"));
    CHECK_EQ(NumberWithUnits(1, "m") , NumberWithUnits(100, "cm"));
    CHECK_EQ(NumberWithUnits(1, "l") , NumberWithUnits(1000, "ml"));
    CHECK_EQ(NumberWithUnits(1, "day") , NumberWithUnits(24, "hour"));
    CHECK_EQ(NumberWithUnits(1, "year") , NumberWithUnits(365, "day"));
    CHECK_EQ(NumberWithUnits(1, "hour") , NumberWithUnits(360, "sec"));                                 
}
    

TEST_CASE("Operator !="){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);

    CHECK_NE(NumberWithUnits(1, "km") , NumberWithUnits(1000, "cm"));
    CHECK_NE(NumberWithUnits(1, "m") , NumberWithUnits(1000, "km"));
    CHECK_NE(NumberWithUnits(1, "hour") , NumberWithUnits(4000, "min"));
    CHECK_NE(NumberWithUnits(1, "year") , NumberWithUnits(364, "day"));
    CHECK_NE(NumberWithUnits(1, "day") , NumberWithUnits(10, "hour"));

}

 //------------------Increament\Decreament operators----------------------//
TEST_CASE("Operator ++"){

    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);
    NumberWithUnits n(4, "day");
    CHECK(n++ == NumberWithUnits(4, "day"));
    CHECK(n == NumberWithUnits(5, "day"));
    CHECK(++n == NumberWithUnits(6, "day"));
    CHECK(n == NumberWithUnits(6, "day"));
    
}
TEST_CASE("Operator --"){

    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);
    NumberWithUnits n(4, "day");
    CHECK(n-- == NumberWithUnits(4, "day"));
    CHECK(n == NumberWithUnits(3, "day"));
    CHECK(--n == NumberWithUnits(2, "day"));
    CHECK(n == NumberWithUnits(2, "day"));
}

//-----------------------in\out stream operators--------------------//
TEST_CASE("Operator <<"){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);

    NumberWithUnits n(1,"km");
    stringstream str;
    str << n << endl;
    CHECK(str.str()=="1[km]");
}

TEST_CASE("Operator >>"){
    ifstream unitsFile{testFile};
    NumberWithUnits::read_units(unitsFile);

    NumberWithUnits n{5,"km"};
    istringstream sample_input{"24 [ hour ]"};
    sample_input >> n;
    CHECK(n == NumberWithUnits{24, "hour"});
   
    istringstream str2("24 [ something ]");
    CHECK_THROWS(str2 >> n);
    CHECK(n.getValue() == 24);
}