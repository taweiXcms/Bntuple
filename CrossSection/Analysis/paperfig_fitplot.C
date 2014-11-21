#include "utilities.h"
#include <TROOT.h>
#include <TPaveText.h>
#include <TPad.h>
#include <TFile.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TColor.h>

double luminosity=34.8*1e-3;
double setparam0=100.;
double setparam1=5.28;
double setparam2=0.05;
double setparam3=0.03;
double fixparam1=5.279;

void paperfig_fitplot()
{
//  gROOT->Macro("rootlogon.C+");
//  gStyle->SetCanvasDefH(600);
//  gStyle->SetCanvasDefW(1800);
//  gStyle->SetPadBorderSize(10);
//  gStyle->SetPadColor(0);

  gStyle->SetTextSize(0.060);
  gStyle->SetTextFont(42);
  //gStyle->SetPadRightMargin(0.000);
  //gStyle->SetPadLeftMargin(0.000);
  gStyle->SetPadRightMargin(0.030);
  gStyle->SetPadLeftMargin(0.130);


//  TFile *infBplus = new TFile("../ResultsBplus/SigmaBplus.root");
//  TFile *infBzero = new TFile("../ResultsBzero/SigmaBzero.root");
//  TFile *infBs = new TFile("../ResultsBs/SigmaBs.root");

  TFile *infBplus = new TFile("/afs/cern.ch/work/h/hckim/public/Plotsforpaper/ResultsBplus/SigmaBplus.root");
  TFile *infBzero = new TFile("/afs/cern.ch/work/h/hckim/public/Plotsforpaper/ResultsBzero/SigmaBzero.root");
  TFile *infBs = new TFile("/afs/cern.ch/work/h/hckim/public/Plotsforpaper/ResultsBs/SigmaBs.root");


  TH1D *h0_Bplus = (TH1D*)infBplus->Get("h0");
  TH1D *hMC0_Bplus = (TH1D*)infBplus->Get("hMC0");
  TF1 *f0_Bplus = (TF1*)infBplus->Get("f0");
  TF1 *background0_Bplus = (TF1*)infBplus->Get("background0");
  TF1 *Bkpi0_Bplus = (TF1*)infBplus->Get("fBkpi0");
  TF1 *mass0_Bplus = (TF1*)infBplus->Get("fmass0");

  TH1D *h0_Bzero = (TH1D*)infBzero->Get("h0");
  TH1D *hMC0_Bzero = (TH1D*)infBzero->Get("hMC0");
  TF1 *f0_Bzero = (TF1*)infBzero->Get("f0");
  TF1 *background0_Bzero = (TF1*)infBzero->Get("background0");
  TF1 *Bkpi0_Bzero = (TF1*)infBzero->Get("fBkpi0");
  TF1 *mass0_Bzero = (TF1*)infBzero->Get("fmass0");

  TH1D *h0_Bs = (TH1D*)infBs->Get("h0");
  TH1D *hMC0_Bs = (TH1D*)infBs->Get("hMC0");
  TF1 *f0_Bs = (TF1*)infBs->Get("f0");
  TF1 *background0_Bs = (TF1*)infBs->Get("background0");
  TF1 *Bkpi0_Bs = (TF1*)infBs->Get("fBkpi0");
  TF1 *mass0_Bs = (TF1*)infBs->Get("fmass0");

  TH1D *h5_Bplus = (TH1D*)infBplus->Get("h5");
  TH1D *hMC5_Bplus = (TH1D*)infBplus->Get("hMC5");
  TF1 *f5_Bplus = (TF1*)infBplus->Get("f5");
  TF1 *background5_Bplus = (TF1*)infBplus->Get("background5");
  TF1 *Bkpi5_Bplus = (TF1*)infBplus->Get("fBkpi5");
  TF1 *mass5_Bplus = (TF1*)infBplus->Get("fmass5");

  TH1D *h3_Bzero = (TH1D*)infBzero->Get("h3");
  TH1D *hMC3_Bzero = (TH1D*)infBzero->Get("hMC3");
  TF1 *f3_Bzero = (TF1*)infBzero->Get("f3");
  TF1 *background3_Bzero = (TF1*)infBzero->Get("background3");
  TF1 *Bkpi3_Bzero = (TF1*)infBzero->Get("fBkpi3");
  TF1 *mass3_Bzero = (TF1*)infBzero->Get("fmass3");

  //TCanvas *cSigma=  new TCanvas("cSigma","",10,10,1810,610);
  //TCanvas *cSigma=  new TCanvas("cSigma","",1200,400);
  //TCanvas *cSigma=  new TCanvas("cSigma","",900,400);
  //TCanvas *cSigma=  new TCanvas("cSigma","",1000,400);
  //TCanvas *cSigma=  new TCanvas("cSigma","",940,320);
  TCanvas *cSigma=  new TCanvas("cSigma","",1128,384);





  cSigma->Clear();
  //makeMultiPanelCanvasWithGap(cSigma,3,1,0.05,0.05,0.05,0.05,0.05,0.05);

  //TCanvas *cSigma=  new TCanvas("cSigma");

  //TPad *pad1 = new TPad("pad1","",0.01,0.05,0.34,0.95,21);
  //TPad *pad2 = new TPad("pad2","",0.34,0.05,0.67,0.95,21);
  //TPad *pad3 = new TPad("pad3","",0.67,0.05,1.00,0.95,21);
  TPad *pad1 = new TPad("pad1","",0.01,0.02,0.33,0.98);
  TPad *pad2 = new TPad("pad2","",0.34,0.02,0.66,0.98);
  TPad *pad3 = new TPad("pad3","",0.67,0.02,0.99,0.98);


  pad1->Draw();
  pad2->Draw();
  pad3->Draw();

  //cSigma->Divide(3);
///////////////////
  pad1->cd();
  //cSigma->cd(1);
  //h0_Bplus->Draw("pe");
  Int_t ci = TColor::GetColor("#000099");
  h0_Bplus->SetLineColor(ci);
  h0_Bplus->SetMarkerStyle(24);
  h0_Bplus->SetMarkerSize(0.8);
  h0_Bplus->SetXTitle("M_{B} (GeV/c^{2})");
  h0_Bplus->GetXaxis()->CenterTitle();
  h0_Bplus->GetXaxis()->SetLabelFont(42);
  h0_Bplus->GetXaxis()->SetLabelSize(0.035);
  h0_Bplus->GetXaxis()->SetTitleSize(0.055);
  h0_Bplus->GetXaxis()->SetTitleFont(42);
  h0_Bplus->SetYTitle("Entries / (20 MeV/c^{2})");
  h0_Bplus->GetYaxis()->CenterTitle();
  h0_Bplus->GetYaxis()->SetLabelFont(42);
  h0_Bplus->GetYaxis()->SetLabelSize(0.035);
  h0_Bplus->GetYaxis()->SetTitleSize(0.055);
  h0_Bplus->GetYaxis()->SetTitleFont(42);
  h0_Bplus->SetStats(0);
  //h0_Bplus->SetTitleOffset(1.5,"Y");
  h0_Bplus->SetTitleOffset(1.10,"Y");
  h0_Bplus->SetAxisRange(0,h0_Bplus->GetMaximum()*1.2,"Y");
  h0_Bplus->Draw("e");

  Bkpi0_Bplus->SetFillColor(kGreen+1);
  //Bkpi0_Bplus->SetFillStyle(3004);
  Bkpi0_Bplus->SetFillStyle(3005);
  Bkpi0_Bplus->SetLineColor(kGreen+1);
  Bkpi0_Bplus->SetLineWidth(3);
  //Bkpi0_Bplus->SetRange(5.00,5.28);
  Bkpi0_Bplus->SetRange(5.00,6.00);
  Bkpi0_Bplus->SetLineStyle(1);
  Bkpi0_Bplus->Draw("same");

  background0_Bplus->SetLineColor(4);
  background0_Bplus->SetLineWidth(3);
  background0_Bplus->SetLineStyle(2);
  background0_Bplus->SetRange(5,6);
  background0_Bplus->Draw("same");   

  mass0_Bplus->SetFillColor(kOrange-3);
  mass0_Bplus->SetFillStyle(3004);
  mass0_Bplus->SetLineColor(kOrange-3);
  mass0_Bplus->SetLineWidth(3);
  mass0_Bplus->SetLineStyle(2);
  mass0_Bplus->SetRange(5,6);
  mass0_Bplus->Draw("same");

  f0_Bplus->SetLineColor(kRed);
  f0_Bplus->SetLineWidth(2);
  //f0_Bplus->SetRange(5,6);  
  f0_Bplus->Draw("same");
  h0_Bplus->Draw("samee");
/*
  TPaveText *tx = new TPaveText(0.20,0.70,0.50,0.80);
  tx->AddText("CMS p+Pb #sqrt{s_{NN}}= 5.02 TeV");
  tx->AddText("CMS");
  tx->AddText(Form("%.0f<p_{T}^{B}<%.0f GeV/c",10.0,15.0));
  tx->Draw("same");
*/

  TLegend *leg = new TLegend(0.53,0.50,0.78,0.73,NULL,"brNDC");

  //leg->AddEntry(h0_Bplus,"CMS","");
  //leg->AddEntry(h0_Bplus,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","");
  //leg->AddEntry(h0_Bplus,Form("%.0f<p_{T}^{B}<%.0f GeV/c",10.0,15.0),"");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.042);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry(h0_Bplus,"Data","pl");
  leg->AddEntry(f0_Bplus,"Fit","l");
  leg->AddEntry(mass0_Bplus,"Signal","f");
  leg->AddEntry(background0_Bplus,"Combinatorial","l");
  leg->AddEntry(Bkpi0_Bplus,"B #rightarrow J/#psi X","f");
  leg->Draw();

   TLatex *   tex = new TLatex(0.1612903,0.88,"CMS");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

   tex = new TLatex(0.55,0.88,"pPb #sqrt{s_{NN}}= 5.02 TeV");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.69,0.81,"L = 34.8 nb^{-1}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.1612903,0.81,"10<p_{T}^{B}<15 GeV/c");
//      tex = new TLatex(0.671371,0.81,"10<p_{T}^{B}<15 GeV/c");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.1612903,0.75,"|y_{LAB}| < 2.4");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();    

      tex = new TLatex(0.8528226,0.6849894,"B^{+}");
      //tex = new TLatex(0.1612903,0.6849894,"B^{+}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();

/*
   TLegend *leg2 = myLegend(0.44,0.33,0.89,0.50);
   leg2->AddEntry(h0_Bplus,"B meson","");
   leg2->AddEntry(h0_Bplus,Form("M_{B}=%.2f #pm %.2f MeV/c^{2}",mass->GetParameter(1)*1000.,mass->GetParError(1)*1000.),"");
   leg2->AddEntry(h0_Bplus,Form("N_{B}=%.0f #pm %.0f", yield, yieldErr),"");
   leg2->Draw();
*/
  pad2->cd();
  //cSigma->cd(2); 
  ci = TColor::GetColor("#000099");
  h0_Bzero->SetLineColor(ci);
  h0_Bzero->SetMarkerStyle(24);
  h0_Bzero->SetMarkerSize(0.8);
  h0_Bzero->SetXTitle("M_{B} (GeV/c^{2})");
  h0_Bzero->GetXaxis()->CenterTitle();
  h0_Bzero->GetXaxis()->SetLabelFont(42);
  h0_Bzero->GetXaxis()->SetLabelSize(0.035);
  h0_Bzero->GetXaxis()->SetTitleSize(0.055);
  h0_Bzero->GetXaxis()->SetTitleFont(42);
  h0_Bzero->SetYTitle("Entries / (20 MeV/c^{2})");
  h0_Bzero->GetYaxis()->CenterTitle();
  h0_Bzero->GetYaxis()->SetLabelFont(42);
  h0_Bzero->GetYaxis()->SetLabelSize(0.035);
  h0_Bzero->GetYaxis()->SetTitleSize(0.055);
  h0_Bzero->GetYaxis()->SetTitleFont(42);
  h0_Bzero->SetStats(0);
  //h0_Bzero->SetTitleOffset(1.5,"Y");
  h0_Bzero->SetTitleOffset(1.10,"Y");
  h0_Bzero->SetAxisRange(0,h0_Bzero->GetMaximum()*1.2,"Y");
  h0_Bzero->Draw("e");

  Bkpi0_Bzero->SetFillColor(kGreen+1);
  //Bkpi0_Bzero->SetFillStyle(3004);
  Bkpi0_Bzero->SetFillStyle(3005);
  Bkpi0_Bzero->SetLineColor(kGreen+1);
  Bkpi0_Bzero->SetLineWidth(3);
  //Bkpi0_Bzero->SetRange(5.00,5.28);
  Bkpi0_Bzero->SetRange(5.00,6.00);
  Bkpi0_Bzero->SetLineStyle(1);
  Bkpi0_Bzero->Draw("same");

  background0_Bzero->SetLineColor(4);
  background0_Bzero->SetLineWidth(3);
  background0_Bzero->SetLineStyle(2);
  background0_Bzero->SetRange(5,6);
  background0_Bzero->Draw("same");   

  mass0_Bzero->SetFillColor(kOrange-3);
  mass0_Bzero->SetFillStyle(3004);
  mass0_Bzero->SetLineColor(kOrange-3);
  mass0_Bzero->SetLineWidth(3);
  mass0_Bzero->SetLineStyle(2);
  mass0_Bzero->SetRange(5,6);
  mass0_Bzero->Draw("same");

  f0_Bzero->SetLineColor(kRed);
  f0_Bzero->SetLineWidth(2);
  //f0_Bzero->SetRange(5,6);  
  f0_Bzero->Draw("same");
  h0_Bzero->Draw("samee");
  leg->Draw();

   tex = new TLatex(0.1612903,0.88,"CMS");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

   tex = new TLatex(0.55,0.88,"pPb #sqrt{s_{NN}}= 5.02 TeV");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.69,0.81,"L = 34.8 nb^{-1}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.1612903,0.81,"10<p_{T}^{B}<15 GeV/c");
//      tex = new TLatex(0.671371,0.81,"10<p_{T}^{B}<15 GeV/c");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.1612903,0.75,"|y_{LAB}| < 2.4");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();    

      tex = new TLatex(0.8528226,0.6849894,"B^{0}");
      //tex = new TLatex(0.1612903,0.6849894,"B^{+}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();

  pad3->cd();
  //cSigma->cd(3);
  ci = TColor::GetColor("#000099");
  h0_Bs->SetLineColor(ci);
  h0_Bs->SetMarkerStyle(24);
  h0_Bs->SetMarkerSize(0.8);
  h0_Bs->SetXTitle("M_{B} (GeV/c^{2})");
  h0_Bs->GetXaxis()->CenterTitle();
  h0_Bs->GetXaxis()->SetLabelFont(42);
  h0_Bs->GetXaxis()->SetLabelSize(0.035);
  h0_Bs->GetXaxis()->SetTitleSize(0.055);
  h0_Bs->GetXaxis()->SetTitleFont(42);
  h0_Bs->SetYTitle("Entries / (20 MeV/c^{2})");
  h0_Bs->GetYaxis()->CenterTitle();
  h0_Bs->GetYaxis()->SetLabelFont(42);
  h0_Bs->GetYaxis()->SetLabelSize(0.035);
  h0_Bs->GetYaxis()->SetTitleSize(0.055);
  h0_Bs->GetYaxis()->SetTitleFont(42);
  h0_Bs->SetStats(0);
  //h0_Bs->SetTitleOffset(1.5,"Y");
  h0_Bs->SetTitleOffset(1.10,"Y");
  h0_Bs->SetAxisRange(0,h0_Bs->GetMaximum()*1.2,"Y");
  h0_Bs->Draw("e");

  Bkpi0_Bs->SetFillColor(kGreen+1);
  //Bkpi0_Bs->SetFillStyle(3004);
  Bkpi0_Bs->SetFillStyle(3005);
  Bkpi0_Bs->SetLineColor(kGreen+1);
  Bkpi0_Bs->SetLineWidth(3);
  //Bkpi0_Bs->SetRange(5.00,5.28);
  Bkpi0_Bs->SetRange(5.00,6.00);
  Bkpi0_Bs->SetLineStyle(1);
  //Bkpi0_Bs->Draw("same");

  background0_Bs->SetLineColor(4);
  background0_Bs->SetLineWidth(3);
  background0_Bs->SetLineStyle(2);
  background0_Bs->SetRange(5,6);
  background0_Bs->Draw("same");   

  mass0_Bs->SetFillColor(kOrange-3);
  mass0_Bs->SetFillStyle(3004);
  mass0_Bs->SetLineColor(kOrange-3);
  mass0_Bs->SetLineWidth(3);
  mass0_Bs->SetLineStyle(2);
  mass0_Bs->SetRange(5,6);
  mass0_Bs->Draw("same");

  f0_Bs->SetLineColor(kRed);
  f0_Bs->SetLineWidth(2);
  //f0_Bs->SetRange(5,6);  
  f0_Bs->Draw("same");
  h0_Bs->Draw("samee");
  TLegend *leg2 = new TLegend(0.53,0.50,0.78,0.73,NULL,"brNDC");
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.042);
  leg2->SetTextFont(42);
  leg2->SetFillStyle(0);
  leg2->AddEntry(h0_Bs,"Data","pl");
  leg2->AddEntry(f0_Bs,"Fit","l");
  leg2->AddEntry(mass0_Bs,"Signal","f");
  leg2->AddEntry(background0_Bs,"Combinatorial","l");
  leg2->Draw();

   tex = new TLatex(0.1612903,0.88,"CMS");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

   tex = new TLatex(0.55,0.88,"pPb #sqrt{s_{NN}}= 5.02 TeV");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.69,0.81,"L = 34.8 nb^{-1}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.1612903,0.81,"10<p_{T}^{B}<60 GeV/c");
