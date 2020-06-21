objects = Hero.o Warrior.o Paladin.o Sorcerer.o

Hero.o : Hero.cpp
	g++ -g3 -std=c++11 -c Hero.cpp

Warrior.o : Warrior.cpp
	g++ -g3 -c Warrior.cpp

Paladin.o : Paladin.cpp
	g++ -g3 -c Paladin.cpp

Sorcerer.o : Sorcerer.cpp
	g++ -g3 -c Sorcerer.cpp

.PHONY: clean

clean:
	rm $(objects)
