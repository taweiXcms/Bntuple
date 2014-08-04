/*

  TString particle="Bs";
  const int nbins=1;
  Double_t xbins[nbins]={35};
  Double_t exl[nbins]={25};
  Double_t yPercSigmapPbSystTotHigh[nbins]={0.089};
  Double_t yPercSigmapPbSystTotLow[nbins]={0.089};

  //Double_t commonErrorP = 0.22; // +0.6/10.4 in quadrature
  //Double_t commonErrorN = 0.24;//  +0.6/10.4 in quadrature
    
  TString particle="Bzero";
  const int nbins=3;
  Double_t xbins[nbins]={12.5,17.5,40};
  Double_t exl[nbins]={2.5,2.5,20};
  Double_t yPercSigmapPbSystTotHigh[nbins]={0.145,0.144,0.144};
  Double_t yPercSigmapPbSystTotLow[nbins]={0.145,0.144,0.144};

  Double_t commonErrorP = TMath::Sqrt(0.0555*0.0555+ (0.7/40.2)*(0.7/40.2));
  Double_t commonErrorN = TMath::Sqrt(0.0555*0.0555+ (0.7/40.2)*(0.7/40.2));


   TString particle="Bplus";
  const int nbins=5;
  Double_t xbins[nbins]={12.5,17.5,22.5,27.5,45.};
  Double_t exl[nbins]={2.5,2.5,2.5,2.5,15.};
  Double_t yPercSigmapPbSystTotHigh[nbins]={0.117,0.116,0.113,0.143,0.120};
  Double_t yPercSigmapPbSystTotLow[nbins]={0.117,0.116,0.113,0.143,0.120};

  Double_t commonErrorP = TMath::Sqrt(0.0445*0.0445+ (0.7/40.2)*(0.7/40.2));
  Double_t commonErrorN = TMath::Sqrt(0.0445*0.0445+ (0.7/40.2)*(0.7/40.2));

*/


TString particle="Bplus";
const int nbinsRFB = 2;
Double_t xbinsRFB[nbinsRFB]={0.5,1.465};
Double_t exlRFB[nbinsRFB]={0.5,0.465};
Double_t yRFBSystTotHighRel[nbinsRFB]= {0.162,0.196};////////////////////////////////////////////////
Double_t yRFBSystTotLowRel[nbinsRFB]= {0.162,0.196};//////////////////////
const int nbins = 5;
Double_t xbins[nbins]={-2.4,-1.465,-0.5,0.5,1.465};
Double_t exl[nbins]={0.465,0.465,0.5,0.5,0.465};
//Double_t yPercSigmapPbSystTotHigh[nbins]={0.145,0.144,0.144};////////////////////////////////////////////////
//Double_t yPercSigmapPbSystTotLow[nbins]={0.145,0.144,0.144};/////////////////////////////////////////////////
Double_t yPercSigmapPbSystTotHigh[nbins]={0.,0.185,0.158,0.133,0.143};////////////////////////////////////////////////
Double_t yPercSigmapPbSystTotLow[nbins]={0.,0.185,0.158,0.133,0.143};//////////////////////

Double_t commonErrorP = 0.0555 ;
Double_t commonErrorN = 0.0555  ;
Double_t tagandprobcorrection[nbins]={1.,1.1742287,1.1346129,1.0915380,1.0972000};

