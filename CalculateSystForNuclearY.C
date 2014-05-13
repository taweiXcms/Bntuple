const int nbins=4;
Double_t acceptance[nbins]={5.8,6.4,4.0,2.8};
Double_t hadron[nbins]={3.9,3.9,3.9,3.9};
Double_t best[nbins]={0.,0.,0.,0.};
Double_t Bselection[nbins]={9.0,9.0,9.0,9.0};
Double_t ptres[nbins]={0.6,0.6,0.6,0.6};
Double_t trgeff[nbins]={3.6,3.6,3.6,3.6};
Double_t muonid[nbins]={2.5,2.5,2.5,2.5};
Double_t innertrk[nbins]={1.6,1.6,1.6,1.6};
Double_t PDF[nbins]={10.6,6.8,5.0,6.6};
Double_t total[nbins]={0.,0.};


void CalculateSystForNuclearY(){

  total[0]=total[0]+acceptance[1]*acceptance[1]+acceptance[2]*acceptance[2];
  total[0]=total[0]+hadron[1]*hadron[1]+hadron[2]*hadron[2];
  total[0]=total[0]+ptres[1]*ptres[1]+ptres[2]*ptres[2];
  total[0]=total[0]+trgeff[1]*trgeff[1]+trgeff[2]*trgeff[2];
  total[0]=total[0]+muonid[1]*muonid[1]+muonid[2]*muonid[2];
  total[0]=total[0]+innertrk[1]*innertrk[1]+innertrk[2]*innertrk[2];
  total[0]=total[0]+PDF[1]*PDF[1]+PDF[2]*PDF[2];


  total[1]=total[1]+acceptance[0]*acceptance[0]+acceptance[3]*acceptance[3];
  total[1]=total[1]+hadron[0]*hadron[0]+hadron[3]*hadron[3];
  total[1]=total[1]+ptres[0]*ptres[0]+ptres[3]*ptres[3];
  total[1]=total[1]+trgeff[0]*trgeff[0]+trgeff[3]*trgeff[3];
  total[1]=total[1]+muonid[0]*muonid[0]+muonid[3]*muonid[3];
  total[1]=total[1]+innertrk[0]*innertrk[0]+innertrk[3]*innertrk[3];
  total[1]=total[1]+PDF[0]*PDF[0]+PDF[3]*PDF[3];
  
  total[0]=TMath::Sqrt(total[0]);
  total[1]=TMath::Sqrt(total[1]);



  cout<<"Total Systematics"<<endl;
  cout<<"{";
  for (int i=0;i<2;i++) {
    printf("%.3f",0.01*total[i]);
    //cout<<total[i];
    if(i!=(nbins-1)) cout<<",";
  }
  cout<<"}";
  cout<<endl;


}