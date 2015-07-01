#include"hand.h"
#include"ltrie.h"

void hpasv(senv*s){
  int p1,p2;
  char*c;
  c=strchr(s->scon->bf,',');
  sscanf(c,",%*d,%*d,%*d,%d,%d",&p1,&p2);
  if(s->cm==PASSIVE){
    sock_d(s->sdat);
    s->sdat=sock_c();
  }else{
    s->cm=PASSIVE;
  }
  sock_a(s->sdat,p1*256+p2,s->sin);
}
void hlist(senv*s){sread(s->sdat);}
void hretr(senv*s){
  char fname[30];
  sread(s->sdat);
  sscanf(fname,"retr %s",s->scon->bf);  
  FILE*fout=fopen(fname,"w");
  fwrite(s->sdat->bf,1,sizeof(s->sdat->bf),fout);
  fclose(fout);
}

trie*hand_i(){
  trie*t=trie_c('\0');
  trie_add(t,"user",huser);
  trie_add(t,"pass",hpass);
  trie_add(t,"pasv",hpasv);
  trie_add(t,"list",hlist);
  trie_add(t, "cwd", hcwd);
  trie_add(t,"retr",hretr);
  return t;
}
