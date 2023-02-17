#include <stdio.h>            // подключаем заголовочный файл stdio.h


enum TypeDataByte
{
  Byte,
  Work,
  Long
};

float* f00(double x0, double x1) 
{
  float rez = 0.0;
  rez = x0 / x1;
  return &rez;
}

struct MyStruct
{
  enum TypeDataByte type_data;
  unsigned char length;
  union Rezul
  {
    unsigned char byte[4];
    unsigned int word[2];
    unsigned long int _long;
  } rezelt;
};


void f01(struct MyStruct* x)
{
  x->type_data = Byte;
  x->length = 12;
  x->rezelt._long =  1;
}


struct MyStruct* f02(struct MyStruct* x)
{
  x->type_data = Long;
  x ->length = 121;
  x->rezelt._long = 100000000001;
  return x;
}



int main(void)                      // определяем функцию main
{                                   // начало функции
  

  printf("Hello METANIT.COM!\n"); // выводим строку на консоль

  float* x0;
  float x1 = 44.2f;

  x0 = &x1;
  float xx0 = (float)(*x0);
  int xx1 = *x0;

  double d0 = 55.3;
  double* _dprn = &d0;
  double d1 = *_dprn;
  int _ii = (int)*_dprn;
  float f1 = (float)*_dprn;
  float z00 = (float) *f00(10.0, 2.0);
  
  struct MyStruct xx00;
  xx00.length = 222;
  f01(&xx00);
//  enum MyEnum TypeDataByte tp0 = xx00.
//  auto tp0 = xx00.type_data;
  enum TypeDataByte tp0 = xx00.type_data;

  struct MyStruct* zzprn = f02(&xx00);
  int _count = zzprn->length;
  unsigned long int _long0 = zzprn->rezelt._long;
  int hh = 1;

  return 0;                       // выходим из функции
}