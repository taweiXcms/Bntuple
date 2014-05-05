void DisplayDoubleRatioBzero(){
  
  TFile*file_Data_resmass_NoCut=new TFile("ResultsBzero/CutId2/SigmaBzeroCutId2_isData1.root");
  TFile*file_Data_resmass_Cut=new TFile("ResultsBzero/CutId1/SigmaBzeroCutId1_isData1.root");
  TFile*file_Data_chi2cl_NoCut=new TFile("ResultsBzero/CutId3/SigmaBzeroCutId3_isData1.root");
  TFile*file_Data_chi2cl_Cut=new TFile("ResultsBzero/CutId1/SigmaBzeroCutId1_isData1.root");
  TFile*file_Data_costheta_NoCut=new TFile("ResultsBzero/CutId4/SigmaBzeroCutId4_isData1.root");
  TFile*file_Data_costheta_Cut=new TFile("ResultsBzero/CutId1/SigmaBzeroCutId1_isData1.root");
  TFile*file_Data_D0err_NoCut=new TFile("ResultsBzero/CutId5/SigmaBzeroCutId5_isData1.root");
  TFile*file_Data_D0err_Cut=new TFile("ResultsBzero/CutId6/SigmaBzeroCutId6_isData1.root");
  TFile*file_Data_Trkpt_NoCut=new TFile("ResultsBzero/CutId7/SigmaBzeroCutId7_isData1.root");
  TFile*file_Data_Trkpt_Cut=new TFile("ResultsBzero/CutId8/SigmaBzeroCutId8_isData1.root");

  
  
  
  TFile*file_MC_resmass_NoCut=new TFile("ResultsBzero/CutId2/SigmaBzeroCutId2_isData0.root");
  TFile*file_MC_resmass_Cut=new TFile("ResultsBzero/CutId1/SigmaBzeroCutId1_isData0.root");
  TFile*file_MC_chi2cl_NoCut=new TFile("ResultsBzero/CutId3/SigmaBzeroCutId3_isData0.root");
  TFile*file_MC_chi2cl_Cut=new TFile("ResultsBzero/CutId1/SigmaBzeroCutId1_isData0.root");
  TFile*file_MC_costheta_NoCut=new TFile("ResultsBzero/CutId4/SigmaBzeroCutId4_isData0.root");
  TFile*file_MC_costheta_Cut=new TFile("ResultsBzero/CutId1/SigmaBzeroCutId1_isData0.root");
  TFile*file_MC_D0err_NoCut=new TFile("ResultsBzero/CutId5/SigmaBzeroCutId5_isData0.root");
  TFile*file_MC_D0err_Cut=new TFile("ResultsBzero/CutId6/SigmaBzeroCutId6_isData0.root");
  TFile*file_MC_Trkpt_NoCut=new TFile("ResultsBzero/CutId7/SigmaBzeroCutId7_isData0.root");
  TFile*file_MC_Trkpt_Cut=new TFile("ResultsBzero/CutId8/SigmaBzeroCutId8_isData0.root");

  TH1F*hPtYield_Data_resmass_Cut=(TH1F*)file_Data_resmass_Cut->Get("hPt");
  TH1F*hPtYield_Data_resmass_NoCut=(TH1F*)file_Data_resmass_NoCut->Get("hPt");
  TH1F*hPtYield_Data_chi2cl_Cut=(TH1F*)file_Data_chi2cl_Cut->Get("hPt");
  TH1F*hPtYield_Data_chi2cl_NoCut=(TH1F*)file_Data_chi2cl_NoCut->Get("hPt");
  TH1F*hPtYield_Data_costheta_Cut=(TH1F*)file_Data_costheta_Cut->Get("hPt");
  TH1F*hPtYield_Data_costheta_NoCut=(TH1F*)file_Data_costheta_NoCut->Get("hPt");  
  TH1F*hPtYield_Data_D0err_NoCut=(TH1F*)file_Data_D0err_NoCut->Get("hPt");
  TH1F*hPtYield_Data_D0err_Cut=(TH1F*)file_Data_D0err_Cut->Get("hPt");
  TH1F*hPtYield_Data_Trkpt_NoCut=(TH1F*)file_Data_Trkpt_NoCut->Get("hPt");
  TH1F*hPtYield_Data_Trkpt_Cut=(TH1F*)file_Data_Trkpt_Cut->Get("hPt");


  TH1F*hPtYield_MC_D0err_NoCut=(TH1F*)file_MC_D0err_NoCut->Get("hPt");
  TH1F*hPtYield_MC_D0err_Cut=(TH1F*)file_MC_D0err_Cut->Get("hPt");
  TH1F*hPtYield_MC_resmass_Cut=(TH1F*)file_MC_resmass_Cut->Get("hPt");
  TH1F*hPtYield_MC_resmass_NoCut=(TH1F*)file_MC_resmass_NoCut->Get("hPt");
  TH1F*hPtYield_MC_chi2cl_NoCut=(TH1F*)file_MC_chi2cl_NoCut->Get("hPt");
  TH1F*hPtYield_MC_chi2cl_Cut=(TH1F*)file_MC_chi2cl_Cut->Get("hPt");
  TH1F*hPtYield_MC_costheta_NoCut=(TH1F*)file_MC_costheta_NoCut->Get("hPt");
  TH1F*hPtYield_MC_costheta_Cut=(TH1F*)file_MC_costheta_Cut->Get("hPt");   
  TH1F*hPtYield_MC_D0err_NoCut=(TH1F*)file_MC_D0err_NoCut->Get("hPt");
  TH1F*hPtYield_MC_D0err_Cut=(TH1F*)file_MC_D0err_Cut->Get("hPt");
  TH1F*hPtYield_MC_Trkpt_NoCut=(TH1F*)file_MC_Trkpt_NoCut->Get("hPt");
  TH1F*hPtYield_MC_Trkpt_Cut=(TH1F*)file_MC_Trkpt_Cut->Get("hPt");
 

  double yield_Data_resmass_Cut=hPtYield_Data_resmass_Cut->GetBinContent(1);
  double yield_Data_resmass_NoCut=hPtYield_Data_resmass_NoCut->GetBinContent(1);
  double yield_MC_resmass_Cut=hPtYield_MC_resmass_Cut->GetBinContent(1);
  double yield_MC_resmass_NoCut=hPtYield_MC_resmass_NoCut->GetBinContent(1);
  double relerryield_Data_resmass_Cut=hPtYield_Data_resmass_Cut->GetBinError(1)/hPtYield_Data_resmass_Cut->GetBinContent(1);
  double relerryield_Data_resmass_NoCut=hPtYield_Data_resmass_NoCut->GetBinError(1)/hPtYield_Data_resmass_NoCut->GetBinContent(1);
  double relerryield_MC_resmass_Cut=hPtYield_MC_resmass_Cut->GetBinError(1)/hPtYield_MC_resmass_Cut->GetBinContent(1);
  double relerryield_MC_resmass_NoCut=hPtYield_MC_resmass_NoCut->GetBinError(1)/hPtYield_MC_resmass_NoCut->GetBinContent(1);
  double dratioresmass=(yield_Data_resmass_Cut/yield_Data_resmass_NoCut)/(yield_MC_resmass_Cut/yield_MC_resmass_NoCut);
  double errdratioresmass=relerryield_Data_resmass_Cut*relerryield_Data_resmass_Cut+relerryield_Data_resmass_NoCut*relerryield_Data_resmass_NoCut;
  errdratioresmass=errdratioresmass+relerryield_MC_resmass_Cut*relerryield_MC_resmass_Cut+relerryield_MC_resmass_NoCut*relerryield_MC_resmass_NoCut;
  errdratioresmass=dratioresmass*TMath::Sqrt(errdratioresmass);

 
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


  
  /*
  cout<<"yield_Data_costheta_NoCut"<<yield_Data_costheta_NoCut*50.<<endl;
  cout<<"yield_Data_chi2cl_NoCut"<<yield_Data_chi2cl_NoCut*50.<<endl;
  cout<<"yield_Data_resmass_NoCut"<<yield_Data_resmass_NoCut*50.<<endl;
  cout<<"yield_Data_Cut"<<yield_Data_resmass_Cut*50.<<endl;

  cout<<"yield_MC_costheta_NoCut"<<yield_MC_costheta_NoCut*50.<<endl;
  cout<<"yield_MC_chi2cl_NoCut"<<yield_MC_chi2cl_NoCut*50.<<endl;
  cout<<"yield_MC_resmass_NoCut"<<yield_MC_resmass_NoCut*50.<<endl;
  cout<<"yield_MC_Cut"<<yield_MC_resmass_Cut*50.<<endl;

*/

  cout<<"double ratio resmass"<<dratioresmass<<" with stat error +- "<<errdratioresmass<<endl;
  cout<<"double ratio chi2cl"<<dratiochi2cl<<" with stat error +- "<<errdratiochi2cl<<endl;
  cout<<"double ratio costheta"<<dratiocostheta<<" with stat error +- "<<errdratiocostheta<<endl;
  cout<<"double ratio D0err"<<dratioD0err<<" with stat error +- "<<errdratioD0err<<endl;
  cout<<"double ratio Trkpt"<<dratioTrkpt<<" with stat error +- "<<errdratioTrkpt<<endl;


  
}
