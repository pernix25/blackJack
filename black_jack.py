import random

class Card:
    def __init__(self, suit, face):
        self.suit = suit
        self.face = face

class Hand:
    def __init__(self, cards: list):
        self.hand = cards

    def calculate_hand(self):
        total = 0
        for card in self.hand:
            if (card.face == 'A'):
                if (total + 11 > 21):
                    total += 1
                else:
                    total += 11
            elif (card.face in ['J', 'Q', 'K']):
                total += 10
            else:
                total += card.face
        return total

    def show_hand(self):
        edge = "+-------+"
        length = len(self.hand)
        card_face = [
            [],
            [],
            []
        ]

        for card_num in range(length):
            card = self.hand[card_num]
            if card.face != 10:
                card_face[0].append(f"| {card.face}     |")
                card_face[1].append(f"|   {card.suit}   |")
                card_face[2].append(f"|     {card.face} |")
            else:
                card_face[0].append(f"|10     |")
                card_face[1].append(f"|   {card.suit}   |")
                card_face[2].append(f"|     10|")


        print(edge*length)
        for row in card_face:
            for item in row:
                print(item, end='')
            print()
        print(edge*length)

    def show_hand_dealer(self):
        if (self.hand[-1].face != 10):
            print("+-------+"*2)
            print(f"|-------|| {self.hand[-1].face}     |")
            print(f"|-------||   {self.hand[-1].suit}   |")
            print(f"|-------||     {self.hand[-1].face} |")
            print("+-------+"*2)
        else:
            print("+-------+"*2)
            print(f"|-------||10     |")
            print(f"|-------||   {self.hand[-1].suit}   |")
            print(f"|-------||     10|")
            print("+-------+"*2)

class BlackJack:
    def __init__(self, cash):
        self.status = True
        self.dealer_hand = []
        self.player_hand = []
        self.allowance = cash

    def check_loss(self):
        if (self.allowance <= 0):
            return True
        else: 
            return False
        
    def check_black_jack(self, bet):
        if (self.dealer_hand.calculate_hand() == 21 and self.player_hand.calculate_hand() == 21):
            self.dealer_hand.show_hand()
            self.player_hand.show_hand()
            print('push')
            return True
        elif (self.dealer_hand.calculate_hand() == 21 and self.player_hand.calculate_hand() != 21):
            self.dealer_hand.show_hand()
            self.player_hand.show_hand()
            print('dealer wins')
            self.allowance -= bet
            return True
        elif (self.dealer_hand.calculate_hand() != 21 and self.player_hand.calculate_hand() == 21):
            self.dealer_hand.show_hand()
            self.player_hand.show_hand()
            print('player wins')
            self.allowance += round(bet * 1.5)
            return True
        else:
            return False
    
    def check_player_bust(self):
        if (self.player_hand.calculate_hand() > 21):
            return True
        else:
            return False

    def check_round(self, bet):
        p_value = self.player_hand.calculate_hand()
        d_value = self.dealer_hand.calculate_hand()

        self.dealer_hand.show_hand()
        self.player_hand.show_hand()

        if (d_value > 21):
            print('player wins')
            self.allowance += bet
        elif (p_value == d_value):
            print('push')
        elif (p_value > d_value):
            print('player wins')
            self.allowance += bet
        else:
            print('dealer wins')
            self.allowance -= bet

    def award_dealer(self, bet):
        self.allowance -= bet
        
    def shuffle_deck(self):
        faces = ['A', 2, 3, 4, 5, 6, 7, 8, 9, 10, 'J', 'Q', 'K']
        suits = ['♠', '♦', '♥', '♣']

        deck = []

        for _ in range(6):
            for suit in suits:
                for face in faces:
                    deck.append(Card(suit, face))

        random.shuffle(deck)

        self.deck = deck
        
    def deal(self):
        dealer = []
        player = []

        while (len(dealer) < 2):
            if (len(self.deck) == 0):
                self.shuffle_deck()
                print('shuffling deck')
            else:
                dealer.append(self.deck.pop(0))
        while (len(player) < 2):
            if (len(self.deck) == 0):
                self.shuffle_deck()
                print('shuffling deck')
            else:
                player.append(self.deck.pop(0))

        self.dealer_hand = Hand(dealer)
        self.player_hand = Hand(player)

    def hit(self, player):
        if (len(self.deck) == 0):
            self.shuffle_deck()
            print('shuffling deck')
            player.hand.append(self.deck.pop(0))
        else:
            player.hand.append(self.deck.pop(0))

def main():

    # input player cash amount
    cash = int(input("Enter cash amount to play with: "))

    game = BlackJack(cash)
    game.shuffle_deck()

    # if player still has money play another round of Black jack
    while (game.status):
        try:
            player_bet = int(input("Bet: "))
        except ValueError:
            print('enter an number')
            continue

        # deal and show board
        game.deal()
        game.dealer_hand.show_hand_dealer()
        game.player_hand.show_hand()

        # check black jacks and handle loss | win
        round_status = game.check_black_jack(player_bet)

        # if black jack present start new round
        # else play on
        if (round_status):
            continue
        else:
            # player turn ->
            while (True):
                # get player input and validate
                player_input = input("hit or stand (h|s): ")
                if (player_input != 'h' and player_input != 's'):
                    player_input = input("enter h or s")
                else:

                    # player stands
                    # else player hits
                    if player_input == 's':
                        break
                    else:
                        game.hit(game.player_hand)

                        # check if player busted
                        if (game.check_player_bust()):
                            game.award_dealer(player_bet)
                            game.dealer_hand.show_hand()
                            game.player_hand.show_hand()
                            round_status = True
                            break
                        else:
                            game.dealer_hand.show_hand_dealer()
                            game.player_hand.show_hand()
            
            # player busted -> end round
            if (round_status):
                # print total cash
                print(f"${game.allowance}")

                # check if player has money for another round
                if (game.check_loss()):
                    print('end of game')
                    game.status = False
            else:
                # dealer turn ->
                while (game.dealer_hand.calculate_hand() < 16):
                    game.hit(game.dealer_hand)

                # check who wins
                game.check_round(player_bet)

                # print total cash
                print(f"${game.allowance}")

                # check if player has money for another round
                if (game.check_loss()):
                    print('end of game')
                    game.status = False

if __name__ == "__main__":
    main()
