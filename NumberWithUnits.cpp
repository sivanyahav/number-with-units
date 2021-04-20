#include <iostream>
#include <fstream>
#include <map>
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;

namespace ariel{
    
    static map<string, map<string, float> > conversionMap;

    double conversion(double value, const string from, const string to){
        if(from == to) {return value;}
        if(conversionMap[from][to] == 0){
            throw invalid_argument{"Units do not match - ["+from+"] cannot be converted to ["+to+"]"};
        }
        return value * conversionMap[from][to];
    };

    void updateMap(const string unit1, const string unit2){
        for(auto [key, value] : conversionMap[unit2]){
            double w = conversionMap[unit1][unit2] * value;
            conversionMap[unit1][key] = w;
            conversionMap[key][unit1] = 1/w;
        }
    }

    void NumberWithUnits ::read_units(ifstream& units_file){
        double num1, num2;
        string unit1, unit2, eq;
        while(units_file >> num1 >> unit1 >> eq >> num2 >> unit2){
        conversionMap[unit1][unit2] = num2;
        conversionMap[unit2][unit1]= num1/num2;
        updateMap(unit1, unit2);
        updateMap(unit2, unit1);
        }
    }


    //-------------in\out stream operator-------------//
    ostream& operator<<(ostream& os, const NumberWithUnits& n){
        return (os << n.val << '[' << n.unit << ']');
    }

    std::istream &operator>>(std::istream &is, NumberWithUnits &n) {
        string str;
        is >> n.val >> str >> n.unit;
        if(conversionMap[n.unit].empty()){throw invalid_argument{"unit doesnt exist"};};
        return is;
        }

    //------------arithmetic operators----------------//

    NumberWithUnits operator+(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double convert= conversion(n2.val, n2.unit, n1.unit);
        return NumberWithUnits(n1.val+convert, n1.unit);
    }

    NumberWithUnits operator+(const NumberWithUnits& n){
        return NumberWithUnits(abs(n.val),n.unit);
    }

    NumberWithUnits operator+=(NumberWithUnits& n1, const NumberWithUnits& n2){
        n1.val+= conversion(n2.val, n2.unit, n1.unit);
        return n1;;
    }

    NumberWithUnits operator-(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double convert= conversion(n2.val, n2.unit, n1.unit);
        return NumberWithUnits(n1.val-convert, n1.unit);
    }

    NumberWithUnits operator-(const NumberWithUnits& n){
        return NumberWithUnits(-n.val,n.unit);
    }

    NumberWithUnits operator-=(NumberWithUnits& n1, const NumberWithUnits& n2){
        n1.val-= conversion(n2.val, n2.unit, n1.unit);
        return n1;;
    }

    //----------Multiplication operators----------//

    NumberWithUnits operator*(NumberWithUnits& n, double num){
        return NumberWithUnits (n.val*num, n.unit);
    }
    NumberWithUnits operator*(double num, NumberWithUnits& n){
        return NumberWithUnits (num*n.val, n.unit);
    }
    NumberWithUnits operator*=(NumberWithUnits& n, double num){
        n.val*=num;
        return n;
    }
    NumberWithUnits operator*=(double num, NumberWithUnits& n){
        n.val*=num;
        return n;
    }

    //------------boolean operators---------------//

    bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double converted=conversion(n2.val, n2.unit, n1.unit);
        return n1.val > converted; 
    }
    bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double converted=conversion(n2.val, n2.unit, n1.unit);
        return n1.val >= converted; 
    }
    bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double converted=conversion(n2.val, n2.unit, n1.unit);
        return n1.val < converted; 
    }
    bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double converted=conversion(n2.val, n2.unit, n1.unit);
        return n1.val <= converted; 
    }
    
    bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2){
        // double converted=conversion(n2.val, n2.unit, n1.unit);
        // cout << "converted = " << converted << " ,n1.val= " << n1.val  << endl;
        // cout << "n1.val == converted: " << (n1.val == converted) << endl; 
        return (n1.val == conversion(n2.val, n2.unit, n1.unit)); 
    }

    bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        return !(n1==n2);
    }

    //------------Increament\Decreament operators-------//
    NumberWithUnits operator++(NumberWithUnits& n){
        return NumberWithUnits(++n.val,n.unit);
    }
    NumberWithUnits operator++(NumberWithUnits& n, int){
        return NumberWithUnits(n.val++,n.unit);
    }
    NumberWithUnits operator--(NumberWithUnits& n){
        return NumberWithUnits(--n.val,n.unit);
    }
    NumberWithUnits operator--(NumberWithUnits& n, int){
        return NumberWithUnits(n.val--,n.unit);
    }

}

