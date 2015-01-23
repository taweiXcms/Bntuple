TString particle="Bplus";
const int nbins=5;
Double_t xbins[nbins]={12.5,17.5,22.5,27.5,45.};
Double_t exl[nbins]={2.5,2.5,2.5,2.5,15.};
Double_t exl0[nbins]={0.,0.,0.,0.,0.};
Double_t yPercSigmapPbSystTotHigh[nbins]={0.163,0.150,0.146,0.142,0.140};
Double_t yPercSigmapPbSystTotLow[nbins]={0.163,0.150,0.146,0.142,0.140};
Double_t commonErrorP = TMath::Sqrt(0.0445*0.0445);
Double_t commonErrorN = TMath::Sqrt(0.0445*0.0445);
Double_t FFsysterror=0.7/40.1;
Double_t tagandprobcorrection[nbins]={1.049,1.030,1.019,1.012,1.006};


void CrossSectionPP(){

  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  
  TFile*filePPReference=new TFile(Form("../../../fonll/output%s_pp.root",particle.Data()));  
  TGraphAsymmErrors*gaeBplusReference=(TGraphAsymmErrors*)filePPReference->Get(Form("gaeSigmaDecay%s",particle.Data()));
  gaeBplusReference->SetName(Form("gae%sReference",particle.Data()));
  
  TFile*filepPb=new TFile(Form("../Results%s_pp/Sigma%s.root",particle.Data(),particle.Data()));
  TH1F*hSigmapPbStat=(TH1F*)filepPb->Get("hPtSigma");  
  TH1F*hPt=(TH1F*)filepPb->Get("hPt");
  TH1F*hEff=(TH1F*)filepPb->Get("hEff");
  
  double scalingfactor=1e-6.;
  
  double yvalue,xvalue,yerrorhigh,yerrorlow;
  
  for (int i=0;i<nbins;i++){
  
    hSigmapPbStat->SetBinContent(i+1,scalingfactor*hSigmapPbStat->GetBinContent(i+1));
    hSigmapPbStat->SetBinError(i+1,scalingfactor*hSigmapPbStat->GetBinError(i+1));
    
    yvalue=-1.;
    xvalue=-1.;
    yerrorhigh=-1.;
    yerrorlow=-1.;
    
    gaeBplusReference->GetPoint(i,xvalue,yvalue);
    yerrorhigh=gaeBplusReference->GetEYhigh()[i];
    yerrorlow=gaeBplusReference->GetEYlow()[i];
  
    gaeBplusReference->SetPoint(i,xvalue,yvalue*scalingfactor/208.);
    gaeBplusReference->SetPointEYhigh(i,yerrorhigh*scalingfactor/208.);
    gaeBplusReference->SetPointEYlow(i,yerrorlow*scalingfactor/208.);

  } 
  
  for (int i=0;i<nbins;i++){
    hSigmapPbStat->SetBinContent(i+1,(1./tagandprobcorrection[i])*hSigmapPbStat->GetBinContent(i+1));
    hSigmapPbStat->SetBinError(i+1,(1./tagandprobcorrection[i])*hSigmapPbStat->GetBinError(i+1));
  
  } 
  Double_t yRefPP[nbins];                        //value y reference
  Double_t xRefPP[nbins];                        //value x reference
  Double_t yPPsystFONLLhigh[nbins];              //y err syst FONLL high
  Double_t yPPsystFONLLlow[nbins];               //y err syst FONLL low
  Double_t yPercPPsystFONLLhigh[nbins];          //y percentuale err syst FONLL high
  Double_t yPercPPsystFONLLlow[nbins];           //y percentuale err syst FONLL low
    
  Double_t ySigmapPb[nbins];                     //value y pPb 
  Double_t xSigmapPb[nbins];                     //value x pPb
  Double_t ySigmapPbStat[nbins];                 //y err stat pPb
  Double_t yPercSigmapPbStat[nbins];             //y err stat pPb
  
  Double_t yFONLL[nbins];                        //1
  Double_t yPPOverFONLL[nbins];                          //value y PPOverFONLL 
  Double_t yPPOverFONLLStat[nbins];                      //y err stat PPOverFONLL 
  Double_t yPPOverFONLLsystFONLLhigh[nbins];             //y err syst FONLL PPOverFONLL high
  Double_t yPPOverFONLLsystFONLLlow[nbins];              //y err syst FONLL PPOverFONLL lzow
  Double_t yPercPPOverFONLLsystFONLLhigh[nbins];         //y percentuale err syst FONLL PPOverFONLL high
  Double_t yPercPPOverFONLLsystFONLLlow[nbins];          //y percentuale err syst FONLL PPOverFONLL low
    
  Double_t ySigmapPbSystTotHigh[nbins];              //y percentuale err syst pPb TOT
  Double_t ySigmapPbSystTotLow[nbins];              //y percentuale err syst pPb TOT

  Double_t yPercRpPbSystTotHigh[nbins];          //y percentuale err syst RpPb TOT
  Double_t yPercRpPbSystTotLow[nbins];          //y percentuale err syst RpPb TOT
  
  Double_t yRpPbSystTotHigh[nbins];              //y percentuale err syst RpPb TOT
  Double_t yRpPbSystTotLow[nbins];              //y percentuale err syst RpPb TOT

  
  double x,y;
  for (Int_t i=0;i<nbins;i++) {
    gaeBplusReference->GetPoint(i,xRefPP[i],yRefPP[i]);
    yPPsystFONLLhigh[i]=gaeBplusReference->GetEYhigh()[i];
    yPPsystFONLLlow[i]=gaeBplusReference->GetEYlow()[i];
    yPercPPsystFONLLhigh[i]=yPPsystFONLLhigh[i]/yRefPP[i];
    yPercPPsystFONLLlow[i]=yPPsystFONLLlow[i]/yRefPP[i];
    yPercPPsystFONLLhigh[i]=TMath::Sqrt(yPercPPsystFONLLhigh[i]*yPercPPsystFONLLhigh[i]+FFsysterror*FFsysterror);
    yPercPPsystFONLLlow[i]=TMath::Sqrt(yPercPPsystFONLLlow[i]*yPercPPsystFONLLlow[i]+FFsysterror*FFsysterror);
    
  }
  
  for(Int_t i=0;i<nbins;i++) {
    ySigmapPb[i]=hSigmapPbStat->GetBinContent(i+1);
    ySigmapPbStat[i]=hSigmapPbStat->GetBinError(i+1);
    yPercSigmapPbStat[i]=ySigmapPbStat[i]/ySigmapPb[i];
    ySigmapPbSystTotHigh[i]=yPercSigmapPbSystTotHigh[i]*ySigmapPb[i];
    ySigmapPbSystTotLow[i]=yPercSigmapPbSystTotLow[i]*ySigmapPb[i];
  }

  for(Int_t i=0;i<nbins;i++) {
    yPPOverFONLL[i]=ySigmapPb[i]/yRefPP[i];
    yPPOverFONLLStat[i]=ySigmapPbStat[i]/yRefPP[i];
    yFONLL[i]=yPPOverFONLL[i];
    yPercPPOverFONLLsystFONLLhigh[i]=(yPercPPsystFONLLlow[i]/(1-yPercPPsystFONLLlow[i]));
    yPercPPOverFONLLsystFONLLlow[i]=(yPercPPsystFONLLhigh[i]/(1+yPercPPsystFONLLhigh[i]));
    yPPOverFONLLsystFONLLhigh[i]=yPercPPOverFONLLsystFONLLhigh[i]*yPPOverFONLL[i];
    yPPOverFONLLsystFONLLlow[i]=yPercPPOverFONLLsystFONLLlow[i]*yPPOverFONLL[i];

    yRpPbSystTotHigh[i]=yPercSigmapPbSystTotHigh[i]*yPPOverFONLL[i];
    yRpPbSystTotLow[i]=yPercSigmapPbSystTotLow[i]*yPPOverFONLL[i];
    //cout<<yRpPbSystTot[i]<<endl;
    
  }

  
  TGraphAsymmErrors *gSigmasyst = new TGraphAsymmErrors(nbins,xbins,ySigmapPb,exl,exl,ySigmapPbSystTotLow,ySigmapPbSystTotHigh);
  gSigmasyst->SetTitle("Sigma syst uncertainty from pPb");
  gSigmasyst->SetMarkerColor(1);
  gSigmasyst->SetLineColor(1);
  gSigmasyst->SetLineWidth(2);   
  gSigmasyst->SetMarkerStyle(21);
  gSigmasyst->SetMarkerColor(1);

  TGraphAsymmErrors *gSigmastat = new TGraphAsymmErrors(nbins,xbins,ySigmapPb,exl,exl,ySigmapPbStat,ySigmapPbStat);
  gSigmastat->SetTitle("Sigma stat uncertainty from pPb");
  gSigmastat->SetMarkerColor(1);
  gSigmastat->SetLineColor(1);
  gSigmastat->SetLineWidth(1);   
  gSigmastat->SetMarkerStyle(21);
  gSigmastat->SetMarkerColor(1);
  
  gSigmastat->SetFillColor(0);
  gSigmastat->SetFillStyle(0);


  TCanvas *canvasSigma=new TCanvas("canvasSigma","canvasSigma",500,500);   
  canvasSigma->cd();
  canvasSigma->Range(-1.989924,-0.2917772,25.49622,2.212202);
  canvasSigma->SetFillColor(0);
  canvasSigma->SetBorderMode(0);
  canvasSigma->SetBorderSize(2);
  canvasSigma->SetLeftMargin(0.1451613);
  canvasSigma->SetRightMargin(0.05443548);
  canvasSigma->SetTopMargin(0.08474576);
  canvasSigma->SetBottomMargin(0.1165254);
  canvasSigma->SetFrameBorderMode(0);
  canvasSigma->SetFrameBorderMode(0);
  canvasSigma->SetLogy();
  
  TH2F* hempty=new TH2F("hempty","",10,0.,70,10.,1e-5,50.);  
  hempty->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  //if(particle=="Bplus") hempty->GetYaxis()->SetTitle("d#sigma / dp_{T} (B^{+}) (pb GeV^{-1}c)");
  //if(particle=="Bzero") hempty->GetYaxis()->SetTitle("d#sigma / dp_{T} (B^{0}) (pb GeV^{-1}c)");
  //if(particle=="Bs") hempty->GetYaxis()->SetTitle("d#sigma / dp_{T} (B_{s}) (pb GeV^{-1}c)");
  
    hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();

  
  hempty->GetYaxis()->SetTitle("d#sigma / dp_{T}( #mub GeV^{-1}c)");
  

  hempty->GetXaxis()->SetTitleOffset(1.);
  hempty->GetYaxis()->SetTitleOffset(1.3);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.04);
  hempty->GetYaxis()->SetLabelSize(0.04);  
  hempty->SetMaximum(2);
  hempty->SetMinimum(0.);
  hempty->Draw();
    
  
  gaeBplusReference->SetMarkerColor(1);
  gaeBplusReference->SetMarkerStyle(21);  
  gaeBplusReference->SetFillColor(5);
  gaeBplusReference->SetFillStyle(1001);
  gaeBplusReference->SetLineColor(1);
  gaeBplusReference->SetLineWidth(5);
  
  
  gSigmastat->SetMarkerColor(1);
  gSigmastat->SetLineColor(1);
  gSigmastat->SetLineWidth(2);   
  gSigmastat->SetMarkerStyle(21);
  gSigmastat->SetMarkerColor(1);

  gaeBplusReference->Draw("2same");
  gSigmastat->SetFillColor(0);
  gSigmastat->Draw("epsame");
  
  

  //coord. for B+ and B0
  //TLegend *legendSigma=new TLegend(0.5745968,0.4756871,0.8729839,0.6490486,"");
  //coord.  B0
  TLegend *legendSigma=new TLegend(0.5100806,0.5868644,0.8084677,0.7605932,"");
  //coord. for B_s
  //TLegend *legendSigma=new TLegend(0.2580645,0.6122881,0.5564516,0.7860169,"");
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);
  
  TBox *c = new TBox(3,1-commonErrorN,7,1+commonErrorP);
  c->SetLineColor(5);
  c->SetFillColor(5);
  c->Draw();

  
  //TLegendEntry *ent_Sigmapp=legendSigma->AddEntry(gaeBplusReference,"pp reference","PLF");
  
  TLegendEntry *ent_SigmapPb=legendSigma->AddEntry(gSigmastat,"pPb","pf");
  ent_SigmapPb->SetTextFont(42);
  ent_SigmapPb->SetLineColor(1);
  //ent_SigmapPb->SetFillColor(0);
  ent_SigmapPb->SetMarkerColor(1);
  
  //TLegendEntry *ent_SigmapPbSyst=legendSigma->AddEntry(gSigmasyst,"pPb","f");
  //ent_SigmapPbSyst->SetTextFont(42);
  //ent_SigmapPbSyst->SetLineColor(1);
  //ent_SigmapPbSyst->SetMarkerColor(1);
  
  TLegendEntry *ent_Sigmapp=legendSigma->AddEntry(c,"FONLL pp ref.","f");
  ent_Sigmapp->SetTextFont(42);
  ent_Sigmapp->SetLineColor(5);
  ent_Sigmapp->SetMarkerColor(1);

  legendSigma->Draw("same");



  

  
  
  gSigmasyst->SetFillColor(0);
  gSigmasyst->SetFillStyle(0);
  
  //hSigmapPbStat->Draw("same");
  gSigmasyst->SetFillColor(0);
  gSigmasyst->SetFillStyle(0);
  gSigmasyst->Draw("2same");
  
  
  

  TBox *d = new TBox(3,1-commonErrorN,7,1+commonErrorP);
  d->SetLineColor(1);
  d->SetFillColor(0);
  d->Draw();


    
  TLatex * tlatex1=new TLatex(0.1612903,0.8625793,"CMS Preliminary     pp #sqrt{s_{NN}}= 2.76 TeV");
  tlatex1->SetNDC();
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.045);
  tlatex1->Draw();
  

  TString mypar;
  if(particle=="Bplus") mypar="B^{+}";
  if(particle=="Bzero") mypar="B^{0}";
  if(particle=="Bs") mypar="B_{s}";
  
  
  TLatex * tlatexlumi=new TLatex(0.671371,0.7801268,"L = 5.4 pb^{-1}");
  tlatexlumi->SetNDC();
  tlatexlumi->SetTextColor(1);
  tlatexlumi->SetTextFont(42);
  tlatexlumi->SetTextSize(0.045);
  tlatexlumi->Draw();

 double xpos=0.8528226;
 double ypos=0.6849894;
  
  TLatex * tlatex3=new TLatex(xpos,ypos,mypar.Data());
   tlatex3->SetNDC();
  tlatex3->SetTextColor(1);
  tlatex3->SetTextFont(42);
  tlatex3->SetTextSize(0.06);
  tlatex3->Draw();
  

  canvasSigma->SaveAs(Form("../Results%s_pp/canvasSigma%s.pdf",particle.Data(),particle.Data()));  

  TGraphAsymmErrors *gPPOverFONLLstat = new TGraphAsymmErrors(nbins,xbins,yPPOverFONLL,exl0,exl0,yPPOverFONLLStat,yPPOverFONLLStat);
  gPPOverFONLLstat->SetTitle("PPOverFONLL stat uncertainty from pPb");
  gPPOverFONLLstat->SetMarkerColor(1);
  gPPOverFONLLstat->SetLineColor(1);
  gPPOverFONLLstat->SetLineWidth(2);   
  gPPOverFONLLstat->SetMarkerStyle(21);
  gPPOverFONLLstat->SetMarkerColor(1);
  
  TGraphAsymmErrors *gPPOverFONLLsyst = new TGraphAsymmErrors(nbins,xbins,yPPOverFONLL,exl,exl,yRpPbSystTotLow,yRpPbSystTotHigh);
  gPPOverFONLLsyst->SetTitle("PPOverFONLL syst uncertainty from pPb");
  gPPOverFONLLsyst->SetMarkerColor(1);
  gPPOverFONLLsyst->SetLineColor(1);
  gPPOverFONLLsyst->SetLineWidth(2);   
  gPPOverFONLLsyst->SetMarkerStyle(21);
  gPPOverFONLLsyst->SetMarkerColor(1);

   
  TGraphAsymmErrors *gPPOverFONLLsystFONLL = new TGraphAsymmErrors(nbins,xbins,yFONLL,exl,exl,yPPOverFONLLsystFONLLlow,yPPOverFONLLsystFONLLhigh);
  gPPOverFONLLsystFONLL->SetTitle("PPOverFONLL syst uncertainty from FONLL reference");
  gPPOverFONLLsystFONLL->SetMarkerColor(2);
  gPPOverFONLLsystFONLL->SetLineColor(2);
  gPPOverFONLLsystFONLL->SetLineWidth(2); 
  gPPOverFONLLsystFONLL->SetMarkerStyle(21);
  gPPOverFONLLsystFONLL->SetMarkerColor(2);

  TCanvas *canvasPPOverFONLL=new TCanvas("canvasPPOverFONLL","canvasPPOverFONLL",500,500);   
  
  

  canvasPPOverFONLL->Range(-1.989924,-0.2917772,25.49622,2.212202);
  canvasPPOverFONLL->SetFillColor(0);
  canvasPPOverFONLL->SetBorderMode(0);
  canvasPPOverFONLL->SetBorderSize(2);
  canvasPPOverFONLL->SetLeftMargin(0.1451613);
  canvasPPOverFONLL->SetRightMargin(0.05443548);
  canvasPPOverFONLL->SetTopMargin(0.08474576);
  canvasPPOverFONLL->SetBottomMargin(0.1165254);
  canvasPPOverFONLL->SetFrameBorderMode(0);
  canvasPPOverFONLL->SetFrameBorderMode(0);
  
  TLegend *legendPPOverFONLL=new TLegend(0.1975806,0.6109937,0.4959677,0.8012685,"");
  legendPPOverFONLL->SetBorderSize(0);
  legendPPOverFONLL->SetLineColor(0);
  legendPPOverFONLL->SetFillColor(0);
  legendPPOverFONLL->SetFillStyle(1001);
  legendPPOverFONLL->SetTextFont(42);
  legendPPOverFONLL->SetTextSize(0.045);

  TH2F* hempty=new TH2F("hempty","",10,0.,70,10.,0.,2.5);  
  
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  
  hempty->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hempty->GetYaxis()->SetTitle("pp measurement/FONLL");
  
  hempty->GetXaxis()->SetTitleOffset(1.1);
  hempty->GetYaxis()->SetTitleOffset(1.1);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.045);
  hempty->GetYaxis()->SetLabelSize(0.045);  
  hempty->SetMaximum(2);
  hempty->SetMinimum(0.);
  hempty->Draw();
  
  TLine *l = new TLine(0,1,70,1);
  l->SetLineStyle(2);
  
  legendPPOverFONLL->Draw();
  gPPOverFONLLstat->SetMarkerStyle(21);
  gPPOverFONLLstat->SetLineColor(1);
  gPPOverFONLLstat->SetMarkerColor(1);

  gPPOverFONLLsystFONLL->SetLineStyle(3);
  gPPOverFONLLsystFONLL->SetLineWidth(3);
  gPPOverFONLLsystFONLL->SetFillColor(5);
  gPPOverFONLLsystFONLL->SetLineColor(5);//kAzure-3);
  gPPOverFONLLsystFONLL->SetMarkerColor(5);//kAzure-3);
  gPPOverFONLLsystFONLL->Draw("2same");
  gPPOverFONLLstat->Draw("psame");
  gPPOverFONLLsyst->SetFillColor(0);
  gPPOverFONLLsyst->SetFillStyle(0);
  
  gPPOverFONLLstat->SetFillColor(0);
  gPPOverFONLLstat->SetFillStyle(0);
  gPPOverFONLLsyst->Draw("2same");
  
  TBox *a = new TBox(3,1-commonErrorN,7,1+commonErrorP);
  a->SetLineColor(1);
  a->SetFillColor(0);
  a->Draw();


  TBox *b = new TBox(3,1-commonErrorN,7,1+commonErrorP);
  b->SetLineColor(1);
  b->SetFillColor(kGray);
  b->Draw();


  TLegendEntry *ent_PPOverFONLLstat=legendPPOverFONLL->AddEntry(gPPOverFONLLstat,"pp measurement/data","pf");
  ent_PPOverFONLLstat->SetTextFont(42);
  ent_PPOverFONLLstat->SetLineColor(2);
  ent_PPOverFONLLstat->SetMarkerColor(2);
  //TLegendEntry *ent_PPOverFONLLsystData=legendPPOverFONLL->AddEntry(gPPOverFONLLsyst,"            syst. unc.","f");
  //ent_PPOverFONLLsystData->SetTextFont(42);
  //ent_PPOverFONLLsystData->SetLineColor(1);
  //ent_PPOverFONLLsystData->SetMarkerColor(1);
  TLegendEntry *ent_PPOverFONLLsystData=legendPPOverFONLL->AddEntry(b,"Syst. L+BR","f");
  ent_PPOverFONLLsystData->SetTextFont(42);
  ent_PPOverFONLLsystData->SetLineColor(2);
  ent_PPOverFONLLsystData->SetMarkerColor(2);


  
  TLegendEntry *ent_PPOverFONLLsystFONLL=legendPPOverFONLL->AddEntry(gPPOverFONLLsystFONLL,"Syst. err. from FONLL pp ref.","f");
  ent_PPOverFONLLsystFONLL->SetTextFont(42);
  ent_PPOverFONLLsystFONLL->SetLineColor(5);
  ent_PPOverFONLLsystFONLL->SetLineStyle(1);
  ent_PPOverFONLLsystFONLL->SetMarkerColor(5);
  
  legendPPOverFONLL->Draw();
  
  TLatex * tlatex1=new TLatex(0.1612903,0.8625793,"     pp #sqrt{s_{NN}}= 2.76 TeV");
  tlatex1->SetNDC();
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.045);
  tlatex1->Draw();
  
    TLatex * tlatex2=new TLatex(0.671371,0.7801268,"L = 5.4 pb^{-1}");
  tlatex2->SetNDC();
  tlatex2->SetTextColor(1);
  tlatex2->SetTextFont(42);
  tlatex2->SetTextSize(0.045);
  tlatex2->Draw();
  
  tlatex3->Draw();

//  l->Draw();  
  canvasPPOverFONLL->SaveAs(Form("../Results%s_pp/canvasPPOverFONLL%s.pdf",particle.Data(),particle.Data()));  


}