void NuclearModificationY(){

  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  
  TFile*filePPReference=new TFile(Form("../fonll/output%sY.root",particle.Data()));  
  TGraphAsymmErrors*gaeBplusReference=(TGraphAsymmErrors*)filePPReference->Get(Form("gaeSigmaDecay%s",particle.Data()));
  gaeBplusReference->SetName(Form("gae%sReference",particle.Data()));
  
//  TFile*filepPb=new TFile(Form("Results%sY/Sigma%s.root",particle.Data(),particle.Data()));
  TFile*filepPb=new TFile(Form("Results%s_y/Sigma%s.root",particle.Data(),particle.Data()));
  TH1F*hSigmapPbStat=(TH1F*)filepPb->Get("hPtSigma");  
  
  
    double scalingfactor=1e-6;
  
  
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
  
    gaeBplusReference->SetPoint(i,xvalue,yvalue*scalingfactor);
    gaeBplusReference->SetPointEYhigh(i,yerrorhigh*scalingfactor);
    gaeBplusReference->SetPointEYlow(i,yerrorlow*scalingfactor);

  } 

  
  
  for (int i=0;i<nbins;i++){
    hSigmapPbStat->SetBinContent(i+1,(1./tagandprobcorrection[i])*(hSigmapPbStat->GetBinContent(i+1)));
    hSigmapPbStat->SetBinError(i+1,(1./tagandprobcorrection[i])*(hSigmapPbStat->GetBinError(i+1)));
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

  Double_t yRFB[nbinsRFB];
  Double_t yRFBStat[nbinsRFB];
Double_t yRFBSystTotHigh[nbinsRFB];////////////////////////////////////////////////
Double_t yRFBSystTotLow[nbinsRFB];

  double x,y;
  cout<<"hello"<<endl;
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
    yPercRpAsystFONLLhigh[i]=(yPercPPsystFONLLlow[i]/(1-yPercPPsystFONLLlow[i]));
    yPercRpAsystFONLLlow[i]=(yPercPPsystFONLLhigh[i]/(1+yPercPPsystFONLLhigh[i]));
    yRpAsystFONLLhigh[i]=yPercRpAsystFONLLhigh[i]*yRpA[i];
    yRpAsystFONLLlow[i]=yPercRpAsystFONLLlow[i]*yRpA[i];
    yRpPbSystTotHigh[i]=yPercSigmapPbSystTotHigh[i]*yRpA[i];
    yRpPbSystTotLow[i]=yPercSigmapPbSystTotLow[i]*yRpA[i];
    //cout<<yRpPbSystTotLow[i]<<endl;
  }

  //RFB stuff
  //central value
 yRFB[0] =  ySigmapPb[3]/ySigmapPb[2];
 yRFB[1] =  ySigmapPb[4]/ySigmapPb[1];
 //Stat.
 yRFBStat[0] =  yRFB[0]*sqrt(pow(ySigmapPbStat[2]/ySigmapPb[2],2)+pow(ySigmapPbStat[3]/ySigmapPb[3],2));
 yRFBStat[1] =  yRFB[1]*sqrt(pow(ySigmapPbStat[4]/ySigmapPb[4],2)+pow(ySigmapPbStat[1]/ySigmapPb[1],2));
 //Syst.

  yRFBSystTotHigh[0] = yRFB[0]*yRFBSystTotHighRel[0];
  yRFBSystTotLow[0] = yRFB[0]*yRFBSystTotLowRel[0];////////////////////////////////////////////////
  yRFBSystTotHigh[1] = yRFB[1]*yRFBSystTotHighRel[1];
  yRFBSystTotLow[1] = yRFB[1]*yRFBSystTotLowRel[1];
  
cout<<yRFBStat[0]<<endl;
cout<<yRFBStat[1]<<endl;
  
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
  
  TH2F* hempty=new TH2F("hempty","",10,-3.5,2.5,10,0,650.);  
  hempty->GetXaxis()->SetTitle("y_{CM}");
  //if(particle=="Bplus") hempty->GetYaxis()->SetTitle("d#sigma / dp_{T} (B^{+}) (pb GeV^{-1}c)");
  //if(particle=="Bzero") hempty->GetYaxis()->SetTitle("d#sigma / dp_{T} (B^{0}) (pb GeV^{-1}c)");
  //if(particle=="Bs") hempty->GetYaxis()->SetTitle("d#sigma / dp_{T} (B_{s}) (pb GeV^{-1}c)");
  
    hempty->GetXaxis()->CenterTitle();
    hempty->GetYaxis()->CenterTitle();

  
  hempty->GetYaxis()->SetTitle("d#sigma / dy_{CM}(#mub GeV^{-1}c)");
  

  hempty->GetXaxis()->SetTitleOffset(1.);
  hempty->GetYaxis()->SetTitleOffset(1.32);
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
  gaeBplusReference->SetMarkerStyle(25);  
  gaeBplusReference->SetFillColor(5);
  gaeBplusReference->SetFillStyle(1001);
  gaeBplusReference->SetLineColor(5);
  gaeBplusReference->SetLineWidth(1);
  
  
  gSigmastat->SetMarkerColor(1);
  gSigmastat->SetLineColor(1);
  gSigmastat->SetLineWidth(2);   
  gSigmastat->SetMarkerStyle(21);
  gSigmastat->SetMarkerColor(1);

  gaeBplusReference->Draw("2psame");
  gSigmastat->SetFillColor(0);
  gSigmastat->Draw("epsame");
  
  

 
  //TLegend *legendSigma=new TLegend(0.5745968,0.564482,0.8729839,0.7378436,"");
  TLegend *legendSigma=new TLegend(0.233871,0.6419492,0.5322581,0.815678,"");
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
  
  TLegendEntry *ent_Sigmapp=legendSigma->AddEntry(gaeBplusReference,"FONLL pp ref.","fp");
  ent_Sigmapp->SetTextFont(42);
  ent_Sigmapp->SetLineColor(5);
  ent_Sigmapp->SetMarkerColor(1);
  ent_Sigmapp->SetMarkerStyle(25);
  legendSigma->Draw("psame");



  

  
  
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


    
  TLatex * tlatex1=new TLatex(0.1612903,0.8625793,"CMS Preliminary     pPb #sqrt{s_{NN}}= 5.02 TeV");
  tlatex1->SetNDC();
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.045);
  tlatex1->Draw();
  

  TString mypar;
  if(particle=="Bplus") mypar="B^{+}";
  if(particle=="Bzero") mypar="B^{0}";
  if(particle=="Bs") mypar="B_{s}";
  
  
  TLatex * tlatexlumi=new TLatex(0.671371,0.7801268,"L = 34.8 nb^{-1}");
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
  

  canvasSigma->SaveAs(Form("Results%s_y/canvasSigma%s.pdf",particle.Data(),particle.Data()));  
  
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

