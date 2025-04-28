#ifndef BJ_CLASSES_H
#define BJ_CLASSES_H

#include <vector>
#include <string>

class Hand {
private:
    std::vector<int> values;
    std::vector<std::string> suits;
    bool isDealer;
public:
    // constructor
    Hand(bool dealer);

    // adds a card to the hand
    void addCard(int& value, std::string& suit);

    // gets length of hand
    int length();

    // gets dealer status
    bool getDealer();
    // sets dealer status
    void setDealer(bool d);

    // calculates the value of the hand
    int calcHand();

    // prints hand
    void printHand();
};

#endif //BJ_CLASSES_H
