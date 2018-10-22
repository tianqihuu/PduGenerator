void comparison60()
{
    TFile* file=new TFile("sample60.root");
    TTree* sample=(TTree*)file->Get("sample");
    double energy;

    sample->SetBranchAddress("energy",&energy);

    TH1D* hisenergy=new TH1D("","Zenith Angle(60)",99,1.,100.);
    //fill the three histograms
    int nentries=sample->GetEntries();
    for(int i=0;i<nentries;i++)
    {
        sample->GetEntry(i);
        hisenergy->Fill(energy);
    }

    const int n=32;//total number of picture points

    //data with angular is 0

    double Picturex[n]={1.00,1.19297,1.5682,1.95518,2.33247,2.73389,3.0933,3.4692,4.17532,4.76608,5.34527,5.78698,6.54775,7.40853,8.45674,9.8251,11.1167,12.9155,14.3578,16.3893,18.3809,20.6147,23.3247,27.0988,29.8604,33.7859,36.902,41.7532,46.4159,56.3583,62.652,100.00};
    //Picture[y]的点在扣点的基础上乘以E5；
    double Picturey[n]={25.4928,26.1284,26.1284,23.6773,23.6773,21.9911,20.9342,18.9703,19.4433,17.1907,14.1167,12.7924,10.5049,9.28783,7.62699,6.11077,5.14316,4.32876,3.46822,2.64521,2.0175,1.46479,1.09002,0.753365,0.560613,0.438239,0.342678,0.219911,0.171907,0.148294,0.118814,0.0382726};
//实验点

    double labx[n]={1.00,1.19337,1.56965,1.97508,2.35701,2.71507,3.10001,3.50837,3.90095,4.26146,5.0855,5.85807,6.57141,7.63691,8.49147,9.9559,11.07,12.8649,14.6888,16.1887,19.6639,22.254,25.8623,30.5918,35.8626,41.3164,45.9397,50.1852,56.2963,66.5911,80.8853,100.0};
    //实验点数值上先乘以1E5
    double laby[n]={25.6214,26.922,26.2636,24.9948,24.3835,22.638,21.5443,19.5129,18.5702,17.2409,14.8608,13.1304,11.3178,10.0,8.20311,7.0707,5.65833,4.64159,3.6236,2.97248,2.05035,1.60067,1.16016,0.78068,0.538496,0.390299,0.304699,0.237872,0.176731,0.121905,0.0742964,0.0430932};


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