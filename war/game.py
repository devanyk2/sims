# Kieran Devany
# Purpose: Simulate the game War, then study it
# yeehaw

# imports


import random
import simdb

# Creates a Deck of cards (1-13) of size 52


def deck():
    deck = []
    cards = [4,4,4,4,4,4,4,4,4,4,4,4,4]
    while len(deck) != 52:
        Card = random.randint(1,13)
        index = Card-1
        if cards[index] != 0:
            deck.append(Card)
            cards[index] = cards[index]-1
    # print(cards)
    
    return deck

# Distributes the deck as best as possible


def shuffle(deck, hands):
    
    shuffleDeck = {}
    players=[]

    for x in range(hands):
        player = "player" + str(x)
        shuffleDeck.update( {player : 0} )
        players.append(player)

    handsize=(52//hands)
   
    # print(handsize)

    for x in shuffleDeck:
        hand = []
        while (len(hand) != handsize):
            hand.append(deck.pop())
        shuffleDeck.update( {x : hand} )

    # Extra Cards leftover


    while (len(deck) >0):
        x = players.pop()
        hand=shuffleDeck[x]
        hand.append(deck.pop())
        shuffleDeck.update( {x : hand} )        
    
    
    # outputs 

    
    # print(shuffleDeck)
    # print(len(deck))
    return shuffleDeck



def dual(players, deck):

    pile={}
    temp=[]


    for P in players:
        hand = deck[P]
        if len(hand) < 4:
            pile.update( { P : hand } )
            hand=[]
        else:
            for x in range (4):
                temp.append( hand.pop())
            pile.update( { P : temp}  )
        deck[P] = hand
        temp=[]
   
    highCard = 0
    winner=[]
    for p, c in pile.items():
        if (len(c) > 0):
            if c[0] == highCard:
                winner.append(p)
            if c[0] > highCard:
                winner = [p]
                highcard = c[0]
    total=[]
    
    if len(winner) > 1:
        winner, total = dual(winner, deck)

    for p in pile.keys():
        total.append(pile[p])
    # print(total)
    return winner, total

def handStrength(gameid, deck):
    for p, v in deck.items():
        strength = Hstrength(v)
        numAce = Ace(v)
        simdb.hands(gameid['gameID'], p, strength, numAce)

def Hstrength(hand):
    avg = 0
    for x in hand:
        avg = avg + x
    return (avg/len(hand))

def Ace(hand):
    total = 0
    for x in hand:
        if x == 13:
            total = total + 1
    return total

def game(deck):
    
    players = deck.keys()
    count = 0
    duals = 0
    numPlayers = len(players)
    gameid = simdb.start(numPlayers) 
    # print(gameid['gameID'])
    handStrength(gameid, deck)

    while len(players) > 1:
        # print("round "+ str(count))
        count=count+1
        
        players = deck.keys()
        pile = {}

        for P in players:
            hand = deck[P]
            pile.update( {P : hand.pop()} )
            deck.update( { P: hand } )
    
        highCard = 0
        winner=[]

        for p, c in pile.items():
            if c == highCard:
                winner.append(p)
            if c > highCard:
                winner = [p]
                highCard = c

        # print(winner)
        # print(pile)

        temp=[]
        total = []

        if (len(winner) > 1):
            # print(winner)
            # call dual function here

            winner, temp = dual(winner, deck)
            duals = duals + 1
        
        for card in temp:
            for x in card:
                total.append(x)
        for p in pile.keys():
            total.append(pile[p])
        hand = deck[str(winner[0])]
        while len(total) != 0:
            hand.append(total.pop())
    
        deck.update( { str(winner[0]) : hand } )
        # print(deck)
    
        losers=[]

        for P in players:
            hand = deck[P]
            if len(hand) == 0:
                # print(str(P) + " Has Dropped Out")
                losers.append(P)
              

        for x in losers:
            del deck[x]


    WinRar = deck.keys()
    for x in WinRar:
        winner = x
    # print("The Winner is " + winner)

    simdb.end(winner, duals, count, gameid['gameID'])










deck1 = deck()
shuffledDeck = shuffle(deck1, 3)
game(shuffledDeck) 

