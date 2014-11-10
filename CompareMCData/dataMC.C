#include <TTree.h>
#include <TH1D.h>
#include <TFile.h>
#include <TString.h>
#include <TCut.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TLegend.h>

//svmit2
//TString inputdata="/data/bmeson/data/nt_20140411_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root";
//TString inputmc="/data/bmeson/MC/nt_BoostedMC_20140411_Kp_TriggerMatchingMuon_EvtBase_skim.root";
//cgate
TString inputdata="/export/d00/scratch/jwang/nt_20140418_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root";
TString inputmc="/export/d00/scratch/jwang/nt_BoostedMC_20140418_Kp_TriggerMatchingMuon_EvtBase_skim.root";

//tk pt, chi2
//TString cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&& isbestchi2&&trk1Pt>0.9&&chi2cl>1.32e-02&&(d0/d0Err)>3.41&&cos(dtheta)>-3.46e01";
TString cut="(HLT_PAMu3_v1)&&abs(mumumass-3.096916)<0.15&&mass>5&&mass<6&&trk1Pt>0.9";
  
TString seldata=Form("abs(y+0.465)<1.93&&%s",cut.Data());
TString seldata_2y=Form("((Run<=1&&abs(y+0.465)<1.93)||(Run>=210498&&Run<=211256&&abs(y+0.465)<1.93)||(Run>=211313&&Run<=211631&&abs(y-0.465)<1.93))&&%s",cut.Data());
TString selmc=Form("abs(y+0.465)<1.93&&gen==23333&&%s",cut.Data());
TString selmcgen="abs(y+0.465)<1.93&&abs(pdgId)==521&&isSignal==1";

TString weight = "(27.493+pt*(-0.218769))";

TCut massCut="abs(mass-5.279)<0.04";

double norm(TH1D* h,double low,double high)
{
    TF1 *f = new TF1("f","[0]+[1]*x");
    h->Fit("f","L","",5.4,6);
    double val = f->Integral(low,high);
    delete f;
    return val;
}

void dataMC(char * var="d0/d0Err",char *title="d0/#sigma(d0)",char *fileTitle="d0d0err",int nBin=20,double BinL=0,double BinH=200,bool
logy=1)
{
//abs(mass-5.279)<0.04&&

    TFile *infData = new TFile("/export/d00/scratch/jwang/nt_20140427_PAMuon_HIRun2013_PromptrecoAndRereco_v1_MuonMatching_EvtBase_skim.root");
    TTree *tData = (TTree*) infData->Get("ntKp");

    TFile *infMC = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140427_Hijing_PPb502_MinimumBias_HIJINGemb_inclBtoPsiMuMu_5TeV.root");///data/bmeson/MC/nt_BoostedMC_20140412_Kp_TriggerMatchingMuon_CandBase_skim.root");
    TTree *tMC = (TTree*) infMC->Get("ntKp");
 
//    TFile *infP = new TFile("/data/bmeson/MC/nt_BoostedMC_20140404_Hijing_PPb502_MinimumBias_HIJINGemb_JPsiWithFSR_5TeV_skim.root");
    TFile *infP = new TFile("/export/d00/scratch/jwang/nt_BoostedMC_20140427_Hijing_PPb502_MinimumBias_HIJINGemb_JPsiWithFSR_5TeV.root");

    TTree *tP = (TTree*) infP->Get("ntKp");

    TH1D *hData = new TH1D("hData","",nBin,BinL,BinH );
    TH1D *hMC = new TH1D("hMC","",nBin,BinL,BinH);
    TH1D *hMCBck = new TH1D("hMCBck","",nBin,BinL,BinH);
    TH1D *hP = new TH1D("hP","",nBin,BinL,BinH);

    TH1D *hDataMass = new TH1D("hDataMass","",50,5,6 );
    TH1D *hMCMass = new TH1D("hMCMass","",50,5,6);
    TH1D *hPMass = new TH1D("hPMass","",50,5,6);

    TCanvas *c = new TCanvas("c","",600,600);
    if (logy) c->SetLogy();
//    tData->Draw("mass>>hDataMass",seldata_2y);    
//    tP->Draw("mass>>hPMass",seldata_2y);    
    
    double normMC = 583./3544.;  // based on # of B+ candidate
    
    tData->Draw(Form("%s>>hData",var),seldata_2y && massCut);    
//    tMC->Draw("d0/d0Err>>hMC",seldata_2y && massCut && TCut("gen==23333"));    
    tMC->Draw(Form("%s>>hMC",var),(seldata_2y && massCut));    
    tMC->Draw(Form("%s>>hMCBck",var),(seldata_2y && massCut && TCut("gen!=23333")));    
    tP->Draw(Form("%s>>hP",var),(seldata_2y));    
    hData->Sumw2();

//TCut("(1.88912-0.0761755*pt+0.00111135*pt*pt)*(0.9+0.4358*(y+0.465)+0.1339*(y+0.465)**2-0.243*(y+0.465)**3)")*
    double normP =  0;
    if (hP->GetEntries()!=0) normP=(hData->GetEntries()-hMC->GetEntries()*normMC)/hP->GetEntries();   // prompt
    hMC->Sumw2();
    hMCBck->Sumw2();
    hP->Sumw2();
    hMC->SetMarkerStyle(0);
    hMCBck->SetMarkerStyle(0);
    hP->SetMarkerStyle(0);
    hMC->Scale(normMC); 
    hMCBck->Scale(normMC); 
    hP->Scale(normP);       
    hMC->Add(hP);
    hMCBck->Add(hP);
    
    hData->Draw();
    hMC->SetLineColor(2);
    hP->SetLineColor(4);
    hMCBck->SetLineColor(kGreen+1);
    hMC->SetFillStyle(3325);
    hMCBck->SetFillStyle(3325);
    hP->SetFillStyle(3325);
    hMC->SetFillColor(2);
    hMCBck->SetFillColor(kGreen+1);
    hP->SetFillColor(4);
    hMC->Draw("same hist e");
    hMCBck->Draw("same hist e");
    hP->Draw("same hist e");
    hData->SetYTitle("Entries");
    hData->SetXTitle(title);
    
    TLegend *leg = new TLegend(0.5,0.7,0.9,0.9);
    leg->AddEntry(hData,"pPb data","pl");
    leg->AddEntry(hMC,"B^{+} signal","f");
    leg->AddEntry(hMCBck,"Non-prompt J/#psi","f");
    leg->AddEntry(hP,"Prompt J/#psi","f");
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->Draw();

    c->SaveAs(Form("figure/DataMC-%s.pdf",fileTitle));
    c->SaveAs(Form("figure/DataMC-%s.C",fileTitle));
    TFile*fout=new TFile(Form("figure/DataMC-%s.root",fileTitle),"recreate");
    fout->cd();
    hData->Write();
    hMC->Write();
    hP->Write();
    hMCBck->Write();
    fout->Close();
    delete fout;
    
}

/*
.x dataMC.C+("d0/d0Err","d0/#sigma(d0)","d0D0err",40,0,200,1)
.x dataMC.C+("chi2cl","Vertex #chi^{2} Probability","ProbChi2",20,0,1)
.x dataMC.C+("cos(dtheta)","cos(#Delta#theta)","cosdtheta",20,-1,1)
.x dataMC.C+("abs(trk1Dxy/trk1D0Err)","|trk1Dxy/trk1D0Err|","trk1DxyDerr",40,0,200,1)
*/
