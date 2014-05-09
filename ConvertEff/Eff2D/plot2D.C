#include <TH2.h>
#include <TCanvas.h>
#include "eff_value.h"

Double_t MuPtBins[8] = {0.0,1.5,3.0,4.5,6.0,9.0,20.0,30.0};
Double_t MuEtaBins[4] = {-2.4, -0.8, 0.8, 1.46};

int type = 3;
void plot2D(){
  TH2F* hdata_ = new TH2F("hdata_","",7,MuPtBins, 3, MuEtaBins);
  TH2F* hmc_ = new TH2F("hmc_","",7,MuPtBins, 3, MuEtaBins);
  for(int i=0; i <7; i++){
    if(type==1){
      hdata_->SetBinContent(i+1,1,MuTrgetabin1[i]);
      hmc_->SetBinContent(i+1,1,_MC_MuTrgetabin1[i]);
      hdata_->SetBinContent(i+1,2,MuTrgetabin2[i]);
      hmc_->SetBinContent(i+1,2,_MC_MuTrgetabin2[i]);
      hdata_->SetBinContent(i+1,3,MuTrgetabin3[i]);
      hmc_->SetBinContent(i+1,3,_MC_MuTrgetabin3[i]);
    }
    if(type==2){
      hdata_->SetBinContent(i+1,1,MuIDetabin1[i]);
      hmc_->SetBinContent(i+1,1,_MC_MuIDetabin1[i]);
      hdata_->SetBinContent(i+1,2,MuIDetabin2[i]);
      hmc_->SetBinContent(i+1,2,_MC_MuIDetabin2[i]);
      hdata_->SetBinContent(i+1,3,MuIDetabin3[i]);
      hmc_->SetBinContent(i+1,3,_MC_MuIDetabin3[i]);
    }
    if(type==3){
      hdata_->SetBinContent(i+1,1,MuTrketabin1[i]);
      hmc_->SetBinContent(i+1,1,_MC_MuTrketabin1[i]);
      hdata_->SetBinContent(i+1,2,MuTrketabin2[i]);
      hmc_->SetBinContent(i+1,2,_MC_MuTrketabin2[i]);
      hdata_->SetBinContent(i+1,3,MuTrketabin3[i]);
      hmc_->SetBinContent(i+1,3,_MC_MuTrketabin3[i]);
    }
  }
  TCanvas *c1=  new TCanvas("c1","",600,600);
  TCanvas *c2=  new TCanvas("c2","",600,600);
  TCanvas *c3=  new TCanvas("c3","",600,600);
  c1->cd();
  c1->SetRightMargin(0.15);
  c2->SetRightMargin(0.15);
  c3->SetRightMargin(0.15);

  hdata_->GetYaxis()->CenterTitle();
  if(type==1) hdata_->SetTitle("data Mu trigger efficiency");
  if(type==2) hdata_->SetTitle("data Mu ID efficiency");
  if(type==3) hdata_->SetTitle("data Mu tracking efficiency");
  hdata_->SetXTitle("pt[GeV]");
  hdata_->SetYTitle("eta_{Lab}");
  hdata_->Draw("COL Z");

  c2->cd();
  hmc_->GetYaxis()->CenterTitle();
  if(type==1)hmc_->SetTitle("MC Mu trigger efficiency");
  if(type==2)hmc_->SetTitle("MC Mu ID efficiency");
  if(type==3)hmc_->SetTitle("MC Mu tracking efficiency");
  hmc_->SetXTitle("pt[GeV]");
  hmc_->SetYTitle("eta_{Lab}");
  hmc_->Draw("COL Z");

  c3->cd();
  TH2F* hdiff_ = (TH2F*)hdata_->Clone();
  hdiff_->Add(hmc_,-1);
  hdiff_->GetYaxis()->CenterTitle();
  if(type==1)hdiff_->SetTitle("Mu trigger efficiency diff. (data-MC)");
  if(type==2)hdiff_->SetTitle("Mu ID efficiency diff. (data-MC)");
  if(type==3)hdiff_->SetTitle("Mu tracking efficiency diff. (data-MC)");
  hdiff_->SetXTitle("pt[GeV]");
  hdiff_->SetYTitle("eta_{Lab}");
  hdiff_->Draw("COL Z");

  if(type==1){
    c1->SaveAs("Trgdata.pdf");
    c2->SaveAs("Trgmc.pdf");
    c3->SaveAs("Trgdiff.pdf");
  }
  if(type==2){
    c1->SaveAs("IDdata.pdf");
    c2->SaveAs("IDmc.pdf");
    c3->SaveAs("IDdiff.pdf");
  }
  if(type==3){
    c1->SaveAs("Trkdata.pdf");
    c2->SaveAs("Trkmc.pdf");
    c3->SaveAs("Trkdiff.pdf");
  }
}
