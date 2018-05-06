#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct AdjListNode
{
	int dest;
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
	AdjListNode *newAdjListNode(int dest)
	{
		AdjListNode *newNode = new AdjListNode;
		newNode->dest = dest;
		newNode->next = NULL;
		return newNode;
	}
	void addEdge(int src, int dest)
	{
		AdjListNode *newNode = newAdjListNode(dest);
		newNode->next = array[src].head;
		array[src].head = newNode;
		newNode = newAdjListNode(src);
		newNode->next = array[dest].head;
		array[dest].head = newNode;
	}
	void printGraph()
	{
		int v;
		for (v = 0; v < V; ++v)
		{
			AdjListNode *pCrawl = array[v].head;
			cout << "\n Adjacency list of vertex " << v << "\n head ";
			while (pCrawl)
			{
				cout << "-> " << pCrawl->dest;
				pCrawl = pCrawl->next;
			}
			cout << endl;
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
		cout << "Columns=" << col << endl
			 << "Rows=" << row << endl;
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
		return x * col + y;
	}
};
int main()
{
	Image Img("sample.pgm");
	Img.display_pixels();
	return 0;
}