

const int nbins=4;
Double_t acceptance[nbins]={5.8,6.4,4.0,2.8};
Double_t hadron[nbins]={3.9,3.9,3.9,3.9};
Double_t best[nbins]={3.2,3.2,3.2,3.2};
Double_t Bselection[nbins]={9.0,9.0,9.0,9.0};
Double_t ptres[nbins]={0.6,0.6,0.6,0.6};
Double_t trgeff[nbins]={5.7,4.6,3.4,4.0};
Double_t muonid[nbins]={5.1,4.4.1,3.8};
Double_t innertrk[nbins]={5.7,3.9,1.7,5.5};
Double_t PDF[nbins]={10.6,6.8,5.0,6.6};
Double_t total[2]={0.,0.};
Double_t tandprobe[2]={0.,0.};


void CalculateSystForNuclearFB(){


   total[0]=total[0]+acceptance[1]*acceptance[1]+acceptance[2]*acceptance[2];
   total[0]=total[0]+hadron[1]*hadron[1]+hadron[2]*hadron[2];
   total[0]=total[0]+best[1]*best[1]+best[2]*best[2];
   total[0]=total[0]+trgeff[1]*trgeff[1]+trgeff[2]*trgeff[2];
   total[0]=total[0]+muonid[1]*muonid[1]+muonid[2]*muonid[2];
   total[0]=total[0]+innertrk[1]*innertrk[1]+innertrk[2]*innertrk[2];
   total[0]=total[0]+PDF[1]*PDF[1]+PDF[2]*PDF[2];
   total[0]=TMath::Sqrt(total[0]);
   tandprobe[0]=((1+trgeff[2]*0.01)*(1+muonid[2]*0.01)*(1+innertrk[2]*0.01))/((1+trgeff[1]*0.01)*(1+muonid[1]*0.01)*(1+innertrk[1]*0.01));
   tandprobe[1]=((1+trgeff[3]*0.01)*(1+muonid[3]*0.01)*(1+innertrk[3]*0.01))/((1+trgeff[0]*0.01)*(1+muonid[0]*0.01)*(1+innertrk[0]*0.01));

   
   
   total[1]=total[1]+acceptance[0]*acceptance[0]+acceptance[3]*acceptance[3];
   total[1]=total[1]+hadron[0]*hadron[0]+hadron[3]*hadron[3];
   total[1]=total[1]+best[0]*best[0]+best[3]*best[3];
   total[1]=total[1]+trgeff[0]*trgeff[0]+trgeff[3]*trgeff[3];
   total[1]=total[1]+muonid[0]*muonid[0]+muonid[3]*muonid[3];
   total[1]=total[1]+innertrk[0]*innertrk[0]+innertrk[3]*innertrk[3];
   total[1]=total[1]+PDF[0]*PDF[0]+PDF[3]*PDF[3];
   total[1]=TMath::Sqrt(total[1]);
   

   
   cout<<total[1]<<endl;

  cout<<"Total Systematics"<<endl;
  cout<<"{";
  for (int i=0;i<2;i++) {
    printf("%.3f",0.01*total[i]);
    //cout<<total[i];
    if(i!=(nbins-1)) cout<<",";
  }
  cout<<"}";
  cout<<endl;
  cout<<"T&P coefficient corrections"<<endl;
  cout<<"{";
  for (int i=0;i<2;i++) {
    printf("%.7f",tandprobe[i]);
    //cout<<total[i];
    if(i!=(nbins-1)) cout<<",";
  }
  cout<<"}";
  cout<<endl;


}