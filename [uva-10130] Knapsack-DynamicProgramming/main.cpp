// UVA:     10130
// UVA Username: mouhammedElshaaer

#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
	int v; // value (price) of object
	int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Knapsack0(int n, int w) // recursive brute force O(2^n)
{
    if(n==0) return 0;

    int ret=Knapsack0(n-1,w);

    int cv=a[n-1].v,
        cw=a[n-1].w;

    if(cw<=w)
    {
        int r=cv+Knapsack0(n-1,w-cw);
        ret=ret>r?ret:r;
    }

    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
int Knapsack1(int n, int w)
{
    if(n==0)
    {
        T1[n][w]=0;
        return 0;
    }

    if(T1[n][w]>0)
        return T1[n][w];

    int ret=Knapsack1(n-1,w);

    int cv=a[n-1].v,
        cw=a[n-1].w;

    if(cw<=w)
    {
        int r=cv+Knapsack1(n-1,w-cw);
        ret=ret>r?ret:r;
    }
    T1[n][w]=ret;
    return ret;
}
int ComputeKnapsack1(int N, int W) // Recursive - memoization - initialize T then call Knapsack1(N,W);
{
    for(int i=0;i<1001;i++)
    for(int j=0;j<31;j++)
    {
        T1[i][j]=-1;
    }

    return Knapsack1(N,W);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int ComputeKnapsack2(int N, int W) // Bottom-up, do not save space
{
    for(int i=0;i<1001;i++)
    for(int j=0;j<31;j++)
    {
        T2[i][j]=-1;
    }

    for(int n=0;n<=N;n++)
    for(int w=0;w<=W;w++)
    {
        if(n==0)
        {
            T2[n][w]=0;
            continue;
        }
        T2[n][w]=T2[n-1][w];


        int cv=a[n-1].v,
            cw=a[n-1].w;

        if(cw<=w)
        {
            int r=cv+T2[n-1][w-cw];
            T2[n][w]=(T2[n][w]>r)?T2[n][w]:r;
        }
    }


    return T2[N][W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W) // Bottom-up, use two rows only
{
    for(int i=0;i<2;i++)
    for(int j=0;j<31;j++)
    {
        T3[i][j]=-1;
    }

    int row=0;
    for(int n=0;n<=N;n++,row=1-row)
    {
        for(int w=0;w<=W;w++)
        {
            if(n==0)
            {
                T3[n][w]=0;
                continue;
            }

            T3[row][w]=T3[1-row][w];

            int cv=a[n-1].v,
                cw=a[n-1].w;

            if(cw<=w)
            {
                int r=cv+T3[1-row][w-cw];
                T3[row][w]=(T3[row][w]>r)?T3[row][w]:r;
            }
        }
    }


    return T3[row][W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W) // Bottom-up, save maximum space
{
    for(int j=0;j<31;j++)
    {
        T4[j]=-1;
    }

    for(int n=0;n<=N;n++)
    {
        for(int w=W;w>=0;w--)
        {
            if(n==0)
            {
                T4[w]=0;
                continue;
            }

            T4[w]=T4[w];

            int cv=a[n-1].v,
                cw=a[n-1].w;

            if(cw<=w)
            {
                int r=cv+T4[w-cw];
                T4[w]=(T4[w]>r)?T4[w]:r;
            }
        }
    }


    return T4[W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) // Here we can choose the method
{
	//return ComputeKnapsack1(N,W);
	//return ComputeKnapsack2(N,W);
	//return ComputeKnapsack3(N,W);
	//return ComputeKnapsack4(N,W);
	return 0;
}

void Compute() // Get input and call ComputeKnapsack() whenever needed
{
    int n=4;
    Obj o1; o1.v=3; o1.w=2; a[0]=o1;
    Obj o2; o2.v=7; o2.w=3; a[1]=o2;
    Obj o3; o3.v=9; o3.w=4; a[2]=o3;
    Obj o4; o4.v=4; o4.w=7; a[3]=o4;

    int maxvalue1=Knapsack0(n,9),
        maxvalue2=ComputeKnapsack1(n,9),
        maxvalue3=ComputeKnapsack2(n,9),
        maxvalue4=ComputeKnapsack3(n,9),
        maxvalue5=ComputeKnapsack4(n,9);

    cout<<"Recursive Knapsack: "<<maxvalue1<<endl;
    cout<<"Recursive memoization Knapsack: "<<maxvalue2<<endl;
    cout<<"Bottom up Knapsack: "<<maxvalue3<<endl;
    cout<<"Bottom-up using two rows only: "<<maxvalue4<<endl;
    cout<<"Bottom-up saving maximum space: "<<maxvalue5<<endl;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt","w",stdout);
	#endif

	//Compute();

	int T, N, G;

	scanf("%d",&T);

	while(T--)
    {
        scanf("%d",&N);

        for(int i=0;i<N;i++)
        {
            Obj obj;
            scanf("%d",&obj.v);
            scanf("%d",&obj.w);
            a[i]=obj;
        }

        int maxSale=0;
        scanf("%d",&G);
        for(int i=0;i<G;i++)
        {
            int MW;
            scanf("%d",&MW);
            maxSale+=ComputeKnapsack4(N,MW);
        }
        printf("%d\n",maxSale);
    }

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
