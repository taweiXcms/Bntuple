/*
const int nbins=5;
Double_t acceptance[nbins]={0.1,0.7,1.0,0.5,0.3};
Double_t hadron[nbins]={3.9,3.9,3.9,3.9,3.9};
Double_t best[nbins]={3.2,3.2,3.2,3.2,3.2};
Double_t Bselection[nbins]={9.0,9.0,9.0,9.0,9.0};
Double_t ptres[nbins]={0.6,0.6,0.6,0.6,0.6};
Double_t trgeff[nbins]={8.4,4.7,3.1,2.6,2.5};
Double_t muonid[nbins]={4.9,3.2,2.3,2.0,1.6};
Double_t innertrk[nbins]={2.1,1.4,1.1,0.8,0.9};
Double_t PDF[nbins]={8.9,8.9,8.9,8.9,8.9};
Double_t total[nbins]={0.,0.,0.,0.,0.};
Double_t tandprobe[nbins]={0.,0.,0.,0.,0.};


const int nbins=3;
Double_t acceptance[nbins]={0.7,0.3,0.4};
Double_t hadron[nbins]={7.8,7.8,7.8};
Double_t best[nbins]={3.1,3.1,3.1};
Double_t Bselection[nbins]={13.5,13.5,13.5};
Double_t ptres[nbins]={0.6,0.6,0.6};
Double_t trgeff[nbins]={8.8,4.8,2.9};
Double_t muonid[nbins]={5.3,3.3,2.2};
Double_t innertrk[nbins]={2.6,1.4,0.6};
Double_t PDF[nbins]={13.4,13.4,13.4};
Double_t total[nbins]={0.,0.,0.};
Double_t tandprobe[nbins]={0.,0.,0.};


const int nbins=1;
Double_t acceptance[nbins]={0.4};
Double_t hadron[nbins]={7.8};
Double_t best[nbins]={2.4};
Double_t Bselection[nbins]={13.5};
Double_t ptres[nbins]={0.6};
Double_t trgeff[nbins]={7.4};
Double_t muonid[nbins]={4.5};
Double_t innertrk[nbins]={2.1};
Double_t PDF[nbins]={7.5};
Double_t total[nbins]={0.};
Double_t tandprobe[nbins]={0.};

*/



const int nbins=1;
Double_t acceptance[nbins]={0.4};
Double_t hadron[nbins]={7.8};
Double_t best[nbins]={2.4};
Double_t Bselection[nbins]={13.5};
Double_t ptres[nbins]={0.6};
Double_t trgeff[nbins]={7.4};
Double_t muonid[nbins]={4.5};
Double_t innertrk[nbins]={2.1};
Double_t PDF[nbins]={7.5};
Double_t total[nbins]={0.};
Double_t tandprobe[nbins]={0.};


void CalculateSystForNuclear(){



  for (int i=0;i<nbins;i++){

    total[i]=total[i]+acceptance[i]*acceptance[i];
    total[i]=total[i]+hadron[i]*hadron[i];
    total[i]=total[i]+best[i]*best[i];
    total[i]=total[i]+Bselection[i]*Bselection[i];
    total[i]=total[i]+ptres[i]*ptres[i];
    total[i]=total[i]+trgeff[i]*trgeff[i];
    total[i]=total[i]+muonid[i]*muonid[i];
    total[i]=total[i]+innertrk[i]*innertrk[i];
    total[i]=total[i]+PDF[i]*PDF[i];
    total[i]=TMath::Sqrt(total[i]);
    tandprobe[i]=(1+trgeff[i]*0.01)*(1+muonid[i]*0.01)*(1-innertrk[i]*0.01);

  }
  cout<<"Total Systematics"<<endl;
  cout<<"{";
  for (int i=0;i<nbins;i++) {
    printf("%.3f",0.01*total[i]);
    //cout<<total[i];
    if(i!=(nbins-1)) cout<<",";
  }
  cout<<"}";
  cout<<endl;
  cout<<"T&P coefficient corrections"<<endl;
  cout<<"{";
  for (int i=0;i<nbins;i++) {
    printf("%.7f",tandprobe[i]);
    //cout<<total[i];
    if(i!=(nbins-1)) cout<<",";
  }
  cout<<"}";
  cout<<endl;


}