{
//=========Macro generated from canvas: canvasSigma/canvasSigma
//=========  (Mon Mar 30 15:32:09 2015) by ROOT version5.32/00
   TCanvas *canvasSigma = new TCanvas("canvasSigma", "canvasSigma",0,0,1150,500);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   canvasSigma->Range(-1.989924,-0.2917772,25.49622,2.212202);
   canvasSigma->SetFillColor(0);
   canvasSigma->SetBorderMode(0);
   canvasSigma->SetBorderSize(2);
   canvasSigma->SetLogy();
   canvasSigma->SetTickx(1);
   canvasSigma->SetTicky(1);
   canvasSigma->SetLeftMargin(0.1451613);
   canvasSigma->SetRightMargin(0.05443548);
   canvasSigma->SetTopMargin(0.005);
   canvasSigma->SetBottomMargin(0.1165254);
   canvasSigma->SetFrameFillStyle(0);
   canvasSigma->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: p_0_0
   TPad *p_0_0 = new TPad("p_0_0", "p_0_0",0,0,0.3658157,0.9491115);
   p_0_0->Draw();
   p_0_0->cd();
   p_0_0->Range(-12.2619,-0.8347859,65,2.501188);
   p_0_0->SetFillColor(0);
   p_0_0->SetBorderMode(0);
   p_0_0->SetBorderSize(2);
   p_0_0->SetLogy();
   p_0_0->SetTickx(1);
   p_0_0->SetTicky(1);
   p_0_0->SetLeftMargin(0.16);
   p_0_0->SetRightMargin(0);
   p_0_0->SetTopMargin(0.06);
   p_0_0->SetBottomMargin(0.16);
   p_0_0->SetFrameFillStyle(0);
   p_0_0->SetFrameBorderMode(0);
   p_0_0->SetFrameFillStyle(0);
   p_0_0->SetFrameBorderMode(0);
   
   TH2F *hempty__1 = new TH2F("hempty__1","",10,0.1,65,10,0.5,200);
   hempty__1->SetMinimum(0.5);
   hempty__1->SetMaximum(200);
   hempty__1->SetDirectory(0);
   hempty__1->SetStats(0);
   hempty__1->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   hempty__1->GetXaxis()->CenterTitle(true);
   hempty__1->GetXaxis()->SetLabelFont(42);
   hempty__1->GetXaxis()->SetLabelSize(0.06);
   hempty__1->GetXaxis()->SetTitleSize(0.07);
   hempty__1->GetXaxis()->SetTitleFont(42);
   hempty__1->GetYaxis()->SetTitle("d#sigma / dp_{T}( #mub GeV^{-1}c)");
   hempty__1->GetYaxis()->CenterTitle(true);
   hempty__1->GetYaxis()->SetLabelFont(42);
   hempty__1->GetYaxis()->SetLabelSize(0.06);
   hempty__1->GetYaxis()->SetTitleSize(0.07);
   hempty__1->GetYaxis()->SetTitleFont(42);
   hempty__1->Draw("");
   
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(5);
   grae->SetName("gaeBplusReference");
   grae->SetTitle(";p_{T}(GeV/c);d#sigma/dp_{T} (B^{+}) #times A (GeV^{-1}c)");
   grae->SetFillColor(5);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#0066ff");
   grae->SetLineColor(ci);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,12.5,134.5964);
   grae->SetPointError(0,2.5,2.5,30.91426,48.2014);
   grae->SetPoint(1,17.5,36.75549);
   grae->SetPointError(1,2.5,2.5,7.605392,11.1745);
   grae->SetPoint(2,22.5,12.48324);
   grae->SetPointError(2,2.5,2.5,2.342097,3.263897);
   grae->SetPoint(3,27.5,4.959252);
   grae->SetPointError(3,2.5,2.5,0.8540604,1.13726);
   grae->SetPoint(4,45,0.7447245);
   grae->SetPointError(4,15,15,0.112934,0.1408491);
   
   TH1F *Graph_gaeBplusReference1 = new TH1F("Graph_gaeBplusReference1","",100,5,65);
   Graph_gaeBplusReference1->SetMinimum(0.5686114);
   Graph_gaeBplusReference1->SetMaximum(201.0144);
   Graph_gaeBplusReference1->SetDirectory(0);
   Graph_gaeBplusReference1->SetStats(0);
   Graph_gaeBplusReference1->GetXaxis()->SetTitle("p_{T}(GeV/c)");
   Graph_gaeBplusReference1->GetYaxis()->SetTitle("d#sigma/dp_{T} (B^{+}) #times A (GeV^{-1}c)");
   grae->SetHistogram(Graph_gaeBplusReference1);
   
   grae->Draw("2");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("gaeBplusReference");
   grae->SetTitle(";p_{T}(GeV/c);d#sigma/dp_{T} (B^{+}) #times A (GeV^{-1}c)");
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#0066ff");
   grae->SetLineColor(ci);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,12.5,134.5964);
   grae->SetPointError(0,2.5,2.5,30.91426,48.2014);
   grae->SetPoint(1,17.5,36.75549);
   grae->SetPointError(1,2.5,2.5,7.605392,11.1745);
   grae->SetPoint(2,22.5,12.48324);
   grae->SetPointError(2,2.5,2.5,2.342097,3.263897);
   grae->SetPoint(3,27.5,4.959252);
   grae->SetPointError(3,2.5,2.5,0.8540604,1.13726);
   grae->SetPoint(4,45,0.7447245);
   grae->SetPointError(4,15,15,0.112934,0.1408491);
   
   TH1F *Graph_gaeBplusReference2 = new TH1F("Graph_gaeBplusReference2","",100,5,65);
   Graph_gaeBplusReference2->SetMinimum(0.5686114);
   Graph_gaeBplusReference2->SetMaximum(201.0144);
   Graph_gaeBplusReference2->SetDirectory(0);
   Graph_gaeBplusReference2->SetStats(0);
   Graph_gaeBplusReference2->GetXaxis()->SetTitle("p_{T}(GeV/c)");
   Graph_gaeBplusReference2->GetYaxis()->SetTitle("d#sigma/dp_{T} (B^{+}) #times A (GeV^{-1}c)");
   grae->SetHistogram(Graph_gaeBplusReference2);
   
   grae->Draw("2");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("Graph");
   grae->SetTitle("Sigma stat uncertainty from pPb");
   grae->SetFillStyle(0);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,12.5,152.3892);
   grae->SetPointError(0,2.5,2.5,10.85708,10.85708);
   grae->SetPoint(1,17.5,44.66065);
   grae->SetPointError(1,2.5,2.5,3.688471,3.688471);
   grae->SetPoint(2,22.5,11.71521);
   grae->SetPointError(2,2.5,2.5,1.536059,1.536059);
   grae->SetPoint(3,27.5,4.391111);
   grae->SetPointError(3,2.5,2.5,0.9031261,0.9031261);
   grae->SetPoint(4,45,0.8994605);
   grae->SetPointError(4,15,15,0.1468206,0.1468206);
   
   TH1F *Graph_Graph3 = new TH1F("Graph_Graph3","Sigma stat uncertainty from pPb",100,5,65);
   Graph_Graph3->SetMinimum(0.6773758);
   Graph_Graph3->SetMaximum(179.4957);
   Graph_Graph3->SetDirectory(0);
   Graph_Graph3->SetStats(0);
   grae->SetHistogram(Graph_Graph3);
   
   grae->Draw("ep");
   
   grae = new TGraphAsymmErrors(5);
   grae->SetName("gSigmasyst");
   grae->SetTitle("Sigma syst uncertainty from pPb");
   grae->SetFillStyle(0);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,12.5,152.3892);
   grae->SetPointError(0,2.5,2.5,21.79166,21.79166);
   grae->SetPoint(1,17.5,44.66065);
   grae->SetPointError(1,2.5,2.5,6.118509,6.118509);
   grae->SetPoint(2,22.5,11.71521);
   grae->SetPointError(2,2.5,2.5,1.593269,1.593269);
   grae->SetPoint(3,27.5,4.391111);
   grae->SetPointError(3,2.5,2.5,0.5884089,0.5884089);
   grae->SetPoint(4,45,0.8994605);
   grae->SetPointError(4,15,15,0.1205277,0.1205277);
   
   TH1F *Graph_gSigmasyst4 = new TH1F("Graph_gSigmasyst4","Sigma syst uncertainty from pPb",100,5,65);
   Graph_gSigmasyst4->SetMinimum(0.7010395);
   Graph_gSigmasyst4->SetMaximum(191.5211);
   Graph_gSigmasyst4->SetDirectory(0);
   Graph_gSigmasyst4->SetStats(0);
   grae->SetHistogram(Graph_gSigmasyst4);
   
   grae->Draw("2");
   TBox *box = new TBox(3,0.9532453,7,1.046755);
   box->Draw();
   
   TLegend *leg = new TLegend(0.55,0.63,0.85,0.8,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.06);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph","pPb","pf");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("gaeBplusReference","FONLL pp ref.","f");
   entry->SetFillColor(5);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#0066ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   TLatex *   tex = new TLatex(0.6,0.86,"CMS");
