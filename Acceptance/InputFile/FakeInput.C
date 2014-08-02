  const int nBins = 5;
  double ptBins[nBins+1] = {10,15,20,25,30,60};
  
  const int nBinsy = 4;
  double yBins[nBinsy+1] = {-2.4,-1.0,0.,1.0,2.4};


void FakeInput(){
  
  TH1D *hPtMC = new TH1D("hPtMC","",nBins,ptBins);
  TH1D *hPtData = new TH1D("hPtData","",nBins,ptBins);
  
  TH1D *hyMC = new TH1D("hyMC","",nBinsy,yBins);
  TH1D *hyData = new TH1D("hyData","",nBinsy,yBins);
  
  hPtMC->SetBinContent(1,0.15);
  hPtMC->SetBinContent(2,0.052);
  hPtMC->SetBinContent(3,0.02);
  hPtMC->SetBinContent(4,0.008);
  hPtMC->SetBinContent(5,0.002);

  hPtData->SetBinContent(1,0.15);
  hPtData->SetBinContent(2,0.055);
  hPtData->SetBinContent(3,0.022);
  hPtData->SetBinContent(4,0.01);
  hPtData->SetBinContent(5,0.0022);  
  
  hPtMC->SetBinError(1,hPtMC->GetBinContent(1)*0.1);
  hPtMC->SetBinError(2,hPtMC->GetBinContent(2)*0.1);
  hPtMC->SetBinError(3,hPtMC->GetBinContent(3)*0.1);
  hPtMC->SetBinError(4,hPtMC->GetBinContent(4)*0.1);
  hPtMC->SetBinError(5,hPtMC->GetBinContent(5)*0.1);
  
  hPtData->SetBinError(1,hPtData->GetBinContent(1)*0.1);
  hPtData->SetBinError(2,hPtData->GetBinContent(2)*0.1);
  hPtData->SetBinError(3,hPtData->GetBinContent(3)*0.1);
  hPtData->SetBinError(4,hPtData->GetBinContent(4)*0.1);
  hPtData->SetBinError(5,hPtData->GetBinContent(5)*0.1);
  
  
  hyMC->SetBinContent(1,0.4);
  hyMC->SetBinContent(2,0.3);
  hyMC->SetBinContent(3,0.2);
  hyMC->SetBinContent(4,0.1);

  hyData->SetBinContent(1,0.42);
  hyData->SetBinContent(2,0.28);
  hyData->SetBinContent(3,0.18);
  hyData->SetBinContent(4,0.08);
  
  hyMC->SetBinError(1,hyMC->GetBinContent(1)*0.1);
  hyMC->SetBinError(2,hyMC->GetBinContent(2)*0.1);
  hyMC->SetBinError(3,hyMC->GetBinContent(3)*0.1);
  hyMC->SetBinError(4,hyMC->GetBinContent(4)*0.1);
  
  hyData->SetBinError(1,hyData->GetBinContent(1)*0.1);
  hyData->SetBinError(2,hyData->GetBinContent(2)*0.1);
  hyData->SetBinError(3,hyData->GetBinContent(3)*0.1);
  hyData->SetBinError(4,hyData->GetBinContent(4)*0.1);


  hPtMC->Scale(1./hPtMC->Integral());
  hPtData->Scale(1./hPtData->Integral());
  hyMC->Scale(1./hyMC->Integral());
  hyData->Scale(1./hyData->Integral());
  
  cout<<"QUI"<<hPtMC->Integral()<<endl;
  cout<<"QUI"<<hPtData->Integral()<<endl;
  cout<<"QUI"<<hyMC->Integral()<<endl;
  cout<<"QUI"<<hyData->Integral()<<endl;
  

  TH1D*hReweightDataOverMC_Pt=(TH1D*)hPtData->Clone("hReweightDataOverMC_Pt");
  TH1D*hReweightDataOverMC_y=(TH1D*)hyData->Clone("hReweightDataOverMC_y");
  
  hReweightDataOverMC_Pt->Divide(hPtMC);
  hReweightDataOverMC_y->Divide(hyMC);

  TCanvas*c=new TCanvas("c","c",800,500);
  c->Divide(2,2);
  c->cd(1);
  hPtData->Draw();
  c->cd(2);
  hPtMC->Draw();
  c->cd(3);
  hyData->Draw();
  c->cd(4);
  hyMC->Draw();

  c->SaveAs("prova.pdf");
  
  TFile*fout=new TFile("InputFilesMCData.root","recreate");
  fout->cd();
  hPtData->Write();
  hPtMC->Write();
  hyData->Write();
  hyMC->Write();
  hReweightDataOverMC_Pt->Write();
  hReweightDataOverMC_y->Write();


}


void BuildFunctions(){

  TFile*fout=new TFile("InputFilesMCData.root","read");
  TH1D*hReweightDataOverMC_Pt=(TH1D*)fout->Get("hReweightDataOverMC_Pt");
  TH1D*hReweightDataOverMC_y=(TH1D*)fout->Get("hReweightDataOverMC_y");

  
  TF1 *fPt = new TF1("fPt","pol2",10.,70.);
  TF1 *fy = new TF1("fy","pol2",-1.4,1.4);

  TCanvas*canvas=new TCanvas("canvas","canvas",1100,500);
  canvas->Divide(2,1);
  
  canvas->cd(1);
  
  hReweightDataOverMC_Pt->SetMinimum(0);
  hReweightDataOverMC_Pt->SetMaximum(1.5);
  hReweightDataOverMC_Pt->Draw("p");
  hReweightDataOverMC_Pt->SetMarkerStyle(22);
  hReweightDataOverMC_Pt->SetMarkerSize(0.5);
  hReweightDataOverMC_Pt->Fit("fPt");  

  
  canvas->cd(2);
  
  hReweightDataOverMC_y->SetMinimum(0);
  hReweightDataOverMC_y->SetMaximum(1.5);
  hReweightDataOverMC_y->Draw("p");
  hReweightDataOverMC_y->SetMarkerStyle(22);
  hReweightDataOverMC_y->SetMarkerSize(0.5);
  hReweightDataOverMC_y->Fit("fy");  
  
  
  TFile*fout=new TFile("FunctionsReweighting.root","recreate");
  fout->cd();
  hReweightDataOverMC_Pt->Write();
  hReweightDataOverMC_y->Write();
  fPt->Write();
  fy->Write();
}
