/****************************************************************************
* FILE: complex.hpp		            Purpose: Implementation for Complex Class.
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: Elizabeta Vitovsky		STATUS: Approved
*
*
****************************************************************************/

#ifndef __ILRD_RD100_COMPLEX_HPP__
#define __ILRD_RD100_COMPLEX_HPP__


namespace ilrd_rd100
{
class Complex
{
public:
    //Ctor, Dtor
    Complex(double re = 0, double im = 0);// non explicit, support arguments such as- 7

    //compunds
    Complex& operator+=(const Complex& rhs);
    Complex& operator-=(const Complex& rhs);
    Complex& operator*=(const Complex& rhs);
    Complex& operator/=(const Complex& rhs);

    //set, get
    void SetReal(double re);
    void SetImaginary(double im);
    double GetReal() const;
    double GetImaginary() const;

private:
    double m_re;
    double m_im;
}; // Complex - end

//standard operators
const Complex operator+(const Complex& lhs, const Complex& rhs);
const Complex operator-(const Complex& lhs, const Complex& rhs);
const Complex operator*(const Complex& lhs, const Complex& rhs);
const Complex operator/(const Complex& lhs, const Complex& rhs);

//comparison operators
bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

//iostream operators
std::ostream& operator<<(std::ostream& os, const Complex& num);
std::istream& operator>>(std::istream& is, Complex& num);

}//ilrd_rd100 - end


#endif//__ILRD_RD100_COMPLEX_HPP__ - end
