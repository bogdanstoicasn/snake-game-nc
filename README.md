#### Copyright 2023-2024 Stoica Mihai-Bogdan 315CA (bogdanstoicasn@yahoo.com)
#### GNU GENERAL PUBLIC LICENSE 
#### Version 3, 29 June 2007

# Snake Game

This is a simple implementation of the classic Snake game in C using the ncurses
library for the user interface. The game consists of a snake that the player
controls with arrow keys or 'w', 'a', 's', 'd' keys to eat food and grow while
avoiding collisions with the wall or itself.

## Prerequisites
Before running the game, make sure you have the following prerequisites:

> **Linux/Unix Environment**: This game is designed to run on Linux/Unix systems
due to its dependency on the ncurses library and unistd.h.

> **GCC Compiler**: You need the GCC compiler to build the game. You can install
it on Debian/Ubuntu with the following command:
	sudo apt-get install build-essential
	
> **Ncurses Library**: You need the ncurses library for the user interface.
Install it on Debian/Ubuntu with:
	sudo apt-get install libncurses-dev

## How to Build

Clone this repository or download the source code.
Navigate to the project directory.
Open a terminal and run the following command to compile the game:
	make

This will create an executable file named **snake_game**. You can run the game with:
	./snake_game


## How to Play

Use '**w**', '**a**', '**s**', '**d**' keys to control the snake's direction.

The snake will automatically move in the last selected direction.

Your goal is to eat the food ('**i**') that appears on the screen.
Each time you eat food, your score increases.

Avoid collisions with the wall and yourself.

You can press '**q**' at any time to quit the current game and return to main menu.

## Features

User-friendly interface using the ncurses library.

Randomly generated food for a dynamic gameplay experience.

Keeps track of the player's score.

Displays a "Game Over" screen when the game ends, showing the final score.

Saves and displays the best score.

## Acknowledgments

This project is a basic implementation of the Snake game in C and was created for
educational purposes. It serves as a demonstration of using the ncurses library for
console-based games.

->[ncurses](https://doc.bccnsoft.com/docs/php-docs-7-en/ref.ncurses.html)

Enjoy playing Snake!
