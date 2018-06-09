// UVA:     348
// UVA Username: mouhammedElshaaer


#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
int MatChain(int a, int b) // Recursive
{
    if(a+1==b){T[a][b]=0;return 0;}
    if(T[a][b]>0){return T[a][b];}
    T[a][b]=INT_MAX;
    for(int k=a+1;k<b;k++)
    {
        int v=MatChain(a,k)+MatChain(k,b)+p[a]*p[k]*p[b];
        if(v<T[a][b]){T[a][b]=v;D[a][b]=k;}
    }
    return T[a][b];
}
void MatChainTopDown(int n) // Initialize T then call MatChain(0,n)
{
    for(int i=0;i<11;i++)
    for(int j=0;j<11;j++)
    {
        T[i][j]=0;
    }
    MatChain(0,n);
}

// BottomUp version
void MatChainBottomUp(int n)
{

    for(int i=0;i<11;i++)
    for(int j=0;j<11;j++)
    {
        T[i][j]=0;
    }

    /*

    the outermost loop is to loop over different matrix chain spans
    "l" till the matrix chain span is equal to the #matrices "n".

    the next loop is to loop over all possible spans "l" considering
    the condition that assures not to cross matrices array boundary.

    the innermost loop is to check the best splitting point "k" that
    gives the minimum multiplications cost of matrices in span of "l".

    n: is the number of matrices
    l: is the matrix chain span length
    k: the splitting point
    i: starting index of span "l"
    j: ending index of span "l"
    T[i][j]= minimum multiplications cost of matrix chain span of length=l (i.e: l = j - i).
    D[i][j]= the value of k at which we split a matrix chain span of length=l to give minimum multiplications cost
    p[]: dimensions of the matrices

    **NOTE**
        2 matrices A1 and A2 of dimensions 10,5 and 5,20 respectively are represented int the p[]:Array as [10, 5, 20].

    */

    for(int l=2;l<=n;l++)
    for(int i=0;i<=n-l;i++)
    {
        int j=i+l;
        T[i][j]=INT_MAX;
        for(int k=i+1;k<j;k++)
        {
            int multCostAtK= T[i][k] + T[k][j] + p[i]*p[k]*p[j];
            if(multCostAtK<T[i][j]){T[i][j]=multCostAtK;D[i][j]=k;}
        }
    }
}

// Recursive to output the solution for both versions
void MatChainSol(int a, int b)
{
    if(a+1==b){cout<<"A"<<b;return;}
    int k=D[a][b];
    cout<<"(";
    MatChainSol(a,k);
    cout<<" x ";
    MatChainSol(k,b);
    cout<<")";
}

void Compute(int n, int caseNumber)
{
    //MatChainBottomUp(n);
    MatChainTopDown(n);
    cout<<"Case "<<caseNumber<<": ";
    MatChainSol(0,n);
    cout<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt","w",stdout);
    #endif // ONLINE_JUDGE

	int N,caseNumber=1;
    while(true)
    {
        scanf("%d",&N);
        if(N==0)return 0;

        int y,x;
        scanf("%d",&y);
        scanf("%d",&x);
        p[0]=y;
        p[1]=x;

        for(int i=2;i<=N;i++)
        {
            int x;
            scanf("%d",&x);
            scanf("%d",&x);
            p[i]=x;
        }

        Compute(N,caseNumber);
        caseNumber++;
    }

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
