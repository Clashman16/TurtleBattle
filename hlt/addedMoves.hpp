using namespace std;
using namespace hlt;

struct AddedMoves
{
	Position treasurePosition;

	Command goToPosition(shared_ptr<Ship> ship, Position pos)
	{
		Command outputCommand;

		log::log("GoToPos");
		if (ship->position.x > pos.x)
		{
			log::log("GoToPos1");
			outputCommand = ship->move(Direction::WEST);
		}
		else if (ship->position.x < pos.x)
		{
			log::log("GoToPos2");
			outputCommand = ship->move(Direction::EAST);
		}

		else if (ship->position.y > pos.y)
		{
			log::log("GoToPos3");
			outputCommand = ship->move(Direction::NORTH);
		}
		else if (ship->position.y < pos.y)
		{
			log::log("GoToPos4");
			outputCommand = ship->move(Direction::SOUTH);
		}

		return outputCommand;
	}

	Command moveToTreasure(shared_ptr<Ship> scout, GameMap map)
	{
		log::log("moveToTreasure");

		if (treasurePosition.x == NULL)
		{
			Halite maxHalite = 0;
			int posX, posY = 0;

			//Get the cell which contains the most halite
			for (int x = 0; x <= map.width; x++)
			{
				for (int y = 0; y <= map.height; y++)
				{
					Halite haliteAtPos = map.at(Position(x, y))->halite;

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
		return goToPosition(scout, treasurePosition);
	}

	void moveToOutpost()
	{
	}

	void moveToEnnemi()
	{
	}
};
