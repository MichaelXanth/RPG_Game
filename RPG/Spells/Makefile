objects = Spell.o IceSpell.o FireSpell.o Potion.o

Spell.o : Spell.cpp
	g++ -g3 -c Spell.cpp

IceSpell.o : IceSpell.cpp
	g++ -g3 -c IceSpell.cpp

FireSpell.o : FireSpell.cpp
	g++ -g3 -c FireSpell.cpp

LightingSpell.o : LightingSpell.cpp
	g++ -g3 -c LightingSpell.cpp

.PHONY: clean

clean:
	rm $(objects)
