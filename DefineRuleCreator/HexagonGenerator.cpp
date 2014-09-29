#include "HexagonGenerator.h"

const double HexagonGenerator::DEFAULT_RADIUS = 25;

void HexagonGenerator::GenerateHexagons(int screenWidth, int screenHeight, 
					double radius, unsigned int rings)
{
	m_hexagonRadius = radius;
	m_rings = rings;
	POINT center = { screenWidth / 2 - radius, screenHeight / 2 - radius };
	int mapSize = 1 + 2 * rings;
	for (int i = 0; i < mapSize; ++i)
	{
		vector<int> temp;
		for (int j = 0; j < mapSize; ++j)
		{
			temp.push_back(0);
		}
		m_hexMap.push_back(temp);
	}
	m_ringDistance = 2 * (sin(toRadians(60))*radius);

	//Create primary seed
	Hexagon* primarySeed = new Hexagon(center, m_hexagonRadius);
	seedQueue.push(HexNode(center, pair<int, int>(mapSize / 2, mapSize / 2), rings));
	m_hexMap[mapSize / 2][mapSize / 2] = 1;
	m_hexagons.push_back(primarySeed);
	//While there is a hexNode that has not been visited, continue seeding
	while (!seedQueue.empty())
	{
		HexNode next = seedQueue.front();
		cout << next.coordinates.x << ", " << next.coordinates.y << ", " << next.indicies.first << ", " << next.indicies.second << endl;
		seedQueue.pop();
		SeedHexagon(next);
	}

	for (int i = 0; i < mapSize; ++i)
	{
		vector<int> temp;
		for (int j = 0; j < mapSize; ++j)
		{
			cout << m_hexMap[i][j] << ", ";
		}
		cout << endl;
	}
}

void HexagonGenerator::SeedHexagon(const HexNode& nextNode)//, queue<HexNode>& seedQueue)
{
	POINT origin = nextNode.coordinates;
	pair<int, int> indicies = nextNode.indicies;
	int depth = nextNode.depth;
	//If we reach the outermost ring, terminate. Hexagon will be created but it wont be added to the queue
	if (depth == 0)
	{
		//Hexagon* primaryHexagon = new Hexagon(origin, m_hexagonRadius);
		//m_hexagons.push_back(primaryHexagon);
		return;
	}

	depth--;

	int angle = 90; //Default angle. This is just based on hexNeighbors an can be rotated along with the matrix to start counting from somewhere else
	int offSetI, offSetJ, currNeighborI, currNeighborJ;
	for (int i = 0; i < 6; ++i)
	{
		offSetI = hexNeighbors[i][0];
		offSetJ = hexNeighbors[i][1];
		currNeighborI = indicies.first + offSetI;
		currNeighborJ = indicies.second + offSetJ;

		//Check the position in m_hexNodes to see if that hex has been visited or not
		if (m_hexMap[currNeighborI][currNeighborJ] == 0)
		{
			//Calculate center for new hexagon
			POINT newOrigin = { origin.x + m_ringDistance*cos(toRadians(angle)), origin.y + m_ringDistance*sin(toRadians(angle)) };
			//Create hexagon and mark it
			Hexagon* primaryHexagon = new Hexagon(newOrigin, m_hexagonRadius);
			m_hexagons.push_back(primaryHexagon);
			m_hexMap[currNeighborI][currNeighborJ] = m_hexagons.size();

			//If it hasn't, pinpoint the new hexagons center, create a HexNode and place it in the queue

			HexNode newNode(newOrigin, pair<int, int>(currNeighborI, currNeighborJ), depth);
			seedQueue.push(newNode);
		}
		angle += 60;
	}
}


