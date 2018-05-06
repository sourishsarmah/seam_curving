#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

struct AdjListNode
{
	int dest;
	int val;
	struct AdjListNode *next;
};

struct AdjList
{
	struct AdjListNode *head;
};

class Graph
{
private:
	int V;
	struct AdjList *array;
public:
	Graph(int V)
	{
		this->V = V;
		array = new AdjList[V];
		for(int i = 0; i < V; ++i)
			array[i].head = NULL;
	}
	AdjListNode *newNode(int dest, int val)
	{
		AdjListNode *node = new AdjListNode;
		node->dest = dest;
		node->val = val;
		node->next = NULL;
		return node;
	}
	void addEdge(int src, int dest, int val)
	{
		AdjListNode *node = newNode(dest,val);
		node->next = array[src].head;
        array[src].head = node;
	}
	void printGraph()
	{
		for (int v = 0; v < V; ++v)
		{
			AdjListNode *temp = array[v].head;
			cout<<"\n Adjacency list of vertex "<<v<<"\n head ";
			while (temp!=NULL)
			{
				cout<<"->"<<temp->dest<<"="<<temp->val;
				temp = temp->next;
			}
			cout<<endl;
		}
	}
};

class Image
{
  private:
  public:
	int **pixels;
	int row;
	int col;
	int size;

	Image(string file)
	{
		fstream fin;
		char c[10];
		int max_val;
		fin.open(file);
		fin >> c >> col >> row;
		fin >> max_val;
		cout << c << endl;
		cout << "Columns=" << col << endl;
		cout << "Rows=" << row << endl;
		pixels = new int *[row];
		for (int i = 0; i < row; i++)
		{
			pixels[i] = new int[col];
		}
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
				fin >> pixels[i][j];
		}
		size = row * col;
	}
	void display_pixels()
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
				cout << pixels[i][j] << "\t";
			cout << endl;
		}
	}
	int coord_to_flat(int x, int y)
	{
		return (x*col+y)+1;
	}
	void construct_graph(Graph &g)
	{
		for (int i=0; i<col;i++)
		{
			g.addEdge(0, i+1, pixels[0][i]);
		}
		for (int i=0; i<col; i++)
		{
			g.addEdge(size-col+1+i, size+1, pixels[row-1][i]);
		}
		for (int i=0; i<row-1; i++)
		{
			for (int j=0; j<col; j++)
			{
				int src = coord_to_flat(i,j);
				int dest =  coord_to_flat(i+1,j);
				int val = abs(pixels[i][j]-pixels[i+1][j]);
				g.addEdge(src, dest, val);
				if (j-1>=0)
				{
					int dest =  coord_to_flat(i+1,j-1);
					int val = abs(pixels[i][j]-pixels[i+1][j-1]);
					g.addEdge(src, dest, val);
				}
				if (j+1<col)
				{
					int dest =  coord_to_flat(i+1,j+1);
					int val = abs(pixels[i][j]-pixels[i+1][j+1]);
					g.addEdge(src, dest, val);
				}
			}
		}

	}
};
int main()
{
	Image img("sample.pgm");
	img.display_pixels();
	Graph g(img.size+2);
	img.construct_graph(g);
	g.printGraph();
	return 0;
}