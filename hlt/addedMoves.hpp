using namespace std;
using namespace hlt;

struct AddedMove
{
	Position treasurePosition;

	void goToPosition(vector<Command> command_queue, shared_ptr<Ship> ship, Position pos);
	void moveToTreasure(vector<Command> command_queue, shared_ptr<Ship> scout, unique_ptr<GameMap> map);
	void moveToOutpost();
	void moveToEnnemi();
}
	
AddedMoves;

