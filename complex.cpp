#include <iostream>
#include <windows.h>
#include <limits>
#include <cmath>
using namespace std;
///Эта функция очищает поток ввода, если пользователь
///вводит ерись, когда его просят ввести что-то с консоли.
void cl(){
if (std::cin.fail())std::cin.clear();// проверяем состояние потока и сбрасываем если сломан
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // сбрасываем буфер
}

class Complex{
private:
    double real;
    double imeg;
public:
///Конструкторы
Complex(): real(1), imeg(1){}
Complex(double r,double i): real(r), imeg(i){}
//#####################################################

///Перегрузка cin
friend istream& operator>> (istream& strm, Complex cx1){
cout << "Введите действительную часть числа: "; strm >> cx1.real;
cout << "Ведите коэф. мнимой части числа: "; strm >> cx1.imeg;
return strm;
}

///Перегрузка cout
 friend  ostream& operator<< (ostream&  strm,Complex cx1){
  if (cx1.real!=0){                                          //Вывод:
    if(cx1.imeg==0)strm<<cx1.real;                           //"a"
    else if(cx1.imeg==1)strm<<cx1.real<< " + "<<"i";         //"a + i"
    else if(cx1.imeg==-1)strm<<cx1.real<<" - "<<"i";         //"a - i"
    else if(cx1.imeg>0)strm<<cx1.real<< " + "<<cx1.imeg<<"i";//"a + bi"
    else strm<<cx1.real<< " - "<<(cx1.imeg*-1)<<"i";         //"a - bi"
  }
  else{
   if(cx1.imeg==0)strm<< "0";                                //"0"
    else if(cx1.imeg==1)strm<<"i";                           //"i"
    else if(cx1.imeg==-1)strm<<"-i";                         //"-i"
    else strm<<cx1.imeg<<"i";                                //"bi"
  }
return strm;
 }

//#####################################################
/// Арифметика
//C целым числом
  Complex operator+ (int n) const{return Complex(real + n,imeg);}
  Complex operator- (int n) const{return Complex(real - n,imeg);}
  Complex operator* (int n) const{return Complex(real * n,imeg * n);}
  Complex operator/ (int n) const{return Complex(real/n,imeg/n);}

//C вещественным числом
  Complex operator+ (double n) const{return Complex(real + n,imeg);}
  Complex operator- (double n) const{return Complex(real - n,imeg);}
  Complex operator* (double n) const{return Complex(real * n,imeg * n);}
  Complex operator/ (double n) const{return Complex(real/n,imeg/n);}

//С комплексным числом
  Complex operator+ (Complex cx2) const{
    return Complex(real + cx2.real,imeg+cx2.imeg);
  }
  Complex operator- (Complex cx2) const{
    return Complex(real - cx2.real,imeg-cx2.imeg);
  }
  Complex operator* (Complex cx2) const{
    return Complex( (real*cx2.real - imeg*cx2.imeg),(imeg*cx2.real + real*cx2.imeg) );
  }
  Complex operator/ (Complex cx2) const{
      double denum = pow(cx2.real,2) + pow(cx2.imeg,2);
      return Complex( (real*cx2.real + imeg*cx2.imeg)/denum,
                      (imeg*cx2.real - real*cx2.imeg)/denum );
  }

};

int main()
{
Complex cx1, cx2(3, -5);
cout<<cx1<<" | "<<cx2<< endl;
cout<<"1) "<< cx2 + cx1 << endl;
cout<<"2) "<< cx2 - cx1 << endl;
cout<<"3) "<< cx2 * cx1 << endl;
cout<<"4) "<< cx2 / cx1 << endl;
    return 0;
}
