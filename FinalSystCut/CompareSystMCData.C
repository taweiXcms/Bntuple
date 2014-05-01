void CompareSystMCData(){

  const int nBins=10;

  int idcut=1; double ptBins[nBins+1]={0.,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1};
  //int idcut=2; double ptBins[nBins+1]={2.4,2.6,2.8,3.0,3.2,3.4,3.6,3.8,4.0,4.2,4.4};
  //int idcut=3; double ptBins[nBins+1]={-0.5,-0.4,-0.3,-0.2,-0.1,0.,0.1,0.2,0.3,0.4,0.5};
  //int idcut=4; double ptBins[nBins+1]={0.6,0.64,0.68,0.72,0.76,0.8,0.84,0.88,0.92,0.96,1.0};
   
  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);

  TFile*file0_Data=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step0_isData1.root",idcut));
  TFile*file1_Data=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step1_isData1.root",idcut));
  TFile*file2_Data=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step2_isData1.root",idcut));
  TFile*file3_Data=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step3_isData1.root",idcut));
  TFile*file4_Data=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step4_isData1.root",idcut));
  TFile*file5_Data=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step5_isData1.root",idcut));
  TFile*file6_Data=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step6_isData1.root",idcut));
  TFile*file7_Data=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step7_isData1.root",idcut));
  TFile*file8_Data=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step8_isData1.root",idcut));
  TFile*file9_Data=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step9_isData1.root",idcut));
  
  
  TFile*file0_MC=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step0_isData0.root",idcut));
  TFile*file1_MC=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step1_isData0.root",idcut));
  TFile*file2_MC=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step2_isData0.root",idcut));
  TFile*file3_MC=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step3_isData0.root",idcut));
  TFile*file4_MC=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step4_isData0.root",idcut));
  TFile*file5_MC=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step5_isData0.root",idcut));
  TFile*file6_MC=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step6_isData0.root",idcut));
  TFile*file7_MC=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step7_isData0.root",idcut));
  TFile*file8_MC=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step8_isData0.root",idcut));
  TFile*file9_MC=new TFile(Form("ResultsBplus/SigmaBplusCutId%d_Step9_isData0.root",idcut));
  
  TH1F*hPtYieldBis_Data0=(TH1F*)file0_Data->Get("hPt");
  TH1F*hPtYieldBis_Data1=(TH1F*)file1_Data->Get("hPt");
  TH1F*hPtYieldBis_Data2=(TH1F*)file2_Data->Get("hPt");
  TH1F*hPtYieldBis_Data3=(TH1F*)file3_Data->Get("hPt");
  TH1F*hPtYieldBis_Data4=(TH1F*)file4_Data->Get("hPt");
  TH1F*hPtYieldBis_Data5=(TH1F*)file5_Data->Get("hPt");
  TH1F*hPtYieldBis_Data6=(TH1F*)file6_Data->Get("hPt");
  TH1F*hPtYieldBis_Data7=(TH1F*)file7_Data->Get("hPt");
  TH1F*hPtYieldBis_Data8=(TH1F*)file8_Data->Get("hPt");
  TH1F*hPtYieldBis_Data9=(TH1F*)file9_Data->Get("hPt");
  
  
  TH1F*hPtYieldBis_MC0=(TH1F*)file0_MC->Get("hPt");
  TH1F*hPtYieldBis_MC1=(TH1F*)file1_MC->Get("hPt");
  TH1F*hPtYieldBis_MC2=(TH1F*)file2_MC->Get("hPt");
  TH1F*hPtYieldBis_MC3=(TH1F*)file3_MC->Get("hPt");
  TH1F*hPtYieldBis_MC4=(TH1F*)file4_MC->Get("hPt");
  TH1F*hPtYieldBis_MC5=(TH1F*)file5_MC->Get("hPt");
  TH1F*hPtYieldBis_MC6=(TH1F*)file6_MC->Get("hPt");
  TH1F*hPtYieldBis_MC7=(TH1F*)file7_MC->Get("hPt");
  TH1F*hPtYieldBis_MC8=(TH1F*)file8_MC->Get("hPt");
  TH1F*hPtYieldBis_MC9=(TH1F*)file9_MC->Get("hPt");


  hPtYieldBis_Data0->SetName("hPtYieldBis_Data0");
  hPtYieldBis_Data1->SetName("hPtYieldBis_Data1");
  hPtYieldBis_Data2->SetName("hPtYieldBis_Data2");
  hPtYieldBis_Data3->SetName("hPtYieldBis_Data3");
  hPtYieldBis_Data4->SetName("hPtYieldBis_Data4");
  hPtYieldBis_Data5->SetName("hPtYieldBis_Data5");
  hPtYieldBis_Data6->SetName("hPtYieldBis_Data6");
  hPtYieldBis_Data7->SetName("hPtYieldBis_Data7");
  hPtYieldBis_Data8->SetName("hPtYieldBis_Data8");
  hPtYieldBis_Data9->SetName("hPtYieldBis_Data9");
  

  hPtYieldBis_MC0->SetName("hPtYieldBis_MC0");
  hPtYieldBis_MC1->SetName("hPtYieldBis_MC1");
  hPtYieldBis_MC2->SetName("hPtYieldBis_MC2");
  hPtYieldBis_MC3->SetName("hPtYieldBis_MC3");
  hPtYieldBis_MC4->SetName("hPtYieldBis_MC4");
  hPtYieldBis_MC5->SetName("hPtYieldBis_MC5");
  hPtYieldBis_MC6->SetName("hPtYieldBis_MC6");
  hPtYieldBis_MC7->SetName("hPtYieldBis_MC7");
  hPtYieldBis_MC8->SetName("hPtYieldBis_MC8");
  hPtYieldBis_MC9->SetName("hPtYieldBis_MC9");
  
  TH1D *hPtAll_Data = new TH1D("hPtAll_Data","",nBins,ptBins);
  hPtAll_Data->SetBinContent(1,hPtYieldBis_Data0->GetBinContent(1));
  hPtAll_Data->SetBinContent(2,hPtYieldBis_Data1->GetBinContent(1));
  hPtAll_Data->SetBinContent(3,hPtYieldBis_Data2->GetBinContent(1));
  hPtAll_Data->SetBinContent(4,hPtYieldBis_Data3->GetBinContent(1));
  hPtAll_Data->SetBinContent(5,hPtYieldBis_Data4->GetBinContent(1));
  hPtAll_Data->SetBinContent(6,hPtYieldBis_Data5->GetBinContent(1));
  hPtAll_Data->SetBinContent(7,hPtYieldBis_Data6->GetBinContent(1));
  hPtAll_Data->SetBinContent(8,hPtYieldBis_Data7->GetBinContent(1));
  hPtAll_Data->SetBinContent(9,hPtYieldBis_Data8->GetBinContent(1));
  hPtAll_Data->SetBinContent(10,hPtYieldBis_Data9->GetBinContent(1));
  
  hPtAll_Data->SetBinError(1,hPtYieldBis_Data0->GetBinError(1));
  hPtAll_Data->SetBinError(2,hPtYieldBis_Data1->GetBinError(1));
  hPtAll_Data->SetBinError(3,hPtYieldBis_Data2->GetBinError(1));
  hPtAll_Data->SetBinError(4,hPtYieldBis_Data3->GetBinError(1));
  hPtAll_Data->SetBinError(5,hPtYieldBis_Data4->GetBinError(1));
  hPtAll_Data->SetBinError(6,hPtYieldBis_Data5->GetBinError(1));
  hPtAll_Data->SetBinError(7,hPtYieldBis_Data6->GetBinError(1));
  hPtAll_Data->SetBinError(8,hPtYieldBis_Data7->GetBinError(1));
  hPtAll_Data->SetBinError(9,hPtYieldBis_Data8->GetBinError(1));
  hPtAll_Data->SetBinError(10,hPtYieldBis_Data9->GetBinError(1));

  hPtAll_Data->Scale(1/hPtAll_Data->GetBinContent(1)); 


  TH1D *hPtAll_MC = new TH1D("hPtAll_MC","",nBins,ptBins);
  hPtAll_MC->SetBinContent(1,hPtYieldBis_MC0->GetBinContent(1));
  hPtAll_MC->SetBinContent(2,hPtYieldBis_MC1->GetBinContent(1));
  hPtAll_MC->SetBinContent(3,hPtYieldBis_MC2->GetBinContent(1));
  hPtAll_MC->SetBinContent(4,hPtYieldBis_MC3->GetBinContent(1));
  hPtAll_MC->SetBinContent(5,hPtYieldBis_MC4->GetBinContent(1));
  hPtAll_MC->SetBinContent(6,hPtYieldBis_MC5->GetBinContent(1));
  hPtAll_MC->SetBinContent(7,hPtYieldBis_MC6->GetBinContent(1));
  hPtAll_MC->SetBinContent(8,hPtYieldBis_MC7->GetBinContent(1));
  hPtAll_MC->SetBinContent(9,hPtYieldBis_MC8->GetBinContent(1));
  hPtAll_MC->SetBinContent(10,hPtYieldBis_MC9->GetBinContent(1));
  
  hPtAll_MC->SetBinError(1,hPtYieldBis_MC0->GetBinError(1));
  hPtAll_MC->SetBinError(2,hPtYieldBis_MC1->GetBinError(1));
  hPtAll_MC->SetBinError(3,hPtYieldBis_MC2->GetBinError(1));
  hPtAll_MC->SetBinError(4,hPtYieldBis_MC3->GetBinError(1));
  hPtAll_MC->SetBinError(5,hPtYieldBis_MC4->GetBinError(1));
  hPtAll_MC->SetBinError(6,hPtYieldBis_MC5->GetBinError(1));
  hPtAll_MC->SetBinError(7,hPtYieldBis_MC6->GetBinError(1));
  hPtAll_MC->SetBinError(8,hPtYieldBis_MC7->GetBinError(1));
  hPtAll_MC->SetBinError(9,hPtYieldBis_MC8->GetBinError(1));
  hPtAll_MC->SetBinError(10,hPtYieldBis_MC9->GetBinError(1));

  hPtAll_MC->Scale(1/hPtAll_MC->GetBinContent(1));   
  

  TCanvas *canvasVscut=new TCanvas("canvasVscut","canvasVscut",500,500);
  canvasVscut->cd();  
  canvasVscut->cd(1);
  if(idcut==1) hPtAll_Data->GetXaxis()->SetTitle("chi2cl cut value");
  if(idcut==2) hPtAll_Data->GetXaxis()->SetTitle("d0/d0err cut value");
  if(idcut==3) hPtAll_Data->GetXaxis()->SetTitle("cosTheta cut value");
  if(idcut==4) hPtAll_Data->GetXaxis()->SetTitle("trk pt cut value");
  hPtAll_Data->GetYaxis()->SetTitle("Raw yield normalized to one with loosest selection");
  hPtAll_Data->GetXaxis()->SetTitleOffset(1.);
  hPtAll_Data->GetYaxis()->SetTitleOffset(1.);
  hPtAll_Data->GetXaxis()->SetTitleSize(0.04);
  hPtAll_Data->GetYaxis()->SetTitleSize(0.04);
  hPtAll_Data->GetXaxis()->SetTitleFont(42);
  hPtAll_Data->GetYaxis()->SetTitleFont(42);
  hPtAll_Data->GetXaxis()->SetLabelFont(42);
  hPtAll_Data->GetYaxis()->SetLabelFont(42);
  hPtAll_Data->GetXaxis()->SetLabelSize(0.035);
  hPtAll_Data->GetYaxis()->SetLabelSize(0.035);  
  hPtAll_Data->SetMinimum(0.8);
  hPtAll_Data->SetMaximum(1.2);
  hPtAll_Data->SetLineColor(1);
  hPtAll_Data->SetLineWidth(2);
  hPtAll_Data->Draw();
  hPtAll_MC->SetLineColor(2);
  hPtAll_MC->SetLineWidth(2);
  hPtAll_MC->Draw("same");
  
  //TF1 *fPt0 = new TF1("fPt0","[0]*x+[1]");
  //hPtAll_Data->Fit("fPt0","L q","",ptBins[0],ptBins[10]);
  //TLatex * tlatexPt0=new TLatex(0.15,0.35,Form("Intersection y axis= %.2f",fPt0->GetParameter(1)));
  //tlatexPt0->SetNDC();
  //tlatexPt0->SetTextColor(1);
  //tlatexPt0->SetTextFont(42);
  //tlatexPt0->SetTextSize(0.06);
  //tlatexPt0->Draw();  
  canvasVscut->SaveAs(Form("Plots/canvasVscutId%d.pdf",idcut));

  
}
