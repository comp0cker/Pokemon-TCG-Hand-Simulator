# Pokemon TCG Hand Simulator
A program that simulates hands and such for the Pokemon TCG!

## Formatting your Deck

Please adhere to the following guidelines to make sure the program doesn't crash and burn :p

* The target deck should be the same directory as the excecutable, and named deck.txt
* Start with the quantity of the card, followed by the name. Please don't use any spaces in card names, or else the program will crash and burn.
* Indicate basic Pokemon by putting an asterisk directly before the Pokemon name (example shown below)

### Example deck.txt

```
4 *heatmor
4 ether
4 max_elixir
4 fire_energy
```

## Current Functions

* Calculates the probability of starting with a card in your oppening hand (e.g. Talonflame STM)
