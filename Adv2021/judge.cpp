#include<bits/stdc++.h>

using namespace std;

struct UnionFind {
  vector<int> data;
  UnionFind(int size) : data(size, -1) { }
  bool unionSet(int x, int y) {
    x = root(x); y = root(y);
    if (x != y) {
      if (data[y] < data[x]) swap(x, y);
      data[x] += data[y]; data[y] = x;
    }
    return x != y;
  }
  bool findSet(int x, int y) {
    return root(x) == root(y);
  }
  int root(int x) {
    return data[x] < 0 ? x : data[x] = root(data[x]);
  }
  int size(int x) {
    return -data[root(x)];
  }
};

int main(int argc,char *argv[]){
  FILE *inp=fopen(argv[1],"r");
  int T,R;
  fscanf(inp,"%d%d",&T,&R);
  printf("%d %d\n",T,R);
  fflush(stdout);
  int p=0;
  int S[5555],tim[5555],pen[5555]={0};
  UnionFind uf(5555);
  for(int i=0;i<T;i++){
    int n;
    fscanf(inp,"%d",&n);
    printf("%d",n);
    for(int j=0;j<n;j++){
      p++;
      tim[p]=i;
      fscanf(inp,"%d",&S[p]);
      printf(" %d",S[p]);
    }printf("\n");
    fflush(stdout);
    int m;
    scanf("%d",&m);
    for(int j=0;j<m;j++){
      int u,v;
      scanf("%d %d",&u,&v);
      if(u<=0 || p<u || v<=0 || p<v){return -1;}
      if(uf.findSet(u,v)){continue;}
      if(uf.size(u)+uf.size(v)>R){return -1;}
      pen[u]+=2*uf.size(u)*uf.size(v)*i;
      uf.unionSet(u,v);
    }
  }
  int score=0;
  int mi[5555],ma[5555];
  for(int i=0;i<5555;i++){mi[i]=1000;ma[i]=-1000;}

  int ps[5555]={0};
  for(int i=1;i<=5400;i++){
    ps[uf.root(i)]+=(pen[i]-(uf.size(i)-1)*tim[i]);
    mi[uf.root(i)]=min(S[i],mi[uf.root(i)]);
    ma[uf.root(i)]=max(S[i],ma[uf.root(i)]);
  }
  for(int i=1;i<=5400;i++){
    if(uf.root(i)==i){
      int ce=0;
      if(uf.size(i)==2){ce=1;}
      else if(uf.size(i)==3){ce=3;}
      else if(uf.size(i)==4){ce=6;}
      score+=max(ce*(200-(ma[i]-mi[i])*(ma[i]-mi[i]))-ps[i],0);
    }
  }
  FILE *fp=fopen(argv[4],"w");
  fprintf(fp,"%d\n",score);
  fclose(fp);
  return 0;
}
