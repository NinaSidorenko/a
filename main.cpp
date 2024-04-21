#include <iostream>
#include <fstream>
#include "matrix.hpp"

using std::cin;
using std::cout;
using std::endl;

int main()
{

    Matrix<double> mdouble;
    std::ifstream indouble("matrixdouble.txt");
    if (indouble.is_open())
    {
        indouble >> mdouble;
    }
    cout << mdouble;

    std::ifstream inint("matrixint.txt");
    Matrix<int> mint(inint);
    cout << mint;

    Matrix <char> mchar (3, 3);
    std::ifstream inchar("matrixchar.txt");
    if (inchar.is_open())
    {
        inchar >> mchar;
    }
    cout << mchar;

    Matrix <std::string> mstring (2, 2);
    std::ifstream instring("matrixstring.txt");
    if (instring.is_open())
    {
        instring >> mstring;
    }
    cout << mstring;

    Matrix <double> mdouble1 = mdouble;
    Matrix <std::string> mstring1 = mstring;
    Matrix <char> mchar1 = mchar;

    Matrix <double> mplus = mdouble + mdouble1;
    cout << mplus;

    Matrix <std::string> mplus1 = mstring + mstring1;
    cout << mplus1;

    Matrix <double> mminus = mdouble - mdouble1;
    cout << mminus;

    Matrix <double> mproizv = mdouble * mdouble1;
    cout << mproizv;

    Matrix <double> mproizvscal = mdouble * 3;
    cout << mproizvscal;

    Matrix <double> mproizvscal1 = mint * 3.5;
    cout << mproizvscal1;

    Matrix<int> zero = mint.zero_matr(5);
    cout << zero;

    Matrix<int> one = mstring.one_matr(4);
    cout << one;

    std::ofstream out("out.txt");
    if (out.is_open())
    {
        out << zero;
        out << one;
    }

    cout << mdouble.determ() << endl;
    cout << mint.determ() << endl;
    cout << mchar.determ() << endl;

    Matrix<std::string> mstringtransp = mstring.transpose();
    cout << mstringtransp;

    Matrix<char> mchartransp = mchar.transpose();
    cout << mchartransp;

    Matrix<double> mintobr = !mint;
    cout << mintobr;

    Matrix<double> mdoubleobr = !mdouble;
    cout << mdoubleobr;

    Matrix <double> rightdouble = mdouble * mdoubleobr;
    cout << rightdouble;

    return 0;
}
