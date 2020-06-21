Living.o : Living.cpp
	g++ -c Living.cpp

	+$(MAKE) -C Heroes
	+$(MAKE) -C Monsters

.PHONY: clean

clean:
	rm Living.o
	+$(MAKE) -C Heroes clean
	+$(MAKE) -C Monsters clean