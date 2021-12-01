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
    std::list<ShipType> typedShips; //Contains all kinds of ship identified by index
    AddedMoves addedMoves; //Calls all additionnal moves

    for (;;) {
        game.update_frame();
        shared_ptr<Player> me = game.me;
        unique_ptr<GameMap>& game_map = game.game_map;

        vector<Command> command_queue;

        if(me->ships.size() == 0)
        {
            if (me->halite >= constants::SHIP_COST) //si on a plus de 1000H, se prépare à faire une tortue
            {
                if( game.turn_number <= 200 && !game_map->at(me->shipyard)->is_occupied()) //si c'est le tour<200 et que y'a rien au chantier
                {
                    command_queue.push_back(me->shipyard->spawn());
                    ShipType type = ShipType::Scout;
                    typedShips.push_back(type);
                }
            }
        }
        if (me->ships.size() != 0) // When player has more than 0 ship on the map
        {
            for (unordered_map<EntityId, shared_ptr<Ship>>::iterator ship_iterator = me->ships.begin(); ship_iterator != me->ships.end(); ship_iterator++) // For all ships
            {   
                for (list<ShipType>::iterator type_iterator = typedShips.begin(); type_iterator != typedShips.end(); type_iterator++) // and for all kinds of ship
                {
                    // Get which ship the loop is processing
                    int shipIndex = distance(me->ships.begin(), ship_iterator);
                    shared_ptr<Ship> ship = me->ships.at(shipIndex);

                    if (distance(typedShips.begin(), type_iterator) == shipIndex) // Get the type of the ship
                    {
                        if (*type_iterator == ShipType::Scout) // If the ship is a scout
                        {
                            addedMoves.moveToTreasure(command_queue, ship, * game_map.get()); //it will find the cell with the most halite
                        }

                        else
                        {
                            if (game_map->at(ship)->halite < constants::MAX_HALITE / 10 || ship->is_full()) //si la case a - de 100H ou la tortue a 1000H
                            {
                                /*Direction random_direction = ALL_CARDINALS[rng() % 4];//bouge dans une dir random entre Nord Sud Est Ouest
                                command_queue.push_back(ship->move(random_direction));*/

                            }
                        }
                    }
                    else
                    {
                        command_queue.push_back(ship->stay_still());//sinon, mine
                    }
                }
            }

            if (me->halite >= constants::SHIP_COST)
            {

            }
        }

        if (game.turn_number <= 200 && me->halite >= constants::SHIP_COST && !game_map->at(me->shipyard)->is_occupied())
        {
            command_queue.push_back(me->shipyard->spawn()); //spawn un chantier?
        }

        if (!game.end_turn(command_queue)) {
            break;
        }
    }

    return 0;
}