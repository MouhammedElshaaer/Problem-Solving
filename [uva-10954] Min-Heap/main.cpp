// UVA:     10954
// UVA handle:    mouhammedElshaaer

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <math.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;

	void Initialize(int _sz)
	{
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

template<class Elem>
struct Heap
{
	Array<Elem> a;
	bool (*IsBefore)(int&, int&);

	void Initialize(bool (*_IsBefore)(int&, int&),int _sz)
	{
        IsBefore=_IsBefore;
        a.Initialize(_sz);
	}
	void Destroy()
	{
        a.Destroy();
    }
	int Child(int i)
	{
	    return i*2+1;
	}
	int Parent(int i)
	{
	    return floor( (i-1)/2 );
	}
	void MoveUp(int ind)
	{
	    int i=ind;
        while(i>0)
        {
            Elem    parent=a[Parent(i)],
                    curr=a[i];

            if(IsBefore(curr,parent))
            {
                Elem temp=parent;
                a[Parent(i)]=curr;
                a[i]=temp;
            }
            else
            {
                break;
            }
            i=Parent(i);
        }
	}
	void MoveDown(int ind)
	{
	    /**Loop Implementation**/

        int maxIndex=floor((a.n)/2);

        while(ind<maxIndex)
        {
            int lChild  =Child(ind),
                rChild  =lChild<(a.n-1)?lChild+1:lChild,
                curr    =ind;

                int child=IsBefore(a[lChild],a[rChild])?lChild:rChild;

                if(IsBefore(a[child],a[curr]))
                {
                    Elem temp=a[curr];
                    a[curr] =a[child];
                    a[child]=temp;

                    ind=child;
                }
                else
                {
                    break;
                }
        }

        /**Recursive Implementation**/
        /*
        int lChild  =Child(ind),
            rChild  =lChild+1,
            curr    =ind,
            heapSize=a.n;

        if(lChild<heapSize&&a[lChild]<a[curr])
        {
            curr=lChild;
        }
        if(rChild<heapSize&&a[rChild]<a[curr])
        {
            curr=rChild;
        }
        if(curr!=ind)
        {
            Elem temp=a[curr];
            a[curr] =a[ind];
            a[ind]=temp;
            MoveDown(curr);
        }*/
	}
	void Add(Elem e)
	{
	    a.AddLast(e);
	    MoveUp(a.n-1);
	}
	Elem GetFirst()
	{
	    return a[0];
	}
	Elem RetrieveFirst()
	{
	    Elem temp = a[0];
	    a[0]=a[a.n-1];
	    a.RemoveLast();
	    MoveDown(0);
	    return temp;
	}
	void print()
	{
	    a.print();
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
	return a<b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

    //freopen("F:\\FCI-CU\\Level-3\\2nd-term\\Algorithms\\Assignments\\G4_20150207_Assign01_ArrayHeap\\in.txt","r",stdin);
    //freopen("F:\\FCI-CU\\Level-3\\2nd-term\\Algorithms\\Assignments\\G4_20150207_Assign01_ArrayHeap\\out.txt","w",stdout);

    while(true)
    {
        int n,number,cost=0;

        cin>>n;

        Heap<int> heap;
        heap.Initialize(IsBeforeInt,n);

        if(n==0)
        {
            break;
        }
        else
        {
            while(n--&&cin>>number)
            {
                heap.Add(number);
            }
            while(heap.a.n>1)
            {
                int addition=0;
                addition+=heap.RetrieveFirst();
                addition+=heap.RetrieveFirst();
                heap.Add(addition);
                cost+=addition;
            }

            cout<<cost<<endl;
        }
        heap.Destroy();
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
