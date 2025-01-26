#ifndef DEVCARD_HPP
#define DEVCARD_HPP

#include "player.hpp"
#include "catan.hpp"
#include <iostream>
#include <string>

namespace ariel {

    class Catan;  // Forward declaration 

    class Devcard {
    private:
        string type;

    public:
        Devcard(const string &type);
        virtual ~Devcard();
        string getType() const
        {
            return type;
        }
        virtual void playCard(Player &player, Catan &catan) = 0;
    };

    class Knight : public Devcard {
    public:
        Knight();
        void playCard(Player &player, Catan &catan) override;
    };

    class VictoryPoint : public Devcard {
    public:
        VictoryPoint();
        void playCard(Player &player, Catan &catan) override;
    };

    class Monopoly : public Devcard {
    public:
        Monopoly();
        void playCard(Player &player, Catan &catan) override;
    };

    class YearOfPlenty : public Devcard {
    public:
        YearOfPlenty();
        void playCard(Player &player, Catan &catan) override;
    };

    class RoadBuilding : public Devcard {
    public:
        RoadBuilding();
        void playCard(Player &player, Catan &catan) override;
    };

}

#endif // DEVCARD_HPP
