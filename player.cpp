#include "player.hpp"
#include "board.hpp"


namespace ariel
{

    int Player::playerCount = 0;
    
     Player::Player(string name)
    {
        this->name = name;
        this->points = 0;
        for(int i = 0; i < 5; i++)
        {
            resources[i] = 0;
        }
        this->playerNumber = ++playerCount;
    }

    Player::~Player()
    {
    }

    string Player::getName()
    {
        return this->name;
    }

    int Player::getPoints()
    {
        return this->points;
    }

    void Player::addPoints(int amount)
    {
        this->points += amount;
    }

    int Player::getRoadsNum()
    {
        return this->roadsNum;
    }

    void Player::addRoadsNum(int amount)
    {
        this->roadsNum += amount;
    }

    int Player::getDevCardsSum()
    {
        devCardsSum = knights + victoryPointCard + monopolyCard + yearOfPlentyCard + roadBuildingCard;
        return devCardsSum;
        
    }

    void Player::addKnights(int amount)
    {
        this->knights += amount;
    }

    void Player::subKnights(int amount)
    {
        this->knights -= amount;
    }

    int Player::getMonopolyCard()
    {
        return this->monopolyCard;
    }
    void Player::subMonopolyCard(int amount)
    {
        this->monopolyCard -= amount;
    }

    int Player::getYearOfPlentyCard()
    {
        return this->yearOfPlentyCard;
    }
    void Player::subYearOfPlentyCard(int amount)
    {
        this->yearOfPlentyCard -= amount;
    }

    int Player::getRoadBuildingCard()
    {
        return this->roadBuildingCard;
    }
    void Player::subRoadBuildingCard(int amount)
    {
        this->roadBuildingCard -= amount;
    }

    int Player::getKnightsNum()
    {
        return this->knights;
    }

    int Player::getVictoryPointCard()
    {
        return this->victoryPointCard;
    }

    void Player::subVictoryPointCard(int amount)
    {
        this->victoryPointCard -= amount;
    }

    void Player::bigArmyCard()
    {
        if(knights > 3)
        {
            points += 2;
        }
    }

    void Player::printResources()
    {
        cout << "Player " << name << " resources:" << endl;
        cout << "Wood: " << resources[WOOD] << endl;
        cout << "Brick: " << resources[BRICK] << endl;
        cout << "Sheep: " << resources[SHEEP] << endl;
        cout << "Wheat: " << resources[WHEAT] << endl;
        cout << "Iron: " << resources[IRON] << endl;
    }

    void Player::addResource(int resourceType, int amount)
    {
        if(resourceType < 0 || resourceType > 4)
        {
            cout << "Invalid resource type in add resource." << endl;
            return;
        }
        else
        {
            resources[resourceType] += amount;
           // cout << "Player " << name << " received " << amount << " " << resourceType << " resources." << endl;

        }
    }

    void Player::removeResource(int resourceType, int amount)
    {
        if(resourceType < 0 || resourceType > 4)
        {
            cout << "Invalid resource type in remove function." << endl;
            return;
        }
        else if(resources[resourceType] < amount)
        {
            cout << "Not enough resources." << endl;
            return;
        }
        else
        {
            resources[resourceType] -= amount;
        }
    } 

    int Player::getResource(int resourceType)
    {
        if(resourceType < 0 || resourceType > 4)
        {
            cout << "Invalid resource type in remove function." << endl;
            return -1;
        }
        else
        {
            return resources[resourceType];
        }
    }

           // int getTotalResources();
    int Player::getTotalResources()
    {
        int totalResources = 0;
        for(int i = 0; i < 5; i++)
        {
            totalResources += resources[i];
        }
        return totalResources;
    }

    void Player::addDevCard(string devCardType)
    {

        if(devCardType == "Knight")
        {
            knights++;
        }
        else if(devCardType == "Victory Point")
        {
            victoryPointCard++;
        }
        else if(devCardType == "Monopoly")
        {
            monopolyCard++;
        }
        else if(devCardType == "Year of Plenty")
        {
            yearOfPlentyCard++;
        }
        else if(devCardType == "Road Building")
        {
            roadBuildingCard++;
        }
        else
        {
            cout << "Invalid development card type." << endl;
            return;
        }
       devCardsSum++;

    }

