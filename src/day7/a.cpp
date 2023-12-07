#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <map>

enum HandType {
    high_card,
    one_pair,
    two_pair,
    three_of_a_kind,
    full_house,
    four_of_a_kind,
    five_of_a_kind
};

enum CardType {
    two = 2,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    T,
    J = 11,
    Q = 12,
    K = 13,
    A = 14
};

std::map<char, CardType> card_map = {
    {'2', two},
    {'3', three},
    {'4', four},
    {'5', five},
    {'6', six},
    {'7', seven},
    {'8', eight},
    {'9', nine},
    {'T', T},
    {'J', J},
    {'Q', Q},
    {'K', K},
    {'A', A}
};

class Hand {
    public:
        HandType type;
        int bid;
        std::vector<CardType> cards;

        Hand(HandType type, int value, std::vector<CardType> cards) {
            this->type = type;
            this->bid = value;
            this->cards = cards;
        }

        bool operator<(const Hand& other) const {
            if (this->type == other.type) {
                for (int i = 0; i < this->cards.size(); i++) {
                    if (this->cards[i] != other.cards[i])
                        return this->cards[i] < other.cards[i];
                }
            }
            return this->type < other.type;
        }
};

HandType find_hand_type(std::vector<CardType> cards) {
    std::vector<int> counts(15, 0);
    for (auto card: cards) {
        counts[card]++;
    }
    std::sort(counts.begin(), counts.end(), std::greater<int>());
    switch (counts[0]) {
        case 5:
            return five_of_a_kind;
        case 4:
            return four_of_a_kind;
        case 3:
            if (counts[1] == 2) {
                return full_house;
            } else {
                return three_of_a_kind;
            }
        case 2:
            if (counts[1] == 2) {
                return two_pair;
            } else {
                return one_pair;
            }
        case 1:
            return high_card;
        default:
            std::cout << "blah";
            throw "Invalid hand";
    }
}

int main(int argc, char* argv[])
{
    std::string line;

    std::vector<Hand> hands;

    while (getline(std::cin, line)) {
        auto cards_ss = line.substr(0, 5);
        std::vector<CardType> cards;
        for (char card: cards_ss) {
            cards.push_back(card_map[card]);
        }

        auto hand_type = find_hand_type(cards);

        auto bid_ss = line.substr(6);
        int bid = 0;
        for (int i = 0; i < bid_ss.size(); i++) {
            bid += (bid_ss[bid_ss.size() - 1 - i]  - '0') * pow(10, i);
        }

        hands.push_back(Hand(hand_type, bid, cards));
    }
    std::sort(hands.begin(), hands.end());
    int acc = 0;
    for (int i = 0; i < hands.size(); i++) {
        acc += hands[i].bid * (i + 1);
    }
    std::cout << acc << std::endl;
}