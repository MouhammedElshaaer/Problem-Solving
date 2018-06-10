// UVA:     10608
//UVA handle: mouhammedElshaaer

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdlib.h>
using namespace std;

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

int main()
{

    //freopen("F:\\FCI-CU\\Level-3\\2nd-term\\Algorithms\\Assignments\\Ass2\\G4_20150207_Assign02_DisjointSets\\in.txt","r",stdin);
    //freopen("F:\\FCI-CU\\Level-3\\2nd-term\\Algorithms\\Assignments\\Ass2\\G4_20150207_Assign02_DisjointSets\\out.txt","w",stdout);

    int testCaseNumber,n,m;
    cin>>testCaseNumber;
    while(testCaseNumber--)
    {
        int friend1,friend2,maxSet=1;
        cin>>n>>m;
        DisjointSets setA;
        setA.Initialize(n);
        while(m--&&cin>>friend1>>friend2)
        {
            friend1--;  friend2--;
            setA.Union(friend1,friend2);
            maxSet=max(setA.num_nodes[setA.Find(friend1)],maxSet);
        }
        cout<<maxSet<<endl;
    }


	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
