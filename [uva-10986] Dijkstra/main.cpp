// UVA:     10986
// UVA Username: mouhammedElshaaer

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <math.h>
#include <vector>
#include <limits.h>

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
        arr=new Value[sz];

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
            Value *newArr=new Value[sz];
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
	    if(i<sz){return arr[i];}
	    else{throw 1;}

    }
    void fill(int val)
    {
        for(int i=0;i<sz;i++)arr[i]=val;
        n=sz;
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

template<class Elem>
struct Heap
{
    Array<int> pos;
	Array<Elem> a;
	bool    (*IsBefore)(Elem& a, Elem& b);
	int     (*getElemId)(Elem& a);

	void Initialize(bool (*_IsBefore)(Elem& a, Elem& b), int (*_getElemId)(Elem& a), int _sz)
	{
        IsBefore=_IsBefore;
        getElemId=_getElemId;
        a.Initialize(_sz);
        pos.Initialize(_sz);
        pos.fill(-1);
	}
	void Destroy()
	{
        a.Destroy();
        pos.Destroy();
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
                pos[getElemId(a[i])]=i;
            }
            else
            {
                break;
            }
            i=Parent(i);
        }

        pos[getElemId(a[i])]=i;
	}
	void MoveDown(int ind)
	{
	    /****Loop Implementation****/

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

                    pos[getElemId(a[curr])]=ind;

                    ind=child;
                }
                else
                {
                    break;
                }
        }
        pos[getElemId(a[ind])]=ind;
        //return Parent(ind);

        /****Recursive Implementation****/
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
	    pos[getElemId(temp)]=-1;
	    if(a.n>1)
        {
            a[0]=a[a.n-1];
            pos[getElemId(a[0])]=0;
        }
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

struct Edge
{
	int		v;
	int		w;
};

struct Node
{
	int nodeLevel;
	Array<Edge> adj;

	void Initialize()
	{
	    adj.Initialize(1);
	}
	void Destroy()
	{
        adj.Destroy();
	}
};


struct Graph
{
	int n;
	Array<Node> nodes;

	void Initialize(int _n)
	{
	    n=_n;
	    nodes.Initialize(n);
	    for(int i=0;i<n;i++)
        {
            Node node;
            node.Initialize();
            nodes.AddLast(node);
        }
	}
	void Destroy()
	{
        nodes.Destroy();
	}
	void Connect(int src, int dst, int weight)
	{
	    Edge e;     e.v=dst;    e.w=weight;
	    nodes[src].adj.AddLast(e);
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Edge& a, Edge& b)
{
	return a.w<b.w;
}

int getElemId(Edge& a)
{
    return a.v;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long Dijkstra(Graph myGraph, int counter, int src, int dest)
{
    vector<bool>    v(myGraph.n, false);
    Array<int>      d;
    Heap<Edge>      heap;
    Array<int>      s;
    Edge            e;

    heap.Initialize(IsBefore,getElemId, myGraph.n);
    s.Initialize(myGraph.n);
    d.Initialize(myGraph.n);
    d.fill(-1);
    e.v=src;  e.w=0;

    v[src]=true;
    d[src]=0;
    s.AddLast(src);
    heap.Add(e);

    while(heap.a.n>0)
    {
        int currNode=heap.GetFirst().v;
        int currAdjs=myGraph.nodes[currNode].adj.n;

        for(int i=0;i<currAdjs;i++)
        {
            Edge currEdge=myGraph.nodes[currNode].adj[i];
            if(v[currEdge.v])
                continue;

            int currDestCost=d[currNode]+currEdge.w;

            if(heap.pos[currEdge.v]!=-1)
            {
                int prevDestCost=(heap.a[heap.pos[currEdge.v]]).w;
                if(currDestCost<prevDestCost)
                {
                    heap.a[heap.pos[currEdge.v]].w=currDestCost;
                    d[currEdge.v]=currDestCost;
                    heap.MoveUp(heap.pos[currEdge.v]);
                }
            }
            else
            {
                currEdge.w=currDestCost;
                d[currEdge.v]=currEdge.w;
                heap.Add(currEdge);
            }
        }

        int nextNode=heap.RetrieveFirst().v;
        s.AddLast(nextNode);
        v[nextNode]=true;
        if(v[dest]) return d[dest];
    }

    return d[dest];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);

    int N;
    cin>>N;

    for(int i=0;i<N;i++)
    {
        int n,m,S,T;
        cin>>n>>m>>S>>T;


        if(m==0)
        {
            cout<<"Case #"<<i+1<<": unreachable\n";
        }
        else
        {
            Graph myGraph ;
            myGraph.Initialize(n);

            while(m--)
            {
                int src,dest,cost;
                cin>>src>>dest>>cost;
                myGraph.Connect(src,dest,cost);
                myGraph.Connect(dest,src,cost);
            }

            int minCost = Dijkstra(myGraph, n, S, T);

            if(minCost>=0)
            {
                cout<<"Case #"<<i+1<<": "<<minCost<<endl;
            }
            else
            {
                cout<<"Case #"<<i+1<<": unreachable\n";
            }
        }
    }

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
