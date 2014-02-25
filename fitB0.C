#include "utilities.h"

void clean0(TH1D *h)
{
   for (int i=1;i<=h->GetNbinsX();i++)
   {
      if (h->GetBinContent(i)==0) h->SetBinError(i,1);
   }
}

TF1 *fit(TTree *nt,TTree *nt2,double ptmin,double ptmax)
{   
   static int count=0;
   count++;
   TCanvas *c= new TCanvas(Form("c%d",count),"",600,600);
   TH1D *h = new TH1D(Form("h%d",count),"",100,4.8,5.8);
   // Fit function
   TF1 *f = new TF1(Form("f%d",count),"[0]*TMath::BreitWigner(x,[1],[2])+[3]+[4]*x+[5]*x*x+[6]*x*x*x");
   nt->Project(Form("h%d",count),"mass",Form("LD>0.075&&abs(y+0.465)<1.93&&pt>%f&&pt<%f",ptmin,ptmax));    // You can change the selection cut here
   nt2->Project(Form("h%d",count),"mass",Form("LD>0.075&&abs(y+0.465)<1.93&&pt>%f&&pt<%f",ptmin,ptmax));    // You can change the selection cut here
   clean0(h);
   h->Draw();

   f->SetParameter(1,5.28);
   f->SetParameter(2,0.03);
   f->SetParameter(0,100);
   f->FixParameter(1,5.279);
   h->Fit(Form("f%d",count),"","",4.8,5.8);
   h->Fit(Form("f%d",count),"L","",4.8,5.8);
   f->ReleaseParameter(1);
   h->Fit(Form("f%d",count),"L","",4.8,5.8);
   h->Fit(Form("f%d",count),"L","",4.8,5.8);
   h->SetMarkerSize(0.8);
   h->SetMarkerStyle(20);
   cout <<h->GetEntries()<<endl;
   cout <<Form("LD>0.08&&pt>%f&&pt<%f",ptmin,ptmax)<<endl;
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
//   c->Write();

   c->SaveAs(Form("BFigure/BMass-%d.C",count));
   c->SaveAs(Form("BFigure/BMass-%d.gif",count));
   c->SaveAs(Form("BFigure/phiMass-%d.eps",count));

   return f;
}

