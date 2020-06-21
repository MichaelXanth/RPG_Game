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
    - Dexterity (_allows him to use potions more effectively_)
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
    

## Gameplay

Heroes move all together. Every step you take to an open square, a battle can be triggered. \
If battle doesn't happen, you restore some of your lost HP an MP (depending on your hero level). \

As your heroes level up, monsters level up as well (The battles are more rewarding). \

You can spend the money you gathered at the local store. There are items and spells you can buy from there. \
(More information on items and spells are given inside the store).

Heroes are indicated with a green mark, obstacles with a red mark and the store with a yellow mark.

When heoes are moving in the map, they can enter in a mode called 'inventory' where they can change their **armor**, change the **weapon** that each hero holds and they also can drink **potions**.


## Special Characteristics

The game is terminal based and it's implemented with an advanced integration and graphics system.

Unbuffered input is implemented so that a better gameplay experience is ensured, removing the need of hitting enter at every needed action.

When heroes are in the store, they can see all available items and spells for sale. They can expand the information tab for all of them as well.

When choosing to buy something, all objects are filtered so that only these that current hero is capable of purchasing are being displayed.

Error messages are also displayed at every wrong or not permitted action for informing player what went wrong.

The graphics system is implemented to work as smoother as possible. It automatically refreshes the screen and resotres the gameplay grid, so that no crushing occurs when hitting wrong buttons and doing not permitted actions.

## Screenshots

| Grid |
|------|
| ![alt_text](https://github.com/MichaelXanth/RPG_Game/blob/master/Screenshots/grid.png) |


| Market (***Info Disabled***) | Market (***Info Enabled***)  |
|--|--|
| ![alt_text](https://github.com/MichaelXanth/RPG_Game/blob/master/Screenshots/market_no_info.png) | ![alt_text](https://github.com/MichaelXanth/RPG_Game/blob/master/Screenshots/market_info.png) |


| Filtered Market (***Info Disabled***) | Filtered Market (***Info Enabled***)  |
|--|--|
| ![alt_text](https://github.com/MichaelXanth/RPG_Game/blob/master/Screenshots/market_filtered_no_info.png) | ![alt_text](https://github.com/MichaelXanth/RPG_Game/blob/master/Screenshots/market_filtered_info.png) |

| Battle Mode (***Round 1***) | Filtered Market (***Round 6 - 1***<sup><b>st</b></sup> ***Monster Defeated***)  |
|--|--|
| ![alt_text](https://github.com/MichaelXanth/RPG_Game/blob/master/Screenshots/battle_mode_round1.png) | ![alt_text](https://github.com/MichaelXanth/RPG_Game/blob/master/Screenshots/battle_mode_round6_defeated_monster.png) |


## Key Bindings

Action                      | Key
----------------------------|----
Move Up                     | w
Move Down                   | s
Move Left                   | a
Move Right                  | d
Navigate heroes, items, ... | 1,2,3
Enter Inventory             | i
Quit Game                   | q
