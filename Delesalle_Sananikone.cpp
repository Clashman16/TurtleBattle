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
    //unordered_map<shared_ptr<Ship>, ShipType> typedShips; //Contains all kinds of ship identified by index
    unordered_map<shared_ptr<Ship>, ShipType> typedShips; //Contains all kinds of ship identified by index
    AddedMoves addedMoves; //Calls all additionnal moves
    ShipType lastSpawnedShip = Nothing;

    for (;;) {
        game.update_frame();
        shared_ptr<Player> me = game.me;
        unique_ptr<GameMap>& game_map = game.game_map;

        vector<Command> command_queue;

        int shipsCount = me->ships.size();

        if (lastSpawnedShip != Nothing)
        {
            shared_ptr<Ship> ship = prev(me->ships.end())->second;

            pair<shared_ptr<Ship>, ShipType> typedShip(ship, lastSpawnedShip);
            typedShips.insert(typedShip);
        }

        for (const auto& type_iterator : typedShips) // For all kinds of ship
        {
            if (type_iterator.second == ShipType::Scout) // If the ship is a scout
            {
                Command goToTreasure = addedMoves.moveToTreasure(type_iterator.first, *game_map.get()); //it will find the cell with the most halite
                command_queue.push_back(goToTreasure);
                log::log("shipX = " + to_string(type_iterator.first->position.x) + "\t shipY = " + to_string(type_iterator.first->position.y));
                log::log("treasureX = " + to_string(addedMoves.treasurePosition.x) + "\ttreasureY = " + to_string(addedMoves.treasurePosition.y));
            }
            else
            {
                command_queue.push_back(type_iterator.first->stay_still());//sinon, mine
            }
        }

        if (shipsCount == 0)
        {
            if (game.turn_number <= constants::MAX_TURNS && me->halite >= constants::SHIP_COST && !game_map->at(me->shipyard)->is_occupied())
            {
                command_queue.push_back(me->shipyard->spawn());
                lastSpawnedShip = Scout;
            }
        }

        if (!game.end_turn(command_queue)) {
            break;
        }
    }

    return 0;
}