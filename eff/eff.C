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
#define BP_MASS     5.27926
#define BZERO_MASS  5.27958
#define BS_MASS     5.36677

float lumi1 = 20.8;
float lumi2 = 14.0;
using namespace std;
TString inputmc;
TString inputmc2;
TString cut;
TString selmc;
TString selmc2;
TString foutname;
TString ntname;
//int MCflag = 1;
TString fig_folder = "fig_eff_fine";
//TString fig_folder = "dummy";
void AcceptedCand(TTree *ntGen, TH1F* gen_bsig_pt, TH1F* gen_bsig_y, bool IsPpb, int nevents_total, int MCflag);
void DrawMyEff(TCanvas* c, TEfficiency* eff, TString axis);
void cal(int MCflag);
void eff(){
  cal(1);
  cal(2);
  cal(3);
}

void cal(int MCflag){
  if(MCflag==1){
//    inputmc="/export/d00/scratch/jwang/nt_BoostedMC_20140427_Kp_TriggerMatchingMuon_EvtBase_skim.root";
//    inputmc2="/net/hidsk0001/d00/scratch/jwang/nt_BoostedMC_20140501_Hijing_PPb502_MinimumBias_HIJINGemb_BuJpsiKp_5TeV_boostPbp.root";
//    cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e01";
//    selmc=Form("abs(y+0.465)<1.93&&gen==23333&&pt>10&&pt<60&&%s",cut.Data());
//    selmc2=Form("abs(y-0.465)<1.93&&gen==23333&&pt>10&&pt<60&&%s",cut.Data());
    inputmc="/mnt/hadoop/cms/store/user/tawei/Bntuple/nt_20140801_mixed_fromQMBFinder_Kp.root";
    inputmc2="/mnt/hadoop/cms/store/user/tawei/Bntuple/nt_20140801_mixed_fromQMBFinder_Kp.root";
	cut="abs(y)<2.4&&(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e01&&mu1pt>1.5&&mu2pt>1.5";
	selmc=Form("Run<=1&&abs(y)<2.4&&gen==23333&&pt>10&&pt<60&&%s",cut.Data());
	selmc2=Form("Run>1&&abs(y)<2.4&&gen==23333&&pt>10&&pt<60&&%s",cut.Data());
    foutname = "fout_kp.root";
    ntname="ntKp";
  }
  if(MCflag==2){
//    inputmc="/export/d00/scratch/jwang/nt_BoostedMC_20140427_Kstar_TriggerMatchingMuon_EvtBase_skim.root";
//    inputmc2="/net/hidsk0001/d00/scratch/jwang/nt_BoostedMC_20140501_Hijing_PPb502_MinimumBias_HIJINGemb_BdJpsiKstar_5TeV_boostPbp.root";
//    cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>1.65e-01&&(d0/d0Err)>4.16&&cos(dtheta)>7.50e-01&&abs(tktkmass-0.89594)<2.33e-01";
//    selmc=Form("abs(y+0.465)<1.93&&(gen==23333||gen==41000)&&pt>10&&pt<60&&%s",cut_kpi.Data());
//    selmc=Form("abs(y+0.465)<1.93&&gen==23333&&pt>10&&pt<60&&%s",cut.Data());
//    selmc2=Form("abs(y-0.465)<1.93&&gen==23333&&pt>10&&pt<60&&%s",cut.Data());
    inputmc="/mnt/hadoop/cms/store/user/tawei/Bntuple/nt_20140801_mixed_fromQMBFinder_Kstar.root";
    inputmc2="/mnt/hadoop/cms/store/user/tawei/Bntuple/nt_20140801_mixed_fromQMBFinder_Kstar.root";
	cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>9.94e-02&&(d0/d0Err)>6.08&&cos(dtheta)>7.93e-01&&abs(tktkmass-0.89594)<0.10&&tktkmassKK>1.04&&mu1pt>1.5&&mu2pt>1.5";
	selmc=Form("Run<=1&&abs(y)<2.4&&(gen==23333||gen==41000)&&pt>10&&pt<60&&%s",cut.Data());
	selmc2=Form("Run>1&&abs(y)<2.4&&(gen==23333||gen==41000)&&pt>10&&pt<60&&%s",cut.Data());
    foutname = "fout_kstar.root";
    ntname="ntKstar";
  }
  if(MCflag==3){
//    inputmc="/export/d00/scratch/jwang/nt_BoostedMC_20140427_Phi_TriggerMatchingMuon_EvtBase_skim.root";
//    inputmc2="/net/hidsk0001/d00/scratch/jwang/nt_BoostedMC_20140501_Hijing_PPb502_MinimumBias_HIJINGemb_BsJpsiPhi_5TeV_boostPbp.root";
//    cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&& chi2cl>3.71e-02&&(d0/d0Err)>3.37&&cos(dtheta)>2.60e-01&&abs(tktkmass-1.019455)<1.55e-02";
//    selmc=Form("abs(y+0.465)<1.93&&gen==23333&&pt>10&&pt<60&&%s",cut.Data());
//    selmc2=Form("abs(y-0.465)<1.93&&gen==23333&&pt>10&&pt<60&&%s",cut.Data());
    inputmc="/mnt/hadoop/cms/store/user/tawei/Bntuple/nt_20140801_mixed_fromQMBFinder_Phi.root";
    inputmc2="/mnt/hadoop/cms/store/user/tawei/Bntuple/nt_20140801_mixed_fromQMBFinder_Phi.root";
	cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&& chi2cl>3.71e-02&&(d0/d0Err)>3.37&&cos(dtheta)>2.60e-01&&abs(tktkmass-1.019455)<1.55e-02&&mu1pt>1.5&&mu2pt>1.5";
	selmc=Form("Run<=1&&abs(y)<2.4&&gen==23333&&pt>10&&pt<60&&%s",cut.Data());
	selmc2=Form("Run>1&&abs(y)<2.4&&gen==23333&&pt>10&&pt<60&&%s",cut.Data());
    foutname = "fout_phi.root";
    ntname="ntphi";
  }
  TFile *infMC = new TFile(inputmc.Data());
  TFile *infMC2 = new TFile(inputmc2.Data());
  TTree *ntGen = (TTree*)infMC->Get("ntGen");
  TTree *ntGen2 = (TTree*)infMC2->Get("ntGen");
  TTree *ntMC = (TTree*)infMC->Get(ntname.Data());
  TTree *ntMC2 = (TTree*)infMC2->Get(ntname.Data());
  TFile *fout = new TFile(foutname.Data(),"recreate");
  ntGen->AddFriend(ntMC);
  ntGen2->AddFriend(ntMC2);

  const int Bp_nBins = 5;
  double Bp_ptBins[Bp_nBins+1] = {10,15,20,25,30,60};
  const int B0_nBins = 3;
  double B0_ptBins[B0_nBins+1] = {10,15,20,60};
  const int Bs_nBins = 1;
  double Bs_ptBins[Bs_nBins+1] = {10,60};
  //const int nEtaBins = 4;
  //double yBins[nEtaBins+1] = {-2.395, -1.47, -0.47, 0.53, 1.465};
  //double yBins[nEtaBins+1] = {-1.93, -1., 0, 1., 1.93};
  const int nEtaBins = 5;
  double yBins[nEtaBins+1] = {-1.935,-1.0,0,1.0,1.935,2.865};
  double yBins2[nEtaBins+1] = {-2.865,-1.935,-1.0,0,1.0,1.935};
  double *ptBins; int nBins;
  if(MCflag==1){ ptBins=Bp_ptBins; nBins=Bp_nBins;}
  if(MCflag==2){ ptBins=B0_ptBins; nBins=B0_nBins;}
  if(MCflag==3){ ptBins=Bs_ptBins; nBins=Bs_nBins;}

  TH1F* reco_bsig_pt = new TH1F("reco_bsig_pt", "", nBins,ptBins);
  TH1F* reco_bsig_y = new TH1F("reco_bsig_y", "", nEtaBins,yBins);
  TH1F* gen_bsig_pt = new TH1F("gen_bsig_pt", "", nBins,ptBins);
  TH1F* gen_bsig_y = new TH1F("gen_bsig_y", "", nEtaBins,yBins);
  TH1F* reco_bsig_pt2 = new TH1F("reco_bsig_pt2", "", nBins,ptBins);
  TH1F* reco_bsig_y2 = new TH1F("reco_bsig_y2", "", nEtaBins,yBins2);
  TH1F* gen_bsig_pt2 = new TH1F("gen_bsig_pt2", "", nBins,ptBins);
  TH1F* gen_bsig_y2 = new TH1F("gen_bsig_y2", "", nEtaBins,yBins2);
  TH2F* sct_pt_y = new TH2F("sct_pt_y","",nEtaBins, yBins, nBins, ptBins);
  TH2F* sct_pt_y2 = new TH2F("sct_pt_y2","",nEtaBins, yBins2, nBins, ptBins);

/*
  TH1F* reco_bsig_pt = new TH1F("reco_bsig_pt", "", 50, ptBins[0], ptBins[nBins]);
  TH1F* reco_bsig_y = new TH1F("reco_bsig_y", "", 50, yBins[0], yBins[nEtaBins]);
  TH1F* gen_bsig_pt = new TH1F("gen_bsig_pt", "", 50, ptBins[0], ptBins[nBins]);
  TH1F* gen_bsig_y = new TH1F("gen_bsig_y", "", 50, yBins[0], yBins[nEtaBins]);
  TH1F* reco_bsig_pt2 = new TH1F("reco_bsig_pt2", "", 10, ptBins[0], ptBins[nBins]);
  TH1F* reco_bsig_y2 = new TH1F("reco_bsig_y2", "", 20, yBins2[0], yBins2[nEtaBins]);
  TH1F* gen_bsig_pt2 = new TH1F("gen_bsig_pt2", "", 10, ptBins[0], ptBins[nBins]);
  TH1F* gen_bsig_y2 = new TH1F("gen_bsig_y2", "", 20, yBins2[0], yBins2[nEtaBins]);
  TH2F* sct_pt_y = new TH2F("sct_pt_y", "", 20, -1.935, 2.865, 20, 10, 60);
  TH2F* sct_pt_y2 = new TH2F("sct_pt_y2", "", 20, -2.865, 1.935, 20, 10, 60);
*/
  reco_bsig_pt->SetMinimum(0);
  reco_bsig_y->SetMinimum(0);
  gen_bsig_pt->SetMinimum(0);
  gen_bsig_y->SetMinimum(0);
  reco_bsig_pt2->SetMinimum(0);
  reco_bsig_y2->SetMinimum(0);
  gen_bsig_pt2->SetMinimum(0);
  gen_bsig_y2->SetMinimum(0);
  sct_pt_y->SetMinimum(0);
  sct_pt_y2->SetMinimum(0);

  int nevents_total = ntMC->GetEntries();
//  nevents_total = 10000;
  ntMC->Project("reco_bsig_pt","pt",selmc.Data(),"",nevents_total);
  ntMC->Project("reco_bsig_y","(y+0.465)",selmc.Data(),"",nevents_total);
  ntMC->Project("sct_pt_y","pt:(y+0.465)",selmc.Data(),"",nevents_total);
  ntMC2->Project("reco_bsig_pt2","pt",selmc2.Data(),"",nevents_total);
  ntMC2->Project("reco_bsig_y2","(y-0.465)",selmc2.Data(),"",nevents_total);
  ntMC2->Project("sct_pt_y2","pt:(y-0.465)",selmc2.Data(),"",nevents_total);
  TCanvas*c3 = new TCanvas("c3", "", 200, 10, 1000, 800);
  c3->cd();
  sct_pt_y->GetYaxis()->SetTitle("pt[GeV]");                      
  sct_pt_y->GetXaxis()->SetTitle("y_{CM}"); 
  sct_pt_y->GetYaxis()->CenterTitle(); 
  sct_pt_y->Draw("COL Z");
  TCanvas*c4 = new TCanvas("c4", "", 200, 10, 1000, 800);
  c4->cd();
  sct_pt_y2->GetYaxis()->SetTitle("pt[GeV]");                      
  sct_pt_y2->GetXaxis()->SetTitle("y_{CM}"); 
  sct_pt_y2->GetYaxis()->CenterTitle(); 
  sct_pt_y2->Draw("COL Z");
  if(MCflag == 1){
      sct_pt_y->SetTitle("Reco Can. K+ channel");                                                                                                                                                    
      c3->SaveAs(fig_folder+"_pPb/kp_sct.pdf");
      sct_pt_y2->SetTitle("Reco Can. K+ channel");                                                                                                                                                    
      c4->SaveAs(fig_folder+"_Pbp/kp_sct.pdf");
  }
  if(MCflag == 2){
      sct_pt_y->SetTitle("Reco Can. K* channel");
      c3->SaveAs(fig_folder+"_pPb/kstar_sct.pdf");
      sct_pt_y2->SetTitle("Reco Can. K* channel");
      c4->SaveAs(fig_folder+"_Pbp/kstar_sct.pdf");
  }
  if(MCflag == 3){
      sct_pt_y->SetTitle("Reco Can.  #phi channel");
      c3->SaveAs(fig_folder+"_pPb/phi_sct.pdf");
      sct_pt_y2->SetTitle("Reco Can.  #phi channel");
      c4->SaveAs(fig_folder+"_Pbp/phi_sct.pdf");
  }
  //return;

  AcceptedCand(ntGen, gen_bsig_pt,  gen_bsig_y, true, nevents_total, MCflag);
  AcceptedCand(ntGen2,gen_bsig_pt2, gen_bsig_y2, false, nevents_total, MCflag);

//for(int ii=1; ii<reco_bsig_pt2->GetNbinsX(); ii++){
//	printf("reco bin: %i = %f\n",ii, reco_bsig_pt2->GetBinContent(ii));
//	printf("gen  bin: %i = %f\n",ii, gen_bsig_pt2->GetBinContent(ii));
//}
//gen_bsig_pt->Draw();
//reco_bsig_pt->Draw("same p");
//return;

  ////PLOTTING////
  TEfficiency *reco_gen_eff_pt = new TEfficiency(*reco_bsig_pt, *gen_bsig_pt);
  TEfficiency *reco_gen_eff_y = new TEfficiency(*reco_bsig_y, *gen_bsig_y);
  TEfficiency *reco_gen_eff_pt2 = new TEfficiency(*reco_bsig_pt2, *gen_bsig_pt2);
  TEfficiency *reco_gen_eff_y2 = new TEfficiency(*reco_bsig_y2, *gen_bsig_y2);
  //reco_gen_eff_pt->SetConfidenceLevel(0.95);
  //reco_gen_eff_y->SetConfidenceLevel(0.95);

/*
reco_gen_eff_y2->SetWeight(200);
reco_gen_eff_pt_merge = (TEfficiency*)reco_gen_eff_pt->Clone();
reco_gen_eff_pt_merge->Add(*reco_gen_eff_pt2);
//reco_gen_eff_y_merge = (TEfficiency*)reco_gen_eff_y->Clone();
//reco_gen_eff_y_merge->Add(*reco_gen_eff_y2);
reco_gen_eff_y_merge = (TEfficiency*)reco_gen_eff_y2->Clone();
reco_gen_eff_y_merge->SetWeight(200.);
cout<<reco_gen_eff_y_merge->GetWeight()<<endl;
reco_gen_eff_y->SetWeight(0.00000001);
//reco_gen_eff_y_merge->Add(*reco_gen_eff_y);
*reco_gen_eff_y_merge += (*reco_gen_eff_y);
cout<<reco_gen_eff_y_merge->GetWeight()<<endl;
*/

  TCanvas*c1 = new TCanvas("c1", "", 200, 10, 1000, 800);
  TCanvas*c2 = new TCanvas("c2", "", 200, 10, 1000, 800);
  TCanvas*c5 = new TCanvas("c5", "", 200, 10, 1000, 800);
  TCanvas*c6 = new TCanvas("c6", "", 200, 10, 1000, 800);
  if(MCflag == 1){
      reco_gen_eff_pt->SetTitle("eff base, K+ channel");
      reco_gen_eff_y->SetTitle("eff base, K+ channel");
      reco_gen_eff_pt2->SetTitle("eff base, K+ channel");
      reco_gen_eff_y2->SetTitle("eff base, K+ channel");
  }
  if(MCflag == 2){
      reco_gen_eff_pt->SetTitle("eff base, K* channel");
      reco_gen_eff_y->SetTitle("eff base, K* channel");
      reco_gen_eff_pt2->SetTitle("eff base, K* channel");
      reco_gen_eff_y2->SetTitle("eff base, K* channel");
  }
  if(MCflag == 3){
      reco_gen_eff_pt->SetTitle("eff base, #phi channel");
      reco_gen_eff_y->SetTitle("eff base, #phi channel");
      reco_gen_eff_pt2->SetTitle("eff base, #phi channel");
      reco_gen_eff_y2->SetTitle("eff base, #phi channel");
  }

  cout<<"pt 1-------------"<<endl;
  for(int i = 0; i < reco_bsig_pt->GetNbinsX(); i ++){
      //printf("bin content pt: %.0f, %.0f\n", reco_bsig_pt->GetBinContent(i+1), gen_bsig_pt->GetBinContent(i+1));
      printf("%.3f$\\pm$%.3f & ", reco_gen_eff_pt->GetEfficiency(i+1), max(reco_gen_eff_pt->GetEfficiencyErrorUp(i+1), reco_gen_eff_pt->GetEfficiencyErrorLow(i+1)));
  }
  cout<<endl;
  cout<<"y 1-------------"<<endl;
  for(int i = 0; i < reco_bsig_y->GetNbinsX(); i ++){
      //printf("bincontent y: %.0f, %.0f\n", reco_bsig_y->GetBinContent(i+1), gen_bsig_y->GetBinContent(i+1));
      printf("%.3f$\\pm$%.3f & ", reco_gen_eff_y->GetEfficiency(i+1), max(reco_gen_eff_y->GetEfficiencyErrorUp(i+1), reco_gen_eff_y->GetEfficiencyErrorLow(i+1)));
  }
  cout<<endl;
  cout<<"pt 2-------------"<<endl;
  for(int i = 0; i < reco_bsig_pt2->GetNbinsX(); i ++){
      //printf("bin content pt: %.0f, %.0f\n", reco_bsig_pt2->GetBinContent(i+1), gen_bsig_pt2->GetBinContent(i+1));
      printf("%.3f$\\pm$%.3f & ", reco_gen_eff_pt2->GetEfficiency(i+1), max(reco_gen_eff_pt2->GetEfficiencyErrorUp(i+1), reco_gen_eff_pt2->GetEfficiencyErrorLow(i+1)));
  }
  cout<<endl;
  cout<<"y 2-------------"<<endl;
  for(int i = 0; i < reco_bsig_y2->GetNbinsX(); i ++){
      //printf("bincontent y: %.0f, %.0f\n", reco_bsig_y2->GetBinContent(i+1), gen_bsig_y2->GetBinContent(i+1));
      printf("%.3f$\\pm$%.3f & ", reco_gen_eff_y2->GetEfficiency(i+1), max(reco_gen_eff_y2->GetEfficiencyErrorUp(i+1), reco_gen_eff_y2->GetEfficiencyErrorLow(i+1)));
  }
  cout<<endl;

  float _lumi1 = lumi1/(lumi1+lumi2);
  float _lumi2 = lumi2/(lumi1+lumi2);
  cout<<"sum pt-------------"<<endl;
  for(int i = 0; i < reco_bsig_pt->GetNbinsX(); i ++){
      printf("%.3f$\\pm$%.3f & ", _lumi1*reco_gen_eff_pt->GetEfficiency(i+1)+_lumi2*reco_gen_eff_pt2->GetEfficiency(i+1),
      max(sqrt(_lumi1*pow(reco_gen_eff_pt->GetEfficiencyErrorUp(i+1),2) + _lumi2*pow(reco_gen_eff_pt2->GetEfficiencyErrorUp(i+1),2)), 
          sqrt(_lumi1*pow(reco_gen_eff_pt->GetEfficiencyErrorLow(i+1),2) + _lumi2*pow(reco_gen_eff_pt2->GetEfficiencyErrorLow(i+1),2))));
  }
  cout<<endl;
  cout<<"sum y-------------"<<endl;
  for(int i = 1; i < reco_bsig_y->GetNbinsX()+1; i ++){
      //
      printf("%.3f$\\pm$%.3f & ", _lumi1*reco_gen_eff_y->GetEfficiency(6-i)+_lumi2*reco_gen_eff_y2->GetEfficiency(i),
      max(sqrt(_lumi1*pow(reco_gen_eff_y->GetEfficiencyErrorUp(6-i),2) + _lumi2*pow(reco_gen_eff_y2->GetEfficiencyErrorUp(i),2)), 
          sqrt(_lumi1*pow(reco_gen_eff_y->GetEfficiencyErrorLow(6-i),2) + _lumi2*pow(reco_gen_eff_y2->GetEfficiencyErrorLow(i),2))));
  }
  cout<<endl;

  DrawMyEff(c1, reco_gen_eff_pt, "pt[GeV]");
  DrawMyEff(c2, reco_gen_eff_y, "y_{CM}");
  DrawMyEff(c5, reco_gen_eff_pt2, "pt[GeV]");
  DrawMyEff(c6, reco_gen_eff_y2, "y_{CM}");

  fout->Write();
  fout->Close();
  if(MCflag == 1){
      c1->SaveAs(fig_folder+"_pPb/kp_pt_eff.pdf");
      c2->SaveAs(fig_folder+"_pPb/kp_y_eff.pdf");
      c5->SaveAs(fig_folder+"_Pbp/kp_pt_eff.pdf");
      c6->SaveAs(fig_folder+"_Pbp/kp_y_eff.pdf");
  }
  if(MCflag == 2){
      c1->SaveAs(fig_folder+"_pPb/kstar_pt_eff.pdf");
      c2->SaveAs(fig_folder+"_pPb/kstar_y_eff.pdf");
      c5->SaveAs(fig_folder+"_Pbp/kstar_pt_eff.pdf");
      c6->SaveAs(fig_folder+"_Pbp/kstar_y_eff.pdf");
  }
  if(MCflag == 3){
      c1->SaveAs(fig_folder+"_pPb/phi_pt_eff.pdf");
      c2->SaveAs(fig_folder+"_pPb/phi_y_eff.pdf");
      c5->SaveAs(fig_folder+"_Pbp/phi_pt_eff.pdf");
      c6->SaveAs(fig_folder+"_Pbp/phi_y_eff.pdf");
  }
  ////PLOTING////
}