//      tex = new TLatex(0.671371,0.81,"10<p_{T}^{B}<15 GeV/c");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.1612903,0.75,"|y_{LAB}| < 2.4");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();    

      tex = new TLatex(0.8528226,0.6849894,"B_{s}");
      //tex = new TLatex(0.1612903,0.6849894,"B^{+}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();


  cSigma->SaveAs("paperfig_fitplot_lowestptbin.pdf");
////////////////////////////////////////////////////////////////
  cSigma->cd(1);
  //h0_Bplus->Draw("pe");
  ci = TColor::GetColor("#000099");
  h5_Bplus->SetLineColor(ci);
  h5_Bplus->SetMarkerStyle(24);
  h5_Bplus->SetMarkerSize(0.8);
  h5_Bplus->SetXTitle("M_{B} (GeV/c^{2})");
  h5_Bplus->GetXaxis()->CenterTitle();
  h5_Bplus->GetXaxis()->SetLabelFont(42);
  h5_Bplus->GetXaxis()->SetLabelSize(0.035);
  h5_Bplus->GetXaxis()->SetTitleSize(0.055);
  h5_Bplus->GetXaxis()->SetTitleFont(42);
  h5_Bplus->SetYTitle("Entries / (20 MeV/c^{2})");
  h5_Bplus->GetYaxis()->CenterTitle();
  h5_Bplus->GetYaxis()->SetLabelFont(42);
  h5_Bplus->GetYaxis()->SetLabelSize(0.035);
  h5_Bplus->GetYaxis()->SetTitleSize(0.055);
  h5_Bplus->GetYaxis()->SetTitleFont(42);
  h5_Bplus->SetStats(0);
  //h5_Bplus->SetTitleOffset(1.5,"Y");
  h5_Bplus->SetTitleOffset(1.10,"Y");
  h5_Bplus->SetAxisRange(0,h5_Bplus->GetMaximum()*1.2,"Y");
  h5_Bplus->Draw("e");

  Bkpi5_Bplus->SetFillColor(kGreen+1);
  //Bkpi5_Bplus->SetFillStyle(3004);
  Bkpi5_Bplus->SetFillStyle(3005);
  Bkpi5_Bplus->SetLineColor(kGreen+1);
  Bkpi5_Bplus->SetLineWidth(3);
  //Bkpi5_Bplus->SetRange(5.00,5.28);
  Bkpi5_Bplus->SetRange(5.00,6.00);
  Bkpi5_Bplus->SetLineStyle(1);
  Bkpi5_Bplus->Draw("same");

  background5_Bplus->SetLineColor(4);
  background5_Bplus->SetLineWidth(3);
  background5_Bplus->SetLineStyle(2);
  background5_Bplus->SetRange(5,6);
  background5_Bplus->Draw("same");   

  mass5_Bplus->SetFillColor(kOrange-3);
  mass5_Bplus->SetFillStyle(3004);
  mass5_Bplus->SetLineColor(kOrange-3);
  mass5_Bplus->SetLineWidth(3);
  mass5_Bplus->SetLineStyle(2);
  mass5_Bplus->SetRange(5,6);
  mass5_Bplus->Draw("same");

  f5_Bplus->SetLineColor(kRed);
  f5_Bplus->SetLineWidth(2);
  //f5_Bplus->SetRange(5,6);  
  f5_Bplus->Draw("same");
  h5_Bplus->Draw("samee");
