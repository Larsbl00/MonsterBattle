# Monster Battle

## Launching
When launching the program you can the `-h` or `--help` flags to see all launch parameters.
When launching the game, make sure you add the `-t` flag to select a trainer file for the player,
and use `-o` to select an opponnent.

The following table will explain all parameters:

| Short | Long | Description |
| :--- | :-- | :--------- |
| -h    | --help | Shows all flags and waht they do |
| -t    | --trainer | Selects a trainerfile that the main player uses |
| -o    | --opponent | Selects a trainer file for the oppononent to use, said opponent should be controlled by another person | 

## Assets
The `assets` directory contains all files for the game, in all of these files you can use `#` to create lines of comments.
All default files have an explanation on how you should format everything. This part of the ReadMe will also tell you how to alter the information.

### Trainers
A trainer has a collection of different monsters used to attack the opponent, which is also a trainer. 
When launching the program you can use different parameters to create a new trainer, 
one of the parameters is a 'Trainer-file' the file has a very simple construct.

Per line in said file you need to use the following format:
```
{NAME, NICK_NAME}

*NAME: The name of the monster
*NICK_NAME: The name you want to display for your monster
```

You can select a total of `6` monsters, you can also decide to choose fewer.

### Moves
You can easily add new moves to the game, we'll go over how to use those moves later.
To add a new move open `assets/moves.txt` and add a new line for your move; said move should be formatted as follows:
```
(NAME,TYPE_AS_INTEGER,DAMAGE,PRECISION)


*NAME:  The name of the move, e.g. 'Yeet'

*TYPE_AS_INTEGER: The typing of the move, i.e. if I want it to be a fire move I'll open `include/Type.h` and check what number fire is, in this case it is 1

*DAMAGE: The damage of the move, with ~50 being equal to normal damage

*PRECISION: A NORMALIZED probability of the move hitting, e.g 0.5 (which is a mediocre accuracy)
```
Do remeber the name you assign to a move, as you'll need this later when linking the move.

### Models
You can create a custom Model for a monster by creating a file containing an ASCII model for a monster and then linking it in `assets/monsters.txt`

### Monsters
Like attack moves, you can easily add more Monsters to the game.
To add a new monster open the file `assets/monsters.txt` and add a line for your new monster.
However do make sure that you add a new monster in the format used in the file itself, the format is as follows:
```
(NICK_NAME; NAME; TYPES; STATS; MOVES; MODEL_FILE)


*NICK_NAME: The nickname of the Monster, normally it is equal to the Monster's name

*NAME: The name of the monster, e.g. SmallBird

*Types: The types of the monster, like with the moves the types should be written down as integers. The Types should be written as follows [TYPE1,TYPE2], if I'd want a Fire type monster it is written as [1,0]

*Stats: The stats of the monster, the stats are formatted as follows:
  {MAX_HP, HP, DEF, ATTACK, PRECISION, AVOIDANCE, SPEED}
  *note: PRECISION and AVOIDANCE should be normalized values

*Moves: This is a list of all moves that the monsater has, to add moves use the following format:
  [MV1,MV2,MV3,MV4]
  Each monster can have a maximum of 4 moves, if you want to use you can write the name down on any of the available slots, do make sure that they are present in "assets/moves.txt"
  
*ModelFile: The path to the file containing an ASCII-model, refer to the SmallBird example in the monster file
```
