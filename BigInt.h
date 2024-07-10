#include <string>
#include <sstream>
#include <vcl.h>
#include <iostream>
#include <cmath>
#include <exception>
#include <stdexcept>

namespace patch
{
	template < typename T > std::string to_string( const T& n )
	{
		std::ostringstream stm ;
		stm << n ;
		return stm.str() ;
	}
}

class bigNumber {
   std::string numb; // значение числа
   bool natural; // флаг знака числа

public:

   bigNumber(long x = 0); // конструктор преобразования из long
   bigNumber(const std::string &numb); // конструктор преобразования из строки
   bigNumber(const bigNumber &BN); // конструктор копирования

   const std::string &getNumb() const; // получение значения числа(без знака)

   const bool getNatural() const; // получение флага знака числа
   void setNatural(bool natural); // установка флага знака числа

   int sign() const; // получение знака числа
   
   // операции сравнения
   friend const bool operator==(const bigNumber &BN1,const bigNumber &BN2);
   friend const bool operator<(const bigNumber &BN1,const bigNumber &BN2);

   // унарный минус
   //bigNumber operator-() const &&;

   // арифметические операции
   friend bigNumber operator+(const bigNumber &BN1,const bigNumber &BN2);
   friend bigNumber operator-(const bigNumber &BN1,const bigNumber &BN2);
   friend bigNumber operator*(const bigNumber &BN1,const bigNumber &BN2);
   friend bigNumber operator/(const bigNumber &BN1,const bigNumber &BN2);
   
   //операции ввода/вывода
   friend std::ostream &operator<<(std::ostream &stream, const bigNumber &BN); // вывод числа
   friend std::istream &operator>>(std::istream &stream, bigNumber &BN); // ввод числа
};
// оператор сокращенного сложения
inline bigNumber &operator+=(bigNumber &BN1,const bigNumber &BN2)
{
   return BN1 = BN1 + BN2;
}

// оператор сокращенного вычитания
inline bigNumber &operator-=(bigNumber &BN1,const bigNumber &BN2)
{
   return BN1 = BN1 - BN2;
}

// оператор сокращенного умножения
inline bigNumber &operator*=(bigNumber &BN1,const bigNumber &BN2)
{
   return BN1 = BN1 * BN2;
}

// оператор сокращенного деления
inline bigNumber &operator/=(bigNumber &BN1,const bigNumber &BN2)
{
   return BN1 = BN1 / BN2;
}

// оператор неравенства
inline const bool operator!=(const bigNumber &BN1, const bigNumber &BN2)
{
   return !(BN1 == BN2);
}

// оператор больше
inline const bool operator>(const bigNumber &BN1, const bigNumber &BN2)
{
   return !(BN1 < BN2 || BN1 == BN2);
}

// оператор меньше или равно
inline const bool operator<=(const bigNumber &BN1, const bigNumber &BN2)
{
   return (BN1 < BN2 || BN1 == BN2);
}

// оператор больше или равно
inline const bool operator>=(const bigNumber &BN1, const bigNumber &BN2)
{
   return (BN1 > BN2 || BN1 == BN2);
}
//AnsiString в string
std::string AtoS(AnsiString AnsiStr);
//BigNumber в AnsiString
AnsiString BNtoA(bigNumber BN);