/*
  TPaveText *tx = new TPaveText(0.20,0.70,0.50,0.80);
  tx->AddText("CMS p+Pb #sqrt{s_{NN}}= 5.02 TeV");
  tx->AddText("CMS");
  tx->AddText(Form("%.0f<p_{T}^{B}<%.0f GeV/c",10.0,15.0));
  tx->Draw("same");
*/

  leg->Draw();

   tex = new TLatex(0.1612903,0.88,"CMS");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

   tex = new TLatex(0.55,0.88,"pPb #sqrt{s_{NN}}= 5.02 TeV");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.69,0.81,"L = 34.8 nb^{-1}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.1612903,0.81,"10<p_{T}^{B}<60 GeV/c");
//      tex = new TLatex(0.671371,0.81,"10<p_{T}^{B}<15 GeV/c");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.1612903,0.75,"|y_{LAB}| < 2.4");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();    

      tex = new TLatex(0.8528226,0.6849894,"B^{+}");
      //tex = new TLatex(0.1612903,0.6849894,"B^{+}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();

/*
   TLegend *leg2 = myLegend(0.44,0.33,0.89,0.50);
   leg2->AddEntry(h0_Bplus,"B meson","");
   leg2->AddEntry(h0_Bplus,Form("M_{B}=%.2f #pm %.2f MeV/c^{2}",mass->GetParameter(1)*1000.,mass->GetParError(1)*1000.),"");
   leg2->AddEntry(h0_Bplus,Form("N_{B}=%.0f #pm %.0f", yield, yieldErr),"");
   leg2->Draw();
*/
  cSigma->cd(2); 
  ci = TColor::GetColor("#000099");
  h3_Bzero->SetLineColor(ci);
  h3_Bzero->SetMarkerStyle(24);
  h3_Bzero->SetMarkerSize(0.8);
  h3_Bzero->SetXTitle("M_{B} (GeV/c^{2})");
  h3_Bzero->GetXaxis()->CenterTitle();
  h3_Bzero->GetXaxis()->SetLabelFont(42);
  h3_Bzero->GetXaxis()->SetLabelSize(0.035);
  h3_Bzero->GetXaxis()->SetTitleSize(0.055);
  h3_Bzero->GetXaxis()->SetTitleFont(42);
  h3_Bzero->SetYTitle("Entries / (20 MeV/c^{2})");
  h3_Bzero->GetYaxis()->CenterTitle();
  h3_Bzero->GetYaxis()->SetLabelFont(42);
  h3_Bzero->GetYaxis()->SetLabelSize(0.035);
  h3_Bzero->GetYaxis()->SetTitleSize(0.055);
  h3_Bzero->GetYaxis()->SetTitleFont(42);
  h3_Bzero->SetStats(0);
  //h3_Bzero->SetTitleOffset(1.5,"Y");
  h3_Bzero->SetTitleOffset(1.10,"Y");
  h3_Bzero->SetAxisRange(0,h3_Bzero->GetMaximum()*1.2,"Y");
  h3_Bzero->Draw("e");

  Bkpi3_Bzero->SetFillColor(kGreen+1);
  //Bkpi3_Bzero->SetFillStyle(3004);
  Bkpi3_Bzero->SetFillStyle(3005);
  Bkpi3_Bzero->SetLineColor(kGreen+1);
  Bkpi3_Bzero->SetLineWidth(3);
  //Bkpi3_Bzero->SetRange(5.00,5.28);
  Bkpi3_Bzero->SetRange(5.00,6.00);
  Bkpi3_Bzero->SetLineStyle(1);
  Bkpi3_Bzero->Draw("same");

  background3_Bzero->SetLineColor(4);
  background3_Bzero->SetLineWidth(3);
  background3_Bzero->SetLineStyle(2);
  background3_Bzero->SetRange(5,6);
  background3_Bzero->Draw("same");   

  mass3_Bzero->SetFillColor(kOrange-3);
  mass3_Bzero->SetFillStyle(3004);
  mass3_Bzero->SetLineColor(kOrange-3);
  mass3_Bzero->SetLineWidth(3);
  mass3_Bzero->SetLineStyle(2);
  mass3_Bzero->SetRange(5,6);
  mass3_Bzero->Draw("same");

  f3_Bzero->SetLineColor(kRed);
  f3_Bzero->SetLineWidth(2);
  //f3_Bzero->SetRange(5,6);  
  f3_Bzero->Draw("same");
  h3_Bzero->Draw("samee");
  leg->Draw();

   tex = new TLatex(0.1612903,0.88,"CMS");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

   tex = new TLatex(0.55,0.88,"pPb #sqrt{s_{NN}}= 5.02 TeV");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.69,0.81,"L = 34.8 nb^{-1}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.1612903,0.81,"10<p_{T}^{B}<60 GeV/c");
