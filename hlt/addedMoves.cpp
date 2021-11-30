#include <command.hpp>
#include <ship.hpp>
#include <vector>
#include <addedMoves.hpp>
#include <game_map.hpp>


void AddedMove::goToPosition(vector<Command> command_queue, shared_ptr<Ship> ship, Position pos)
{
	while (ship.get()->position != pos)
	{
		if (ship.get()->position.x > pos.x)
		{
			command_queue.push_back(ship->move(Direction::WEST));
		}
		else if (ship.get()->position.x < pos.x)
		{
			command_queue.push_back(ship->move(Direction::EAST));
		}

		if (ship.get()->position.y > pos.y)
		{
			command_queue.push_back(ship->move(Direction::SOUTH));
		}
		else if (ship.get()->position.y < pos.y)
		{
			command_queue.push_back(ship->move(Direction::EAST));
		}
	}
}

void AddedMove::moveToTreasure(vector<Command> command_queue, shared_ptr<Ship> scout, unique_ptr<GameMap> map)
{

	Halite maxHalite;
	int posX, posY;

	//Get the cell which contains the most halite
	for(int x = 0; x <= map.get()->width; x++)
	{
		for (int y = 0; y <= map.get()->height; y++)
		{
			Halite haliteAtPos = map.get()->at(Position(x, y))->halite;

			if (haliteAtPos > maxHalite)
			{
				maxHalite = haliteAtPos;
				posX = x;
				posY = y;
			}
		}
	}

	//Make the scout got to this cell
	goToPosition(command_queue, scout, Position(posX, posY));
	//Get the scout's position
	treasurePosition = scout.get()->position;
}

void AddedMove::moveToOutpost()
{
}

void AddedMove::moveToEnnemi()
{
}
