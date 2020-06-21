/* File: Names.cpp */

#include "Names.hpp"

Names::Names()
{
    names.push_back("Aasterinian");                   names.push_back("Gadhelyn");                 names.push_back("Panzuriel");
    names.push_back("Abbathor");                      names.push_back("Gaerdal");                  names.push_back("Pelor");
    names.push_back("Aerdrie");                       names.push_back("Gaknulak");                 names.push_back("Peryroyl");
    names.push_back("Annam");                         names.push_back("Garl");                     names.push_back("Rallathil");
    names.push_back("Argrim");                        names.push_back("Gendwar");                  names.push_back("Raxivort");
    names.push_back("Arvoreen");                      names.push_back("Glittergold");              names.push_back("Rillifane");
    names.push_back("Baervan");                       names.push_back("Grankhul");                 names.push_back("Roykyn");
    names.push_back("Bagrivyek");                     names.push_back("Great");                    names.push_back("Sashelas");
    names.push_back("Bahamut");                       names.push_back("Grolantor");                names.push_back("Segojan");
    names.push_back("Bahgtru");                       names.push_back("Gruumsh");                  names.push_back("Sehanine");
    names.push_back("Baravar");                       names.push_back("Halani");                   names.push_back("Sekolah");
    names.push_back("Berronar");                      names.push_back("Heironeous");               names.push_back("Semuanya");
    names.push_back("Blibdoolpoolp");                 names.push_back("Hiatea");                   names.push_back("Shargaas");
    names.push_back("Brandobaris");                   names.push_back("Hruggek");                  names.push_back("Sheela");
    names.push_back("Brightmantle");                  names.push_back("Iallanis");                 names.push_back("Shekinester");
    names.push_back("Callarduran");                   names.push_back("Ilesere");                  names.push_back("Silverbeard");
    names.push_back("Celanil");                       names.push_back("Ilneval");                  names.push_back("Sixin");
    names.push_back("Charmalaine");                   names.push_back("Ilsensine");                names.push_back("Skerrit");
    names.push_back("Chronepsis");                    names.push_back("Ironhand");                 names.push_back("Skoraeus");
    names.push_back("Clangeddin");                    names.push_back("Jubilex");                  names.push_back("Smoothhands");
    names.push_back("Cloakshadow");                   names.push_back("Karontor");                 names.push_back("Solonor");
    names.push_back("Corellon");                      names.push_back("Khurgorbaeyag");            names.push_back("Squerrik");
    names.push_back("Cuthbert");                      names.push_back("Kiaransalee");              names.push_back("Steelskin");
    names.push_back("Cyrrollalee");                   names.push_back("Kurtulmak");                names.push_back("Stonebones");
    names.push_back("Deep");                          names.push_back("Labelas");                  names.push_back("Stronmaus");
    names.push_back("Diirinka");                      names.push_back("Laduguer");                 names.push_back("Surtr");
    names.push_back("Doresain");                      names.push_back("Larethian");                names.push_back("Thelandira");
    names.push_back("Duathal");                       names.push_back("Loagzed");                  names.push_back("Thrym");
    names.push_back("Dugmaren");                      names.push_back("Lolth");                    names.push_back("Tiamat");
    names.push_back("Dumathoin");                     names.push_back("Luthic");                   names.push_back("Truesilver");
    names.push_back("Eadro");                         names.push_back("Maglubiyet");               names.push_back("Urdlen");
    names.push_back("Earthcaller");                   names.push_back("Memnor");                   names.push_back("Urogalan");
    names.push_back("Ehlonna");                       names.push_back("Merrshaulk");               names.push_back("Vaprak");
    names.push_back("Enoreth");                       names.push_back("Mestarine");                names.push_back("Vergadain");
    names.push_back("Erevan");                        names.push_back("Moonbow");                  names.push_back("Vhaeraun");
    names.push_back("Faenya");                        names.push_back("Moradin");                  names.push_back("Wildwanderer");
    names.push_back("Falazure");                      names.push_back("Muamman");                  names.push_back("Ye'Cind");
    names.push_back("Fenmarel");                      names.push_back("Nomog-Geaya");              names.push_back("Yeenoghu");
    names.push_back("Fharlanghn");                    names.push_back("Olidammara");               names.push_back("Yondalla");
    names.push_back("Flandal");                       names.push_back("Orcus");                    names.push_back("Yurtrus");


    weaponsNames.push_back("Abraxas");                weaponsNames.push_back("Herding Staff");     weaponsNames.push_back("Rod of Lightning");
    weaponsNames.push_back("Arc Arcana");             weaponsNames.push_back("Hunter's Sword");    weaponsNames.push_back("Rod of Roses");
    weaponsNames.push_back("Astral Rod");             weaponsNames.push_back("Ice Brand");         weaponsNames.push_back("Rod of Silence");
    weaponsNames.push_back("Baroque Sword");          weaponsNames.push_back("Judgment");          weaponsNames.push_back("Rod of Striking");
    weaponsNames.push_back("Belladonna Wand");        weaponsNames.push_back("Laevatein");         weaponsNames.push_back("Rod of Water");
    weaponsNames.push_back("Bizarre Staff");          weaponsNames.push_back("Lightning Steel");   weaponsNames.push_back("Rod of Wisdom");
    weaponsNames.push_back("Break Rod");              weaponsNames.push_back("Lullaby Rod");       weaponsNames.push_back("Rune Rod");
    weaponsNames.push_back("Calcite Staff");          weaponsNames.push_back("Lullaby Steel");     weaponsNames.push_back("Rune Steel");
    weaponsNames.push_back("Chaos Rod");              weaponsNames.push_back("Mage's Staff");      weaponsNames.push_back("Seraphim Rod");
    weaponsNames.push_back("Conductor");              weaponsNames.push_back("Magistral Rod");     weaponsNames.push_back("Shining Staff");
    weaponsNames.push_back("Darkness Staff");         weaponsNames.push_back("Malleable Staff");   weaponsNames.push_back("Slasher");
    weaponsNames.push_back("Defender");               weaponsNames.push_back("Mirage Rod");        weaponsNames.push_back("Soldier's Saber");
    weaponsNames.push_back("Dual Rod");               weaponsNames.push_back("Monk Staff");        weaponsNames.push_back("Sorcery Rod");
    weaponsNames.push_back("Ductile Rod");            weaponsNames.push_back("Muted Steel");       weaponsNames.push_back("Sorcery Sword");
    weaponsNames.push_back("El Dorado");              weaponsNames.push_back("Nemesis Rod");       weaponsNames.push_back("Spiked Rod");
    weaponsNames.push_back("Enchanted Rod");          weaponsNames.push_back("Nimbus Rod");        weaponsNames.push_back("Staff of Thorns");
    weaponsNames.push_back("Enchanted Sword");        weaponsNames.push_back("Nirvana");           weaponsNames.push_back("Tri-Rod");
    weaponsNames.push_back("Entangling Rod");         weaponsNames.push_back("Ominous Rod");       weaponsNames.push_back("Twilight Steel");
    weaponsNames.push_back("Faerie Staff");           weaponsNames.push_back("Poison Steel");      weaponsNames.push_back("Wicked Wand");
    weaponsNames.push_back("Fencing Saber");          weaponsNames.push_back("Power Staff");       weaponsNames.push_back("Wind Rod");
    weaponsNames.push_back("Flametongue");            weaponsNames.push_back("Prism Rod");         weaponsNames.push_back("Wing Wand");
    weaponsNames.push_back("Force Rod");              weaponsNames.push_back("Punisher");          weaponsNames.push_back("Wonder Wand");
    weaponsNames.push_back("Force Saber");            weaponsNames.push_back("Reticent Staff");
    weaponsNames.push_back("Full Metal Rod");         weaponsNames.push_back("Rod of Darkness");
    weaponsNames.push_back("Healing Rod");            weaponsNames.push_back("Rod of Fire");
    weaponsNames.push_back("Heavenly Axis");          weaponsNames.push_back("Rod of Ice");


    armorsNames.push_back("Adept's Shield");          armorsNames.push_back("Light Shield");       armorsNames.push_back("Revive Shield");
    armorsNames.push_back("Aegis Shield");            armorsNames.push_back("Lucid Shield");       armorsNames.push_back("Ruby Shield");
    armorsNames.push_back("Alert Shield");            armorsNames.push_back("Mage's Shield");      armorsNames.push_back("Sapphire Shield");
    armorsNames.push_back("Assault Shield");          armorsNames.push_back("Magic Shield");       armorsNames.push_back("Seeker's Shield");
    armorsNames.push_back("Barrier Shield");          armorsNames.push_back("Magister Shield");    armorsNames.push_back("Serene Shield");
    armorsNames.push_back("Blessed Shield");          armorsNames.push_back("Marching Shield");    armorsNames.push_back("Serum Shield");
    armorsNames.push_back("Blue Shield");             armorsNames.push_back("Medical Shield");     armorsNames.push_back("Shaman Shield");
    armorsNames.push_back("Bright Shield");           armorsNames.push_back("Metal Shield");       armorsNames.push_back("Shell Shield");
    armorsNames.push_back("Cerulean Shield");         armorsNames.push_back("Moon Shield");        armorsNames.push_back("Shield of Hope");
    armorsNames.push_back("Collector's Shield");      armorsNames.push_back("Mythril Shield");     armorsNames.push_back("Shining Shield");
    armorsNames.push_back("Crimson Shield");          armorsNames.push_back("NulBlaze Shield");    armorsNames.push_back("Silver Shield");
    armorsNames.push_back("Crystal Shield");          armorsNames.push_back("NulFrost Shield");    armorsNames.push_back("Snow Shield");
    armorsNames.push_back("Curative Shield");         armorsNames.push_back("NulTide Shield");     armorsNames.push_back("Soft Shield");
    armorsNames.push_back("Defending Shield");        armorsNames.push_back("Ochre Shield");       armorsNames.push_back("Soldier's Shield");
    armorsNames.push_back("Diamond Shield");          armorsNames.push_back("Onyx Shield");        armorsNames.push_back("Sorcery Shield");
    armorsNames.push_back("Dynasty Shield");          armorsNames.push_back("Paladin Shield");     armorsNames.push_back("Soul Shield");
    armorsNames.push_back("Echo Shield");             armorsNames.push_back("Peaceful Shield");    armorsNames.push_back("Spiritual Shield");
    armorsNames.push_back("Elemental Shield");        armorsNames.push_back("Pearl Shield");       armorsNames.push_back("Star Shield");
    armorsNames.push_back("Emblem");                  armorsNames.push_back("Phantom Shield");     armorsNames.push_back("Tetra Shield");
    armorsNames.push_back("Emerald Shield");          armorsNames.push_back("Phoenix Shield");     armorsNames.push_back("Treasure Shield");
    armorsNames.push_back("Endless Road");            armorsNames.push_back("Platinum Shield");    armorsNames.push_back("Warrior's Shield");
    armorsNames.push_back("Faerie Shield");           armorsNames.push_back("Protect Shield");     armorsNames.push_back("White Shield");
    armorsNames.push_back("Genji Shield");            armorsNames.push_back("Rainbow Shield");     armorsNames.push_back("Wizard Shield");
    armorsNames.push_back("Glorious Shield");         armorsNames.push_back("Recovery Shield");    armorsNames.push_back("Yellow Shield");
    armorsNames.push_back("Gold Shield");             armorsNames.push_back("Red Shield");
    armorsNames.push_back("Golem Shield");            armorsNames.push_back("Reflect Shield");
    armorsNames.push_back("Haste Shield");            armorsNames.push_back("Regen Shield");
    armorsNames.push_back("Knight's Shield");         armorsNames.push_back("Rescue Shield");


    potionsNames.push_back("Ability Distiller");      potionsNames.push_back("Light Curtain");     potionsNames.push_back("Silver Hourglass");
    potionsNames.push_back("Al Bhed Potion");         potionsNames.push_back("Lunar Curtain");     potionsNames.push_back("Sleeping Powder");
    potionsNames.push_back("Amulet");                 potionsNames.push_back("Mana Distiller");    potionsNames.push_back("Smoke Bomb");
    potionsNames.push_back("Antidote");               potionsNames.push_back("Mana Spring");       potionsNames.push_back("Soft");
    potionsNames.push_back("Blessed Gem");            potionsNames.push_back("Mana Tablet");       potionsNames.push_back("Soul Spring");
    potionsNames.push_back("Candle of Life");         potionsNames.push_back("Mana Tonic");        potionsNames.push_back("Speed Distiller");
    potionsNames.push_back("Dark Matter");            potionsNames.push_back("Map");               potionsNames.push_back("Stamina Spring");
    potionsNames.push_back("Designer Wallet");        potionsNames.push_back("Mega Phoenix");      potionsNames.push_back("Stamina Tablet");
    potionsNames.push_back("Door to Tomorrow");       potionsNames.push_back("Megalixir");         potionsNames.push_back("Stamina Tonic");
    potionsNames.push_back("Dream Powder");           potionsNames.push_back("Gambler's Spirit");  potionsNames.push_back("Star Curtain");
    potionsNames.push_back("Echo Screen");            potionsNames.push_back("Mega-Potion");       potionsNames.push_back("Supreme Gem");
    potionsNames.push_back("Elixir");                 potionsNames.push_back("Musk");              potionsNames.push_back("Tetra Elemental");
    potionsNames.push_back("Ether");                  potionsNames.push_back("Pendulum");          potionsNames.push_back("Three Stars");
    potionsNames.push_back("Eye Drops");              potionsNames.push_back("Petrify Grenade");   potionsNames.push_back("Turbo Ether");
    potionsNames.push_back("Farplane Shadow");        potionsNames.push_back("Phoenix Down");      potionsNames.push_back("Twin Stars");
    potionsNames.push_back("Farplane Wind");          potionsNames.push_back("Poison Fang");       potionsNames.push_back("Underdog's Secret");
    potionsNames.push_back("Frag Grenade");           potionsNames.push_back("Power Distiller");   potionsNames.push_back("Wings to Discovery");
    potionsNames.push_back("Gold Hourglass");         potionsNames.push_back("Purifying Salt");    potionsNames.push_back("Winning Formula");
    potionsNames.push_back("Healing Spring");         potionsNames.push_back("Remedy");            potionsNames.push_back("X-Potion");
    potionsNames.push_back("Healing Water");          potionsNames.push_back("Shadow Gem");
    potionsNames.push_back("Hi-Potion");              potionsNames.push_back("Shining Gem");
    potionsNames.push_back("Holy Water");             potionsNames.push_back("Shining Thorn");
    potionsNames.push_back("Hypello Potion");         potionsNames.push_back("Silence Grenade");


    fireSpellsNames.push_back("Blazing Arrows");      iceSpellsNames.push_back("Avalanche");       lightingSpellsNames.push_back("Angel's Mercy");
    fireSpellsNames.push_back("Blazing Katana");      iceSpellsNames.push_back("Chill");           lightingSpellsNames.push_back("Arrow of Purity");
    fireSpellsNames.push_back("Bolt Strike");         iceSpellsNames.push_back("Cleanse");         lightingSpellsNames.push_back("Bolt");
    fireSpellsNames.push_back("Breath of Suitengu");  iceSpellsNames.push_back("Douse");           lightingSpellsNames.push_back("Channel Energy");
    fireSpellsNames.push_back("Decay");               iceSpellsNames.push_back("Endless Depth");   lightingSpellsNames.push_back("Confuse");
    fireSpellsNames.push_back("Dragon Fire");         iceSpellsNames.push_back("Flood");           lightingSpellsNames.push_back("Cyclone");
    fireSpellsNames.push_back("Explosion");           iceSpellsNames.push_back("Freeze Wave");     lightingSpellsNames.push_back("Daze");
    fireSpellsNames.push_back("Fester");              iceSpellsNames.push_back("Freeze");          lightingSpellsNames.push_back("Deluge");
    fireSpellsNames.push_back("Fire Wings");          iceSpellsNames.push_back("Frostbite");       lightingSpellsNames.push_back("Flash");
    fireSpellsNames.push_back("Fireball");            iceSpellsNames.push_back("Scour");           lightingSpellsNames.push_back("Gale");
    fireSpellsNames.push_back("Fury of Osano-Wo");    iceSpellsNames.push_back("Sinkhole");        lightingSpellsNames.push_back("Gust");
    fireSpellsNames.push_back("Gaijin Flames");       iceSpellsNames.push_back("Siphon");          lightingSpellsNames.push_back("Heaven's Sword");
    fireSpellsNames.push_back("Gloom");               iceSpellsNames.push_back("Sleep");           lightingSpellsNames.push_back("Light");
    fireSpellsNames.push_back("Hungry Blade");        iceSpellsNames.push_back("Staff of Ice");    lightingSpellsNames.push_back("Plasma");
    fireSpellsNames.push_back("Landslide");           iceSpellsNames.push_back("Surge");           lightingSpellsNames.push_back("Purge");
    fireSpellsNames.push_back("Meteor");              iceSpellsNames.push_back("Surging Soul");    lightingSpellsNames.push_back("Radiance");
    fireSpellsNames.push_back("Rancor");              iceSpellsNames.push_back("The Inner Ocean"); lightingSpellsNames.push_back("Shock");
    fireSpellsNames.push_back("Rockfall");            iceSpellsNames.push_back("Tsunami");         lightingSpellsNames.push_back("Stun");
    fireSpellsNames.push_back("Salamander's Blade");  iceSpellsNames.push_back("Wave");            lightingSpellsNames.push_back("Tempest");
    fireSpellsNames.push_back("Shade");                                                            lightingSpellsNames.push_back("Vortex");
    fireSpellsNames.push_back("Shadow Blade");                                                     lightingSpellsNames.push_back("Whirlwind");
    fireSpellsNames.push_back("Spite");                                                            lightingSpellsNames.push_back("Wyvern's Wings");
    fireSpellsNames.push_back("Whispered Blade");
    fireSpellsNames.push_back("Wrath");
    fireSpellsNames.push_back("Yakamo's Eye");
    fireSpellsNames.push_back("Yakamo's Wrath");
}
