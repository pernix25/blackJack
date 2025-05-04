import random as r

class Hand():
    def __init__(self, dealer:bool) -> None:
        self.values = []
        self.suits = []
        self.is_dealer = dealer

    def add_card(self, value:int, suit:str) -> None:
        self.values.append(value)
        self.suits.append(suit)

    def calc_value(self) -> int:
        total = 0
        num_aces = 0

        # loop over values and add basic cards, don't handle ace cards
        for value in self.values:
            if value == 1:
                num_aces += 1
            elif value >= 10:
                total += 10
            else:
                total += value
        
        # add the value of the aces
        # if there are more than 1 ace -> add 1 to the total per ace card
        if num_aces > 1:
            total += (num_aces - 1)

        # check if ace is eaither an 11 or 1
        if num_aces:
            if total + 11 > 21:
                total += 1
            else:
                total += 11

        return total
    
    def set_dealer(self, new_delaer:bool) -> None:
        self.is_dealer = new_delaer

    def print_hand(self) -> None:
        if self.is_dealer:
            hand = "+-------++-------+\n"
            card = self.values[-1]
            suit = self.suits[-1]
            if card == 1:
                hand += "|-------|| A     |\n"
                hand += f"|-------||   {suit}   |\n"
                hand += "|-------||     A |\n"
            elif card == 10:
                hand += "|-------||10     |\n"
                hand += f"|-------||   {suit}   |\n"
                hand += "|-------||     10|\n"
            elif card == 11:
                hand += "|-------|| J     |\n"
                hand += f"|-------||   {suit}   |\n"
                hand += "|-------||     J |\n"
            elif card == 12:
                hand += "|-------|| Q     |\n"
                hand += f"|-------||   {suit}   |\n"
                hand += "|-------||     Q |\n"
            elif card == 13:
                hand += "|-------|| K     |\n"
                hand += f"|-------||   {suit}   |\n"
                hand += "|-------||     K |\n"
            else:
                hand += f"|-------|| {card}     |\n"
                hand += f"|-------||   {suit}   |\n"
                hand += f"|-------||     {card} |\n"
            hand += "+-------++-------+\n"
            print(hand)
        else:
            hand_length = len(self.values)
            hand = ("+-------+" * hand_length) + '\n'
            hand_bottom = ""
            for i in range(hand_length):
                card = self.values[i]
                if card == 1:
                    hand += "| A     |"
                    hand_bottom += "|     A |"
                elif card == 10:
                    hand += "|10     |"
                    hand_bottom += "|     10|"
                elif card == 11:
                    hand += "| J     |"
                    hand_bottom += "|     J |"
                elif card == 12:
                    hand += "| Q     |"
                    hand_bottom += "|     Q |"
                elif card == 13:
                    hand += "| K     |"
                    hand_bottom += "|     K |"
                else:
                    hand += f"| {card}     |"
                    hand_bottom += f"|     {card} |"

            hand += '\n'
            hand_bottom = hand_bottom + '\n' + ("+-------+" * hand_length) + '\n'
            
            for i in range(hand_length):
                suit = self.suits[i]
                hand += f"|   {suit}   |"

            hand += '\n'
            hand = hand + hand_bottom
            print(hand)

class Deck():
    def __init__(self) -> None:
        self.deck = self.create_deck()

    def create_deck(self, num_decks=6) -> list[tuple[int,str]]:
        values = [x for x in range(1,14)]
        suits = ['♠', '♦', '♥', '♣']

        deck = []

        for _ in range(num_decks):
            for suit in suits:
                for value in values:
                    deck.append((value, suit))

        r.shuffle(deck)
        return deck

    def num_cards_in_deck(self) -> int:
        return len(self.deck)
    
class Black_jack():
    def __init__(self) -> None:
        self.player_turn = True
        self.game_over = False
        self.balance = 0
    
    def get_balance(self) -> float:
        return self.balance
    