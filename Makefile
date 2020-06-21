objects = Main.o Names.o ./Battle/Battle.o ./Game/Game.o ./Grid/Grid.o ./Input_Validation/Input_Validation.o ./Items/Items.o ./Items/Weapon.o ./Items/Armor.o ./Items/Potion.o ./Keyboard/Keyboard.o ./Living/Living.o ./Living/Heroes/Hero.o ./Living/Heroes/Warrior.o ./Living/Heroes/Paladin.o ./Living/Heroes/Sorcerer.o ./Living/Monsters/Monster.o ./Living/Monsters/Dragon.o ./Living/Monsters/Spirit.o ./Living/Monsters/Exoskeleton.o ./Market/Market.o ./Spells/Spell.o ./Spells/IceSpell.o ./Spells/FireSpell.o ./Spells/LightingSpell.o

rpg_game : $(objects)
	g++ -g3 -Wall -o rpg_game $(objects)

Names.o : Names.cpp
	g++ -g3 -c Names.cpp

Main.o : Main.cpp
	g++ -g3 -c Main.cpp
	+$(MAKE) -C Battle
	+$(MAKE) -C Game
	+$(MAKE) -C Grid
	+$(MAKE) -C Input_Validation
	+$(MAKE) -C Items
	+$(MAKE) -C Keyboard
	+$(MAKE) -C Living
	+$(MAKE) -C Market
	+$(MAKE) -C Spells

.PHONY: clean

clean:
	rm rpg_game $(objects)

