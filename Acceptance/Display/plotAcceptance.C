

void plotAcceptance(){

  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);

  TFile*fileoutput=new TFile("../Code/Results/outputBplus.root");
  
  TH1D*hAccVsPt=(TH1D*)fileoutput->Get("hAccVsPt");
  TH1D*hAccVsPtReweight=(TH1D*)fileoutput->Get("hAccVsPtReweight");
  TH1D*hPtAccNumVsPt=(TH1D*)fileoutput->Get("hPtAccNumVsPt");
  TH1D*hPtAccDenVsPt=(TH1D*)fileoutput->Get("hPtAccDenVsPt");
  
  TH1D*hAccVsy=(TH1D*)fileoutput->Get("hAccVsy");
  TH1D*hAccVsyReweight=(TH1D*)fileoutput->Get("hAccVsyReweight");
  TH1D*hPtAccNumVsy=(TH1D*)fileoutput->Get("hPtAccNumVsy");
  TH1D*hAccVsPt=(TH1D*)fileoutput->Get("hAccVsPt");
  
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

  TLegend *legAccVsPt=new TLegend(0.2383901,0.6608392,0.7972136,0.7706294,"");
  legAccVsPt->SetBorderSize(0);
  legAccVsPt->SetFillStyle(0);
  legAccVsPt->SetTextSize(0.045);

  TLegendEntry *entAccVsPt=legAccVsPt->AddEntry(hPtAccNumVsPt," central","P");
  entAccVsPt->SetTextColor(1);
  TLegendEntry *entAccVsPtReweight=legAccVsPt->AddEntry(hPtAccNumVsPtReweight," reweighted","P");
  entAccVsPtReweight->SetTextColor(2);
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
  legAccVsPt->Draw();

  canvasAccVsPt->cd(4);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  TH1D*hAccVsPtRatioWeightOverNoWeight=(TH1D*)hAccVsPtReweight->Clone("hAccVsPtRatioWeightOverNoWeight");
  hAccVsPtRatioWeightOverNoWeight->Divide(hAccVsPt);
  
  hAccVsPtRatioWeightOverNoWeight->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hAccVsPtRatioWeightOverNoWeight->GetYaxis()->SetTitle("Ratio Acceptance Reweight/NoWeight");
  hAccVsPtRatioWeightOverNoWeight->SetMinimum(0.9);
  hAccVsPtRatioWeightOverNoWeight->SetMaximum(1.1);
  hAccVsPtRatioWeightOverNoWeight->GetXaxis()->SetTitleOffset(1.1);
  hAccVsPtRatioWeightOverNoWeight->GetYaxis()->SetTitleOffset(1.85);
  hAccVsPtRatioWeightOverNoWeight->SetLineWidth(2);
  hAccVsPtRatioWeightOverNoWeight->SetLineColor(1);
  hAccVsPtRatioWeightOverNoWeight->SetMarkerSize(0.5);
  hAccVsPtRatioWeightOverNoWeight->SetMarkerStyle(21);
  hAccVsPtRatioWeightOverNoWeight->SetMarkerColor(1);
  hAccVsPtRatioWeightOverNoWeight->Draw();
  
  TLegend *legRatioAccVsPt=new TLegend(0.2383901,0.6608392,0.7972136,0.7706294,"");
  legRatioAccVsPt->SetBorderSize(0);
  legRatioAccVsPt->SetFillStyle(0);
  legRatioAccVsPt->SetTextSize(0.045);

  TLegendEntry *entRatioAccVsPt=legRatioAccVsPt->AddEntry(hAccVsPtRatioWeightOverNoWeight," function","P");
  entRatioAccVsPt->SetTextColor(1);
  legRatioAccVsPt->Draw();
  canvasAccVsPt->SaveAs("Plots/canvasAccVsPt.eps");



  TCanvas*canvasAccVsy=new TCanvas("canvasAccVsy","canvasAccVsy",1000,1200);
  canvasAccVsy->Divide(2,2);
  
  canvasAccVsy->cd(1);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  hPtAccNumVsy->GetXaxis()->SetTitle("y_{LAB}");
  hPtAccNumVsy->GetYaxis()->SetTitle("Numerator");
  hPtAccNumVsy->SetMinimum(0.);
  hPtAccNumVsy->SetMaximum(30000.);
  hPtAccNumVsy->GetXaxis()->SetTitleOffset(1.1);
  hPtAccNumVsy->GetYaxis()->SetTitleOffset(1.85);
  hPtAccNumVsy->SetLineWidth(2);
  hPtAccNumVsy->SetLineColor(1);
  hPtAccNumVsy->SetMarkerSize(0.5);
  hPtAccNumVsy->SetMarkerStyle(21);
  hPtAccNumVsy->SetMarkerColor(1);
  hPtAccNumVsy->Draw();
  hPtAccNumVsyReweight->SetLineWidth(2);
  hPtAccNumVsyReweight->SetLineColor(2);
  hPtAccNumVsyReweight->SetMarkerSize(0.5);
  hPtAccNumVsyReweight->SetMarkerStyle(21);
  hPtAccNumVsyReweight->SetMarkerColor(2);
  hPtAccNumVsyReweight->Draw("SAMES");

  TLegend *legAccVsy=new TLegend(0.2383901,0.6608392,0.7972136,0.7706294,"");
  legAccVsy->SetBorderSize(0);
  legAccVsy->SetFillStyle(0);
  legAccVsy->SetTextSize(0.045);

  TLegendEntry *entAccVsy=legAccVsy->AddEntry(hPtAccNumVsy," central","P");
  entAccVsy->SetTextColor(1);
  TLegendEntry *entAccVsyReweight=legAccVsy->AddEntry(hPtAccNumVsyReweight," reweighted","P");
  entAccVsyReweight->SetTextColor(2);
  legAccVsy->Draw();
  
  canvasAccVsy->cd(2);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  hPtAccDenVsy->GetXaxis()->SetTitle("y_{LAB}");
  hPtAccDenVsy->GetYaxis()->SetTitle("Denumerator");
  hPtAccDenVsy->SetMinimum(0.);
  hPtAccDenVsy->SetMaximum(60000.);
  hPtAccDenVsy->GetXaxis()->SetTitleOffset(1.1);
  hPtAccDenVsy->GetYaxis()->SetTitleOffset(1.85);
  hPtAccDenVsy->SetLineWidth(2);
  hPtAccDenVsy->SetLineColor(1);
  hPtAccDenVsy->SetMarkerSize(0.5);
  hPtAccDenVsy->SetMarkerStyle(21);
  hPtAccDenVsy->SetMarkerColor(1);
  hPtAccDenVsy->Draw();
  hPtAccDenVsyReweight->SetLineWidth(2);
  hPtAccDenVsyReweight->SetLineColor(2);
  hPtAccDenVsyReweight->SetMarkerSize(0.5);
  hPtAccDenVsyReweight->SetMarkerStyle(21);
  hPtAccDenVsyReweight->SetMarkerColor(2);
  hPtAccDenVsyReweight->Draw("SAMES");
  legAccVsy->Draw();

  canvasAccVsy->cd(3);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  
  hAccVsy->GetXaxis()->SetTitle("y_{LAB}");
  hAccVsy->GetYaxis()->SetTitle("Acceptance");
  hAccVsy->SetMinimum(0.);
  hAccVsy->SetMaximum(1.5);
  hAccVsy->GetXaxis()->SetTitleOffset(1.1);
  hAccVsy->GetYaxis()->SetTitleOffset(1.85);
  hAccVsy->SetLineWidth(2);
  hAccVsy->SetLineColor(1);
  hAccVsy->SetMarkerSize(0.5);
  hAccVsy->SetMarkerStyle(21);
  hAccVsy->SetMarkerColor(1);
  hAccVsy->Draw();
  hAccVsyReweight->SetLineWidth(2);
  hAccVsyReweight->SetLineColor(2);
  hAccVsyReweight->SetMarkerSize(0.5);
  hAccVsyReweight->SetMarkerStyle(21);
  hAccVsyReweight->SetMarkerColor(2);
  hAccVsyReweight->Draw("SAMES");
  legAccVsy->Draw();

  canvasAccVsy->cd(4);
  gPad->SetLeftMargin(0.12);
  gPad->SetBottomMargin(0.12);
  gPad->SetTickx();
  gPad->SetTicky();
  TH1D*hAccVsyRatioWeightOverNoWeight=(TH1D*)hAccVsyReweight->Clone("hAccVsyRatioWeightOverNoWeight");
  hAccVsyRatioWeightOverNoWeight->Divide(hAccVsy);
  
  hAccVsyRatioWeightOverNoWeight->GetXaxis()->SetTitle("y_{LAB}");
  hAccVsyRatioWeightOverNoWeight->GetYaxis()->SetTitle("Ratio Acceptance Reweight/NoWeight");
  hAccVsyRatioWeightOverNoWeight->SetMinimum(0.9);
  hAccVsyRatioWeightOverNoWeight->SetMaximum(1.1);
  hAccVsyRatioWeightOverNoWeight->GetXaxis()->SetTitleOffset(1.1);
  hAccVsyRatioWeightOverNoWeight->GetYaxis()->SetTitleOffset(1.85);
  hAccVsyRatioWeightOverNoWeight->SetLineWidth(2);
  hAccVsyRatioWeightOverNoWeight->SetLineColor(1);
  hAccVsyRatioWeightOverNoWeight->SetMarkerSize(0.5);
  hAccVsyRatioWeightOverNoWeight->SetMarkerStyle(21);
  hAccVsyRatioWeightOverNoWeight->SetMarkerColor(1);
  hAccVsyRatioWeightOverNoWeight->Draw();
  
  TLegend *legRatioAccVsy=new TLegend(0.2383901,0.6608392,0.7972136,0.7706294,"");
  legRatioAccVsy->SetBorderSize(0);
  legRatioAccVsy->SetFillStyle(0);
  legRatioAccVsy->SetTextSize(0.045);

  TLegendEntry *entRatioAccVsy=legRatioAccVsy->AddEntry(hAccVsyRatioWeightOverNoWeight," function","P");
  entRatioAccVsy->SetTextColor(1);
  legRatioAccVsy->Draw();
  canvasAccVsy->SaveAs("Plots/canvasAccVsy.eps");

}