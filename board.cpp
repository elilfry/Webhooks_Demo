#include "board.hpp"

namespace ariel
{



    //vector <int> numbers = {2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 8 ,8 , 9 , 9 , 10 , 10 , 11 , 11 , 12}; //numbers for the tiles
    vector<int> numbers = {
        10, 2, 9,
        12, 6, 4, 10,
        9, 11, 0, 3, 8,
        8, 3, 4, 5,
        5, 6, 11
    };

    vector<int> resources = {
        IRON, SHEEP, WOOD,
        WHEAT, BRICK, SHEEP, BRICK,
        WHEAT, WOOD, DESERT, WOOD, IRON,
        WOOD, IRON, WHEAT, SHEEP,
        BRICK, WHEAT, SHEEP
    };
    // Initialize the 2D vector of tiles with the appropriate layer sizes 3 4 5 4 3 
    // and fill it with the appropriate tiles.


      


/*
Resources and Numbers Layout:
Top row: 10 (iron), 2 (Wool), 9 (Wheat)
Second row: 12 (Wheat), 6 (Brick), 4 (Wood), 10 (Wheat)
Third row: 9 (Brick), 11 (Wool), Desert, 3 (Wood), 8 (iron)
Fourth row: 8 (Wheat), 3 (Wood), 4 (Wool), 5 (Wood)
Bottom row: 5 (Brick), 6 (Wheat), 11 (iron)
*/
    

    
    Board::Board()
    {

        
         tiles = {
        vector<Tile>(3),
        vector<Tile>(4),
        vector<Tile>(5),
        vector<Tile>(4),
        vector<Tile>(3)
    };    
        // Initialize tiles with resources and numbers
        size_t resourceIndex = 0;
        size_t numberIndex = 0;
        int tileIndex = 0;
        for (size_t layer = 0; layer < tiles.size(); ++layer) {
            for (size_t i = 0; i < tiles[layer].size(); ++i) {
                 tiles[layer][i] = Tile(numbers[numberIndex], resources[resourceIndex], tileIndex);
                ++numberIndex;
                ++resourceIndex;
                ++tileIndex;
            }
        }

        
        // Initialize the board with 19 tiles.
        
        // Initialize the board with 54 vertices.
        for(int i = 0; i < 54; i++)
        {
            vertices.push_back(Vertex(i));
        }
        initializeVerticesNeighbors(); // -------------------------------------------
        // Initialize the board with 72 edges.
        for(int i = 0; i < 72; i++)
        {
            edges.push_back(Edge(i));
        }
        initializeEdgesNeighbors(); // -------------------------------------------
        // Assign vertices and edges to the tiles -------------------------------------------
        assignVerticesAndEdgesToTiles();// -------------------------------------------
        // Initialize the neighbors of the vertices and edges. -------------------------------------------

    }
    Board::~Board() {    }         // Destructor implementation

    string Tile::getResourceType(int resource)
    {
        switch (resource)
        {
        case WOOD:
            return "Wood";
        case BRICK:
            return "Brick";
        case SHEEP:
            return "Sheep";
        case WHEAT:
            return "Wheat";
        case IRON:
            return "Iron";
        case DESERT:
            return "Desert";
        default:
            return "Unknown";
        }
    }

    bool Board::placeSettlement(Player &player, int vertex)
    {
        if (vertex < 0 || vertex >= 54)
        {
            cout << "Invalid vertex, vertex is out of range, you chose: " << vertex <<endl;
            return false;
        }

    for (size_t i = 0; i < vertices.size(); i++)
    {
        Vertex &currentVertex = vertices[i];
        if (currentVertex.getNumber() == vertex)
        {
            // Check if the vertex is already occupied
            if (currentVertex.getOwner() != "none")
            {
                cout << "Vertex " << vertex << " is already owned by " << currentVertex.getOwner() << endl;
                return false;
            }

            // Check if the vertex has an adjacent settlement
            for (size_t j = 0; j < currentVertex.neighbors_vertice.size(); j++)
            {
                int neighborVertexIndex = currentVertex.neighbors_vertice[j];
                if (vertices[(size_t)neighborVertexIndex].getOwner() != "none") //
                {
                    cout << "Adjacent vertex " << neighborVertexIndex << " is already owned by " << vertices[(size_t)neighborVertexIndex].getOwner() << endl;
                    return false;
                }
            }

            // Check if the vertex has no adjacent Road (if it is not the first turn)
            if (player.getPoints() >= 2)
            {
                bool hasAdjacentRoad = false;
                for (size_t j = 0; j < currentVertex.neighbors_edges.size(); j++)
                {
                    int edgeIndex = currentVertex.neighbors_edges[j];
                    if (edges[(size_t)edgeIndex].getOwner() == player.getName())
                    {
                        hasAdjacentRoad = true;
                        break;
                    }
                }

                if (!hasAdjacentRoad)
                {
                    cout << "Vertex " << vertex << " has no adjacent Road owned by " << player.getName() << endl;
                    return false;
                }
            }

            // Place the settlement at the vertex
            vertices[i].setType("settlement");
            vertices[i].setOwner(player.getName());
            vertices[i].setColor(player.getColor());
            cout << "Settlement placed successfully at vertex " << vertex <<  " to player " << currentVertex.getOwner() << endl;
           
            return true;
        }
    }

    return false;
    }

