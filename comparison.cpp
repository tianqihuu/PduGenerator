//比较抽样点和实验点，用各个BIN所占比例来比较
void graph()//读出能量分布概率密度函数
{
    TFile* file=new TFile("sample0.root");
    TTree* sample=(TTree*)file->Get("sample");
    double energy;

    sample->SetBranchAddress("energy",&energy);

    TH1D* hisenergy=new TH1D("energy","energy",200,0.,100.);
    //fill the three histograms
    Long64_t nentries=sample->GetEntries();
    for(Long64_t i=0;i<nentries;i++)
    {
        sample->GetEntry(i);
        hisenergy->Fill(energy);
    }

    const int n=200;

    double x[n],y[n];

    for(int ii=1;ii<=200;ii++)
    {
        double entry=hisenergy->GetBinContent(ii);
        y[ii-1]=entry;
        x[ii-1]=0.25+(ii-1)*0.5;
    }

    TCanvas* c1=new TCanvas("c1","c1",800,600);

    TGraph* gr2=new TGraph(n,x,y);
    gr2->SetMarkerColor(2);
    gr2->SetMarkerSize(0.5);
    gr2->SetMarkerStyle(20);
    
    gr2->Draw("AP");
    
    
    
    //实验数据点，包括换算
    const int labn=19;

    //75度角采点，20个点,所有数据乘以1E7
    //double labx[labn]={1.11009,1.38938,1.73676,2.30596,2.84161,3.60774,4.44578,5.64443,7.16624,8.96363,11.2118,14.2347,17.5412,22.6054,27.8564,33.3668,44.9022,56.1643,71.3069,87.8708};
    //double swichy[labn]={303.552,341.552,346.081,355.552,340.081,330.687,307.777,294.208,281.832,220.3,193.668,173.526,120.9034,87.3987,60.6572,41.9705,23.3637,10.9802,6.8796,3.92562};
    
    //0度角采点，19个点.所有数据乘以1E6
    double labx[labn]={1.73884,2.48945,3.45908,4.46016,5.4987,6.4816,7.41532,8.48343,9.41946,12.5142,17.3844,22.7585,27.2311,35.1119,45.2736,54.987,63.855,86.1122,95.6136};
    double swichy[labn]={1463.51,1271.53,795.726,573.152,393.931,311.63,235.235,161.678,134.038,80.0401,34.4267,18.7182,11.7139,6.07736,3.15303,1.42125,0.848698,0.36504,0.164545};


    double laby[labn];//转换回原数据，除以相应的阶数
    for(int i3=0;i3<19;i3++)
    {
        laby[i3]=swichy[i3]*y[3]/1463.51;
    }
    
    TGraph* gr1=new TGraph(labn,labx,laby);
    gr1->SetMarkerColor(4);
    gr1->SetMarkerSize(1);
    gr1->SetMarkerStyle(22);
    gr1->GetXaxis()->SetTitle("energy[GEV]");

    gr1->Draw("Psame");

    
}
