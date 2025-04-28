#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <windows.h>

#include "bj_functions.h"
#include "bj_classes.h"


using namespace std;

int main() {
    // enables suit symbols to print in terminal
    SetConsoleOutputCP(CP_UTF8);

    // user inputs starting amount
    double balance = startMessage();

    // creates and shuffles 6 decks of cards
    vector<tuple<int, string>> deck = createDeck();

    // game loop
    while (balance > 0) {
        // print balance
        cout << "your balance is " << balance << endl;

        // user inputs amount to bet for the round
        double bet;
        cout << "Enter an amount to bet: ";
        cin >> bet;

        // pop 2 cards for dealer and 2 for player and build hands for each
        Hand dealerHand = Hand(true);
        Hand playerHand = Hand(false);
        for (int i=0; i < 2; i++) {
            if (!deck.empty()) {
                tuple<int, string> card = deck.back();
                deck.pop_back();

                dealerHand.addCard(get<0>(card), get<1>(card));
            } else { // deck is empty and new one is created
                deck = createDeck();

                tuple<int, string> card = deck.back();
                deck.pop_back();

                dealerHand.addCard(get<0>(card), get<1>(card));
            }
        }
        for (int i=0; i < 2; i++) {
            if (!deck.empty()) {
                tuple<int, string> card = deck.back();
                deck.pop_back();

                playerHand.addCard(get<0>(card), get<1>(card));
            } else { // deck is empty and new one is created
                deck = createDeck();

                tuple<int, string> card = deck.back();
                deck.pop_back();

                playerHand.addCard(get<0>(card), get<1>(card));
            }
        }

        // calculates the dealer's and player's hand value
        int dealerValue = dealerHand.calcHand();
        int playerValue = playerHand.calcHand();

        // prints dealer and player hands
        dealerHand.printHand();
        playerHand.printHand();

        // checks for player BlackJack
        if ((playerValue == 21) && (dealerValue != 21)) {
            cout << "BlackJack!" << endl;
            balance = balance + (bet * 1.5);
        } else if ((playerValue == 21) && (dealerValue == 21)) {
            cout << "Tie" << endl;
        }

        // ask player to hit or stay
        char hitStay;
        cout << "Hit or stay (h|s): ";
        cin >> hitStay;

        // players turn
        if (hitStay == 'h') {
            do {
                tuple<int, string> card;
                card = deck.back();
                deck.pop_back();

                // calculates new player value
                playerHand.addCard(get<0>(card), get<1>(card));
                playerValue = playerHand.calcHand();

                // print both hands
                dealerHand.printHand();
                playerHand.printHand();

                // ends if player over 21
                if (playerValue > 21) {
                    dealerHand.setDealer(false);
                    break;
                }

                cout << "Hit or Stay (h|s): ";
                cin >> hitStay;
            } while (hitStay == 'h' && playerValue < 21);
        }

        // dealers turn
        if (hitStay != 'h' && playerValue <= 21) {
            dealerHand.setDealer(false);
            while (dealerValue < 17 && dealerValue < playerValue) {
                tuple<int, string> card;
                if (!deck.empty()) {
                    card = deck.back();
                    deck.pop_back();
                } else {
                    deck = createDeck();
                    card = deck.back();
                    deck.pop_back();
                }
                dealerHand.addCard(get<0>(card), get<1>(card));

                dealerValue = dealerHand.calcHand();
            }
        }

        // print both hands
        dealerHand.printHand();
        playerHand.printHand();

        // compare hands for end of round
        if (playerValue == dealerValue) {
            cout << "Tie" << endl;
        } else if (playerValue > 21 || dealerValue > playerValue) {
            cout << "Dealer wins" << endl;
            balance = balance - bet;
        } else if (playerValue == 21 || playerValue > dealerValue) {
            cout << "Player wins!" << endl;
            balance = balance + bet;
        }
    }
    return 0;
}
