#include "utilities.h"

double luminosity=34*1e-3;
double setparam0=100.;
double setparam1=5.28;
double setparam2=0.03;
double fixparam1=5.279;

TString inputdata="../InputsFits/nt_20140218_PAMuon_HIRun2013_PromptReco_v1.root";
TString inputmc="../InputsFits/nt_mc_Kp.root";

TString cut="chi2cl>0.0104&&(d0)/d0Err>3.37&&dtheta<2.98&&TMath::Abs((trk1Dxy)/trk1D0Err)>2.42";

TString seldata=Form("abs(y+0.465)<1.93&&%s",cut.Data());
TString selmc=Form("abs(y+0.465)<1.93&&gen==22233&&%s",cut.Data());
TString selmcgen="abs(y+0.465)<1.93&&abs(pdgId)==521&&isSignal==1";

void clean0(TH1D *h){
  for (int i=1;i<=h->GetNbinsX();i++){
    if (h->GetBinContent(i)==0) h->SetBinError(i,1);
  }
}

TF1 *fit(TTree *nt,double ptmin,double ptmax){   
   //cout<<cut.Data()<<endl;
   static int count=0;
   count++;
   TCanvas *c= new TCanvas(Form("c%d",count),"",600,600);
   TH1D *h = new TH1D(Form("h%d",count),"",100,4.8,5.8);
   // Fit function
   TF1 *f = new TF1(Form("f%d",count),"[0]*TMath::BreitWigner(x,[1],[2])+[3]+[4]*x+[5]*x*x+[6]*x*x*x");
   nt->Project(Form("h%d",count),"mass",Form("%s&&pt>%f&&pt<%f",seldata.Data(),ptmin,ptmax));   
   clean0(h);
   h->Draw();
   
   f->SetParameter(0,setparam0);
   f->SetParameter(1,setparam1);
   f->SetParameter(2,setparam2);
   f->FixParameter(1,fixparam1);
   h->GetEntries();
   h->Fit(Form("f%d",count),"","",4.8,5.8);
   h->Fit(Form("f%d",count),"L","",4.8,5.8);
   f->ReleaseParameter(1);
   h->Fit(Form("f%d",count),"L","",4.8,5.8);
   h->Fit(Form("f%d",count),"LL","",4.8,5.8);
   h->SetMarkerSize(0.8);
   h->SetMarkerStyle(20);
   cout <<h->GetEntries()<<endl;

   // function for background shape plotting. take the fit result from f
   TF1 *background = new TF1(Form("background%d",count),"[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x");
   background->SetParameter(0,f->GetParameter(3));
   background->SetParameter(1,f->GetParameter(4));
   background->SetParameter(2,f->GetParameter(5));
   background->SetParameter(3,f->GetParameter(6));
   background->SetParameter(4,f->GetParameter(7));
   background->SetLineColor(4);
   background->SetRange(4.8,5.8);
   background->SetLineStyle(2);
   
   // function for signal shape plotting. take the fit result from f
   TF1 *mass = new TF1(Form("fmass",count),"[0]*TMath::BreitWigner(x,[1],[2])");
   mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2));
   mass->SetParError(0,f->GetParError(0));
   mass->SetParError(1,f->GetParError(1));
   mass->SetParError(2,f->GetParError(2));
   mass->SetLineColor(2);
   mass->SetLineStyle(2);

