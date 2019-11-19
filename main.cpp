#include <iostream>
#include <iomanip>
#include <vector>
using std::cout;
using std::endl;


unsigned int getNumberOfCard(char number)
{
    if (std::isdigit(number))
    {
        return number - '0';
    }
    else
    {
        switch (number)
        {
            case 'T':
                return 10;
            case 'J':
                return 11;
            case 'Q':
                return 12;
            case 'K':
                return 13;
            case 'A':
                return 14;
            default:
                return 0;
        }
    }
}

void turn(std::vector<unsigned int> &player, std::vector<unsigned int> &opponent, std::vector<unsigned int> &gameCards, int &coverTries, bool &turn)
{
    if (coverTries > 0)
    {
        while (coverTries > 0 and !player.empty())
        {
            --coverTries;
            int cardPlayed = player.front();
            gameCards.insert(gameCards.begin(), cardPlayed);
            player.erase(player.begin());

            if (cardPlayed > 10)
            {
                coverTries = cardPlayed - 10;
                turn = !turn;
                return;
            }

            if (coverTries == 0)
            {
                while (!gameCards.empty())
                {
                    opponent.push_back(gameCards.back());
                    gameCards.pop_back();
                }
                turn = !turn;
            }
        }
    }
    else
    {
        int cardPlayed = player.front();
        gameCards.insert(gameCards.begin(), cardPlayed);
        player.erase(player.begin());

        if (cardPlayed > 10)
            coverTries = cardPlayed - 10;

        turn = !turn;
    }
}

int main() {
    while (true) {
        std::string card;
        std::vector<unsigned int> nonDealer, dealer, gameCards;
        bool nonDealerTurn = true;

        for (int i = 0; i < 52; ++i)
        {
            std::cin >> card;
            if (card[0] == '#')
                return EXIT_SUCCESS;

            nonDealerTurn ? nonDealer.insert(nonDealer.begin(), getNumberOfCard(card[1])) :
            dealer.insert(dealer.begin(), getNumberOfCard(card[1]));
            nonDealerTurn = !nonDealerTurn;
        }

        int coverTries = 0;

        while (true) {
            if ((nonDealer.empty() && nonDealerTurn) || (dealer.empty() && !nonDealerTurn))
                break;

            if (nonDealerTurn)
                turn(nonDealer, dealer, gameCards, coverTries, nonDealerTurn);
            else
                turn(dealer, nonDealer, gameCards, coverTries, nonDealerTurn);
        }

        if (!nonDealer.empty())
            cout << "2" << std::setw(3) << nonDealer.size() << endl;
        else
            cout << "1" << std::setw(3) << dealer.size() << endl;
    }
}