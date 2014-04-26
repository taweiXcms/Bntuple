#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include "TMath.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TLegendEntry.h"


#define NUM_BX 9000

void loop(){

  TFile *inf = new TFile("../../output/myoutputBzero.root");
  TTree *nt = (TTree*)inf->Get("ntKp");
  
  TString cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e01";
  TString seldata=Form("abs(y+0.465)<1.93&&%s",cut.Data());

  TH1D *hproject = new TH1D("hproject","",50,5,6);
  nt->Project("hproject","mass",Form("%s&&pt>%f&&pt<%f",seldata.Data(),10.,60.));

  TCanvas*canvassecond=new TCanvas("canvassecond","canvassecond",800,400);
  hproject->Draw();
  canvassecond->SaveAs("Plots/canvasBplusProject.png");

}

void checkBplus(){

  TFile *inf = new TFile("../../output/myoutputBzero.root");
  TTree *nt = (TTree*)inf->Get("ntKp");

  TH1F*hTotalNonPrompt=new TH1F("hTotalNonPrompt","hTotalNonPrompt",50,5,6);
  TH1F*hBplustoJPsiPi=new TH1F("hBplustoJPsiPi","hBplustoJPsiPi",50,5,6);
  

  Float_t pt[NUM_BX];
  Float_t mumumass[NUM_BX];
  Float_t y[NUM_BX];
  Float_t mass[NUM_BX];
  Float_t trk1Pt[NUM_BX];
  Float_t trk2Pt[NUM_BX];
  Float_t chi2cl[NUM_BX];
  Float_t d0[NUM_BX];
  Float_t d0Err[NUM_BX];
  Float_t dtheta[NUM_BX];
  Float_t tktkmass[NUM_BX];
  Int_t isbestchi2[NUM_BX];
  Int_t HLT_PAMu3_v1;
  Int_t size;
  Float_t gen[NUM_BX];


  Int_t trk1geninfo[NUM_BX];
  Int_t pdgtrk1[NUM_BX];
  Int_t mothertrk1geninfo[NUM_BX];
  Int_t pdgmothertrk1[NUM_BX];
  Int_t grandmothertrk1geninfo[NUM_BX];
  Int_t pdggrandmothertrk1[NUM_BX];

  Int_t trk2geninfo[NUM_BX];
  Int_t pdgtrk2[NUM_BX];
  Int_t mothertrk2geninfo[NUM_BX];
  Int_t pdgmothertrk2[NUM_BX];
  Int_t grandmothertrk2geninfo[NUM_BX];
  Int_t pdggrandmothertrk2[NUM_BX];

  Int_t muon1geninfo[NUM_BX];
  Int_t pdgmuon1[NUM_BX];
  Int_t mothermuon1geninfo[NUM_BX];
  Int_t pdgmothermuon1[NUM_BX];
  Int_t grandmothermuon1geninfo[NUM_BX];
  Int_t pdggrandmothermuon1[NUM_BX];

  Int_t muon2geninfo[NUM_BX];
  Int_t pdgmuon2[NUM_BX];
  Int_t mothermuon2geninfo[NUM_BX];
  Int_t pdgmothermuon2[NUM_BX];
  Int_t grandmothermuon2geninfo[NUM_BX];
  Int_t pdggrandmothermuon2[NUM_BX];

  Int_t Event;

  nt->SetBranchAddress("y",y);
  nt->SetBranchAddress("HLT_PAMu3_v1",&HLT_PAMu3_v1);
  nt->SetBranchAddress("size",&size);
  nt->SetBranchAddress("mumumass",mumumass);
  nt->SetBranchAddress("mass",mass);
  nt->SetBranchAddress("isbestchi2",isbestchi2);
  nt->SetBranchAddress("trk1Pt",trk1Pt);
  nt->SetBranchAddress("trk2Pt",trk2Pt);
  nt->SetBranchAddress("chi2cl",chi2cl);
  nt->SetBranchAddress("d0Err",d0Err);
  nt->SetBranchAddress("d0",d0);
  nt->SetBranchAddress("dtheta",dtheta);
  nt->SetBranchAddress("tktkmass",tktkmass);
  nt->SetBranchAddress("gen",gen);
  nt->SetBranchAddress("Event",&Event);
  nt->SetBranchAddress("pt",pt);

  nt->SetBranchAddress("pdgtrk1",pdgtrk1);
  nt->SetBranchAddress("pdgtrk2",pdgtrk2);
  nt->SetBranchAddress("pdgmuon1",pdgmuon1);
  nt->SetBranchAddress("pdgmuon2",pdgmuon2);
  
  nt->SetBranchAddress("pdgmothertrk1",pdgmothertrk1);
  nt->SetBranchAddress("pdgmothertrk2",pdgmothertrk2);
  nt->SetBranchAddress("pdgmothermuon1",pdgmothermuon1);
  nt->SetBranchAddress("pdgmothermuon2",pdgmothermuon2);
  
  nt->SetBranchAddress("pdggrandmothertrk1",pdggrandmothertrk1);
  nt->SetBranchAddress("pdggrandmothertrk2",pdggrandmothertrk2);
  nt->SetBranchAddress("pdggrandmothermuon1",pdggrandmothermuon1);
  nt->SetBranchAddress("pdggrandmothermuon2",pdggrandmothermuon2);
  
  nt->SetBranchAddress("trk1geninfo",trk1geninfo);
  nt->SetBranchAddress("trk2geninfo",trk2geninfo);
  nt->SetBranchAddress("muon1geninfo",muon1geninfo);
  nt->SetBranchAddress("muon2geninfo",muon2geninfo);
  
  nt->SetBranchAddress("grandmothertrk1geninfo",grandmothertrk1geninfo);
  nt->SetBranchAddress("grandmothertrk2geninfo",grandmothertrk2geninfo);
  nt->SetBranchAddress("grandmothermuon1geninfo",grandmothermuon1geninfo);
  nt->SetBranchAddress("grandmothermuon2geninfo",grandmothermuon2geninfo);
  
  nt->SetBranchAddress("mothermuon1geninfo",mothermuon1geninfo);
  nt->SetBranchAddress("mothermuon2geninfo",mothermuon2geninfo);
  nt->SetBranchAddress("mothertrk1geninfo",mothertrk1geninfo);
  nt->SetBranchAddress("mothertrk2geninfo",mothertrk2geninfo);
  

  Int_t nentries = (Int_t)nt->GetEntries();

  cout<<"entries"<<nentries<<endl;
  int counter=0;
  int countercase2=0;
  int countercase3=0;
  int countercaseno=0;


  int i,j;
  for (i=0; i<nentries; i++) {
    nt->GetEntry(i);

    for(j=0;j<size;j++){
      
      bool cut0=abs(y[j]+0.465)<1.93;
   	  bool cut1=((pt[j]>10.)&&(pt[j]<60.));
	  bool cut2=abs(mumumass[j]-3.096916)<0.15;
	  bool cut3=(HLT_PAMu3_v1);
	  bool cut4=(mass[j]>5.);
	  bool cut5=(mass[j]<6.);
	  bool cut6=(isbestchi2[j]);
	  bool cut7=(trk1Pt[j]>0.9);
	  bool cut8=(chi2cl[j]>(1.32e-02));
	  bool cut9=((d0[j]/d0Err[j])>3.41);
  	  bool cut10=(cos(dtheta[j])>(-3.46));
	  bool cut11=((mass[j]>5.)&&(mass[j]<6.));
	  bool cut12=(!(gen[j]==22233));
      
      bool case2=false;
      bool case3=false;
      
	  if(cut0&&cut1&&cut2&&cut3&&cut4&&cut5&&cut6&&cut7&&cut8&&cut9&&cut10&&cut11){
   	    if((trk1geninfo[j]>-1)&&(muon1geninfo[j]>-1)&&(muon2geninfo[j]>-1)){
	      if((pdgtrk1[j]>0)&&(pdgtrk2[j]>0)&&(pdgmuon1[j]>0)&&(pdgmuon2[j]>0)){
	      
	        counter++;	        
	        
	        hTotalNonPrompt->Fill(mass[j]);
		  
	        if((pdgtrk1[j]==211)&&(pdggrandmothertrk1[j]==521)&&(pdggrandmothermuon1[j]==531)&&(pdggrandmothermuon2[j]==531)){
              if ((mothertrk1geninfo[j]==grandmothermuon1geninfo[j])&&(grandmothermuon1geninfo[j]==grandmothermuon2geninfo[j])){
                hBplustoJPsiPi->Fill(mass[j]);
                case2=true;
                countercase2++;
              }
            } 
            
           if((case2==false)){
             countercaseno++;
             cout<<"--------------------------"<<endl;
             cout<<"pdgtrk1="<<pdgtrk1[j]<<", pdgmothertrk1="<<pdgmothertrk1[j]<<", pdggrandmothertrk1="<<pdggrandmothertrk1[j]<<endl;
             cout<<"pdgtrk2="<<pdgtrk2[j]<<", pdgmothertrk2="<<pdgmothertrk2[j]<<", pdggrandmothertrk2="<<pdggrandmothertrk2[j]<<endl;
             cout<<"pdgmuon1="<<pdgmuon1[j]<<", pdgmothermuon1="<<pdgmothermuon1[j]<<", pdggrandmothermuon1="<<pdggrandmothermuon1[j]<<endl;
             cout<<"pdgmuon2="<<pdgmuon2[j]<<", pdgmothermuon2="<<pdgmothermuon2[j]<<", pdggrandmothermuon2="<<pdggrandmothermuon2[j]<<endl;
             cout<<"grandmothertrk1geninfo="<<grandmothertrk1geninfo[j]<<", grandmothertrk2geninfo="<<grandmothertrk2geninfo[j]<<", grandmothermuon1geninfo="<<grandmothermuon1geninfo[j]<<", grandmothermuon2geninfo="<<grandmothermuon2geninfo[j]<<endl;
             cout<<"mothertrk1geninfo="<<mothertrk1geninfo[j]<<", mothertrk2geninfo="<<mothertrk2geninfo[j]<<", mothermuon1geninfo="<<mothermuon1geninfo[j]<<", mothermuon2geninfo="<<mothermuon2geninfo[j]<<endl;

           }
          }
 	    }
      }
    }
  }
  cout<<counter<<endl;
  cout<<"countercase2"<<countercase2<<endl;

  cout<<countercase2<<endl;

  
  
  TCanvas*canvassecond=new TCanvas("canvassecond","canvassecond",800,400);
  canvassecond->Divide(3,2);
  canvassecond->cd(1);
  hTotalNonPrompt->Draw("e");
  canvassecond->SaveAs("Plots/CanvasComponentBzero.png");
  
  TFile*fileoutput=new TFile("Plots/PlotoutputBzero.root","recreate");
  fileoutput->cd();
  hTotalNonPrompt->Write();
  hBplustoJPsiPi->Write();
  fileoutput->Close();
  delete fileoutput;
  

}


