void ComparedNdcutNew(int variationoption=1){
  
  void ComparedNdcutNewInternal(int ,const int);
  
  if(variationoption==1) ComparedNdcutNewInternal(1,5);
  if(variationoption==2) ComparedNdcutNewInternal(2,5);
  if(variationoption==3) ComparedNdcutNewInternal(3,5);
  if(variationoption==4) ComparedNdcutNewInternal(4,5);
  if(variationoption==5) ComparedNdcutNewInternal(5,5);
  if(variationoption==6) ComparedNdcutNewInternal(6,4);
  
}


void ComparedNdcutNewInternal(int variationoption=6,const int nBins=4){
  
  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);

  double ptBins[nBins+1];
  
  if(variationoption==1){ ptBins[0]=1.32e-02; ptBins[1]=0.2; ptBins[2]=0.4; ptBins[3]=0.6; ptBins[4]=0.8; ptBins[5]=1.;}
  if(variationoption==2){ ptBins[0]=3.41; ptBins[1]=6.; ptBins[2]=10.; ptBins[3]=20.; ptBins[4]=30.; ptBins[5]=50.;}
  if(variationoption==3){ ptBins[0]=0.9995; ptBins[1]=0.9997; ptBins[2]=0.9998; ptBins[3]=0.9999; ptBins[4]=0.99995; ptBins[5]=1.0;}
  if(variationoption==4){ ptBins[0]=0.7; ptBins[1]=2.; ptBins[2]=4.; ptBins[3]=6.; ptBins[4]=10.; ptBins[5]=20.;}
  if(variationoption==5){ ptBins[0]=10.; ptBins[1]=15.; ptBins[2]=20.; ptBins[3]=25.; ptBins[4]=30.; ptBins[5]=60.;}
  if(variationoption==6){ ptBins[0]=-1.93; ptBins[1]=-1; ptBins[2]=0; ptBins[3]=1.0; ptBins[4]=1.93;}

  TH1D *hPtAll_Data = new TH1D("hPtAll_Data","",nBins,ptBins);  
  TH1D *hPtAll_MC = new TH1D("hPtAll_MC","",nBins,ptBins);  


  //if(variationoption==1 || variationoption==2 || variationoption==3 || variationoption==4 ){
  if(0){
  
    double binsize1=ptBins[1]-ptBins[0];
    double binsize2=ptBins[2]-ptBins[1];
    double binsize3=ptBins[3]-ptBins[2];
    double binsize4=ptBins[4]-ptBins[3];
    double binsize5=ptBins[5]-ptBins[4];
    double binsize6=ptBins[6]-ptBins[5];
    double binsize7=ptBins[7]-ptBins[6];
    double binsize8=ptBins[8]-ptBins[7];
  

    TFile*file0_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step0_isData1.root",variationoption,variationoption));
    TFile*file1_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step1_isData1.root",variationoption,variationoption));
    TFile*file2_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step2_isData1.root",variationoption,variationoption));
    TFile*file3_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step3_isData1.root",variationoption,variationoption));
    TFile*file4_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step4_isData1.root",variationoption,variationoption));
    TFile*file5_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step5_isData1.root",variationoption,variationoption));
    TFile*file6_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step6_isData1.root",variationoption,variationoption));
    TFile*file7_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step7_isData1.root",variationoption,variationoption));

    TFile*file0_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step0_isData0.root",variationoption,variationoption));
    TFile*file1_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step1_isData0.root",variationoption,variationoption));
    TFile*file2_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step2_isData0.root",variationoption,variationoption));
    TFile*file3_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step3_isData0.root",variationoption,variationoption));
    TFile*file4_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step4_isData0.root",variationoption,variationoption));
    TFile*file5_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step5_isData0.root",variationoption,variationoption));
    TFile*file6_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step6_isData0.root",variationoption,variationoption));
    TFile*file7_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step7_isData0.root",variationoption,variationoption));

    TH1F*hPtYieldBis_Data1=(TH1F*)file0_Data->Get("hPt");
    TH1F*hPtYieldBis_Data2=(TH1F*)file1_Data->Get("hPt");
    TH1F*hPtYieldBis_Data3=(TH1F*)file2_Data->Get("hPt");
    TH1F*hPtYieldBis_Data4=(TH1F*)file3_Data->Get("hPt");
    TH1F*hPtYieldBis_Data5=(TH1F*)file4_Data->Get("hPt");
    TH1F*hPtYieldBis_Data6=(TH1F*)file5_Data->Get("hPt");
    TH1F*hPtYieldBis_Data7=(TH1F*)file6_Data->Get("hPt");
    TH1F*hPtYieldBis_Data8=(TH1F*)file7_Data->Get("hPt");
   
    TH1F*hPtYieldBis_MC1=(TH1F*)file0_MC->Get("hPt");
    TH1F*hPtYieldBis_MC2=(TH1F*)file1_MC->Get("hPt");
    TH1F*hPtYieldBis_MC3=(TH1F*)file2_MC->Get("hPt");
    TH1F*hPtYieldBis_MC4=(TH1F*)file3_MC->Get("hPt");
    TH1F*hPtYieldBis_MC5=(TH1F*)file4_MC->Get("hPt");
    TH1F*hPtYieldBis_MC6=(TH1F*)file5_MC->Get("hPt");
    TH1F*hPtYieldBis_MC7=(TH1F*)file6_MC->Get("hPt");
    TH1F*hPtYieldBis_MC8=(TH1F*)file7_MC->Get("hPt");


    hPtYieldBis_Data1->SetName("hPtYieldBis_Data1");
    hPtYieldBis_Data2->SetName("hPtYieldBis_Data2");
    hPtYieldBis_Data3->SetName("hPtYieldBis_Data3");
    hPtYieldBis_Data4->SetName("hPtYieldBis_Data4");
    hPtYieldBis_Data5->SetName("hPtYieldBis_Data5");
    hPtYieldBis_Data6->SetName("hPtYieldBis_Data6");
    hPtYieldBis_Data7->SetName("hPtYieldBis_Data7");
    hPtYieldBis_Data8->SetName("hPtYieldBis_Data8");

    hPtYieldBis_MC1->SetName("hPtYieldBis_MC1");
    hPtYieldBis_MC2->SetName("hPtYieldBis_MC2");
    hPtYieldBis_MC3->SetName("hPtYieldBis_MC3");
    hPtYieldBis_MC4->SetName("hPtYieldBis_MC4");
    hPtYieldBis_MC5->SetName("hPtYieldBis_MC5");
    hPtYieldBis_MC6->SetName("hPtYieldBis_MC6");
    hPtYieldBis_MC7->SetName("hPtYieldBis_MC7");
    hPtYieldBis_MC8->SetName("hPtYieldBis_MC8");
    
    hPtAll_Data->SetBinContent(1,hPtYieldBis_Data1->GetBinContent(1)/binsize1);
    hPtAll_Data->SetBinContent(2,hPtYieldBis_Data2->GetBinContent(1)/binsize2);
    hPtAll_Data->SetBinContent(3,hPtYieldBis_Data3->GetBinContent(1)/binsize3);
    hPtAll_Data->SetBinContent(4,hPtYieldBis_Data4->GetBinContent(1)/binsize4);
    hPtAll_Data->SetBinContent(5,hPtYieldBis_Data5->GetBinContent(1)/binsize5);
    hPtAll_Data->SetBinContent(6,hPtYieldBis_Data6->GetBinContent(1)/binsize6);
    hPtAll_Data->SetBinContent(7,hPtYieldBis_Data7->GetBinContent(1)/binsize7);
    hPtAll_Data->SetBinContent(8,hPtYieldBis_Data8->GetBinContent(1)/binsize8);

    hPtAll_Data->SetBinError(1,hPtYieldBis_Data1->GetBinError(1)/binsize1);
    hPtAll_Data->SetBinError(2,hPtYieldBis_Data2->GetBinError(1)/binsize2);
    hPtAll_Data->SetBinError(3,hPtYieldBis_Data3->GetBinError(1)/binsize3);
    hPtAll_Data->SetBinError(4,hPtYieldBis_Data4->GetBinError(1)/binsize4);
    hPtAll_Data->SetBinError(5,hPtYieldBis_Data5->GetBinError(1)/binsize5);
    hPtAll_Data->SetBinError(6,hPtYieldBis_Data6->GetBinError(1)/binsize6);
    hPtAll_Data->SetBinError(7,hPtYieldBis_Data7->GetBinError(1)/binsize7);
    hPtAll_Data->SetBinError(8,hPtYieldBis_Data8->GetBinError(1)/binsize8);
   
    hPtAll_MC->SetBinContent(1,hPtYieldBis_MC1->GetBinContent(1)/binsize1);
    hPtAll_MC->SetBinContent(2,hPtYieldBis_MC2->GetBinContent(1)/binsize2);
    hPtAll_MC->SetBinContent(3,hPtYieldBis_MC3->GetBinContent(1)/binsize3);
    hPtAll_MC->SetBinContent(4,hPtYieldBis_MC4->GetBinContent(1)/binsize4);
    hPtAll_MC->SetBinContent(5,hPtYieldBis_MC5->GetBinContent(1)/binsize5);
    hPtAll_MC->SetBinContent(6,hPtYieldBis_MC6->GetBinContent(1)/binsize6);
    hPtAll_MC->SetBinContent(7,hPtYieldBis_MC7->GetBinContent(1)/binsize7);
    hPtAll_MC->SetBinContent(8,hPtYieldBis_MC8->GetBinContent(1)/binsize8);

    hPtAll_MC->SetBinError(1,hPtYieldBis_MC1->GetBinError(1)/binsize1);
    hPtAll_MC->SetBinError(2,hPtYieldBis_MC2->GetBinError(1)/binsize2);
    hPtAll_MC->SetBinError(3,hPtYieldBis_MC3->GetBinError(1)/binsize3);
    hPtAll_MC->SetBinError(4,hPtYieldBis_MC4->GetBinError(1)/binsize4);
    hPtAll_MC->SetBinError(5,hPtYieldBis_MC5->GetBinError(1)/binsize5);
    hPtAll_MC->SetBinError(6,hPtYieldBis_MC6->GetBinError(1)/binsize6);
    hPtAll_MC->SetBinError(7,hPtYieldBis_MC7->GetBinError(1)/binsize7);
    hPtAll_MC->SetBinError(8,hPtYieldBis_MC8->GetBinError(1)/binsize8);
      
  }

  if(variationoption==1 || variationoption==2 || variationoption==3 || variationoption==4 || variationoption==5){
  
    double binsize1=ptBins[1]-ptBins[0];
    double binsize2=ptBins[2]-ptBins[1];
    double binsize3=ptBins[3]-ptBins[2];
    double binsize4=ptBins[4]-ptBins[3];
    double binsize5=ptBins[5]-ptBins[4];
  

    TFile*file0_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step0_isData1.root",variationoption,variationoption));
    TFile*file1_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step1_isData1.root",variationoption,variationoption));
    TFile*file2_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step2_isData1.root",variationoption,variationoption));
    TFile*file3_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step3_isData1.root",variationoption,variationoption));
    TFile*file4_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step4_isData1.root",variationoption,variationoption));

    TFile*file0_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step0_isData0.root",variationoption,variationoption));
    TFile*file1_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step1_isData0.root",variationoption,variationoption));
    TFile*file2_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step2_isData0.root",variationoption,variationoption));
    TFile*file3_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step3_isData0.root",variationoption,variationoption));
    TFile*file4_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step4_isData0.root",variationoption,variationoption));

    TH1F*hPtYieldBis_Data1=(TH1F*)file0_Data->Get("hPt");
    TH1F*hPtYieldBis_Data2=(TH1F*)file1_Data->Get("hPt");
    TH1F*hPtYieldBis_Data3=(TH1F*)file2_Data->Get("hPt");
    TH1F*hPtYieldBis_Data4=(TH1F*)file3_Data->Get("hPt");
    TH1F*hPtYieldBis_Data5=(TH1F*)file4_Data->Get("hPt");
   
    TH1F*hPtYieldBis_MC1=(TH1F*)file0_MC->Get("hPt");
    TH1F*hPtYieldBis_MC2=(TH1F*)file1_MC->Get("hPt");
    TH1F*hPtYieldBis_MC3=(TH1F*)file2_MC->Get("hPt");
    TH1F*hPtYieldBis_MC4=(TH1F*)file3_MC->Get("hPt");
    TH1F*hPtYieldBis_MC5=(TH1F*)file4_MC->Get("hPt");


    hPtYieldBis_Data1->SetName("hPtYieldBis_Data1");
    hPtYieldBis_Data2->SetName("hPtYieldBis_Data2");
    hPtYieldBis_Data3->SetName("hPtYieldBis_Data3");
    hPtYieldBis_Data4->SetName("hPtYieldBis_Data4");
    hPtYieldBis_Data5->SetName("hPtYieldBis_Data5");

    hPtYieldBis_MC1->SetName("hPtYieldBis_MC1");
    hPtYieldBis_MC2->SetName("hPtYieldBis_MC2");
    hPtYieldBis_MC3->SetName("hPtYieldBis_MC3");
    hPtYieldBis_MC4->SetName("hPtYieldBis_MC4");
    hPtYieldBis_MC5->SetName("hPtYieldBis_MC5");
    
    hPtAll_Data->SetBinContent(1,hPtYieldBis_Data1->GetBinContent(1)/binsize1);
    hPtAll_Data->SetBinContent(2,hPtYieldBis_Data2->GetBinContent(1)/binsize2);
    hPtAll_Data->SetBinContent(3,hPtYieldBis_Data3->GetBinContent(1)/binsize3);
    hPtAll_Data->SetBinContent(4,hPtYieldBis_Data4->GetBinContent(1)/binsize4);
    hPtAll_Data->SetBinContent(5,hPtYieldBis_Data5->GetBinContent(1)/binsize5);

    hPtAll_Data->SetBinError(1,hPtYieldBis_Data1->GetBinError(1)/binsize1);
    hPtAll_Data->SetBinError(2,hPtYieldBis_Data2->GetBinError(1)/binsize2);
    hPtAll_Data->SetBinError(3,hPtYieldBis_Data3->GetBinError(1)/binsize3);
    hPtAll_Data->SetBinError(4,hPtYieldBis_Data4->GetBinError(1)/binsize4);
    hPtAll_Data->SetBinError(5,hPtYieldBis_Data5->GetBinError(1)/binsize5);
   
    hPtAll_MC->SetBinContent(1,hPtYieldBis_MC1->GetBinContent(1)/binsize1);
    hPtAll_MC->SetBinContent(2,hPtYieldBis_MC2->GetBinContent(1)/binsize2);
    hPtAll_MC->SetBinContent(3,hPtYieldBis_MC3->GetBinContent(1)/binsize3);
    hPtAll_MC->SetBinContent(4,hPtYieldBis_MC4->GetBinContent(1)/binsize4);
    hPtAll_MC->SetBinContent(5,hPtYieldBis_MC5->GetBinContent(1)/binsize5);

    hPtAll_MC->SetBinError(1,hPtYieldBis_MC1->GetBinError(1)/binsize1);
    hPtAll_MC->SetBinError(2,hPtYieldBis_MC2->GetBinError(1)/binsize2);
    hPtAll_MC->SetBinError(3,hPtYieldBis_MC3->GetBinError(1)/binsize3);
    hPtAll_MC->SetBinError(4,hPtYieldBis_MC4->GetBinError(1)/binsize4);
    hPtAll_MC->SetBinError(5,hPtYieldBis_MC5->GetBinError(1)/binsize5);
      
  }
  
  if(variationoption==6){
  
    double binsize1=ptBins[1]-ptBins[0];
    double binsize2=ptBins[2]-ptBins[1];
    double binsize3=ptBins[3]-ptBins[2];
    double binsize4=ptBins[4]-ptBins[3];
  

    TFile*file0_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step0_isData1.root",variationoption,variationoption));
    TFile*file1_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step1_isData1.root",variationoption,variationoption));
    TFile*file2_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step2_isData1.root",variationoption,variationoption));
    TFile*file3_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step3_isData1.root",variationoption,variationoption));

    TFile*file0_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step0_isData0.root",variationoption,variationoption));
    TFile*file1_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step1_isData0.root",variationoption,variationoption));
    TFile*file2_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step2_isData0.root",variationoption,variationoption));
    TFile*file3_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step3_isData0.root",variationoption,variationoption));

    TH1F*hPtYieldBis_Data1=(TH1F*)file0_Data->Get("hPt");
    TH1F*hPtYieldBis_Data2=(TH1F*)file1_Data->Get("hPt");
    TH1F*hPtYieldBis_Data3=(TH1F*)file2_Data->Get("hPt");
    TH1F*hPtYieldBis_Data4=(TH1F*)file3_Data->Get("hPt");
   
    TH1F*hPtYieldBis_MC1=(TH1F*)file0_MC->Get("hPt");
    TH1F*hPtYieldBis_MC2=(TH1F*)file1_MC->Get("hPt");
    TH1F*hPtYieldBis_MC3=(TH1F*)file2_MC->Get("hPt");
    TH1F*hPtYieldBis_MC4=(TH1F*)file3_MC->Get("hPt");


    hPtYieldBis_Data1->SetName("hPtYieldBis_Data1");
    hPtYieldBis_Data2->SetName("hPtYieldBis_Data2");
    hPtYieldBis_Data3->SetName("hPtYieldBis_Data3");
    hPtYieldBis_Data4->SetName("hPtYieldBis_Data4");

    hPtYieldBis_MC1->SetName("hPtYieldBis_MC1");
    hPtYieldBis_MC2->SetName("hPtYieldBis_MC2");
    hPtYieldBis_MC3->SetName("hPtYieldBis_MC3");
    hPtYieldBis_MC4->SetName("hPtYieldBis_MC4");
    
    hPtAll_Data->SetBinContent(1,hPtYieldBis_Data1->GetBinContent(1)/binsize1);
    hPtAll_Data->SetBinContent(2,hPtYieldBis_Data2->GetBinContent(1)/binsize2);
    hPtAll_Data->SetBinContent(3,hPtYieldBis_Data3->GetBinContent(1)/binsize3);
    hPtAll_Data->SetBinContent(4,hPtYieldBis_Data4->GetBinContent(1)/binsize4);

    hPtAll_Data->SetBinError(1,hPtYieldBis_Data1->GetBinError(1)/binsize1);
    hPtAll_Data->SetBinError(2,hPtYieldBis_Data2->GetBinError(1)/binsize2);
    hPtAll_Data->SetBinError(3,hPtYieldBis_Data3->GetBinError(1)/binsize3);
    hPtAll_Data->SetBinError(4,hPtYieldBis_Data4->GetBinError(1)/binsize4);
   
    hPtAll_MC->SetBinContent(1,hPtYieldBis_MC1->GetBinContent(1)/binsize1);
    hPtAll_MC->SetBinContent(2,hPtYieldBis_MC2->GetBinContent(1)/binsize2);
    hPtAll_MC->SetBinContent(3,hPtYieldBis_MC3->GetBinContent(1)/binsize3);
    hPtAll_MC->SetBinContent(4,hPtYieldBis_MC4->GetBinContent(1)/binsize4);

    hPtAll_MC->SetBinError(1,hPtYieldBis_MC1->GetBinError(1)/binsize1);
    hPtAll_MC->SetBinError(2,hPtYieldBis_MC2->GetBinError(1)/binsize2);
    hPtAll_MC->SetBinError(3,hPtYieldBis_MC3->GetBinError(1)/binsize3);
    hPtAll_MC->SetBinError(4,hPtYieldBis_MC4->GetBinError(1)/binsize4);
      
  }


    
    
  hPtAll_Data->SetMinimum(0.01);
  hPtAll_MC->SetMinimum(0.01);
  
  double normMC=0.;
  double normData=0.;
  
  for (int i=1;i<nBins;i++){
  normMC=normMC+hPtAll_MC->GetBinContent(i);
  normData=normData+hPtAll_Data->GetBinContent(i);
  }
  hPtAll_MC->Scale(1/normMC); 
  hPtAll_Data->Scale(1/normData); 
  
  
  
  TH1D *hPtAll_DataOverMC = (TH1D*)hPtAll_Data->Clone();
  hPtAll_DataOverMC->SetName("hPtAll_DataOverMC");
  hPtAll_DataOverMC->Divide(hPtAll_MC);  
  
  TCanvas *canvasVscut=new TCanvas("canvasVscut","canvasVscut",1200,500);
  canvasVscut->Divide(2,1);
  canvasVscut->cd(1);
  

  if(variationoption==1) {
    hPtAll_Data->GetXaxis()->SetTitle("chi2cl");
    hPtAll_Data->GetYaxis()->SetTitle("dN^{yield}/d(chi2cl)");
    hPtAll_DataOverMC->GetXaxis()->SetTitle("chi2cl");
    hPtAll_DataOverMC->GetYaxis()->SetTitle("dN^{yield}/d(chi2cl) Data/MC");   
    hPtAll_Data->SetMinimum(0);
    hPtAll_Data->SetMaximum(0.5);
 
  }
   
  if(variationoption==2) {
    hPtAll_Data->GetXaxis()->SetTitle("d0/d0err");
    hPtAll_Data->GetYaxis()->SetTitle("dN^{yield}/d(d0/d0err)");
    hPtAll_DataOverMC->GetXaxis()->SetTitle("d0/d0err");
    hPtAll_DataOverMC->GetYaxis()->SetTitle("dN^{yield}/d(d0/d0err) Data/MC");
  }
  
  if(variationoption==3) {
    hPtAll_Data->GetXaxis()->SetTitle("cos(Theta)");
    hPtAll_Data->GetYaxis()->SetTitle("dN^{yield}/d(cos(Theta))");
    hPtAll_DataOverMC->GetXaxis()->SetTitle("chi2cl");
    hPtAll_DataOverMC->GetYaxis()->SetTitle("dN^{yield}/d(cos(Theta)) Data/MC");
  }
  
  if(variationoption==4) {
    hPtAll_Data->GetXaxis()->SetTitle("p^{track}_{t}");
    hPtAll_Data->GetYaxis()->SetTitle("dN^{yield}/d(p^{track}_{t})");
    hPtAll_DataOverMC->GetXaxis()->SetTitle("p^{track}_{t}");
    hPtAll_DataOverMC->GetYaxis()->SetTitle("dN^{yield}/d(p^{track}_{t}) Data/MC");
    
    hPtAll_Data->GetXaxis()->SetRangeUser(0.,20.);
    hPtAll_DataOverMC->GetXaxis()->SetRangeUser(0.,20.);
    hPtAll_Data->SetMaximum(0.5);

  }
   
  if(variationoption==5) {
    hPtAll_Data->GetXaxis()->SetTitle("p_{t}");
    hPtAll_Data->GetYaxis()->SetTitle("dN^{yield}/dp_{t}");
    hPtAll_DataOverMC->GetXaxis()->SetTitle("p_{t}");
    hPtAll_DataOverMC->GetYaxis()->SetTitle("dN^{yield}/dp_{t} Data/MC");
    canvasVscut_1->SetLogy();
  }
  
  if(variationoption==6) {
    hPtAll_Data->GetXaxis()->SetTitle("y_{LAB}");
    hPtAll_Data->GetYaxis()->SetTitle("dN^{yield}/dy_{LAB}");
    hPtAll_DataOverMC->GetXaxis()->SetTitle("y_{LAB}");
    hPtAll_DataOverMC->GetYaxis()->SetTitle("dN^{yield}/dy_{LAB} Data/MC");
    hPtAll_Data->SetMinimum(0);
    hPtAll_Data->SetMaximum(1);
  }

  hPtAll_Data->GetXaxis()->SetTitleOffset(1.);
  hPtAll_Data->GetYaxis()->SetTitleOffset(1.2);
  hPtAll_Data->GetXaxis()->SetTitleSize(0.04);
  hPtAll_Data->GetYaxis()->SetTitleSize(0.04);
  hPtAll_Data->GetXaxis()->SetTitleFont(42);
  hPtAll_Data->GetYaxis()->SetTitleFont(42);
  hPtAll_Data->GetXaxis()->SetLabelFont(42);
  hPtAll_Data->GetYaxis()->SetLabelFont(42);
  hPtAll_Data->GetXaxis()->SetLabelSize(0.035);
  hPtAll_Data->GetYaxis()->SetLabelSize(0.035);  
  
  
  hPtAll_Data->SetLineColor(1);
  hPtAll_Data->SetLineWidth(3);
  hPtAll_Data->Draw();
  hPtAll_MC->SetLineColor(2);
  hPtAll_MC->SetLineWidth(3);
  hPtAll_MC->Draw("same");
  
  TLegend *leg = new TLegend(0.4597315,0.6173362,0.8590604,0.7463002,NULL,"brNDC");
  leg->AddEntry(hPtAll_Data,"Data","pl");
  leg->AddEntry(hPtAll_MC,"MC","pl");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw();
  
  canvasVscut->cd(2);
  
  hPtAll_DataOverMC->GetXaxis()->SetTitleOffset(1.);
  hPtAll_DataOverMC->GetYaxis()->SetTitleOffset(1.2);
  hPtAll_DataOverMC->GetXaxis()->SetTitleSize(0.04);
  hPtAll_DataOverMC->GetYaxis()->SetTitleSize(0.04);
  hPtAll_DataOverMC->GetXaxis()->SetTitleFont(42);
  hPtAll_DataOverMC->GetYaxis()->SetTitleFont(42);
  hPtAll_DataOverMC->GetXaxis()->SetLabelFont(42);
  hPtAll_DataOverMC->GetYaxis()->SetLabelFont(42);
  hPtAll_DataOverMC->GetXaxis()->SetLabelSize(0.035);
  hPtAll_DataOverMC->GetYaxis()->SetLabelSize(0.035); 
  hPtAll_DataOverMC->SetLineColor(1);
  hPtAll_DataOverMC->SetLineWidth(3);
  hPtAll_DataOverMC->SetMinimum(0);
  hPtAll_DataOverMC->SetMaximum(2.);
  
  hPtAll_DataOverMC->Draw();

  
  canvasVscut->SaveAs(Form("Plots/canvasMCDataVscutId%d.pdf",variationoption));
  
  
}
