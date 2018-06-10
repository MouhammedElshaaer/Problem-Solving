// UVA:     534
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
            for(int i=0; i<n; i++)
            {
                newArr[i]=arr[i];
            }
            newArr[n++]=v;
            arr=newArr;
        }
    }
    void RemoveLast()
    {
        if(n>0)
        {
            n--;
        }
        else
        {
            throw 1;
        }

    }
    Value& operator[](int i)
    {
        if(i<sz)
        {
            return arr[i];
        }
        else
        {
            throw 1;
        }

    }
    void fill(int val)
    {
        for(int i=0; i<sz; i++)arr[i]=val;
        n=sz;
    }
    void print()
    {
        for(int i=0; i<n; i++)
        {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int		v;  // id of the adjacent node
    double	w;  // edge weight = distance between the two nodes
};

struct Node
{
    int x,y; // x and y coordinates of the node
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
    }
    void Destroy()
    {
        nodes.Destroy();
    }
    void Connect(int src, int dst, double weight)
    {
        Edge e;
        e.v=dst;
        e.w=weight;
        nodes[src].adj.AddLast(e);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100)
{
    double a=0, b=v, s;
    for(int i=0; i<n; i++)
    {
        s=(a+b)/2;
        if((s*s)<v)
            a=s;
        else
            b=s;
    }
    return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

double calc_dist(Node& node1, Node& node2)
{
    int x1=node1.x, y1=node1.y,
        x2=node2.x, y2=node2.y;

    return Sqrt( ( pow( (x1-x2), 2 ) + pow( (y1-y2), 2 ) ) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

Graph construct_graph(Array<Node>& stones)
{
    Graph graph;

    graph.Initialize(stones.n);

    Node node;
    node.Initialize();

    node.x=stones[0].x, node.y=stones[0].y;

    graph.nodes.AddLast(node);


    for(int i=0; i<graph.n; i++)
    {
        for(int j=i+1; j<graph.n; j++)
        {
            Node node;
            node.Initialize();

            node.x=stones[j].x, node.y=stones[j].y;

            graph.nodes.AddLast(node);

            double distance=calc_dist(graph.nodes[i],graph.nodes[j]);

            graph.Connect(i,j,distance);
            graph.Connect(j,i,distance);
        }
    }
    return graph;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int minEdge(Array<double>& d, vector<bool>& v)
{
    int minEdge=1;
    for(int i=1; i<d.n; i++)
    {
        if(!v[i])
        {
            minEdge= d[i]<d[minEdge]?i:minEdge;
        }
    }
    return minEdge;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////

double minDist(Array<double>& d, Array<int>& p, int src, int dest)
{
    int i=dest;
    double minDist=d[i];
    while(i!=p[i])
    {
        minDist=max(minDist,d[p[i]]);
        i=p[i];
    }
    d.Destroy();
    p.Destroy();
    return minDist;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

double prim(Array<Node>& stones, int src, int dest)
{
    Graph   graph=construct_graph(stones);

    vector<bool>    v(graph.n, false);
    Array<double>   d;
    Array<int>      p;
    Array<int>      s;

    d.Initialize(graph.n);
    p.Initialize(graph.n);
    s.Initialize(graph.n);
    d.fill(INT_MAX);

    v[src]=true;
    d[src]=src;
    p[src]=src;
    s.AddLast(src);

    while(!v[dest])
    {
        int currNode=s[s.n-1];
        int currAdjs=graph.nodes[currNode].adj.n;
        int minEdgeIndx;
        for(int i=0; i<currAdjs; i++)
        {
            Edge currEdge=graph.nodes[currNode].adj[i];
            if(!v[currEdge.v])
            {
                if(currEdge.w<d[currEdge.v])
                {
                    d[currEdge.v]=currEdge.w;
                    p[currEdge.v]=currNode;
                }
            }

        }

        minEdgeIndx=minEdge(d,v);
        int nextNode=minEdgeIndx;
        s.AddLast(nextNode);
        v[nextNode]=true;
    }

    for(int i=0;i<graph.n;i++)
    {
        (graph.nodes[i]).Destroy();
    }
    graph.Destroy();
    return minDist(d,p,src,dest);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);

    while(true)
    {
        int n,x,y;
        static int scenarioNumber=1;
        if(cin>>n && n<=0)
        {
            cout<<endl;
            break;
        }


        Array<Node> stones;
        stones.Initialize(n);


        cin>>x;
        cin>>y;

        Node src;
        src.Initialize();
        src.x=x;
        src.y=y;

        stones.AddLast(src);

        cin>>x;
        cin>>y;

        Node dest;
        dest.Initialize();
        dest.x=x;
        dest.y=y;

        stones.AddLast(dest);

        n-=2;
        while(n--)
        {
            cin>>x;
            cin>>y;

            Node node;
            node.Initialize();
            node.x=x;
            node.y=y;

            stones.AddLast(node);
        }

        double minDist=prim(stones,0,1);

        cout<<"Scenario #"<<scenarioNumber++<<endl;
        cout.precision(3);
        cout<<fixed<<"Frog Distance = "<<minDist<<endl<<endl;

        stones.Destroy();
    }


    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
