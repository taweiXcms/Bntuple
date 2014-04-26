#include "utilities.h"

TString inputdata="/export/d00/scratch/jwang/nt_20140418_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root";
TString inputmc="/export/d00/scratch/jwang/nt_BoostedMC_20140418_Kp_TriggerMatchingMuon_EvtBase_skim.root";

//TString cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&chi2cl>0.0054&&(d0)/d0Err>3.3&&cos(dtheta)>-0.53&&TMath::Abs((trk1Dxy)/trk1D0Err)>1.9&&mass>5.24&&mass<5.31";
TString cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5.24&&mass<5.31&&isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e01";

TString seldata=Form("abs(y+0.465)<1.93&&%s&&pt>10.&&pt<60.",cut.Data());
TString selmc="1";//Form("abs(y+0.465)<1.93&&%s&&gen!=22233&&pt>10.&&pt<60.",cut.Data());
TString selmcsignal=Form("abs(y+0.465)<1.93&&%s&&gen==22233&&pt>10.&&pt<60.",cut.Data());



//TString seldata=Form("%s&&pt>10.&&pt<60.",cut.Data());
//TString selmc=Form("%s&&gen!=22233&&pt>10.&&pt<60.",cut.Data());
//TString selmcsignal=Form("%s&&gen==22233&&pt>10.&&pt<60.",cut.Data());

