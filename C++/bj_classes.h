#ifndef BJ_CLASSES_H
#define BJ_CLASSES_H

#include <vector>
#include <string>

class Hand {
private:
    std::vector<int> values;
    std::vector<std::string> suits;
    bool isDealer;
    int length;
public:
    // constructor
    Hand(bool dealer);

    // adds a card to the hand
    void addCard(const int& value, const std::string& suit);

    // gets length of hand
    int getLength() const;

    // gets dealer status
    bool getDealer() const;
    // sets dealer status
    void setDealer(bool d);

    // calculates the value of the hand
    int calcHand() const;

    // prints hand
    void printHand() const;
};

#endif //BJ_CLASSES_H
