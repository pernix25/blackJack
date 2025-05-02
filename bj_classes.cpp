#include <iostream>
#include <vector>
#include <string>
#include "bj_classes.h"

Hand::Hand(const bool dealer) {
    isDealer = dealer;
    length = 0;
}

void Hand::addCard(const int& value, const std::string& suit) {
    values.push_back(value);
    suits.push_back(suit);

    this->length++;
}
int Hand::getLength() const {
    return this->length;
}
bool Hand::getDealer() const {
    return isDealer;
}
void Hand::setDealer(const bool d) {
    this->isDealer = d;
}
int Hand::calcHand() const {
    int total = 0;
    int numAces = 0;

    for (const int value : values) {
        switch (value) {
            case 1:
                numAces++;
                break;
            case 11:
            case 12:
            case 13:
                total = total + 10;
                break;
            default:
                total = total + value;
                break;
        }
    }
    if (numAces == 1) {
        if (total + 11 > 21) {
            total++;
        } else {
            total = total + 11;
        }
    } else if (numAces > 1) {
        total = total + (numAces - 1);
        if (total + 11 > 21) {
            total++;
        } else {
            total = total + 11;
        }
    }
    return total;
}
void Hand::printHand() const {
    const int handLength = getLength();

    if (getDealer()) {
        const int& visibleCardValue = values.back();
        const std::string& visibleCardSuit = suits.back();

        switch(visibleCardValue) {
            case 1:
                std::cout << "+-------++-------+" << std::endl;
                std::cout << "|-------||A      |" << std::endl;
                std::cout << "|-------||   " << visibleCardSuit << "   |" << std::endl;
                std::cout << "|-------||      A|" << std::endl;
                std::cout << "+-------++-------+" << std::endl;
                break;
            case 10:
                std::cout << "+-------++-------+" << std::endl;
                std::cout << "|-------||10     |" << std::endl;
                std::cout << "|-------||   " << visibleCardSuit << "   |" << std::endl;
                std::cout << "|-------||     10|" << std::endl;
                std::cout << "+-------++-------+" << std::endl;
                break;
            case 11:
                std::cout << "+-------++-------+" << std::endl;
                std::cout << "|-------||J      |" << std::endl;
                std::cout << "|-------||   " << visibleCardSuit << "   |" << std::endl;
                std::cout << "|-------||      J|" << std::endl;
                std::cout << "+-------++-------+" << std::endl;
                break;
            case 12:
                std::cout << "+-------++-------+" << std::endl;
                std::cout << "|-------||Q      |" << std::endl;
                std::cout << "|-------||   " << visibleCardSuit << "   |" << std::endl;
                std::cout << "|-------||      Q|" << std::endl;
                std::cout << "+-------++-------+" << std::endl;
                break;
            case 13:
                std::cout << "+-------++-------+" << std::endl;
                std::cout << "|-------||K      |" << std::endl;
                std::cout << "|-------||   " << visibleCardSuit << "   |" << std::endl;
                std::cout << "|-------||      K|" << std::endl;
                std::cout << "+-------++-------+" << std::endl;
                break;
            default:
                std::cout << "+-------++-------+" << std::endl;
                std::cout << "|-------||" << visibleCardValue << "      |" << std::endl;
                std::cout << "|-------||   " << visibleCardSuit << "   |" << std::endl;
                std::cout << "|-------||      " << visibleCardValue << '|' << std::endl;
                std::cout << "+-------++-------+" << std::endl;
                break;
        }
    }
    else {
        int i = 0;
        do {
            std::cout << "+-------+";
            i++;
        } while(i < handLength);
        std::cout << std::endl;

        i = 0;
        do {
            const int visibleCardValue = this->values[i];
            switch(visibleCardValue) {
                case 1:
                    std::cout << "|A      |";
                    break;
                case 10:
                    std::cout << "|10     |";
                    break;
                case 11:
                    std::cout << "|J      |";
                    break;
                case 12:
                    std::cout << "|Q      |";
                    break;
                case 13:
                    std::cout << "|K      |";
                    break;
                default:
                    std::cout << '|' << visibleCardValue << "      |";
                    break;
            }
            i++;
        } while (i < handLength);
        std::cout << std::endl;

        i = 0;
        do {
          std::string visibleCardSuit = this->suits[i];
            std::cout << "|   " << visibleCardSuit << "   |";
            i++;
        } while (i < handLength);
        std::cout << std::endl;

        i = 0;
        do {
            const int visibleCardValue = this->values[i];
            switch(visibleCardValue) {
                case 1:
                    std::cout << "|      A|";
                    break;
                case 10:
                    std::cout << "|     10|";
                    break;
                case 11:
                    std::cout << "|      J|";
                    break;
                case 12:
                    std::cout << "|      Q|";
                    break;
                case 13:
                    std::cout << "|      K|";
                    break;
                default:
                    std::cout << "|      " << visibleCardValue << '|';
                    break;
            }
            i++;
        } while(i < handLength);
        std::cout << std::endl;

        i = 0;
        do {
            std::cout << "+-------+";
            i++;
        } while(i < handLength);
        std::cout << std::endl;
    }
}