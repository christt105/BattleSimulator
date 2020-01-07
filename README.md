# Battle Simulator

A battle simulator created for Game Design 2 subject in Video Game Design and Development's degree in UPC-CITM (Terrassa, Catalunya). The program consists in a series of combat simulations that use our own gamerules and characters of the story mode we have made. The objective of the software is to balance the characters and to tell a captivating story in a very simple way.

## Features

- Simulator allows to do combats 1 vs 1, 1 vs AI and AI vs AI. In order to test a new movement it also has a mode to test that move in 10^9(number of parameters) of battles, giving the number of wins only doing that move. Moreover, it also has a mode to do hundred of battles to test the union of all stats of characters.

- On the other hand, the program allows you to create your own Character. The program reads all characters in the folder "Characters/". All you have to do is to create a new .txt and write the stats you want. here an example:

// Example==========================================================
// In the order you want
name: Brodinski
basic_attack: 5
b_precision: 90
special_attack: 10
sp_precision: 75
speed: 10
mana: 40
mana_cost: 15
health: 100
potions: 5
//=================================================================

- **Adventure mode** is a system to create a story. It is very simple to use. The adventure is written with nodes in a json file. Each node owns a type and information. All nodes have an id, which must be unique to every node, a type and a "to" container that will be the next node. There are four types:
	* "text": which displays text. The text must be in a .txt and set the route in "text" container.
	* "choice": which displays the options you set and will jump to that node. "choices" is an array of objects that contains a name to display and a "to" to jump to that id.
	* "battle": which starts a battle. Has three parameters: "player" as the route of .txt that the player will be, "enemy" which is the adversary and "song"  in case you want some music during the battle.
	* "end": which is the end node. The adventure will start in node with id "0" and will finish when jumps to a node "end".

## Contributors

This project was made for:
	* Christian Martínez De La Rosa: https://github.com/christt105
	* Marc Gálvez Llorens: https://github.com/optus23
	* Lluís Moreu Farran: https://github.com/youis11

[Github repository](https://github.com/christt105/BattleSimulator) and [latest release](https://github.com/christt105/BattleSimulator/releases/latest).