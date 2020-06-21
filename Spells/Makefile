objects = Spell.o IceSpell.o FireSpell.o Potion.o

Spell.o : Spell.cpp
	g++ -c Spell.cpp

IceSpell.o : IceSpell.cpp
	g++ -c IceSpell.cpp

FireSpell.o : FireSpell.cpp
	g++ -c FireSpell.cpp

LightingSpell.o : LightingSpell.cpp
	g++ -c LightingSpell.cpp

.PHONY: clean

clean:
	rm $(objects)
