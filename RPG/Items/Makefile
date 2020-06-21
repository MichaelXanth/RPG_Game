objects = Items.o Weapon.o Armor.o Potion.o

Items.o : Items.cpp
	g++ -g3 -c Items.cpp

Weapon.o : Weapon.cpp
	g++ -g3 -c Weapon.cpp

Armor.o : Armor.cpp
	g++ -g3 -c Armor.cpp

Potion.o : Potion.cpp
	g++ -g3 -c Potion.cpp

.PHONY: clean

clean:
	rm $(objects)
