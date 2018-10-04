//比较抽样点和实验点，用各个BIN所占比例来比较
void graph()//读出能量分布概率密度函数
{
    TFile* file=new TFile("sample75.root");
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

    TGraph* gr=new TGraph(n,x,y);
    gr->SetMarkerColor(2);
    gr->SetMarkerSize(0.5);
    gr->SetMarkerStyle(20);
    gr->GetXaxis()->SetTitle("energy[GEV]");
    gr->Draw("AP");
    
    
    //实验数据点，包括换算
    const int labn=20;
    double labx[labn]={1.11009,1.40938,1.73676,2.30596,2.84161,3.60774,4.44578,5.64443,7.16624,8.96363,11.2118,14.2347,17.5412,22.6054,27.8564,33.3668,44.9022,56.1643,71.3069,87.8708};
    double laby[labn]={273.687,287.552,300.081,300.081,300.081,287.552,276.777,250.276,240.832,200.212,173.668,128.526,105.9034,69.3987,40.6572,29.9705,18.3637,10.9802,6.8796,3.92562};
    double swichy[labn];
    for(int i3=0;i3<20;i3++)
    {
        swichy[i3]=laby[i3]*5;
    }
    
    TGraph* gr=new TGraph(labn,labx,swichy);
    gr->SetMarkerColor(4);
    gr->SetMarkerSize(0.5);
    gr->SetMarkerStyle(22);

    gr->Draw("Psame");
}