/*

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

  TH2F* hempty=new TH2F("hempty","",4,-2.7,2.7,10.,0.,3.5);  
  hempty->GetXaxis()->SetTitle("y_{CM}");
  if(particle=="Bplus") hempty->GetYaxis()->SetTitle("R^{FONLL}_{pA}  (B^{+})");
  if(particle=="Bzero") hempty->GetYaxis()->SetTitle("R^{FONLL}_{pA}  (B^{0})");
  if(particle=="Bs") hempty->GetYaxis()->SetTitle("R^{FONLL}_{pA}  (B_{s})");
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
  hempty->SetMaximum(3);
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
  

  TBox *b = new TBox(-2.5,1-commonErrorN,-2.1,1+commonErrorP);
  b->SetLineColor(1);
  b->SetFillColor(kGray);
  b->Draw();

  TLegendEntry *ent_RpAstat=legendRpA->AddEntry(gRpAstat,"R^{FONLL}_{pA}  stat unc","P");
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
  
  TLatex * tlatex2=new TLatex(0.5564516,0.8498943,"pPb #sqrt{s_{NN}}= 5.02 TeV");
  tlatex2->SetNDC();
  tlatex2->SetTextColor(1);
  tlatex2->SetTextFont(42);
  tlatex2->SetTextSize(0.04);
  tlatex2->Draw();

  TLatex * tlatex2=new TLatex(0.5564516,0.8,"L = 34.8 nb^{-1}");
  tlatex2->SetNDC();
  tlatex2->SetTextColor(1);
  tlatex2->SetTextFont(42);
  tlatex2->SetTextSize(0.04);
  tlatex2->Draw();

*/

  TCanvas *canvasRFB=new TCanvas("canvasRFB","canvasRFB",500,500);   
  canvasRFB->cd();
  canvasRFB->Range(-1.989924,-0.2917772,25.49622,2.212202);
  canvasRFB->SetFillColor(0);
  canvasRFB->SetBorderMode(0);
  canvasRFB->SetBorderSize(2);
  canvasRFB->SetLeftMargin(0.1451613);
  canvasRFB->SetRightMargin(0.05443548);
  canvasRFB->SetTopMargin(0.08474576);
  canvasRFB->SetBottomMargin(0.1165254);
  canvasRFB->SetFrameBorderMode(0);
  canvasRFB->SetFrameBorderMode(0);
 
  TLegend *legendRFB=new TLegend(0.2560484,0.6490486,0.5483871,0.7716702,"");
  legendRFB->SetBorderSize(0);
  legendRFB->SetLineColor(0);
  legendRFB->SetFillColor(0);
  legendRFB->SetFillStyle(1001);
  legendRFB->SetTextFont(42);
  legendRFB->SetTextSize(0.045);

  TH2F* hempty=new TH2F("hempty","",4,-0.1,2.,10.,0.,2.5);  
  hempty->GetXaxis()->SetTitle("|y_{CM}|");
 //  if(particle=="Bplus") hempty->GetYaxis()->SetTitle("R^{FONLL}_{pA}  (B^{+})");
