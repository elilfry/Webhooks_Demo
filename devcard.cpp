#include "devcard.hpp"

namespace ariel {

    // Constructor for Devcard
    Devcard::Devcard(const string &type) : type(type) {}
    Devcard::~Devcard() {}

    // Constructor for Knight card
    Knight::Knight() : Devcard("Knight") {}
    void Knight::playCard(Player &player, Catan &catan) {
        player.addKnights(1);
        player.bigArmyCard();
        cout << "Knight added to Player " << player.getName() << ". now has " << player.getKnightsNum() << " knights." << endl;
    }

    // Constructor for Victory Point card
    VictoryPoint::VictoryPoint() : Devcard("Victory Point") {}

    void VictoryPoint::playCard(Player &player, Catan &catan) 
    {
        player.addPoints(1);
        player.subVictoryPointCard(1);
        cout << "Victory Point added to Player " << player.getName() << " now has " << player.getPoints() << " victory points." << endl;
    }


    // Constructor for Monopoly card
    Monopoly::Monopoly() : Devcard("Monopoly") {}
    

    void Monopoly::playCard(Player &player, Catan &catan) {
        int resource;
        cout << "Choose a resource to monopolize,type in numbers 1: Wood. 2: brick 3: Sheep 4: Wheat 5: Iron): ";
        cin >> resource;

        while(resource < 1 || resource > 5)
        {
            cout << "Invalid resource type. Please choose a number between 1 and 5:(or 0 to exit ) ";
            cin >> resource;
            if(resource == 0)
            {
                return;
            }
        }
        int total = 0;
        for (Player *other : catan.getPlayers()) { // Loop through all players
            if (other != &player) {// If the player is not the current player
                int amount = other->getResource(resource-1); // Get the amount of the resource
                total += amount;
                other->removeResource(resource-1, amount);// Remove the resource from the other player
            }
        }
        player.addResource(resource-1, total);// Add the total amount of the resource to the current player
        player.subMonopolyCard(1); // Remove the card from the player
        cout << "Monopoly played. Player " << player.getName() << " monopolized all " << resource << "." << std::endl;
    }


    // Constructor for Year of Plenty card
    YearOfPlenty::YearOfPlenty() : Devcard("Year of Plenty") {}

    void YearOfPlenty::playCard(Player &player, Catan &catan)
     {
        int resource;
 
        cout << "Choose a resource to receive,type in numbers 1: Wood. 2: brick 3: Sheep 4: Wheat 5: Iron): ";
        cin >> resource;

        while(resource < 1 || resource > 5)
        {
            cout << "Invalid resource type. Please choose a number between 1 and 5:(or 0 to exit ) ";
            cin >> resource;
            if(resource == 0)
            {
                return;
            }
        }
        player.addResource((resource-1), 2);
        player.subYearOfPlentyCard(1); // Remove the card from the player
        cout << "Year of Plenty played. Player " << player.getName() << " received 2 (number) " << resource  << "." << std::endl;
    }

    // Constructor for Road Building card
    RoadBuilding::RoadBuilding() : Devcard("Road Building") {}
    

    void RoadBuilding::playCard(Player &player, Catan &catan) 
    {
        cout << "Road Building card played. Player " << player.getName() << " you get the resources to build 2 new roads" << endl;
        player.addResource(WOOD, 2);
        player.addResource(BRICK, 2);
            
            catan.placeRoad(player, catan.getBoard());
            catan.placeRoad(player, catan.getBoard());
        
        player.subRoadBuildingCard(1); // Remove the card from the player

        
    }
}
