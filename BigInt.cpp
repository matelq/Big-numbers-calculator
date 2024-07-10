#include "BigInt.h"

// ����������� �������������� �� long
bigNumber::bigNumber(long x) 
{
   this->natural = x < 0;
   this->numb = patch::to_string(natural ? -x : x);
   
   
}

// ����������� �������������� �� ������
bigNumber::bigNumber(const std::string &numb) 
{
   if (!numb.length()) 
   {
      this->numb = "0";
      natural = false;
      return;
   }

   natural = numb[0] == '-';
   this->numb = numb.substr(natural);

   // ���������� ����� ������� ����� � ������
   int count = 0;
   while (this->numb[count] == '0' && this->numb.length() - count > 1)
      count++;

   this->numb = this->numb.substr(count); // �������� ���  ������� ����

   // ��������� ������ ������ ������, ���� ���� ������� ����� ����, �� ������� ����������
   for (unsigned int i = 0; i < this->numb.length(); i++)
      if (this->numb[i] < '0' || this->numb[i] > '9')
      {
         throw std::out_of_range("Incorrect symbols");
      }
}

// ����������� �����������
bigNumber::bigNumber(const bigNumber &BN) 
{
   this->numb = BN.getNumb();
   this->natural = BN.getNatural();
}

// ��������� �������� �����(��� �����)
const std::string &bigNumber::getNumb() const 
{
   return numb;
}

// ��������� ����� ��������������� �����
const bool bigNumber::getNatural() const 
{
   return natural;
}

// ��������� ����� ��������������� �����
void bigNumber::setNatural(bool natural) 
{
   this->natural = natural;
}

// ��������� ����� �����
int bigNumber::sign() const 
{
   return (1 - 2 * natural) * (numb != "0");
}

// �������� ���������
const bool operator==(const bigNumber &BN21,const bigNumber &BN2)
{
   return (BN21.numb == BN2.numb) && (BN21.natural == BN2.natural);
}

// �������� ������
const bool operator<(const bigNumber &BN21,const bigNumber &BN2)
{
   std::string value2 = BN2.numb; 
   int len1 = BN21.numb.length(); 
   int len2 = value2.length(); 

   if (BN21.natural == BN2.natural) 
      {
      if (len1 != len2)
         return (len1 < len2) ^ BN21.natural; // ������ ����� � ������� ������� ��� ������������� � � ������� ������ ��� �������������

      int i = 0;

      // ���� ������, � ������� �������� ����������
      while (i < len1 && BN21.numb[i] == value2[i])
         i++;

      // ���� ������ ������, �� ������ ����� � ������� ������ ��� ������������� � � ������� ������ ��� �������������, ����� ����� �����
      return (i < len1) && ((BN21.numb[i] < value2[i]) ^ BN21.natural);
   }

   return BN21.natural; // ����� ������, ���� ����� �������������, �� ��� ������, ���� �������������, �� ������
}

// ������� �����(�������� ���� �����)
/*
bigNumber bigNumber::operator-() const &&
{
   return bigNumber(natural ? numb : std::string("-") + numb);
}  */

// �������� ��������
bigNumber operator+(const bigNumber &BN21, const bigNumber &BN2)
{
   if (!(BN2.getNatural() ^ BN21.natural)) // ���� ����� ����������, �� ��������� ��������
   {
	  std::string num2 = BN2.getNumb(); // ���������� �������� ������� �����

      int len1 = BN21.numb.length(); // ���������� ����� ������� �����
      int len2 = num2.length(); // ���������� ����� ������� �����
      int length = 1 + std::max(len1, len2);  // ����� ����� ����� ��������� �� ���� ���� + 1 ��-�� ���������� �������� �������

	  char *res; // ������ ��� ���������� �������� ��������
	  res = new char[length + 1];

      res[length - 1] = res[length] = '\0';

      for (int i = 0; i < length - 1; i++) 
      {
		 int j = length - 1 - i;
         res[j] += ((i < len2) ? (num2[len2 - 1 - i] - '0') : 0) + ((i < len1) ? (BN21.numb[len1 - 1 - i] - '0') : 0); // ��������� �������� ��������
         res[j - 1] = res[j] / 10; // ��������� ������� � �������� ������, ���� �� ���
         res[j] = res[j] % 10 + '0'; // ��������� ������ ������� �� ���������� �������� � ���������� ������ � �����
      }

	  res[0] += '0';
	  std::string out;
	  if (BN21.natural)
		 out = std::string("-") + std::string(res);
	  else
		 out = std::string(res);
	  return bigNumber(out);
	  //return bigNumber(BN21.natural ? std::string("-") + std::string(res) : std::string(res)); // ���������� ���������, � ����������� �� �����`
   }
   else// ���� �� ����� �������������, � ������ �������������, ���������� �� ���������, ����� ����
	  return BN21.natural ? (BN2 - (bigNumber(BN21) * (-1))) : (BN21 - (bigNumber(BN2) * (-1)));
}

