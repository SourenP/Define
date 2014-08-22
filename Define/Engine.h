#ifndef ENGINE
#define ENGINE

#include "define_structs.h"
#include "Cell.h"
#include "Tile.h"

static const Changes getResult(const Cell& thisCell, const std::vector<Cell*>, const std::vector<Tile*>);
vector<sf::Vector3i> getNeighbors(sf::Vector3i coordinates);

#endif