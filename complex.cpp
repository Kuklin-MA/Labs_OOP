#include <iostream>
#include <windows.h>
#include <limits>
#include <cmath>
using namespace std;
///��� ������� ������� ����� �����, ���� ������������
///������ �����, ����� ��� ������ ������ ���-�� � �������.
void cl(){
if (std::cin.fail())std::cin.clear();// ��������� ��������� ������ � ���������� ���� ������
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���������� �����
}

class Complex{
private:
    double real;
    double imeg;
    double mdls (){
    return sqrt(pow(real,2)+pow(imeg,2));
    }
//    double mdls (double real,double imeg){
//    return sqrt(pow(real,2)+pow(imeg,2));
//    }
public:
///������������
Complex(): real(1), imeg(1){}
Complex(double r,double i): real(r), imeg(i){}
Complex(double i): real(i), imeg(0){}
//#####################################################

///���������� cin
friend istream& operator>> (istream& strm, Complex cx1){
cout << "������� �������������� ����� �����: "; strm >> cx1.real;
cout << "������ ����. ������ ����� �����: "; strm >> cx1.imeg;
return strm;
}

///���������� cout
 friend  ostream& operator<< (ostream&  strm,Complex cx1){
  if (cx1.real!=0){                                          //�����:
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
/// ����������
//C ������������(�����) ������
  Complex operator+ (double n) const{return Complex(real + n,imeg);}
  Complex operator- (double n) const{return Complex(real - n,imeg);}
  Complex operator* (double n) const{return Complex(real * n,imeg * n);}
  Complex operator/ (double n) const{return Complex(real/n,imeg/n);}

//� ����������� ������
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

//#####################################################
/// ������
//� ������������(�����) ������
bool operator> (double n){return this->mdls()>n;}
bool operator< (double n){return this->mdls()<n;}
bool operator>= (double n){return this->mdls()>=n;}
bool operator<= (double n){return this->mdls()<=n;}
bool operator== (double n){return this->mdls()==n;}
bool operator!= (double n){return this->mdls()!=n;}

//� ����������� ������
bool operator> (Complex cx2){return this->mdls()> cx2.mdls();}
bool operator< (Complex cx2){return this->mdls()< cx2.mdls();}
bool operator>= (Complex cx2){return this->mdls()>= cx2.mdls();}
bool operator<= (Complex cx2){return this->mdls()<= cx2.mdls();}
bool operator==(Complex cx2){return this->mdls()== cx2.mdls();}
bool operator!=(Complex cx2){return this->mdls()!=cx2.mdls();}

//#####################################################
///�������������
////����������
Complex operator++ (){
return real++;
}
////�����������
Complex operator++ (int){
return imeg++;
}

///�������������
////����������
Complex operator-- (){
return real--;
}
////�����������
Complex operator-- (int){
return imeg--;
}

//#####################################################
///���������� ����� (conjugate number)
Complex get_conj_number(Complex cx1){return Complex(real,imeg*-1);}

//#####################################################
///������� � ������������������ ����� (Trigonometry)
void out_trig (){
    // acos(-1.0) - ��� pi
    if(real==0)
        if(imeg<0)cout<<this->mdls()<<"*(cos("<< -acos(-1.0)/2
                                  <<") + isin("<<-acos(-1.0)/2<<"))"<<endl;

        else
        cout<<this->mdls()<<"*(cos("<< acos(-1.0)/2
                                  <<") + isin("<<acos(-1.0)/2<<"))"<<endl;


    else
        if(real>0)
        cout<<this->mdls()<<"*(cos("<<atan(imeg/real)
            <<") + isin("<<atan(imeg/real)<<"))"<<endl;

        else cout<<this->mdls()<<"*(cos("<<atan(imeg/real) - acos(-1.0)
                 <<") + isin("<<atan(imeg/real) - acos(-1.0)<<"))"<<endl;


}

//#####################################################
///�������� � ������� (Raise to the power)
Complex cx_pow (double n){
    if(real==0)
        if(fmod(n,2)==0) return Complex(pow(this->mdls(),n)*-1,0);
        else return Complex(0,pow(this->mdls(),n));
    else
        if(real>0)
        return Complex (pow(this->mdls(),n)*cos(atan(imeg/real)*n),
               pow(this->mdls(),n)*sin(atan(imeg/real)*n));

        // acos(-1.0) - ��� pi
        else
        return Complex(pow(this->mdls(),n)*cos((atan(imeg/real) - acos(-1.0))*n),
               pow(this->mdls(),n)*sin((atan(imeg/real) - acos(-1.0))*n));
}
//#####################################################
///���������� ����� n-������� (sqrt ��� s)
Complex cx_qrt (double n){
    if(real==0)
        if(imeg>0) return Complex(pow(this->mdls(),1/n)*cos(acos(-1.0)/(2*n)),
                                  pow(this->mdls(),1/n)*sin(acos(-1.0)/(2*n)) );
        else return Complex(pow(this->mdls(),1/n)*cos(-acos(-1.0)/(2*n)),
                            pow(this->mdls(),1/n)*sin(-acos(-1.0)/(2*n)) );
    else return this->cx_pow(1/n);
}
//#####################################################
///������� �������������  ����� (the exponential form of a number)
void out_exp(){
    if(real==0)
        if(imeg>0)cout<<this->mdls()<<"e^i"<<acos(-1.0)/2;
        else cout<<this->mdls()<<"e^i"<<-acos(-1.0)/2;
    else
        if(real>0)cout<<this->mdls()<<"e^i"<<atan(imeg/real);
        else cout<<this->mdls()<<"e^i"<<atan(imeg/real) - acos(-1.0);
}
};


int main()
{
Complex cx1, cx2(3,-4);
cout<<cx1<<" | "<<cx2<< endl;
cout<<"1) "<< cx2 + cx1 << endl;
cout<<"2) "<< cx2 - cx1 << endl;
cout<<"3) "<< cx2 * cx1 << endl;
cout<<"4) "<< cx2 / cx1 << endl;
cout<<"5) "; cx2.out_trig();
cout<<"6) "<< cx2.cx_pow(2)<<endl;
cout<<"7) "<< cx2.cx_qrt(2)<<endl;
cout<<"8) "; cx2.out_exp();
    return 0;
}
