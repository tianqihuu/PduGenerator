#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TMath.h"



double PduModel(double* x,double* par)
{
    using namespace TMath;
    double Emu = x[0]; // Unit: GeV
    double cosX = Cos(par[0]);

    const double Alpha = 0.002382; // constant A
    const double lambda = 120;     // absorption mean free path 120 g/cm2
    const double kappa = 2.645;    // exponent (-)
    const double bp = 0.771;
    const double jp = 148.16;
  // correction factor (-); factor (GeV)
    const double alpha = 0.0025; // muon energy loss in GeV/g/cm2
    const double rho = 0.76;
  // fraction of pion energy that is transferred to muon
    const double y0 = 1000; // atmoshperic depth g/cm2
    const double bm = 0.8;
    const double Bm = 1.041231831;

  // Energy of Pion
    double Ep = (1 / rho) * (Emu + alpha * y0 * (1 / cosX - 0.1));

  // Prob. of Muon Production
    double Pmu = 0.1 * cosX * (1 - alpha * (y0 / cosX - 100)/ rho / Ep);
    Pmu = Power(Pmu, Bm / (rho * Ep + 100 * alpha) / cosX);

    double numerator = Alpha * Pmu * Power(Ep, -kappa) * lambda * bp * jp;
    double denominator = Ep * cosX + bp * jp;

    return (numerator/denominator);
}

double GetTheta()//get one zenith value
{
    using namespace TMath;//Inverse transform

    double num1;
    double num2;
    double theta;

    TRandom3 r(0);

    num1=1-r.Rndm();
    num2=pow(num1,1.0/3);
    theta=acos(num2)*180/TMath::Pi();
   
    return theta;
}

double GetPhi()//get one azimuth value
{
    using namespace TMath;

    TRandom3 r(0);
    double azimuth;
    azimuth=r.Rndm()*360/TMath::Pi()/2.;
    
    return azimuth;
}

void write()
{
    double zenith;
    double azimuth;
    double energy;

    TFile file("sample0.root","recreate");
    TTree* sample=new TTree("sample","a tree with sample");

    sample->Branch("zenith",&zenith,"zenith/D");
    sample->Branch("azimuth",&azimuth,"azimuth/D");
    sample->Branch("energy",&energy,"energy/D");

    double fEmin=1;
    double fEmax=100;
    double fTheta=0.00/180*TMath::Pi();

    TF1* fPduModel = new TF1("pdu", PduModel, fEmin, fEmax, 1);
    fPduModel->SetParameter(0,fTheta);

    int n=100000;//total number of particle
    
    //fill the tree
    for(int i=0;i<n;i++)
    {
        zenith=GetTheta();
        azimuth=GetPhi();
        
        //fTheta=zenith/180*TMath::Pi();
        //fPduModel->SetParameter(0,fTheta);
        energy=fPduModel->GetRandom();
        
        sample->Fill();
    }

    sample->Print();

    sample->Write();
}




void John_Leong()
{
    double fEmin=1;
    double fEmax=100;
    double fTheta=30/180*TMath::Pi();

    TF1* f1_Test = new TF1("pdu", PduModel, fEmin, fEmax, 1);
    f1_Test -> SetParameter(0, fTheta);


    auto h = new TH1D("h", "h", 500, fEmin, fEmax);

    for(int i = 0; i < 10000; i++)
    {
        double y = f1_Test -> GetRandom();
        h -> Fill(y);
    }

    auto c = new TCanvas("c1", "c1", 1);

    c -> cd();
    // h -> DrawNormalized();
    f1_Test -> Draw("");
    cout << "Test 1: " << f1_Test -> GetParameter(0) << endl;

    TF1* f2_Test = new TF1("pdu2", PduModel, fEmin, fEmax, 1);

    f2_Test -> FixParameter(0, 1);
    // f2_Test -> FixParameter(0, 90/180*TMath::Pi());
    cout << "Test 2: " << f2_Test -> GetParameter(0) << endl;
    f2_Test -> SetLineColor(kBlue);

    // f2_Test -> Draw("same");

    c -> BuildLegend();
}
