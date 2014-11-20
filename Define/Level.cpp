#include "Level.h"

Level::Level(int windowSize)
{
	// Fill m_tileIDs with -1 
	for (int i = 0; i < MAP_DIAMETER; i++)
	{
		m_tileIDs.push_back(vector<int>(MAP_DIAMETER, -1));
	}

	float tileHeight = windowSize / MAP_DIAMETER;
	float tileRadius = tileHeight / sqrt(3);
	float tileDiameter = 2 * tileRadius;
	float xThickness = (MAP_DIAMETER - 1) * tileDiameter * 3.0 / 4.0 + tileDiameter;
	float xMapOffset = (windowSize - xThickness) / 2.0;
	float yMapOffset = 0;
	float xOffset = tileRadius;
	float yOffset;
	int rowMin = 0;
	int rowMax = MAP_SIDE_LENGTH - 1;
	int tileID = 0;

	// c and r produce numbers matchin axial coordinates
	for (int c = 1-MAP_SIDE_LENGTH; c < MAP_SIDE_LENGTH; ++c)
	{
		yOffset = tileHeight*((MAP_DIAMETER - abs(rowMax - rowMin)) / 2.0);
		for (int r = rowMin; r <= rowMax; ++r)
		{
			m_tiles.push_back(new Tile(tileRadius, sf::Vector2f(xOffset + xMapOffset, yOffset + yMapOffset), sf::Vector3i(c, -c - r, r)));
			m_tileIDs[r + MAP_SIDE_LENGTH - 1][c + MAP_SIDE_LENGTH - 1] = tileID;
			tileID++;
			yOffset += tileHeight;
		}
		xOffset += tileDiameter * 3.0 / 4.0;
		c < 0 ? rowMin-- : rowMax--;
	}
	
	LoadCellTypes("files/SavedData.xml");
	m_isBeingSetup = true;
	//testing
	//InitializeCells();
}

bool Level::ProcessMouseInput(int mousex, int mouseY)
{
	return true;
}

void Level::LoadCellTypes(string file)
{
	string bitCode;
	int code = 0, direction, R = 255, G = 0, B = 0, rank = 11;
	bool noColor = false;
	ActionType actionType;
	char trash;
	CellType* newCellType;
	vector<CellRule> cellRules;

	XMLError error = m_cellTypeFile.LoadFile(file.c_str());
	
	XMLNode * pRoot = m_cellTypeFile.FirstChild();	
	XMLElement* pCellTypes = pRoot->FirstChildElement("CellTypes");

	XMLElement* pCellType = pCellTypes->FirstChildElement("CellType");
	while (pCellType != nullptr)
	{
		//if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;
		pCellType->QueryAttribute("R", &R);
		pCellType->QueryAttribute("G", &G);
		pCellType->QueryAttribute("B", &B);

		XMLElement* pRule = pCellType->FirstChildElement("Rule");
		cellRules.clear();
		while (pRule != nullptr)
		{
			bitCode = pRule->Attribute("Code");
			pRule->QueryAttribute("Direction", &direction);
			pRule->QueryAttribute("Action Type", &code);
			actionType = ActionType(code);

			code = 0;
			for (unsigned int i = 0; i < 6; ++i)
			{

				if (bitCode[0] == '1')
				{
					code += pow(2, rank);
				}
				rank--;
			}
			CellRule newRule;
			newRule.code = code;
			newRule.direction = direction;
			newRule.actionType = actionType;

			cellRules.push_back(newRule);
			pRule = pRule->NextSiblingElement("Rule");
		}
		newCellType = new CellType(m_cellTypes.size(), cellRules, sf::Color(R, G, B));
		m_cellTypes.push_back(newCellType);
		pCellType = pCellType->NextSiblingElement("CellType");
	}
}

void Level::InitializeCells()
{
	/*CellRule rule;
	rule.code = 72;
	rule.actionType = ActionType::Move;

	CellType *red = new CellType(m_cellTypes.size(), rule, sf::Color::Red);
	CellType *green = new CellType(m_cellTypes.size(), rule);
	*/

	CreateCell(*m_cellTypes[0], sf::Vector3i(0, 0, 0), 1);
	//CreateCell(*m_cellTypes[1], sf::Vector3i(0, 2, -2), 2);
	//CreateCell(*m_cellTypes[2], sf::Vector3i(0, 5, -5), 1);

	//CreateCell(*m_cellTypes[3], sf::Vector3i(3, 3, -2), 1);
	//CreateCell(*m_cellTypes[4], sf::Vector3i(-3, -3, 2), 1);
}

bool Level::CreateCell(CellType& celltype, sf::Vector3i location, int team)
{
	// check if tile is full
	if (GetTile(location)->GetCellIndex() != -1)
	{
		//cout << "Tried to create cell where one existed" << endl;
		return 0;
	}

	Cell *cell = new Cell(celltype, location, team);

	// create heapnode
	HeapNode cellNode;
	cellNode.cellIndex = cellCount;
	cellNode.priority = cell->GetPriority();
	m_turnHeap.push(cellNode);

	m_cells.push_back(cell);
	GetTile(location)->SetCell(*cell, cellCount++);

	return 1;
}

