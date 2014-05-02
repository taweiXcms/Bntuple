void ComparedNdcutNew(int variationoption=6,const int nBins=4){

  double ptBins[nBins+1];
  
  if(variationoption==1){ ptBins[0]=0.; ptBins[1]=0.125; ptBins[2]=0.250; ptBins[3]=0.375; ptBins[4]=0.500; ptBins[4]=0.625; ptBins[4]=0.750; ptBins[4]=0.875; ptBins[4]=1.;}
  if(variationoption==2){ ptBins[0]=5.; ptBins[1]=7.5; ptBins[2]=10.; ptBins[3]=15.; ptBins[4]=20.; ptBins[5]=30.;   ptBins[6]=40.;  ptBins[7]=50.;  ptBins[8]=100.;    }
  if(variationoption==3){ ptBins[0]=0.9995; ptBins[1]=0.9996; ptBins[2]=0.9997; ptBins[3]=0.9998; ptBins[4]=0.99985; ptBins[5]=0.9999; ptBins[6]=0.99995; ptBins[7]=0.999975; ptBins[8]=1.;}
  if(variationoption==4){ ptBins[0]=0.5; ptBins[1]=2.; ptBins[2]=3.; ptBins[3]=4.; ptBins[4]=5.; ptBins[5]=10.; ptBins[6]=15.; ptBins[7]=20.; ptBins[8]=50.;  }
  if(variationoption==5){ ptBins[0]=10.; ptBins[1]=15.; ptBins[2]=20.; ptBins[3]=25.; ptBins[4]=30.; ptBins[5]=60.;}
  if(variationoption==6){ ptBins[0]=-1.93-0.465; ptBins[1]=-1.0-0.465; ptBins[2]=-0.465; ptBins[3]=1.0-0.465; ptBins[4]=1.93-0.465;}

  
  double binsize1=ptBins[1]-ptBins[0];
  double binsize2=ptBins[2]-ptBins[1];
  double binsize3=ptBins[3]-ptBins[2];
  double binsize4=ptBins[4]-ptBins[3];
  //double binsize5=ptBins[5]-ptBins[4];
  //double binsize6=ptBins[6]-ptBins[5];
  //double binsize7=ptBins[7]-ptBins[6];
  //double binsize8=ptBins[8]-ptBins[7];
  
 
  gROOT->SetStyle("Plain");	
  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0000);
  gStyle->SetPalette(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetOptTitle(0);

  TFile*file0_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step0_isData1.root",variationoption,variationoption));
  TFile*file1_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step1_isData1.root",variationoption,variationoption));
  TFile*file2_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step2_isData1.root",variationoption,variationoption));
  TFile*file3_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step3_isData1.root",variationoption,variationoption));
  //TFile*file4_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step4_isData1.root",variationoption,variationoption));
  //TFile*file5_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step5_isData1.root",variationoption,variationoption));
  //TFile*file6_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step6_isData1.root",variationoption,variationoption));
  //TFile*file7_Data=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step7_isData1.root",variationoption,variationoption));

  
  TFile*file0_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step0_isData0.root",variationoption,variationoption));
  TFile*file1_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step1_isData0.root",variationoption,variationoption));
  TFile*file2_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step2_isData0.root",variationoption,variationoption));
  TFile*file3_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step3_isData0.root",variationoption,variationoption));
  //TFile*file4_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step4_isData0.root",variationoption,variationoption));
  //TFile*file5_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step5_isData0.root",variationoption,variationoption));
  //TFile*file6_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step6_isData0.root",variationoption,variationoption));
  ///TFile*file7_MC=new TFile(Form("ResultsBplus/CutId%d/SigmaBplusCutId%d_Step7_isData0.root",variationoption,variationoption));

  TH1F*hPtYieldBis_Data1=(TH1F*)file0_Data->Get("hPt");
  TH1F*hPtYieldBis_Data2=(TH1F*)file1_Data->Get("hPt");
  TH1F*hPtYieldBis_Data3=(TH1F*)file2_Data->Get("hPt");
  TH1F*hPtYieldBis_Data4=(TH1F*)file3_Data->Get("hPt");
  //TH1F*hPtYieldBis_Data5=(TH1F*)file4_Data->Get("hPt");
  //TH1F*hPtYieldBis_Data6=(TH1F*)file5_Data->Get("hPt");
  //TH1F*hPtYieldBis_Data7=(TH1F*)file6_Data->Get("hPt");
  //TH1F*hPtYieldBis_Data8=(TH1F*)file7_Data->Get("hPt");
  
  TH1F*hPtYieldBis_MC1=(TH1F*)file0_MC->Get("hPt");
  TH1F*hPtYieldBis_MC2=(TH1F*)file1_MC->Get("hPt");
  TH1F*hPtYieldBis_MC3=(TH1F*)file2_MC->Get("hPt");
  TH1F*hPtYieldBis_MC4=(TH1F*)file3_MC->Get("hPt");
  //TH1F*hPtYieldBis_MC5=(TH1F*)file4_MC->Get("hPt");
  //TH1F*hPtYieldBis_MC6=(TH1F*)file5_MC->Get("hPt");
  //TH1F*hPtYieldBis_MC7=(TH1F*)file6_MC->Get("hPt");
  //TH1F*hPtYieldBis_MC8=(TH1F*)file7_MC->Get("hPt");


  hPtYieldBis_Data1->SetName("hPtYieldBis_Data1");
  hPtYieldBis_Data2->SetName("hPtYieldBis_Data2");
  hPtYieldBis_Data3->SetName("hPtYieldBis_Data3");
  hPtYieldBis_Data4->SetName("hPtYieldBis_Data4");
  //hPtYieldBis_Data5->SetName("hPtYieldBis_Data5");
  //hPtYieldBis_Data6->SetName("hPtYieldBis_Data6");
  //hPtYieldBis_Data7->SetName("hPtYieldBis_Data7");
  //hPtYieldBis_Data8->SetName("hPtYieldBis_Data8");

  hPtYieldBis_MC1->SetName("hPtYieldBis_MC1");
  hPtYieldBis_MC2->SetName("hPtYieldBis_MC2");
  hPtYieldBis_MC3->SetName("hPtYieldBis_MC3");
  hPtYieldBis_MC4->SetName("hPtYieldBis_MC4");
  //hPtYieldBis_MC5->SetName("hPtYieldBis_MC5");
  //hPtYieldBis_MC6->SetName("hPtYieldBis_MC6");
  //hPtYieldBis_MC7->SetName("hPtYieldBis_MC7");
  //hPtYieldBis_MC8->SetName("hPtYieldBis_MC8");
  
  TH1D *hPtAll_Data = new TH1D("hPtAll_Data","",nBins,ptBins);  
  
  hPtAll_Data->SetBinContent(1,hPtYieldBis_Data1->GetBinContent(1)/binsize1);
  hPtAll_Data->SetBinContent(2,hPtYieldBis_Data2->GetBinContent(1)/binsize2);
  hPtAll_Data->SetBinContent(3,hPtYieldBis_Data3->GetBinContent(1)/binsize3);
  hPtAll_Data->SetBinContent(4,hPtYieldBis_Data4->GetBinContent(1)/binsize4);
  //hPtAll_Data->SetBinContent(5,hPtYieldBis_Data5->GetBinContent(1)/binsize5);
  //hPtAll_Data->SetBinContent(6,hPtYieldBis_Data6->GetBinContent(1)/binsize6);
  //hPtAll_Data->SetBinContent(7,hPtYieldBis_Data7->GetBinContent(1)/binsize7);
  //hPtAll_Data->SetBinContent(8,hPtYieldBis_Data8->GetBinContent(1)/binsize8);

  hPtAll_Data->SetBinError(1,hPtYieldBis_Data1->GetBinError(1)/binsize1);
  hPtAll_Data->SetBinError(2,hPtYieldBis_Data2->GetBinError(1)/binsize2);
  hPtAll_Data->SetBinError(3,hPtYieldBis_Data3->GetBinError(1)/binsize3);
  hPtAll_Data->SetBinError(4,hPtYieldBis_Data4->GetBinError(1)/binsize4);
  //hPtAll_Data->SetBinError(5,hPtYieldBis_Data5->GetBinError(1)/binsize5);
  //hPtAll_Data->SetBinError(6,hPtYieldBis_Data6->GetBinError(1)/binsize6);
  //hPtAll_Data->SetBinError(7,hPtYieldBis_Data7->GetBinError(1)/binsize7);
  //hPtAll_Data->SetBinError(8,hPtYieldBis_Data8->GetBinError(1)/binsize8);

  TH1D *hPtAll_MC = new TH1D("hPtAll_MC","",nBins,ptBins);  


  hPtAll_MC->SetBinContent(1,hPtYieldBis_MC1->GetBinContent(1)/binsize1);
  hPtAll_MC->SetBinContent(2,hPtYieldBis_MC2->GetBinContent(1)/binsize2);
  hPtAll_MC->SetBinContent(3,hPtYieldBis_MC3->GetBinContent(1)/binsize3);
  hPtAll_MC->SetBinContent(4,hPtYieldBis_MC4->GetBinContent(1)/binsize4);
  //hPtAll_MC->SetBinContent(5,hPtYieldBis_MC5->GetBinContent(1)/binsize5);
  //hPtAll_MC->SetBinContent(6,hPtYieldBis_MC6->GetBinContent(1)/binsize6);
  //hPtAll_MC->SetBinContent(7,hPtYieldBis_MC7->GetBinContent(1)/binsize7);
  //hPtAll_MC->SetBinContent(8,hPtYieldBis_MC8->GetBinContent(1)/binsize8);

  hPtAll_MC->SetBinError(1,hPtYieldBis_MC1->GetBinError(1)/binsize1);
  hPtAll_MC->SetBinError(2,hPtYieldBis_MC2->GetBinError(1)/binsize2);
  hPtAll_MC->SetBinError(3,hPtYieldBis_MC3->GetBinError(1)/binsize3);
  hPtAll_MC->SetBinError(4,hPtYieldBis_MC4->GetBinError(1)/binsize4);
  //hPtAll_MC->SetBinError(5,hPtYieldBis_MC5->GetBinError(1)/binsize5);
  //hPtAll_MC->SetBinError(6,hPtYieldBis_MC6->GetBinError(1)/binsize6);
  //hPtAll_MC->SetBinError(7,hPtYieldBis_MC7->GetBinError(1)/binsize7);
  //hPtAll_MC->SetBinError(8,hPtYieldBis_MC8->GetBinError(1)/binsize8);
  
  hPtAll_Data->SetMinimum(0.01);
  hPtAll_MC->SetMinimum(0.01);
  
  
  hPtAll_Data->Scale(60.); 
  hPtAll_MC->Scale(60.); 
  double normMC = 604./12750.;  
  hPtAll_MC->Scale(normMC); 
  
  TCanvas *canvasVscut=new TCanvas("canvasVscut","canvasVscut",600,500);
  canvasVscut->cd();  
  canvasVscut->cd(1);
  //canvasVscut->SetLogy();

  if(variationoption==1) hPtAll_Data->GetXaxis()->SetTitle("chi2cl");
  if(variationoption==2) hPtAll_Data->GetXaxis()->SetTitle("d0/d0err");
  if(variationoption==3) hPtAll_Data->GetXaxis()->SetTitle("cos(Theta)");
  if(variationoption==4) hPtAll_Data->GetXaxis()->SetTitle("p^{track}_{t}");
  if(variationoption==5) hPtAll_Data->GetXaxis()->SetTitle("p_{t}");
  if(variationoption==6) hPtAll_Data->GetXaxis()->SetTitle("y_{LAB}");

  if(variationoption==1) hPtAll_Data->GetYaxis()->SetTitle("dN^{yield}/d(chi2cl)");
  if(variationoption==2) hPtAll_Data->GetYaxis()->SetTitle("dN^{yield}/d(d0/d0err)");
  if(variationoption==3) hPtAll_Data->GetYaxis()->SetTitle("dN^{yield}/d(cos(Theta))");
  if(variationoption==4) hPtAll_Data->GetYaxis()->SetTitle("dN^{yield}/dp^{track}_{t}");
  if(variationoption==5) hPtAll_Data->GetYaxis()->SetTitle("dN^{yield}/dp_{t}");
  if(variationoption==6) hPtAll_Data->GetYaxis()->SetTitle("dN^{yield}/dy_{LAB}");


  hPtAll_Data->GetXaxis()->SetTitleOffset(1.);
  hPtAll_Data->GetYaxis()->SetTitleOffset(1.1);
  hPtAll_Data->GetXaxis()->SetTitleSize(0.04);
  hPtAll_Data->GetYaxis()->SetTitleSize(0.04);
  hPtAll_Data->GetXaxis()->SetTitleFont(42);
  hPtAll_Data->GetYaxis()->SetTitleFont(42);
  hPtAll_Data->GetXaxis()->SetLabelFont(42);
  hPtAll_Data->GetYaxis()->SetLabelFont(42);
  hPtAll_Data->GetXaxis()->SetLabelSize(0.035);
  hPtAll_Data->GetYaxis()->SetLabelSize(0.035);  
  
  
  
  if(variationoption==4){ 
  hPtAll_Data->GetXaxis()->SetRangeUser(0,55.);
  hPtAll_Data->SetMinimum(0.01);
  hPtAll_Data->SetMaximum(400);
  }
  
  if(variationoption==2){ 
  hPtAll_Data->GetXaxis()->SetRangeUser(0,105.);
  hPtAll_Data->SetMinimum(0.1);
  hPtAll_Data->SetMaximum(200);
  }
  
  hPtAll_Data->SetLineColor(1);
  hPtAll_Data->SetLineWidth(3);
  hPtAll_Data->Draw();
  hPtAll_MC->SetLineColor(2);
  hPtAll_MC->SetLineWidth(3);
  hPtAll_MC->Draw("same");
  
  TLegend *leg = new TLegend(0.4597315,0.6173362,0.8590604,0.7463002,NULL,"brNDC");
  leg->AddEntry(hPtAll_Data,"Data","pl");
  leg->AddEntry(hPtAll_MC,"MC","pl");
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->Draw();
  canvasVscut->SaveAs(Form("Plots/canvasMCDataVscutId%d.pdf",variationoption));
  
  
}
