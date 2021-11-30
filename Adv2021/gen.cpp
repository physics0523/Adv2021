#include<bits/stdc++.h>

using namespace std;

int T,R,N;
double C;
double omega;
double F(double t){
  double res=1.5*t;
  res-=(((double)T)*cos(omega + 2.0*M_PI*t/((double)T))) / (2.0*M_PI);
  res+=C;
  return res;
}

double G(double x){
  double st=0.0,fi=((double)T);
  for(int i=0;(i<200 && st<=fi);i++){
    double te=(st+fi)/2.0;
    if(F(te)<x){st=te;}
    else{fi=te;}
  }
  return (st+fi)/2.0;
}

int main(){
  FILE *sd=fopen("seed.txt","r");
  int case_num;
  fscanf(sd,"%d",&case_num);
  for(int i=1;i<=case_num;i++){
    uint_fast64_t seed;
    fscanf(sd,"%llu",&seed);
    mt19937_64 engine(seed);

    char fn[32];
    sprintf(fn,"%04d.txt",i);
    FILE *oup=fopen(fn,"w");

    T=3600;R=4;N=5400;
    fprintf(oup,"%d %d\n",T,R);
    uniform_real_distribution<> d_omg(0.0, 2.0*M_PI);
    uniform_real_distribution<> d_noise(-20.0,20.0);
    omega=d_omg(engine);
    C=((double)T)*cos(omega) / (2.0*M_PI);
    normal_distribution<> nd(50.0,20.0);
    vector<int> bk(T,0);
    for(int j=0;j<N;j++){
      double val=G(((double)j)+0.5)+d_noise(engine);
      val+=3.0*((double)T);
      int tg=((int)round(val))%T;
      bk[tg]++;
    }
    for(int j=0;j<T;j++){
      fprintf(oup,"%d",bk[j]);
      for(int k=0;k<bk[j];k++){
        int sk;
        do{
          sk=round(nd(engine));
        }while(!(0<=sk && sk<=100));
        fprintf(oup," %d",sk);
      }
      fprintf(oup,"\n");
    }
    fclose(oup);
  }
  fclose(sd);
}
