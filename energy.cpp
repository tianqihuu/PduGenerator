#include "head.h"
double B_muon()
{
    double b=0.8;
    double m=105.659;
    double y=1000;
    double c=pow(10,10)*3.0;
    double t=2.2*pow(10,-6);
    double rho=0.00123;

    double up;
    double down;
    double result;

    up=b*m*y*c;
    down=t*rho;

    return result=up/down;
}

double P_muon(double theta,double E_PI)
{
    double a=2.5;
    double y=1000;
    double r=0.76;
    double B=B_muon();

    double index;
    double base;

    base=0.1*cos(theta)*(1-a*(y*(1/cos(theta))-100.0)/r/E_PI);
    index=B/((r*E_PI+100.0*a)*cos(theta));
    
    double result;
    return result=pow(base,index);
}

double N(double* vars,double* pars)
{
    double E_PI=vars[0]+2.5*1000.0*(1/cos(vars[1])-0.1);
    double up;
    double down;
    auto P=P_muon(vars[1],E_PI);

    up=pars[0]*pow(E_PI,-1*pars[1])*P*lambda*b*j;
    down=E_PI*cos(vars[1])+b*j;
    
    double result;
    return result=up/down;
}

int main()//main程序绘制图形
{
    TCanvas* c1=new TCanvas("c1","differential_intensity",1500,1000);
    
return 0;
}

