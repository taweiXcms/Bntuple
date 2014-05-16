/*

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
Double_t total[nbins]={0.,0.,0.,0.};
Double_t tandprobe[nbins]={0.,0.,0.,0.};




const int nbins=5;
Double_t acceptance[nbins]={0.8,0.5,1.0,0.5,0.7};
Double_t hadron[nbins]={3.9,3.9,3.9,3.9,3.9};
Double_t best[nbins]={3.2,3.2,3.2,3.2,3.2};
Double_t Bselection[nbins]={9.0,9.0,9.0,9.0,9.0};
Double_t ptres[nbins]={0.6,0.6,0.6,0.6,0.6};
Double_t trgeff[nbins]={5.9,3.1,2.1,1.6,1.3};
Double_t muonid[nbins]={5.2,3.5,2.8,2.4,2.6};
Double_t innertrk[nbins]={4.3,4.1,3.6,2.9,1.2};
Double_t PDF[nbins]={8.9,8.9,8.9,8.9,8.9};
Double_t total[nbins]={0.,0.,0.,0.,0.};
Double_t tandprobe[nbins]={0.,0.,0.,0.,0.};


const int nbins=3;
Double_t acceptance[nbins]={1.4,0.7,2.0};
Double_t hadron[nbins]={7.8,7.8,7.8};
Double_t best[nbins]={3.1,3.1,3.1};
Double_t Bselection[nbins]={13.5,13.5,13.5};
Double_t ptres[nbins]={0.6,0.6,0.6};
Double_t trgeff[nbins]={6.8,3.4,1.8};
Double_t muonid[nbins]={5.6,3.8,2.8};
Double_t innertrk[nbins]={4.3,4.2,2.9};
Double_t PDF[nbins]={13.4,13.4,13.4};
Double_t total[nbins]={0.,0.,0.};
Double_t tandprobe[nbins]={0.,0.,0.};


const int nbins=1;
Double_t acceptance[nbins]={5.6};
Double_t hadron[nbins]={7.8};
Double_t best[nbins]={2.4};
Double_t Bselection[nbins]={13.5};
Double_t ptres[nbins]={0.6};
Double_t trgeff[nbins]={4.9};
Double_t muonid[nbins]={4.6};
Double_t innertrk[nbins]={4.0};
Double_t PDF[nbins]={7.5};
Double_t total[nbins]={0.};
Double_t tandprobe[nbins]={0.};

*/




const int nbins=3;
Double_t acceptance[nbins]={1.4,0.7,2.0};
Double_t hadron[nbins]={7.8,7.8,7.8};
Double_t best[nbins]={3.1,3.1,3.1};
Double_t Bselection[nbins]={13.5,13.5,13.5};
Double_t ptres[nbins]={0.6,0.6,0.6};
Double_t trgeff[nbins]={6.8,3.4,1.8};
Double_t muonid[nbins]={5.6,3.8,2.8};
Double_t innertrk[nbins]={4.3,4.2,2.9};
Double_t PDF[nbins]={13.4,13.4,13.4};
Double_t total[nbins]={0.,0.,0.};
Double_t tandprobe[nbins]={0.,0.,0.};



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
    tandprobe[i]=(1+trgeff[i]*0.01)*(1+muonid[i]*0.01)*(1+innertrk[i]*0.01);

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