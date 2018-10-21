
void graph()
{
    TFile* file=new TFile("sample0.root");
    TTree* sample=(TTree*)file->Get("sample");
    double energy;

    sample->SetBranchAddress("energy",&energy);

    TH1D* hisenergy=new TH1D("energy","energy",396,1.,100.);
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


    //transform to lab point
    double x[n];
    double y[n];

    for(int i0=0;i0<n;i0++)
    {
        x[i0]=Picturex[i0];
        y[i0]=Picturey[i0]/100000;
    }

    double area=0;  //intergrated flux


    for(int i1=0;i1<n;i1++)
    {
        area+=(x[i1+1]-x[i1])*(y[i1]+y[i1+1])/2;
    }

    //normalized const

    double constant=1/area;

    printf("area:%f,constant:%f\n",area,constant);

    //normalized

    double nx[n];
    double ny[n];

    for(int i2=0;i2<n;i2++)
    {
        nx[i2]=x[i2];
        ny[i2]=y[i2]*constant;
    }

    TCanvas* c1=new TCanvas("c1","Contrast",800,600);
    //hisenergy->DrawNormalized();

    TGraph* gr=new TGraph(n,nx,ny);
    gr->SetMarkerColor(2);
    gr->SetMarkerSize(0.5);
    gr->SetMarkerStyle(20);
    
    
    gr->Draw();

}