// �������� ���������
bigNumber operator-(const bigNumber &BN21,const bigNumber &BN2)
{
   if (BN21 == BN2)
	  return 0; // ���� ����� �����, �� ���������� 0

   // ���� ��� ����� �������������, �� ��������� ���������
   if (!BN21.natural && !BN2.natural) 
      {
      std::string value2 = BN2.numb; // ���������� �������� ������� �����

      int len1 = BN21.numb.length(); // ���������� ����� ������� �����
      int len2 = value2.length(); // ���������� ����� ������� �����
      int len = std::max(len1, len2); // ����� ���������� �� �������� ��������� ���� �����

      bool result_sign = BN2 > BN21; // ���������� ���� ����������

	  //int a[len], b[len]; // ������� ����������
	  int *a, *b;
	  a = new int[len];
	  b = new int[len];
      a[0] = 0;// �������� ������� �������� ��������
      b[0] = 0; 

	  //char res[len + 1]; // ��������� ������ ��� ����������
	  char *res;
	  res = new char[len + 1];

      res[len - 1] = '\0'; // ������������� ������ ��������� ������
      res[len] = '\0'; 

      int sign = (2 * result_sign - 1); // �������� ���� ���������� ��������

      for (int i = 0; i < len - 1; i++) 
         {
         a[i] += (i < len1) ? (BN21.numb[len1 - 1 - i] - '0') : 0; // ��������� ������� �� ����� ����������
         b[i] += (i < len2) ? (value2[len2 - 1 - i] - '0') : 0;

         b[i + 1] = -result_sign; // � ����������� �� ����� �������� ��� �� �������� 10 � ���������� �������
         a[i + 1] = result_sign- 1; 

         res[len - 1 - i] += 10 + sign * (b[i] - a[i]);
         res[len - 1 - i - 1]  = res[len - 1 - i] / 10;
         res[len - 1 - i] = res[len - 1 - i] % 10 + '0';
      }

      // ��������� �������� � ��������� ��������
      a[len - 1] += (len - 1 < len1) * (BN21.numb[0] - '0');
      b[len - 1] += (len - 1 < len2) * (value2[0] - '0');

      // ���������� � ������ ��������� ������
	  res[0] += sign * (b[len - 1] - a[len - 1]) + '0';

	  std::string out;
	  if(result_sign)
		  out = std::string("-") + std::string(res);
	  else
		  out = std::string(res);
	  return out;
	  //return bigNumber(result_sign ? std::string("-") + std::string(res) : std::string(res)); // ���������� ���������, �������� ����
   } 
   else // ���� ��� ����� �������������, �� ������ �������, ������ ����� � ��������� ���������, � ���� ����� ������, �� ���������� �� �����
	  return BN21.natural && BN2.natural ? ((bigNumber(BN2) * (-1)) - (bigNumber(BN21) * (-1))) : (BN21 + (bigNumber(BN2) * (-1)));
}

// �������� ���������
bigNumber operator*(const bigNumber &BN21,const bigNumber &BN2)
{
   if (BN21.numb == "0" || BN2.getNumb() == "0")
      return 0; // ���� ���� �� ���������� ����� ����, �� ��������� ����� ����

   std::string numb2 = BN2.numb; // ���������� �������� ������� �����

   int len1 = BN21.numb.length(); // ���������� ����� ������� �����
   int len2 = numb2.length(); // ���������� ����� ������� �����
   int length = len1 + len2 + 1; // �������� ������ � ����� ���� + 1 ��-�� ���������� ��������
   bool result_sign = BN21.natural ^ BN2.natural; // ���� ��������������� ���������� - �������������, ���� ����� ������ ������

   if (length < 10) // �������� ��� ������� long
   {
	  const char* c_1 = BN21.numb.c_str();
	  const char* c_2 = numb2.c_str();
	  long res = std::atoi(c_1) * std::atoi(c_2);
	  //long res = stol(BN21.numb) * stol(numb2);
	  return bigNumber(result_sign ? -res : res);
   }
   else // �������� � �������
   {
	  //int a[length], b[length]; // ������� ���������� � ����������
	  int *a, *b;
	  a = new int[length];
	  b = new int[length];

	  //char res[length + 1]; // ��������� ������ ��� ����������
	  char *res;
	  res = new char[length + 1];

      res[length] = '\0'; // ������������� ������ ��������� ������

      // ��������� ������� ������� ����� � �������� ������
      for (int i = 0; i < length; i++) 
      {
         a[i] = (i < len1) ? (BN21.numb[len1 - 1 - i] - '0') : 0;
         b[i] = (i < len2) ? (numb2[len2 - 1 - i] - '0') : 0;
         res[i] = 0;
      }

	  // ��������� ���������
	  for (int i = 0; i < len1; i++)
	  {
         for (int j = 0; j < len2; j++) 
		 {
            res[length - 1 - (i + j)] += a[i] * b[j];
			res[length - 1 - (i + j + 1)] += res[length - 1 - (i + j)] / 10;
            res[length - 1 - (i + j)] %= 10;
         }
      }

      // ������������ ��������� � ������
      for (int i = 0; i < length; i++)
		 res[length - 1 - i] += '0';

	  std::string out;

	  if (result_sign)
		 out = std::string("-") + std::string(res);
	  else
		 out = std::string(res);
	  return out;
	  //return bigNumber(result_sign ? std::string("-") + std::string(res) : std::string(res)); // ���������� ���������, �������� ��� ����
   }
}

