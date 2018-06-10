// UVA:     11631
// UVA Handle: mouhammedElshaaer

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;

	void Initialize(int _sz)
	{
	    //sz=1;
	    sz=_sz;
	    n=0;
        arr=new int[sz];

	}
	void Destroy()
	{
        delete arr;
	}
	void AddLast(Value v)
	{
        if(n<sz)
        {
            arr[n++]=v;
        }
        else
        {
            sz*=2;
            int *newArr=new int[sz];
            for(int i=0;i<n;i++)
            {
                newArr[i]=arr[i];
            }
            newArr[n++]=v;
            arr=newArr;
        }
	}
	void RemoveLast()
	{
        if(n>0){n--;}
        else{throw 1;}

	}
	Value& operator[](int i)
	{
	    if(i<n){return arr[i];}
	    else{throw 1;}

    }
    void print()
    {
        for(int i=0;i<n;i++)
        {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
	int n;
	Array<int> parent;
	Array<int> num_nodes;

	void Initialize(int _n)
	{
	    n=_n;
	    parent.Initialize(n);
	    num_nodes.Initialize(n);

	    for(int i=0;i<n;i++)
	    {
	        parent.AddLast(i);
	    }

        for(int i=0;i<n;i++)
        {
            num_nodes.AddLast(1);
        }
	}
	void Destroy()
	{
        parent.Destroy();
        num_nodes.Destroy();
	}
	int Find(int i)
	{
	    while(parent[i]!=i){
            i=parent[i];
	    }
	    return i;
	}
	bool Union(int i, int j)
	{
        int root1=Find(i),
            root2=Find(j);

        if(root1==root2)
        {
            return false;
        }
        else
        {
            if(num_nodes[root1]<num_nodes[root2])
            {
                parent[root1]=root2;
                num_nodes[root2]+=num_nodes[root1];
            }
            else
            {
                parent[root2]=root1;
                num_nodes[root1]+=num_nodes[root2];
            }
            return true;
        }
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid=n/2;
	int i=0, j=mid, k;
	Type* t=new Type[n];
	for(k=0;k<n;k++)
	{
        if(j==n || (i<mid && IsBeforeEdge(a[i],a[j])))
            t[k]=a[i++];
        else
        {
            t[k]=a[j++];
        }
	}
	for(i=0;i<n;i++) a[i]=t[i];
	delete t;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid=n/2;
    if(n<=1)
        return;

    MergeSort(a,mid,IsBefore);
    MergeSort(a+mid,n-mid,IsBefore);

    Merge(a,n,IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int u, v;
	long long w;
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
	return a.w<b.w;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long kruskal(Edge* arr,int edgesNumber, int nodesNumber)
{
    MergeSort(arr,edgesNumber,IsBeforeEdge);

    DisjointSets mySets;
    mySets.Initialize(nodesNumber);
    long long minCost=0;

    for(int i=0;i<edgesNumber;i++)
    {
        if(mySets.Union(arr[i].u,arr[i].v))
        {
            minCost+=arr[i].w;
        }
    }

    return minCost;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{


    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    while(true)
    {

        int m,n;
        cin>>m>>n;

        if(n==0&&m==0)
            {
                return 0;
            }

        Edge* arr=new Edge[n];
        long long x,y,z;
        int edgesNumber=n;
        long long sum=0;


        while(n--)
        {
            cin>>x>>y>>z;

            Edge e;
            e.u=x;  e.v=y;  e.w=z;
            arr[n]=e;

            sum+=z;
        }
        long long minCost = kruskal(arr,edgesNumber,m);
        cout<<sum-minCost<<endl;
    }






	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
