# Driver that will run the game.py file and then manipulate data

import game
import click


@click.command()
@click.argument("iterations")
@click.argument("players")
def runProg(iterations, players):
    
    if (iterations <=0) or (players <=0):
        print("invalid arguments") 


    click.echo("running game for " +str(iterations) + "times", nl=False)
    count = 0
    
    while iterations > 0:
        print("game" + str(count))
        count = count + 1

        deck = game.deck()
        shuffledDeck = game.shuffle(deck, players)
        game(shuffledDeck)
        
        iterations = iterations - 1 