    bool Board::placeRoad(Player &player, int edge){

        if (edge < 0 || edge > 71) // Check if the edge is out of range
        {
            cout << "Invalid edge, edge is out of range, you chose: " << edge <<endl;
            return false;
        }

        
            Edge currentEdge = edges[(size_t)edge];
            
                // Check if the edge is already occupied
                if (currentEdge.getOwner() != "none")
                {
                    cout << "Edge " << edge << " is already owned by " << currentEdge.getOwner() << endl;
                    return false;
                }

                // Check if the edge has an adjacent settlement owned by the player
                for (size_t j = 0; j < currentEdge.neighbors_vertice.size(); j++)
                {
                    //check if there is a neighbor vetex of the player
                    int neighborVertexIndex = currentEdge.neighbors_vertice[j];
                    if (vertices[(size_t)neighborVertexIndex].getOwner() == player.getName())
                    {
                        // Place the Road at the edge
                         edges[(size_t)edge].setOwner(player.getName());
                        edges[(size_t)edge].setColor(player.getColor());
                        

                        //cout << "the color is " << currentEdge.getColor() << "\033[0m" <<  endl;

                        player.addRoadsNum(1);
                        cout << "Road placed successfully at edge " << edge << "." << endl;
                        return true;
                    }
                }

                //check if the edge has an adjacent Road owned by the player    
                for (size_t j = 0; j < currentEdge.neighbors_edges.size(); j++)
                {
                    int neighborEdgeIndex = currentEdge.neighbors_edges[j];
                    if (edges[(size_t)neighborEdgeIndex].getOwner() == player.getName()) // if the edge has an adjacent Road owned by the player
                    {
                        //check if the  adjacent edge has an adjacent settlement owned by the player
                        for (size_t k = 0; k < edges[(size_t)neighborEdgeIndex].neighbors_vertice.size(); k++)
                        {
                            int neighborVertexIndex = edges[(size_t)neighborEdgeIndex].neighbors_vertice[k];
                            if (vertices[(size_t)neighborVertexIndex].getOwner() == player.getName()) // if the adjacent edge has an adjacent settlement owned by the player
                            {
                                // Place the Road at the edge
                                edges[(size_t)edge].setOwner(player.getName());
                                edges[(size_t)edge].setColor(player.getColor());
                                
                               // cout << "the color is " << currentEdge.getColor() << "\033[0m" <<  endl;
                                player.addRoadsNum(1);
                                cout << "Road placed successfully at edge " << edge << "." << endl;
                                return true;
                            }
                        }
                        
                    }
                }

        return false;
    }

    bool Board::upgradeSettlementToCity(Player &player, int vertex)
    {
        if (vertex < 0 || vertex >= 54)
        {
            cout << "Invalid vertex, vertex is out of range, you chose: " << vertex <<endl;
            return false;
        }

        Vertex &currentVertex = vertices[(size_t)vertex];
        if (currentVertex.getOwner() != player.getName())
        {
            cout << "Vertex " << vertex << " is not owned by " << player.getName() << endl;
            return false;
        }

        if (currentVertex.getType() != "settlement")
        {
            cout << "Vertex " << vertex << " is not a settlement" << endl;
            return false;
        }

        currentVertex.setType("city");
        player.removeResource(WHEAT, 2);
        player.removeResource(IRON, 3);
        player.addPoints(1);
        cout << "Settlement at vertex " << vertex << " upgraded to a city." << endl;

        return true;


    }

    string Board::printVertex(Vertex &vertex)
     {
        if (vertex.getOwner() == "none")
        {   if(vertex.getNumber()<10)
            {
                return "(" +to_string(vertex.getNumber())+ ")" + "     ";
            }else{
                return "(" +to_string(vertex.getNumber())+ ")" + "    ";
            }
    
        }else{
            if(vertex.getNumber()<10)
            {
                return vertex.getColor() + vertex.getOwner() + "(" + to_string(vertex.getNumber()) + ")" + "\033[0m" + "     " ;
            }else{
                return vertex.getColor() +vertex.getOwner() + "(" + to_string(vertex.getNumber()) + ")" +"\033[0m" + "    " ;

            }
        }
     }  
//print tile will  print the type of the tile and the number on it
    string printTile(Tile& tile) 
    {
        // if (tile.getNumber()<10)
        // {
        //     return tile.getResourceType(tile.getType()) + ", " + to_string(tile.getNumber());
        // }else{
            return tile.getResourceType(tile.getType()) + "," + to_string(tile.getNumber()) ;
        //}
    }



