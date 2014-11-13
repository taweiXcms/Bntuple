#include <TF1.h>
#include <TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TLatex.h>

void fitX()
{

   TFile *inf = new TFile("/data/bmeson/data/nt_20140421_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root");
   TTree *ntmix=(TTree*)inf->Get("ntmix");
   
   TH1D *h = new TH1D("h","",50,3.6,4);
   TCut cutTrk = "";//"trk1PixelHit>=2&&trk1StripHit>=10&&trk1Chi2ndf<5&&trk2PixelHit>=2&&trk2StripHit>=10&&trk2Chi2ndf<5";
   
   TCanvas *c = new TCanvas("c","",750,600);
  
   ntmix->Draw("mass>>h","abs(y)<1.2&&ujvProb>0.3&&mass-3.0969-tktkmass<0.3&&tktkvProb>0.3&&trk1Pt>0.7&&trk2Pt>0.7&&chi2cl>0.3&&ujpt>12"&&cutTrk,"");
   h->Sumw2();
   TF1 *f = new TF1("f","[0]+[1]*x+[2]*x*x+[3]*Gaus(x,[4],[5])+[6]*Gaus(x,[7],[8])");
   f->SetLineColor(4);
   f->SetParameters(-2.5e4,12855,-1620,228,3.686,0.00545,44,3.8725,0.0054);
   h->Fit("f","");
   h->SetXTitle("m(J/#psi#pi^{+}#pi^{-}) [GeV]");
   h->SetYTitle("Entries");
   h->SetStats(0);
   h->SetAxisRange(1,500,"Y");
   TF1 *f2 = new TF1("f2","[0]+[1]*x+[2]*x*x+0*Gaus(x,[4],[5])+0*Gaus(x,[7],[8])");
   f2->SetParameter(0,f->GetParameter(0));
   f2->SetParameter(1,f->GetParameter(1));
   f2->SetParameter(2,f->GetParameter(2));
   TF1 *f3 = new TF1("f3","[3]*Gaus(x,[4],[5])+[6]*Gaus(x,[7],[8])");
   f3->SetParameter(3,f->GetParameter(3));
   f3->SetParameter(4,f->GetParameter(4));
   f3->SetParameter(5,f->GetParameter(5));
   f3->SetParameter(6,f->GetParameter(6));
   f3->SetParameter(7,f->GetParameter(7));
   f3->SetParameter(8,f->GetParameter(8));

   f->SetLineColor(4);
   f2->SetLineColor(4);
   f3->SetRange(3.6,4.0);
   f2->SetRange(3.6,4.0);
   f2->SetLineStyle(2);
   f3->SetLineStyle(2);
   f2->Draw("same");
   f3->SetLineColor(2);
   f3->SetFillStyle(3004);
   f3->SetFillColor(2);
   f3->Draw("same");
   TLatex *l = new TLatex(3.7,391,"#psi(2S)");
   l->Draw();
   TLatex *l2 = new TLatex(3.875,262,"X(3872)");
   l2->Draw();
   TLatex *l3 = new TLatex(3.812,455,"CMS Preliminary");
   l3->Draw();
   TLatex *l4 = new TLatex(3.78,421,"p+Pb #sqrt{s_{NN}}=5.02 TeV");
   l4->Draw();
   
}
