objects = Hero.o Warrior.o Paladin.o Sorcerer.o

Hero.o : Hero.cpp
	g++ -std=c++11 -c Hero.cpp

Warrior.o : Warrior.cpp
	g++ -c Warrior.cpp

Paladin.o : Paladin.cpp
	g++ -c Paladin.cpp

Sorcerer.o : Sorcerer.cpp
	g++ -c Sorcerer.cpp

.PHONY: clean

clean:
	rm $(objects)
