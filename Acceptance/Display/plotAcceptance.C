void plotAcceptanceVsPt(TString suffix="Pt"){

  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);

  TFile*fileoutput=new TFile("../Code/Results/outputBplus.root");
  
  TH1D*hPtAccNumVsPt=(TH1D*)fileoutput->Get("hPtAccNumVsPt");
  TH1D*hPtAccNumVsPtReweight=(TH1D*)fileoutput->Get("hPtAccNumVsPtReweight");
  TH1D*hPtAccNumVsPtLow=(TH1D*)fileoutput->Get("hPtAccNumVsPtLow");
  TH1D*hPtAccNumVsPtHigh=(TH1D*)fileoutput->Get("hPtAccNumVsPtHigh");
  
  TH1D*hPtAccDenVsPt=(TH1D*)fileoutput->Get("hPtAccDenVsPt");
  TH1D*hPtAccDenVsPtReweight=(TH1D*)fileoutput->Get("hPtAccDenVsPtReweight");
  TH1D*hPtAccDenVsPtLow=(TH1D*)fileoutput->Get("hPtAccDenVsPtLow");
  TH1D*hPtAccDenVsPtHigh=(TH1D*)fileoutput->Get("hPtAccDenVsPtHigh");
  
  TH1D*hAccVsPt=(TH1D*)fileoutput->Get("hAccVsPt");
  TH1D*hAccVsPtReweight=(TH1D*)fileoutput->Get("hAccVsPtReweight");
  TH1D*hAccVsPtLow=(TH1D*)fileoutput->Get("hAccVsPtLow");
  TH1D*hAccVsPtHigh=(TH1D*)fileoutput->Get("hAccVsPtHigh");

  TH1D*hPtAccNumVsy=(TH1D*)fileoutput->Get("hPtAccNumVsy");
  TH1D*hPtAccNumVsyReweight=(TH1D*)fileoutput->Get("hPtAccNumVsyReweight");
  TH1D*hPtAccNumVsyLow=(TH1D*)fileoutput->Get("hPtAccNumVsyLow");
  TH1D*hPtAccNumVsyHigh=(TH1D*)fileoutput->Get("hPtAccNumVsyHigh");
  
  TH1D*hPtAccDenVsy=(TH1D*)fileoutput->Get("hPtAccDenVsy");
  TH1D*hPtAccDenVsyReweight=(TH1D*)fileoutput->Get("hPtAccDenVsyReweight");
  TH1D*hPtAccDenVsyLow=(TH1D*)fileoutput->Get("hPtAccDenVsyLow");
  TH1D*hPtAccDenVsyHigh=(TH1D*)fileoutput->Get("hPtAccDenVsyHigh");
  
  TH1D*hAccVsy=(TH1D*)fileoutput->Get("hAccVsy");
  TH1D*hAccVsyReweight=(TH1D*)fileoutput->Get("hAccVsyReweight");
  TH1D*hAccVsyLow=(TH1D*)fileoutput->Get("hAccVsyLow");
  TH1D*hAccVsyHigh=(TH1D*)fileoutput->Get("hAccVsyHigh");

  
  TCanvas*canvasAccVsPt=new TCanvas("canvasAccVsPt","canvasAccVsPt",1000,1200);
  canvasAccVsPt->Divide(2,2);
  
  canvasAccVsPt->cd(1);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  hPtAccNumVsPt->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hPtAccNumVsPt->GetYaxis()->SetTitle("Numerator");
  hPtAccNumVsPt->SetMinimum(0.);
  hPtAccNumVsPt->GetXaxis()->SetTitleOffset(1.1);
  hPtAccNumVsPt->GetYaxis()->SetTitleOffset(1.85);
  hPtAccNumVsPt->SetLineWidth(2);
  hPtAccNumVsPt->SetLineColor(1);
  hPtAccNumVsPt->SetMarkerSize(0.5);
  hPtAccNumVsPt->SetMarkerStyle(21);
  hPtAccNumVsPt->SetMarkerColor(1);
  hPtAccNumVsPt->Draw();
  hPtAccNumVsPtReweight->SetLineWidth(2);
  hPtAccNumVsPtReweight->SetLineColor(2);
  hPtAccNumVsPtReweight->SetMarkerSize(0.5);
  hPtAccNumVsPtReweight->SetMarkerStyle(21);
  hPtAccNumVsPtReweight->SetMarkerColor(2);
  hPtAccNumVsPtReweight->Draw("SAMES");
  hPtAccNumVsPtLow->SetLineWidth(2);
  hPtAccNumVsPtLow->SetLineColor(3);
  hPtAccNumVsPtLow->SetMarkerSize(0.5);
  hPtAccNumVsPtLow->SetMarkerStyle(21);
  hPtAccNumVsPtLow->SetMarkerColor(3);
  hPtAccNumVsPtLow->Draw("SAMES");
  hPtAccNumVsPtHigh->SetLineWidth(2);
  hPtAccNumVsPtHigh->SetLineColor(4);
  hPtAccNumVsPtHigh->SetMarkerSize(0.5);
  hPtAccNumVsPtHigh->SetMarkerStyle(21);
  hPtAccNumVsPtHigh->SetMarkerColor(4);
  hPtAccNumVsPtHigh->Draw("SAMES");


  TLegend *legAccVsPt=new TLegend(0.2383901,0.6608392,0.7972136,0.7706294,"");
  legAccVsPt->SetBorderSize(0);
  legAccVsPt->SetFillStyle(0);
  legAccVsPt->SetTextSize(0.045);

  TLegendEntry *entAccVsPt=legAccVsPt->AddEntry(hPtAccNumVsPt," central","P");
  entAccVsPt->SetTextColor(1);
  TLegendEntry *entAccVsPtReweight=legAccVsPt->AddEntry(hPtAccNumVsPtReweight," reweighted","P");
  entAccVsPtReweight->SetTextColor(2);
  TLegendEntry *entAccVsPtLow=legAccVsPt->AddEntry(hPtAccNumVsPtLow," reweight y low 40%","P");
  entAccVsPtLow->SetTextColor(3);
  TLegendEntry *entAccVsPtHigh=legAccVsPt->AddEntry(hPtAccNumVsPtHigh," reweight y up 40%","P");
  entAccVsPtHigh->SetTextColor(4);

  legAccVsPt->Draw();
  
  canvasAccVsPt->cd(2);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  hPtAccDenVsPt->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hPtAccDenVsPt->GetYaxis()->SetTitle("Denumerator");
  hPtAccDenVsPt->SetMinimum(0.);
  hPtAccDenVsPt->GetXaxis()->SetTitleOffset(1.1);
  hPtAccDenVsPt->GetYaxis()->SetTitleOffset(1.85);
  hPtAccDenVsPt->SetLineWidth(2);
  hPtAccDenVsPt->SetLineColor(1);
  hPtAccDenVsPt->SetMarkerSize(0.5);
  hPtAccDenVsPt->SetMarkerStyle(21);
  hPtAccDenVsPt->SetMarkerColor(1);
  hPtAccDenVsPt->Draw();
  hPtAccDenVsPtReweight->SetLineWidth(2);
  hPtAccDenVsPtReweight->SetLineColor(2);
  hPtAccDenVsPtReweight->SetMarkerSize(0.5);
  hPtAccDenVsPtReweight->SetMarkerStyle(21);
  hPtAccDenVsPtReweight->SetMarkerColor(2);
  hPtAccDenVsPtReweight->Draw("SAMES");
  hPtAccDenVsPtLow->SetLineWidth(2);
  hPtAccDenVsPtLow->SetLineColor(3);
  hPtAccDenVsPtLow->SetMarkerSize(0.5);
  hPtAccDenVsPtLow->SetMarkerStyle(21);
  hPtAccDenVsPtLow->SetMarkerColor(3);
  hPtAccDenVsPtLow->Draw("SAMES");
  hPtAccDenVsPtHigh->SetLineWidth(2);
  hPtAccDenVsPtHigh->SetLineColor(4);
  hPtAccDenVsPtHigh->SetMarkerSize(0.5);
  hPtAccDenVsPtHigh->SetMarkerStyle(21);
  hPtAccDenVsPtHigh->SetMarkerColor(4);
  hPtAccDenVsPtHigh->Draw("SAMES");

  legAccVsPt->Draw();

  canvasAccVsPt->cd(3);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  hAccVsPt->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hAccVsPt->GetYaxis()->SetTitle("Acceptance");
  hAccVsPt->SetMinimum(0.);
  hAccVsPt->SetMaximum(1.5);
  hAccVsPt->GetXaxis()->SetTitleOffset(1.1);
  hAccVsPt->GetYaxis()->SetTitleOffset(1.85);
  hAccVsPt->SetLineWidth(2);
  hAccVsPt->SetLineColor(1);
  hAccVsPt->SetMarkerSize(0.5);
  hAccVsPt->SetMarkerStyle(21);
  hAccVsPt->SetMarkerColor(1);
  hAccVsPt->Draw();
  hAccVsPtReweight->SetLineWidth(2);
  hAccVsPtReweight->SetLineColor(2);
  hAccVsPtReweight->SetMarkerSize(0.5);
  hAccVsPtReweight->SetMarkerStyle(21);
  hAccVsPtReweight->SetMarkerColor(2);
  hAccVsPtReweight->Draw("SAMES");
  hAccVsPtLow->SetLineWidth(2);
  hAccVsPtLow->SetLineColor(3);
  hAccVsPtLow->SetMarkerSize(0.5);
  hAccVsPtLow->SetMarkerStyle(21);
  hAccVsPtLow->SetMarkerColor(3);
  hAccVsPtLow->Draw("SAMES");
  hAccVsPtHigh->SetLineWidth(2);
  hAccVsPtHigh->SetLineColor(4);
  hAccVsPtHigh->SetMarkerSize(0.5);
  hAccVsPtHigh->SetMarkerStyle(21);
  hAccVsPtHigh->SetMarkerColor(4);
  hAccVsPtHigh->Draw("SAMES");

  legAccVsPt->Draw();

  canvasAccVsPt->cd(4);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  TH1D*hAccVsPtRatioReweightOverNoWeight=(TH1D*)hAccVsPtReweight->Clone("hAccVsPtRatioReweightOverNoWeight");
  hAccVsPtRatioReweightOverNoWeight->Divide(hAccVsPt);
  TH1D*hAccVsPtRatioLowOverNoWeight=(TH1D*)hAccVsPtLow->Clone("hAccVsPtRatioLowOverNoWeight");
  hAccVsPtRatioLowOverNoWeight->Divide(hAccVsPt);
  TH1D*hAccVsPtRatioHighOverNoWeight=(TH1D*)hAccVsPtHigh->Clone("hAccVsPtRatioHighOverNoWeight");
  hAccVsPtRatioHighOverNoWeight->Divide(hAccVsPt);

  
  hAccVsPtRatioReweightOverNoWeight->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hAccVsPtRatioReweightOverNoWeight->GetYaxis()->SetTitle("Ratio Acceptance Reweight/NoWeight");
  hAccVsPtRatioReweightOverNoWeight->SetMinimum(0.9);
  hAccVsPtRatioReweightOverNoWeight->SetMaximum(1.1);
  hAccVsPtRatioReweightOverNoWeight->GetXaxis()->SetTitleOffset(1.1);
  hAccVsPtRatioReweightOverNoWeight->GetYaxis()->SetTitleOffset(1.85);
  
  hAccVsPtRatioReweightOverNoWeight->SetLineWidth(2);
  hAccVsPtRatioReweightOverNoWeight->SetLineColor(2);
  hAccVsPtRatioReweightOverNoWeight->SetMarkerSize(0.5);
  hAccVsPtRatioReweightOverNoWeight->SetMarkerStyle(21);
  hAccVsPtRatioReweightOverNoWeight->SetMarkerColor(2);
  hAccVsPtRatioReweightOverNoWeight->Draw();

  hAccVsPtRatioLowOverNoWeight->SetLineWidth(2);
  hAccVsPtRatioLowOverNoWeight->SetLineColor(3);
  hAccVsPtRatioLowOverNoWeight->SetMarkerSize(0.5);
  hAccVsPtRatioLowOverNoWeight->SetMarkerStyle(21);
  hAccVsPtRatioLowOverNoWeight->SetMarkerColor(3);
  hAccVsPtRatioLowOverNoWeight->Draw("same");

  hAccVsPtRatioHighOverNoWeight->SetLineWidth(2);
  hAccVsPtRatioHighOverNoWeight->SetLineColor(4);
  hAccVsPtRatioHighOverNoWeight->SetMarkerSize(0.5);
  hAccVsPtRatioHighOverNoWeight->SetMarkerStyle(21);
  hAccVsPtRatioHighOverNoWeight->SetMarkerColor(4);
  hAccVsPtRatioHighOverNoWeight->Draw("same");


  for (int i=1;i<=40;i++){
    hAccVsPtRatioReweightOverNoWeight->SetBinError(i,0.);
    hAccVsPtRatioLowOverNoWeight->SetBinError(i,0.);
    hAccVsPtRatioHighOverNoWeight->SetBinError(i,0.);
  
  }
  
  TLegend *legRatioAccVsPt=new TLegend(0.2383901,0.6608392,0.7972136,0.7706294,"");
  legRatioAccVsPt->SetBorderSize(0);
  legRatioAccVsPt->SetFillStyle(0);
  legRatioAccVsPt->SetTextSize(0.045);

  TLegendEntry *entRatioReweightAccVsPt=legRatioAccVsPt->AddEntry(hAccVsPtRatioReweightOverNoWeight," reweight","P");
  entRatioReweightAccVsPt->SetTextColor(2);
  TLegendEntry *entRatioLowAccVsPt=legRatioAccVsPt->AddEntry(hAccVsPtRatioLowOverNoWeight," reweight y up 40%","P");
  entRatioLowAccVsPt->SetTextColor(3);
  TLegendEntry *entRatioHighAccVsPt=legRatioAccVsPt->AddEntry(hAccVsPtRatioHighOverNoWeight," reweight y down 40%","P");
  entRatioHighAccVsPt->SetTextColor(4);

  legRatioAccVsPt->Draw();
  canvasAccVsPt->SaveAs("Plots/canvasAccVsPt.eps");

}