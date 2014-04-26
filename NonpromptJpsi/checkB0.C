#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include "TMath.h"
#include "TCanvas.h"
#include "TH1F.h"

#define NUM_BX 9000

void loop(){

  TFile *inf = new TFile("../../output/myoutputBzero.root");
  TTree *nt = (TTree*)inf->Get("ntKstar");

  TString cut_kpi="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>1.65e-01&&(d0/d0Err)>4.16&&cos(dtheta)>7.50e-01&&abs(tktkmass-0.89594)<2.33e-01";
  TString seldata=Form("abs(y+0.465)<1.93&&%s&&mass>5.&&mass<6.",cut_kpi.Data());

  TH1D *hproject = new TH1D("hproject","",50,5,6);
  nt->Project("hproject","mass",Form("%s&&pt>%f&&pt<%f",seldata.Data(),10.,60.));

  cout<<hproject->GetEntries()<<endl;
  TCanvas*canvassecond=new TCanvas("canvassecond","canvassecond",800,400);
  hproject->Draw();
  canvassecond->SaveAs("canvassecond2.png");

}

void checkB0(){

  TFile *inf = new TFile("../../output/myoutputBzero.root");
  TTree *nt = (TTree*)inf->Get("ntKstar");

  TH1F*myhisto=new TH1F("myhisto","myhisto",50,5,6);
  TH1F*hBstoJPsiPhi=new TH1F("hBstoJPsiPhi","hBstoJPsiPhi",50,5,6);
  TH1F*hBplustoJPsiK1plus=new TH1F("hBplustoJPsiK1plus","hBplustoJPsiK1plus",50,5,6);
  TH1F*hBzerotoJPsiK10=new TH1F("hBzerotoJPsiK10","hBzerotoJPsiK10",50,5,6);

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

  Int_t nentries = (Int_t)nt->GetEntries();

  cout<<"entries"<<nentries<<endl;
  int counter=0;

  int i,j;
  for (i=0; i<nentries; i++) {
    nt->GetEntry(i);

    for(j=0;j<size;j++)
      {
	bool cut0=abs(y[j]+0.465)<1.93;
	bool cut1=((pt[j]>10.)&&(pt[j]<60.));
	bool cut2=abs(mumumass[j]-3.096916)<0.15;
	bool cut3=(HLT_PAMu3_v1);
	bool cut4=(mass[j]>5.);
	bool cut5=(mass[j]<6.);
	bool cut6=(isbestchi2[j]);
	bool cut7=(trk1Pt[j]>0.7);
	bool cut8=(trk2Pt[j]>0.7);
	bool cut9=(chi2cl[j]>(1.65*0.1));
	bool cut10=((d0[j]/d0Err[j])>4.16);
	bool cut11=(cos(dtheta[j])>(7.50*0.1));
	bool cut12=abs(tktkmass[j]-0.89594)<(2.33*0.1);
	bool cut13=((mass[j]>5.)&&(mass[j]<6.));


	if(cut0&&cut1&&cut2&&cut3&&cut4&&cut5&&cut6&&cut7&&cut8&&cut9&&cut10&&cut11&&cut12&&cut13){
	if((trk1geninfo[j]>-1)&&(trk2geninfo[j]>-1)&&(muon1geninfo[j]>-1)&&(muon2geninfo[j]>-1)){

	  counter++;
	  myhisto->Fill(mass[j]);
	  
	  if((pdggrandmothertrk1[0]==531)&&(pdggrandmothertrk2[0]==531)&&(pdggrandmothermuon1[0]==531)&&(pdggrandmothermuon2[0]==531)){
    if ((grandmothertrk1geninfo[0]==grandmothertrk2geninfo[0])&&(grandmothertrk1geninfo[0]==grandmothermuon1geninfo[0])&&(grandmothermuon1geninfo[0]==grandmothermuon2geninfo[0])){
    hBstoJPsiPhi->Fill(mass[0]);
    }
    }
    
    if((pdggrandmothertrk1[0]==521)&&(pdggrandmothertrk2[0]==521)&&(pdggrandmothermuon1[0]==521)&&(pdggrandmothermuon2[0]==521)){
    if((pdgmothertrk1[0]==10323)&&(pdgmothertrk2[0]==10323)&&(pdgmothermuon1[0]==443)&&(pdgmothermuon2[0]==443)){
    if ((grandmothertrk1geninfo[0]==grandmothertrk2geninfo[0])&&(grandmothertrk1geninfo[0]==grandmothermuon1geninfo[0])&&(grandmothermuon1geninfo[0]==grandmothermuon2geninfo[0])){

    hBplustoJPsiK1plus->Fill(mass[0]);
    }
    }
    }
    
    if((pdggrandmothertrk1[0]==511)&&(pdggrandmothertrk2[0]==511)&&(pdggrandmothermuon1[0]==511)&&(pdggrandmothermuon2[0]==511)){
    if((pdgmothertrk1[0]==10313)&&(pdgmothertrk2[0]==10313)&&(pdgmothermuon1[0]==443)&&(pdgmothermuon2[0]==443)){
    if ((grandmothertrk1geninfo[0]==grandmothertrk2geninfo[0])&&(grandmothertrk1geninfo[0]==grandmothermuon1geninfo[0])&&(grandmothermuon1geninfo[0]==grandmothermuon2geninfo[0])){

    hBzerotoJPsiK10->Fill(mass[0]);
    }
    }
    }
    
    if((pdggrandmothertrk1[0]==pdggrandmothertrk2[0])&&(pdggrandmothermuon1[0]==pdggrandmothermuon2[0])&&(pdggrandmothermuon1[0]==pdggrandmothertrk1[0])){
   
    cout<<"--------------------------"<<endl;
    cout<<"pdgtrk1="<<pdgtrk1[0]<<", pdgmothertrk1="<<pdgmothertrk1[0]<<", pdggrandmothertrk1="<<pdggrandmothertrk1[0]<<endl;
    cout<<"pdgtrk2="<<pdgtrk2[0]<<", pdgmothertrk2="<<pdgmothertrk2[0]<<", pdggrandmothertrk2="<<pdggrandmothertrk2[0]<<endl;
    cout<<"pdgmuon1="<<pdgmuon1[0]<<", pdgmothermuon1="<<pdgmothermuon1[0]<<", pdggrandmothermuon1="<<pdggrandmothermuon1[0]<<endl;
    cout<<"pdgmuon2="<<pdgmuon2[0]<<", pdgmothermuon2="<<pdgmothermuon2[0]<<", pdggrandmothermuon2="<<pdggrandmothermuon2[0]<<endl;

   }
	  
	}
	}

      }
  }

   TCanvas*canvassecond=new TCanvas("canvassecond","canvassecond",800,400);
   canvassecond->Divide(3,2);
   canvassecond->cd(1);
   myhisto->Draw();
   canvassecond->cd(2);
   hBstoJPsiPhi->Draw();
   canvassecond->cd(3);
   hBplustoJPsiK1plus->Draw();
   canvassecond->cd(4);
   hBzerotoJPsiK10->Draw();
   canvassecond->cd(5);
   myhisto->Draw();
  
  

}