    string printRoad(Edge &edge, string direction) 
    {
        if (edge.getOwner() == "none")
        {
            return direction;
        }else{
            
            return edge.getColor()+direction + "\033[0m";  ;
        }
    }

     void Board::printBoard(){
        cout << "\n-------------------------------------------------------------------\n";
        cout << "            " << printVertex(vertices[1]) << printVertex(vertices[3]) << printVertex(vertices[5]) << endl;
        cout << "           "<<printRoad(edges[0],"/   ")<<printRoad(edges[1],"\\   ")<<printRoad(edges[2], "/   ")<<printRoad(edges[3],"\\   ")<<printRoad(edges[4],"/   ")<<printRoad(edges[5],"\\   ") << endl;
        cout << "        " << printVertex(vertices[0]) << printVertex(vertices[2]) << printVertex(vertices[4]) << printVertex(vertices[6]) << endl;
        cout << "         "<<printRoad(edges[6],"|")<<printTile(tiles[0][0])<<printRoad(edges[7],"|")<<printTile(tiles[0][1])<<printRoad(edges[8], "|")<<printTile(tiles[0][2])<<printRoad(edges[9] ,"|") << endl;
        cout << "        " << printVertex(vertices[8]) << printVertex(vertices[10]) << printVertex(vertices[12]) << printVertex(vertices[14] )<< endl;
        cout << "       "<<printRoad(edges[10],"/    ")<<printRoad(edges[11],"\\  ")<<printRoad(edges[12],"/    ")<<printRoad(edges[13],"\\  ")<<printRoad(edges[14],"/    ")<<printRoad(edges[15],"\\  ")<<printRoad(edges[16],"/    ")<<printRoad(edges[17],"\\  ") << endl;
        cout << "    " << printVertex(vertices[7]) << printVertex(vertices[9]) << printVertex(vertices[11]) << printVertex(vertices[13]) << printVertex(vertices[15]) << endl;
        cout << "     "<<printRoad(edges[18],"|")<<printTile(tiles[1][0])<<printRoad(edges[19],"|")<<printTile(tiles[1][1])<<printRoad(edges[20],"|")<<printTile(tiles[1][2])<<printRoad(edges[21],"|")<<printTile(tiles[1][3])<<printRoad(edges[22],"|") << endl;
        cout << "    " << printVertex(vertices[17]) << printVertex(vertices[19])<< printVertex(vertices[21]) << printVertex(vertices[23]) << printVertex(vertices[25]) << endl;
        cout << "   "<<printRoad(edges[23],"/    ")<<printRoad(edges[24],"\\  ")<<printRoad(edges[25],"/    ")<<printRoad(edges[26],"\\  ")<<printRoad(edges[27],"/    ")<<printRoad(edges[28],"\\  ")<<printRoad(edges[29],"/    ")<<printRoad(edges[30],"\\  ")<<printRoad(edges[31],"/    ")<<printRoad(edges[32],"\\  ") << endl;
        cout << printVertex(vertices[16]) << printVertex(vertices[18]) << printVertex(vertices[20]) << printVertex(vertices[22]) << printVertex(vertices[24]) << printVertex(vertices[26]) << endl;
        cout << " "<<printRoad(edges[33],"|")<<printTile(tiles[2][0])<<printRoad(edges[34],"|")<<printTile(tiles[2][1])<<printRoad(edges[35],"|")<<printTile(tiles[2][2])<<printRoad(edges[36],"|")<<printTile(tiles[2][3])<<printRoad(edges[37],"|")<<printTile(tiles[2][4])<<printRoad(edges[38],"|") << endl;
        cout << printVertex(vertices[27]) << printVertex(vertices[29]) << printVertex(vertices[31]) << printVertex(vertices[33]) << printVertex(vertices[35]) << printVertex(vertices[37]) << endl;
        cout << "   "<<printRoad(edges[39],"\\    ")<<printRoad(edges[40],"/  ")<<printRoad(edges[41],"\\    ")<<printRoad(edges[42],"/  ")<<printRoad(edges[43],"\\    ")<<printRoad(edges[44],"/  ")<<printRoad(edges[45],"\\    ")<<printRoad(edges[46],"/  ")<<printRoad(edges[47],"\\    ")<<printRoad(edges[48],"/  ") << endl;
        cout << "    " << printVertex(vertices[28]) << printVertex(vertices[30]) << printVertex(vertices[32]) << printVertex(vertices[34]) << printVertex(vertices[36]) << endl;
        cout << "     "<<printRoad(edges[49],"|")<<printTile(tiles[3][0])<<printRoad(edges[50],"|")<<printTile(tiles[3][1])<<printRoad(edges[51]," |")<<printTile(tiles[3][2])<<printRoad(edges[52]," |")<<printTile(tiles[3][3])<<printRoad(edges[53],"  |") << endl;
        cout << "    " << printVertex(vertices[38]) << printVertex(vertices[40]) << printVertex(vertices[42]) << printVertex(vertices[44]) << printVertex(vertices[46]) << endl;
        cout << "       "<<printRoad(edges[54],"\\    ")<<printRoad(edges[55],"/  ")<<printRoad(edges[56],"\\    ")<<printRoad(edges[57],"/  ")<<printRoad(edges[58],"\\    ")<<printRoad(edges[59],"/  ")<<printRoad(edges[60],"\\    ")<<printRoad(edges[61],"/  ") << endl;
        cout << "        " << printVertex(vertices[39]) << printVertex(vertices[41]) << printVertex(vertices[43]) << printVertex(vertices[45]) << endl;
        cout << "         "<<printRoad(edges[62],"|")<<printTile(tiles[4][0])<<printRoad(edges[63],"|")<<printTile(tiles[4][1])<<printRoad(edges[64],"|")<<printTile(tiles[4][2])<<printRoad(edges[65],"|") << endl;
        cout << "        " << printVertex(vertices[47]) << printVertex(vertices[49]) << printVertex(vertices[51]) << printVertex(vertices[53]) << endl;
        cout << "           "<<printRoad(edges[66],"\\    ")<<printRoad(edges[67],"/  ")<<printRoad(edges[68],"\\    ")<<printRoad(edges[69],"/  ")<<printRoad(edges[70],"\\    ")<<printRoad(edges[71],"/  ") << endl;
        cout << "            " << printVertex(vertices[48])<< printVertex(vertices[50]) << printVertex(vertices[52]) << "\n\n-------------------------------------------------------------------\n\n";
    }


    
    void Board::distributeResources(Player &player, int diceRoll)
    {
        //cout << "Distributing resources for dice roll " << diceRoll << "..." << endl;

        // Iterate over all tiles
        for (int i = 0; i < 19; i++)
        {
            // Get the tile at index i
            Tile &currentTile = getTile(i);

                //print tile info
              //  cout << "Checking tile at index " << i << " with number " << currentTile.getNumber() << " and type " << currentTile.getType() << endl;

                // Check if the tile's number is equal to the dice roll
                if (currentTile.getNumber() == diceRoll) {
                   // cout << "Tile " <<  i << " matches the dice roll (" << diceRoll << ")." << endl;

                    // Iterate over all vertices of the tile
                    for (int vertexId : currentTile.vertices) {
                    
                        Vertex &currentVertex = getVertex(vertexId);
                        //veterx info
                        //cout << "Checking vertex " << currentVertex.getNumber() << " with owner " << currentVertex.getOwner() << " is equal to == " << player.getName() << endl;

                        //cout << "Checking vertex " << currentVertex.getNumber() << " with owner " << currentVertex.getOwner() << " is equal to == " << player.getName() << endl;
                        // Check if the vertex is owned by the player
                        if (currentVertex.getOwner() == player.getName()) {
                            //cout << "Player " << player.getName() << " owns vertex " << currentVertex.getNumber() << "." << endl;

                            // Check if the vertex is a settlement
                            if (currentVertex.getType() == "settlement") {
                                player.addResource(currentTile.getType(), 1);
                              //  cout << "Player " << player.getName() << " received 1 " << currentTile.getType() << " from settlement at vertex " << currentVertex.getNumber() << endl;
                            }
                            // Check if the vertex is a city
                            else if (currentVertex.getType() == "city") {
                                player.addResource(currentTile.getType(), 2);
                               // cout << "Player " << player.getName() << " received 2 " << currentTile.getType() << " from city at vertex " << currentVertex.getNumber() << endl;
                            }
                        }
                    }
                }
            
            
        }
    }

