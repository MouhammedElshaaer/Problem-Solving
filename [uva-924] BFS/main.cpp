// UVA:     924
//UVA handle: mouhammedElshaaer

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <stdlib.h>
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

struct Node
{
    int nodeLevel;
	Array<int> adj;

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
	void Connect(int src, int dst)
	{
	    nodes[src].adj.AddLast(dst);

	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
struct Queue
{
	int f, n;
	Type* elems;

	void Initialize(int size)
	{
        f=0;
        n=0;
        elems=new Type[size];
	}
	void Destroy()
	{
	    delete elems;
	}
	void Add(Type t)
	{
	    elems[n++]=t;
	}
	Type Pop()
	{
	    if(f<n)
        {
            return elems[f++];
        }
        else
        {
            throw 1;
        }

	}
	Type Peek()
	{
	    if(f<n)
        {
            return elems[f];
        }
        else
        {
            throw 1;
        }
	}
	int Num()
	{
	    return n-f;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

    //freopen("F:\\FCI-CU\\Level-3\\2nd-term\\Algorithms\\Assignments\\Ass3\\G4_20150207_Assign03_Graphs\\in.txt","r",stdin);
    //freopen("F:\\FCI-CU\\Level-3\\2nd-term\\Algorithms\\Assignments\\Ass3\\G4_20150207_Assign03_Graphs\\out.txt","w",stdout);

    int employees,friendSetNumber,testCasesNumber,sourceNode;
    Graph graph;

    cin>>employees;
    graph.Initialize(employees);

    /****************Constructing The Graph****************/
    for(int i=0;i<employees;i++)
    {
        cin>>friendSetNumber;
        while(friendSetNumber--)
        {
            int f;
            cin>>f;
            graph.Connect(i,f);
        }
    }
    /******************************************************/

    cin>>testCasesNumber;
    while(testCasesNumber--&&cin>>sourceNode)
    {
        Queue<int> q;
        vector<bool>    visitied(graph.n,false);
        vector<int>     days    (graph.n+1,0);
        int boomDay     =0;

        q.Initialize(2500);
        q.Add(sourceNode);
        visitied[sourceNode]=true;
        graph.nodes[sourceNode].nodeLevel=0;
        /*******************BFS*******************/
        while(q.Num()>0)
        {
            for(int j=0;j<graph.nodes[q.Peek()].adj.n;j++)
            {
                int adjNode=graph.nodes[q.Peek()].adj[j];
                if(!visitied[adjNode])
                {
                    graph.nodes[adjNode].nodeLevel=graph.nodes[q.Peek()].nodeLevel+1;
                    q.Add(adjNode);
                    visitied[adjNode]=true;
                    days[(graph.nodes[adjNode].nodeLevel)]++;
                }
            }
            boomDay=days[graph.nodes[q.Peek()].nodeLevel+1]>days[boomDay]?graph.nodes[q.Peek()].nodeLevel+1:boomDay;
            q.Pop();

        }
        /****************End OF BFS****************/

        if(days[boomDay]!=0)
        {
            cout<<days[boomDay]<<" ";
            cout<<boomDay<<endl;
        }
        else
        {
            cout<<0<<endl;
        }

        q.Destroy();
    }
    graph.Destroy();

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
