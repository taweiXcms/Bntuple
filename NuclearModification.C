/*
  TString particle="Bs";
  const int nbins=1;
  Double_t xbins[nbins]={35};
  Double_t exl[nbins]={25};
  Double_t yPercSigmapPbSystTotHigh[nbins]={0.089};
  Double_t yPercSigmapPbSystTotLow[nbins]={0.089};

  //Double_t commonErrorP = 0.22; // +0.6/10.4 in quadrature
  //Double_t commonErrorN = 0.24;//  +0.6/10.4 in quadrature
  Double_t commonErrorP = TMath::Sqrt(0.22*0.22+ (0.6/10.4)*(0.6/10.4));
  Double_t commonErrorN = TMath::Sqrt(0.24*0.24+ (0.6/10.4)*(0.6/10.4));
*/
    
  TString particle="Bzero";
  const int nbins=3;
  Double_t xbins[nbins]={12.5,17.5,40};
  Double_t exl[nbins]={2.5,2.5,20};
  Double_t yPercSigmapPbSystTotHigh[nbins]={0.145,0.144,0.144};
  Double_t yPercSigmapPbSystTotLow[nbins]={0.145,0.144,0.144};

  //Double_t commonErrorP = 0.0555 ;
  //Double_t commonErrorN = 0.0555  ;
  Double_t commonErrorP = TMath::Sqrt(0.0555*0.0555+ (0.7/40.2)*(0.7/40.2));
  Double_t commonErrorN = TMath::Sqrt(0.0555*0.0555+ (0.7/40.2)*(0.7/40.2));

/*
  TString particle="Bplus";
  const int nbins=5;
  Double_t xbins[nbins]={12.5,17.5,22.5,27.5,45.};
  Double_t exl[nbins]={2.5,2.5,2.5,2.5,15.};
  Double_t yPercSigmapPbSystTotHigh[nbins]={0.117,0.116,0.113,0.143,0.120};
  Double_t yPercSigmapPbSystTotLow[nbins]={0.117,0.116,0.113,0.143,0.120};

  //Double_t commonErrorP = 0.0445 ;
  //Double_t commonErrorN = 0.0445  ;
  
  Double_t commonErrorP = TMath::Sqrt(0.0445*0.0445+ (0.7/40.2)*(0.7/40.2));
  Double_t commonErrorN = TMath::Sqrt(0.0445*0.0445+ (0.7/40.2)*(0.7/40.2));
*/
 /* 
  TString particle="Bzero";
  const int nbins=3;
  Double_t xbins[nbins]={12.5,17.5,40};
  Double_t exl[nbins]={2.5,2.5,20};
  Double_t yPercSigmapPbSystTotHigh[nbins]={0.145,0.144,0.144};
  Double_t yPercSigmapPbSystTotLow[nbins]={0.145,0.144,0.144};

  //Double_t commonErrorP = 0.0555 ;
  //Double_t commonErrorN = 0.0555  ;
  Double_t commonErrorP = TMath::Sqrt(0.0555*0.0555+(0.7/40.2)*(0.7/40.2));
  Double_t commonErrorN = TMath::Sqrt(0.0555*0.0555+ (0.7/40.2)*(0.7/40.2));
*/