    string Player::getColor()
    {
        switch(playerNumber)
        {
            case 1:
                return "\033[1;33m"; //yellow
                break;

            case 2:
                return "\033[1;34m"; //blue
                break;
                
            case 3:
                return "\033[1;31m"; //red
                break;
        
            default:
                return "\033[0m"; //default color
                break;
        }

    }
        /*
        check ifthe recources are the same 
        check if the player has enough resources to trade
        deduct the resources from the player
        */
    void Player::tradeResources(Player &otherPlayer, int giveResource, int giveAmount, int takeResource, int takeAmount)
    {
        cout << "other player resources" << otherPlayer.getResource(takeResource-1) << endl;
        if(giveResource < 0 || giveResource > 4 || otherPlayer.getResource(takeResource-1)  < 0 || otherPlayer.getResource(takeResource-1) > 4 || giveResource == takeResource)
        {
            cout << "Invalid resource type." << endl;
            return;
        }
        else if(resources[giveResource-1] < giveAmount || otherPlayer.getResource(takeResource-1) < takeAmount)
        {
            cout << "Not enough resources to trade." << endl;
            return;
        }
        else
        {
            resources[giveResource-1] -= giveAmount;
            otherPlayer.addResource(giveResource-1, giveAmount);
            resources[takeResource-1] += takeAmount;
            otherPlayer.removeResource(takeResource-1, takeAmount);
            cout << "Player " << name << " traded " << giveAmount << " " << giveResource << " resources for " << takeAmount << " " << takeResource << " resources with player " << otherPlayer.getName() << "." << endl;
        }
    
    }
    /*
    check ifthe player have knight cards
    check if the player has enough resources to trade
    deduct the resources from the player
    */
    void Player::tradeDevelopmentCards(Player &otherPlayer,int knightAmount,int woodAmount,int brickAmount, int sheepAmount, int wheatAmount,int ironAmount)
    {
        if(getKnightsNum() < knightAmount)
        {
            cout << "Not enough knight cards to trade." << endl;
            return;
        }

        if(otherPlayer.getResource(WOOD) < woodAmount || otherPlayer.getResource(BRICK) < brickAmount || otherPlayer.getResource(SHEEP) < sheepAmount || otherPlayer.getResource(WHEAT) < wheatAmount || otherPlayer.getResource(IRON) < ironAmount)
        {
            cout << "Not enough resources to trade." << endl;
            return;
        }
        else
        {
            subKnights(knightAmount);
            otherPlayer.addResource(WOOD, woodAmount);
            otherPlayer.addResource(BRICK, brickAmount);
            otherPlayer.addResource(SHEEP, sheepAmount);
            otherPlayer.addResource(WHEAT, wheatAmount);
            otherPlayer.addResource(IRON, ironAmount);
            cout << "Player " << name << " traded " << knightAmount << " knight cards for " << woodAmount << " wood, " << brickAmount << " brick, " << sheepAmount << " sheep, " << wheatAmount << " wheat, and " << ironAmount << " iron resources with player " << otherPlayer.getName() << "." << endl;
        }

    }

    void Player::printDetails()
    {

        cout << "Player " << name << " details:" << endl;
        cout << "Wood: " << resources[WOOD] << endl;
        cout << "Brick: " << resources[BRICK] << endl;
        cout << "Sheep: " << resources[SHEEP] << endl;
        cout << "Wheat: " << resources[WHEAT] << endl;
        cout << "Iron: " << resources[IRON] << endl;

        cout<<"Points: "<<getPoints()<<endl;
        if(getKnightsNum() > 0 ) {cout<<"Knights: "<<getKnightsNum()<<endl;}
        if(getKnightsNum() > 3 ) {cout<<"Big Army Card: Yes"<<endl;}

        if(getVictoryPointCard() > 0 ) {cout<<"Victory Point Cards: "<<getVictoryPointCard()<<endl;}
        if(getMonopolyCard() > 0 ) {cout<<"Monopoly Cards: "<<getMonopolyCard()<<endl;}
        if(getYearOfPlentyCard() > 0 ) {cout<<"Year Of Plenty Cards: "<<getYearOfPlentyCard()<<endl;}
        if(getRoadBuildingCard() > 0 ) {cout<<"Road Building Cards: "<<getRoadBuildingCard()<<endl;}



        
    }

