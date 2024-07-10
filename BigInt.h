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
   std::string numb; // �������� �����
   bool natural; // ���� ����� �����

public:

   bigNumber(long x = 0); // ����������� �������������� �� long
   bigNumber(const std::string &numb); // ����������� �������������� �� ������
   bigNumber(const bigNumber &BN); // ����������� �����������

   const std::string &getNumb() const; // ��������� �������� �����(��� �����)

   const bool getNatural() const; // ��������� ����� ����� �����
   void setNatural(bool natural); // ��������� ����� ����� �����

   int sign() const; // ��������� ����� �����
   
   // �������� ���������
   friend const bool operator==(const bigNumber &BN1,const bigNumber &BN2);
   friend const bool operator<(const bigNumber &BN1,const bigNumber &BN2);

   // ������� �����
   //bigNumber operator-() const &&;

   // �������������� ��������
   friend bigNumber operator+(const bigNumber &BN1,const bigNumber &BN2);
   friend bigNumber operator-(const bigNumber &BN1,const bigNumber &BN2);
   friend bigNumber operator*(const bigNumber &BN1,const bigNumber &BN2);
   friend bigNumber operator/(const bigNumber &BN1,const bigNumber &BN2);
   
   //�������� �����/������
   friend std::ostream &operator<<(std::ostream &stream, const bigNumber &BN); // ����� �����
   friend std::istream &operator>>(std::istream &stream, bigNumber &BN); // ���� �����
};
// �������� ������������ ��������
inline bigNumber &operator+=(bigNumber &BN1,const bigNumber &BN2)
{
   return BN1 = BN1 + BN2;
}

// �������� ������������ ���������
inline bigNumber &operator-=(bigNumber &BN1,const bigNumber &BN2)
{
   return BN1 = BN1 - BN2;
}

// �������� ������������ ���������
inline bigNumber &operator*=(bigNumber &BN1,const bigNumber &BN2)
{
   return BN1 = BN1 * BN2;
}

// �������� ������������ �������
inline bigNumber &operator/=(bigNumber &BN1,const bigNumber &BN2)
{
   return BN1 = BN1 / BN2;
}

// �������� �����������
inline const bool operator!=(const bigNumber &BN1, const bigNumber &BN2)
{
   return !(BN1 == BN2);
}

// �������� ������
inline const bool operator>(const bigNumber &BN1, const bigNumber &BN2)
{
   return !(BN1 < BN2 || BN1 == BN2);
}

// �������� ������ ��� �����
inline const bool operator<=(const bigNumber &BN1, const bigNumber &BN2)
{
   return (BN1 < BN2 || BN1 == BN2);
}

// �������� ������ ��� �����
inline const bool operator>=(const bigNumber &BN1, const bigNumber &BN2)
{
   return (BN1 > BN2 || BN1 == BN2);
}
//AnsiString � string
std::string AtoS(AnsiString AnsiStr);
//BigNumber � AnsiString
AnsiString BNtoA(bigNumber BN);
