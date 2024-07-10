#include "BigInt.h"

// конструктор преобразования из long
bigNumber::bigNumber(long x) 
{
   this->natural = x < 0;
   this->numb = patch::to_string(natural ? -x : x);
   
   
}

// конструктор преобразования из строки
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

   // определяем число ведущих нулей в строке
   int count = 0;
   while (this->numb[count] == '0' && this->numb.length() - count > 1)
      count++;

   this->numb = this->numb.substr(count); // обрезаем все  ведущие нули

   // проверяем каждый символ строки, если есть символы кроме цифр, то выводим исключение
   for (unsigned int i = 0; i < this->numb.length(); i++)
      if (this->numb[i] < '0' || this->numb[i] > '9')
      {
         throw std::out_of_range("Incorrect symbols");
      }
}

// конструктор копирования
bigNumber::bigNumber(const bigNumber &BN) 
{
   this->numb = BN.getNumb();
   this->natural = BN.getNatural();
}

// получение значения числа(без знака)
const std::string &bigNumber::getNumb() const 
{
   return numb;
}

// получение флага отрицательности числа
const bool bigNumber::getNatural() const 
{
   return natural;
}

// изменение флага отрицательности числа
void bigNumber::setNatural(bool natural) 
{
   this->natural = natural;
}

// получение знака числа
int bigNumber::sign() const 
{
   return (1 - 2 * natural) * (numb != "0");
}

// оператор равенства
const bool operator==(const bigNumber &BN21,const bigNumber &BN2)
{
   return (BN21.numb == BN2.numb) && (BN21.natural == BN2.natural);
}

// оператор меньше
const bool operator<(const bigNumber &BN21,const bigNumber &BN2)
{
   std::string value2 = BN2.numb; 
   int len1 = BN21.numb.length(); 
   int len2 = value2.length(); 

   if (BN21.natural == BN2.natural) 
      {
      if (len1 != len2)
         return (len1 < len2) ^ BN21.natural; // меньше число с меньшей длинной для положительных и с большей длиной для отрицательных

      int i = 0;

      // ищем разряд, в котором значения отличаются
      while (i < len1 && BN21.numb[i] == value2[i])
         i++;

      // если разряд найден, то меньше число с меньшей цифрой для положительных и с большей цифрой для отрицательных, иначе числа равны
      return (i < len1) && ((BN21.numb[i] < value2[i]) ^ BN21.natural);
   }

   return BN21.natural; // знаки разные, если число отрицательное, то оно меньше, если положительное, то больше
}

// унарный минус(поменять знак числа)
/*
bigNumber bigNumber::operator-() const &&
{
   return bigNumber(natural ? numb : std::string("-") + numb);
}  */

// оператор сложения
bigNumber operator+(const bigNumber &BN21, const bigNumber &BN2)
{
   if (!(BN2.getNatural() ^ BN21.natural)) // если знаки одинаковые, то выполняем сложение
   {
	  std::string num2 = BN2.getNumb(); // запоминаем значение второго числа

      int len1 = BN21.numb.length(); // запоминаем длину первого числа
      int len2 = num2.length(); // запоминаем длину второго числа
      int length = 1 + std::max(len1, len2);  // длина суммы равна максимуму из двух длин + 1 из-за возможного переноса разряда

	  char *res; // строка для выполнения операции сложения
	  res = new char[length + 1];

      res[length - 1] = res[length] = '\0';

      for (int i = 0; i < length - 1; i++) 
      {
		 int j = length - 1 - i;
         res[j] += ((i < len2) ? (num2[len2 - 1 - i] - '0') : 0) + ((i < len1) ? (BN21.numb[len1 - 1 - i] - '0') : 0); // выполняем сложение разрядов
         res[j - 1] = res[j] / 10; // выполняем перенос в следущий разряд, если он был
         res[j] = res[j] % 10 + '0'; // оставляем только единицы от возможного переноса и превращаем символ в цифру
      }

	  res[0] += '0';
	  std::string out;
	  if (BN21.natural)
		 out = std::string("-") + std::string(res);
	  else
		 out = std::string(res);
	  return bigNumber(out);
	  //return bigNumber(BN21.natural ? std::string("-") + std::string(res) : std::string(res)); // возвращаем результат, в зависимости от знака`
   }
   else// одно из чисел отрицательное, а другое положительное, отправляем на вычитание, меняя знак
	  return BN21.natural ? (BN2 - (bigNumber(BN21) * (-1))) : (BN21 - (bigNumber(BN2) * (-1)));
}

