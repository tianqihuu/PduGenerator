//数据用TTree保存，一个entry包含一个天顶角，一个方位角，以及相应的能量抽样（用数组保存）
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TRandom.h"

#define PI 3.1415926

double PduGenerator(double* x,double* par)
{
    double Emu=x[0];    //Unit:Gev
    double cosX=cos(par[0]);

    const double lambda=120;     //absorption mean free path 120g/cm^2
    const double Alpha=0.002382; //constant A
    const double gamma=2.645;
    const double b=0.771;
    const double jp=148.16;      
    const double alpha=0.0025;//muon energu loss in Gev/g/cm^2
    const double rho=0.76;//when a pi of energy Ep decays it gives rise to a mu meson of approximate average energy Emu*=0.76Ep
    const double y0=1000;
    const double bm=0.8;
    const double Bm=1.041231831;//correction factor

    //Energy of pion
    double Ep=(1/rho)*(Emu+alpha*y0*(1/cosX-0.1));
    
    //prob. of Muon Production
    double Pmu=0.1*cosX*(1-alpha/rho/Ep*(y0/cosX-0.1));
    Pmu=pow(Pmu,Bm/(rho*Ep+100*alpha)/cosX);

    double numerator=Alpha*Pmu*pow(Ep,-gamma)*lambda*b*jp;
    double denominator=Ep*cosX+b*jp;

    return (numerator/denominator);
}

double angulardistribution(double U)//此函数接收随机数，并返回theta值
{
    double result1;//1-随机数的值
    double result2;//result开立方
    double result3;

    result1=1-U;
    result2=pow(result1,1.0/3);
    result3=acos(result2)*180/PI;
    return result3;
}

void samplewrite()
{
    double zenith;
    double azimuth;
    double energy[100000];

    TFile file("sample.root","recreate");
    TTree* sample=new TTree("sample","a tree with sample");

    sample->Branch("zenith",&zenith,"zenith/D");
    sample->Branch("azimuth",&azimuth,"azimuth/D");
    sample->Branch("energy",energy,"energy[10000]/D");//这里的数字为能量抽样的总数

    TF1* model=new TF1("energy-distribution",PduGenerator,1,100,1);//定出抽样函数

    TRandom3 r;
    int n=10000;//entry的总数
    
    //fill the tree
    for(int i=0;i<n;i++)
    {
        //角度抽样
        double number=r.Rndm(0);
        zenith=angulardistribution(number);
        azimuth=r.Rndm(0)*360;

        
        model->SetParameter(0,zenith/180*PI);
        for(int ii=0;ii<100000;ii++)
        {
            energy[ii]=model->GetRandom();
        }
        
        sample->Fill();
    }

    sample->Print();

    sample->Write();
}


void angularread()//读出天顶角分布，方位角分布
{
    TFile* file=new TFile("sample.root");
    TTree* sample=(TTree*)file->Get("sample");
    double zenith;
    double azimuth;

    sample->SetBranchAddress("zenith",&zenith);
    sample->SetBranchAddress("azimuth",&azimuth);

    //create three histograms
    TH1D* hiszenith=new TH1D("zenith","zenith",270,0,90);
    TH1D* hisazimuth=new TH1D("azimuth","azimuth",720,0,360);

    //fill the three histograms
    Long64_t nentries=sample->GetEntries();
    for(Long64_t i=0;i<nentries;i++)
    {
        sample->GetEntry(i);
        hiszenith->Fill(zenith);
        hisazimuth->Fill(azimuth);
    }

    TCanvas* c1=new TCanvas("c1","c1",600,800);
    c1->Divide(1,2);
    c1->cd(1);
    hisazimuth->Draw("L");
    c1->cd(2);
    hiszenith->Draw("L");

    if(gROOT->IsBatch()) return;
    new TBrowser();
    sample->StartViewer();
}

void energyread()//读相应的能量分布，需要给出指定的的entrie数，然后进入读取相应的能量数值(数组），并画图。
{
    TFile* file=new TFile("sample.root");
    TTree* sample=(TTree*)file->Get("sample");

    double num[100000];//数值和上面的能量抽样相应

    sample->SetBranchAddress("energy",num);

    TH1D* hisenergy=new TH1D("energy","energy",198,1.,100.);

    sample->GetEntry(10);//进入相应的entry,要设定进入哪一个entry

    for(int i=0;i<100000;i++)
    {
        hisenergy->Fill(num[i]);
    }

    hisenergy->Draw("P");

    if(gROOT->IsBatch()) return;
    new TBrowser();
    sample->StartViewer();
}

void sample()
{
    samplewrite();
    angularread();
    energyread();
}
