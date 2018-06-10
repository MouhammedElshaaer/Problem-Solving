// UVA:     10810
//UVA Hnadle: mouhammedElshaaer

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
Type CountInvMerge(Type* a, int n, bool (*IsBefore)(Type&,Type&))
{
	int mid=n/2;
	Type val=0;
	int i=0, j=mid, k;
	Type* t=new Type[n];
	for(k=0;k<n;k++)
	{
        if(j==n || (i<mid && IsBefore(a[i],a[j])))
            t[k]=a[i++];
        else
        {
            val+=mid-i;
            t[k]=a[j++];
        }
	}
	for(i=0;i<n;i++) a[i]=t[i];
	delete t;
	return val;
}

template <class Type>
Type CountInv(Type* a, int n, bool (*IsBefore)(Type&,Type&))
{
    int mid=n/2;
    if(n<=1)
        return 0;

    return  CountInv(a,mid,IsBefore)+
            CountInv(a+mid,n-mid,IsBefore)+
            CountInvMerge(a,n,IsBefore);
}

bool IsBeforeInt(long long& a, long long& b)
{
	return a<b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //long long arr[]={4,5,1,2,6,7,79,2,264,26,246,24,624,6,47,53,8};
    long long arr[]={5,4,1};
    cout<<CountInv<long long>(arr,3,IsBeforeInt)<<endl;

    for(int i=0;i<3;i++)
    {
        cout<<arr[i]<<" ";
    }

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