    void Board::intialDistributeResources(Player &player)
    {
        for (Vertex &vertex : vertices) // Iterate over all vertices on the board

        {  
             // Check if the vertex is owned by the player and is a settlement
            if (vertex.getOwner() == player.getName() && vertex.getType() == "settlement") 
            {            
                // Iterate over all tiles adjacent to this vertex
                for (int tileId : vertex.tiles) 
                {
                    Tile &tile = getTile(tileId);
                    if (tile.getType() != DESERT) 
                    {
                        player.addResource(tile.getType(), 1);
                        //cout << "Player " << player.getName() << " received 1 " << tile.getResourceType(tile.getType()) << " from tile " << tile.getIndex() << "." << endl;
                    }
                }
            }
        }
    }

     void Board::initializeVerticesNeighbors()
    {
        vertices[0].neighbors_vertice = {1, 8};
        vertices[1].neighbors_vertice = {0, 2};
        vertices[2].neighbors_vertice = {1, 3, 10};
        vertices[3].neighbors_vertice = {2, 4};
        vertices[4].neighbors_vertice = {3, 5, 12};
        vertices[5].neighbors_vertice = {4, 6};
        vertices[6].neighbors_vertice = {5, 14};
        vertices[7].neighbors_vertice = {8, 17};
        vertices[8].neighbors_vertice = {0, 7, 9};
        vertices[9].neighbors_vertice = {8, 10, 19};
        vertices[10].neighbors_vertice = {2, 9, 11};
        vertices[11].neighbors_vertice = {10, 12, 21};
        vertices[12].neighbors_vertice = {4, 11, 13};
        vertices[13].neighbors_vertice = {12, 14, 23};
        vertices[14].neighbors_vertice = {6, 13, 15};
        vertices[15].neighbors_vertice = {14, 25};
        vertices[16].neighbors_vertice = {17, 27};
        vertices[17].neighbors_vertice = {7, 16, 18};
        vertices[18].neighbors_vertice = {17, 19, 29};
        vertices[19].neighbors_vertice = {9, 18, 20};
        vertices[20].neighbors_vertice = {19, 21, 31};
        vertices[21].neighbors_vertice = {11, 20, 22};
        vertices[22].neighbors_vertice = {21, 23, 33};
        vertices[23].neighbors_vertice = {13, 22, 24};
        vertices[24].neighbors_vertice = {23, 25, 35};
        vertices[25].neighbors_vertice = {15, 24, 26};
        vertices[26].neighbors_vertice = {25, 37};
        vertices[27].neighbors_vertice = {16, 28};
        vertices[28].neighbors_vertice = {27, 29, 38};
        vertices[29].neighbors_vertice = {18, 28, 30};
        vertices[30].neighbors_vertice = {29, 31, 40};
        vertices[31].neighbors_vertice = {20, 30, 32};
        vertices[32].neighbors_vertice = {31, 33, 42};
        vertices[33].neighbors_vertice = {22, 32, 34};
        vertices[34].neighbors_vertice = {33, 35, 44};
        vertices[35].neighbors_vertice = {24, 34, 36};
        vertices[36].neighbors_vertice = {35, 37, 46};
        vertices[37].neighbors_vertice = {26, 36};
        vertices[38].neighbors_vertice = {28, 39};
        vertices[39].neighbors_vertice = {38, 40, 47};
        vertices[40].neighbors_vertice = {30, 39, 41};
        vertices[41].neighbors_vertice = {40, 42, 49};
        vertices[42].neighbors_vertice = {32, 41, 43};
        vertices[43].neighbors_vertice = {42, 44, 51};
        vertices[44].neighbors_vertice = {34, 43, 45};
        vertices[45].neighbors_vertice = {44, 46, 53};
        vertices[46].neighbors_vertice = {36, 45};
        vertices[47].neighbors_vertice = {39, 48};
        vertices[48].neighbors_vertice = {47, 49};
        vertices[49].neighbors_vertice = {41, 48, 50};
        vertices[50].neighbors_vertice = {49, 51};
        vertices[51].neighbors_vertice = {43, 50, 52};
        vertices[52].neighbors_vertice = {51, 53};
        vertices[53].neighbors_vertice = {45, 52};

        vertices[0].neighbors_edges = {0, 6};
        vertices[1].neighbors_edges = {0, 1};
        vertices[2].neighbors_edges = {1, 2, 7};
        vertices[3].neighbors_edges = {2, 3};
        vertices[4].neighbors_edges = {3, 4, 8};
        vertices[5].neighbors_edges = {4, 5};
        vertices[6].neighbors_edges = {5, 9};
        vertices[7].neighbors_edges = {10, 18};
        vertices[8].neighbors_edges = {6, 10, 11};
        vertices[12].neighbors_edges = {8, 14, 15};
        vertices[13].neighbors_edges = {15, 16, 21};
        vertices[14].neighbors_edges = {9, 16, 17};
        vertices[15].neighbors_edges = {17, 22};
        vertices[16].neighbors_edges = {23, 33};
        vertices[17].neighbors_edges = {18, 23, 24};
        vertices[18].neighbors_edges = {24, 25, 34};
        vertices[19].neighbors_edges = {19, 25, 26};
        vertices[20].neighbors_edges = {26, 27, 35};
        vertices[21].neighbors_edges = {20, 27, 28};
        vertices[22].neighbors_edges = {28, 29, 36};
        vertices[23].neighbors_edges = {21, 29, 30};
        vertices[24].neighbors_edges = {30, 31, 37};
        vertices[25].neighbors_edges = {22, 31, 32};
        vertices[26].neighbors_edges = {32, 38};
        vertices[27].neighbors_edges = {33, 39};
        vertices[28].neighbors_edges = {39, 40, 49};
        vertices[29].neighbors_edges = {34, 40, 41};
        vertices[30].neighbors_edges = {41, 42, 50};
        vertices[31].neighbors_edges = {35, 42, 43};
        vertices[32].neighbors_edges = {43, 44, 51};
        vertices[33].neighbors_edges = {36, 44, 45};
        vertices[34].neighbors_edges = {45, 46, 52};
        vertices[35].neighbors_edges = {37, 46, 47};
        vertices[36].neighbors_edges = {47, 48, 53};
        vertices[37].neighbors_edges = {38, 48};
        vertices[38].neighbors_edges = {49, 54};
        vertices[39].neighbors_edges = {54, 55, 62};
        vertices[40].neighbors_edges = {50, 55, 56};
        vertices[41].neighbors_edges = {56, 57, 63};
        vertices[42].neighbors_edges = {51, 57, 58};
        vertices[43].neighbors_edges = {58, 59, 64};
        vertices[44].neighbors_edges = {52, 59, 60};
        vertices[45].neighbors_edges = {60, 61, 65};
        vertices[46].neighbors_edges = {53, 61};
        vertices[47].neighbors_edges = {62, 66};
        vertices[48].neighbors_edges = {66, 67};
        vertices[49].neighbors_edges = {63, 67, 68};
        vertices[50].neighbors_edges = {68, 69};
        vertices[51].neighbors_edges = {64, 69, 70};
        vertices[52].neighbors_edges = {70, 71};
        vertices[53].neighbors_edges = {65, 71};
    }

