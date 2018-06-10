// UVA:     10245
// UVA Username: mouhammedElshaaer

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>     // please use the built-in sqrt() function
#include <float.h>
#include <stdio.h>




using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid =n/2;
    int i   =0;
    int j   =mid;
    int k;
    Type* temp=new Type[n];

    for(k=0;k<n;k++)
    {
        if(j==n || (i<mid && IsBefore(a[i],a[j])))
        {
            temp[k]=a[i++];
        }
        else
        {
            temp[k]=a[j++];
        }
    }

    for(int i=0;i<n;i++) a[i]=temp[i];
    delete temp;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    if(n<=1) return;

    int mid= n/2;

    MergeSort(a,mid,IsBefore);
    MergeSort(a+mid,n-mid,IsBefore);

    Merge(a,n,IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
	double x,y;
};

bool IsBeforeX(Point& a, Point& b)
{
    return a.x<b.x;
}
bool IsBeforeY(Point& a, Point& b)
{
    return a.y<b.y;
}

double dist(Point& a, Point& b)
{
    return sqrt( pow(b.x-a.x,2) + pow(b.y-a.y,2) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ClosestPairMerge(Point* p, int n, double m, bool (*IsBefore)(Point& a, Point& b))
{

    double left,right,symmetryAxe;

    left    =p[n/2-1].x;
    right   =p[n/2].x;

    symmetryAxe= (left+right)/2.0;

    Point* strip=new Point[n];

    int _size=0;

    for(int i=0;i<n;i++)
    {
        if(abs(symmetryAxe-p[i].x)<=m)
        {
            strip[i].x=p[i].x;
            strip[i].y=p[i].y;
            _size++;
        }
        else
        {
            strip[i].x=DBL_MAX;
            strip[i].y=DBL_MAX;
        }
    }

    MergeSort(strip,n,IsBefore);

    double minDist=m;
    for(int i=0;i<_size;i++)
    {
        Point point=strip[i];

        for(int j=i+1;j<_size;j++)
        {
            double distance=dist(point,strip[j]);
            if(distance<=m)
            {
                minDist=distance<=minDist?distance:minDist;
            }
        }
    }
    delete strip;
    return minDist;
}

// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n)
{
    if(n==1) return DBL_MAX;

    int mid=n/2;

    double  a=ClosestPair(p,mid);
    double  b=ClosestPair(p+mid,n-mid);

    double  m=a;
            m=b<m?b:m;

    return ClosestPairMerge(p,n,m,IsBeforeY);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt","w",stdout);
    #endif

    int N;
    while(true)
    {
        scanf("%d",&N);

        if(N==0) return 0;

        Point* p=new Point[N];
        for(int i=0;i<N;i++)
        {
            scanf("%lf %lf",&p[i].x,&p[i].y);
        }

        MergeSort(p,N,IsBeforeX);
        double minDist=ClosestPair(p,N);
        if(minDist<10000)
        {
            printf("%.4lf\n",minDist);
        }
        else
        {
            printf("INFINITY\n");
        }

        delete p;
    }

	return 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////
