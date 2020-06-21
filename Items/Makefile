objects = Items.o Weapon.o Armor.o Potion.o

Items.o : Items.cpp
	g++ -c Items.cpp

Weapon.o : Weapon.cpp
	g++ -c Weapon.cpp

Armor.o : Armor.cpp
	g++ -c Armor.cpp

Potion.o : Potion.cpp
	g++ -c Potion.cpp

.PHONY: clean

clean:
	rm $(objects)
