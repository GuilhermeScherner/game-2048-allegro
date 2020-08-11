# game-2048-allegro

Game made from a work by PROGRAMMING LABORATORY 1, the game is a clone of the mobile game Drop the Number.

## GamePlay
Control of the game can be done using the arrow keys, moving the falling block (right and left), the down arrow causes the block to fall immediately. With the mouse you can select the target column of the block.

With a ranking system, where the score that is increased according to the junction of the blocks, and the timer are the main factors.

The game has pause and restart options.

## Difficulties
At the beginning I made the program in a single file, however when the complexity was increased I had to separate them in separate files, leaving the application modular, so much so that the modules work independently.


## StartGame
First you need allegro 5 installed on your computer.

```properties
gcc -Wall main.c -o main -lm `pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5`
```
next 

```properties
./main
```