void AcceptedCand(TTree *ntGen, TH1F* gen_bsig_pt, TH1F* gen_bsig_y, bool IsPpb, int nevents_total, int MCflag){
  if(nevents_total != ntGen->GetEntries()) printf("Warning evt # inconsistence %i, %lli\n", nevents_total, ntGen->GetEntries());
  Int_t size;
  Int_t Run;
  Float_t y[MAX_GEN];
  Float_t eta[MAX_GEN];
  Float_t phi[MAX_GEN];
  Float_t pt[MAX_GEN];
  Float_t pdgId[MAX_GEN];
  Float_t isSignal[MAX_GEN];
  Float_t mu1pt[MAX_GEN];
  Float_t mu2pt[MAX_GEN];
  Float_t mu1p[MAX_GEN];
  Float_t mu2p[MAX_GEN];
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
  ntGen->SetBranchAddress("Run",&Run);
  ntGen->SetBranchAddress("y",&y);
  ntGen->SetBranchAddress("eta",eta);
  ntGen->SetBranchAddress("phi",phi);
  ntGen->SetBranchAddress("pt",pt);
  ntGen->SetBranchAddress("pdgId",pdgId);
  ntGen->SetBranchAddress("isSignal",isSignal);
  ntGen->SetBranchAddress("mu1pt",mu1pt);
  ntGen->SetBranchAddress("mu2pt",mu2pt);
  ntGen->SetBranchAddress("mu1p",mu1p);
  ntGen->SetBranchAddress("mu2p",mu2p);
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
    if ((entry%100000) == 0) printf("Loading event #%d of %d.\n",entry,nevents_total);
    ntGen->GetEntry(entry);
	if(IsPpb && Run>1) continue;
	if(!IsPpb && Run<=1) continue;
    for(int c=0; c<size; c++){
      if(isSignal[c]){
        if(fabs(mu1eta[c]) < 1.3) {if(mu1pt[c] < 3.3) continue;}
        else if(fabs(mu1eta[c]) > 1.3 && fabs(mu1eta[c]) < 2.2) {if(mu1p[c] < 2.9) continue;}
        else if(fabs(mu1eta[c]) > 2.2 && fabs(mu1eta[c]) < 2.4) {if(mu1pt[c] < 0.8) continue;}
        else {continue;}
        if(fabs(mu2eta[c]) < 1.3) {if(mu2pt[c] < 3.3) continue;}
        else if(fabs(mu2eta[c]) > 1.3 && fabs(mu2eta[c]) < 2.2) {if(mu2p[c] < 2.9) continue;}
        else if(fabs(mu2eta[c]) > 2.2 && fabs(mu2eta[c]) < 2.4) {if(mu2pt[c] < 0.8) continue;}
        else {continue;}

		//muon pt cut
        if(mu1pt[c]<1.5 || mu2pt[c]<1.5) continue;

        mu1.SetPtEtaPhiM(mu1pt[c], mu1eta[c], mu1phi[c], MUON_MASS);
        mu2.SetPtEtaPhiM(mu2pt[c], mu2eta[c], mu2phi[c], MUON_MASS);
        if(MCflag==1){
          if(tk1pt[c] < 0.9) continue;
          tk1.SetPtEtaPhiM(tk1pt[c], tk1eta[c], tk1phi[c], KAON_MASS);
          B = mu1+mu2+tk1;
        }
        if(MCflag==2){
          if(tk1pt[c] < 0.7) continue;
          if(tk2pt[c] < 0.7) continue;
          tk1.SetPtEtaPhiM(tk1pt[c], tk1eta[c], tk1phi[c], KAON_MASS);
          tk2.SetPtEtaPhiM(tk2pt[c], tk2eta[c], tk2phi[c], PION_MASS);
          B = mu1+mu2+tk1+tk2;
        }
        if(MCflag==3){
          if(tk1pt[c] < 0.7) continue;
          if(tk2pt[c] < 0.7) continue;
          tk1.SetPtEtaPhiM(tk1pt[c], tk1eta[c], tk1phi[c], KAON_MASS);
          tk2.SetPtEtaPhiM(tk2pt[c], tk2eta[c], tk2phi[c], KAON_MASS);
          B = mu1+mu2+tk1+tk2;
        }
		//cout<<B.Mag()<<endl;
        //if(B.Mag() < 4.95 || B.Mag() > 5.55) continue;
        if(MCflag==1 && fabs(B.Mag()-BP_MASS)>1) continue;
        if(MCflag==2 && fabs(B.Mag()-BZERO_MASS)>1) continue;
        if(MCflag==3 && fabs(B.Mag()-BS_MASS)>1) continue;
		
        
        if(pt[c]>10 && pt[c]<60){
          //if(IsPpb && abs(y[c]+0.465)<1.93){
          if(IsPpb && abs(y[c])<2.4){
            gen_bsig_pt->Fill(pt[c]);
            gen_bsig_y->Fill(y[c]+0.465);
          }
          //if(!IsPpb && abs(y[c]-0.465)<1.93){
          if(!IsPpb && abs(y[c])<2.4){
            gen_bsig_pt->Fill(pt[c]);
            gen_bsig_y->Fill(y[c]-0.465);
          }
        }
      }
    }
  }
}
void DrawMyEff(TCanvas* c, TEfficiency* eff, TString axis){
  c->cd();
  eff->SetFillColor(2);
  eff->SetFillStyle(3001);
  eff->Draw("");
  c->Update();
  eff->GetPaintedGraph()->GetXaxis()->SetTitle(axis);
  eff->GetPaintedGraph()->SetMaximum(1);
  eff->GetPaintedGraph()->SetMinimum(0);
  eff->Draw("a2");
  eff->Draw("same");
  eff->Write();
  c->Write();
}
