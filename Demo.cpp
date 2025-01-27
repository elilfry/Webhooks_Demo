/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "catan.hpp"
#include "player.hpp"
#include "board.hpp"
#include "devcard.hpp"
using namespace std;
using namespace ariel;

//create a new game with print to the user each step and printing the map of the game in the terminal

int main()
{
    string name1="Eli", name2="Meni", name3="Chen";
    cout << "Welcome to Catan game right on your terminal!\n" << endl;
    // cout << "Please enter the names of the first player:" << endl;
    // cin >> name1;
    // cout << "Please enter the names of the second player:" << endl;
    // cin >> name2;
    // cout << "Please enter the names of the third player:" << endl;
    // cin >> name3;

    Player p1(name1);
    cout << "Player " << name1 << " created." << endl;
    Player p2(name2);
    cout << "Player " << name2 << " created." << endl;
    Player p3(name3);
    cout << "Player " << name3 << " created." << endl;

    Catan catan(p1, p2, p3); //create a new game with the 3 players
   Board &board = catan.getBoard();
    //print the board
    board.printBoard();


    catan.ChooseStartingPlayer(); 

        cout << "-----Starting of the game. Every player places two settlements and two roads.-----" << endl;
        

        for(int i = 0; i < 3; i++)
        {
            
            cout << "\n Player " << catan.getCurrentPlayer().getName() << " turn. 1st Settelment" << endl;
            
           catan.placeSettlement(catan.getCurrentPlayer(), board);

            catan.placeRoad(catan.getCurrentPlayer(), board);
            catan.nextPlayer();
        }
        
        //place the second settlement and road now frome the last player to the first player

        catan.previousPlayer();
        for(int i = 0; i < 3; i++)
        {
            cout << "\n Player " << catan.getCurrentPlayer().getName() << " turn.2nd Settelment" << endl;
           catan.placeSettlement(catan.getCurrentPlayer(), board);

            catan.placeRoad(catan.getCurrentPlayer(), board);
            catan.previousPlayer();
        }
            cout << "\n";
            board.printBoard();
            catan.intialResources(board);


        cout << "--------------Starting the normal rounds--------------------." << endl;

        
        while(!catan.isGameFinished())
        {
            Player &player = catan.getCurrentPlayer();

            cout << "Player " << catan.getCurrentPlayer().getName() << " turn." << endl;
            
            catan.rollDice(board);
            catan.getCurrentPlayer().printResources();

            bool endTurn = false;
            while(!endTurn)
            {
            cout << "Please enter the action you want to do:" << endl;
            cout << "1. Build a settlement" << endl;
            cout << "2. Build a road" << endl;

            
            cout << "3. Upgrade a settlement to a city" << endl;
            cout << "4. Buy a development card" << endl;
            cout << "5. Play a development card" << endl;
            cout << "6. Make a trade" << endl;
            cout << "7. Print details" << endl;
            cout << "8. End turn" << endl;
            cout << "0. Exit" << endl;


            int action = -1;
            cin >> action;

            switch(action)
            {
                case 1: //build a settlement
                    catan.placeSettlement(player, board);
                    break;
                
                case 2: //build a road
                    catan.placeRoad(player, board);

                    break;

                case 3: //upgrade a settlement to a city
                    catan.upgradeSettlementToCity(player,board);

                    break;
                
                case 4: //buy a development card
                    catan.buyDevelopmentCard(player);
                    break;

                case 5: //play a development card
                    catan.playDevelopmentCard(player);
                    endTurn = true;
                    catan.nextPlayer();
                    break;

                case 6: //make a trade
                    catan.trade(player);
                    break;
                case 7: //print details
                    player.printDetails();
                    break;
                case 8: //end turn
                    endTurn = true;
                    catan.nextPlayer();
                    break;
                case 0: //exit
                    cout << "Exiting the game." << endl;
                    return 0;
                    break;
                default:
                    cout << "Invalid action." << endl;
                    break;
                
            }
         }
            board.printBoard();
        }    





}
    