void Draw(){



  TFile*fileoutput=new TFile("Plots/PlotoutputBzero.root");
  
  TH1F*hTotalNonPrompt=(TH1F*)fileoutput->Get("hTotalNonPrompt");
  TH1F*hBplustoJPsiPi=(TH1F*)fileoutput->Get("hBplustoJPsiPi");

  TCanvas *canvas=new TCanvas("canvas","canvas",600,600);
  canvas->cd();
  TH2F* hempty=new TH2F("hempty","",10,5.,6,10.,0,180);  
  hempty->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
  hempty->GetYaxis()->SetTitle("Entries");
  hempty->GetXaxis()->SetTitleOffset(1.);
  hempty->GetYaxis()->SetTitleOffset(1.);
  hempty->GetXaxis()->SetTitleSize(0.04);
  hempty->GetYaxis()->SetTitleSize(0.04);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.035);
  hempty->GetYaxis()->SetLabelSize(0.035);  
  hempty->SetMinimum(0.);
  hempty->SetMaximum(400);
  hempty->Draw();
  
  TLegend *legend=new TLegend(0.1795302,0.6377119,0.25,0.8728814,"");
  legend->SetBorderSize(0);
  legend->SetFillStyle(0);
  legend->SetBorderSize(0);
  legend->SetTextFont(42);
  legend->SetTextSize(0.045);
  
  TLegendEntry *entTotalNonPrompt=legend->AddEntry(hTotalNonPrompt,"Total non prompt","P");
  hTotalNonPrompt->SetLineColor(1);
  hTotalNonPrompt->SetMarkerColor(1);
  entTotalNonPrompt->SetTextColor(1);
  entTotalNonPrompt->SetLineColor(1);
  hTotalNonPrompt->SetMarkerStyle(21);
  entTotalNonPrompt->SetLineWidth(1);
  hTotalNonPrompt->SetLineWidth(1);
  entTotalNonPrompt->SetTextSize(0.03);
  hTotalNonPrompt->Draw("esame");
  canvas->Update();
  legend->Draw();

  TLegendEntry *entBplusstoJPsiPi=legend->AddEntry(hBplustoJPsiPi,"B_{s} #rightarrow JPsi+Phi","P");
  hBplustoJPsiPi->SetLineColor(2);
  hBplustoJPsiPi->SetMarkerColor(2);
  entBplusstoJPsiPi->SetTextColor(2);
  entBplusstoJPsiPi->SetLineColor(2);
  hBplustoJPsiPi->SetMarkerStyle(21);
  entBplusstoJPsiPi->SetLineWidth(1);
  hBplustoJPsiPi->SetLineWidth(1);
  entBplusstoJPsiPi->SetTextSize(0.03);
  hBplustoJPsiPi->Draw("esame");
  canvas->Update();
 
  canvas->SaveAs("Plots/canvasSummaryBplus.png");

}