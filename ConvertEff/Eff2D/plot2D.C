#include <TH2.h>
#include <TCanvas.h>

Double_t MuTrgetabin1[7] = {0.0001, 0.0070, 0.574, 0.855, 0.895, 0.887, 0.86};
Double_t MuTrgetabin1Err[7] = {0.0002, 0.0006, 0.003, 0.003, 0.003, 0.005, 0.03};
Double_t MuTrgetabin2[7] = {0.00000, 0.00000, 0.370, 0.810, 0.968, 0.969, 0.99};
Double_t MuTrgetabin2Err[7] = {0.00000, 0.00000, 0.003, 0.003, 0.002, 0.003, 0.01};
Double_t MuTrgetabin3[7] = {0.00000,0.0071,0.655,0.893,0.930,0.926,0.97};
Double_t MuTrgetabin3Err[7] = {0.00009,0.0006,0.003,0.003,0.003,0.005,0.02};

Double_t MuIDetabin1[7] = {0.668,0.883,0.949,0.981,0.986,0.987,0.983};
Double_t MuIDetabin1Err[7] = {0.009,0.003,0.002,0.001,0.001,0.002,0.007};
Double_t MuIDetabin2[7] = {0.00000,0.00000,0.853,0.976,0.985,0.984,0.999999999};
Double_t MuIDetabin2Err[7] = {0.00000,0.00000,0.003,0.001,0.001,0.002,0.0000000003};
Double_t MuIDetabin3[7] = {0.499,0.805,0.942,0.978,0.986,0.993,0.97};
Double_t MuIDetabin3Err[7] = {0.006,0.003,0.002,0.002,0.002,0.002,0.02};

Double_t MuTrketabin1[7] = {0.95,0.939,0.953,0.958,0.962,0.952,0.92};
Double_t MuTrketabin1Err[7] = {0.10,0.004,0.003,0.003,0.004,0.007,0.08};
Double_t MuTrketabin2[7] = {0.0,0.0,0.929,0.965,0.966,0.971,0.95};
Double_t MuTrketabin2Err[7] = {0.5,0.7,0.007,0.003,0.003,0.004,0.02};
Double_t MuTrketabin3[7] = {1.0,0.959,0.958,0.956,0.962,0.971,1.0};
Double_t MuTrketabin3Err[7] = {0.6,0.007,0.003,0.004,0.004,0.008,0.2};

Double_t _MC_MuTrgetabin1[7] = {0.00000, 0.0045, 0.446, 0.754, 0.820, 0.834, 0.79};
Double_t _MC_MuTrgetabin1Err[7] = {0.000006, 0.0002, 0.002, 0.002, 0.002, 0.003, 0.02};
Double_t _MC_MuTrgetabin2[7] = {0.00000, 0.00000, 0.284, 0.725, 0.947, 0.957, 0.911};
Double_t _MC_MuTrgetabin2Err[7] = {0.00000, 0.00000, 0.002, 0.002, 0.001, 0.002, 0.009};
Double_t _MC_MuTrgetabin3[7] = {0.00000,0.0034,0.465,0.807,0.882,0.890,0.86};
Double_t _MC_MuTrgetabin3Err[7] = {0.00007,0.0003,0.003,0.003,0.003,0.004,0.02};

Double_t _MC_MuIDetabin1[7] = {0.533,0.876,0.976,0.984,0.984,0.988,0.991};
Double_t _MC_MuIDetabin1Err[7] = {0.005,0.002,0.001,0.001,0.001,0.002,0.006};
Double_t _MC_MuIDetabin2[7] = {0.22,0.676,0.833,0.9636,0.9762,0.9788,0.981};
Double_t _MC_MuIDetabin2Err[7] = {0.01,0.003,0.001,0.0008,0.0007,0.0009,0.003};
Double_t _MC_MuIDetabin3[7] = {0.383,0.807,0.970,0.979,0.979,0.987,0.98};
Double_t _MC_MuIDetabin3Err[7] = {0.004,0.002,0.002,0.002,0.002,0.003,0.01};

Double_t _MC_MuTrketabin1[7] = {0.78,0.903,0.927,0.938,0.954,0.958,0.95};
Double_t _MC_MuTrketabin1Err[7] = {0.03,0.003,0.002,0.003,0.003,0.004,0.02};
Double_t _MC_MuTrketabin2[7] = {0.0,0.3,0.936,0.954,0.959,0.966,0.981};
Double_t _MC_MuTrketabin2Err[7] = {0.2,0.3,0.004,0.002,0.002,0.002,0.007};
Double_t _MC_MuTrketabin3[7] = {1.0,0.938,0.932,0.940,0.948,0.961,0.93};
Double_t _MC_MuTrketabin3Err[7] = {0.1,0.005,0.003,0.003,0.003,0.004,0.05};

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