//      tex = new TLatex(0.671371,0.81,"10<p_{T}^{B}<15 GeV/c");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.1612903,0.75,"|y_{LAB}| < 2.4");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();    

      tex = new TLatex(0.8528226,0.6849894,"B^{0}");
      //tex = new TLatex(0.1612903,0.6849894,"B^{+}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();

  cSigma->cd(3);
  ci = TColor::GetColor("#000099");
  h0_Bs->SetLineColor(ci);
  h0_Bs->SetMarkerStyle(24);
  h0_Bs->SetMarkerSize(0.8);
  h0_Bs->SetXTitle("M_{B} (GeV/c^{2})");
  h0_Bs->GetXaxis()->CenterTitle();
  h0_Bs->GetXaxis()->SetLabelFont(42);
  h0_Bs->GetXaxis()->SetLabelSize(0.035);
  h0_Bs->GetXaxis()->SetTitleSize(0.055);
  h0_Bs->GetXaxis()->SetTitleFont(42);
  h0_Bs->SetYTitle("Entries / (20 MeV/c^{2})");
  h0_Bs->GetYaxis()->CenterTitle();
  h0_Bs->GetYaxis()->SetLabelFont(42);
  h0_Bs->GetYaxis()->SetLabelSize(0.035);
  h0_Bs->GetYaxis()->SetTitleSize(0.055);
  h0_Bs->GetYaxis()->SetTitleFont(42);
  h0_Bs->SetStats(0);
  //h0_Bs->SetTitleOffset(1.5,"Y");
  h0_Bs->SetTitleOffset(1.10,"Y");
  h0_Bs->SetAxisRange(0,h0_Bs->GetMaximum()*1.2,"Y");
  h0_Bs->Draw("e");

  Bkpi0_Bs->SetFillColor(kGreen+1);
  //Bkpi0_Bs->SetFillStyle(3004);
  Bkpi0_Bs->SetFillStyle(3005);
  Bkpi0_Bs->SetLineColor(kGreen+1);
  Bkpi0_Bs->SetLineWidth(3);
  //Bkpi0_Bs->SetRange(5.00,5.28);
  Bkpi0_Bs->SetRange(5.00,6.00);
  Bkpi0_Bs->SetLineStyle(1);
  //Bkpi0_Bs->Draw("same");

  background0_Bs->SetLineColor(4);
  background0_Bs->SetLineWidth(3);
  background0_Bs->SetLineStyle(2);
  background0_Bs->SetRange(5,6);
  background0_Bs->Draw("same");   

  mass0_Bs->SetFillColor(kOrange-3);
  mass0_Bs->SetFillStyle(3004);
  mass0_Bs->SetLineColor(kOrange-3);
  mass0_Bs->SetLineWidth(3);
  mass0_Bs->SetLineStyle(2);
  mass0_Bs->SetRange(5,6);
  mass0_Bs->Draw("same");

  f0_Bs->SetLineColor(kRed);
  f0_Bs->SetLineWidth(2);
  //f0_Bs->SetRange(5,6);  
  f0_Bs->Draw("same");
  h0_Bs->Draw("samee");
  leg2->Draw();

   tex = new TLatex(0.1612903,0.88,"CMS");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

   tex = new TLatex(0.55,0.88,"pPb #sqrt{s_{NN}}= 5.02 TeV");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.69,0.81,"L = 34.8 nb^{-1}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.1612903,0.81,"10<p_{T}^{B}<60 GeV/c");
//      tex = new TLatex(0.671371,0.81,"10<p_{T}^{B}<15 GeV/c");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();

      tex = new TLatex(0.1612903,0.75,"|y_{LAB}| < 2.4");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();    

      tex = new TLatex(0.8528226,0.6849894,"B_{s}");
      //tex = new TLatex(0.1612903,0.6849894,"B^{+}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();


  cSigma->SaveAs("paperfig_fitplot_integptbin.pdf");

}
