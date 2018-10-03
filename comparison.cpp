//比较抽样点和实验点，用各个BIN所占比例来比较
void graph()//读出能量分布概率密度函数
{
    TFile* file=new TFile("sample.root");
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
        y[ii-1]=entry/200000;//entry中的粒子占总粒子数的比例
        x[ii-1]=0.25+(ii-1)*0.5;
    }

    TCanvas* c1=new TCanvas("c1","c1",800,600);

    TGraph* gr=new TGraph(n,x,y);
    gr->SetMarkerColor(2);
    gr->SetMarkerSize(0.5);
    gr->SetMarkerStyle(20);
    gr->GetXaxis()->SetTitle("energy[GEV]");
    gr->Draw("AP");
    
    const int p=17;
    double lpx[p]={0.148451,0.249335,0.398599,0.846475,1.38705,2.03381,2.63579,3.29175,4.37271,5.32772,5.95386,6.99043,8.62977,20.5035,24.0835,32.0167,53.1871};
    double lpy[p]={410.663,1237.031,1594.61,1901.82,1554.98,1337.03,1013.69,768.544,513.783,441.77,379.857,247.62,214.464,35.6566,28.4292,12.3895,2.87795};
    
    double px[p],py[p];//实验点换算
    for(int iii=0;iii<17;iii++)
    {
        px[iii]=lpx[iii];
        py[iii]=lpy[iii]/18000;
    }

    TGraph* labpoint=new TGraph(p,px,py);
    labpoint->SetMarkerColor(4);
    labpoint->SetMarkerSize(0.5);
    labpoint->SetMarkerStyle(22);

    labpoint->Draw("Psame");
}