#ifndef ENGINE
#define ENGINE

#include "define_structs.h"
#include "Cell.h"
#include "Tile.h"
#include "Level.h"
#include "CellType.h"

class Engine
{
public:
	const Changes PerformMove(const Cell& thisCell, const vector<int> neighbors);

	//vector<int> GetNeighborsByTeam(sf::Vector3i origin, const Level& level);

	static Engine& GetInstance()
	{
		static Engine instance;

		return instance;
	}
private:
	int GenerateBinaryFormOfNeighbors(vector<int> neighbors, int team);

	Engine() {};

	Engine(Engine&);
	void operator=(const Engine&);
};
#endif 