tex->SetNDC();
   tex->SetTextSize(0.07);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.39,0.95,"34.6 nb^{-1} (pPb 5.02 TeV)");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.86,0.86,"B^{+}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
   p_0_0->Modified();
   canvasSigma->cd();
  
// ------------>Primitives in pad: p_1_0
   p_1_0 = new TPad("p_1_0", "p_1_0",0.3658157,0,0.6731009,0.9491115);
   p_1_0->Draw();
   p_1_0->cd();
   p_1_0->Range(0.1,-0.8347859,65,2.501188);
   p_1_0->SetFillColor(0);
   p_1_0->SetBorderMode(0);
   p_1_0->SetBorderSize(2);
   p_1_0->SetLogy();
   p_1_0->SetTickx(1);
   p_1_0->SetTicky(1);
   p_1_0->SetLeftMargin(0);
   p_1_0->SetRightMargin(0);
   p_1_0->SetTopMargin(0.06);
   p_1_0->SetBottomMargin(0.16);
   p_1_0->SetFrameFillStyle(0);
   p_1_0->SetFrameBorderMode(0);
   p_1_0->SetFrameFillStyle(0);
   p_1_0->SetFrameBorderMode(0);
   
   TH2F *hempty__2 = new TH2F("hempty__2","",10,0.1,65,10,0.5,200);
   hempty__2->SetMinimum(0.5);
   hempty__2->SetMaximum(200);
   hempty__2->SetDirectory(0);
   hempty__2->SetStats(0);
   hempty__2->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   hempty__2->GetXaxis()->CenterTitle(true);
   hempty__2->GetXaxis()->SetLabelFont(42);
   hempty__2->GetXaxis()->SetLabelOffset(0.0001);
   hempty__2->GetXaxis()->SetLabelSize(0.07142867);
   hempty__2->GetXaxis()->SetTitleSize(0.08333346);
   hempty__2->GetXaxis()->SetTitleOffset(0.8);
   hempty__2->GetXaxis()->SetTitleFont(42);
   hempty__2->GetYaxis()->SetTitle("d#sigma / dp_{T}( #mub GeV^{-1}c)");
   hempty__2->GetYaxis()->CenterTitle(true);
   hempty__2->GetYaxis()->SetLabelFont(42);
   hempty__2->GetYaxis()->SetLabelSize(0.07142867);
   hempty__2->GetYaxis()->SetTitleSize(0.08333346);
   hempty__2->GetYaxis()->SetTitleFont(42);
   hempty__2->Draw("");
   
   grae = new TGraphAsymmErrors(3);
   grae->SetName("gaeBzeroReference");
   grae->SetTitle(";p_{T}(GeV/c);d#sigma(B^{+} full chain)/dp_{T} #times A (GeV^{-1}c)");
   grae->SetFillColor(5);

   ci = TColor::GetColor("#0066ff");
   grae->SetLineColor(ci);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,12.5,134.5964);
   grae->SetPointError(0,2.5,2.5,30.91426,48.2014);
   grae->SetPoint(1,17.5,36.75549);
   grae->SetPointError(1,2.5,2.5,7.605392,11.1745);
   grae->SetPoint(2,40,2.738855);
   grae->SetPointError(2,20,20,0.4842202,0.6557813);
   
   TH1F *Graph_gaeBzeroReference5 = new TH1F("Graph_gaeBzeroReference5","",100,5,65);
   Graph_gaeBzeroReference5->SetMinimum(2.029172);
   Graph_gaeBzeroReference5->SetMaximum(200.8521);
   Graph_gaeBzeroReference5->SetDirectory(0);
   Graph_gaeBzeroReference5->SetStats(0);
   Graph_gaeBzeroReference5->GetXaxis()->SetTitle("p_{T}(GeV/c)");
   Graph_gaeBzeroReference5->GetYaxis()->SetTitle("d#sigma(B^{+} full chain)/dp_{T} #times A (GeV^{-1}c)");
   grae->SetHistogram(Graph_gaeBzeroReference5);
   
   grae->Draw("2");
   
   grae = new TGraphAsymmErrors(3);
   grae->SetName("gaeBzeroReference");
   grae->SetTitle(";p_{T}(GeV/c);d#sigma(B^{+} full chain)/dp_{T} #times A (GeV^{-1}c)");
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#0066ff");
   grae->SetLineColor(ci);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,12.5,134.5964);
   grae->SetPointError(0,2.5,2.5,30.91426,48.2014);
   grae->SetPoint(1,17.5,36.75549);
   grae->SetPointError(1,2.5,2.5,7.605392,11.1745);
   grae->SetPoint(2,40,2.738855);
   grae->SetPointError(2,20,20,0.4842202,0.6557813);
   
   TH1F *Graph_gaeBzeroReference6 = new TH1F("Graph_gaeBzeroReference6","",100,5,65);
   Graph_gaeBzeroReference6->SetMinimum(2.029172);
   Graph_gaeBzeroReference6->SetMaximum(200.8521);
   Graph_gaeBzeroReference6->SetDirectory(0);
   Graph_gaeBzeroReference6->SetStats(0);
   Graph_gaeBzeroReference6->GetXaxis()->SetTitle("p_{T}(GeV/c)");
   Graph_gaeBzeroReference6->GetYaxis()->SetTitle("d#sigma(B^{+} full chain)/dp_{T} #times A (GeV^{-1}c)");
   grae->SetHistogram(Graph_gaeBzeroReference6);
   
   grae->Draw("2");
   
   grae = new TGraphAsymmErrors(3);
   grae->SetName("Graph");
   grae->SetTitle("Sigma stat uncertainty from pPb");
   grae->SetFillStyle(0);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,12.5,136.1234);
   grae->SetPointError(0,2.5,2.5,20.58441,20.58441);
   grae->SetPoint(1,17.5,31.16716);
   grae->SetPointError(1,2.5,2.5,5.614183,5.614183);
   grae->SetPoint(2,40,2.924694);
   grae->SetPointError(2,20,20,0.4021059,0.4021059);
   
   TH1F *Graph_Graph7 = new TH1F("Graph_Graph7","Sigma stat uncertainty from pPb",100,5,65);
   Graph_Graph7->SetMinimum(2.27033);
   Graph_Graph7->SetMaximum(172.1263);
   Graph_Graph7->SetDirectory(0);
   Graph_Graph7->SetStats(0);
   grae->SetHistogram(Graph_Graph7);
   
   grae->Draw("ep");
   
   grae = new TGraphAsymmErrors(3);
   grae->SetName("gSigmasyst");
   grae->SetTitle("Sigma syst uncertainty from pPb");
   grae->SetFillStyle(0);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,12.5,136.1234);
   grae->SetPointError(0,2.5,2.5,24.22996,24.22996);
   grae->SetPoint(1,17.5,31.16716);
   grae->SetPointError(1,2.5,2.5,5.423085,5.423085);
   grae->SetPoint(2,40,2.924694);
   grae->SetPointError(2,20,20,0.5030474,0.5030474);
   
   TH1F *Graph_gSigmasyst8 = new TH1F("Graph_gSigmasyst8","Sigma syst uncertainty from pPb",100,5,65);
   Graph_gSigmasyst8->SetMinimum(2.179482);
   Graph_gSigmasyst8->SetMaximum(176.1465);
   Graph_gSigmasyst8->SetDirectory(0);
   Graph_gSigmasyst8->SetStats(0);
   grae->SetHistogram(Graph_gSigmasyst8);
   
   grae->Draw("2");
   box = new TBox(3,0.9421986,7,1.057801);
   box->Draw();
      tex = new TLatex(0.86,0.86,"B^{0}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.07142867);
   tex->SetLineWidth(2);
   tex->Draw();
   p_1_0->Modified();
   canvasSigma->cd();
  
// ------------>Primitives in pad: p_2_0
   p_2_0 = new TPad("p_2_0", "p_2_0",0.6731009,0,1,0.9491115);
   p_2_0->Draw();
   p_2_0->cd();
   p_2_0->Range(0.1,-0.8347859,69.14255,2.501188);
   p_2_0->SetFillColor(0);
   p_2_0->SetBorderMode(0);
   p_2_0->SetBorderSize(2);
   p_2_0->SetLogy();
   p_2_0->SetTickx(1);
   p_2_0->SetTicky(1);
   p_2_0->SetLeftMargin(0);
   p_2_0->SetRightMargin(0.06);
   p_2_0->SetTopMargin(0.06);
   p_2_0->SetBottomMargin(0.16);
   p_2_0->SetFrameFillStyle(0);
   p_2_0->SetFrameBorderMode(0);
   p_2_0->SetFrameFillStyle(0);
   p_2_0->SetFrameBorderMode(0);
   
   TH2F *hempty__3 = new TH2F("hempty__3","",10,0.1,65,10,0.5,200);
   hempty__3->SetMinimum(0.5);
   hempty__3->SetMaximum(200);
   hempty__3->SetDirectory(0);
   hempty__3->SetStats(0);
   hempty__3->GetXaxis()->SetTitle("p_{T} (GeV/c)");
   hempty__3->GetXaxis()->CenterTitle(true);
   hempty__3->GetXaxis()->SetLabelFont(42);
   hempty__3->GetXaxis()->SetLabelOffset(0.0005);
   hempty__3->GetXaxis()->SetLabelSize(0.06714294);
   hempty__3->GetXaxis()->SetTitleSize(0.07833343);
   hempty__3->GetXaxis()->SetTitleOffset(0.85);
   hempty__3->GetXaxis()->SetTitleFont(42);
   hempty__3->GetYaxis()->SetTitle("d#sigma / dp_{T}( #mub GeV^{-1}c)");
   hempty__3->GetYaxis()->CenterTitle(true);
   hempty__3->GetYaxis()->SetLabelFont(42);
   hempty__3->GetYaxis()->SetLabelSize(0.06714294);
   hempty__3->GetYaxis()->SetTitleSize(0.07833343);
   hempty__3->GetYaxis()->SetTitleFont(42);
   hempty__3->Draw("");
   
   grae = new TGraphAsymmErrors(1);
   grae->SetName("gaeBsReference");
   grae->SetTitle(";p_{T}(GeV/c);d#sigma(B^{+} full chain)/dp_{T} #times A (GeV^{-1}c)");
   grae->SetFillColor(5);

   ci = TColor::GetColor("#0066ff");
   grae->SetLineColor(ci);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,35,5.060496);
   grae->SetPointError(0,25,25,1.110052,1.692101);
   
   TH1F *Graph_gaeBsReference9 = new TH1F("Graph_gaeBsReference9","",100,5,65);
   Graph_gaeBsReference9->SetMinimum(3.670228);
   Graph_gaeBsReference9->SetMaximum(7.032812);
   Graph_gaeBsReference9->SetDirectory(0);
   Graph_gaeBsReference9->SetStats(0);
   Graph_gaeBsReference9->GetXaxis()->SetTitle("p_{T}(GeV/c)");
   Graph_gaeBsReference9->GetYaxis()->SetTitle("d#sigma(B^{+} full chain)/dp_{T} #times A (GeV^{-1}c)");
   grae->SetHistogram(Graph_gaeBsReference9);
   
   grae->Draw("2");
   
   grae = new TGraphAsymmErrors(1);
   grae->SetName("gaeBsReference");
   grae->SetTitle(";p_{T}(GeV/c);d#sigma(B^{+} full chain)/dp_{T} #times A (GeV^{-1}c)");
   grae->SetFillStyle(0);

   ci = TColor::GetColor("#0066ff");
   grae->SetLineColor(ci);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,35,5.060496);
   grae->SetPointError(0,25,25,1.110052,1.692101);
   
   TH1F *Graph_gaeBsReference10 = new TH1F("Graph_gaeBsReference10","",100,5,65);
   Graph_gaeBsReference10->SetMinimum(3.670228);
   Graph_gaeBsReference10->SetMaximum(7.032812);
   Graph_gaeBsReference10->SetDirectory(0);
   Graph_gaeBsReference10->SetStats(0);
   Graph_gaeBsReference10->GetXaxis()->SetTitle("p_{T}(GeV/c)");
   Graph_gaeBsReference10->GetYaxis()->SetTitle("d#sigma(B^{+} full chain)/dp_{T} #times A (GeV^{-1}c)");
   grae->SetHistogram(Graph_gaeBsReference10);
   
   grae->Draw("2");
   
   grae = new TGraphAsymmErrors(1);
   grae->SetName("Graph");
   grae->SetTitle("Sigma stat uncertainty from pPb");
   grae->SetFillStyle(0);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,35,4.812462);
   grae->SetPointError(0,25,25,0.9525294,0.9525294);
   
   TH1F *Graph_Graph11 = new TH1F("Graph_Graph11","Sigma stat uncertainty from pPb",100,5,65);
   Graph_Graph11->SetMinimum(3.669427);
   Graph_Graph11->SetMaximum(5.955498);
   Graph_Graph11->SetDirectory(0);
   Graph_Graph11->SetStats(0);
   grae->SetHistogram(Graph_Graph11);
   
   grae->Draw("ep");
   
   grae = new TGraphAsymmErrors(1);
   grae->SetName("gSigmasyst");
   grae->SetTitle("Sigma syst uncertainty from pPb");
   grae->SetFillStyle(0);
   grae->SetMarkerStyle(21);
   grae->SetPoint(0,35,4.812462);
   grae->SetPointError(0,25,25,1.020242,1.020242);
   
   TH1F *Graph_gSigmasyst12 = new TH1F("Graph_gSigmasyst12","Sigma syst uncertainty from pPb",100,5,65);
   Graph_gSigmasyst12->SetMinimum(3.588172);
   Graph_gSigmasyst12->SetMaximum(6.036753);
   Graph_gSigmasyst12->SetDirectory(0);
   Graph_gSigmasyst12->SetStats(0);
   grae->SetHistogram(Graph_gSigmasyst12);
   
   grae->Draw("2");
   box = new TBox(3,0.9080761,7,1.091924);
   box->Draw();
      tex = new TLatex(0.86,0.86,"B_{s}^{0}");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.06714294);
   tex->SetLineWidth(2);
   tex->Draw();
   p_2_0->Modified();
   canvasSigma->cd();
   canvasSigma->Modified();
   canvasSigma->cd();
   canvasSigma->SetSelected(canvasSigma);
}
