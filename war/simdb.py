import sqlite3


# connects to db
def get_db():
    conn = None
    try:
        conn = sqlite3.connect('war.db',  detect_types=sqlite3.PARSE_DECLTYPES)
        conn.row_factory = sqlite3.Row
    except Error as e:
        print(e)
    return conn


def init_db():
    conn = get_db()
    f = open("schema.sql", "r")
    cur = conn.cursor()
    cur.executescript(f.read())


def start(players):
    db = get_db()
    db.execute(
    'INSERT INTO game(players) VALUES(?)',
    (players,))
    db.commit()

    game = db.execute(
            'SELECT gameID FROM game ORDER BY gameID DESC').fetchone()

    return game
    

def end(winner, duals, rounds, gameID):
    db = get_db()
    db.execute(
    'UPDATE game SET winner = ?, duals = ?, rounds = ? WHERE gameID = ?', (winner, duals, rounds, gameID))
    db.commit()


def hands(handID, player, strength, numAce):
    db = get_db()

    db.execute(
    'INSERT INTO hand(gameID, player, strength, numAce) VALUES(?,?,?,?)', 
    (handID, player, strength, numAce))
    db.commit()


