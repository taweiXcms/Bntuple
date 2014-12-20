#include <cmath>
#include <iostream>
#include <iomanip>
#include "TString.h"

void calsys()
{
  const int nSys = 7;

  const int nBplus = 5;
  double ptBplus[nBplus+1] = {10,15,20,25,30,60};
  double Bplus[nSys][nBplus] = {{0.4,0.2,1.0,0.7,0.9},//acc
				{3.9,3.9,3.9,3.9,3.9},//had tr eff
				{3.2,3.2,3.2,3.2,3.2},//best b
				{9.0,9.0,9.0,9.0,9.0},//b eff
				{0.6,0.6,0.6,0.6,0.6},//pt reso
				{5.0,3.0,2.5,0.6,0.5},//tnp
				{11.7,11.7,11.7,11.7,11.7}};//pdf

  const int nBzero = 3;
  double ptBzero[nBzero+1] = {10,15,20,60};
  double Bzero[nSys][nBzero] = {{0.3,0.3,1.7},//acc
				{7.8,7.8,7.8},//had tr eff
				{3.1,3.1,3.1},//best b
				{13.5,13.5,13.5},//b eff
				{0.6,0.6,0.6},//pt reso
				{5.2,3.3,1.7},//tnp
				{10.0,10.0,10.0}};//pdf

  const int nBs = 1;
  double ptBs[nBs+1] = {10,60};
  double Bs[nSys][nBs] = {{5.6},//acc
			     {7.8},//had tr eff
			     {2.4},//best b
			     {13.5},//b eff
			     {0.6},//pt reso
			     {4.0},//tnp
			     {14.6}};//pdf

  const int nBplus_y = 5;
  double ptBplus_y[nBplus_y+1] = {-2.86,-1.93,-1.0,0.0,1.0,1.93};
  double Bplus_y[nSys][nBplus_y] = {{2.5,2.8,3.4,2.9,2.5},//acc
				    {3.9,3.9,3.9,3.9,3.9},//had tr eff
				    {3.2,3.2,3.2,3.2,3.2},//best b
				    {9.0,9.0,9.0,9.0,9.0},//b eff
				    {0.6,0.6,0.6,0.6,0.6},//pt reso
				    {5.4,4.4,3.7,3.4,3.6},//tnp
				    {11.7,11.7,11.7,11.7,11.7}};//pdf

  int i=0,j=0;
  TString bin;
  double sum=0,sq=0;
  cout<<"====================================================================================="<<endl;

  cout<<"  B+"<<endl;
  cout<<"-------------------------------------------------------------------------------------"<<endl;
  for(i=0;i<nBplus;i++)
    {
      bin = Form("(%.0f,%.0f)",ptBplus[i],ptBplus[i+1]);
      cout<<setw(15)<<bin;
    }
  cout<<endl;
  for(i=0;i<nBplus;i++)
    {
      sum=0;
      for(j=0;j<nSys;j++)
	{
	  sum+=(Bplus[j][i]*Bplus[j][i]);
	}
      sq=sqrt(sum);
      cout<<setw(15)<<sq;
    }
  cout<<endl;
  cout<<endl;

  cout<<"  B0"<<endl;
  cout<<"-------------------------------------------------------------------------------------"<<endl;

  for(i=0;i<nBzero;i++)
    {
      bin = Form("(%.0f,%.0f)",ptBzero[i],ptBzero[i+1]);
      cout<<setw(15)<<bin;
    }
  cout<<endl;
  for(i=0;i<nBzero;i++)
    {
      sum=0;
      for(j=0;j<nSys;j++)
	{
	  sum+=(Bzero[j][i]*Bzero[j][i]);
	}
      sq=sqrt(sum);
      cout<<setw(15)<<sq;
    }
  cout<<endl;
  cout<<endl;

  cout<<"  Bs"<<endl;
  cout<<"-------------------------------------------------------------------------------------"<<endl;

  for(i=0;i<nBs;i++)
    {
      bin = Form("(%.0f,%.0f)",ptBs[i],ptBs[i+1]);
      cout<<setw(15)<<bin;
    }
  cout<<endl;
  for(i=0;i<nBs;i++)
    {
      sum=0;
      for(j=0;j<nSys;j++)
	{
	  sum+=(Bs[j][i]*Bs[j][i]);
	}
      sq=sqrt(sum);
      cout<<setw(15)<<sq;
    }
  cout<<endl;
  cout<<endl;

  cout<<"  Bplus_y"<<endl;
  cout<<"-------------------------------------------------------------------------------------"<<endl;

  for(i=0;i<nBplus_y;i++)
    {
      bin = Form("(%.2f,%.2f)",ptBplus_y[i],ptBplus_y[i+1]);
      cout<<setw(15)<<bin;
    }
  cout<<endl;
  for(i=0;i<nBplus_y;i++)
    {
      sum=0;
      for(j=0;j<nSys;j++)
	{
	  sum+=(Bplus_y[j][i]*Bplus_y[j][i]);
	}
      sq=sqrt(sum);
      cout<<setw(15)<<sq;
    }
  cout<<endl;
  cout<<endl;

  cout<<"====================================================================================="<<endl;  
}
