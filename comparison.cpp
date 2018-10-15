//比较抽样点和实验点，积分通量统一为实验的积分通量
void graph()//读出能量分布概率密度函数
{
    TFile* file=new TFile("sample75.root");
    TTree* sample=(TTree*)file->Get("sample");
    double energy;

    sample->SetBranchAddress("energy",&energy);

    TH1D* hisenergy=new TH1D("energy","energy",1998,1.,1000.);
    //fill the three histograms
    Long64_t nentries=sample->GetEntries();
    for(Long64_t i=0;i<nentries;i++)
    {
        sample->GetEntry(i);
        hisenergy->Fill(energy);
    }

    const int n=1998;

    double x[n],y[n];

    for(int i2=1;i2<=1998;i2++)
    {
        double entry=hisenergy->GetBinContent(i2);
        y[i2-1]=entry;
        x[i2-1]=1.25+(i2-1)*0.5;
    }

    
    //实验数据点
    
    //75度角，采样29个点
    const int labn=29;

    //diff-intensity所有数据乘以1E7
    double px[labn]={1.11571,1.38884,1.72863,2.28449,3.84378,3.5399,4.45056,5.65147,7.10534,8.93327,11.3473,14.2619,17.7533,22.5437,28.0625,35.2818,44.8019,55.7696,70.8181,88.1546,110.833,140.739,176.945,222.465,279.696,355.167,451.002,620.165,990.096};
    double py[labn]={297.148,306.54,326.222,316.228,306.54,297.22,262.373,231.667,204.555,169.719,136.501,106.421,82.9696,57.159,39.3183,25.4335,17.5083,10.6421,6.46861,3.6946,2.1769,1.24335,0.667305,0.381173,0.192213,0.0939665,0.0536698,0.0175083,0.00393183};

    //转换回实验数据点
    double labx[labn];
    double laby[labn];

    double multiple=pow(10,7);
    for(int i3=0;i3<labn;i3++)
    {
        labx[i3]=px[i3];
        laby[i3]=py[i3]/multiple;
    }

    double area=0;//初始化积分通量
    area=(labx[0]-1)*laby[0]+(1000-labx[28])*laby[28];//首尾部分先处理，剩下的取中间值在处理

    for (int i4=0;i4<(labn-1);i4++)
    {
        area=area+((laby[i4]+laby[i4+1])/2)*(labx[i4+1]-labx[i4]);

    }

    //得到的积分归一化

    double const1=1/area;//const1为实验中归一化常数

    //抽样点换算

    double samplex[n];
    double sampley[n];

    for(int i5=0;i5<=1998;i5++)
    {
        samplex[i5]=x[i5];
        sampley[i5]=y[i5]/20000/const1;
    }


    TCanvas* c1=new TCanvas("c1","c1",800,600);

    TGraph* gr1=new TGraph(n,samplex,sampley);
    gr1->SetMarkerColor(2);
    gr1->SetMarkerSize(0.5);
    gr1->SetMarkerStyle(20);
  
    TGraph* gr2=new TGraph(labn,labx,laby);
    gr2->SetMarkerColor(4);
    gr2->SetMarkerSize(1);
    gr2->SetMarkerStyle(22);
    gr2->GetXaxis()->SetTitle("energy[GEV]");

    gr1->Draw("AP");

    gr2->Draw("Psame"); 
}