void NuclearModification(){

  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  
  TFile*filePPReference=new TFile(Form("../fonll/output%s.root",particle.Data()));  
  TGraphAsymmErrors*gaeBplusReference=(TGraphAsymmErrors*)filePPReference->Get(Form("gaeSigmaDecay%s",particle.Data()));
  gaeBplusReference->SetName(Form("gae%sReference",particle.Data()));
  
  TFile*filepPb=new TFile(Form("Results%s/Sigma%s.root",particle.Data(),particle.Data()));
  TH1F*hSigmapPbStat=(TH1F*)filepPb->Get("hPtSigma");  
  
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
  Double_t yRpA[nbins];                          //value y RpA 
  Double_t yRpAStat[nbins];                      //y err stat RpA 
  Double_t yRpAsystFONLLhigh[nbins];             //y err syst FONLL RpA high
  Double_t yRpAsystFONLLlow[nbins];              //y err syst FONLL RpA lzow
  Double_t yPercRpAsystFONLLhigh[nbins];         //y percentuale err syst FONLL RpA high
  Double_t yPercRpAsystFONLLlow[nbins];          //y percentuale err syst FONLL RpA low
    
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
  }
  
  for(Int_t i=0;i<nbins;i++) {
    ySigmapPb[i]=hSigmapPbStat->GetBinContent(i+1);
    ySigmapPbStat[i]=hSigmapPbStat->GetBinError(i+1);
    yPercSigmapPbStat[i]=ySigmapPbStat[i]/ySigmapPb[i];
    ySigmapPbSystTotHigh[i]=yPercSigmapPbSystTotHigh[i]*ySigmapPb[i];
    ySigmapPbSystTotLow[i]=yPercSigmapPbSystTotLow[i]*ySigmapPb[i];
  }
  
  for(Int_t i=0;i<nbins;i++) {
    yRpA[i]=ySigmapPb[i]/yRefPP[i];
    yRpAStat[i]=ySigmapPbStat[i]/yRefPP[i];
    yFONLL[i]=yRpA[i];
    yRpAsystFONLLhigh[i]=yPercPPsystFONLLlow[i];//*yRpA[i];
    yRpAsystFONLLlow[i]=yPercPPsystFONLLhigh[i];//*yRpA[i];
    yRpPbSystTotHigh[i]=yPercSigmapPbSystTotHigh[i]*yRpA[i];
    yRpPbSystTotLow[i]=yPercSigmapPbSystTotLow[i]*yRpA[i];
    //cout<<yRpPbSystTot[i]<<endl;
    
  }
  
  TGraphAsymmErrors *gSigmasyst = new TGraphAsymmErrors(nbins,xbins,ySigmapPb,exl,exl,ySigmapPbSystTotLow,ySigmapPbSystTotHigh);
  gSigmasyst->SetTitle("Sigma syst uncertainty from pPb");
  gSigmasyst->SetMarkerColor(1);
  gSigmasyst->SetLineColor(1);
  gSigmasyst->SetLineWidth(2);   
  gSigmasyst->SetMarkerStyle(21);
  gSigmasyst->SetMarkerColor(1);


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
  
  TH2F* hempty=new TH2F("hempty","",10,0.,70,10.,1e5,1e10.);  
  hempty->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  if(particle=="Bplus") hempty->GetYaxis()->SetTitle("d#sigma / dp_{T} (B^{+}) (pb GeV^{-1}c)");
  if(particle=="Bzero") hempty->GetYaxis()->SetTitle("d#sigma / dp_{T} (B^{0}) (pb GeV^{-1}c)");
  if(particle=="Bs") hempty->GetYaxis()->SetTitle("d#sigma / dp_{T} (B_{s}) (pb GeV^{-1}c)");
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
    
  
  gaeBplusReference->SetMarkerColor(4);
  gaeBplusReference->SetMarkerStyle(21);  
  gaeBplusReference->SetFillColor(4);
   gaeBplusReference->SetFillStyle(3001);
   gaeBplusReference->SetLineColor(4);
   gaeBplusReference->SetLineWidth(4);

  gaeBplusReference->Draw("2epsame");

  hSigmapPbStat->SetMarkerSize(2);
  hSigmapPbStat->SetMarkerStyle(21);
  hSigmapPbStat->SetLineWidth(3);
  hSigmapPbStat->SetMarkerSize(1);
  hSigmapPbStat->SetLineColor(1);
  hSigmapPbStat->Draw("same");
  
  gSigmasyst->SetFillColor(0);
  gSigmasyst->SetFillStyle(0);
  gSigmasyst->Draw("2esame");
  
  
  TLegend *legendSigma=new TLegend(0.5685484,0.5864271,0.8145161,0.7167019,"");
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.04);

  TLegendEntry *ent_SigmapPb=legendSigma->AddEntry(hSigmapPbStat,"pPb","PL");
  ent_SigmapPb->SetTextFont(42);
  ent_SigmapPb->SetLineColor(1);
  ent_SigmapPb->SetMarkerColor(1);

 // TLegendEntry *ent_SigmapPbSyst=legendSigma->AddEntry(gSigmasyst,"pPb syst err","PL");
 // ent_SigmapPbSyst->SetTextFont(42);
 // ent_SigmapPbSyst->SetLineColor(1);
 // ent_SigmapPbSyst->SetMarkerColor(1);

  TLegendEntry *ent_Sigmapp=legendSigma->AddEntry(gaeBplusReference,"pp reference","PLF");
  ent_Sigmapp->SetTextFont(42);
  ent_Sigmapp->SetLineColor(4);
  ent_Sigmapp->SetMarkerColor(4);
  legendSigma->Draw("same");
  
  TLatex * tlatex1=new TLatex(0.1693548,0.8562368,"CMS Preliminary");
  tlatex1->SetNDC();
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.04);
  tlatex1->Draw();
  
  TLatex * tlatex2=new TLatex(0.5564516,0.8498943,"p+Pb #sqrt{s_{NN}}= 5.02 TeV");
  tlatex2->SetNDC();
  tlatex2->SetTextColor(1);
  tlatex2->SetTextFont(42);
  tlatex2->SetTextSize(0.04);
  tlatex2->Draw();

  
  
  canvasSigma->SaveAs(Form("Results%s/canvasSigma%s.pdf",particle.Data(),particle.Data()));  
  
    TGraphAsymmErrors *gRpAstat = new TGraphAsymmErrors(nbins,xbins,yRpA,exl,exl,yRpAStat,yRpAStat);
  gRpAstat->SetTitle("RpA stat uncertainty from pPb");
  gRpAstat->SetMarkerColor(1);
  gRpAstat->SetLineColor(1);
  gRpAstat->SetLineWidth(2);   
  gRpAstat->SetMarkerStyle(22);
  gRpAstat->SetMarkerColor(1);
  
  TGraphAsymmErrors *gRpAsyst = new TGraphAsymmErrors(nbins,xbins,yRpA,exl,exl,yRpPbSystTotLow,yRpPbSystTotHigh);
  gRpAsyst->SetTitle("RpA syst uncertainty from pPb");
  gRpAsyst->SetMarkerColor(4);
  gRpAsyst->SetLineColor(4);
  gRpAsyst->SetLineWidth(2);   
  gRpAsyst->SetMarkerStyle(21);
  gRpAsyst->SetMarkerColor(4);

   
  TGraphAsymmErrors *gRpAsystFONLL = new TGraphAsymmErrors(nbins,xbins,yFONLL,exl,exl,yRpAsystFONLLlow,yRpAsystFONLLhigh);
  gRpAsystFONLL->SetTitle("RpA syst uncertainty from FONLL reference");
  gRpAsystFONLL->SetMarkerColor(2);
  gRpAsystFONLL->SetLineColor(2);
  gRpAsystFONLL->SetLineWidth(2);   
  gRpAsystFONLL->SetMarkerStyle(21);
  gRpAsystFONLL->SetMarkerColor(2);




  TCanvas *canvasRpA=new TCanvas("canvasRpA","canvasRpA",500,500);   
  
  

  canvasRpA->Range(-1.989924,-0.2917772,25.49622,2.212202);
  canvasRpA->SetFillColor(0);
  canvasRpA->SetBorderMode(0);
  canvasRpA->SetBorderSize(2);
  canvasRpA->SetLeftMargin(0.1451613);
  canvasRpA->SetRightMargin(0.05443548);
  canvasRpA->SetTopMargin(0.08474576);
  canvasRpA->SetBottomMargin(0.1165254);
  canvasRpA->SetFrameBorderMode(0);
  canvasRpA->SetFrameBorderMode(0);
  
  TLegend *legendRpA=new TLegend(0.3145161,0.5804503,0.5604839,0.770252,"");
  legendRpA->SetBorderSize(0);
  legendRpA->SetLineColor(0);
  legendRpA->SetFillColor(0);
  legendRpA->SetFillStyle(1001);
  legendRpA->SetTextFont(42);
  legendRpA->SetTextSize(0.04);

  TH2F* hempty=new TH2F("hempty","",10,0.,70,10.,0.,2.5);  
  hempty->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  if(particle=="Bplus") hempty->GetYaxis()->SetTitle("R_{pA} (B^{+})");
  if(particle=="Bzero") hempty->GetYaxis()->SetTitle("R_{pA} (B^{0})");
  if(particle=="Bs") hempty->GetYaxis()->SetTitle("R_{pA} (B_{s})");
  hempty->GetXaxis()->SetTitleOffset(1.1);
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
  
  TLine *l = new TLine(0,1,70,1);
  l->SetLineStyle(2);
  
  legendRpA->Draw();
  gRpAstat->SetMarkerStyle(21);
  gRpAstat->SetLineColor(1);
  gRpAstat->SetMarkerColor(1);

  gRpAsystFONLL->SetLineStyle(3);
  gRpAsystFONLL->SetLineWidth(3);
  gRpAsystFONLL->SetFillColor(5);
  gRpAsystFONLL->SetLineColor(5);//kAzure-3);
  gRpAsystFONLL->SetMarkerColor(5);//kAzure-3);
  gRpAsystFONLL->Draw("2same");
  gRpAstat->Draw("psame");
  gRpAsyst->SetFillColor(0);
  gRpAsyst->SetFillStyle(0);
  gRpAsyst->Draw("2same");
  

  TBox *b = new TBox(3,1-commonErrorN,7,1+commonErrorP);
  b->SetLineColor(1);
  b->SetFillColor(kGray);
  b->Draw();

  TLegendEntry *ent_RpAstat=legendRpA->AddEntry(gRpAstat,"R_{pA} stat unc","P");
  ent_RpAstat->SetTextFont(42);
  ent_RpAstat->SetLineColor(2);
  ent_RpAstat->SetMarkerColor(2);
  TLegendEntry *ent_RpAsystData=legendRpA->AddEntry(gRpAsyst,"Syst err pPb data","P");
  ent_RpAsystData->SetTextFont(42);
  ent_RpAsystData->SetLineColor(4);
  ent_RpAsystData->SetMarkerColor(1);
  TLegendEntry *ent_RpAsystData=legendRpA->AddEntry(b,"Syst Lumi+BR","f");
  ent_RpAsystData->SetTextFont(42);
  ent_RpAsystData->SetLineColor(2);
  ent_RpAsystData->SetMarkerColor(2);

  
  TLegendEntry *ent_RpAsystFONLL=legendRpA->AddEntry(gRpAsystFONLL,"Syst err from FONLL pp ref","P");
  ent_RpAsystFONLL->SetTextFont(42);
  ent_RpAsystFONLL->SetLineColor(5);
  ent_RpAsystFONLL->SetMarkerColor(5);
  
  TLatex * tlatex1=new TLatex(0.1693548,0.8562368,"CMS Preliminary");
  tlatex1->SetNDC();
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.04);
  tlatex1->Draw();
  
  TLatex * tlatex2=new TLatex(0.5564516,0.8498943,"p+Pb #sqrt{s_{NN}}= 5.02 TeV");
  tlatex2->SetNDC();
  tlatex2->SetTextColor(1);
  tlatex2->SetTextFont(42);
  tlatex2->SetTextSize(0.04);
  tlatex2->Draw();

  TLatex * tlatex2=new TLatex(0.5564516,0.8,"L_{int} = 34.8 nb^{-1}");
  tlatex2->SetNDC();
  tlatex2->SetTextColor(1);
  tlatex2->SetTextFont(42);
  tlatex2->SetTextSize(0.04);
  tlatex2->Draw();

//  l->Draw();  
  canvasRpA->SaveAs(Form("Results%s/canvasRpA%s.pdf",particle.Data(),particle.Data()));  
  
  TFile *fout=new TFile(Form("Results%s/fileRpA%s.root",particle.Data(),particle.Data()),"recreate");  
  fout->cd();
  gSigmasyst->SetName("gSigmasyst");
  gSigmasyst->Write();
  gaeBplusReference->Write();
  hSigmapPbStat->Write();
}
