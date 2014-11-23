#include "HexagonGenerator.h"

const double HexagonGenerator::DEFAULT_RADIUS = 25;

void HexagonGenerator::GenerateHexagons(int screenWidth, int screenHeight, 
					double radius, unsigned int rings)
{
	m_hexagonRadius = radius;
	m_rings = rings;
	m_center = { screenWidth / 2 - radius, screenHeight / 2 - radius };
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
	Hexagon* primarySeed = new Hexagon(m_center, m_hexagonRadius);
	seedQueue.push(HexNode(m_center, pair<int, int>(mapSize / 2, mapSize / 2), rings));
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

	double realIndexI = (((-1 * (mouseX - m_center.x)) / 3) + ((sqrt(3) * (mouseY - m_center.y)) / 3)) / m_hexagonRadius;
	double realIndexJ = (2 * (mouseX - m_center.x) / (3 * m_hexagonRadius));
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

void HexagonGenerator::SaveToXML()
{
	tinyxml2::XMLDocument xmlDoc;

	tinyxml2::XMLNode * pRoot = xmlDoc.NewElement("CellTypeDoc");
	xmlDoc.InsertFirstChild(pRoot);

	tinyxml2::XMLElement * pCellTypes = xmlDoc.NewElement("CellTypes");
	for (unsigned int i = 0; i < m_cellTypes.size(); ++i)
	{
		tinyxml2::XMLElement* pCellType = xmlDoc.NewElement("CellType");
		sf::Color color = m_cellTypes[i]->GetColor();
		pCellType->SetAttribute("R", color.r);
		pCellType->SetAttribute("G", color.g);
		pCellType->SetAttribute("B", color.b);
		vector<CellRule> cellRules = m_cellTypes[i]->GetRules();
		for (unsigned int j = 0; j < cellRules.size(); ++j)
		{
			tinyxml2::XMLElement* pRule = xmlDoc.NewElement("Rule");
			string bitCode = "";
			long decimalCode = cellRules[j].code, multiplier = 1, remainder;
			do
			{
				if ((decimalCode & 1) == 0)
					bitCode += "0";
				else
					bitCode += "1";

				decimalCode >>= 1;
			} while (decimalCode);

			int missingBits = ((m_hexagons.size() - 1) * 2) - bitCode.size();
			if (missingBits > 0)
			{
				bitCode.append(missingBits, '0');
			}

			char *cstr = &bitCode[0];

			pRule->SetAttribute("Code", cstr);
			pRule->SetAttribute("Action", cellRules[j].actionType);
			pRule->SetAttribute("Direction", cellRules[j].direction);
			pRule->SetText("");

			pCellType->InsertEndChild(pRule);
		}

		pCellTypes->InsertEndChild(pCellType);
	}

	pRoot->InsertEndChild(pCellTypes);
	tinyxml2::XMLError eResult = xmlDoc.SaveFile("../Define/files/SavedData.xml");
	
}

string HexagonGenerator::SaveCellType(sf::Color color)
{	
	if (m_storedRules.empty())
		return "no rules";
	
	CellType* newCellType = new CellType(0, m_storedRules, color);
	m_cellTypes.push_back(newCellType);

	m_storedRules.clear();

	return "Success";
}

void HexagonGenerator::SaveRule(int direction, ActionType actionType)
{
	CellRule newRule;

	int code = 0;
	int index = 0;
	int ringsRead = 0;

	newRule.actionType = actionType;
	newRule.direction = direction;

	/*
	The recursive generation causes a slight issues with the indexing of cells when we have more than 1 ring.
	Instead of                 We get
	0  0  14 15 16             0  0  15 16 17
	0  13  5  6 17             0  14  5  6 18
	12  4  1  7 18             13  4  1  7 19
	11  3  2 19  0             12  3  2 10  0
	10  9  8  0  0             11  9  8  0  0

	This is why when saving the rule we skip the 3rd element of the new ring and read the 4th, appending the 3rd at the end of the ring.
	So we read ....8 9 11.....18 19 10. This is so the code of the rule has a logical way of being read.
	*/

	vector<Hexagon*>::iterator it = m_hexagons.begin() + 1;

	for (unsigned int i = 1; i <= m_rings; ++i)
	{
		unsigned int ringElements = 3 * pow(2, i);
		unsigned int j = 0;
		Hexagon* backup;
		if (i > 1)
		{
			while (j < 2)
			{
				if ((*it)->GetState() == Hexagon::HexagonState::Enemy)
				{
					code += pow(2, index);
				}
				else if ((*it)->GetState() == Hexagon::HexagonState::Ally)
				{
					code += pow(2, index + 1);
				}

				index += 2;
				it++;
				j++;
			}

			backup = (*it);
			it++;
			j++;

			if ((*it)->GetState() == Hexagon::HexagonState::Enemy)
			{
				code += pow(2, index);
			}
			else if ((*it)->GetState() == Hexagon::HexagonState::Ally)
			{
				code += pow(2, index + 1);
			}

			index += 2;
			it++;
			j++;

		}
		while(j < ringElements)
		{
			if ((*it)->GetState() == Hexagon::HexagonState::Enemy)
			{
				code += pow(2, index);
			}
			else if ((*it)->GetState() == Hexagon::HexagonState::Ally)
			{
				code += pow(2, index + 1);
			}

			index += 2;
			it++;
			j++;
		}

		if (i > 1)
		{
			if (backup->GetState() == Hexagon::HexagonState::Enemy)
			{
				code += pow(2, index);
			}
			else if (backup->GetState() == Hexagon::HexagonState::Ally)
			{
				code += pow(2, index + 1);
			}
			index += 2;
		}
	}

	newRule.code = code;
	
	m_storedRules.push_back(newRule);
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