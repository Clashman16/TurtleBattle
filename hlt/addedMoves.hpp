using namespace std;
using namespace hlt;

struct AddedMove
{
	void moveToTreasure(vector<Command> command_queue, shared_ptr<Ship> scout);
	void moveToOutpost();
	void moveToEnnemi();
}
AddedMoves;

