#include <iostream>
#include <math.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TCut.h>
#include <TFile.h>
#include <TNtuple.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include <TEfficiency.h>
#include <TGraphAsymmErrors.h>

#define MAX_GEN 4096 //default 2048
#define MUON_MASS   0.10565837
#define PION_MASS   0.13957018
#define KAON_MASS   0.493677
#define KSHORT_MASS 0.497614
#define KSTAR_MASS  0.89594
#define PHI_MASS    1.019455
#define JPSI_MASS   3.096916
#define PSI2S_MASS  3.686109

using namespace std;

TString inputmc;
TString cut;
TString selmc;
TString foutname;
TString ntname;
int MCflag = 3;

void eff(){
  if(MCflag==1){
    inputmc="/export/d00/scratch/jwang/nt_BoostedMC_20140418_Kp_TriggerMatchingMuon_EvtBase_skim.root";
    cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e01";
    selmc=Form("abs(y+0.465)<1.93&&gen==22233&&pt>10&&pt<60&&%s",cut.Data());
    foutname = "fout_kp.root";
    ntname="ntKp";
  }
  if(MCflag==2){
    inputmc="/export/d00/scratch/jwang/nt_BoostedMC_20140418_Kstar_TriggerMatchingMuon_EvtBase_skim.root";
    cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>1.65e-01&&(d0/d0Err)>4.16&&cos(dtheta)>7.50e-01&&abs(tktkmass-0.89594)<2.33e-01";
//    selmc=Form("abs(y+0.465)<1.93&&(gen==22233||gen==41000)&&pt>10&&pt<60&&%s",cut_kpi.Data());
    selmc=Form("abs(y+0.465)<1.93&&gen==22233&&pt>10&&pt<60&&%s",cut.Data());
    foutname = "fout_kstar.root";
    ntname="ntKstar";
  }
  if(MCflag==3){
    inputmc="/export/d00/scratch/jwang/nt_BoostedMC_20140424_Phi_TriggerMatchingMuon_EvtBase_skim.root";
    cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&& chi2cl>3.71e-02&&(d0/d0Err)>3.37&&cos(dtheta)>2.60e-01&&abs(tktkmass-1.019455)<1.55e-02";
    selmc=Form("abs(y+0.465)<1.93&&gen==22233&&pt>10&&pt<60&&%s",cut.Data());
    foutname = "fout_phi.root";
    ntname="ntphi";
  }
  TFile *infMC = new TFile(inputmc.Data());
  TTree *ntGen = (TTree*)infMC->Get("ntGen");
  TTree *ntMC = (TTree*)infMC->Get(ntname.Data());
  TFile *fout = new TFile(foutname.Data(),"recreate");

  const int nBins = 6;
  double ptBins[nBins+1] = {5,10,15,20,25,30,60};
  const int nEtaBins = 4;
  double yBins[nEtaBins+1] = {-2.395, -1.47, -0.47, 0.53, 1.465};
  TH1F* reco_bsig_pt = new TH1F("reco_bsig_pt", "", nBins,ptBins);
  TH1F* reco_bsig_y = new TH1F("reco_bsig_y", "", nEtaBins,yBins);
  TH1F* gen_bsig_pt = new TH1F("gen_bsig_pt", "", nBins,ptBins);
  TH1F* gen_bsig_y = new TH1F("gen_bsig_y", "", nEtaBins,yBins);

//  TH2F* sct_pt_y = new TH2F("sct_pt_y","",nEtaBins, yBins, nBins, ptBins);
  TH2F* sct_pt_y = new TH2F("sct_pt_y","",50,-2.395, 1.465, 50, 10, 60);

  reco_bsig_pt->SetMinimum(0);
  reco_bsig_y->SetMinimum(0);
  gen_bsig_pt->SetMinimum(0);
  gen_bsig_y->SetMinimum(0);

  int nevents_total = ntGen->GetEntries();
//  nevents_total = 10000;
  ntMC->Project("reco_bsig_pt","pt",selmc.Data(),"",nevents_total);
  ntMC->Project("reco_bsig_y","y",selmc.Data(),"",nevents_total);
  ntMC->Project("sct_pt_y","pt:y",selmc.Data(),"",nevents_total);

  TCanvas*c3 = new TCanvas("c3", "", 200, 10, 1000, 800);
  c3->cd();
  sct_pt_y->GetXaxis()->SetTitle("pt[GeV]");                      
  sct_pt_y->GetYaxis()->SetTitle("y_{Lab}"); 
  sct_pt_y->GetYaxis()->CenterTitle(); 
  sct_pt_y->Draw("COL Z");
  if(MCflag == 1){
      sct_pt_y->SetTitle("Reco Can. K+ channel");                                                                                                                                                    
      c3->SaveAs("fig_eff/kp_sct.pdf");
  }
  if(MCflag == 2){
      sct_pt_y->SetTitle("Reco Can. K* channel");
      c3->SaveAs("fig_eff/kstar_sct.pdf");
  }
  if(MCflag == 3){
      sct_pt_y->SetTitle("Reco Can.  #phi channel");
      c3->SaveAs("fig_eff/phi_sct.pdf");
  }
  
  Int_t size;
  Float_t y[MAX_GEN];
  Float_t eta[MAX_GEN];
  Float_t phi[MAX_GEN];
  Float_t pt[MAX_GEN];
  Float_t pdgId[MAX_GEN];
  Float_t isSignal[MAX_GEN];
  Float_t mu1pt[MAX_GEN];
  Float_t mu2pt[MAX_GEN];
  Float_t mu1eta[MAX_GEN];
  Float_t mu2eta[MAX_GEN];
  Float_t mu1phi[MAX_GEN];
  Float_t mu2phi[MAX_GEN];
  Float_t tk1pt[MAX_GEN];
  Float_t tk2pt[MAX_GEN];
  Float_t tk1eta[MAX_GEN];
  Float_t tk2eta[MAX_GEN];
  Float_t tk1phi[MAX_GEN];
  Float_t tk2phi[MAX_GEN];
  ntGen->SetBranchAddress("size",&size);
  ntGen->SetBranchAddress("y",&y);
  ntGen->SetBranchAddress("eta",eta);
  ntGen->SetBranchAddress("phi",phi);
  ntGen->SetBranchAddress("pt",pt);
  ntGen->SetBranchAddress("pdgId",pdgId);
  ntGen->SetBranchAddress("isSignal",isSignal);
  ntGen->SetBranchAddress("mu1pt",mu1pt);
  ntGen->SetBranchAddress("mu2pt",mu2pt);
  ntGen->SetBranchAddress("mu1eta",mu1eta);
  ntGen->SetBranchAddress("mu2eta",mu2eta);
  ntGen->SetBranchAddress("mu1phi",mu1phi);
  ntGen->SetBranchAddress("mu2phi",mu2phi);
  ntGen->SetBranchAddress("tk1pt",tk1pt);
  ntGen->SetBranchAddress("tk2pt",tk2pt);
  ntGen->SetBranchAddress("tk1eta",tk1eta);
  ntGen->SetBranchAddress("tk2eta",tk2eta);
  ntGen->SetBranchAddress("tk1phi",tk1phi);
  ntGen->SetBranchAddress("tk2phi",tk2phi);
  TLorentzVector mu1;
  TLorentzVector mu2;
  TLorentzVector tk1;
  TLorentzVector tk2;
  TLorentzVector B;
  for(int entry=0; entry<nevents_total; entry++){
    if ((entry%10000) == 0) printf("Loading event #%d of %d.\n",entry,nevents_total);
    ntGen->GetEntry(entry);
    for(int c=0; c<size; c++){
      if(isSignal[c]){
        if(fabs(mu1eta[c]) < 1.3) {if(mu1pt[c] < 3.3) continue;}
        else if(fabs(mu1eta[c]) > 1.3 && fabs(mu1eta[c]) < 2.2) {if(mu1pt[c] < 2.9) continue;}
        else if(fabs(mu1eta[c]) > 2.2 && fabs(mu1eta[c]) < 2.4) {if(mu1pt[c] < 0.8) continue;}
        else {continue;}
        if(fabs(mu2eta[c]) < 1.3) {if(mu2pt[c] < 3.3) continue;}
        else if(fabs(mu2eta[c]) > 1.3 && fabs(mu2eta[c]) < 2.2) {if(mu2pt[c] < 2.9) continue;}
        else if(fabs(mu2eta[c]) > 2.2 && fabs(mu2eta[c]) < 2.4) {if(mu2pt[c] < 0.8) continue;}
        else {continue;}
        
        mu1.SetPtEtaPhiM(mu1pt[c], mu1eta[c], mu1phi[c], MUON_MASS);
        mu2.SetPtEtaPhiM(mu2pt[c], mu2eta[c], mu2phi[c], MUON_MASS);
        if(MCflag==1){
          tk1.SetPtEtaPhiM(tk1pt[c], tk1eta[c], tk1phi[c], KAON_MASS);
          B = mu1+mu2+tk1;
        }
        if(MCflag==2){
          tk1.SetPtEtaPhiM(tk1pt[c], tk1eta[c], tk1phi[c], KAON_MASS);
          tk2.SetPtEtaPhiM(tk2pt[c], tk2eta[c], tk2phi[c], PION_MASS);
          B = mu1+mu2+tk1+tk2;
        }
        if(MCflag==3){
          tk1.SetPtEtaPhiM(tk1pt[c], tk1eta[c], tk1phi[c], KAON_MASS);
          tk2.SetPtEtaPhiM(tk2pt[c], tk2eta[c], tk2phi[c], KAON_MASS);
          B = mu1+mu2+tk1+tk2;
        }
		//cout<<B.Mag()<<endl;
        if(B.Mag() < 4.95 || B.Mag() > 5.55) continue;
        
        if(pt[c]>10 && pt[c]<60 && abs(y[c]+0.465)<1.93){
          gen_bsig_pt->Fill(pt[c]);
          gen_bsig_y->Fill(y[c]);
        }
      }
    }
  }
/*
  ////PLOTTING////
  TEfficiency *reco_gen_eff_pt = new TEfficiency(*reco_bsig_pt, *gen_bsig_pt);
  TEfficiency *reco_gen_eff_y = new TEfficiency(*reco_bsig_y, *gen_bsig_y);
  TCanvas*c1 = new TCanvas("c1", "", 200, 10, 1000, 800);
  TCanvas*c2 = new TCanvas("c2", "", 200, 10, 1000, 800);
  if(MCflag == 1){
      reco_gen_eff_pt->SetTitle("eff base, K+ channel");
      reco_gen_eff_y->SetTitle("eff base, K+ channel");
  }
  if(MCflag == 2){
      reco_gen_eff_pt->SetTitle("eff base, K* channel");
      reco_gen_eff_y->SetTitle("eff base, K* channel");
  }
  if(MCflag == 3){
      reco_gen_eff_pt->SetTitle("eff base, #phi channel");
      reco_gen_eff_y->SetTitle("eff base, #phi channel");
  }
  for(int i = 0; i < reco_bsig_pt->GetNbinsX(); i ++){
      printf("bin content pt: %.0f, %.0f\n", reco_bsig_pt->GetBinContent(i+1), gen_bsig_pt->GetBinContent(i+1));
  }

  c1->cd();
  reco_gen_eff_pt->SetFillColor(2);
  reco_gen_eff_pt->SetFillStyle(3001);
  reco_gen_eff_pt->Draw("");
  c1->Update();
  reco_gen_eff_pt->GetPaintedGraph()->GetXaxis()->SetTitle("pt[GeV]");
  reco_gen_eff_pt->GetPaintedGraph()->SetMaximum(1);
  reco_gen_eff_pt->GetPaintedGraph()->SetMinimum(0);
  reco_gen_eff_pt->Draw("a2");
  reco_gen_eff_pt->Draw("same");
  reco_gen_eff_pt->Write();
  c1->Write();

  for(int i = 0; i < reco_bsig_y->GetNbinsX(); i ++){
      printf("bincontent y: %.0f, %.0f\n", reco_bsig_y->GetBinContent(i+1), gen_bsig_y->GetBinContent(i+1));
  }

  c2->cd();
  reco_gen_eff_y->SetFillColor(2);
  reco_gen_eff_y->SetFillStyle(3001);
  reco_gen_eff_y->Draw("");
  c2->Update();
  reco_gen_eff_y->GetPaintedGraph()->GetXaxis()->SetTitle("y_{Lab}");
  reco_gen_eff_y->GetPaintedGraph()->SetMaximum(1);
  reco_gen_eff_y->GetPaintedGraph()->SetMinimum(0);
  reco_gen_eff_y->Draw("a2");
  reco_gen_eff_y->Draw("same");
  reco_gen_eff_y->Write();
  c2->Update();
  c2->Write();

  fout->Write();
  fout->Close();
  if(MCflag == 1){
      c1->SaveAs("fig_eff/kp_pt_eff.pdf");
      c2->SaveAs("fig_eff/kp_y_eff.pdf");
  }
  if(MCflag == 2){
      c1->SaveAs("fig_eff/kstar_pt_eff.pdf");
      c2->SaveAs("fig_eff/kstar_y_eff.pdf");
  }
  if(MCflag == 3){
      c1->SaveAs("fig_eff/phi_pt_eff.pdf");
      c2->SaveAs("fig_eff/phi_y_eff.pdf");
  }
*/
  ////PLOTING////
}
