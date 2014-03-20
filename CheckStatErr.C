#include "utilities.h"
#include "TRandom.h"

double luminosity=34.8*1e-3;
double setparam0=100.;
double setparam1=5.28;
double setparam2=0.03;
double fixparam1=5.279;
double setparam3=0.03;
double fixparam2=0.04;

TString inputmc="/mnt/hadoop/cms/store/user/jwang/nt_BoostedMC_20140318_Kstar_TriggerMatchingMuon.root";
TString cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&chi2cl>0.15&&(d0)/d0Err>8.1&&cos(dtheta)>-0.44&&TMath::Abs((trk1Dxy)/trk1D0Err)>0.81&&abs(tktkmass-0.89591)<0.14&&mass>5&&mass<6";
TString seldata=Form("abs(y+0.465)<1.93&&%s",cut.Data());

void clean0(TH1D *h)
{
  for (int i=1;i<=h->GetNbinsX();i++)
    {
      if (h->GetBinContent(i)==0) h->SetBinError(i,1);
    }
}

void Clean0(TH1D *h)
{
  for (int i=1;i<=h->GetNbinsX();i++)
    {
      h->SetBinContent(i,0);
    }
}


TF1 *fit(TH1D* h, TTree *ntMC, TTree *ntMC2,double ptmin,double ptmax)
{   

  static int count=0;
  count++;

  TCanvas *c= new TCanvas(Form("c%d",count),"",600,600);
  TH1D *hMC = new TH1D(Form("hMC%d",count),"",50,5,6);

  // Fit function
  TF1 *f = new TF1(Form("f%d",count),"[0]*([7]*Gaus(x,[1],[2])+(1-[7])*Gaus(x,[1],[8]))+[3]+[4]*x+[6]*(38.42*Gaus(x,5.25,0.03473)+15.04*Gaus(x,5.25,0.1121)+104.3*Gaus(x,5.026,0.0935))");

  ntMC->Project(Form("hMC%d",count),"mass",Form("%s&&pt>%f&&pt<%f",seldata.Data(),ptmin,ptmax));   
  ntMC2->Project(Form("hMC%d",count),"mass",Form("%s&&pt>%f&&pt<%f",seldata.Data(),ptmin,ptmax));   

  clean0(h);
  h->Draw();
  f->SetParLimits(4,-1000,0);
  f->SetParLimits(2,0.01,0.05);
  f->SetParLimits(8,0.01,0.1);
  f->SetParLimits(7,0,1);
  f->SetParameter(0,setparam0);
  f->SetParameter(1,setparam1);
  f->SetParameter(2,setparam2);
  f->SetParameter(8,setparam3);
  f->FixParameter(1,fixparam1);
  h->GetEntries();

  hMC->Fit(Form("f%d",count),"q","",5,6);
  hMC->Fit(Form("f%d",count),"q","",5,6);
  f->ReleaseParameter(1);
  hMC->Fit(Form("f%d",count),"L q","",5,6);
  hMC->Fit(Form("f%d",count),"L q","",5,6);
  hMC->Fit(Form("f%d",count),"L q","",5,6);
  hMC->Fit(Form("f%d",count),"L m","",5,6);

  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(7,f->GetParameter(7));
  f->FixParameter(8,f->GetParameter(8));
   
  h->Fit(Form("f%d",count),"q","",5,6);
  h->Fit(Form("f%d",count),"q","",5,6);
  f->ReleaseParameter(1);
  h->Fit(Form("f%d",count),"L q","",5,6);
  h->Fit(Form("f%d",count),"L q","",5,6);
  h->Fit(Form("f%d",count),"L q","",5,6);
  h->Fit(Form("f%d",count),"L m","",5,6);
  h->SetMarkerSize(0.8);
  h->SetMarkerStyle(20);
  cout <<h->GetEntries()<<endl;


  // function for background shape plotting. take the fit result from f
  TF1 *background = new TF1(Form("background%d",count),"[0]+[1]*x+[3]*(38.42*Gaus(x,5.25,0.03473)+15.04*Gaus(x,5.25,0.1121)+104.3*Gaus(x,5.026,0.0935))");
  //   TF1 *background = new TF1(Form("background%d",count),"[0]+[1]*x+[2]*(1.24e2*Gaus(x,5.107,0.02987)+1.886e2*Gaus(x,5.0116,5.546e-2))");
  background->SetParameter(0,f->GetParameter(3));
  background->SetParameter(1,f->GetParameter(4));
  background->SetParameter(2,f->GetParameter(5));
  background->SetParameter(3,f->GetParameter(6));
  background->SetLineColor(4);
  background->SetRange(5,6);
  background->SetLineStyle(2);
   
  // function for signal shape plotting. take the fit result from f
  TF1 *Bkpi = new TF1(Form("fBkpi",count),"[0]*(38.42*Gaus(x,5.25,0.03473)+15.04*Gaus(x,5.25,0.1121)+104.3*Gaus(x,5.026,0.0935))");
  Bkpi->SetParameter(0,f->GetParameter(6));
  Bkpi->SetLineColor(kGreen+1);
  Bkpi->SetFillColor(kGreen+1);
  Bkpi->SetRange(5.00,5.45);
  Bkpi->SetLineStyle(1);
  Bkpi->SetFillStyle(3005);

  // function for signal shape plotting. take the fit result from f
  TF1 *mass = new TF1(Form("fmass",count),"[0]*([3]*Gaus(x,[1],[2])+(1-[3])*Gaus(x,[1],[4]))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(8));
  mass->SetParError(0,f->GetParError(0));
  mass->SetParError(1,f->GetParError(1));
  mass->SetParError(2,f->GetParError(2));
  mass->SetParError(7,f->GetParError(7));
  mass->SetParError(8,f->GetParError(8));
  mass->SetLineColor(2);
  mass->SetLineStyle(2);

  //   cout <<mass->Integral(0,1.2)<<" "<<mass->IntegralError(0,1.2)<<endl;
  h->SetMarkerStyle(24);
  h->SetStats(0);
  h->Draw("e");
  h->SetXTitle("M_{B} (GeV/c^{2})");
  h->SetYTitle("Entries / (20 MeV/c^{2})");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->SetTitleOffset(1.4,"Y");
  h->SetAxisRange(0,h->GetMaximum()*1.2,"Y");

  //  hBck->Draw("hist same");
  
  Bkpi->Draw("same");
  background->Draw("same");   
  mass->SetRange(5,6);
  mass->Draw("same");
  mass->SetLineStyle(2);
  mass->SetFillStyle(3004);
  mass->SetFillColor(2);
  f->Draw("same");
  
  cout <<"fit result:"<<f->GetParameter(0)*2.5<<" "<<f->Integral(5,6)/h->GetBinWidth(1)<<endl;

  double yield = mass->Integral(5,6)/0.02;
  double yieldErr = mass->Integral(5,6)/0.02*mass->GetParError(0)/mass->GetParameter(0);

  // Draw the legend:)   
  TLegend *leg = myLegend(0.50,0.5,0.86,0.92);
  leg->AddEntry(h,"CMS Preliminary","");
  leg->AddEntry(h,"p+Pb #sqrt{s_{NN}}= 5.02 TeV","");
  leg->AddEntry(h,Form("%.0f<p_{T}^{B}<%.0f GeV/c",ptmin,ptmax),"");
  leg->AddEntry(h,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"Signal","f");
  leg->AddEntry(background,"Combinatorial Background","l");
  leg->AddEntry(Bkpi,"Non-prompt J/#psi","f");
  leg->Draw();
  TLegend *leg2 = myLegend(0.44,0.33,0.89,0.50);
  leg2->AddEntry(h,"B meson","");
  leg2->AddEntry(h,Form("M_{B}=%.2f #pm %.2f MeV/c^{2}",f->GetParameter(1)*1000.,f->GetParError(1)*1000.),"");
  leg2->AddEntry(h,Form("N_{B}=%.0f #pm %.0f",yield,yieldErr),"");
  leg2->Draw();


  //c->SaveAs(Form("ResultsCheckStatErr/BMass-%d.C",count));
  c->SaveAs(Form("ResultsCheckStatErr/BMass-%d.gif",count));
  //c->SaveAs(Form("ResultsBzero/BMass-%d.eps",count));

  return mass;
}


void CheckStatErr(){

  TFile*finput=new TFile("fileFitfunctionData.root");
  TF1*fbackground=(TF1*)finput->Get("fbackground1");//
  TF1*fsignal=(TF1*)finput->Get("fmass1");//

  fbackground->SetName("fbackground");
  fsignal->SetName("fsignal");

  TFile *infMC = new TFile(inputmc.Data());
  TTree *ntMC = (TTree*)infMC->Get("ntKstar1");
  TTree *ntMC2 = (TTree*)infMC->Get("ntKstar2");



  int i,j;
  int nexp=100;

  const int nBins = 3;
  double ptBins[nBins+1] = {10,15,20,60};

  TH1D *hyield = new TH1D("hyield","",30,450,550);

  for(j=0;j<nexp;j++)
    {
      if(j%10==0) cout<<j<<" / "<<nexp<<endl;
      TH1D *hMass = new TH1D("hMass","",50,5,6);
      for (i=0;i<500;i++)
	{
	  double sgn=fsignal->GetRandom();
	  double bkg=fbackground->GetRandom();

	  hMass->Fill(sgn);
	  hMass->Fill(bkg);
	}
      i=0;//first pt bin
      //hMass->Draw();
      TF1 *f = fit(hMass,ntMC,ntMC2,ptBins[i],ptBins[i+1]);
      double yield = f->Integral(5,6)/0.02;
      hyield->Fill(yield);
    }
  TCanvas *c2= new TCanvas("c2","",600,600);
  hyield->Draw();
  c2->SaveAs("ResultsCheckStatErr/YieldDistribution.gif");
}