void Level::Draw(sf::RenderWindow& rw)
{
	for (int i = 0; i < m_tiles.size(); i++)
		m_tiles[i]->Draw(rw);
}

void Level::Update(Changes changes)
{
	for (int i = 0; i < changes.kills.size(); i++)
	{
		KillCell(changes.kills[i]);
	}
	for (int i = 0; i < changes.moves.size(); i++)
	{
		sf::Vector3i origin = changes.moves[i][0];
		sf::Vector3i target = changes.moves[i][1];

		MoveCell(origin, target);
	}
}

bool Level::MoveCell(sf::Vector3i origin, sf::Vector3i destination)
{
	Tile* originTile = GetTile(origin);

	if (IsOutOfBounds(destination))
		return 0;
	else
	{
		Tile* destinationTile = GetTile(destination);
		int originCellIndex = originTile->GetCellIndex();

		originTile->SetEmpty();
		destinationTile->SetCell(*m_cells[originCellIndex], originCellIndex);

		m_cells[originCellIndex]->SetLocation(destination);

		return 1;
	}
}

bool Level::KillCell(sf::Vector3i targetCell)
{
	if (IsOutOfBounds(targetCell))
		return 0;
	else
	{
		sf::Vector2i tileIndex = IndexFromCoordinates(targetCell);

		int tileID = m_tileIDs[tileIndex.x][tileIndex.y];
		int cellIndex = m_tiles[tileID]->GetCellIndex();
		if (cellIndex != -1)
		{
			m_cells[cellIndex]->SetIsAlive(false);
			m_tiles[tileID]->SetEmpty();
		}
		return 1;
	}
	
}

const bool Level::IsOutOfBounds(sf::Vector3i coordinates) const
{
	sf::Vector2i ij = IndexFromCoordinates(coordinates);
	
	if (ij.x < 0 || ij.x > MAP_DIAMETER - 1 || ij.y < 0 || ij.y > MAP_DIAMETER - 1 || (m_tileIDs[ij.x][ij.y] == -1))
		return true;
	return false;
}

Tile* Level::GetTile(sf::Vector3i coordinates)
{
	sf::Vector2i indices = IndexFromCoordinates(coordinates);
	int currID = m_tileIDs[indices.x][indices.y];
	return m_tiles[currID];
}

const Tile& Level::GetConstTile(sf::Vector3i coordinates) const
{
	sf::Vector2i indices = IndexFromCoordinates(coordinates);
	int currID = m_tileIDs[indices.x][indices.y];
	return *m_tiles[currID];
}

int Level::GetCellIndex(sf::Vector3i coordinates) const
{
	return GetConstTile(coordinates).GetCellIndex();
}

const Cell& Level::GetNextCell()
{
	HeapNode nextNode = m_turnHeap.top();

	//Continuing popping from heap until live cell is found
	while (!m_turnHeap.empty() && !m_cells[nextNode.cellIndex]->IsAlive())
	{
		m_turnHeap.pop();
		nextNode = m_turnHeap.top();
	}
	m_turnHeap.pop(); // pop the alive cell
	nextNode.priority -= 1; // reduce priority based on action
	
	m_turnHeap.push(nextNode); // push the alive cell back

	return (*m_cells[nextNode.cellIndex]);
}

const vector<int> Level::GetNeighborsByTeam(const Cell& cell) const
{
	vector<int> neighbors;
	sf::Vector3i origin = cell.GetLocation();
	for (int i = 0; i < 6; i++)
	{
		sf::Vector3i currNeighborCoordinates(origin.x + neighborOffsets[i][0], origin.y + neighborOffsets[i][1],
									origin.z + neighborOffsets[i][2]);
		if (!IsOutOfBounds(currNeighborCoordinates))
		{
			int currCellIndex = (GetConstTile(currNeighborCoordinates).GetCellIndex());
			neighbors.push_back(currCellIndex == -1 ? 0 : GetCell(currCellIndex).GetTeam());
		}
		else
		{
			neighbors.push_back(0);
		}
		
	}

	return neighbors;
}

const Cell& Level::GetCell(int index) const
{
	return *m_cells[index];
}

const Cell& Level::GetCell(sf::Vector3i coordinates) const
{
	int index = GetCellIndex(coordinates);
	return *m_cells[index];
}

const vector<Cell*>& Level::GetCellContainer() const
{
	return m_cells;
}

const vector<Tile*>& Level::GetTileContainer() const
{
	return m_tiles;
}

vector<vector<int>> Level::GetTileIDs() const
{
	return m_tileIDs;
}

sf::Vector2i Level::IndexFromCoordinates(sf::Vector3i coordinates) const
{
	return sf::Vector2i(coordinates.z + MAP_SIDE_LENGTH - 1, coordinates.x + MAP_SIDE_LENGTH - 1);
}

Level::~Level()
{
	for (int i = 0; i < m_tiles.size(); ++i)
	{
		delete m_tiles[i];
	}
	m_tiles.clear();

	for (int j = 0; j < m_cells.size(); ++j)
	{
		delete m_cells[j];
	}
	m_cells.clear();

	for (int k = 0; k < m_cellTypes.size(); ++k)
	{
		delete m_cellTypes[k];
	}
	m_cellTypes.clear();
}