//UVA: 	11195
//UVA handle: 	mouhammedElshaaer


#include <iostream>

using namespace std;

#define N 8

int n=8;
int num_solu=0;
int curr_solu[N];
bool    col_taken[N],
        fdialog_taken[N*2-1],
        bdialog_taken[N*2-1];
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Backtrack1(int r)
{
    if(r==n){num_solu++;return;}
    for(int c=0;c<n;c++)if(!col_taken[c] ) if( !fdialog_taken[r-c+n-1] ) if( !bdialog_taken[r+c])
    {
        col_taken[c]=true;  fdialog_taken[r-c+n-1]=true;  bdialog_taken[r+c]=true;
        curr_solu[r]=c;
        Backtrack1(r+1);
        col_taken[c]=false;  fdialog_taken[r-c+n-1]=false;  bdialog_taken[r+c]=false;
    }
}
void Compute1() // do necessay initializations and call Backtrack1()
{
    for(int i=0;i<n;i++) col_taken[i]=false;
    for(int i=0;i<(n*2-1);i++){fdialog_taken[i]=false;bdialog_taken[i]=false;}
    Backtrack1(0);
    cout<<"num_solu: "<<num_solu<<endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int F[N+1]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[N+1]; // B[0]=n, B[1]=0
void Remove(int i) {F[B[i]]=F[i]; B[F[i]]=B[i];}
void Restore(int i) {B[F[i]]=i; F[B[i]]=i;}
void InitDancingLinks(int n)
{
    int i;
    for(i=0;i<n;i++) F[i]=i+1; F[n]=0;
    for(i=n;i>0;i--) B[i]=i-1; B[0]=n;
}


void Backtrack2(int r)
{
    if(r==n){num_solu++;return;}
    for(int c=F[0];c!=0;c=F[c])if( !fdialog_taken[r-c+n-1] ) if( !bdialog_taken[r+c])
    {
        Remove(c);      fdialog_taken[r-c+n-1]=true;  bdialog_taken[r+c]=true;
        curr_solu[r]=B[c];
        Backtrack2(r+1);
        Restore(c);     fdialog_taken[r-c+n-1]=false;  bdialog_taken[r+c]=false;
    }
}
void Compute2() // do necessay initializations and call Backtrack1()
{
    InitDancingLinks(n);
    for(int i=0;i<n;i++) col_taken[i]=false;
    for(int i=0;i<(n*2-1);i++){fdialog_taken[i]=false;bdialog_taken[i]=false;}
    num_solu=0;
    Backtrack2(0);
    cout<<"num_solu: "<<num_solu<<endl;
}



int main()
{
    Compute1();
    Compute2();
    return 0;
}