//   cout <<mass->Integral(0,1.2)<<" "<<mass->IntegralError(0,1.2)<<endl;
   h->SetMarkerStyle(24);
   h->SetStats(0);
   h->Draw("e");
   h->SetXTitle("M_{KK} (GeV/c^{2})");
   h->SetYTitle("Entries / (1 MeV/c^{2})");
   h->GetXaxis()->CenterTitle();
   h->GetYaxis()->CenterTitle();
   h->SetTitleOffset(1.65,"Y");
   h->SetAxisRange(0,h->GetMaximum()*1.2,"Y");
   background->Draw("same");   
   mass->SetRange(4.8,5.8);
   mass->Draw("same");
   mass->SetLineStyle(2);
   mass->SetFillStyle(3004);
   mass->SetFillColor(2);
   f->Draw("same");

   // Draw the legend:)   
   TLegend *leg = myLegend(0.50,0.78,0.86,0.92);
   leg->AddEntry(h,"CMS Preliminary","");
   leg->AddEntry(h,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","pl");
   leg->Draw();
   TLegend *leg2 = myLegend(0.44,0.23,0.89,0.40);
   leg2->AddEntry(h,"B meson","");
   leg2->AddEntry(h,Form("M_{B}=%.2f #pm %.2f MeV/c^{2}",f->GetParameter(1)*1000.,f->GetParError(1)*1000.),"");
   leg2->AddEntry(h,Form("N_{B}=%.0f #pm %.0f",f->GetParameter(0)*100.,f->GetParError(0)*100.),"");
   leg2->Draw();

   c->SaveAs(Form("ResultsBplus/BMass-%d.C",count));
   c->SaveAs(Form("ResultsBplus/BMass-%d.gif",count));
   c->SaveAs(Form("ResultsBplus/phiMass-%d.eps",count));

   return f;
}

void fitB(){

  TFile *inf = new TFile(inputdata.Data());
  TTree *nt = (TTree*) inf->Get("ntKp");

  TFile *infMC = new TFile(inputmc.Data());
  TTree *ntGen = (TTree*)infMC->Get("ntGen");
  TTree *ntMC = (TTree*)infMC->Get("ntKp");
    
  const int nBins = 6;
  double ptBins[nBins+1] = {5,10,15,20,25,30,60};
  TH1D *hPt = new TH1D("hPt","",nBins,ptBins);
  TH1D *hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D *hPtGen = new TH1D("hPtGen","",nBins,ptBins);

  for (int i=0;i<nBins;i++)
    {
      TF1 *f = fit(nt,ptBins[i],ptBins[i+1]);
      hPt->SetBinContent(i+1,f->GetParameter(0)*100./(ptBins[i+1]-ptBins[i]));
      hPt->SetBinError(i+1,f->GetParError(0)*100./(ptBins[i+1]-ptBins[i]));
    }  
  
  TCanvas *c=  new TCanvas("cResult","",600,600);
  hPt->SetXTitle("B^{+} p_{T} (GeV/c)");
  hPt->SetYTitle("Uncorrected B^{+} dN/dp_{T}");
  hPt->Sumw2();
  hPt->Draw();
  
  ntMC->Project("hPtMC","pt",selmc.Data());
  ntGen->Project("hPtGen","pt",selmcgen.Data());
  
  hPtMC->Sumw2();
  TH1D *hEff = (TH1D*)hPtMC->Clone("hEff");
  hPtMC->Sumw2();
  hEff->Divide(hPtGen);
  
  TH1D *hPtCor = (TH1D*)hPt->Clone("hPtCor");
  hPtCor->Divide(hEff);
  TCanvas *cCor=  new TCanvas("cCorResult","",600,600);
  hPtCor->SetYTitle("Corrected B^{+} dN/dp_{T}");
  hPtCor->Draw();

  TH1D *hPtSigma= (TH1D*)hPtCor->Clone("hPtSigma");
  hPtSigma->Scale(1./(2*luminosity));
  hPtSigma->SetYTitle("d#sigma (B^{+})/dp_{T}");

  TCanvas *cSigma=  new TCanvas("cSigma","",600,600);

  hPtSigma->Draw();
  
  TFile *outf = new TFile("ResultsBplus/SigmaBplus.root","recreate");
  outf->cd();
  hPt->Write();
  hEff->Write();
  hPtCor->Write();
  hPtSigma->Write();
  outf->Close();
  delete outf;
}
