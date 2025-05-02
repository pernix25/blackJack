#include <iostream>
#include "bj_functions.h"
#include <algorithm>
#include <random>

using namespace std;

double startMessage() { // prints the starting message and gets the starting amount for the player
    double balance;

    cout << "Welcome to Black Jack" << endl;
    cout << "Enter starting amount: " << endl;

    cin >> balance;
    return balance;
}

vector<tuple<int, string>> createDeck() {
    vector<tuple<int, string>> deck;

    int possibleValues[13] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
    vector<string> possibleSuits = {"♠", "♥", "♦", "♣"};

    for (int i = 0; i < 6; i++) {
        for (int value : possibleValues)
        {
            for (string suit : possibleSuits)
            {
                tuple<int, string> myTuple(value, suit);
                deck.push_back(myTuple);
            }
        }
    }

    random_device rd;
    default_random_engine rng(rd());

    shuffle(deck.begin(), deck.end(), rng);

    return deck;
}