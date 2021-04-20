#include <iostream>
#include <map>
#include <string>
using namespace std;
  
namespace ariel{
    class NumberWithUnits{

    private:
        double val;
        string unit;

    public:
        NumberWithUnits(double value, string type): val(value), unit(type){
        }

        double getValue() const{
            return val;
        };
        std::string getType() const{
            return unit;
        };

        ~NumberWithUnits(){}
        static void read_units(ifstream& units_file);

        /* Overloading the in/out stream operators */
        friend ostream& operator<<(ostream& os, const NumberWithUnits& n);
        friend istream& operator>>(istream& is, NumberWithUnits& n);

        /* Overloading the arithmetic operators */
        friend NumberWithUnits operator+(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend NumberWithUnits operator+(const NumberWithUnits& n);
        friend NumberWithUnits operator+=(NumberWithUnits& n1, const NumberWithUnits& n2);
        friend NumberWithUnits operator-(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend NumberWithUnits operator-(const NumberWithUnits& n);
        friend NumberWithUnits operator-=(NumberWithUnits& n1, const NumberWithUnits& n2);

        /* ++, -- operators */
        friend NumberWithUnits operator++(NumberWithUnits& n);
        friend NumberWithUnits operator++(NumberWithUnits& n, int);
        friend NumberWithUnits operator--(NumberWithUnits& n);
        friend NumberWithUnits operator--(NumberWithUnits& n, int);

        /* Multiplication operations overiding */
        friend NumberWithUnits operator*(NumberWithUnits& n, double num);
        friend NumberWithUnits operator*(double num, NumberWithUnits& n);
        friend NumberWithUnits operator*=(NumberWithUnits& n, double num);
        friend NumberWithUnits operator*=(double num, NumberWithUnits& n);

        /* Overloading the comparison operators */
        friend bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2);
        friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2);
    };
}