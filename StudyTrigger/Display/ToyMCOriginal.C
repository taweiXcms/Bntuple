#include <TRandom3.h>
#include <iostream>
#include <TH1D.h>

// Numero di candidate prima di ogni selezione 322/0.96=335


void ToyMCBplus(){ 

  double DoubleRatioError(double,double);
  
  
  const int ptbins=5;
  double signal[ptbins]={321.676,164.774,59.5159,26.7268,35.9101};
  double ratio[ptbins]={0.,0.,0.,0.,0.};
  double errratio[ptbins]={0.,0.,0.,0.,0.};

  void Check(double,double&,double&);
  Check(signal[0],ratio[0],errratio[0]);
  Check(signal[1],ratio[1],errratio[1]);
  Check(signal[2],ratio[2],errratio[2]);
  Check(signal[3],ratio[3],errratio[3]);
  Check(signal[4],ratio[4],errratio[4]);
  
  for (int i=0;i<ptbins;i++) printf("pt bin %d, rel error TOY %.3f and rel error BIN %.3f\n",i,errratio[i]/ratio[i],DoubleRatioError(ratio[i],signal[i])/ratio[i]);
   
}

void ToyMCBzero(){ 

  double DoubleRatioError(double,double);
  
  
  const int ptbins=3;
  double signal[ptbins]={85.0,37.0,54};
  double ratio[ptbins]={0.,0.,0.};
  double errratio[ptbins]={0.,0.,0.};

  void Check(double,double&,double&);
  Check(signal[0],ratio[0],errratio[0]);
  Check(signal[1],ratio[1],errratio[1]);
  Check(signal[2],ratio[2],errratio[2]);
  
  for (int i=0;i<ptbins;i++) printf("pt bin %d, rel error TOY %.3f and rel error BIN %.3f\n",i,errratio[i]/ratio[i],DoubleRatioError(ratio[i],signal[i])/ratio[i]);
   
}

void ToyMCBs(){ 

  double DoubleRatioError(double,double);
  
  
  const int ptbins=1;
  double signal[ptbins]={40.0};
  double ratio[ptbins]={40.0};
  double errratio[ptbins]={40.0};

  void Check(double,double&,double&);
  Check(signal[0],ratio[0],errratio[0]);
  
  for (int i=0;i<ptbins;i++) printf("pt bin %d, rel error TOY %.3f and rel error BIN %.3f\n",i,errratio[i]/ratio[i],DoubleRatioError(ratio[i],signal[i])/ratio[i]);
   
}



void Check(double Nsingle=322,double & mean,double & sigma){ 

  double eff1=0.18;   // 1,0       
  double eff2=0.77;   // 1,1       
  double eff3=0.04;   // 0,1       

  //int N=100;
  TRandom3 a;

  TH1D *h = new TH1D("h","",200,0,2);
  
  for (int i=0;i<10000;i++){  
    double N1 = 0;            
    double N2 = 0;            
    double N = Nsingle/0.96;
    for (int j=0;j<N;j++){   
      double p = a.Rndm();   
      if (p<eff1) N1++;   
      if (p>eff1&&p<(eff2+eff1)) {N1++; N2++;}
      if (p>(eff2+eff1)) {N2++;}
      h->Fill(N2/N1);
    }
  }

  h->Fit("gaus","Q");
  mean=h->GetMean();
  sigma=h->GetRMS();
    
}



double DoubleRatioError(double ratio=-1,double Den=-1){

  double ratio,errratio;

  errratio=TMath::Sqrt(ratio*(1-ratio)/Den);
  return errratio;
}