RECT& HexagonGenerator::CycleClickedHexagon(const POINT& mouseCoordinates)
{
	RECT repaintRect;
	Hexagon* target;

	int mouseX = mouseCoordinates.x;
	int mouseY = mouseCoordinates.y;

	double realIndexI = (((-1 * (mouseX - 225))/ 3) + ((sqrt(3) * (mouseY - 225)) / 3)) / m_hexagonRadius;
	double realIndexJ = (2 * (mouseX - 225) / (3 * m_hexagonRadius));
	pair<int, int> roundedIndicies = RoundToNearestHexagon(realIndexI, realIndexJ);

	if (IsOutOfMapBounds(roundedIndicies))
	{
		repaintRect.left = 0;
		repaintRect.top = 0;
		repaintRect.bottom = 0;
		repaintRect.right = 0;
		return repaintRect;
	}

	int targetI = roundedIndicies.first, targetJ = roundedIndicies.second;
	if (m_hexMap[targetI][targetJ] - 1 < 0)
	{
		repaintRect.left = 0;
		repaintRect.top = 0;
		repaintRect.bottom = 0;
		repaintRect.right = 0;
		return repaintRect;
	}
	target = m_hexagons[m_hexMap[targetI][targetJ] - 1];
	POINT targetOrigin = target->GetOrigin();

	double minDist = CalculateAbsDistance(targetOrigin, mouseCoordinates);
	double currDist = minDist;

	cout << "Mouse Coords: " << mouseX << ", " << mouseY << endl;
	cout << "Guess: " << targetI << ", " << targetJ  << ", Guess Origin: " << targetOrigin.x << ", " << targetOrigin.y<< endl;
	cout << "Guess Distance: " << minDist << endl;

	for (int i = 0; i < 6; ++i)
	{
		targetI = (roundedIndicies.first + hexNeighbors[i][0]);
		targetJ = (roundedIndicies.second + hexNeighbors[i][1]);
		if (!IsOutOfMapBounds(pair<int, int>(targetI, targetJ)))
		{
			if (m_hexMap[targetI][targetJ] != 0)
			{
				targetOrigin = m_hexagons[m_hexMap[targetI][targetJ] - 1]->GetOrigin();
				currDist = CalculateAbsDistance(targetOrigin, mouseCoordinates);

				if (currDist < minDist)
				{
					minDist = currDist;
					target = m_hexagons[m_hexMap[targetI][targetJ] - 1];
				}
			}
		}
	}
	target->CycleState();
	
	repaintRect.top = 0;
	repaintRect.left = 0;
	repaintRect.right = 500;
	repaintRect.bottom = 500;
	
	return repaintRect;
}

bool HexagonGenerator::IsOutOfMapBounds(pair<int, int> indicies)
{
	if (indicies.first < 0 || indicies.first > m_hexMap.size() - 1)
		return true;
	if (indicies.second < 0 || indicies.second > m_hexMap.size() - 1)
		return true;
	return false;
}

pair<int, int> HexagonGenerator::RoundToNearestHexagon(double i, double j)
{
	double x = i;
	double z = j;
	double y = -1 * x - z;

	double rx = round(x);
	double ry = round(y);
	double rz = round(z);

	double x_diff = abs(rx - x);
	double y_diff = abs(ry - y);
	double z_diff = abs(rz - z);

	if ((x_diff > y_diff) && (x_diff > z_diff))
		rx = -ry - rz;
	else if (y_diff > z_diff)
		ry = -rx - rz;
	else
		rz = -rx - ry;

	return pair<int, int>(rx + m_hexMap.size()/2, rz + m_hexMap.size()/2);
}

string HexagonGenerator::GetRule()
{
	string result;
	result += "C:";
	for (int i = 0; i < m_hexagons.size(); ++i)
	{
		if (m_hexagons[i]->GetState() == Hexagon::HexagonState::Empty)
		{
			result += "00";
		}
		else if (m_hexagons[i]->GetState() == Hexagon::HexagonState::Enemy)
		{
			result += "01";
		}
		else
		{
			result += "10";
		}
	}

	result += " A:1 D:2 R:0 G:0 B:255 \n";

	return result;
}

void HexagonGenerator::CycleHexagon()
{
	for (int i = 0; i < m_hexagons.size(); i++)
	{
		m_hexagons[i]->CycleState();
	}
}


void HexagonGenerator::DrawHexagons(HDC& hdc) const
{
	for (int i = 0; i < m_hexagons.size(); ++i)
	{
		m_hexagons[i]->Draw(hdc);
		//SetPixel(hdc, m_hexagons[i]->GetOrigin().x, m_hexagons[i]->GetOrigin().y, RGB(255, 55, 5));
	}
}

HexagonGenerator::~HexagonGenerator()
{
	for (int i = 0; i < m_hexagons.size(); ++i)
	{
		delete m_hexagons[i];
	}
}