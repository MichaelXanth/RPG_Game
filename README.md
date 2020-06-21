# RPG Game

This is an RPG (Role Playing Game).

## How to use

1. Use the Makefile to compile: `make`
2. Run with: `./rpg_game`

## Game Description

There are **heroes** and **monsters** who are in a constant battle. \
Their world is represented by a grid, consisted of territories which are dominated by either heroes or monsters. 

As heroes move accross the map they may be involved in battles with monsters. \
They can use **spells** and **objects** to defeat them. 

There is a fixed-point market area from where heroes can buy spells and items for fighting against monsters. 

They have a limited amount of coins to spend as the game begins which is being increased by gaining experience. 

A hero earns coins and experience when a monster is defeated. The amount of earnings depends on heroe's level. \
Their level is increased when enough experience is collected and then their skills are automatically upgraded.

<br>

#### General Info

- **Heroes**

  All heroes have:
    - Health Power (HP)
    - Magic Power  (MP)
    - Dexterity (_allows him to use portions more effectively_)
    - Strength &nbsp;(_increases the amount of damaged caused by a weapon_)
    - Agility &emsp;&nbsp;(_increases the chance of avoiding an attack_)
    - Money
    - Level
  <br>
  
  There are **3** different types of heroes:
  - Warriors \
    They have increased **strength** and **agility**
    
  - Sorcerer \
    They have increased **dexterity** and **agility**
    
  - Paladin \
    They have increased **strength** and **dexterity**
<br>
    
- **Monsters**

  All monsters have:
    - Damage Range
    - Defense Amount (reduces the amount of received damage)
    - Probability of avoiding an attack
    <br>
  
  There are **3** different types of monsters:
  - Dragon \
    They have increased **damage range**
    
  - Exoskeleton \
    They have increased **defense amount**
    
  - Spirit \
    They have increased **probability** of avoiding an attack
<br>
    
- **Items**

  All items have:
    - Name
    - Price
    - Minmum required level for a hero before he can use them
    <br>
  
  There are **3** different types of items:
  - Weapons \
    They can be used for attacking monsters. \
    They have a specific amount of damage they can cause. \
    They may require one or two hands for being used.
    
  - Armors \
    When used, they reduce the amount of received damage
    
  - Potion \
    When used, they increase a specific feature of the hero. \
    They are disposable, which means that they can't be reused.
<br>
    
- **Spells**

  They represnt a **magic attack** that can a hero excute. \
  The amount of damaged caused is affected by heroes **dexterity**.
  
  All spells have:
    - Name
    - Price
    - Minmum required level for a hero before he can use them
    - Damage Range
    - Magic Power required amount for use
    <br>
  
  There are **3** different types of spells:
  - IceSpells \
    Besides the damage it causes, it reduces the **damage range** of the opponent for some rounds
    
  - FireSpells \
    Besides the damage it causes, it reduces the **defense amount** of the opponent for some rounds
    
  - LightingSpells \
    Besides the damage it causes, it reduces the **probability** for the opponent to avoid an attack for some rounds
    
    
You are given 3 heroes one of each class (Warrior, Sorcerer, Paladin) and you have to battle monsters to level up and gain money. Each of the heroes have unique characteristic
and they begin level 1 with certain values.
Every step you take to an open space can trigger a battle, if the battle doesn't happen then you restore some of your lost HP an MP (depending on your hero level).
As your heroes level up, the monsters level up as well (The battles are more rewarding).
You can spend the money you gathered at the local store.
There are items and spells you can buy from there (More information on items and spells are given inside-game when you enter the store).
Heroes are indicated with a green mark, obstacles with a red mark and the store with a yellow mark.
