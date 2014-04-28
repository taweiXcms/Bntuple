
void BmesonRatio(){

  double Bplus=6.09604*1e-5;
  double Bzero=5.244e-5;

  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
    
  TFile*filepPbBplus=new TFile("ResultsBplus/fileRpABplus.root");
  TFile*filepPbBzero=new TFile("ResultsBzero/fileRpABzero.root");
  
  TH1F*hSigmapPbStatBplusOriginal=(TH1F*)filepPbBplus->Get("hPtSigma");  
  TH1F*hSigmapPbStatBzero=(TH1F*)filepPbBzero->Get("hPtSigma");  
  
  hSigmapPbStatBplusOriginal->Scale(Bplus);
  hSigmapPbStatBzero->Scale(Bzero);
  
  double rebin[4] = {10,15,20,60};
  
  //************** Bplus
  
  double value10_15Bplus=hSigmapPbStatBplusOriginal->GetBinContent(1);
  double value15_20Bplus=hSigmapPbStatBplusOriginal->GetBinContent(2);
  double value20_25Bplus=hSigmapPbStatBplusOriginal->GetBinContent(3);
  double value25_30Bplus=hSigmapPbStatBplusOriginal->GetBinContent(4);
  double value30_60Bplus=hSigmapPbStatBplusOriginal->GetBinContent(5);
  
  double errvalue10_15Bplus=hSigmapPbStatBplusOriginal->GetBinError(1);
  double errvalue15_20Bplus=hSigmapPbStatBplusOriginal->GetBinError(2);
  double errvalue20_25Bplus=hSigmapPbStatBplusOriginal->GetBinError(3);
  double errvalue25_30Bplus=hSigmapPbStatBplusOriginal->GetBinError(4);
  double errvalue30_60Bplus=hSigmapPbStatBplusOriginal->GetBinError(5);
  
  double value20_60Bplus=(value20_25Bplus*5+value25_30Bplus*5+value30_60Bplus*30)/40.;
  double errvalue20_60Bplus=TMath::Sqrt((errvalue20_25Bplus*5)*(errvalue20_25Bplus*5)+(errvalue25_30Bplus*5)*(errvalue25_30Bplus*5)+(errvalue30_60Bplus*30)*(errvalue30_60Bplus*30));
  errvalue20_60Bplus=errvalue20_60Bplus/40;
  
  //************** Bzero


  double value10_15Bzero=hSigmapPbStatBzero->GetBinContent(1);
  double value15_20Bzero=hSigmapPbStatBzero->GetBinContent(2);
  double value20_60Bzero=hSigmapPbStatBzero->GetBinContent(3);
  double errvalue10_15Bzero=hSigmapPbStatBzero->GetBinError(1);
  double errvalue15_20Bzero=hSigmapPbStatBzero->GetBinError(2);
  double errvalue20_60Bzero=hSigmapPbStatBzero->GetBinError(3);

  TH1F*hSigmapPbStatBplus=new TH1F("hSigmapPbStatBplus","hSigmapPbStatBplus",3,rebin);
  hSigmapPbStatBplus->SetBinContent(1,value10_15Bplus);
  hSigmapPbStatBplus->SetBinContent(2,value15_20Bplus);
  hSigmapPbStatBplus->SetBinContent(3,value20_60Bplus);
  hSigmapPbStatBplus->SetBinError(1,errvalue10_15Bplus);
  hSigmapPbStatBplus->SetBinError(2,errvalue15_20Bplus);
  hSigmapPbStatBplus->SetBinError(3,errvalue20_60Bplus);

  hSigmapPbStatBplus->Sumw2();
  hSigmapPbStatBzero->Sumw2();

  double ratio10_15=value10_15Bplus/value10_15Bzero;
  double ratio15_20=value15_20Bplus/value15_20Bzero;
  double ratio20_60=value20_60Bplus/value20_60Bzero;
  
  
  //****************************   STAT UNCERTAINTY ****************************  
  
  double errratio10_15=(errvalue10_15Bplus/value10_15Bplus)*(errvalue10_15Bplus/value10_15Bplus);
  errratio10_15=errratio10_15+(errvalue10_15Bzero/value10_15Bzero)*(errvalue10_15Bzero/value10_15Bzero);
  errratio10_15=TMath::Sqrt(errratio10_15);
  errratio10_15=errratio10_15*ratio10_15;
  
  double errratio15_20=(errvalue15_20Bplus/value15_20Bplus)*(errvalue15_20Bplus/value15_20Bplus);
  errratio15_20=errratio15_20+(errvalue15_20Bzero/value15_20Bzero)*(errvalue15_20Bzero/value15_20Bzero);
  errratio15_20=TMath::Sqrt(errratio15_20);
  errratio15_20=errratio15_20*ratio15_20;

  double errratio20_60=(errvalue20_60Bplus/value20_60Bplus)*(errvalue20_60Bplus/value20_60Bplus);
  errratio20_60=errratio20_60+(errvalue20_60Bzero/value20_60Bzero)*(errvalue20_60Bzero/value20_60Bzero);
  errratio20_60=TMath::Sqrt(errratio20_60);
  errratio20_60=errratio20_60*ratio20_60;
  

  hRatioBplusOverBzero=new TH1F("hRatioBplusOverBzero","hRatioBplusOverBzero",3,rebin);
  hRatioBplusOverBzero->SetBinContent(1,ratio10_15);
  hRatioBplusOverBzero->SetBinContent(2,ratio15_20);
  hRatioBplusOverBzero->SetBinContent(3,ratio20_60);
  
  hRatioBplusOverBzero->SetBinError(1,errratio10_15);
  hRatioBplusOverBzero->SetBinError(2,errratio15_20);
  hRatioBplusOverBzero->SetBinError(3,errratio20_60);
  
  
  //****************************   SYST UNCERTAINTY ****************************  
  
  Double_t systAcc_Bplus=0.03;
  Double_t systHadronTrack_Bplus=0.039;
  Double_t systCutEff_Bplus=0.05;
  Double_t systptres_Bplus=0.06;
  Double_t systpifeeddown_Bplus=0.05;
  Double_t systTrigger_Bplus=0.016;
  Double_t systMuonEff_Bplus=0.032;
  Double_t systInnerEff_Bplus=0.018;
  Double_t systPDF_Bplus=0.064;
  
  Double_t systAcc_Bzero=0.027;
  Double_t systHadronTrack_Bzero=0.078;
  Double_t systCutEff_Bzero=0.05;
  Double_t systptres_Bzero=0.06;
  Double_t systTrigger_Bzero=0.016;
  Double_t systMuonEff_Bzero=0.032;
  Double_t systInnerEff_Bzero=0.018;
  Double_t systPDF_Bzero=0.1;


  Double_t systAccRatio=TMath::Sqrt(systAcc_Bzero*systAcc_Bzero+systAcc_Bplus*systAcc_Bplus);
  Double_t systHadronTrack=systHadronTrack_Bzero-systHadronTrack_Bplus;
  Double_t systCutEff=TMath::Sqrt(systCutEff_Bplus*systCutEff_Bplus+systCutEff_Bzero*systCutEff_Bzero);
  Double_t systptres=systptres_Bplus-systptres_Bzero;
  Double_t systpifeeddown=systpifeeddown_Bplus;
  Double_t systTrigger=systTrigger_Bplus-systTrigger_Bzero;
  Double_t systMuonEff=systMuonEff_Bplus-systMuonEff_Bzero;
  Double_t systInnerEff_Bplus=systInnerEff_Bplus-systInnerEff_Bzero;
  Double_t systPDF=TMath::Sqrt(systPDF_Bplus*systPDF_Bplus+systPDF_Bzero*systPDF_Bzero);
  
  Double_t systTot=systAccRatio*systAccRatio+systHadronTrack*systHadronTrack+systCutEff*systCutEff;
  systTot=systTot+systptres*systptres+systpifeeddown*systpifeeddown+systTrigger*systTrigger;
  systTot=systTot+systMuonEff*systMuonEff+systInnerEff_Bplus*systInnerEff_Bplus+systPDF*systPDF;
  systTot=TMath::Sqrt(systTot);
  
  double errsystratio10_15=systTot*ratio10_15;
  double errsystratio15_20=systTot*ratio15_20;
  double errsystratio20_60=systTot*ratio20_60;
  
  cout<<"guarda qui"<<systTot<<endl;
    
 TGraphAsymmErrors* gSystratio=new TGraphAsymmErrors(0);
 gSystratio->SetPoint(0,12.5,ratio10_15);
 gSystratio->SetPoint(1,17.5,ratio15_20);
 gSystratio->SetPoint(2,40.,ratio20_60);
 
 gSystratio->SetPointEYlow(0,errsystratio10_15);
 gSystratio->SetPointEYhigh(0,errsystratio10_15);
 gSystratio->SetPointEYlow(1,errsystratio15_20);
 gSystratio->SetPointEYhigh(1,errsystratio15_20);
 gSystratio->SetPointEYlow(2,errsystratio20_60);
 gSystratio->SetPointEYhigh(2,errsystratio20_60);
 
 gSystratio->SetPointEXlow(0,2.5);
 gSystratio->SetPointEXhigh(0,2.5);
 gSystratio->SetPointEXlow(1,2.5);
 gSystratio->SetPointEXhigh(1,2.5);
 gSystratio->SetPointEXlow(2,20.);
 gSystratio->SetPointEXhigh(2,20.);

 

 gSystratio->SetLineColor(1);
 gSystratio->SetMarkerColor(2);
 gSystratio->SetLineWidth(2);
 gSystratio->SetMarkerStyle(20);
 gSystratio->SetMarkerSize(1.2);

  
  
  TCanvas *canvasRatio=new TCanvas("canvasRatio","canvasRatio",500,500);   
  
  

  canvasRatio->Range(-1.989924,-0.2917772,25.49622,2.212202);
  canvasRatio->SetFillColor(0);
  canvasRatio->SetBorderMode(0);
  canvasRatio->SetBorderSize(2);
  canvasRatio->SetLeftMargin(0.1451613);
  canvasRatio->SetRightMargin(0.05443548);
  canvasRatio->SetTopMargin(0.08474576);
  canvasRatio->SetBottomMargin(0.1165254);
  canvasRatio->SetFrameBorderMode(0);
  canvasRatio->SetFrameBorderMode(0);
  
  TLegend *legend=new TLegend(0.3145161,0.75,0.5604839,0.85,"");
  legend->SetBorderSize(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetTextFont(42);
  legend->SetTextSize(0.05);
  
  TH2F* hempty=new TH2F("hempty","",10,0.,70,10.,0.,2.5);  
   hempty->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   hempty->GetYaxis()->SetTitle("Ratio corrected yield B^{+}/B^{0}");
  
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

  
  hRatioBplusOverBzero->SetMarkerColor(1);
  hRatioBplusOverBzero->SetLineColor(1);
  hRatioBplusOverBzero->SetLineWidth(2);   
  hRatioBplusOverBzero->SetMarkerStyle(22);
  
  gSystratio->SetMarkerColor(4);
  gSystratio->SetLineColor(4);
  gSystratio->SetLineWidth(4);   
  gSystratio->SetMarkerStyle(21);
  gSystratio->SetMarkerColor(4);
  gSystratio->SetFillStyle(3001);
  gSystratio->SetFillColor(0);
  gSystratio->SetFillStyle(0);
  


  TLegendEntry *ent_Stat=legend->AddEntry(hRatioBplusOverBzero,"Stat. err.","P");
  ent_Stat->SetTextFont(42);
  ent_Stat->SetLineColor(2);
  ent_Stat->SetMarkerColor(2);
  TLegendEntry *ent_Syst=legend->AddEntry(gSystratio,"Syst. err","P");
  ent_Syst->SetTextFont(42);
  ent_Syst->SetLineColor(4);
  ent_Syst->SetMarkerColor(1);
  
  hempty->Draw();
  hRatioBplusOverBzero->Draw("same");
  gSystratio->Draw("2same");
  legend->Draw();
  

  
  
  double BRBplusBzero=Bplus/Bzero;
  double RelBRBplusBzeroErr=TMath::Sqrt(0.0318*0.0318+0.0459*0.0459);
  TLine*line=new TLine(10.,BRBplusBzero,60,BRBplusBzero);
  TLine*lineHigh=new TLine(10.,BRBplusBzero*(1+RelBRBplusBzeroErr),60,BRBplusBzero*(1+RelBRBplusBzeroErr));
  TLine*lineLow=new TLine(10.,BRBplusBzero*(1-RelBRBplusBzeroErr),60,BRBplusBzero*(1-RelBRBplusBzeroErr));
  line->SetLineColor(2);
  lineLow->SetLineColor(2);
  lineHigh->SetLineColor(2);
  line->SetLineWidth(3);
  lineLow->SetLineWidth(3);
  lineHigh->SetLineWidth(3);
  line->Draw();
  lineHigh->Draw();
  lineLow->Draw();
  
  canvasRatio->SaveAs("canvasRatioBplusOverBzero.pdf");
  
  
  
  
  
  
  
  
  
  
}
