// UVA:     526
// UVA Username: mouhammedElshaaer

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>      // std::setw
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82];
char b[82];

int D[81][81]; // D[][] is the same for all versions (no memory reduction)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int substitute(char a, char b)
{
    if(a==b)    return 0;
    else        return 1;
}

int T1[81][81];
int EditDist1(int n, int m)
{
    if(T1[n][m]>=0){return T1[n][m];}
    if(n==0||m==0){T1[n][m]=n+m;D[n][m]=n+m;return T1[n][m];}

    int distances[3];
    distances[0]= substitute(a[n-1],b[m-1])   + EditDist1(n-1 ,m-1);   //Matching
    distances[1]=                         1   + EditDist1(n-1 ,m  );   //Deletion
    distances[2]=                         1   + EditDist1(n   ,m-1);   //Insertion

    T1[n][m]=distances[0];
    D [n][m]=1;
    for(int i=1;i<3;i++)
    {
        if(distances[i]<T1[n][m])
        {
            T1[n][m]=distances[i];
            D[n][m]=i+1;
        }
    }

    return T1[n][m];
}
int ComputeEditDist1(int N, int M) // Recursive - memoization - initialize T then call EditDist1(N,M);
{
    for(int i=0;i<81;i++)
    for(int j=0;j<81;j++)
    {
        T1[i][j]=-1;
    }

    return EditDist1(N,M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[81][81];
int ComputeEditDist2(int N, int M) // Bottom-up, do not save space
{
    for(int i=0;i<81;i++)
    for(int j=0;j<81;j++)
    {
        T2[i][j]=-1;
    }

    for(int n=0;n<=N;n++)
    for(int m=0;m<=M;m++)
    {
        if(n==0||m==0){T2[n][m]=n+m;continue;}
        int distances[3];
        distances[0]= substitute(a[n-1],b[m-1])   + T2[n-1  ][m-1   ];   //Matching
        distances[1]=                         1   + T2[n-1  ][m     ];   //Deletion
        distances[2]=                         1   + T2[n    ][m-1   ];   //Insertion

        T2[n][m]=distances[0];
        D [n][m]=1;
        for(int i=1;i<3;i++)
        {
            if(distances[i]<T2[n][m])
            {
                T2[n][m]=distances[i];
                D[n][m]=i+1;
            }
        }
    }
    return T2[N][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];
int ComputeEditDist3(int N, int M) // Bottom-up, use two rows only
{
    for(int i=0;i<2;i++)
    for(int j=0;j<81;j++)
    {
        T3[i][j]=-1;
    }

    int row=1;
    for(int n=0;n<=N;n++,row=1-row)
    for(int m=0;m<=M;m++)
    {
        if(n==0||m==0){T3[row][m]=n+m;continue;}
        int distances[3];
        distances[0]= substitute(a[n-1],b[m-1])   + T3[1-row][m-1   ];   //Matching
        distances[1]=                         1   + T3[1-row][m     ];   //Deletion
        distances[2]=                         1   + T3[  row][m-1   ];   //Insertion

        T3[row][m]=distances[0];
        D [n][m]=1;
        for(int i=1;i<3;i++)
        {
            if(distances[i]<T3[row][m])
            {
                T3[row][m]=distances[i];
                D[n][m]=i+1;
            }
        }
    }
    return T3[1-row][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];
int ComputeEditDist4(int N, int M) // Bottom-up, save maximum space
{
    for(int i=0;i<81;i++)
        T4[i]=-1;

    int prevT;
    for(int n=0;n<=N;n++)
    for(int m=0;m<=M;m++)
    {
        if(n==0||m==0){prevT=T4[m];T4[m]=n+m;continue;}
        int distances[3];
        distances[0]= substitute(a[n-1],b[m-1])   + prevT;          //Matching
        distances[1]=                         1   + T4[m     ];     //Deletion
        distances[2]=                         1   + T4[m-1   ];     //Insertion

        prevT=T4[m];

        int sol = distances[2], decision = 3;
        if (distances[0] < sol)
        {
            sol = distances[0];
            decision = 1;
        }
        if (distances[1] < sol)
        {
            sol = distances[1];
            decision = 2;
        }

        T4[m] = sol;
        D[n][m] = decision;
    }

    return T4[M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper
{
	int n,m;
	int oper;
};

Oper opers[81];

int EditDistSol(int N, int M) // Print the solution using D[][]
{
    int n = N, m = M;
	int i = 0;
	int shift = 0;

	while (n>0 && m>0)
	{
		if (D[n][m] == 2) //remove
		{
			Oper oper;
			oper.oper = 2;
			oper.n = n;
			n -= 1;
			opers[i++] = oper;
			continue;
		}
		else if (D[n][m] == 3) //insert
		{
			Oper oper;
			oper.oper = 3;
			oper.n = n;
			oper.m = b[m - 1];
			m -= 1;
			opers[i++] = oper;
			continue;
		}
		else if (D[n][m] == 1 && a[n - 1] != b[m - 1]) //replace
		{
			Oper oper;
			oper.oper = 1;
			oper.n = n;
			oper.m = b[m - 1];
			n -= 1;
			m -= 1;
			opers[i++] = oper;
			continue;
		}
		n--;
		m--;
	}

    while (true)
	{
		if (n == 0 && m == 0)break;

		if (n == 0 && m != 0)//insert
		{
			Oper oper;
			oper.oper = 3;
			oper.n = n;
			oper.m = b[m - 1];
			m -= 1;
			opers[i++] = oper;
		}
		if (n != 0 && m == 0)//remove
		{
			Oper oper;
			oper.oper = 2;
			oper.n = n;
			n -= 1;
			opers[i++] = oper;
		}
	}

	int c = 0;
	for (int j = i - 1; j >= 0; j--)
	{
		c++;

		cout << c << " ";
		Oper curr = opers[j];
		switch (curr.oper){
		case 1:{
            cout << "Replace "<< curr.n + shift<< "," << char(curr.m);
			break;
		}

		case 2:{
            cout << "Delete " << curr.n + shift;
			shift--;
			break;
		}

		case 3:{
            cout << "Insert " << curr.n +shift+1<< "," << char(curr.m);
			shift++;
			break;
		}
		}
		cout << endl;

	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) // Here we can choose the method
{
    //return ComputeEditDist1(N,M);
	//return ComputeEditDist2(N,M);
	//return ComputeEditDist3(N,M);
	return ComputeEditDist4(N,M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Compute() // Get input and call ComputeEditDist()
{
	int cas=0;
	while(true)
	{
		a[0]=0; b[0]=0;
		if(!fgets(a,82,stdin)) break; fgets(b,82,stdin);
		a[strlen(a)-1]=0;
		b[strlen(b)-1]=0;
		if(cas) cout<<endl; // print an empty line between test cases
		int N=strlen(a), M=strlen(b);
		cout<<ComputeEditDist(N,M)<<endl;
		EditDistSol(N,M);
		cas++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt","w",stdout);
    #endif // ONLINE_JUDGE

	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
