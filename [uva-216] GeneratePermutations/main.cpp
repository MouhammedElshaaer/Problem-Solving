// UVA:     216
// UVA Username: mouhammedElshaaer


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>      // use built-in sqrt()
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void swap(int& a, int& b)
{
    int temp=a;
    a=b;
    b=temp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_COMPUTERS 8

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
   int x,y;
};
double Dist(Point& a, Point& b)
{
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int		n; // number of computers (input)
Point	com[MAX_COMPUTERS]; // locations of computers (input)
double	dist[MAX_COMPUTERS][MAX_COMPUTERS]; // dist[i][j]=distance from com[i] to com[j] (pre-computed)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

double	best_val; // best value until now
int		best_sol[MAX_COMPUTERS]; // best solution until now (a permutation)

int		s[MAX_COMPUTERS]; // s is current permutation. s[i]=index of the ith computer in this permutation.

////////////////////////////////////////////////////////////////////////////////////////////////////////////

string f;

void UpdateSol() // evaluate the permutation s, then update best_val and best_sol if necessary
{
    double sum=0;
    for(int i=0;i<n-1;i++)
        sum+=dist[s[i]][s[i+1]]+16;
    if(best_val>sum)
    {
        best_val=sum;
        for(int i=0;i<n;i++)
            best_sol[i]=s[i];
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Backtrack0(int i)// backtrack using swaps
{
    if(i==n){UpdateSol();return;}
    for(int j=i;j<n;j++)
    {
        swap(s[i],s[j]);
        Backtrack0(i+1);
        swap(s[i],s[j]);
    }

}
void Compute0() // do necessay initializations and call Backtrack0()
{
    for(int i=0;i<n;i++) s[i]=i;
    Backtrack0(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool v[MAX_COMPUTERS]; // v[i]=true if com[i] already taken in the permutation

void Backtrack1(int i) // backtrack using the v[] array
{
    if(i==n){UpdateSol();return;}
    for(int j=0;j<n;j++)if(!v[j])
    {
        s[i]=j;
        v[j]=true;
        Backtrack1(i+1);
        v[j]=false;
    }
}
void Compute1() // do necessay initializations and call Backtrack1()
{
    for(int i=0;i<n;i++) v[i]=false;
    Backtrack1(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dancing Links:

int F[MAX_COMPUTERS+1]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_COMPUTERS+1]; // B[0]=n, B[1]=0
void Remove(int i) {F[B[i]]=F[i]; B[F[i]]=B[i];}
void Restore(int i) {B[F[i]]=i; F[B[i]]=i;}
void InitDancingLinks(int n)
{
    int i;
    for(i=0;i<n;i++) F[i]=i+1; F[n]=0;
    for(i=n;i>0;i--) B[i]=i-1; B[0]=n;
}
// for(i=F[0];i!=0;i=F[i]) iterate on available list indexes

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Backtrack2(int i) // backtrack using dancing links
{
    if(i==n){UpdateSol();return;}
    for(int j=F[0];j!=0;j=F[j])
    {
        s[i]=j-1;
        Remove(j);
        Backtrack2(i+1);
        Restore(j);
    }
}
void Compute2() // do necessay initializations and call Backtrack2()
{
    InitDancingLinks(n);
    Backtrack2(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ComputeCore()
{
    int number=1;
    while(true)
    {
        cin>>n;
        best_val=INT_MAX;
        if(n==0)
            break;
        cout<<"**********************************************************"<<endl;
        for(int i=0;i<n;i++)
            cin>>com[i].x>>com[i].y;
        for(int i=0;i<n;i++)
            for(int x=0;x<n;x++)
                dist[i][x]=Dist(com[i],com[x]);
        Compute0();
        cout<<"Network #"<<number++<<endl;

        for(int i=0;i<n-1;i++)
        {
            cout<<"Cable requirement to connect ("<<com[best_sol[i]].x<<","<<com[best_sol[i]].y<<") "
                    "to ("<<com[best_sol[i+1]].x<<","<<com[best_sol[i+1]].y<<") is "
                <<fixed<<setprecision(2)<<dist[best_sol[i]][best_sol[i+1]]+16<<" feet."<<endl;
        }
        cout<<"Number of feet of cable required is "<<fixed<<setprecision(2)<<best_val<<"."<<endl;

    }
    // do necessay initializations of dist[][] and best_val

    //Compute1();
    //Compute2();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Compute(); // get input and then call ComputeCore(); then print output

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign13_00216.txt", "r", stdin);
    ComputeCore();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
