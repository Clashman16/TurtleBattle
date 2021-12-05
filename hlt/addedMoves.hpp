	using namespace std;
using namespace hlt;

struct AddedMoves
{
	Position treasurePosition;

	void goToPosition(vector<Command> command_queue, shared_ptr<Ship> ship, Position pos)
	{
		if (ship.get()->position != pos)
		{
			if (ship.get()->position.x > pos.x)
			{
				command_queue.push_back(ship->move(Direction::WEST));
			}
			else if (ship.get()->position.x < pos.x)
			{
				command_queue.push_back(ship->move(Direction::EAST));
			}

			else if (ship.get()->position.y > pos.y)
			{
				command_queue.push_back(ship->move(Direction::SOUTH));
			}
			else if (ship.get()->position.y < pos.y)
			{
				command_queue.push_back(ship->move(Direction::EAST));
			}
		}
	}

	void moveToTreasure(vector<Command> command_queue, shared_ptr<Ship> scout, GameMap map)
	{
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
		goToPosition(command_queue, scout, treasurePosition);
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
