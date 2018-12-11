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
#include <TLine.h>

//double luminosity=34.8*1e-3;
double luminosity=34.6*1e-3;


double setparam0=100.;
double setparam1=5.28;
double setparam2=0.05;
double setparam3=0.03;
double fixparam1=5.279;

TLatex* tex;

void drawplots(TH1D* h, TH1D* hMC, TF1* f, TF1* background, TF1* fBkpi, TF1* fmass, TH1D* hraw, std::string str, int i)
{
	//cSigma->cd(1);
	//h->Draw("pe");
	TH1F* hempty=new TH1F("hempty","", 50, 5.0, 6.0);
	hempty->GetXaxis()->CenterTitle();
	hempty->GetYaxis()->CenterTitle();
	hempty->GetXaxis()->SetTitle("m_{B} (GeV/c^{2})");
	if (str=="B^{+}+B^{-}") hempty->SetYTitle("Entries / (20 MeV/c^{2})");
	else if (str=="B^{#lower[0.2]{0}}+#bar{B^{#lower[0.2]{0}}}") hempty->SetYTitle("Entries / (30 MeV/c^{2})");
	else if (str=="B_{s}^{#lower[0.1]{0}}+#bar{B_{s}^{#lower[0.1]{0}}}") hempty->SetYTitle("Entries / (40 MeV/c^{2})");
	hempty->GetXaxis()->SetTitleOffset(1.1);//0.95
	hempty->GetYaxis()->SetTitleOffset(1.4);//1.30
	hempty->GetXaxis()->SetTitleSize(0.055);
	hempty->GetYaxis()->SetTitleSize(0.055);//###0.055
	hempty->GetXaxis()->SetTitleFont(42);
	hempty->GetYaxis()->SetTitleFont(42);
	hempty->GetXaxis()->SetLabelFont(42);
	hempty->GetYaxis()->SetLabelFont(42);
	hempty->GetXaxis()->SetLabelSize(0.055);//###0.055
	hempty->GetYaxis()->SetLabelSize(0.055);//###0.055
	double axisymin=-0.05;
	hempty->SetAxisRange(axisymin,h->GetMaximum()*1.2,"Y");
	hempty->SetStats(0);
	hempty->GetXaxis()->SetNdivisions(-50205);
	hempty->Draw();
	//////////////////////////////////////////////////
	Int_t ci = TColor::GetColor("#000099");
	h->SetLineColor(ci);
	h->SetMarkerStyle(20);
	h->SetMarkerSize(1.55);
	h->SetLineWidth(4);
	h->SetLineColor(1);
	TF1 *myfunc = h->GetFunction(Form("f%d",i));
	myfunc->SetLineColor(kRed);
	myfunc->SetLineWidth(4);
    myfunc->SetNpx(5000);
	/*
	//###h->SetXTitle("M_{B} (GeV/c^{2})");
	h->SetXTitle("m_{B} (GeV/c^{2})");
	h->GetXaxis()->CenterTitle();
	h->GetXaxis()->SetLabelFont(42);
	h->GetXaxis()->SetLabelSize(0.060);//0.05
	h->GetXaxis()->SetTitleSize(0.070);//0.055
	h->GetXaxis()->SetTitleFont(42);
	h->GetXaxis()->SetTitleOffset(0.90);//0.95
	if (str=="B^{+}+B^{-}") h->SetYTitle("Entries / (20 MeV/c^{2})");
	else if (str=="B^{#lower[0.2]{0}}+#bar{B^{#lower[0.2]{0}}}") h->SetYTitle("Entries / (30 MeV/c^{2})");
	else if (str=="B_{s}^{#lower[0.1]{0}}+#bar{B_{s}^{#lower[0.1]{0}}}") h->SetYTitle("Entries / (40 MeV/c^{2})");
	h->GetYaxis()->CenterTitle();
	h->GetYaxis()->SetLabelFont(42);
	h->GetYaxis()->SetLabelSize(0.060);//0.05
	h->GetYaxis()->SetTitleSize(0.070);//0.055
	h->GetYaxis()->SetTitleFont(42);
	//###if (str=="B^{+}+B^{-}") h->GetYaxis()->SetTitleOffset(1.140);//1.30
	//###else h->GetYaxis()->SetTitleOffset(0.95);//1.30
	if (str=="B^{+}+B^{-}" || str=="B^{#lower[0.2]{0}}+#bar{B^{#lower[0.2]{0}}}") h->GetYaxis()->SetTitleOffset(1.140);//1.30
	else h->GetYaxis()->SetTitleOffset(0.95);//1.30
	*/

	h->SetStats(0);
	//h->SetTitleOffset(1.5,"Y");
	//h->SetTitleOffset(1.10,"Y");
	/*
	   double axisymin=-0.05;
	   h->SetAxisRange(axisymin,h->GetMaximum()*1.2,"Y");
	   h->SetAxisRange(5.0,6.0,"X");
	   */
	h->Draw("samee");

	//###  fBkpi->SetFillColor(kGreen+1);
	fBkpi->SetFillColor(kGreen+4);
	//fBkpi->SetFillStyle(3004);
	fBkpi->SetFillStyle(3005);
	//###  fBkpi->SetLineColor(kGreen+1);
	fBkpi->SetLineColor(kGreen+4);
	fBkpi->SetLineWidth(4);
	//fBkpi->SetRange(5.00,5.28);
	//###fBkpi->SetRange(5.00,6.00);
	if (str=="B^{+}+B^{-}") fBkpi->SetRange(5.00,5.40);
	else if (str=="B^{#lower[0.2]{0}}+#bar{B^{#lower[0.2]{0}}}") fBkpi->SetRange(5.00,5.40);
	else if (str=="B_{s}^{#lower[0.1]{0}}+#bar{B_{s}^{#lower[0.1]{0}}}") fBkpi->SetRange(0.00,1.00);


	fBkpi->SetLineStyle(1);
	if (str=="B^{+}+B^{-}" || str=="B^{#lower[0.2]{0}}+#bar{B^{#lower[0.2]{0}}}") fBkpi->Draw("same");

	background->SetLineColor(4);
	background->SetLineWidth(4);
	background->SetLineStyle(2);
	background->SetRange(5,6);
	background->Draw("same");   

	fmass->SetFillColor(kOrange-3);
	fmass->SetFillStyle(3002);
	fmass->SetLineColor(kOrange-3);
	fmass->SetLineWidth(4);
	fmass->SetLineStyle(2);
	//###fmass->SetRange(5,6);
	if (str=="B^{+}+B^{-}") fmass->SetRange(5.16,5.40);
	else if (str=="B^{#lower[0.2]{0}}+#bar{B^{#lower[0.2]{0}}}") fmass->SetRange(5.16,5.40);
	else if (str=="B_{s}^{#lower[0.1]{0}}+#bar{B_{s}^{#lower[0.1]{0}}}") fmass->SetRange(5.28,5.46);


	fmass->Draw("same");

	f->SetLineColor(kRed);
	f->SetLineWidth(4);
	//f->SetRange(5,6);  
	f->Draw("same");

	hraw->SetMarkerStyle(20);
	hraw->Draw("samee");
	TLine* line0;
	/*
	   if (str=="B^{+}+B^{-}") line0 = new TLine(5.000,axisymin,6.000,axisymin);
	   else if (str=="B^{#lower[0.2]{0}}+#bar{B^{#lower[0.2]{0}}}") line0 = new TLine(5.030,axisymin,5.930,axisymin);
	   else if (str=="B_{s}^{#lower[0.1]{0}}+#bar{B_{s}^{#lower[0.1]{0}}}") line0 = new TLine(5.030,axisymin,5.990,axisymin);
	   */
	if (str=="B^{+}+B^{-}") line0 = new TLine(5.000,axisymin,6.000,axisymin);
	else if (str=="B^{#lower[0.2]{0}}+#bar{B^{#lower[0.2]{0}}}") line0 = new TLine(5.000,axisymin,6.000,axisymin);
	else if (str=="B_{s}^{#lower[0.1]{0}}+#bar{B_{s}^{#lower[0.1]{0}}}") line0 = new TLine(5.000,axisymin,6.000,axisymin);

	line0->SetLineColor(kBlack);
	line0->SetLineWidth(2);//###2.5
	line0->Draw("same");
	//h->Draw("samee");

	/*
	   TPaveText *tx = new TPaveText(0.20,0.70,0.50,0.80);
	   tx->AddText("CMS p+Pb #sqrt{s_{NN}}= 5.02 TeV");
	   tx->AddText("CMS");
	   tx->AddText(Form("%.0f<p_{T}^{B}<%.0f GeV/c",10.0,15.0));
	   tx->Draw("same");
	   */

	//###  TLegend *leg = new TLegend(0.54,0.38,0.82,0.65,NULL,"brNDC");
	//###  TLegend *leg = new TLegend(0.525,0.335,0.85,0.65,NULL,"brNDC");
	TLegend *leg = new TLegend(0.525,0.38,0.85,0.70,NULL,"brNDC");


	//leg->AddEntry(h0_Bplus,"CMS","");
	//leg->AddEntry(h0_Bplus,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","");
	//leg->AddEntry(h0_Bplus,Form("%.0f<p_{T}^{B}<%.0f GeV/c",10.0,15.0),"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.060);//0.050
	leg->SetTextFont(42);
	leg->SetFillStyle(0);
	leg->AddEntry(h,"Data","pl");
	leg->AddEntry(f,"Fit","l");
	leg->AddEntry(fmass,"Signal","f");
	leg->AddEntry(background,"Combinatorial","l");
	if (str=="B^{+}+B^{-}" || str=="B^{#lower[0.2]{0}}+#bar{B^{#lower[0.2]{0}}}") leg->AddEntry(fBkpi,"B #rightarrow J/#psi X","f");
	leg->Draw();


}    
void drawtex(std::string str, int ptmin, int ptmax)
{
	//      tex = new TLatex(0.4552936,0.9418305,"34.8 nb^{-1} (pPb 5.02 TeV)");
	//tex = new TLatex(0.50,0.94,"34.8 nb^{-1} (pPb 5.02 TeV)");
	//###tex = new TLatex(0.49,0.94,"34.6 nb^{-1} (pPb 5.02 TeV)");
	if (str=="B^{+}+B^{-}") tex = new TLatex(0.41,0.94,"34.6 nb^{-1} (pPb 5.02 TeV)");
	else tex = new TLatex(0.39,0.94,"34.6 nb^{-1} (pPb 5.02 TeV)");

	tex->SetNDC();
	tex->SetTextFont(42);
	//   tex->SetTextSize(0.05266854);
	tex->SetTextSize(0.06);//0.05
	tex->SetLineWidth(2);
	tex->Draw();
	//TLatex *   tex = new TLatex(0.1837838,0.8523297,"CMS");
	//tex = new TLatex(0.19,0.84,"CMS");
	tex = new TLatex(0.19,0.86,"CMS");
	tex->SetNDC();
	//tex->SetTextSize(0.06379928);
	tex->SetTextSize(0.07);//0.06
	tex->SetLineWidth(2);
	tex->SetTextFont(62);
	tex->Draw();
	/*
	   tex = new TLatex(0.19,0.81,"Preliminary");
	   tex->SetNDC();
	//tex->SetTextSize(0.06379928);
	tex->SetTextSize(0.05);//0.06
	tex->SetLineWidth(2);
	tex->SetTextFont(52);
	tex->Draw();
	*/
	//      tex = new TLatex(0.1891892,0.771261,"B^{+}+B^{-}");
	//      tex = new TLatex(0.19,0.75,str.c_str());
	tex = new TLatex(0.19,0.73,str.c_str());
	tex->SetNDC();
	tex->SetTextFont(42);
	//   tex->SetTextSize(0.0585206);
	tex->SetTextSize(0.07);//0.06
	//tex->SetLineWidth(2);
	tex->SetLineWidth(1);
	tex->Draw();
	//      tex = new TLatex(0.5581628,0.7721208,"10<p_{T}^{B}<60 GeV/c");
	//###      tex = new TLatex(0.605,0.75,Form("%i<p_{T}^{B}<%i GeV/c",ptmin,ptmax));

	//###    if (str=="B^{+}+B^{-}") tex = new TLatex(0.488,0.75,Form("%i < p_{T}^{B} < %i GeV/c",ptmin,ptmax));
	//###    else tex = new TLatex(0.480,0.75,Form("%i < p_{T}^{B} < %i GeV/c",ptmin,ptmax));
	//###if (str=="B^{+}+B^{-}") tex = new TLatex(0.488,0.84,Form("%i < p_{T}^{B} < %i GeV/c",ptmin,ptmax));
	//###else tex = new TLatex(0.480,0.84,Form("%i < p_{T}^{B} < %i GeV/c",ptmin,ptmax));
	if (str=="B^{+}+B^{-}") tex = new TLatex(0.488,0.84,Form("%i < p_{T} < %i GeV/c",ptmin,ptmax));
	else tex = new TLatex(0.480,0.84,Form("%i < p_{T} < %i GeV/c",ptmin,ptmax));
	tex->SetNDC();
	tex->SetTextFont(42);
	//   tex->SetTextSize(0.05266854);
	tex->SetTextSize(0.06);//0.05
	tex->SetLineWidth(2);
	tex->Draw();
	//      tex = new TLatex(0.6804938,0.696044,"|y_{LAB}| < 2.4");
	//###      tex = new TLatex(0.72,0.68,"|y_{LAB}| < 2.4");
	//###      tex = new TLatex(0.685,0.68,"|y_{LAB}| < 2.4");
	tex = new TLatex(0.700,0.77,"|y_{lab}| < 2.4");//0.685
	tex->SetNDC();
	tex->SetTextFont(42);
	//   tex->SetTextSize(0.05266854);
	tex->SetTextSize(0.06);//0.05
	tex->SetLineWidth(2);
	tex->Draw();
}
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
	gStyle->SetPadRightMargin(0.020);
	gStyle->SetPadLeftMargin(0.165);//0.145
	gStyle->SetPadTopMargin(0.075);
	gStyle->SetPadBottomMargin(0.145);


	TFile *infBplus = new TFile("../../ResultsBplus/SigmaBplus_extend.root");
	TFile *infBzero = new TFile("../../ResultsBzero/SigmaBzero_extend.root");
	TFile *infBs = new TFile("../../ResultsBs/SigmaBs_extend.root");

	//  TFile *infBplus = new TFile("/afs/cern.ch/work/h/hckim/public/Plotsforpaper/ResultsBplus/SigmaBplus.root");
	//  TFile *infBzero = new TFile("/afs/cern.ch/work/h/hckim/public/Plotsforpaper/ResultsBzero/SigmaBzero.root");
	//  TFile *infBs = new TFile("/afs/cern.ch/work/h/hckim/public/Plotsforpaper/ResultsBs/SigmaBs.root");

	TCanvas *cSigma=  new TCanvas("cSigma","",600,600);
	cSigma->Clear();

	int ptbinBp[6] = {10,15,20,25,30,60};
	for(int i = 0; i < 5; i++){
		TH1D *h0_Bplus = (TH1D*)infBplus->Get(Form("h%d",i));
		TH1D *hMC0_Bplus = (TH1D*)infBplus->Get(Form("hMC%d",i));
		TF1 *f0_Bplus = (TF1*)infBplus->Get(Form("f%d",i));
		TF1 *background0_Bplus = (TF1*)infBplus->Get(Form("background%d",i));
		TF1 *Bkpi0_Bplus = (TF1*)infBplus->Get(Form("fBkpi%d",i));
		TF1 *mass0_Bplus = (TF1*)infBplus->Get(Form("fmass%d",i));
		TH1D *hraw0_Bplus = (TH1D*)infBplus->Get(Form("hraw%d",i));
		drawplots(h0_Bplus, hMC0_Bplus, f0_Bplus, background0_Bplus, Bkpi0_Bplus, mass0_Bplus, hraw0_Bplus, "B^{+}+B^{-}", i);
		drawtex("B^{+}+B^{-}",ptbinBp[i],ptbinBp[i+1]);
		cSigma->SaveAs(Form("Bplus%d.pdf",i));
	}

	int ptbinBd[4] = {10,15,20,60};
	for(int i = 0; i < 3; i++){
		TH1D *h0_Bzero = (TH1D*)infBzero->Get(Form("h%d",i));
		TH1D *hMC0_Bzero = (TH1D*)infBzero->Get(Form("hMC%d",i));
		TF1 *f0_Bzero = (TF1*)infBzero->Get(Form("f%d",i));
		TF1 *background0_Bzero = (TF1*)infBzero->Get(Form("background%d",i));
		TF1 *Bkpi0_Bzero = (TF1*)infBzero->Get(Form("fBkpi%d",i));
		TF1 *mass0_Bzero = (TF1*)infBzero->Get(Form("fmass%d",i));
		TH1D *hraw0_Bzero = (TH1D*)infBzero->Get(Form("hraw%d",i));
		drawplots(h0_Bzero, hMC0_Bzero, f0_Bzero, background0_Bzero, Bkpi0_Bzero, mass0_Bzero, hraw0_Bzero, "B^{#lower[0.2]{0}}+#bar{B^{#lower[0.2]{0}}}", i);
		drawtex("B^{#lower[0.2]{0}}+#bar{B^{#lower[0.2]{0}}}",ptbinBd[i],ptbinBd[i+1]);
		cSigma->SaveAs(Form("Bzero%d.pdf",i));
	}

	TH1D *h0_Bs = (TH1D*)infBs->Get("h0");
	TH1D *hMC0_Bs = (TH1D*)infBs->Get("hMC0");
	TF1 *f0_Bs = (TF1*)infBs->Get("f0");
	TF1 *background0_Bs = (TF1*)infBs->Get("background0");
	TF1 *Bkpi0_Bs = (TF1*)infBs->Get("fBkpi0");
	TF1 *mass0_Bs = (TF1*)infBs->Get("fmass0");
	TH1D *hraw0_Bs = (TH1D*)infBs->Get("hraw0");
	drawplots(h0_Bs, hMC0_Bs, f0_Bs, background0_Bs, Bkpi0_Bs, mass0_Bs, hraw0_Bs, "B_{s}^{#lower[0.1]{0}}+#bar{B_{s}^{#lower[0.1]{0}}}", 0);
	drawtex("B_{s}^{#lower[0.1]{0}}+#bar{B_{s}^{#lower[0.1]{0}}}",10,60);
	cSigma->SaveAs(Form("Bs%d.pdf",0));
}