// оператор вычитания
bigNumber operator-(const bigNumber &BN21,const bigNumber &BN2)
{
   if (BN21 == BN2)
	  return 0; // если числа равны, то возвращаем 0

   // если оба числа положительные, то выполняем вычитание
   if (!BN21.natural && !BN2.natural) 
      {
      std::string value2 = BN2.numb; // запоминаем значение второго числа

      int len1 = BN21.numb.length(); // запоминаем длину первого числа
      int len2 = value2.length(); // запоминаем длину второго числа
      int len = std::max(len1, len2); // длина результата не превысит максимума длин чисел

      bool result_sign = BN2 > BN21; // определяем знак результата

	  //int a[len], b[len]; // массивы аргументов
	  int *a, *b;
	  a = new int[len];
	  b = new int[len];
      a[0] = 0;// обнуляем нулевые элементы массивов
      b[0] = 0; 

	  //char res[len + 1]; // строковый массив для результата
	  char *res;
	  res = new char[len + 1];

      res[len - 1] = '\0'; // устанавливаем символ окончания строки
      res[len] = '\0'; 

      int sign = (2 * result_sign - 1); // получаем знак результата операции

      for (int i = 0; i < len - 1; i++) 
         {
         a[i] += (i < len1) ? (BN21.numb[len1 - 1 - i] - '0') : 0; // формируем разряды из строк аргументов
         b[i] += (i < len2) ? (value2[len2 - 1 - i] - '0') : 0;

         b[i + 1] = -result_sign; // в зависимости от знака занимаем или не занимаем 10 у следующего разряда
         a[i + 1] = result_sign- 1; 

         res[len - 1 - i] += 10 + sign * (b[i] - a[i]);
         res[len - 1 - i - 1]  = res[len - 1 - i] / 10;
         res[len - 1 - i] = res[len - 1 - i] % 10 + '0';
      }

      // выполняем операцию с последним разрядом
      a[len - 1] += (len - 1 < len1) * (BN21.numb[0] - '0');
      b[len - 1] += (len - 1 < len2) * (value2[0] - '0');

      // записываем в строку последний разряд
	  res[0] += sign * (b[len - 1] - a[len - 1]) + '0';

	  std::string out;
	  if(result_sign)
		  out = std::string("-") + std::string(res);
	  else
		  out = std::string(res);
	  return out;
	  //return bigNumber(result_sign ? std::string("-") + std::string(res) : std::string(res)); // возвращаем результат, учитывая знак
   } 
   else // если оба числа отрицательные, то меняем местами, меняем знаки и повторяем вычитание, а если знаки разные, то отправляем на сумму
	  return BN21.natural && BN2.natural ? ((bigNumber(BN2) * (-1)) - (bigNumber(BN21) * (-1))) : (BN21 + (bigNumber(BN2) * (-1)));
}

// оператор умножения
bigNumber operator*(const bigNumber &BN21,const bigNumber &BN2)
{
   if (BN21.numb == "0" || BN2.getNumb() == "0")
      return 0; // если один из множителей равен нулю, то результат равен нулю

   std::string numb2 = BN2.numb; // запоминаем значение второго числа

   int len1 = BN21.numb.length(); // запоминаем длину первого числа
   int len2 = numb2.length(); // запоминаем длину второго числа
   int length = len1 + len2 + 1; // резульат влезет в сумму длин + 1 из-за возможного переноса
   bool result_sign = BN21.natural ^ BN2.natural; // флаг отрицательности результата - отрицательный, если числа разных знаков

   if (length < 10) // умножаем как обычный long
   {
	  const char* c_1 = BN21.numb.c_str();
	  const char* c_2 = numb2.c_str();
	  long res = std::atoi(c_1) * std::atoi(c_2);
	  //long res = stol(BN21.numb) * stol(numb2);
	  return bigNumber(result_sign ? -res : res);
   }
   else // умножаем в столбик
   {
	  //int a[length], b[length]; // массивы аргументов и результата
	  int *a, *b;
	  a = new int[length];
	  b = new int[length];

	  //char res[length + 1]; // строковый массив для результата
	  char *res;
	  res = new char[length + 1];

      res[length] = '\0'; // устанавливаем символ окончания строки

      // заполняем массивы записью чисел с ведущими нулями
      for (int i = 0; i < length; i++) 
      {
         a[i] = (i < len1) ? (BN21.numb[len1 - 1 - i] - '0') : 0;
         b[i] = (i < len2) ? (numb2[len2 - 1 - i] - '0') : 0;
         res[i] = 0;
      }

	  // выполняем умножение
	  for (int i = 0; i < len1; i++)
	  {
         for (int j = 0; j < len2; j++) 
		 {
            res[length - 1 - (i + j)] += a[i] * b[j];
			res[length - 1 - (i + j + 1)] += res[length - 1 - (i + j)] / 10;
            res[length - 1 - (i + j)] %= 10;
         }
      }

      // переписываем результат в строку
      for (int i = 0; i < length; i++)
		 res[length - 1 - i] += '0';

	  std::string out;

	  if (result_sign)
		 out = std::string("-") + std::string(res);
	  else
		 out = std::string(res);
	  return out;
	  //return bigNumber(result_sign ? std::string("-") + std::string(res) : std::string(res)); // возвращаем результат, учитывая его знак
   }
}

