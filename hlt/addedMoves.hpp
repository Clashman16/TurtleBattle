using namespace std;
using namespace hlt;

struct AddedMoves
{
	Position treasurePosition;

	Command goToPosition(shared_ptr<Ship> ship, Position pos, unique_ptr<GameMap>& map)
	{
		Command outputCommand;

		Direction dir;
		log::log("shipX = " + to_string(ship->position.x) + "\t shipY = " + to_string(ship->position.y));

		if(ship->position.x != pos.x)
		{
			if(ship->position.x >= 0 && ship->position.x <= map->width/4 && pos.x >= 3/4*map->width && pos.x <= map->width)
			{
				dir = Direction::WEST;
			}

			if(pos.x - ship->position.x >  0 || (pos.x >= 0 && pos.x <= map->width/4 && ship->position.x >= 3/4 * map->width && ship->position.x <= map->width))
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
			if (ship->position.y >= 0 && ship->position.y <= map->height/4 && pos.y >= 3/4 * map->height && pos.y <= map->height)
			{
				dir = Direction::NORTH;
			}

			if (pos.y - ship->position.y > 0 || (pos.y >= 0 && pos.y <= map->height/4 && ship->position.y >= 3/4 * map->height && ship->position.y <= map->height))
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
					int dist1 = 0;
					int dist2 = 0;

					if (haliteAtPos >= maxHalite)
					{
						maxHalite = haliteAtPos;

						if (dist1 != 0)
						{
							dist2 = sqrt((x - scout->position.x) ^ 2 + (y - scout->position.y) ^ 2);
							if (dist2 > dist1)
							{
								posX = x;
								posY = y;
							}
						}

						posX = x;
						posY = y;
						dist1 = sqrt((x-scout->position.x)^2+(y - scout->position.y)^2);
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
