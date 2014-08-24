#include "Level.h"

Level::Level(int windowSize)
{
	// Fill m_tileIDs with -1 
	for (int i = 0; i < MAP_DIAMETER; i++)
		for (int j = 0; j < MAP_DIAMETER; j++)
			m_tileIDs[i][j] = -1;

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

	//testing
	InitializeCells();

	// Initialize Tiles based on Cells
	for (size_t i = 0; i < m_cells.size(); i++)
	{
		sf::Vector3i currentLoc = m_cells[i]->GetLocation();
		Tile* currentTile = GetTile(currentLoc);
		currentTile->SetCell(*m_cells[i], i);
	}
}

void Level::Draw(sf::RenderWindow& rw)
{
	for (int i = 0; i < m_tiles.size(); i++)
		m_tiles[i]->Draw(rw);
}

// returnes by reference (might cause memory issues)
sf::Vector2i Level::indexFromCoordinates(sf::Vector3i coordinates)
{	
	return sf::Vector2i(coordinates.z + MAP_SIDE_LENGTH - 1, coordinates.x + MAP_SIDE_LENGTH - 1);
}

Tile* Level::GetTile(sf::Vector3i coordinates)
{
	sf::Vector2i indices = indexFromCoordinates(coordinates);
	int currID = m_tileIDs[indices.x][indices.y];
	return m_tiles[currID];
}

const vector<Cell*> Level::GetCellContainer() const
{
	return m_cells;
}

const vector<Tile*> Level::GetTileContainer() const
{
	return m_tiles;
}

void Level::InitializeCells()
{
	CellType *red = new CellType();
	CellType *green = new CellType();
	CellType *blue = new CellType();

	Cell *test1 = new Cell(red, sf::Vector3i(0, 0, 0));
	Cell *test2 = new Cell(green, sf::Vector3i(-1, 0, 1));
	Cell *test3 = new Cell(blue, sf::Vector3i(-2, 0, 2));

	m_cells.push_back(test1);
	m_cells.push_back(test2);
	m_cells.push_back(test3);

	HeapNode node;

	node.cellIndex = 0;
	node.priority = m_cells[0]->GetPriority();
	m_priorityHeap.push(node);

	node.cellIndex = 1;
	node.priority = m_cells[1]->GetPriority();
	m_priorityHeap.push(node);

	node.cellIndex = 2;
	node.priority = m_cells[2]->GetPriority();
	m_priorityHeap.push(node);
}


bool Level::MoveCell(sf::Vector3i origin, sf::Vector3i destination)
{
	Tile* originTile = GetTile(origin);
	Tile* destinationTile = GetTile(destination);

	if (destinationTile->GetCellIndex() != -1)
		return 0;
	else
	{
		int originCellIndex = originTile->GetCellIndex();

		originTile->SetEmpty();
		destinationTile->SetCell(*m_cells[originCellIndex], originCellIndex);

		m_cells[originCellIndex]->setLocation(destination);
		
		return 1;
	}
}

const Cell* Level::GetNextCell()
{
	HeapNode nextNode = m_priorityHeap.top();

	//Continuing popping from heap until live cell is found
	while (!m_priorityHeap.empty() && !m_cells[nextNode.cellIndex]->IsAlive())
	{
		m_priorityHeap.pop();
		nextNode = m_priorityHeap.top();
	}
	cout << "index=" << nextNode.cellIndex << " priority=" << nextNode.priority << endl;
 	m_priorityHeap.pop(); // pop the alive cell
	nextNode.priority -= 1; // reduce priority based on action
	m_priorityHeap.push(nextNode); // push the alive cell back

	return (m_cells[nextNode.cellIndex]);
}

void Level::Update(Changes changes)
{
	for (int i = 0; i < changes.moves.size(); i++)
	{
		sf::Vector3i origin = changes.moves[i][0];
		sf::Vector3i target = changes.moves[i][1];

		Tile* originTile = GetTile(origin);
		Tile* targetTile = GetTile(target);

		m_cells[originTile->GetCellIndex()]->setLocation(target);

		targetTile->SetCell(*m_cells[originTile->GetCellIndex()], originTile->GetCellIndex());
		originTile->SetEmpty();
	}
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
}