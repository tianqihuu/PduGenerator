void comparison75()
{
    TFile* file=new TFile("sample75.root");
    TTree* sample=(TTree*)file->Get("sample");
    double energy;

    sample->SetBranchAddress("energy",&energy);

    TH1D* hisenergy=new TH1D("","Zenith Angle(75)",99,1.,100.);
    //fill the three histograms
    int nentries=sample->GetEntries();
    for(int i=0;i<nentries;i++)
    {
        sample->GetEntry(i);
        hisenergy->Fill(energy);
    }

    const int n=23;
    
    double Picturex[n]={1.00,3.50837,4.33747,5.3153,6.57141,7.98199,9.86829,11.9866,14.0538,17.0705,20.3714,24.5265,28.5033,32.8333,38.8375,45.5354,53.9186,59.8896,66.5911,74.0426,85.2908,89.9362,100.00};
    double Picturey[n]={4.64159,4.52808,4.10113,3.80755,3.3642,2.82887,2.32055,2.10175,1.60067,1.38924,0.840875,0.624739,0.430932,0.304699,0.215449,0.141429,0.0883561,0.0609461,0.0390299,0.0289978,0.0200021,0.0160067,0.013797};
//实验点

    double labx[n]={1.00,1.16214,1.51503,1.87306,2.21559,2.55217,2.91401,3.60267,4.2993,4.99639,5.70477,6.74799,8.05286,9.44165,12.3087,15.0835,17.5292,20.7347,25.6348,32.8333,43.9536,58.8401,100.0};
    //实验点数值上先乘以1E5
    double laby[n]={2.75969,2.89978,3.28193,3.3642,3.3642,3.44853,3.44853,3.3642,3.3642,3.28193,3.04699,2.82887,2.56214,2.20844,1.81161,1.44974,1.16016,0.928415,0.656454,0.430932,0.249948,0.128093,0.0441734};


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
    grl->SetMarkerSize(1.5);
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
