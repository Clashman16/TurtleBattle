#include "game.hpp"
#include "constants.hpp"
#include "log.hpp"
#include "shipType.cpp"
#include <random>
#include <ctime>
#include <addedMoves.hpp>

using namespace std;
using namespace hlt;

int main(int argc, char* argv[])
{
    unsigned int rng_seed;
    if (argc > 1) {
        rng_seed = static_cast<unsigned int>(stoul(argv[1]));
    }
    else {
        rng_seed = static_cast<unsigned int>(time(nullptr));
    }
    mt19937 rng(rng_seed);

    Game game;
    // At this point "game" variable is populated with initial map data.
    // This is a good place to do computationally expensive start-up pre-processing.
    // As soon as you call "ready" function below, the 2 second per turn timer will start.
    game.ready("MyCppBot");

    log::log("Successfully created bot! My Player ID is " + to_string(game.my_id) + ". Bot rng seed is " + to_string(rng_seed) + ".");

    //Initializing our updates
    list<ShipType> typedShips; //Contains all kinds of ship identified by index
    AddedMoves addedMoves; //Calls all additionnal moves

    for (;;) {
        game.update_frame();
        shared_ptr<Player> me = game.me;
        unique_ptr<GameMap>& game_map = game.game_map;

        vector<Command> command_queue;

        int shipsCount = me->ships.size();

        /*if (me->ships.size() > 0) // When player has more than 0 ship on the map
        {
            for (unordered_map<EntityId, shared_ptr<Ship>>::iterator ship_iterator = me->ships.begin(); ship_iterator != me->ships.end(); ship_iterator++) // For all ships
            {   
                int shipIndex = distance(me->ships.begin(), ship_iterator); // get the index of the ship
                shared_ptr<Ship> ship = me->ships.at(shipIndex); // get the ship

                for(list<ShipType>::iterator type_iterator = typedShips.begin(); type_iterator != typedShips.end(); type_iterator++) // and for all kinds of ship
                {
                    int typeIndex = distance(typedShips.begin(), type_iterator); // get the index of the ship's type

                    if(typeIndex == shipIndex)
                    {
                        if (*type_iterator == ShipType::Scout) // If the ship is a scout
                        {
                            addedMoves.moveToTreasure(command_queue, ship, * game_map.get()); //it will find the cell with the most halite
                        }
                    }
                    else
                    {
                        command_queue.push_back(ship->stay_still());//sinon, mine
                    }
                }
            }
        }*/
        if (shipsCount == 0)
        {
            if (game.turn_number <= 200 && me->halite >= constants::SHIP_COST && !game_map->at(me->shipyard)->is_occupied())
            {
                ShipType type = ShipType::Scout;
                typedShips.push_back(type);
                command_queue.push_back(me->shipyard->spawn());
            }
        }

        if (!game.end_turn(command_queue)) {
            break;
        }
    }

    return 0;
}