void LoopMCDataSignal(){

  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);
  
  Double_t cutd0d0Err=3.;
  Double_t cutchi2cl=0.005;
  Double_t cutcostheta=-0.5;
  Double_t cuttrk1D0Err=2.;

  TFile *inf = new TFile(inputdata.Data());
  TTree *nt = (TTree*) inf->Get("ntKp");
  
  TFile *infMC = new TFile(inputmc.Data());
  TTree *ntMC = (TTree*)infMC->Get("ntKp");

  TH1D *hd0d0Err_Data = new TH1D("hd0d0Err_Data","hd0d0Err_Data",50,-.1,200);
  TH1D *hchi2cl_Data = new TH1D("hchi2cl_Data","hchi2cl_Data",20,-.1,1);
  TH1D *hcostheta_Data = new TH1D("hcostheta_Data","hcostheta_Data",50,0.9,1);
  TH1D *htrk1D0Err_Data = new TH1D("htrk1D0Err_Data","htrk1D0Err_Data",50,-.1,100);
  
  hd0d0Err_Data->Sumw2(); 
  hchi2cl_Data->Sumw2();
  hcostheta_Data->Sumw2();
  htrk1D0Err_Data->Sumw2();


  nt->Project("hd0d0Err_Data","(d0)/d0Err",seldata.Data());  
  nt->Project("hchi2cl_Data","chi2cl",seldata.Data());
  nt->Project("hcostheta_Data","cos(dtheta)",seldata.Data());
  nt->Project("htrk1D0Err_Data","TMath::Abs((trk1Dxy)/trk1D0Err)",seldata.Data());

  TH1D *hd0d0Err_MCsignal = new TH1D("hd0d0Err_MCsignal","hd0d0Err_MCsignal",50,-.1,200);  
  TH1D *hchi2cl_MCsignal = new TH1D("hchi2cl_MCsignal","hchi2cl_MCsignal",20,-.1,1);
  TH1D *hcostheta_MCsignal = new TH1D("hcostheta_MCsignal","hcostheta_MCsignal",50,0.9,1);
  TH1D *htrk1D0Err_MCsignal = new TH1D("htrk1D0Err_MCsignal","htrk1D0Err_MCsignal",50,-.1,100);

  ntMC->Project("hd0d0Err_MCsignal","(d0)/d0Err",selmcsignal.Data());  
  ntMC->Project("hchi2cl_MCsignal","chi2cl",selmcsignal.Data());
  ntMC->Project("hcostheta_MCsignal","cos(dtheta)",selmcsignal.Data());
  ntMC->Project("htrk1D0Err_MCsignal","TMath::Abs((trk1Dxy)/trk1D0Err)",selmcsignal.Data());
  
  TH1D *hd0d0Err_MC = new TH1D("hd0d0Err_MC","hd0d0Err_MC",50,-.1,200);  
  TH1D *hchi2cl_MC = new TH1D("hchi2cl_MC","hchi2cl_MC",20,-.1,1);
  TH1D *hcostheta_MC = new TH1D("hcostheta_MC","hcostheta_MC",50,0.9,1);
  TH1D *htrk1D0Err_MC = new TH1D("htrk1D0Err_MC","htrk1D0Err_MC",50,-.1,100);

  ntMC->Project("hd0d0Err_MC","(d0)/d0Err",selmc.Data());  
  ntMC->Project("hchi2cl_MC","chi2cl",selmc.Data());
  ntMC->Project("hcostheta_MC","cos(dtheta)",selmc.Data());
  ntMC->Project("htrk1D0Err_MC","TMath::Abs((trk1Dxy)/trk1D0Err)",selmc.Data());

  hd0d0Err_Data->Scale(1./(hd0d0Err_Data->GetEntries()));
  hcostheta_Data->Scale(1./(hcostheta_Data->GetEntries()));
  hchi2cl_Data->Scale(1./(hchi2cl_Data->GetEntries()));
  htrk1D0Err_Data->Scale(1./(htrk1D0Err_Data->GetEntries()));

  hd0d0Err_MC->Scale(1./(hd0d0Err_MC->GetEntries()));
  hcostheta_MC->Scale(1./(hcostheta_MC->GetEntries()));
  hchi2cl_MC->Scale(1./(hchi2cl_MC->GetEntries()));
  htrk1D0Err_MC->Scale(1./(htrk1D0Err_MC->GetEntries()));
  
  hd0d0Err_MCsignal->Scale(1./(hd0d0Err_MCsignal->GetEntries()));
  hcostheta_MCsignal->Scale(1./(hcostheta_MCsignal->GetEntries()));
  hchi2cl_MCsignal->Scale(1./(hchi2cl_MCsignal->GetEntries()));
  htrk1D0Err_MCsignal->Scale(1./(htrk1D0Err_MCsignal->GetEntries()));
  
  
  cout<<"integrals"<<htrk1D0Err_Data->Integral()<<endl;
  cout<<"integrals"<<hcostheta_Data->Integral()<<endl;
  cout<<"integrals"<<hchi2cl_Data->Integral()<<endl;
  cout<<"integrals"<<htrk1D0Err_Data->Integral()<<endl;
  
  cout<<"integrals"<<hd0d0Err_MC->Integral()<<endl;
  cout<<"integrals"<<hcostheta_MC->Integral()<<endl;
  cout<<"integrals"<<hchi2cl_MC->Integral()<<endl;
  cout<<"integrals"<<htrk1D0Err_MC->Integral()<<endl;
  
  cout<<"integrals"<<hd0d0Err_MCsignal->Integral()<<endl;
  cout<<"integrals"<<hcostheta_MCsignal->Integral()<<endl;
  cout<<"integrals"<<hchi2cl_MCsignal->Integral()<<endl;
  cout<<"integrals"<<htrk1D0Err_MCsignal->Integral()<<endl;  
  
  TCanvas *canvas=new TCanvas("canvas","canvas",900,800);
  canvas->SetFillColor(0);
  canvas->Divide(2,2);
  canvas_1->SetLogy();
  canvas_2->SetLogy();
  canvas_3->SetLogy();
  canvas_4->SetLogy();
  canvas->cd(1);
  hd0d0Err_Data->GetXaxis()->SetTitle("d_{0}/Err(d_{0})");
  hd0d0Err_Data->GetYaxis()->SetTitle("Entries");
    hd0d0Err_Data->GetXaxis()->SetTitleOffset(0.85);
  hd0d0Err_Data->GetYaxis()->SetTitleOffset(0.9);
  hd0d0Err_Data->GetXaxis()->SetTitleSize(0.055);
  hd0d0Err_Data->GetYaxis()->SetTitleSize(0.055);
  hd0d0Err_Data->GetXaxis()->SetTitleFont(42);
  hd0d0Err_Data->GetYaxis()->SetTitleFont(42);
  hd0d0Err_Data->GetXaxis()->SetLabelFont(42);
  hd0d0Err_Data->GetYaxis()->SetLabelFont(42);
  hd0d0Err_Data->GetXaxis()->SetLabelSize(0.05);
  hd0d0Err_Data->GetYaxis()->SetLabelSize(0.05);  
  hd0d0Err_Data->SetLineWidth(2);
  hd0d0Err_MC->SetLineWidth(2);
  hd0d0Err_MCsignal->SetLineWidth(2);
  hd0d0Err_Data->SetLineColor(2);
  hd0d0Err_MC->SetLineColor(1);
  hd0d0Err_MCsignal->SetLineColor(4);
  hd0d0Err_Data->GetXaxis()->SetRangeUser(0.,200.);
    hd0d0Err_Data->SetMaximum(10.);
  hd0d0Err_Data->SetMinimum(1e-6);

  
    TLegend* legd0d0Err=new TLegend(0.1210007,0.7162524,0.4000186,0.8868177);
  legd0d0Err->SetFillStyle(0);
  legd0d0Err->SetBorderSize(0);
  legd0d0Err->SetTextFont(42);
  legd0d0Err->SetTextSize(0.055);

  hd0d0Err_Data->Draw();
  //hd0d0Err_MC->Draw("SAME");
  hd0d0Err_MCsignal->Draw("SAME");
  
  
  TLegendEntry* entDecayLength=legd0d0Err->AddEntry(hd0d0Err_Data,"Data signal region","PL");
  entDecayLength->SetTextColor(2);
  TLegendEntry* entDecayLength=legd0d0Err->AddEntry(hd0d0Err_MCsignal,"MC Signal","PL");
  entDecayLength->SetTextColor(4);

  legd0d0Err->Draw(); 
  
    TLatex*latexd0d0Err=new TLatex(5.,0.35,"10 <p_{t}< 60 GeV/c");
  latexd0d0Err->SetTextSize(0.05);
  latexd0d0Err->SetTextColor(1);
  latexd0d0Err->SetTextFont(42);
  
  
  canvas->cd(2);
  hchi2cl_Data->GetXaxis()->SetTitle("Prob chi square");
  hchi2cl_Data->GetYaxis()->SetTitle("Entries");
  hchi2cl_Data->GetXaxis()->SetTitleOffset(0.85);
  hchi2cl_Data->GetYaxis()->SetTitleOffset(0.9);
  hchi2cl_Data->GetXaxis()->SetTitleSize(0.055);
  hchi2cl_Data->GetYaxis()->SetTitleSize(0.055);
  hchi2cl_Data->GetXaxis()->SetTitleFont(42);
  hchi2cl_Data->GetYaxis()->SetTitleFont(42);
  hchi2cl_Data->GetXaxis()->SetLabelFont(42);
  hchi2cl_Data->GetYaxis()->SetLabelFont(42);
  hchi2cl_Data->GetXaxis()->SetLabelSize(0.05);
  hchi2cl_Data->GetYaxis()->SetLabelSize(0.05);  
  hchi2cl_Data->SetLineWidth(2);
  hchi2cl_MC->SetLineWidth(2);
  hchi2cl_MCsignal->SetLineWidth(2);
  hchi2cl_Data->SetLineColor(2);
  hchi2cl_MC->SetLineColor(1);
  hchi2cl_MCsignal->SetLineColor(4);
  hchi2cl_Data->GetXaxis()->SetRangeUser(-0,1.05.);
  hchi2cl_Data->SetMinimum(1e-4);
  hchi2cl_Data->SetMaximum(1);
  
  TLegend* legchi2cl=new TLegend(0.1210007,0.7162524,0.4000186,0.8868177);
  legchi2cl->SetFillStyle(0);
  legchi2cl->SetBorderSize(0);
  legchi2cl->SetTextFont(42);
  legchi2cl->SetTextSize(0.055);

  hchi2cl_Data->Draw();
  hchi2cl_MCsignal->Draw("SAME");
  
  TLegendEntry* entDecayLength=legchi2cl->AddEntry(hchi2cl_Data,"Data signal region","PL");
  entDecayLength->SetTextColor(2);
  TLegendEntry* entDecayLength=legchi2cl->AddEntry(hchi2cl_MCsignal,"MC Signal","PL");
  entDecayLength->SetTextColor(4);

  legchi2cl->Draw(); 
  
  canvas->cd(3);
  hcostheta_Data->GetXaxis()->SetTitle("Cos(#theta)");
  hcostheta_Data->GetYaxis()->SetTitle("Entries");
    hcostheta_Data->GetXaxis()->SetTitleOffset(0.85);
  hcostheta_Data->GetYaxis()->SetTitleOffset(0.9);
  hcostheta_Data->GetXaxis()->SetTitleSize(0.055);
  hcostheta_Data->GetYaxis()->SetTitleSize(0.055);
  hcostheta_Data->GetXaxis()->SetTitleFont(42);
  hcostheta_Data->GetYaxis()->SetTitleFont(42);
  hcostheta_Data->GetXaxis()->SetLabelFont(42);
  hcostheta_Data->GetYaxis()->SetLabelFont(42);
  hcostheta_Data->GetXaxis()->SetLabelSize(0.05);
  hcostheta_Data->GetYaxis()->SetLabelSize(0.05);  

  hcostheta_Data->SetLineWidth(2);
  hcostheta_MC->SetLineWidth(2);
  hcostheta_MCsignal->SetLineWidth(2);
  hcostheta_Data->SetLineColor(2);
  hcostheta_MC->SetLineColor(1);
  hcostheta_MCsignal->SetLineColor(4);
  hcostheta_Data->GetXaxis()->SetRangeUser(-1.05,1.05.);
  hcostheta_Data->SetMinimum(1e-6);
  hcostheta_Data->SetMaximum(5);
  
  TLegend* legcostheta=new TLegend(0.1210007,0.7162524,0.4000186,0.8868177);
  legcostheta->SetFillStyle(0);
  legcostheta->SetBorderSize(0);
  legcostheta->SetTextFont(42);
  legcostheta->SetTextSize(0.055);

  hcostheta_Data->Draw();
  hcostheta_MCsignal->Draw("SAME");
  
  TLegendEntry* entDecayLength=legcostheta->AddEntry(hcostheta_Data,"Data signal region","PL");
  entDecayLength->SetTextColor(2);
  TLegendEntry* entDecayLength=legcostheta->AddEntry(hcostheta_MCsignal,"MC Signal","PL");
  entDecayLength->SetTextColor(4);
  legcostheta->Draw(); 
  

  canvas->cd(4);
  htrk1D0Err_Data->GetXaxis()->SetTitle("|trk1Dxy/trk1D0Err|");
  htrk1D0Err_Data->GetYaxis()->SetTitle("Entries");
  htrk1D0Err_Data->GetXaxis()->SetTitleOffset(0.85);
  htrk1D0Err_Data->GetYaxis()->SetTitleOffset(0.9);
  htrk1D0Err_Data->GetXaxis()->SetTitleSize(0.055);
  htrk1D0Err_Data->GetYaxis()->SetTitleSize(0.055);
  htrk1D0Err_Data->GetXaxis()->SetTitleFont(42);
  htrk1D0Err_Data->GetYaxis()->SetTitleFont(42);
  htrk1D0Err_Data->GetXaxis()->SetLabelFont(42);
  htrk1D0Err_Data->GetYaxis()->SetLabelFont(42);
  htrk1D0Err_Data->GetXaxis()->SetLabelSize(0.05);
  htrk1D0Err_Data->GetYaxis()->SetLabelSize(0.05);  
  htrk1D0Err_Data->SetLineWidth(2);
  htrk1D0Err_MC->SetLineWidth(2);
  htrk1D0Err_MCsignal->SetLineWidth(2);
  htrk1D0Err_Data->SetLineColor(2);
  htrk1D0Err_MC->SetLineColor(1);
  htrk1D0Err_MCsignal->SetLineColor(4);
  htrk1D0Err_Data->GetXaxis()->SetRangeUser(0.,100.);
  htrk1D0Err_Data->SetMinimum(1e-7);
  htrk1D0Err_Data->SetMaximum(5.);
  
  TLegend* legtrk1D0Err=new TLegend(0.1210007,0.7162524,0.4000186,0.8868177);
  legtrk1D0Err->SetFillStyle(0);
  legtrk1D0Err->SetBorderSize(0);
  legtrk1D0Err->SetTextFont(42);
  legtrk1D0Err->SetTextSize(0.055);

  htrk1D0Err_Data->Draw();
  htrk1D0Err_MCsignal->Draw("SAME");
  
  TLegendEntry* entDecayLength=legtrk1D0Err->AddEntry(htrk1D0Err_Data,"Data signal region","PL");
  entDecayLength->SetTextColor(2);
  TLegendEntry* entDecayLength=legtrk1D0Err->AddEntry(htrk1D0Err_MCsignal,"MC Signal","PL");
  entDecayLength->SetTextColor(4);

  legtrk1D0Err->Draw(); 
  
  TLatex*latextrk1D0Err=new TLatex(5.,0.35,"10 <p_{t}< 60 GeV/c");
  latextrk1D0Err->SetTextSize(0.05);
  latextrk1D0Err->SetTextColor(1);
  latextrk1D0Err->SetTextFont(42);
  //latextrk1D0Err->Draw();
  
  canvas->SaveAs("Plots/canvasSignal.pdf");

}