// UVA:     10130
// UVA Username: mouhammedElshaaer


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid=n/2,i,j,k;
    int n1=mid;
    int n2=n-mid;

    Type* L=new Type[n1];
    Type* R=new Type[n2];

    for (i=0;i<n1;i++)
    {
        L[i]=a[i];
    }
    j=0;
    for (;i<n;i++)
    {
        R[j++]=a[i];
    }
    i=0,j=0,k=0;
    while(i<n1&&j<n2)
    {
        if(IsBefore(R[j],L[i]))
        {
            a[k++]=R[j++];
        }
        else
        {
            a[k++]=L[i++];
        }
    }
    while(i<n1)
    {
        a[k++]=L[i++];
    }
    while(j<n2)
    {
        a[k++]=R[j++];
    }
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    if (n <= 1)
        return;
    int mid=n/2;
    MergeSort(a,mid,IsBefore);
    MergeSort(a+mid,n-mid,IsBefore);
    Merge(a,n,IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
    int v;
    int w;
};

int n;       // number of objects (input)
Obj a[1000]; // objects (input)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Obj& a, Obj& b) // return true if unit value of a is greater than unit value of b
{
    if((double)a.v/a.w>(double)b.v/b.w)
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int best_val; // the best total value found until now

double Bound(int i, int w) // upper bound on the total value of items [i..n-1] that can fit in w
{
    double sum=0;
    for(int x=i;x<n;x++)
    {
        if(a[x].w<=w)
        {
            sum+=a[x].v;
            w-=a[x].w;
        }
        else
        {
            sum+=a[x].v*((double)(w)/(a[x].w));
            return sum;
        }
    }
}
void BackTrack(int i, int w, int cur_val) // starting from item i, remaining weight w, cur_value of objects[0..i-1]
{
    if(i==n)
    {
        best_val=max(best_val,cur_val);
        return;
    }
    if(a[i].w<=w)
    {
        if(best_val<=cur_val+Bound(i,w))
        {
            BackTrack(i+1,w-a[i].w,cur_val+a[i].v);
        }
    }
    BackTrack(i+1,w,cur_val);


}
int ComputeKnapsack(int N, int W) // solve knapsack of N objects and W weight
{
    best_val=0;
    BackTrack(0,W,0);
    return best_val;
}
void Compute()
{
    int t,counter=0;
    cin>>t;
    while(true)
    {
        if(counter==t)
            break;
        cin>>n;
        for(int i=0;i<n;i++)
            cin>>a[i].v>>a[i].w;
        MergeSort(a,n,IsBefore);
        int num;
        cin>>num;
        int weight;
        int sum=0;
        for(int i=0;i<num;i++)
        {
            cin>>weight;
            sum+=ComputeKnapsack(n,weight);
        }
        cout<<sum<<endl;
        counter++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Compute();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
