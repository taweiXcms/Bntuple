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

  TFile *inf = new TFile("/net/hisrv0001/home/yenjie/scratch/gianTemp/myoutputBzero.root");
  TTree *nt = (TTree*)inf->Get("ntKstar");

  TString cut_kpi="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>1.65e-01&&(d0/d0Err)>4.16&&cos(dtheta)>7.50e-01&&abs(tktkmass-0.89594)<2.33e-01";
  TString seldata=Form("abs(y+0.465)<1.93&&%s&&mass>5.&&mass<6.",cut_kpi.Data());

  TH1D *hproject = new TH1D("hproject","",50,5,6);
  nt->Project("hproject","mass",Form("%s&&pt>%f&&pt<%f",seldata.Data(),10.,60.));

  cout<<hproject->GetEntries()<<endl;
  TCanvas*canvassecond=new TCanvas("canvassecond","canvassecond",800,400);
  hproject->Draw();
  canvassecond->SaveAs("Plots/canvasBzeroProject.png");

}

void checkB0(){

  TFile *inf = new TFile("/net/hisrv0001/home/yenjie/scratch/gianTemp/myoutputBzero.root");
  TTree *nt = (TTree*)inf->Get("ntKstar");

  TH1F*hTotalNonPrompt=new TH1F("hTotalNonPrompt","hTotalNonPrompt",50,5,6);
  TH1F*hBstoJPsiPhi=new TH1F("hBstoJPsiPhi","hBstoJPsiPhi",50,5,6);
  TH1F*hBplustoJPsiK1plus=new TH1F("hBplustoJPsiK1plus","hBplustoJPsiK1plus",50,5,6);
  TH1F*hBzerotoJPsiK10=new TH1F("hBzerotoJPsiK10","hBzerotoJPsiK10",50,5,6);
  TH1F*hBzerotoJPsiKstar20=new TH1F("hBzerotoJPsiKstar20","hBzerotoJPsiKstar20",50,5,6);
  TH1F*hBzerotoJPsiKPi=new TH1F("hBzerotoJPsiKPi","hBzerotoJPsiKPi",50,5,6);
  
  TH1F*hBplustoJPsiKPi=new TH1F("hBplustoJPsiKPi","hBplustoJPsiKPi",50,5,6);
  TH1F*hBstoJPsiTrackTrack=new TH1F("hBstoJPsiTrackTrack","hBstoJPsiTrackTrack",50,5,6);
  TH1F*hBzerotoJPsiKstarplusPion=new TH1F("hBzerotoJPsiKstarplusPion","hBzerotoJPsiKstarplusPion",50,5,6);
  
    /*

  pdgtrk1=211, pdgmothertrk1=323, pdggrandmothertrk1=511
pdgtrk2=211, pdgmothertrk2=511, pdggrandmothertrk2=513
pdgmuon1=13, pdgmothermuon1=443, pdggrandmothermuon1=511
pdgmuon2=13, pdgmothermuon2=443, pdggrandmothermuon2=511
grandmothertrk1geninfo=63, grandmothertrk2geninfo=21, grandmothermuon1geninfo=63, grandmothermuon2geninfo=63
mothertrk1geninfo=91, mothertrk2geninfo=63, mothermuon1geninfo=90, mothermuon2geninfo=90
  
  */




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
  int countercase1=0;
  int countercase2=0;
  int countercase3=0;
  int countercase4=0;
  int countercase5=0;
  int countercase6=0;
  int countercase7=0;
  int countercase8=0;
  int countercase9=0;
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
	  bool cut7=(trk1Pt[j]>0.7);
	  bool cut8=(trk2Pt[j]>0.7);
	  bool cut9=(chi2cl[j]>(1.65*0.1));
	  bool cut10=((d0[j]/d0Err[j])>4.16);
  	  bool cut11=(cos(dtheta[j])>(7.50*0.1));
	  bool cut12=abs(tktkmass[j]-0.89594)<(2.33*0.1);
	  bool cut13=((mass[j]>5.)&&(mass[j]<6.));
	  bool cut14=(!((gen[j]==22233)||(gen[j]==41000)));
      
      bool case1=false;
      bool case2=false;
      bool case3=false;
      bool case4=false;
      bool case5=false;
      bool case6=false;
      bool case7=false;
      bool case8=false;
      bool case9=false;
      
	  if(cut0&&cut1&&cut2&&cut3&&cut4&&cut5&&cut6&&cut7&&cut8&&cut9&&cut10&&cut11&&cut12&&cut13&&cut14){
	    if((trk1geninfo[j]>-1)&&(trk2geninfo[j]>-1)&&(muon1geninfo[j]>-1)&&(muon2geninfo[j]>-1)){
	      if((pdgtrk1[j]>0)&&(pdgtrk2[j]>0)&&(pdgmuon1[j]>0)&&(pdgmuon2[j]>0)){
	      
	        counter++;
	        
	        hTotalNonPrompt->Fill(mass[j]);
		  
	        if((pdggrandmothertrk1[j]==531)&&(pdggrandmothertrk2[j]==531)&&(pdggrandmothermuon1[j]==531)&&(pdggrandmothermuon2[j]==531)){
              if ((grandmothertrk1geninfo[j]==grandmothertrk2geninfo[j])&&(grandmothertrk1geninfo[j]==grandmothermuon1geninfo[j])&&(grandmothermuon1geninfo[j]==grandmothermuon2geninfo[j])){
                hBstoJPsiPhi->Fill(mass[j]);
                case2=true;
                countercase2++;
              }
            } 
    
            if((pdggrandmothertrk1[j]==521)&&(pdggrandmothertrk2[j]==521)&&(pdggrandmothermuon1[j]==521)&&(pdggrandmothermuon2[j]==521)){
              if((pdgmothertrk1[j]==10323)&&(pdgmothertrk2[j]==10323)&&(pdgmothermuon1[j]==443)&&(pdgmothermuon2[j]==443)){
                if ((grandmothertrk1geninfo[j]==grandmothertrk2geninfo[j])&&(grandmothertrk1geninfo[j]==grandmothermuon1geninfo[j])&&(grandmothermuon1geninfo[j]==grandmothermuon2geninfo[j])){
                  hBplustoJPsiK1plus->Fill(mass[j]);
                  case3=true;
                  countercase3++;
                }
              }
            }
            
            

     
            if((pdggrandmothertrk1[j]==511)&&(pdggrandmothertrk2[j]==511)&&(pdggrandmothermuon1[j]==511)&&(pdggrandmothermuon2[j]==511)){
              if((pdgmothertrk1[j]==10313)&&(pdgmothertrk2[j]==10313)&&(pdgmothermuon1[j]==443)&&(pdgmothermuon2[j]==443)){
                if((grandmothertrk1geninfo[j]==grandmothertrk2geninfo[j])&&(grandmothertrk1geninfo[j]==grandmothermuon1geninfo[j])&&(grandmothermuon1geninfo[j]==grandmothermuon2geninfo[j])){
                  case4=true;
                  hBzerotoJPsiK10->Fill(mass[j]);
                  countercase4++;
                }
              }
            }
     
            if((pdggrandmothertrk1[j]==511)&&(pdggrandmothertrk2[j]==511)&&(pdggrandmothermuon1[j]==511)&&(pdggrandmothermuon2[j]==511)){
              if((pdgmothertrk1[j]==315)&&(pdgmothertrk2[j]==315)&&(pdgmothermuon1[j]==443)&&(pdgmothermuon2[j]==443)){
                if ((grandmothertrk1geninfo[j]==grandmothertrk2geninfo[j])&&(grandmothertrk1geninfo[j]==grandmothermuon1geninfo[j])&&(grandmothermuon1geninfo[j]==grandmothermuon2geninfo[j])){
                  hBzerotoJPsiKstar20->Fill(mass[j]);
                  case5=true;
                  countercase5++;
                  
                }
              }
            }
    
            if((pdgmothertrk1[j]==511)&&(pdgmothertrk2[j]==511)&&(pdggrandmothermuon1[j]==511)&&(pdggrandmothermuon2[j]==511)){
              if ((mothertrk1geninfo[j]==mothertrk2geninfo[j])&&(mothertrk1geninfo[j]==grandmothermuon1geninfo[j])&&(grandmothermuon1geninfo[j]==grandmothermuon2geninfo[j])){
                hBzerotoJPsiKPi->Fill(mass[j]);
                case6=true;
                countercase6++;
              }
            }
            
            if((pdgmothertrk1[j]==521)&&(pdgmothertrk2[j]==521)&&(pdggrandmothermuon1[j]==521)&&(pdggrandmothermuon2[j]==521)){
              if ((mothertrk1geninfo[j]==mothertrk2geninfo[j])&&(mothertrk1geninfo[j]==grandmothermuon1geninfo[j])&&(grandmothermuon1geninfo[j]==grandmothermuon2geninfo[j])){
                hBplustoJPsiKPi->Fill(mass[j]);
                case7=true;
                countercase7++;
              }
            }
             if((pdgmothertrk1[j]==531)&&(pdgmothertrk2[j]==531)&&(pdggrandmothermuon1[j]==531)&&(pdggrandmothermuon2[j]==531)){
              if ((mothertrk1geninfo[j]==mothertrk2geninfo[j])&&(mothertrk1geninfo[j]==grandmothermuon1geninfo[j])&&(grandmothermuon1geninfo[j]==grandmothermuon2geninfo[j])){
                hBstoJPsiTrackTrack->Fill(mass[j]);
                case8=true;
                countercase8++;
              }
            }
            
            if((pdgmothertrk1[j]==323)&&(pdggrandmothertrk1[j]==511)&&(pdgmothertrk2[j]==511)&&(pdggrandmothermuon1[j]==511)&&(pdggrandmothermuon2[j]==511)){
              if ((grandmothertrk1geninfo[j]==mothertrk2geninfo[j])&&(mothertrk2geninfo[j]==grandmothermuon1geninfo[j])&&(grandmothermuon1geninfo[j]==grandmothermuon2geninfo[j])){
                hBzerotoJPsiKstarplusPion->Fill(mass[j]);
                case9=true;
                countercase9++;
              }
            }
            
            if((pdgmothertrk2[j]==323)&&(pdggrandmothertrk2[j]==511)&&(pdgmothertrk1[j]==511)&&(pdggrandmothermuon1[j]==511)&&(pdggrandmothermuon2[j]==511)){
              if ((grandmothertrk2geninfo[j]==mothertrk1geninfo[j])&&(mothertrk1geninfo[j]==grandmothermuon1geninfo[j])&&(grandmothermuon1geninfo[j]==grandmothermuon2geninfo[j])){
                hBzerotoJPsiKstarplusPion->Fill(mass[j]);
                case9=true;
                countercase9++;
              }
            }
            
           if((case2==false)&&(case3==false)&&(case4==false)&&(case5==false)&&(case6==false)&&(case6==false)&&(case7==false)&&(case8==false)&&(case8==false)&&(case9==false)){
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
  cout<<"countercase3"<<countercase3<<endl;
  cout<<"countercase4"<<countercase4<<endl; 
  cout<<"countercase5"<<countercase5<<endl; 
  cout<<"countercase6"<<countercase6<<endl; 
  cout<<"countercase7"<<countercase7<<endl; 
  cout<<"countercase8"<<countercase8<<endl; 
  cout<<"countercase9"<<countercase9<<endl; 


  cout<<countercaseno<<endl;
  cout<<countercase2+countercase3+countercase4+countercase5+countercase6+countercase7+countercase8+countercase9<<endl;

  
  
  TCanvas*canvassecond=new TCanvas("canvassecond","canvassecond",800,400);
  canvassecond->Divide(3,2);
  canvassecond->cd(1);
  hTotalNonPrompt->Draw("e");
  canvassecond->cd(2);
  hBstoJPsiPhi->Draw("e");
  canvassecond->cd(3);
  hBplustoJPsiK1plus->Draw("e");
  canvassecond->cd(4);
  hBzerotoJPsiK10->Draw("e");
  canvassecond->cd(4);
  hBzerotoJPsiKstar20->Draw("e");
  canvassecond->cd(5);
  hBzerotoJPsiKPi->Draw("e");
  canvassecond->cd(5);
  hBplustoJPsiKPi->Draw("e");
  canvassecond->cd(6);
  hBstoJPsiTrackTrack->Draw("e");
  canvassecond->SaveAs("Plots/CanvasComponentBzero.png");
  
  TFile*fileoutput=new TFile("Plots/PlotoutputBzero.root","recreate");
  fileoutput->cd();
  hTotalNonPrompt->Write();
  hBstoJPsiPhi->Write();
  hBzerotoJPsiK10->Write();
  hBplustoJPsiK1plus->Write();
  hBzerotoJPsiKstar20->Write();
  hBzerotoJPsiKPi->Write();
  hBplustoJPsiKPi->Write();
  hBstoJPsiTrackTrack->Write();
  hBzerotoJPsiKstarplusPion->Write();
  fileoutput->Close();
  delete fileoutput;
  

}


void Draw(){



  TFile*fileoutput=new TFile("Plots/PlotoutputBzero.root");
  
  TH1F*hTotalNonPrompt=(TH1F*)fileoutput->Get("hTotalNonPrompt");
  TH1F*hBstoJPsiPhi=(TH1F*)fileoutput->Get("hBstoJPsiPhi");
  TH1F*hBzerotoJPsiK10=(TH1F*)fileoutput->Get("hBzerotoJPsiK10");
  TH1F*hBplustoJPsiK1plus=(TH1F*)fileoutput->Get("hBplustoJPsiK1plus");
  TH1F*hBzerotoJPsiKstar20=(TH1F*)fileoutput->Get("hBzerotoJPsiKstar20");
  TH1F*hBzerotoJPsiKPi=(TH1F*)fileoutput->Get("hBzerotoJPsiKPi");
  TH1F*hBplustoJPsiKPi=(TH1F*)fileoutput->Get("hBplustoJPsiKPi");
  TH1F*hBstoJPsiTrackTrack=(TH1F*)fileoutput->Get("hBstoJPsiTrackTrack");
  TH1F*hBzerotoJPsiKstarplusPion=(TH1F*)fileoutput->Get("hBzerotoJPsiKstarplusPion");
  
  hBstoJPsiTrackTrack->Draw();

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

  TLegendEntry *entBstoJPsiPhi=legend->AddEntry(hBstoJPsiPhi,"B_{s} #rightarrow JPsi+Phi","P");
  hBstoJPsiPhi->SetLineColor(2);
  hBstoJPsiPhi->SetMarkerColor(2);
  entBstoJPsiPhi->SetTextColor(2);
  entBstoJPsiPhi->SetLineColor(2);
  hBstoJPsiPhi->SetMarkerStyle(21);
  entBstoJPsiPhi->SetLineWidth(1);
  hBstoJPsiPhi->SetLineWidth(1);
  entBstoJPsiPhi->SetTextSize(0.03);
  hBstoJPsiPhi->Draw("esame");
  canvas->Update();
 
  TLegendEntry *entBzerotoJPsiK10=legend->AddEntry(hBzerotoJPsiK10,"B^{0} #rightarrow JPsi+K10","P");
  hBzerotoJPsiK10->SetLineColor(4);
  hBzerotoJPsiK10->SetMarkerColor(4);
  entBzerotoJPsiK10->SetTextColor(4);
  entBzerotoJPsiK10->SetLineColor(4);
  hBzerotoJPsiK10->SetMarkerStyle(21);
  entBzerotoJPsiK10->SetLineWidth(1);
  hBzerotoJPsiK10->SetLineWidth(1);
  entBzerotoJPsiK10->SetTextSize(0.03);
  hBzerotoJPsiK10->Draw("esame");
  canvas->Update();

  TLegendEntry *entBplustoJPsiK1plus=legend->AddEntry(hBplustoJPsiK1plus,"B^{+} #rightarrow JPsi+K1plus","P");
  hBplustoJPsiK1plus->SetLineColor(12);
  hBplustoJPsiK1plus->SetMarkerColor(12);
  entBplustoJPsiK1plus->SetTextColor(12);
  entBplustoJPsiK1plus->SetLineColor(12);
  hBplustoJPsiK1plus->SetMarkerStyle(21);
  entBplustoJPsiK1plus->SetLineWidth(1);
  hBplustoJPsiK1plus->SetLineWidth(1);
  entBplustoJPsiK1plus->SetTextSize(0.03);
  hBplustoJPsiK1plus->Draw("esame");
  canvas->Update();

  TLegendEntry *entBzerotoJPsiKstar20=legend->AddEntry(hBzerotoJPsiKstar20,"B^{0} #rightarrow JPsi+K*20","P");
  hBzerotoJPsiKstar20->SetLineColor(6);
  hBzerotoJPsiKstar20->SetMarkerColor(6);
  entBzerotoJPsiKstar20->SetTextColor(6);
  entBzerotoJPsiKstar20->SetLineColor(6);
  hBzerotoJPsiKstar20->SetMarkerStyle(21);
  entBzerotoJPsiKstar20->SetLineWidth(1);
  hBzerotoJPsiKstar20->SetLineWidth(1);
  entBzerotoJPsiKstar20->SetTextSize(0.03);
  hBzerotoJPsiKstar20->Draw("esame");
  canvas->Update();
  

  TLegendEntry *entBzerotoJPsiKPi=legend->AddEntry(hBzerotoJPsiKPi,"B^{0} #rightarrow JPsi+K Pi","P");
  hBzerotoJPsiKPi->SetLineColor(7);
  hBzerotoJPsiKPi->SetMarkerColor(7);
  entBzerotoJPsiKPi->SetTextColor(7);
  entBzerotoJPsiKPi->SetLineColor(7);
  hBzerotoJPsiKPi->SetMarkerStyle(21);
  entBzerotoJPsiKPi->SetLineWidth(1);
  hBzerotoJPsiKPi->SetLineWidth(1);
  entBzerotoJPsiKPi->SetTextSize(0.03);
  hBzerotoJPsiKPi->Draw("esame");
  canvas->Update();

  TLegendEntry *entBplustoJPsiKPi=legend->AddEntry(hBplustoJPsiKPi,"B^{+} #rightarrow JPsi+K Pi","P");
  hBplustoJPsiKPi->SetLineColor(8);
  hBplustoJPsiKPi->SetMarkerColor(8);
  entBplustoJPsiKPi->SetTextColor(8);
  entBplustoJPsiKPi->SetLineColor(8);
  hBplustoJPsiKPi->SetMarkerStyle(21);
  entBplustoJPsiKPi->SetLineWidth(1);
  hBplustoJPsiKPi->SetLineWidth(1);
  entBplustoJPsiKPi->SetTextSize(0.03);
  hBplustoJPsiKPi->Draw("esame");
  canvas->Update();

  TLegendEntry *entBstoJPsiKPi=legend->AddEntry(hBstoJPsiTrackTrack,"B_{s} #rightarrow JPsi+Track+Track","P");
  hBstoJPsiTrackTrack->SetLineColor(9);
  hBstoJPsiTrackTrack->SetMarkerColor(9);
  entBstoJPsiKPi->SetTextColor(9);
  entBstoJPsiKPi->SetLineColor(9);
  hBstoJPsiTrackTrack->SetMarkerStyle(21);
  entBstoJPsiKPi->SetLineWidth(1);
  hBstoJPsiTrackTrack->SetLineWidth(1);
  entBstoJPsiKPi->SetTextSize(0.03);
  hBstoJPsiTrackTrack->Draw("esame");
  canvas->Update();
  legend->Draw();
  
  
  TLegendEntry *entBzerotoJPsiKstarplusPion=legend->AddEntry(hBzerotoJPsiKstarplusPion,"B^{0} #rightarrow JPsi+K*+ Pi","P");
  hBzerotoJPsiKstarplusPion->SetLineColor(9);
  hBzerotoJPsiKstarplusPion->SetMarkerColor(9);
  entBzerotoJPsiKstarplusPion->SetTextColor(9);
  entBzerotoJPsiKstarplusPion->SetLineColor(9);
  hBzerotoJPsiKstarplusPion->SetMarkerStyle(21);
  entBzerotoJPsiKstarplusPion->SetLineWidth(1);
  hBzerotoJPsiKstarplusPion->SetLineWidth(1);
  entBzerotoJPsiKstarplusPion->SetTextSize(0.03);
  hBzerotoJPsiKstarplusPion->Draw("esame");
  canvas->Update();
  legend->Draw();
  
  canvas->SaveAs("Plots/canvasSummaryBzero.png");

}



void DrawAll(){



  TFile*fileoutput=new TFile("Plots/PlotoutputBzero.root");
  
  TH1F*hTotalNonPrompt=(TH1F*)fileoutput->Get("hTotalNonPrompt");
  TH1F*hBstoJPsiPhi=(TH1F*)fileoutput->Get("hBstoJPsiPhi");
  TH1F*hBzerotoJPsiK10=(TH1F*)fileoutput->Get("hBzerotoJPsiK10");
  TH1F*hBplustoJPsiK1plus=(TH1F*)fileoutput->Get("hBplustoJPsiK1plus");
  TH1F*hBzerotoJPsiKstar20=(TH1F*)fileoutput->Get("hBzerotoJPsiKstar20");
  TH1F*hBzerotoJPsiKPi=(TH1F*)fileoutput->Get("hBzerotoJPsiKPi");
  TH1F*hBplustoJPsiKPi=(TH1F*)fileoutput->Get("hBplustoJPsiKPi");
  TH1F*hBstoJPsiTrackTrack=(TH1F*)fileoutput->Get("hBstoJPsiTrackTrack");
  TH1F*hBzerotoJPsiKstarplusPion=(TH1F*)fileoutput->Get("hBzerotoJPsiKstarplusPion");
  
  hBstoJPsiTrackTrack->Draw();

  TCanvas *canvas=new TCanvas("canvas","canvas",600,600);
  canvas->Divide(2,4);
  TH2F* hempty=new TH2F("hempty","",10,5.,6,10.,0,80);  
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
  //hempty->Draw();
  
  
  canvas->cd(1);
  TLegend *legendBstoJPsiPhi=new TLegend(0.595302,0.6377119,0.25,0.8728814,"");
  legendBstoJPsiPhi->SetBorderSize(0);
  legendBstoJPsiPhi->SetFillStyle(0);
  legendBstoJPsiPhi->SetBorderSize(0);
  legendBstoJPsiPhi->SetTextFont(42);
  legendBstoJPsiPhi->SetTextSize(0.085);
  
  TLegendEntry *entBstoJPsiPhi=legendBstoJPsiPhi->AddEntry(hBstoJPsiPhi,"B_{s} #rightarrow JPsi+Phi","P");
  hBstoJPsiPhi->SetLineColor(2);
  hBstoJPsiPhi->SetMarkerColor(2);
  entBstoJPsiPhi->SetTextColor(2);
  entBstoJPsiPhi->SetLineColor(2);
  hBstoJPsiPhi->SetMarkerStyle(21);
  entBstoJPsiPhi->SetLineWidth(1);
  hBstoJPsiPhi->SetLineWidth(1);
  entBstoJPsiPhi->SetTextSize(0.085);
  hempty->Draw();
  hBstoJPsiPhi->Draw("esame");
  legendBstoJPsiPhi->Draw();
  canvas->Update();
   
  canvas->cd(2);
  
  TLegend *legendBzerotoJPsiK10=new TLegend(0.595302,0.6377119,0.25,0.8728814,"");
  legendBzerotoJPsiK10->SetBorderSize(0);
  legendBzerotoJPsiK10->SetFillStyle(0);
  legendBzerotoJPsiK10->SetBorderSize(0);
  legendBzerotoJPsiK10->SetTextFont(42);
  legendBzerotoJPsiK10->SetTextSize(0.085);
 
  TLegendEntry *entBzerotoJPsiK10=legendBzerotoJPsiK10->AddEntry(legendBzerotoJPsiK10,"B^{0} #rightarrow JPsi+K10","P");
  hBzerotoJPsiK10->SetLineColor(4);
  hBzerotoJPsiK10->SetMarkerColor(4);
  entBzerotoJPsiK10->SetTextColor(4);
  entBzerotoJPsiK10->SetLineColor(4);
  hBzerotoJPsiK10->SetMarkerStyle(21);
  entBzerotoJPsiK10->SetLineWidth(1);
  hBzerotoJPsiK10->SetLineWidth(1);
  entBzerotoJPsiK10->SetTextSize(0.085);
  hempty->Draw();
  hBzerotoJPsiK10->Draw("esame");
  legendBzerotoJPsiK10->Draw();
  canvas->Update();
  
  canvas->cd(3);
  
  TLegend *legendBplustoJPsiK1plus=new TLegend(0.595302,0.6377119,0.25,0.8728814,"");
  legendBplustoJPsiK1plus->SetBorderSize(0);
  legendBplustoJPsiK1plus->SetFillStyle(0);
  legendBplustoJPsiK1plus->SetBorderSize(0);
  legendBplustoJPsiK1plus->SetTextFont(42);
  legendBplustoJPsiK1plus->SetTextSize(0.085);

  TLegendEntry *entBplustoJPsiK1plus=legendBplustoJPsiK1plus->AddEntry(hBplustoJPsiK1plus,"B^{+} #rightarrow JPsi+K1plus","P");
  hBplustoJPsiK1plus->SetLineColor(12);
  hBplustoJPsiK1plus->SetMarkerColor(12);
  entBplustoJPsiK1plus->SetTextColor(12);
  entBplustoJPsiK1plus->SetLineColor(12);
  hBplustoJPsiK1plus->SetMarkerStyle(21);
  entBplustoJPsiK1plus->SetLineWidth(1);
  hBplustoJPsiK1plus->SetLineWidth(1);
  entBplustoJPsiK1plus->SetTextSize(0.085);
  hempty->Draw();
  hBplustoJPsiK1plus->Draw("esame");
  legendBplustoJPsiK1plus->Draw();
  canvas->Update();
  
  canvas->cd(4);
  
  TLegend *legendBzerotoJPsiKstar20=new TLegend(0.595302,0.6377119,0.25,0.8728814,"");
  legendBzerotoJPsiKstar20->SetBorderSize(0);
  legendBzerotoJPsiKstar20->SetFillStyle(0);
  legendBzerotoJPsiKstar20->SetBorderSize(0);
  legendBzerotoJPsiKstar20->SetTextFont(42);
  legendBzerotoJPsiKstar20->SetTextSize(0.085);

  TLegendEntry *entBzerotoJPsiKstar20=legendBzerotoJPsiKstar20->AddEntry(hBzerotoJPsiKstar20,"B^{0} #rightarrow JPsi+K*20","P");
  hBzerotoJPsiKstar20->SetLineColor(6);
  hBzerotoJPsiKstar20->SetMarkerColor(6);
  entBzerotoJPsiKstar20->SetTextColor(6);
  entBzerotoJPsiKstar20->SetLineColor(6);
  hBzerotoJPsiKstar20->SetMarkerStyle(21);
  entBzerotoJPsiKstar20->SetLineWidth(1);
  hBzerotoJPsiKstar20->SetLineWidth(1);
  entBzerotoJPsiKstar20->SetTextSize(0.085);
  hempty->Draw();
  hBzerotoJPsiKstar20->Draw("esame");
  legendBzerotoJPsiKstar20->Draw();
  canvas->Update();
  
  canvas->cd(5);
  
  TLegend *legendBzerotoJPsiKPi=new TLegend(0.595302,0.6377119,0.25,0.8728814,"");
  legendBzerotoJPsiKPi->SetBorderSize(0);
  legendBzerotoJPsiKPi->SetFillStyle(0);
  legendBzerotoJPsiKPi->SetBorderSize(0);
  legendBzerotoJPsiKPi->SetTextFont(42);
  legendBzerotoJPsiKPi->SetTextSize(0.085);
  

  TLegendEntry *entBzerotoJPsiKPi=legendBzerotoJPsiKPi->AddEntry(hBzerotoJPsiKPi,"B^{0} #rightarrow JPsi+K Pi","P");
  hBzerotoJPsiKPi->SetLineColor(7);
  hBzerotoJPsiKPi->SetMarkerColor(7);
  entBzerotoJPsiKPi->SetTextColor(7);
  entBzerotoJPsiKPi->SetLineColor(7);
  hBzerotoJPsiKPi->SetMarkerStyle(21);
  entBzerotoJPsiKPi->SetLineWidth(1);
  hBzerotoJPsiKPi->SetLineWidth(1);
  entBzerotoJPsiKPi->SetTextSize(0.085);
  hempty->Draw();
  hBzerotoJPsiKPi->Draw("esame");
  legendBzerotoJPsiKPi->Draw();
  canvas->Update();

  canvas->cd(6);
  
  TLegend *legendBplustoJPsiKPi=new TLegend(0.595302,0.6377119,0.25,0.8728814,"");
  legendBplustoJPsiKPi->SetBorderSize(0);
  legendBplustoJPsiKPi->SetFillStyle(0);
  legendBplustoJPsiKPi->SetBorderSize(0);
  legendBplustoJPsiKPi->SetTextFont(42);
  legendBplustoJPsiKPi->SetTextSize(0.085);

  TLegendEntry *entBplustoJPsiKPi=legendBplustoJPsiKPi->AddEntry(hBplustoJPsiKPi,"B^{+} #rightarrow JPsi+K Pi","P");
  hBplustoJPsiKPi->SetLineColor(8);
  hBplustoJPsiKPi->SetMarkerColor(8);
  entBplustoJPsiKPi->SetTextColor(8);
  entBplustoJPsiKPi->SetLineColor(8);
  hBplustoJPsiKPi->SetMarkerStyle(21);
  entBplustoJPsiKPi->SetLineWidth(1);
  hBplustoJPsiKPi->SetLineWidth(1);
  entBplustoJPsiKPi->SetTextSize(0.085);
  hempty->Draw();
  hBplustoJPsiKPi->Draw("esame");
  legendBplustoJPsiKPi->Draw();
  canvas->Update();

  canvas->cd(7);
  
  TLegend *legendBstoJPsiKPi=new TLegend(0.595302,0.6377119,0.25,0.8728814,"");
  legendBstoJPsiKPi->SetBorderSize(0);
  legendBstoJPsiKPi->SetFillStyle(0);
  legendBstoJPsiKPi->SetBorderSize(0);
  legendBstoJPsiKPi->SetTextFont(42);
  legendBstoJPsiKPi->SetTextSize(0.085);
  
  TLegendEntry *entBstoJPsiKPi=legendBstoJPsiKPi->AddEntry(hBstoJPsiTrackTrack,"B_{s} #rightarrow JPsi+Track+Track","P");
  hBstoJPsiTrackTrack->SetLineColor(9);
  hBstoJPsiTrackTrack->SetMarkerColor(9);
  entBstoJPsiKPi->SetTextColor(9);
  entBstoJPsiKPi->SetLineColor(9);
  hBstoJPsiTrackTrack->SetMarkerStyle(21);
  entBstoJPsiKPi->SetLineWidth(1);
  hBstoJPsiTrackTrack->SetLineWidth(1);
  entBstoJPsiKPi->SetTextSize(0.085);
  hBstoJPsiTrackTrack->Draw("esame");
  hempty->Draw();
  hBstoJPsiTrackTrack->Draw("esame");
  legendBstoJPsiKPi->Draw();
  canvas->Update();
  
  canvas->cd(8);
  
  TLegend *legendBzerotoJPsiKstarplusPion=new TLegend(0.595302,0.6377119,0.25,0.8728814,"");
  legendBzerotoJPsiKstarplusPion->SetBorderSize(0);
  legendBzerotoJPsiKstarplusPion->SetFillStyle(0);
  legendBzerotoJPsiKstarplusPion->SetBorderSize(0);
  legendBzerotoJPsiKstarplusPion->SetTextFont(42);
  legendBzerotoJPsiKstarplusPion->SetTextSize(0.085);
  
  TLegendEntry *entBzerotoJPsiKstarplusPion=legendBzerotoJPsiKstarplusPion->AddEntry(hBzerotoJPsiKstarplusPion,"B^{0} #rightarrow JPsi+K*+ Pi","P");
  hBzerotoJPsiKstarplusPion->SetLineColor(9);
  hBzerotoJPsiKstarplusPion->SetMarkerColor(9);
  entBzerotoJPsiKstarplusPion->SetTextColor(9);
  entBzerotoJPsiKstarplusPion->SetLineColor(9);
  hBzerotoJPsiKstarplusPion->SetMarkerStyle(21);
  entBzerotoJPsiKstarplusPion->SetLineWidth(1);
  hBzerotoJPsiKstarplusPion->SetLineWidth(1);
  entBzerotoJPsiKstarplusPion->SetTextSize(0.085);
  hBzerotoJPsiKstarplusPion->Draw("esame");
  hempty->Draw();
  hBzerotoJPsiKstarplusPion->Draw("esame");
  legendBzerotoJPsiKstarplusPion->Draw();
  canvas->Update();
  
  
  canvas->SaveAs("Plots/canvasSummaryAllBzero.png");
  canvas->SaveAs("Plots/canvasSummaryAllBzero.pdf");


}