    /*
    ask the player to discard half of his resources
    */
    void Player::sumIs7()
    {
        int total = getTotalResources();
        int half = total / 2;

        cout << "Displaying player " << name << " resources:" << endl;
        printResources();

        cout << "Player " << name << " has " << total << " resources." << endl;
        cout << "Player " << name << " must discard " << half << " of his resources." << endl;

        int discarded = 0;
        
        while(true)
        {

            int wood_discarded = 0;
            int brick_discarded = 0;
            int sheep_discarded = 0;
            int wheat_discarded = 0;
            int iron_discarded = 0;

            if(getResource(WOOD) > 0)
            {
                while(true)
                {
                    cout << "How many wood resources would you like to discard?" << endl;
                    cin >> wood_discarded;
                    if(wood_discarded < 0 || wood_discarded > getResource(WOOD))
                    {
                        cout << "Invalid amount." << endl;
                        continue; // ask the player again
                    }
                    else
                    {
                        break; // exit the first while loop
                    }
                
                }
            }

            if(getResource(BRICK) > 0)
            {
                while(true)
                {
                    cout << "How many brick resources would you like to discard?" << endl;
                    cin >> brick_discarded;
                    if(brick_discarded < 0 || brick_discarded > getResource(BRICK))
                    {
                        cout << "Invalid amount." << endl;
                        continue; // ask the player again
                    }
                    else
                    {
                        break; // exit the first while loop
                    }
                
                }
            }

            if(getResource(SHEEP) > 0)
            {
                while(true)
                {
                    cout << "How many sheep resources would you like to discard?" << endl;
                    cin >> sheep_discarded;
                    if(sheep_discarded < 0 || sheep_discarded > getResource(SHEEP))
                    {
                        cout << "Invalid amount." << endl;
                        continue; // ask the player again
                    }
                    else
                    {
                        break; // exit the first while loop
                    }
                
                }
            }

            if(getResource(WHEAT) > 0)
            {
                while(true)
                {
                    cout << "How many wheat resources would you like to discard?" << endl;
                    cin >> wheat_discarded;
                    if(wheat_discarded < 0 || wheat_discarded > getResource(WHEAT))
                    {
                        cout << "Invalid amount." << endl;
                        continue; // ask the player again
                    }
                    else
                    {
                        break; // exit the first while loop
                    }
                
                }
            }

            if(getResource(IRON) > 0)
            {
                while(true)
                {
                    cout << "How many iron resources would you like to discard?" << endl;
                    cin >> iron_discarded;
                    if(iron_discarded < 0 || iron_discarded > getResource(IRON))
                    {
                        cout << "Invalid amount." << endl;
                        continue; // ask the player again
                    }
                    else
                    {
                        break; // exit the first while loop
                    }
                
                }
            }

            int total_discarded = wood_discarded + brick_discarded + sheep_discarded + wheat_discarded + iron_discarded;
            if(total_discarded != half)
            {
                cout << "You must discard exactly " << half << " resources." << endl;
                cout << "You have discarded " << total_discarded << " resources." << endl;
                continue; // ask the player again
            }
            else
            {
                removeResource(WOOD, wood_discarded);
                removeResource(BRICK, brick_discarded);
                removeResource(SHEEP, sheep_discarded);
                removeResource(WHEAT, wheat_discarded);
                removeResource(IRON, iron_discarded);
                cout << "Player " << name << " discarded " << total_discarded << " resources." << endl;
                break; // exit the second while loop
            }


     }
    }

    

} // namespace ariel
