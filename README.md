# Battle Simulator

A battle simulator made in Game Design 2 subject in Bachelor's degree in UPC-CITM (Terrassa). The program consists in battle simulators with our gamerules and characters of the history we made.

## Features

- Simulator allows to do combats 1 vs 1, 1 vs AI and AI vs AI. In order to test a new movement it also has a mode to test that move in hundred of battles, giving the number of wins only doing that move. Moreover, it also has a mode to do hundred of battles to test the union of all stats of characters.

- On the other hand, the program allows you to create your own Character. The program read all characters in the folder "Characters/". All you have to do is to create a new .txt and write the stats you want. here an example:

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

- **Adventure mode** is a mode to create a history. It is very simple to create. The adventure is made with nodes in a json file. Each node has a type and information. All nodes have a id and must be single to every node, a type and "to" container that will be the next node. There are four types:
	* "text": will display text. The text must be in a .txt and set the route in "text" container.
	* "choice": will display the options you set and will jump to that node. "choices" is an array of objects that contains a name to display and a "to" to jump to that id.
	* "battle": will start a battle. Has three parameters. "player" route of .txt that the player will be, "enemy" the contrincant and "song" if you want music in the battle.
	* "end": is the end node. The adventure will start in node with id 0 and will finish when jump to a node "end".

## Contributors

This project was made for:
	* Christian Martínez De La Rosa: https://github.com/christt105
	* Marc Gálvez Llorens: https://github.com/optus23
	* Lluís Moreu Farran: https://github.com/youis11

[Github repository](https://github.com/christt105/BattleSimulator) and [latest release](https://github.com/christt105/BattleSimulator/releases/latest).