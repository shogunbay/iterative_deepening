#ifndef H_NODE
#define H_NODE

#include <string>
#include <vector>

class Node
{
	enum
	{
		TYPE_START = 0,
		TYPE_FINISH,
		TYPE_NODE
	};

	std::string m_Name;
	bool m_Visited;
	
	class Neighbor
	{
	public:
		int m_NodeIndex;
		int m_Distance;

		Neighbor(int NodeIndex, int Distance) :m_NodeIndex(NodeIndex), m_Distance(Distance) {}
	};

public:
	std::vector<Neighbor> m_lNeighbors;
	int m_CurrentDistance;
	int m_CurrentParent;

	Node() { m_Visited = false; m_CurrentDistance = 0; }

	void SetName(std::string Name);
	void AddNeighbor(int NeighborIndex, int Distance);
	void SetVisited();
	bool Visited();
};

class Map
{
	std::vector<Node> m_lNodes;
	bool m_Done;

public:
	Map() { m_Done = false; }

	int m_StartNode;
	int m_FinishNode;

	void AddNode(std::string Name, int ID);
	void AddNeighbor(int NodeID, int NeighborID, int Distance);

	void GetWay();

	void PrintWay();

	int Costs();
};

#endif // !H_NODE