// оператор деления
bigNumber operator/(const bigNumber &BN21,const bigNumber &BN2)
{
   std::string numb1 = BN21.numb;
   std::string numb2 = BN2.numb; // запоминаем значение второго числа

   if (numb2[0] == '0')
   {
      throw std::out_of_range("Division by zero!");
   }
   if (BN21.numb[0] == '0')// делить ноль на что угодно нет смысла
      return 0; 

   if (numb2 == "1")
	  return bigNumber(BN2.natural ? (bigNumber(BN21) * (-1)) : BN21); // делить на 1 нет смысла

   int zeroCnt = 0;
   while (numb2[numb2.length() - 1 - zeroCnt] == '0')
      zeroCnt++;

   // избавляемся от круглых чисел
   if (zeroCnt) 
   {
      numb1 = numb1.substr(0, numb1.length() - zeroCnt);
      numb2 = numb2.substr(0, numb2.length() - zeroCnt);
   }

   bool result_sign = BN21.natural ^ BN2.getNatural(); // считаем знак результата

   bigNumber tmp(numb2);

   int del_length = numb2.length(); // запоминаем длину делителя
   long divider_prom = del_length > 8 ? 0 : std::atoi(numb2.c_str()); // если длина больше 8, то обнуляем long'овый делитель, иначе переводим строку в long

   int length = numb1.length(); // получаем длину делимого
   int index = 0; // стартуем с нулевого индекса

   std::string del; // строка результата деления
   std::string prom; // строка промежуточного результата

   // формируем число для деления
   while (bigNumber(prom) < tmp && index < length)
      prom += numb1[index++];

   do 
   {
      int count = 0; // результат деления подчисла на делитель

      // если можем разделить, то делим
      if (bigNumber(prom) >= tmp) 
      {
         if (del_length > 8) // если не входит в long, то делим с помощью вычитания
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

      del += count + '0'; // если не делили, то добавили ноль к результату, иначе добавили результат деления

      if (index <= length)
         prom += numb1[index++]; // формируем новое значение для промежуточного результата
   } while (index <= length);

   return bigNumber(result_sign && del != "0" ? std::string("-") + del : del); // возвращаем результат учитывая знак и возможное равенство нулю
}


// оператор вывода
std::ostream &operator<<(std::ostream &out, const bigNumber &BN) {
   if (BN.getNatural())
      out << "-";
   out << BN.getNumb();
   return out;
}

// оператор ввода
std::istream &operator>>(std::istream &in, bigNumber &BN) {
   std::string numb;
   in >> numb;
   BN = bigNumber(numb);
   return in;
}
//AnsiString в string
std::string AtoS(AnsiString AnsiStr)
{
	char *s;
	s = new char[AnsiStr.Length() + 2];
	strcpy(s,AnsiStr.c_str());
	std::string str = s;
	return str;
}
//BigNumber в AnsiString
AnsiString BNtoA(bigNumber BN)
{
	AnsiString out;
	if(BN.getNatural())
		out = (std::string("-") + BN.getNumb()).c_str();
	else
		out = (BN.getNumb()).c_str();
	return out;
}

