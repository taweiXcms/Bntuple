void NuclearModification(TString particle="Bplus"){

  const int nbins=6;
  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  
  TFile*filePPReference=new TFile("../fonll/outputBpluszerosdpt.root");  
  TGraphAsymmErrors*gaeBplusReference=(TGraphAsymmErrors*)filePPReference->Get(Form("gae%s",particle.Data()));
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
  
  Double_t yRpA[nbins];                          //value y RpA 
  Double_t yRpAStat[nbins];                      //y err stat RpA 
  Double_t yRpAsystFONLLhigh[nbins];             //y err syst FONLL RpA high
  Double_t yRpAsystFONLLlow[nbins];              //y err syst FONLL RpA lzow
  Double_t yPercRpAsystFONLLhigh[nbins];         //y percentuale err syst FONLL RpA high
  Double_t yPercRpAsystFONLLlow[nbins];          //y percentuale err syst FONLL RpA low
  
  
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
  }
  
  for(Int_t i=0;i<nbins;i++) {
    yRpA[i]=ySigmapPb[i]/yRefPP[i];
    yRpAStat[i]=ySigmapPbStat[i]/yRefPP[i];
    yRpAsystFONLLhigh[i]=yPercPPsystFONLLlow[i]*yRpA[i];
    yRpAsystFONLLlow[i]=yPercPPsystFONLLhigh[i]*yRpA[i];
  }
  
  Double_t xbins[nbins]={7.5,12.5,17.5,22.5,27.5,45.};
  Double_t exl[nbins]={2.5,2.5,2.5,2.5,2.5,15.};

  TGraphAsymmErrors *gRpAstat = new TGraphAsymmErrors(nbins,xbins,yRpA,exl,exl,yRpAStat,yRpAStat);
  gRpAstat->SetTitle("RpA stat uncertainty from pPb");
  gRpAstat->SetMarkerColor(2);
  gRpAstat->SetLineColor(2);
  gRpAstat->SetLineWidth(2);   
  gRpAstat->SetMarkerStyle(22);
   
  TGraphAsymmErrors *gRpAsystFONLL = new TGraphAsymmErrors(nbins,xbins,yRpA,exl,exl,yRpAsystFONLLlow,yRpAsystFONLLhigh);
  gRpAsystFONLL->SetTitle("RpA syst uncertainty from FONLL reference");
  gRpAsystFONLL->SetMarkerColor(1);
  gRpAsystFONLL->SetMarkerStyle(21);
  gRpAsystFONLL->SetLineWidth(5.);
  gRpAsystFONLL->SetFillStyle(300);

    
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
  
  TH2F* hempty=new TH2F("hempty","",10,0.,60,10.,0.1,1e7.);  
  hempty->GetXaxis()->SetTitle("p_{t} (GeV/c)");
  hempty->GetYaxis()->SetTitle("d#sigma/dp_{t} (GeV^{-1})");
  hempty->GetXaxis()->SetTitleOffset(1.);
  hempty->GetYaxis()->SetTitleOffset(1.05);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.035);
  hempty->GetYaxis()->SetLabelSize(0.035);  
  hempty->SetMaximum(2);
  hempty->SetMinimum(0.);
  hempty->Draw();
    
  gaeBplusReference->SetLineWidth(2);
  gaeBplusReference->SetLineColor(kAzure-1);//kAzure-3);
  gaeBplusReference->SetFillStyle(0);
  gaeBplusReference->SetMarkerColor(kWhite);
  gaeBplusReference->SetMarkerStyle(24);
  gaeBplusReference->Draw("2");

    
//  gaeBplusReference->SetLineStyle(3);
//  gaeBplusReference->SetLineColor(kAzure-1);//kAzure-3);
//  gaeBplusReference->SetFillColor(2);//kAzure-3);
  
  gaeBplusReference->Draw("2same");
  gaeBplusReference->SetMarkerColor(2);

  hSigmapPbStat->SetMarkerSize(2);
  hSigmapPbStat->SetMarkerStyle(22);
  hSigmapPbStat->SetLineWidth(3);
  hSigmapPbStat->SetMarkerSize(1);
  hSigmapPbStat->SetLineColor(1);

  
  hSigmapPbStat->Draw("same");
  
  TLegend *legendSigma=new TLegend(0.5544355,0.6934461,0.8004032,0.8287526,"");
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.029);

  TLegendEntry *ent_SigmapPb=legendSigma->AddEntry(hSigmapPbStat,"d#sigma/dp_{t} in pPb","P");
  ent_SigmapPb->SetTextFont(42);
  TLegendEntry *ent_Sigmapp=legendSigma->AddEntry(gRpAsystFONLL,"d#sigma/dp_{t} pp reference","P");
  ent_Sigmapp->SetTextFont(42);
  legendSigma->Draw("same");
  canvasSigma->SaveAs(Form("Results%s/canvasSigma%s.eps",particle.Data(),particle.Data()));  
  

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
  
  TLegend *legendRpA=new TLegend(0.5362903,0.7505285,0.7822581,0.8858351,"");
  legendRpA->SetBorderSize(0);
  legendRpA->SetLineColor(0);
  legendRpA->SetFillColor(0);
  legendRpA->SetFillStyle(1001);
  legendRpA->SetTextFont(42);
  legendRpA->SetTextSize(0.029);

  TLegendEntry *ent_RpAstat=legendRpA->AddEntry(gRpAstat,"R_{pA} stat unc","P");
  ent_RpAstat->SetTextFont(42);
  TLegendEntry *ent_RpAsystFONLL=legendRpA->AddEntry(gRpAsystFONLL,"Syst err from FONLL pp ref","P");
  ent_RpAsystFONLL->SetTextFont(42);

  TH2F* hempty=new TH2F("hempty","",10,0.,60,10.,0.,4.);  
  hempty->GetXaxis()->SetTitle("p_{t} (GeV/c)");
  hempty->GetYaxis()->SetTitle("R_{pA} (B^{0} mesons)");
  hempty->GetXaxis()->SetTitleOffset(1.);
  hempty->GetYaxis()->SetTitleOffset(1.05);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.035);
  hempty->GetYaxis()->SetLabelSize(0.035);  
  hempty->SetMaximum(2);
  hempty->SetMinimum(0.);
  hempty->Draw();
  legendRpA->Draw();
  gRpAstat->SetMarkerStyle(21);

  gRpAsystFONLL->SetLineStyle(3);
  gRpAsystFONLL->SetLineWidth(3);
  gRpAsystFONLL->SetLineColor(1);//kAzure-3);
  gRpAsystFONLL->Draw("2same");
  gRpAstat->Draw("psame");
  
  canvasRpA->SaveAs(Form("Results%s/canvasRpA%s.eps",particle.Data(),particle.Data()));  
}
