using namespace std;
using namespace hlt;

struct AddedMoves
{
	Position treasurePosition;

	Command goToPosition(shared_ptr<Ship> ship, Position pos, unique_ptr<GameMap>& map)
	{

		return ship->move(map->naive_navigate(ship, pos));
		Command outputCommand;

		Direction dir;

		log::log("GoToPos");

		log::log("shipX = " + to_string(ship->position.x) + "\t shipY = " + to_string(ship->position.y));

		if(ship->position.x != pos.x)
		{
			log::log("GoToPos1");
			if (pos.x - ship->position.x >  0)
			{
				dir = Direction::EAST;
			}
			else
			{
				dir = Direction::WEST;
			}
		}
		else if(ship->position.y != pos.y)
		{
			log::log("GoToPos2");
			if (pos.y - ship->position.y > 0)
			{
				dir = Direction::SOUTH;
			}
			else
			{
				dir = Direction::NORTH;
			}
		}
		else
		{
			dir = Direction::STILL;
		}

		return ship->move(dir);
	}

	Command moveToTreasure(shared_ptr<Ship> scout, unique_ptr<GameMap>& map)
	{
		Command outputCommand;

		log::log("moveToTreasure");

		log::log("treasureX = " + to_string(treasurePosition.x) + "\ttreasureY = " + to_string(treasurePosition.y));

		if (treasurePosition.x == NULL)
		{
			Halite maxHalite = 0;
			int posX = 0, posY = 0;

			//Get the cell which contains the most halite
			for (int x = 0; x < map->width; x++)
			{
				for (int y = 0; y < map->height; y++)
				{
					Halite haliteAtPos = map->at(Position(x, y))->halite;

					if (haliteAtPos > maxHalite)
					{
						maxHalite = haliteAtPos;
						posX = x;
						posY = y;
					}
				}
			}
			treasurePosition = Position(posX, posY);
		}

		//Make the scout got to this cell
		outputCommand = goToPosition(scout, treasurePosition, map);

		return outputCommand;
	}

	void moveToOutpost()
	{
	}

	void moveToEnnemi()
	{
	}

	void followScout(vector<Command> command_queue, shared_ptr<Ship> Picker, Position treasurePosition) 
	{
		if (Picker.get()->position != treasurePosition) {
			if (Picker.get()->position.x > treasurePosition.x)
			{
				command_queue.push_back(Picker->move(Direction::WEST));
			}
			else if (Picker.get()->position.x < treasurePosition.x)
			{
				command_queue.push_back(Picker->move(Direction::EAST));
			}

			else if (Picker.get()->position.y > treasurePosition.y)
			{
				command_queue.push_back(Picker->move(Direction::SOUTH));
			}
			else if (Picker.get()->position.y < treasurePosition.y)
			{
				command_queue.push_back(Picker->move(Direction::EAST));
			}
		}
	}
};
