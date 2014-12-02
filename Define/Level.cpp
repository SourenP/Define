#include "Level.h"

Level::Level(int windowSize)
{
	// Fill m_tileIDs with -1 
	for (unsigned int i = 0; i < MAP_DIAMETER; i++)
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

bool Level::ProcessMouseInput(int mouseX, int mouseY)
{
	double tileRadius = m_tiles[0]->GetRadius();

	float tileDiameter = 2 * tileRadius;
	float xThickness = (MAP_DIAMETER - 1) * tileDiameter * 3.0 / 4.0 + tileDiameter;
	float xMapOffset = (800 - xThickness) / 2.0;
	float yMapOffset = 0;

	cout << mouseX<< ", " << mouseY << std::endl;

	double realY = (((-1 * (mouseX - 400 - tileRadius)) / 3) + ((sqrt(3) * (mouseY - tileRadius - 400)) / 3)) / tileRadius;
	double realX = (2 * (mouseX - 400 - tileRadius)) / (3 * tileRadius);
	cout << realX << ", " << realY << std::endl;

	sf::Vector3f cubeCoords = CoordinateConversions::ConvertAxialToCube(sf::Vector2f(realX, realY));
	cout << cubeCoords.x << ", " << cubeCoords.y << ", " << cubeCoords.z << std::endl;
	
	sf::Vector3i roundedCoords = RoundToNearestTile(cubeCoords);
	cout << roundedCoords.x << ", " << roundedCoords.y << ", " << roundedCoords.z<< std::endl;

	cout << "**************************" << std::endl;
	if (IsOutOfBounds(roundedCoords))
	{
		if (m_currSetupTile != 0)
			m_currSetupTile->Unmark();
		return false;
	}
	else
	{
		sf::Vector2i tileIndicies = GetIndexFromCoordinates(roundedCoords);
		int tileID = m_tileIDs[tileIndicies.x][tileIndicies.y];
		if (m_currSetupTile != 0)
			m_currSetupTile->Unmark();
		m_currSetupTile = (m_tiles[tileID]);
		m_currSetupTile->MarkForSetup();
		return true;
	}
}

void Level::LoadCellTypes(string file)
{
	string bitCode;
	int code = 0, direction, R = 255, G = 0, B = 0, rank = 11;
	bool noColor = false;
	ActionType actionType;
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
			rank = 11;
			bitCode = pRule->Attribute("Code");
			pRule->QueryAttribute("Direction", &direction);
			pRule->QueryAttribute("Action", &code);
			actionType = ActionType(code);

			code = 0;
			for (unsigned int i = 0; i < 12; ++i)
			{
				if (bitCode[i] == '1')
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
	for (unsigned int i = 0; i < m_tiles.size(); i++)
		m_tiles[i]->Draw(rw);
}

void Level::Update(Changes changes)
{
	for (unsigned int i = 0; i < changes.kills.size(); i++)
	{
		KillCell(changes.kills[i]);
	}
	for (unsigned int i = 0; i < changes.moves.size(); i++)
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
		sf::Vector2i tileIndex = GetIndexFromCoordinates(targetCell);

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
	sf::Vector2i ij = GetIndexFromCoordinates(coordinates);
	
	if (ij.x < 0 || ij.x > MAP_DIAMETER - 1 || ij.y < 0 || ij.y > MAP_DIAMETER - 1 || (m_tileIDs[ij.x][ij.y] == -1))
		return true;
	return false;
}

Tile* Level::GetTile(sf::Vector3i coordinates)
{
	sf::Vector2i indices = GetIndexFromCoordinates(coordinates);
	int currID = m_tileIDs[indices.x][indices.y];
	return m_tiles[currID];
}

const Tile& Level::GetConstTile(sf::Vector3i coordinates) const
{
	sf::Vector2i indices = GetIndexFromCoordinates(coordinates);
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
	for (unsigned int i = 0; i < 6; i++)
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

const vector<CellType*>& Level::GetCellTypeContainer() const
{
	return m_cellTypes;
}

vector<vector<int>> Level::GetTileIDs() const
{
	return m_tileIDs;
}

sf::Vector2i Level::GetIndexFromCoordinates(sf::Vector3i coordinates) const
{
	return sf::Vector2i(coordinates.z + MAP_SIDE_LENGTH - 1, coordinates.x + MAP_SIDE_LENGTH - 1);
}

Level::~Level()
{
	for (unsigned int i = 0; i < m_tiles.size(); ++i)
	{
		delete m_tiles[i];
	}
	m_tiles.clear();

	for (unsigned int j = 0; j < m_cells.size(); ++j)
	{
		delete m_cells[j];
	}
	m_cells.clear();

	for (unsigned int k = 0; k < m_cellTypes.size(); ++k)
	{
		delete m_cellTypes[k];
	}
	m_cellTypes.clear();
}

sf::Vector3i Level::RoundToNearestTile(sf::Vector3f realCoords)
{
	double x = realCoords.x;
	double y = realCoords.y;
	double z = realCoords.z;

	int rx = round(x);
	int ry = round(y);
	int rz = round(z);

	double x_diff = abs(rx - x);
	double y_diff = abs(ry - y);
	double z_diff = abs(rz - z);

	if ((x_diff > y_diff) && (x_diff > z_diff))
		rx = -ry - rz;
	else if (y_diff > z_diff)
		ry = -rx - rz;
	else
		rz = -rx - ry;

	return sf::Vector3i(rx, ry, rz);
}

void Level::PreviewCellTypeSelection(int cellTypeIndex)
{
	CellType highlightedCellType = *m_cellTypes[cellTypeIndex];
	
	CellRule rule = highlightedCellType.GetRules()[0];

	if (rule.actionType == ActionType::Move)
		m_currSetupTile->SetText("Move");
	else
		m_currSetupTile->SetText("Attack");

	int array[12];

	for (int i = 0; i < 12; ++i)
	{
		array[i] = rule.code & (1 << i) ? 1 : 0;
	}

	sf::Vector3i origin = m_currSetupTile->GetCoordinates();
	for (unsigned int i = 0; i < 6; i++)
	{
		sf::Vector3i currNeighborCoordinates(origin.x + neighborOffsets[i][0], origin.y + neighborOffsets[i][1],
			origin.z + neighborOffsets[i][2]);
		if (!IsOutOfBounds(currNeighborCoordinates))
		{
			Tile* currNeighbor = GetTile(currNeighborCoordinates);
			int neighborCode = array[11 - 2 * i] + array[10 - 2 * i];
			if (neighborCode == 1)
				currNeighbor->SetBorderColor(sf::Color::Red);
			else if (neighborCode == 2)
				currNeighbor->SetBorderColor(sf::Color::Green);
		}
	}
	sf::Vector3i directionNeighborCoordinates(origin.x + neighborOffsets[rule.direction][0], origin.y + neighborOffsets[rule.direction][1],
		origin.z + neighborOffsets[rule.direction][2]);
	if (!IsOutOfBounds(directionNeighborCoordinates))
		GetTile(directionNeighborCoordinates)->SetText("Target");
}

void Level::ClearPreview()
{
	if (m_currSetupTile == 0)
		return;

	m_currSetupTile->SetText("");
	sf::Vector3i origin = m_currSetupTile->GetCoordinates();
	for (unsigned int i = 0; i < 6; i++)
	{
		sf::Vector3i currNeighborCoordinates(origin.x + neighborOffsets[i][0], origin.y + neighborOffsets[i][1],
			origin.z + neighborOffsets[i][2]);
		if (!IsOutOfBounds(currNeighborCoordinates))
		{
			Tile* currNeighbor = GetTile(currNeighborCoordinates);
			currNeighbor->SetBorderColor(sf::Color(200, 200, 200));
			currNeighbor->SetText("");
		}
	}
}

void Level::AddCell(int cellTypeIndex, int team)
{
	CreateCell(*m_cellTypes[cellTypeIndex], m_currSetupTile->GetCoordinates(), team);
}