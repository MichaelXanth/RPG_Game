objects = Monster.o Dragon.o Spirit.o Exoskeleton.o

Monster.o : Monster.cpp
	g++ -g3 -c Monster.cpp


Dragon.o : Dragon.cpp
	g++ -g3 -c Dragon.cpp


Spirit.o : Spirit.cpp
	g++ -g3 -c Spirit.cpp

Exoskeleton.o : Exoskeleton.cpp
	g++ -g3 -c Exoskeleton.cpp

.PHONY: clean

clean:
	rm $(objects)
