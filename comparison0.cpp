
void comparison0()
{
    TFile* file=new TFile("sample0.root");
    TTree* sample=(TTree*)file->Get("sample");
    double energy;

    sample->SetBranchAddress("energy",&energy);

    TH1D* hisenergy=new TH1D("","Zenith Angle(0)",99,1.,100.);
    //fill the three histograms
    int nentries=sample->GetEntries();
    for(int i=0;i<nentries;i++)
    {
        sample->GetEntry(i);
        hisenergy->Fill(energy);
    }

    const int n=37;//total number of picture points

    //data with angular is 0

    double Picturex[n]={1.00,1.23632,1.66974,2.13862,2.57483,3.04569,3.4775,3.97053,4.41483,4.82282,5.26853,5.75542,6.23198,6.62975,7.11553,7.50309,8.02074,8.56686,10.13345,11.2674,12.5282,14.1785,16.1887,18.3213,20.5523,23.2596,27.271,30.8634,35.2391,42.3164,46.3476,51.0803,55.8009,58.8401,61.4989,66.0051,100.00};
    //Picture[y]的点在扣点的基础上乘以5E5；
    double Picturey[n]={205.908,200.806,164.731,141.429,121.905,97.5545,82.0311,68.9779,58.0017,51.2481,44.1734,36.236,33.642,28.9978,26.922,23.2055,18.7697,17.2409,12.4961,10.0,8.20311,6.404,4.64159,3.44853,2.62636,1.85702,1.21905,0.883561,0.580017,0.36236,0.256214,0.190357,0.152334,0.121905,0.107711,0.0883561,0.02};
    
    //实验点

    double labx[n]={1.00,1.21466,1.66974,2.1198,2.52483,2.99232,3.4775,3.97053,4.33747,4.82282,5.26853,5.70477,6.12277,6.62975,8.12435,9.44165,9.9559,10.876,11.5702,12.3087,13.8075,14.9508,16.7714,18.1601,19.8383,22.6509,25.4092,28.5033,31.6927,35.2391,43.5668,52.9186,57.3004,64.8485,75.3632,83.0588,100.00};
    //实验点数值上先乘以1E5
    double laby[n]={226.38,210.175,176.731,148.608,124.961,105.076,90.571,72.4795,64.04,55.1995,48.7722,41.0113,37.1443,32.8193,22.638,16.0067,14.1429,12.1905,10.5076,9.51688,7.24795,6.09461,4.75794,3.90299,3.28193,2.32055,1.68192,1.24961,0.90571,0.70707,0.390299,0.262636,0.181161,0.090571,0.0565833,0.0441734,0.0297248};


    //transform to lab point
    double x[n];
    double y[n];
    double lx[n];
    double ly[n];

    for(int i0=0;i0<n;i0++)
    {
        x[i0]=Picturex[i0];
        y[i0]=Picturey[i0]/100000.0;
        lx[i0]=labx[i0];
        ly[i0]=laby[i0]/100000.0;
    }

    double area=0;  //intergrated flux
    double areal=0;


    for(int i1=0;i1<(n-1);i1++)
    {
        area+=(x[i1+1]-x[i1])*(y[i1]+y[i1+1])/2;
        areal+=(lx[i1+1]-lx[i1])*(ly[i1]+ly[i1+1])/2;
    }

    //normalized const
 
    double constant=1/area;
    double constantl=1/areal;

    //normalized

    double nx[n];
    double ny[n];
    double lnx[n];
    double lny[n];

    for(int i2=0;i2<n;i2++)
    {
        nx[i2]=x[i2];
        ny[i2]=y[i2]*constant;
        lnx[i2]=lx[i2];
        lny[i2]=ly[i2]*constantl;
    }

    TCanvas* c1=new TCanvas("c1","Contrast",800,600);

    hisenergy->GetXaxis()->SetTitle("Muon Momentum[GEV]");
    hisenergy->GetYaxis()->SetTitle("Arbitrary Units");
    hisenergy->GetXaxis()->CenterTitle();
    hisenergy->GetYaxis()->CenterTitle();
    hisenergy->DrawNormalized("P");


    TGraph* gr=new TGraph(n,nx,ny);
    gr->SetMarkerColor(2);
    gr->SetMarkerStyle(20);

    TGraph* grl=new TGraph(n,lnx,lny);
    grl->SetMarkerColor(kBlack);
    grl->SetMarkerSize(1.2);
    grl->SetMarkerStyle(22);
    
    
    gr->Draw("Psame");
    grl->Draw("Psame");

    auto legend = new TLegend(0.1,0.1,0.4,0.3);
    legend->SetHeader("Notation","C"); 
    legend->AddEntry(hisenergy,"My Point","lep");
    legend->AddEntry(gr,"Experimental Point","p");
    legend->AddEntry(grl,"Author Point","p");
    legend->Draw();
}