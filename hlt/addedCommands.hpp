using namespace std;
using namespace hlt;

struct AddedCommand
{
	void moveToTreasure(vector<Command> command_queue, shared_ptr<Ship> scout);
	void moveToOutpost();
	void moveToEnnemi();
}
AddedCommands;