// �������� �������
bigNumber operator/(const bigNumber &BN21,const bigNumber &BN2)
{
   std::string numb1 = BN21.numb;
   std::string numb2 = BN2.numb; // ���������� �������� ������� �����

   if (numb2[0] == '0')
   {
      throw std::out_of_range("Division by zero!");
   }
   if (BN21.numb[0] == '0')// ������ ���� �� ��� ������ ��� ������
      return 0; 

   if (numb2 == "1")
	  return bigNumber(BN2.natural ? (bigNumber(BN21) * (-1)) : BN21); // ������ �� 1 ��� ������

   int zeroCnt = 0;
   while (numb2[numb2.length() - 1 - zeroCnt] == '0')
      zeroCnt++;

   // ����������� �� ������� �����
   if (zeroCnt) 
   {
      numb1 = numb1.substr(0, numb1.length() - zeroCnt);
      numb2 = numb2.substr(0, numb2.length() - zeroCnt);
   }

   bool result_sign = BN21.natural ^ BN2.getNatural(); // ������� ���� ����������

   bigNumber tmp(numb2);

   int del_length = numb2.length(); // ���������� ����� ��������
   long divider_prom = del_length > 8 ? 0 : std::atoi(numb2.c_str()); // ���� ����� ������ 8, �� �������� long'���� ��������, ����� ��������� ������ � long

   int length = numb1.length(); // �������� ����� ��������
   int index = 0; // �������� � �������� �������

   std::string del; // ������ ���������� �������
   std::string prom; // ������ �������������� ����������

   // ��������� ����� ��� �������
   while (bigNumber(prom) < tmp && index < length)
      prom += numb1[index++];

   do 
   {
      int count = 0; // ��������� ������� �������� �� ��������

      // ���� ����� ���������, �� �����
      if (bigNumber(prom) >= tmp) 
      {
         if (del_length > 8) // ���� �� ������ � long, �� ����� � ������� ���������
         { 
            bigNumber mod = prom;

            while (mod >= tmp) 
            {
               mod -= tmp;
               count++;
            }

            prom = mod.numb;
         } 
         else 
		 {
			const char* c_prom = prom.c_str();
			long mod = std::atoi(c_prom);
			//long mod = stol(prom);
            count = mod / divider_prom;
			prom = patch::to_string(mod % divider_prom);
         }
      }

      del += count + '0'; // ���� �� ������, �� �������� ���� � ����������, ����� �������� ��������� �������

      if (index <= length)
         prom += numb1[index++]; // ��������� ����� �������� ��� �������������� ����������
   } while (index <= length);

   return bigNumber(result_sign && del != "0" ? std::string("-") + del : del); // ���������� ��������� �������� ���� � ��������� ��������� ����
}


// �������� ������
std::ostream &operator<<(std::ostream &out, const bigNumber &BN) {
   if (BN.getNatural())
      out << "-";
   out << BN.getNumb();
   return out;
}

// �������� �����
std::istream &operator>>(std::istream &in, bigNumber &BN) {
   std::string numb;
   in >> numb;
   BN = bigNumber(numb);
   return in;
}
//AnsiString � string
std::string AtoS(AnsiString AnsiStr)
{
	char *s;
	s = new char[AnsiStr.Length() + 2];
	strcpy(s,AnsiStr.c_str());
	std::string str = s;
	return str;
}
//BigNumber � AnsiString
AnsiString BNtoA(bigNumber BN)
{
	AnsiString out;
	if(BN.getNatural())
		out = (std::string("-") + BN.getNumb()).c_str();
	else
		out = (BN.getNumb()).c_str();
	return out;
}