    void Board::initializeEdgesNeighbors()
    {
        edges[0].neighbors_vertice = {0, 1};
        edges[1].neighbors_vertice = {1, 2};
        edges[2].neighbors_vertice = {2, 3};
        edges[3].neighbors_vertice = {3, 4};
        edges[4].neighbors_vertice = {4, 5};
        edges[5].neighbors_vertice = {5, 6};
        edges[6].neighbors_vertice = {0, 8};
        edges[7].neighbors_vertice = {2, 10};
        edges[8].neighbors_vertice = {4, 12};
        edges[9].neighbors_vertice = {6, 14};
        edges[10].neighbors_vertice = {7, 8};
        edges[11].neighbors_vertice = {8, 9};
        edges[12].neighbors_vertice = {9, 10};
        edges[13].neighbors_vertice = {10, 11};
        edges[14].neighbors_vertice = {11, 12};
        edges[15].neighbors_vertice = {12, 13};
        edges[16].neighbors_vertice = {13, 14};
        edges[17].neighbors_vertice = {14, 15};
        edges[18].neighbors_vertice = {7, 17};
        edges[19].neighbors_vertice = {9, 19};
        edges[20].neighbors_vertice = {11, 21};
        edges[21].neighbors_vertice = {13, 23};
        edges[22].neighbors_vertice = {15, 25};
        edges[23].neighbors_vertice = {16, 17};

        edges[24].neighbors_vertice = {17, 18};
        edges[25].neighbors_vertice = {18, 19};
        edges[26].neighbors_vertice = {19, 20};
        edges[27].neighbors_vertice = {20, 21};
        edges[28].neighbors_vertice = {21, 22};
        edges[29].neighbors_vertice = {22, 23};
        edges[30].neighbors_vertice = {23, 24};
        edges[31].neighbors_vertice = {24, 25};
        edges[32].neighbors_vertice = {25, 26};
        edges[33].neighbors_vertice = {16, 27};
        edges[34].neighbors_vertice = {18, 29};
        edges[35].neighbors_vertice = {20, 31};
        edges[36].neighbors_vertice = {22, 33};
        edges[37].neighbors_vertice = {24, 35};
        edges[38].neighbors_vertice = {26, 37};
        edges[39].neighbors_vertice = {27, 28};
        edges[40].neighbors_vertice = {28, 29};
        edges[41].neighbors_vertice = {29, 30};
        edges[42].neighbors_vertice = {30, 31};
        edges[43].neighbors_vertice = {31, 32};
        edges[44].neighbors_vertice = {32, 33};
        edges[45].neighbors_vertice = {33, 34};
        edges[46].neighbors_vertice = {34, 35};
        edges[47].neighbors_vertice = {35, 36};
        edges[48].neighbors_vertice = {36, 37};
        edges[49].neighbors_vertice = {28, 38};
        edges[50].neighbors_vertice = {30, 40};
        edges[51].neighbors_vertice = {32, 42};
        edges[52].neighbors_vertice = {34, 44};
        edges[53].neighbors_vertice = {36, 46};
        edges[54].neighbors_vertice = {38, 39};
        edges[55].neighbors_vertice = {39, 40};
        edges[56].neighbors_vertice = {40, 41};
        edges[57].neighbors_vertice = {41, 42};
        edges[58].neighbors_vertice = {42, 43};
        edges[59].neighbors_vertice = {43, 44};
        edges[60].neighbors_vertice = {44, 45};
        edges[61].neighbors_vertice = {45, 46};
        edges[62].neighbors_vertice = {39, 47};
        edges[63].neighbors_vertice = {41, 49};
        edges[64].neighbors_vertice = {43, 51};
        edges[65].neighbors_vertice = {45, 53};
        edges[66].neighbors_vertice = {47, 48};
        edges[67].neighbors_vertice = {48, 49};
        edges[68].neighbors_vertice = {49, 50};
        edges[69].neighbors_vertice = {50, 51};
        edges[70].neighbors_vertice = {51, 52};
        edges[71].neighbors_vertice = {52, 53};

        edges[0].neighbors_edges = {1, 6};
        edges[1].neighbors_edges = {0, 2, 7};
        edges[2].neighbors_edges = {1, 3, 7};
        edges[3].neighbors_edges = {2, 4, 8};
        edges[4].neighbors_edges = {3, 5, 8};
        edges[5].neighbors_edges = {4, 9};
        edges[6].neighbors_edges = {0, 10, 11};
        edges[7].neighbors_edges = {1, 2, 12, 13};
        edges[8].neighbors_edges = {3, 4, 14, 15};
        edges[9].neighbors_edges = {5, 16, 17};
        edges[10].neighbors_edges = {6, 11, 18};
        edges[11].neighbors_edges = {6, 10, 12, 19};
        edges[12].neighbors_edges = {7, 11, 13, 19};
        edges[13].neighbors_edges = {7, 12, 14, 20};
        edges[14].neighbors_edges = {8, 13, 15, 20};
        edges[15].neighbors_edges = {8, 14, 16, 21};
        edges[16].neighbors_edges = {9, 15, 17, 21};
        edges[17].neighbors_edges = {9, 16, 22};
        edges[18].neighbors_edges = {10, 23, 24};
        edges[19].neighbors_edges = {11, 12, 25, 26};
        edges[20].neighbors_edges = {13, 14, 27, 28};
        edges[21].neighbors_edges = {15, 16, 29, 30};
        edges[22].neighbors_edges = {17, 31, 32};
        edges[23].neighbors_edges = {18, 24, 33};
        edges[24].neighbors_edges = {18, 23, 25, 34};
        edges[25].neighbors_edges = {19, 24, 26, 34};
        edges[26].neighbors_edges = {19, 25, 27, 35};
        edges[27].neighbors_edges = {20, 26, 28, 35};
        edges[28].neighbors_edges = {20, 27, 29, 36};
        edges[29].neighbors_edges = {21, 28, 30, 36};
        edges[30].neighbors_edges = {21, 29, 31, 37};
        edges[31].neighbors_edges = {22, 30, 32, 37};
        edges[32].neighbors_edges = {22, 31, 38};
        edges[33].neighbors_edges = {23, 39};
        edges[34].neighbors_edges = {24, 25, 40, 41};
        edges[35].neighbors_edges = {26, 27, 42, 43};
        edges[36].neighbors_edges = {28, 29, 44, 45};
        edges[37].neighbors_edges = {30, 31, 46, 47};
        edges[38].neighbors_edges = {32, 48};
        edges[39].neighbors_edges = {33, 40, 49};
        edges[40].neighbors_edges = {34, 39, 41, 49};
        edges[41].neighbors_edges = {34, 40, 42, 50};
        edges[42].neighbors_edges = {35, 41, 43, 50};
        edges[43].neighbors_edges = {35, 42, 44, 51};
        edges[44].neighbors_edges = {36, 43, 45, 51};
        edges[45].neighbors_edges = {36, 44, 46, 52};
        edges[46].neighbors_edges = {37, 45, 47, 52};
        edges[47].neighbors_edges = {37, 46, 48, 53};
        edges[48].neighbors_edges = {38, 47, 53};
        edges[49].neighbors_edges = {39, 40, 54};
        edges[50].neighbors_edges = {41, 42, 55, 56};
        edges[51].neighbors_edges = {43, 44, 57, 58};
        edges[52].neighbors_edges = {45, 46, 59, 60};
        edges[53].neighbors_edges = {47, 48, 61};
        edges[54].neighbors_edges = {49, 55, 62};
        edges[55].neighbors_edges = {50, 54, 56, 62};
        edges[56].neighbors_edges = {50, 55, 57, 63};
        edges[57].neighbors_edges = {51, 56, 58, 63};
        edges[58].neighbors_edges = {51, 57, 59, 64};
        edges[59].neighbors_edges = {52, 58, 60, 64};
        edges[60].neighbors_edges = {52, 59, 61, 65};
        edges[61].neighbors_edges = {53, 60, 65};
        edges[62].neighbors_edges = {54, 55, 66};
        edges[63].neighbors_edges = {56, 57, 67, 68};
        edges[64].neighbors_edges = {58, 59, 69, 70};
        edges[65].neighbors_edges = {60, 61, 71};
        edges[66].neighbors_edges = {62, 67};
        edges[67].neighbors_edges = {63, 66, 68};
        edges[68].neighbors_edges = {63, 67, 69};
        edges[69].neighbors_edges = {64, 68, 70};
        edges[70].neighbors_edges = {64, 69, 71};
        edges[71].neighbors_edges = {65, 70};
    }

