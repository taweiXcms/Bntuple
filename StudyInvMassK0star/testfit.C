#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "utilities.h"
#include "TH1D.h"
#define NUM_BX 9000

double setparam0=100.;
double setparam1=5.28;
double setparam2=0.03;
double fixparam1=5.279;
double setparam3=0.03;
double fixparam2=0.04;


void testfit(int icut=3){

  TFile*fileoutput=new TFile(Form("Results/file_CutId%d.root",icut));
  TH1D*hInvMassSelected_data=(TH1D*)fileoutput->Get("hInvMassSelected_mcNP");
  TH1D*hInvMassSelected_mc=(TH1D*)fileoutput->Get("hInvMassSelected_mc");
  TH1D*hInvMassSelected_mcNP=(TH1D*)fileoutput->Get("hInvMassSelected_mcNP");
  
  TCanvas *c= new TCanvas("canvas","",600,600);
    
  TString iNP="6.71675e+00*Gaus(x,5.30142e+00,8.42680e-02)/(sqrt(2*3.14159)*8.42680e-02)+4.06744e+01*Gaus(x,5.00954e+00,8.11305e-02)/(sqrt(2*3.14159)*8.11305e-02)+5.99974e-01*(2.376716*Gaus(x,5.640619,0.095530)/(sqrt(2*3.14159)*0.095530)+3.702342*Gaus(x,5.501706,0.046222)/(sqrt(2*3.14159)*0.046222))+1.31767e-01*(61.195688*Gaus(x,5.127566,0.087439)/(sqrt(2*3.14159)*0.087439)+58.943919*Gaus(x,5.246471,0.041983)/(sqrt(2*3.14159)*0.041983))";
  TF1 *f = new TF1("f","[0]*([7]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[7])*Gaus(x,[1],[8])/(sqrt(2*3.14159)*[8]))+[3]+[4]*x+[6]*("+iNP+")");
  
  hInvMassSelected_data->Draw();
  f->SetParLimits(4,-1000,0);
  f->SetParLimits(2,0.01,0.05);
  f->SetParLimits(8,0.01,0.1);
  f->SetParLimits(7,0,1);
  f->SetParLimits(6,0,1000);
  
  f->SetParameter(0,setparam0);
  f->SetParameter(1,setparam1);
  f->SetParameter(2,setparam2);
  f->SetParameter(8,setparam3);
  f->FixParameter(1,fixparam1);
  f->FixParameter(6,0);
  hInvMassSelected_data->GetEntries();
  
  hInvMassSelected_mc->Fit("f","q","",5,6);
  hInvMassSelected_mc->Fit("f","q","",5,6);
  f->ReleaseParameter(1);
  hInvMassSelected_mc->Fit("f","L q","",5,6);
  hInvMassSelected_mc->Fit("f","L q","",5,6);
  hInvMassSelected_mc->Fit("f","L q","",5,6);
  hInvMassSelected_mc->Fit("f","L m","",5,6);
  
  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(7,f->GetParameter(7));
  f->FixParameter(8,f->GetParameter(8));
  f->ReleaseParameter(6);
  
  hInvMassSelected_data->Fit("f","q","",5,6);
  hInvMassSelected_data->Fit("f","q","",5,6);
  f->ReleaseParameter(1);
  hInvMassSelected_data->Fit("f","L q","",5,6);
  hInvMassSelected_data->Fit("f","L q","",5,6);
  hInvMassSelected_data->Fit("f","L q","",5,6);
  hInvMassSelected_data->Fit("f","L m","",5,6);
  hInvMassSelected_data->SetMarkerSize(0.8);
  hInvMassSelected_data->SetMarkerStyle(20);
  cout <<hInvMassSelected_data->GetEntries()<<endl;
  
  // function for background shape plotting. take the fit result from f
  TF1 *background = new TF1("background","[0]+[1]*x");
  background->SetParameter(0,f->GetParameter(3));
  background->SetParameter(1,f->GetParameter(4));
  background->SetLineColor(4);
  background->SetRange(5,6);
  background->SetLineStyle(2);
   
  // function for signal shape plotting. take the fit result from f
  TF1 *Bkpi = new TF1("fBkpi","[0]*("+iNP+")");
  Bkpi->SetParameter(0,f->GetParameter(6));
  Bkpi->SetLineColor(kGreen+1);
  Bkpi->SetFillColor(kGreen+1);
  Bkpi->SetRange(5.00,6.00);
  Bkpi->SetLineStyle(1);
  Bkpi->SetFillStyle(3005);

  // function for signal shape plotting. take the fit result from f
  TF1 *mass = new TF1("fmass","[0]*([3]*Gaus(x,[1],[2])/(sqrt(2*3.14159)*[2])+(1-[3])*Gaus(x,[1],[4])/(sqrt(2*3.14159)*[4]))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(8));
  mass->SetParError(0,f->GetParError(0));
  mass->SetParError(1,f->GetParError(1));
  mass->SetParError(2,f->GetParError(2));
  mass->SetParError(7,f->GetParError(7));
  mass->SetParError(8,f->GetParError(8));
  mass->SetLineColor(2);
  mass->SetLineStyle(2);

  hInvMassSelected_data->SetMarkerStyle(24);
  hInvMassSelected_data->SetStats(0);
  hInvMassSelected_data->Draw("e");
  hInvMassSelected_data->SetXTitle("M_{B} (GeV/c^{2})");
  hInvMassSelected_data->SetYTitle("Entries / (30 MeV/c^{2})");
  hInvMassSelected_data->GetXaxis()->CenterTitle();
  hInvMassSelected_data->GetYaxis()->CenterTitle();
  hInvMassSelected_data->SetTitleOffset(1.,"Y");
  hInvMassSelected_data->SetAxisRange(0,hInvMassSelected_data->GetMaximum()*1.2,"Y");
  
  Bkpi->Draw("same");
  background->Draw("same");   
  mass->SetRange(5,6);
  mass->Draw("same");
  mass->SetLineStyle(2);
  mass->SetFillStyle(3004);
  mass->SetFillColor(2);
  f->Draw("same");
  
  double yield = mass->Integral(5,6)/0.03;
  double yieldErr = mass->Integral(5,6)/0.03*mass->GetParError(0)/mass->GetParameter(0);


  TLegend *leg = myLegend(0.50,0.5,0.86,0.92);
  leg->AddEntry(hInvMassSelected_data,"CMS Preliminary","");
  leg->AddEntry(hInvMassSelected_data,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","");
  //leg->AddEntry(hInvMassSelected_data,Form("%.0f<p_{T}^{B}<%.0f GeV/c",ptmin,ptmax),"");
  leg->AddEntry(hInvMassSelected_data,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"Signal","f");
  leg->AddEntry(background,"Combinatorial Background","l");
  leg->AddEntry(Bkpi,"Non-prompt J/#psi","f");
  leg->Draw();
  TLegend *leg2 = myLegend(0.44,0.33,0.89,0.50);
  leg2->AddEntry(hInvMassSelected_data,"B meson","");
  leg2->AddEntry(hInvMassSelected_data,Form("M_{B}=%.2f #pm %.2f MeV/c^{2}",f->GetParameter(1)*1000.,f->GetParError(1)*1000.),"");
  leg2->AddEntry(hInvMassSelected_data,Form("N_{B}=%.0f #pm %.0f",yield,yieldErr),"");
  leg2->Draw();
  
  c->SaveAs("Results/BMass.pdf");


}
