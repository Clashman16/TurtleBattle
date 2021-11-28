#include <command.hpp>
#include <ship.hpp>
#include <vector>
#include <addedCommands.hpp>


void AddedCommand::moveToTreasure(vector<Command> command_queue, shared_ptr<Ship> scout)
{

	array<Direction, 4> directionOrder = ALL_CARDINALS;

	array<Position, 4 > shipSurroundingCardinals = scout.get()->position.get_surrounding_cardinals();
	array<Position, 5> possiblePosition;

	for (array<Position, 4>::iterator position_iterator = shipSurroundingCardinals.begin(); position_iterator != shipSurroundingCardinals.end(); position_iterator++)
	{
		possiblePosition[distance(shipSurroundingCardinals.begin(), position_iterator)] = * position_iterator;
	}

	possiblePosition[5] = scout.get()->position;


	for (int i = 0; i < positionOptions.size(); i++)
	{
		for (int j = 0; j < directionOrder.size(); j++)
		{

		}
	}

	command_queue.push_back(scout->move(random_direction))
}

void AddedCommand::moveToOutpost()
{
}

void AddedCommand::moveToEnnemi()
{
}
