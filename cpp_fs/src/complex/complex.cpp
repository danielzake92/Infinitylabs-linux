/****************************************************************************
* FILE: complex.cpp		            Purpose: Implementation for Complex Class.
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: Elizabeta Vitovsky		STATUS: Approved
*
*
****************************************************************************/
#include <iostream> //std::cout
 
#include "complex.hpp" 

namespace ilrd_rd100
{
/****************************************************************************/
/****************************************************************************/	
/****************************************************************************/

static inline double RealResFromMultiply(const Complex &lhs, const Complex &rhs);

static inline double ImaginaryResFromMultiply(const Complex &lhs,
											  const Complex &rhs);

static inline double RealResFromDivision(const Complex &lhs, const Complex &rhs);

static inline double ImaginaryResFromDivision(const Complex &lhs,
 											  const Complex &rhs);

static inline double GetPoweredMangitude(const Complex &num);

Complex::Complex(double re, double im): m_re(re), m_im(im)
{
}
/****************************************************************************/
/*****************************COMPOUND OPERATORS*****************************/
/****************************************************************************/
Complex& Complex::operator+=(const Complex& rhs)
{
	*this = (*this) + rhs;
	return *this;
}
/****************************************************************************/
Complex& Complex::operator-=(const Complex& rhs)
{
	*this = (*this) - rhs;
	return *this;
}
/****************************************************************************/
Complex& Complex::operator*=(const Complex& rhs)
{
	*this = (*this) * rhs;
	return *this;
}
/****************************************************************************/
Complex& Complex::operator/=(const Complex& rhs)
{
	*this = (*this) / rhs;
	return *this;
}
/****************************************************************************/
/******************************REGULAR OPERATORS*****************************/
/****************************************************************************/
const Complex operator+(const Complex& lhs, const Complex& rhs)
{
	Complex temp(lhs.GetReal() + rhs.GetReal(),
				 lhs.GetImaginary() + rhs.GetImaginary());
	return temp;	
}
/****************************************************************************/
const Complex operator-(const Complex& lhs, const Complex& rhs)
{
	Complex temp(lhs.GetReal() - rhs.GetReal(),
				 lhs.GetImaginary() - rhs.GetImaginary());
	return temp;	
}
/****************************************************************************/
const Complex operator*(const Complex& lhs, const Complex& rhs)
{
	Complex temp(RealResFromMultiply(lhs, rhs),
				 ImaginaryResFromMultiply(lhs, rhs));
	return temp;
}
/****************************************************************************/
const Complex operator/(const Complex& lhs, const Complex& rhs)
{
	Complex temp(RealResFromDivision(lhs, rhs),
				 ImaginaryResFromDivision(lhs, rhs));
	return temp;
}
/****************************************************************************/
bool operator==(const Complex& lhs, const Complex& rhs)
{
	return(lhs.GetReal() == rhs.GetReal() &&
		   lhs.GetImaginary() == rhs.GetImaginary());
}
/****************************************************************************/
bool operator!=(const Complex& lhs, const Complex& rhs)
{
	return(!(lhs.GetReal() == rhs.GetReal() &&
		   lhs.GetImaginary() == rhs.GetImaginary()));
}
/****************************************************************************/
/*******************************STREAM OPERATORS*****************************/
/****************************************************************************/
std::ostream& operator<<(std::ostream& os, const Complex& num)
{
	char imSign = ((num.GetImaginary() < 0) ? (0) : ('+'));
	return os<<num.GetReal()<< imSign << num.GetImaginary() << "i" << std::endl;
}
/****************************************************************************/
std::istream& operator>>(std::istream& is, Complex& num)
{
	std::cout<<"(Real,imaginary)"<<std::endl;

	double temp_real;
	double temp_imaginary;
	is>>temp_real>>temp_imaginary;
	num.SetReal(temp_real);
	num.SetImaginary(temp_imaginary);

	return is;
}
/****************************************************************************/
/****************************GET & SET FUNCTIONS*****************************/
/****************************************************************************/
void Complex::SetReal(double re)
{
	m_re = re;
}
/****************************************************************************/
void Complex::SetImaginary(double im)
{
	m_im = im;
}
/****************************************************************************/
double Complex::GetReal() const
{
	return m_re;
}
/****************************************************************************/
double Complex::GetImaginary() const
{
	return m_im;
}
/****************************************************************************/
/***************************STATIC UTIIL FUNCS*******************************/
/****************************************************************************/
static inline double RealResFromMultiply(const Complex &lhs, const Complex &rhs)
{
	return(lhs.GetReal() * rhs.GetReal() -
		   lhs.GetImaginary() * rhs.GetImaginary());
}
/****************************************************************************/
static inline double ImaginaryResFromMultiply(const Complex &lhs,
											  const Complex &rhs)
{
	return(lhs.GetReal() * rhs.GetImaginary() +
		   lhs.GetImaginary() * rhs.GetReal());
}
/****************************************************************************/
static inline double RealResFromDivision(const Complex &lhs, const Complex &rhs)
{
	return((lhs.GetReal() * rhs.GetReal() +
	 	   lhs.GetImaginary() * rhs.GetImaginary())/GetPoweredMangitude(rhs));
}
/****************************************************************************/
static inline double ImaginaryResFromDivision(const Complex &lhs,
											  const Complex &rhs)
{
	return((lhs.GetImaginary() * rhs.GetReal() -
	 	   lhs.GetReal() * rhs.GetImaginary())/GetPoweredMangitude(rhs));
}
/****************************************************************************/
static inline double GetPoweredMangitude(const Complex &num)
{
	return(num.GetReal() * num.GetReal() +
		   num.GetImaginary() * num.GetImaginary());
}
/****************************************************************************/
/****************************************************************************/
/****************************************************************************/
}//ilrd_rd100 - end

