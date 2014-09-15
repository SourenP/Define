#ifndef ENGINE
#define ENGINE

#include "define_structs.h"
#include "Cell.h"
#include "Tile.h"
#include "Level.h"
#include "CellType.h"

static int neighborOffsets[6][3] = { { +1, -1, 0 }, { +1, 0, -1 }, { 0, +1, -1 }, { -1, +1, 0 }, { -1, 0, +1 }, { 0, -1, +1 } };
class Engine
{
public:
	const Changes PerformMove(const Cell& thisCell, const Level& level);

	vector<int> GetNeighborsByTeam(sf::Vector3i origin, const Level& level);

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