     void Board::assignVerticesAndEdgesToTiles()
    {

        tiles[0][0].vertices = {0, 1, 2, 8, 9, 10};
        tiles[0][1].vertices = {2, 3, 4, 10, 11, 12};
        tiles[0][2].vertices = {4, 5, 6, 12, 13, 14};
        tiles[1][0].vertices = {7, 8, 9, 17, 18, 19};
        tiles[1][1].vertices = {9, 10, 11, 19, 20, 21};
        tiles[1][2].vertices = {11, 12, 13, 21, 22, 23};
        tiles[1][3].vertices = {13, 14, 15, 23, 24, 25};
        tiles[2][0].vertices = {16, 17, 18, 27, 28, 29};
        tiles[2][1].vertices = {18, 19, 20, 29, 30, 31};
        tiles[2][2].vertices = {20, 21, 22, 31, 32, 33};
        tiles[2][3].vertices = {22, 23, 24, 33, 34, 35};
        tiles[2][4].vertices = {24, 25, 26, 35, 36, 37};
        tiles[3][0].vertices = {28, 29, 30, 38, 39, 40};
        tiles[3][1].vertices = {30, 31, 32, 40, 41, 42};
        tiles[3][2].vertices = {32, 33, 34, 42, 43, 44};
        tiles[3][3].vertices = {34, 35, 36, 44, 45, 46};
        tiles[4][0].vertices = {39, 40, 41, 47, 48, 49};
        tiles[4][1].vertices = {41, 42, 43, 49, 50, 51};
        tiles[4][2].vertices = {43, 44, 45, 51, 52, 53};

        tiles[0][0].edges = {0, 1, 6, 7, 11, 12};
        tiles[0][1].edges = {2, 3, 7, 8, 13, 14};
        tiles[0][2].edges = {4, 5, 8, 9, 15, 16};
        tiles[1][0].edges = {10, 11, 18, 19, 24, 25};
        tiles[1][1].edges = {12, 13, 19, 20, 26, 27};
        tiles[1][2].edges = {14, 15, 20, 21, 28, 29};
        tiles[1][3].edges = {16, 17, 21, 22, 30, 31};
        tiles[2][0].edges = {23, 24, 33, 34, 39, 40};
        tiles[2][1].edges = {25, 26, 34, 35, 41, 42};
        tiles[2][2].edges = {27, 28, 35, 36, 43, 44};
        tiles[2][3].edges = {29, 30, 36, 37, 45, 46};
        tiles[2][4].edges = {31, 32, 37, 38, 47, 48};
        tiles[3][0].edges = {40, 41, 49, 50, 54, 55};
        tiles[3][1].edges = {42, 43, 50, 51, 56, 57};
        tiles[3][2].edges = {44, 45, 51, 52, 58, 59};
        tiles[3][3].edges = {46, 47, 52, 53, 60, 61};
        tiles[4][0].edges = {55, 56, 62, 63, 66, 67};
        tiles[4][1].edges = {57, 58, 63, 64, 68, 69};
        tiles[4][2].edges = {59, 60, 64, 65, 70, 71};


        // Assign tiles to vertices
    for (size_t layer = 0; layer < tiles.size(); ++layer) {
        for (size_t i = 0; i < tiles[layer].size(); ++i) {
            Tile &tile = tiles[layer][i];
            for (int vertexId : tile.vertices) {
                vertices[(size_t)vertexId].addTile(tile.getIndex());
            }
        }
    }

    }

    

    Tile &Board::getTile(int i1)
    {
        size_t i = (size_t)i1;
        if (i < 0 || i >= 19)
        {
            throw invalid_argument("Invalid tile index");
        }
        if (i < 3)
        {
            return tiles[0][i];
        }
        else if (i < 7)
        {
            return tiles[1][i - 3];
        }
        else if (i < 12)
        {
            return tiles[2][i - 7];
        }
        else if (i < 16)
        {
            return tiles[3][i - 12];
        }
        else
        {
            return tiles[4][i - 16];
        }
    }

    Vertex &Board::getVertex(int vertexId)
    {
        if (vertexId < 0 || vertexId >= vertices.size())
        {
            throw invalid_argument("Invalid vertex index");
        }
        return vertices[(size_t)vertexId];
    }


    
} // namespace ariel    