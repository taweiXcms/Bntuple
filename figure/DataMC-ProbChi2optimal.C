{
//=========Macro generated from canvas: c/
//=========  (Wed Apr 30 10:47:49 2014) by ROOT version5.32/00
   TCanvas *c = new TCanvas("c", "",0,0,600,600);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetLogy();
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   
   TH1D *hData = new TH1D("hData","",20,0,0);
   hData->SetBinContent(21,722);
   hData->SetBinError(21,26.87006);
   hData->SetEntries(722);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *text = ptstats->AddText("hData");
   text->SetTextSize(0.0368);
   text = ptstats->AddText("Entries = 722    ");
   text = ptstats->AddText("Mean  =      0");
   text = ptstats->AddText("RMS   =      0");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   hData->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(hData);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   hData->SetLineColor(ci);
   hData->GetXaxis()->SetTitle("Vertex #chi^{2} Probability");
   hData->GetXaxis()->SetLabelFont(42);
   hData->GetXaxis()->SetLabelSize(0.035);
   hData->GetXaxis()->SetTitleSize(0.035);
   hData->GetXaxis()->SetTitleFont(42);
   hData->GetYaxis()->SetTitle("Entries");
   hData->GetYaxis()->SetLabelFont(42);
   hData->GetYaxis()->SetLabelSize(0.035);
   hData->GetYaxis()->SetTitleSize(0.035);
   hData->GetYaxis()->SetTitleFont(42);
   hData->GetZaxis()->SetLabelFont(42);
   hData->GetZaxis()->SetLabelSize(0.035);
   hData->GetZaxis()->SetTitleSize(0.035);
   hData->GetZaxis()->SetTitleFont(42);
   hData->Draw("");
   
   TH1D *hMC = new TH1D("hMC","",20,0,0);
   hMC->SetBinContent(21,722);
   hMC->SetBinError(21,33.5392);
   hMC->SetEntries(3727);
   hMC->SetFillColor(2);
   hMC->SetFillStyle(3325);
   hMC->SetLineColor(2);
   hMC->SetMarkerStyle(0);
   hMC->GetXaxis()->SetLabelFont(42);
   hMC->GetXaxis()->SetLabelSize(0.035);
   hMC->GetXaxis()->SetTitleSize(0.035);
   hMC->GetXaxis()->SetTitleFont(42);
   hMC->GetYaxis()->SetLabelFont(42);
   hMC->GetYaxis()->SetLabelSize(0.035);
   hMC->GetYaxis()->SetTitleSize(0.035);
   hMC->GetYaxis()->SetTitleFont(42);
   hMC->GetZaxis()->SetLabelFont(42);
   hMC->GetZaxis()->SetLabelSize(0.035);
   hMC->GetZaxis()->SetTitleSize(0.035);
   hMC->GetZaxis()->SetTitleFont(42);
   hMC->Draw("same hist e");
   
   TH1D *hMCBck = new TH1D("hMCBck","",20,0,0);
   hMCBck->SetBinContent(21,181.1129);
   hMCBck->SetBinError(21,32.1854);
   hMCBck->SetEntries(439);

   ci = TColor::GetColor("#00cc00");
   hMCBck->SetFillColor(ci);
   hMCBck->SetFillStyle(3325);

   ci = TColor::GetColor("#00cc00");
   hMCBck->SetLineColor(ci);
   hMCBck->SetMarkerStyle(0);
   hMCBck->GetXaxis()->SetLabelFont(42);
   hMCBck->GetXaxis()->SetLabelSize(0.035);
   hMCBck->GetXaxis()->SetTitleSize(0.035);
   hMCBck->GetXaxis()->SetTitleFont(42);
   hMCBck->GetYaxis()->SetLabelFont(42);
   hMCBck->GetYaxis()->SetLabelSize(0.035);
   hMCBck->GetYaxis()->SetTitleSize(0.035);
   hMCBck->GetYaxis()->SetTitleFont(42);
   hMCBck->GetZaxis()->SetLabelFont(42);
   hMCBck->GetZaxis()->SetLabelSize(0.035);
   hMCBck->GetZaxis()->SetTitleSize(0.035);
   hMCBck->GetZaxis()->SetTitleFont(42);
   hMCBck->Draw("same hist e");
   
   TH1D *hP = new TH1D("hP","",20,0,0);
   hP->SetBinContent(21,110.8699);
   hP->SetBinError(21,32.00539);
   hP->SetEntries(12);
   hP->SetFillColor(4);
   hP->SetFillStyle(3325);
   hP->SetLineColor(4);
   hP->SetMarkerStyle(0);
   hP->GetXaxis()->SetLabelFont(42);
   hP->GetXaxis()->SetLabelSize(0.035);
   hP->GetXaxis()->SetTitleSize(0.035);
   hP->GetXaxis()->SetTitleFont(42);
   hP->GetYaxis()->SetLabelFont(42);
   hP->GetYaxis()->SetLabelSize(0.035);
   hP->GetYaxis()->SetTitleSize(0.035);
   hP->GetYaxis()->SetTitleFont(42);
   hP->GetZaxis()->SetLabelFont(42);
   hP->GetZaxis()->SetLabelSize(0.035);
   hP->GetZaxis()->SetTitleSize(0.035);
   hP->GetZaxis()->SetTitleFont(42);
   hP->Draw("same hist e");
   
   TLegend *leg = new TLegend(0.5,0.7,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(19);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("hData","pPb data","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("hMC","B^{+} signal","f");
   entry->SetFillColor(2);
   entry->SetFillStyle(3325);
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("hMCBck","Non-prompt J/#psi","f");

   ci = TColor::GetColor("#00cc00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3325);

   ci = TColor::GetColor("#00cc00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("hP","Prompt J/#psi","f");
   entry->SetFillColor(4);
   entry->SetFillStyle(3325);
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