//   if(particle=="Bzero") hempty->GetYaxis()->SetTitle("R^{FONLL}_{pA}  (B^{0})");
  hempty->GetYaxis()->SetTitle("R_{FB}");
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
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->SetMaximum(3);
  hempty->SetMinimum(0.);
  hempty->Draw();
  legendRFB->Draw();

  TGraphAsymmErrors *gRFBsyst = new TGraphAsymmErrors(nbinsRFB,xbinsRFB,yRFB,exlRFB,exlRFB,yRFBSystTotLow,yRFBSystTotHigh);
  gRFBsyst->SetTitle("gRFBsyst");
   gRFBsyst->SetName("gRFBsyst");
  gRFBsyst->SetMarkerColor(4);
  gRFBsyst->SetLineColor(4);
  gRFBsyst->SetLineWidth(2);   
  gRFBsyst->SetMarkerStyle(0);
  gRFBsyst->SetMarkerColor(1);


  


  TGraphAsymmErrors *gRFBstat = new TGraphAsymmErrors(nbinsRFB,xbinsRFB,yRFB,exlRFB,exlRFB,yRFBStat, yRFBStat);
  gRFBstat->SetTitle("gRFBstat");
  gRFBstat->SetName("gRFBstat");
  gRFBstat->SetMarkerColor(1);
  gRFBstat->SetLineColor(1);
  gRFBstat->SetLineWidth(2);   
  gRFBstat->SetMarkerStyle(21);
  gRFBstat->SetMarkerColor(1);
  gRFBstat->SetFillColor(0);
  gRFBstat->SetFillStyle(0);

  gRFBsyst->SetFillColor(0);
  gRFBsyst->SetFillStyle(0);
  
  gRFBsyst->Draw("2same");
  gRFBstat->Draw("psame");



  TLegendEntry *ent_RFB=legendRFB->AddEntry(gRFBstat,"R_{FB} stat.","pl");
  ent_RFB->SetTextFont(42);
  ent_RFB->SetLineColor(2);
  ent_RFB->SetMarkerColor(2);

  TLegendEntry *ent_RFB=legendRFB->AddEntry(gRFBsyst,"R_{FB} syst.","l");
  ent_RFB->SetTextFont(42);
  ent_RFB->SetLineColor(4);
  // ent_RFB->SetMarkerColor(2);

  TLatex * tlatex1=new TLatex(0.1612903,0.8625793,"CMS Preliminary     pPb #sqrt{s_{NN}}= 5.02 TeV");
  tlatex1->SetNDC();
  tlatex1->SetTextColor(1);
  tlatex1->SetTextFont(42);
  tlatex1->SetTextSize(0.045);
  tlatex1->Draw();

    
  TLatex * tlatexlumi=new TLatex(0.671371,0.7801268,"L = 34.8 nb^{-1}");
  tlatexlumi->SetNDC();
  tlatexlumi->SetTextColor(1);
  tlatexlumi->SetTextFont(42);
  tlatexlumi->SetTextSize(0.045);
  tlatexlumi->Draw();

  
  //double xpos1=0.6528226;
  // double ypos1=0.6849894;
  TLatex * tlatex3=new TLatex(xpos,ypos,mypar.Data());
   tlatex3->SetNDC();
  tlatex3->SetTextColor(1);
  tlatex3->SetTextFont(42);
  tlatex3->SetTextSize(0.06);
  tlatex3->Draw();
  canvasRFB->SaveAs(Form("Results%s_y/CanvasRDFB.pdf",particle.Data(),particle.Data()));




//  l->Draw();  
//  canvasRpA->SaveAs(Form("Results%sY/canvasRpA%s.pdf",particle.Data(),particle.Data()));  
//  canvasRpA->SaveAs(Form("Results%s_y/canvasRpA%s.pdf",particle.Data(),particle.Data()));  
  
//  TFile *fout=new TFile(Form("Results%sY/fileRpA%s.root",particle.Data(),particle.Data()),"recreate");  
  TFile *fout=new TFile(Form("Results%s_y/fileRpA%s.root",particle.Data(),particle.Data()),"recreate");  
  fout->cd();
  gSigmasyst->SetName("gSigmasyst");
  gSigmasyst->Write();
  gaeBplusReference->Write();
  hSigmapPbStat->Write();






}
