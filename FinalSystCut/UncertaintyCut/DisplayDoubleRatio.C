void DisplayDoubleRatio(){

  double DoubleRatioError(double,double,double,double,double&,double&,double&,double&);

  TFile*file_Data_D0err_NoCut=new TFile("Results/CutId1/SigmaBplusCutId1_isData1.root");
  TFile*file_Data_D0err_Cut=new TFile("Results/CutId2/SigmaBplusCutId2_isData1.root");
  TFile*file_Data_Trkpt_NoCut=new TFile("Results/CutId3/SigmaBplusCutId3_isData1.root");
  TFile*file_Data_Trkpt_Cut=new TFile("Results/CutId4/SigmaBplusCutId4_isData1.root");
  TFile*file_Data_chi2cl_NoCut=new TFile("Results/CutId5/SigmaBplusCutId5_isData1.root");
  TFile*file_Data_chi2cl_Cut=new TFile("Results/CutId6/SigmaBplusCutId6_isData1.root");
  TFile*file_Data_costheta_NoCut=new TFile("Results/CutId7/SigmaBplusCutId7_isData1.root");
  TFile*file_Data_costheta_Cut=new TFile("Results/CutId8/SigmaBplusCutId8_isData1.root");
  
  TFile*file_MC_D0err_NoCut=new TFile("Results/CutId1/SigmaBplusCutId1_isData0.root");
  TFile*file_MC_D0err_Cut=new TFile("Results/CutId2/SigmaBplusCutId2_isData0.root");
  TFile*file_MC_Trkpt_NoCut=new TFile("Results/CutId3/SigmaBplusCutId3_isData0.root");
  TFile*file_MC_Trkpt_Cut=new TFile("Results/CutId4/SigmaBplusCutId4_isData0.root");
  TFile*file_MC_chi2cl_NoCut=new TFile("Results/CutId5/SigmaBplusCutId5_isData0.root");
  TFile*file_MC_chi2cl_Cut=new TFile("Results/CutId6/SigmaBplusCutId6_isData0.root");
  TFile*file_MC_costheta_NoCut=new TFile("Results/CutId7/SigmaBplusCutId7_isData0.root");
  TFile*file_MC_costheta_Cut=new TFile("Results/CutId8/SigmaBplusCutId8_isData0.root");
  
  
  TH1F*hPtYield_Data_D0err_NoCut=(TH1F*)file_Data_D0err_NoCut->Get("hPt");
  TH1F*hPtYield_Data_D0err_Cut=(TH1F*)file_Data_D0err_Cut->Get("hPt");
  TH1F*hPtYield_Data_Trkpt_NoCut=(TH1F*)file_Data_Trkpt_NoCut->Get("hPt");
  TH1F*hPtYield_Data_Trkpt_Cut=(TH1F*)file_Data_Trkpt_Cut->Get("hPt");
  TH1F*hPtYield_Data_chi2cl_NoCut=(TH1F*)file_Data_chi2cl_NoCut->Get("hPt");
  TH1F*hPtYield_Data_chi2cl_Cut=(TH1F*)file_Data_chi2cl_Cut->Get("hPt");
  TH1F*hPtYield_Data_costheta_NoCut=(TH1F*)file_Data_costheta_NoCut->Get("hPt");
  TH1F*hPtYield_Data_costheta_Cut=(TH1F*)file_Data_costheta_Cut->Get("hPt");  

  TH1F*hPtYield_MC_D0err_NoCut=(TH1F*)file_MC_D0err_NoCut->Get("hPt");
  TH1F*hPtYield_MC_D0err_Cut=(TH1F*)file_MC_D0err_Cut->Get("hPt");
  TH1F*hPtYield_MC_Trkpt_NoCut=(TH1F*)file_MC_Trkpt_NoCut->Get("hPt");
  TH1F*hPtYield_MC_Trkpt_Cut=(TH1F*)file_MC_Trkpt_Cut->Get("hPt");
  TH1F*hPtYield_MC_chi2cl_NoCut=(TH1F*)file_MC_chi2cl_NoCut->Get("hPt");
  TH1F*hPtYield_MC_chi2cl_Cut=(TH1F*)file_MC_chi2cl_Cut->Get("hPt");
  TH1F*hPtYield_MC_costheta_NoCut=(TH1F*)file_MC_costheta_NoCut->Get("hPt");
  TH1F*hPtYield_MC_costheta_Cut=(TH1F*)file_MC_costheta_Cut->Get("hPt");  
  
  hPtYield_Data_D0err_NoCut->Scale(50);
  hPtYield_Data_D0err_Cut->Scale(50);
  hPtYield_Data_Trkpt_NoCut->Scale(50);
  hPtYield_Data_Trkpt_Cut->Scale(50);
  hPtYield_Data_chi2cl_NoCut->Scale(50);
  hPtYield_Data_chi2cl_Cut->Scale(50);
  hPtYield_Data_costheta_NoCut->Scale(50);
  hPtYield_Data_costheta_Cut->Scale(50);
  
  hPtYield_MC_D0err_NoCut->Scale(50);
  hPtYield_MC_D0err_Cut->Scale(50);
  hPtYield_MC_Trkpt_NoCut->Scale(50);
  hPtYield_MC_Trkpt_Cut->Scale(50);
  hPtYield_MC_chi2cl_NoCut->Scale(50);
  hPtYield_MC_chi2cl_Cut->Scale(50);
  hPtYield_MC_costheta_NoCut->Scale(50);
  hPtYield_MC_costheta_Cut->Scale(50);
  
    
  double yield_Data_D0err_Cut=hPtYield_Data_D0err_Cut->GetBinContent(1);
  double yield_Data_D0err_NoCut=hPtYield_Data_D0err_NoCut->GetBinContent(1);
  double yield_MC_D0err_Cut=hPtYield_MC_D0err_Cut->GetBinContent(1);
  double yield_MC_D0err_NoCut=hPtYield_MC_D0err_NoCut->GetBinContent(1);
  double relerryield_Data_D0err_Cut=hPtYield_Data_D0err_Cut->GetBinError(1)/hPtYield_Data_D0err_Cut->GetBinContent(1);
  double relerryield_Data_D0err_NoCut=hPtYield_Data_D0err_NoCut->GetBinError(1)/hPtYield_Data_D0err_NoCut->GetBinContent(1);
  double relerryield_MC_D0err_Cut=hPtYield_MC_D0err_Cut->GetBinError(1)/hPtYield_MC_D0err_Cut->GetBinContent(1);
  double relerryield_MC_D0err_NoCut=hPtYield_MC_D0err_NoCut->GetBinError(1)/hPtYield_MC_D0err_NoCut->GetBinContent(1);
  double dratioD0err=(yield_Data_D0err_Cut/yield_Data_D0err_NoCut)/(yield_MC_D0err_Cut/yield_MC_D0err_NoCut);
  
  double errdratioD0err=relerryield_Data_D0err_Cut*relerryield_Data_D0err_Cut+relerryield_Data_D0err_NoCut*relerryield_Data_D0err_NoCut;
  errdratioD0err=errdratioD0err+relerryield_MC_D0err_Cut*relerryield_MC_D0err_Cut+relerryield_MC_D0err_NoCut*relerryield_MC_D0err_NoCut;
  errdratioD0err=dratioD0err*TMath::Sqrt(errdratioD0err);
  
    
  double yield_Data_Trkpt_Cut=hPtYield_Data_Trkpt_Cut->GetBinContent(1);
  double yield_Data_Trkpt_NoCut=hPtYield_Data_Trkpt_NoCut->GetBinContent(1);
  double yield_MC_Trkpt_Cut=hPtYield_MC_Trkpt_Cut->GetBinContent(1);
  double yield_MC_Trkpt_NoCut=hPtYield_MC_Trkpt_NoCut->GetBinContent(1);
  double relerryield_Data_Trkpt_Cut=hPtYield_Data_Trkpt_Cut->GetBinError(1)/hPtYield_Data_Trkpt_Cut->GetBinContent(1);
  double relerryield_Data_Trkpt_NoCut=hPtYield_Data_Trkpt_NoCut->GetBinError(1)/hPtYield_Data_Trkpt_NoCut->GetBinContent(1);
  double relerryield_MC_Trkpt_Cut=hPtYield_MC_Trkpt_Cut->GetBinError(1)/hPtYield_MC_Trkpt_Cut->GetBinContent(1);
  double relerryield_MC_Trkpt_NoCut=hPtYield_MC_Trkpt_NoCut->GetBinError(1)/hPtYield_MC_Trkpt_NoCut->GetBinContent(1);
  double dratioTrkpt=(yield_Data_Trkpt_Cut/yield_Data_Trkpt_NoCut)/(yield_MC_Trkpt_Cut/yield_MC_Trkpt_NoCut);
  double errdratioTrkpt=relerryield_Data_Trkpt_Cut*relerryield_Data_Trkpt_Cut+relerryield_Data_Trkpt_NoCut*relerryield_Data_Trkpt_NoCut;
  errdratioTrkpt=errdratioTrkpt+relerryield_MC_Trkpt_Cut*relerryield_MC_Trkpt_Cut+relerryield_MC_Trkpt_NoCut*relerryield_MC_Trkpt_NoCut;
  errdratioTrkpt=dratioTrkpt*TMath::Sqrt(errdratioTrkpt);


 
  double yield_Data_chi2cl_Cut=hPtYield_Data_chi2cl_Cut->GetBinContent(1);
  double yield_Data_chi2cl_NoCut=hPtYield_Data_chi2cl_NoCut->GetBinContent(1);
  double yield_MC_chi2cl_Cut=hPtYield_MC_chi2cl_Cut->GetBinContent(1);
  double yield_MC_chi2cl_NoCut=hPtYield_MC_chi2cl_NoCut->GetBinContent(1);
  double relerryield_Data_chi2cl_Cut=hPtYield_Data_chi2cl_Cut->GetBinError(1)/hPtYield_Data_chi2cl_Cut->GetBinContent(1);
  double relerryield_Data_chi2cl_NoCut=hPtYield_Data_chi2cl_NoCut->GetBinError(1)/hPtYield_Data_chi2cl_NoCut->GetBinContent(1);
  double relerryield_MC_chi2cl_Cut=hPtYield_MC_chi2cl_Cut->GetBinError(1)/hPtYield_MC_chi2cl_Cut->GetBinContent(1);
  double relerryield_MC_chi2cl_NoCut=hPtYield_MC_chi2cl_NoCut->GetBinError(1)/hPtYield_MC_chi2cl_NoCut->GetBinContent(1);
  double dratiochi2cl=(yield_Data_chi2cl_Cut/yield_Data_chi2cl_NoCut)/(yield_MC_chi2cl_Cut/yield_MC_chi2cl_NoCut);  
  double errdratiochi2cl=relerryield_Data_chi2cl_Cut*relerryield_Data_chi2cl_Cut+relerryield_Data_chi2cl_NoCut*relerryield_Data_chi2cl_NoCut;
  errdratiochi2cl=errdratiochi2cl+relerryield_MC_chi2cl_Cut*relerryield_MC_chi2cl_Cut+relerryield_MC_chi2cl_NoCut*relerryield_MC_chi2cl_NoCut;
  errdratiochi2cl=dratiochi2cl*TMath::Sqrt(errdratiochi2cl);

  

  double yield_Data_costheta_Cut=hPtYield_Data_costheta_Cut->GetBinContent(1);
  double yield_Data_costheta_NoCut=hPtYield_Data_costheta_NoCut->GetBinContent(1);
  double yield_MC_costheta_Cut=hPtYield_MC_costheta_Cut->GetBinContent(1);
  double yield_MC_costheta_NoCut=hPtYield_MC_costheta_NoCut->GetBinContent(1);
  double relerryield_Data_costheta_Cut=hPtYield_Data_costheta_Cut->GetBinError(1)/hPtYield_Data_costheta_Cut->GetBinContent(1);
  double relerryield_Data_costheta_NoCut=hPtYield_Data_costheta_NoCut->GetBinError(1)/hPtYield_Data_costheta_NoCut->GetBinContent(1);
  double relerryield_MC_costheta_Cut=hPtYield_MC_costheta_Cut->GetBinError(1)/hPtYield_MC_costheta_Cut->GetBinContent(1);
  double relerryield_MC_costheta_NoCut=hPtYield_MC_costheta_NoCut->GetBinError(1)/hPtYield_MC_costheta_NoCut->GetBinContent(1);
  double dratiocostheta=(yield_Data_costheta_Cut/yield_Data_costheta_NoCut)/(yield_MC_costheta_Cut/yield_MC_costheta_NoCut);

  double errdratiocostheta=relerryield_Data_costheta_Cut*relerryield_Data_costheta_Cut+relerryield_Data_costheta_NoCut*relerryield_Data_costheta_NoCut;
  errdratiocostheta=errdratiocostheta+relerryield_MC_costheta_Cut*relerryield_MC_costheta_Cut+relerryield_MC_costheta_NoCut*relerryield_MC_costheta_NoCut;
  errdratiocostheta=dratiocostheta*TMath::Sqrt(errdratiocostheta);
  
  
  //__________________________________
  
  double myeffdataD0err,myerreffdataD0err,myeffmcD0err,myerreffmcD0err;
  double errdratioD0errBINObis=DoubleRatioError(yield_Data_D0err_Cut,yield_Data_D0err_NoCut,yield_MC_D0err_Cut,yield_MC_D0err_NoCut,myeffdataD0err,myerreffdataD0err,myeffmcD0err,myerreffmcD0err);
  
  cout<<"******* D0err *******"<<endl;
  cout<<"eff Data with error = "<<myeffdataD0err<<" +- "<<myerreffdataD0err<<endl;
  cout<<"eff MC with error = "<<myeffmcD0err<<" +- "<<myerreffmcD0err<<endl;
  cout<<"double ratio with bin error = "<<dratioD0err<<" +- "<<errdratioD0errBINObis<<endl;
  
   //__________________________________
  
  double myeffdatacostheta,myerreffdatacostheta,myeffmccostheta,myerreffmccostheta;
  double errdratiocosthetaBINObis=DoubleRatioError(yield_Data_costheta_Cut,yield_Data_costheta_NoCut,yield_MC_costheta_Cut,yield_MC_costheta_NoCut,myeffdatacostheta,myerreffdatacostheta,myeffmccostheta,myerreffmccostheta);
  
  cout<<"******* costheta *******"<<endl;
  cout<<"eff Data with error = "<<myeffdatacostheta<<" +- "<<myerreffdatacostheta<<endl;
  cout<<"eff MC with error = "<<myeffmccostheta<<" +- "<<myerreffmccostheta<<endl;
  cout<<"double ratio with bin error = "<<dratiocostheta<<" +- "<<errdratiocosthetaBINObis<<endl;
  
   //__________________________________
  
  double myeffdatachi2cl,myerreffdatachi2cl,myeffmcchi2cl,myerreffmcchi2cl;
  double errdratiochi2clBINObis=DoubleRatioError(yield_Data_chi2cl_Cut,yield_Data_chi2cl_NoCut,yield_MC_chi2cl_Cut,yield_MC_chi2cl_NoCut,myeffdatachi2cl,myerreffdatachi2cl,myeffmcchi2cl,myerreffmcchi2cl);
  
  cout<<"******* chi2cl *******"<<endl;
  cout<<"eff Data with error = "<<myeffdatachi2cl<<" +- "<<myerreffdatachi2cl<<endl;
  cout<<"eff MC with error = "<<myeffmcchi2cl<<" +- "<<myerreffmcchi2cl<<endl;
  cout<<"double ratio with bin error = "<<dratiochi2cl<<" +- "<<errdratiochi2clBINObis<<endl;
  
   //__________________________________
  
  double myeffdataTrkpt,myerreffdataTrkpt,myeffmcTrkpt,myerreffmcTrkpt;
  double errdratioTrkptBINObis=DoubleRatioError(yield_Data_Trkpt_Cut,yield_Data_Trkpt_NoCut,yield_MC_Trkpt_Cut,yield_MC_Trkpt_NoCut,myeffdataTrkpt,myerreffdataTrkpt,myeffmcTrkpt,myerreffmcTrkpt);
  
  cout<<"******* Trkpt *******"<<endl;
  cout<<"eff Data with error = "<<myeffdataTrkpt<<" +- "<<myerreffdataTrkpt<<endl;
  cout<<"eff MC with error = "<<myeffmcTrkpt<<" +- "<<myerreffmcTrkpt<<endl;
  cout<<"double ratio with bin error = "<<dratioTrkpt<<" +- "<<errdratioTrkptBINObis<<endl;
  
}



double DoubleRatioError(double NumData=-1,double DenData=-1,double NumMC=-1,double DenMC=-1,double& effdata, double& erreffdata, double& effmc, double& erreffmc){

double EffMC,EffData,ErrEffMC,ErrEffData,RelErrEffMC,RelErrEffData;
double doubleratioDataMC,errdoubleratioDataMC;

EffMC=NumMC/DenMC;
EffData=NumData/DenData;
doubleratioDataMC=EffData/EffMC;

ErrEffMC=TMath::Sqrt(EffMC*(1-EffMC)/DenMC);
ErrEffData=TMath::Sqrt(EffData*(1-EffData)/DenData);

RelErrEffMC=ErrEffMC/EffMC;
RelErrEffData=ErrEffData/EffData;


errdoubleratioDataMC=TMath::Sqrt(RelErrEffMC*RelErrEffMC+RelErrEffData*RelErrEffData)*doubleratioDataMC;
effdata=EffData;
effmc=EffMC;
erreffdata=ErrEffData;
erreffmc=ErrEffMC;
return errdoubleratioDataMC;
}