//void fitB(char *infname)
void fitB0()
{
  TFile *inf = new TFile("nt_20140218_PAMuon_HIRun2013_PromptReco_v1.root");
  //TFile *inf = new TFile("/net/hidsk0001/d00/scratch/jwang/nt_data.root");
  //TFile *inf = new TFile("nt_mc.root");
  TTree *nt = (TTree*) inf->Get("ntKstar1");
  TTree *nt2 = (TTree*) inf->Get("ntKstar2");

  TFile *infMC = new TFile("nt_MC_20140219_Kstar.root");
  TTree *ntGen = (TTree*)infMC->Get("ntGen");
  TTree *ntMC = (TTree*)infMC->Get("ntKstar1");
  TTree *ntMC2 = (TTree*)infMC->Get("ntKstar2");

  nt->SetAlias("LD","d0/d0Err*(6.3620309200679024e-03)+chi2ndf*(-3.3028968583503635e-03)+cos(dtheta)*(3.8455903163972559e-04)+abs(trk1Dxy)/trk1D0Err*(5.4963988488223574e-03)+abs(trk2Dxy)/trk2D0Err*(4.8390766628313066e-03)+abs(trk1Dxy-trk2Dxy)/sqrt(trk1D0Err*trk1D0Err+trk2D0Err*trk2D0Err)*(-3.6357387392698215e-03)+abs(tktkmass-0.895)*(-8.1212127436237937e-03)+(-2.9275756650773135e-03)");
  nt2->SetAlias("LD","d0/d0Err*(5.9858061844734268e-03)+chi2ndf*(-2.9723424043930366e-03)+cos(dtheta)*(3.6157812430758781e-04)+abs(trk1Dxy)/trk1D0Err*(4.2077995182416431e-03)+abs(trk2Dxy)/trk2D0Err*(5.0408167101183166e-03)+abs(trk1Dxy-trk2Dxy)/sqrt(trk1D0Err*trk1D0Err+trk2D0Err*trk2D0Err)*(-3.3742778938305284e-03)+abs(tktkmass-0.895)*(-7.7128693253717484e-03)+(-2.6672823771736751e-03)");

  ntMC->SetAlias("LD","d0/d0Err*(6.3620309200679024e-03)+chi2ndf*(-3.3028968583503635e-03)+cos(dtheta)*(3.8455903163972559e-04)+abs(trk1Dxy)/trk1D0Err*(5.4963988488223574e-03)+abs(trk2Dxy)/trk2D0Err*(4.8390766628313066e-03)+abs(trk1Dxy-trk2Dxy)/sqrt(trk1D0Err*trk1D0Err+trk2D0Err*trk2D0Err)*(-3.6357387392698215e-03)+abs(tktkmass-0.895)*(-8.1212127436237937e-03)+(-2.9275756650773135e-03)");
  ntMC2->SetAlias("LD","d0/d0Err*(5.9858061844734268e-03)+chi2ndf*(-2.9723424043930366e-03)+cos(dtheta)*(3.6157812430758781e-04)+abs(trk1Dxy)/trk1D0Err*(4.2077995182416431e-03)+abs(trk2Dxy)/trk2D0Err*(5.0408167101183166e-03)+abs(trk1Dxy-trk2Dxy)/sqrt(trk1D0Err*trk1D0Err+trk2D0Err*trk2D0Err)*(-3.3742778938305284e-03)+abs(tktkmass-0.895)*(-7.7128693253717484e-03)+(-2.6672823771736751e-03)");

//  nt->SetAlias("LD","(4.239e-03*abs(trk1Dxy)/trk1D0Err +chi2ndf*1.168e-03+trk1Chi2ndf*4.045e-04+trk1PixelHit*1.595e-04+trk1StripHit*3.943e-05)");
  //nt->SetAlias("LD","(-2.704e-02-4.649e-03*(d0/d0Err)+5.805e-4*chi2ndf+2.021e-03*abs(trk1Dxy/trk1D0Err)-7.560e-04*trk1PixelHit+1.405e-05*trk1StripHit-2.786e-04*trk1Chi2ndf)");
  
  //   TFile *outf = new TFile("phiHistos.root","recreate");
  //   outf->cd();
  const int nBins = 6;
  double ptBins[nBins+1] = {5,10,15,20,25,30,60};
  TH1D *hPt = new TH1D("hPt","",nBins,ptBins);
  TH1D *hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D *hPtGen = new TH1D("hPtGen","",nBins,ptBins);

  TH1D *hRef = new TH1D("hRef","",nBins,ptBins);
  hRef->SetBinContent(1,2.509091);
  hRef->SetBinContent(2,0.5519121);
  hRef->SetBinContent(3,0.1522497);
  hRef->SetBinContent(4,0.05214935);
  hRef->SetBinContent(5,0.00657091);

  hRef->Scale(208*30000*115*1.028*5.93*1e-5/10.);  

  for (int i=0;i<nBins;i++)
    {
      TF1 *f = fit(nt,nt2,ptBins[i],ptBins[i+1]);
      hPt->SetBinContent(i+1,f->GetParameter(0)*100./(ptBins[i+1]-ptBins[i]));
      hPt->SetBinError(i+1,f->GetParError(0)*100./(ptBins[i+1]-ptBins[i]));
    }  
  
  TCanvas *c=  new TCanvas("cResult","",600,600);
  hPt->SetXTitle("B^{0} p_{T} (GeV/c)");
  hPt->SetYTitle("Uncorrected dN/dp_{T}");
  hPt->Sumw2();
  hPt->Draw();
  

  ntMC->Project("hPtMC","pt","LD>0.08&&abs(y+0.465)<1.93&&gen==22233");
  ntMC2->Project("hPtMC","pt","LD>0.08&&abs(y+0.465)<1.93&&gen==22233");
  ntGen->Project("hPtGen","pt","abs(y+0.465)<1.93&&isSignal!=0");
  
  hPtMC->Sumw2();
  TH1D *hEff = (TH1D*)hPtMC->Clone("hEff");
  hPtMC->Sumw2();
  hEff->Divide(hPtGen);
  
  TH1D *hPtCor = (TH1D*)hPt->Clone("hPtCor");
  hPtCor->Divide(hEff);
  TCanvas *cCor=  new TCanvas("cCorResult","",600,600);
  hPtCor->SetYTitle("Correctd dN/dp_{T}");
  hPtCor->Draw();



  
  //   outf->Write();  
}
