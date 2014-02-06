#include <stack>
#include <iostream>

#include "node.h"

//name vom knote
void Node::SetName(std::string Name)
{
	m_Name = Name;
}

void Node::AddNeighbor(int NeighborIndex, int Distance)
{
	m_lNeighbors.push_back(Neighbor(NeighborIndex, Distance));
}

void Node::SetVisited()
{
	m_Visited = true;
}

bool Node::Visited()
{
	return m_Visited;
}

void Map::AddNode(std::string Name, int ID)
{
	if (m_lNodes.size() < (unsigned int)ID)
	{
		if (m_lNodes.size() > 1000000)
			m_lNodes.resize(ID * 3); // 3 times the wanted size
		else
			m_lNodes.resize(ID * 10); // 10 times the wanted size
		//m_lNodes.resize(3000000);
	}

	m_lNodes[ID - 1].SetName(Name);
}

void Map::AddNeighbor(int NodeID, int NeighborID, int Distance)
{
	m_lNodes[NodeID - 1].AddNeighbor(NeighborID - 1, Distance);
}

void Map::GetWay()
{
	std::stack<int> NodeIndexStack;
	//std::stack<int> DistanceStack;
	NodeIndexStack.push(m_StartNode); //start node to stack
	//DistanceStack.push(0);

	while (!NodeIndexStack.empty())
	{
		int CurrentNode = NodeIndexStack.top(); // current = last entry on stack
		Node *pCurNode = &m_lNodes[CurrentNode]; // ein object vom activen knoten

		// set visited
		m_lNodes[CurrentNode].SetVisited();

		// set new distance if needed
		/*
		* alle nachbarn von dem activen knoten durchen
		* zurueckgelegte distanz + distanz[i] < zurueckgelegte distanz zum gewaehlten nachbarn
		* sonst kuerzeren weg nehmen und parent setzen
		*
		*/
		for (unsigned i = 0; i < pCurNode->m_lNeighbors.size(); i++)
		{
			Node *pNNode = &m_lNodes[pCurNode->m_lNeighbors[i].m_NodeIndex];

			if (pCurNode->m_CurrentDistance + pCurNode->m_lNeighbors[i].m_Distance < pNNode->m_CurrentDistance || (pNNode->m_CurrentDistance == 0 && pCurNode->m_lNeighbors[i].m_NodeIndex != m_StartNode))
			{
				pNNode->m_CurrentDistance = pCurNode->m_CurrentDistance + pCurNode->m_lNeighbors[i].m_Distance;
				pNNode->m_CurrentParent = CurrentNode;

			}
		}

		// get neighbor with smallest distance
		int SmallesID = -1;
		/*

		wieder alle nachbarn vom activen knoten durchgehen
		ueberpruefen ob er schon besucht wurde, falls nicht dann gucken ob momentan zurueck gelegte distanz auch wirklich die kleinste ist

		*/
		for (unsigned i = 0; i < m_lNodes[CurrentNode].m_lNeighbors.size(); i++)
		{
			Node *pNNode = &m_lNodes[pCurNode->m_lNeighbors[i].m_NodeIndex];
			if (!pNNode->Visited())
			{
				if (SmallesID == -1 || (pNNode->m_CurrentDistance < m_lNodes[m_lNodes[CurrentNode].m_lNeighbors[SmallesID].m_NodeIndex].m_CurrentDistance))
					SmallesID = i;
			}
		}

		// refresh stack
		if (SmallesID > -1)
		{
			NodeIndexStack.push(m_lNodes[CurrentNode].m_lNeighbors[SmallesID].m_NodeIndex);
		}
		else
		{
			NodeIndexStack.pop();
		}
	}

	m_Done = true;
}

void Map::PrintWay()
{
	std::vector<int> lWay;
	int Index = m_FinishNode;
	while (Index != m_StartNode)
	{
		lWay.push_back(Index + 1);
		Index = m_lNodes[Index].m_CurrentParent;
	}

	std::cout << "Z" << m_StartNode + 1 << " ";
	for (int i = lWay.size() - 1; i >= 0; i--)
		std::cout << "Z" << lWay[i] << " ";

	std::cout << std::endl;
}

int Map::Costs()
{
	if (m_Done)
		return m_lNodes[m_FinishNode].m_CurrentDistance;
	return -1;
}
