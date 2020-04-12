DROP TABLE IF EXISTS game;
DROP TABLE IF EXISTS hand;


CREATE TABLE game(
  gameID INTEGER PRIMARY KEY AUTOINCREMENT,
  players INTEGER NOT NULL,
  winner INTEGER,
  duals INTEGER,
  rounds INTEGER
 );

CREATE TABLE hand(
  handID INTEGER PRIMARY KEY AUTOINCREMENT,
  gameID INTEGER NOT NULL,
  player INTEGER NOT NULL,
  strength INTEGER NOT NULL,
  numAce INTEGER NOT NULL,
  FOREIGN KEY (gameID) REFERENCES game (gameID)
);
