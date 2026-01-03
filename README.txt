================================================================================
                                SPACE INVADERS
================================================================================

--------------------------------------------------------------------------------
1. O HŘE
--------------------------------------------------------------------------------
Tato hra je klasická 2D vesmírná střílečka inspirovaná hrou Space Invaders. 
Hráč hraje za vesmírnou lod a snaží se odrazit invazi nepřátelů.

Hra obsahuje:
- Úvodní menu
- Tabulku nejlepších skóre
- Jednoduchý návod pro hru

--------------------------------------------------------------------------------
2. OVLÁDÁNÍ
--------------------------------------------------------------------------------

Hru lze ovládat pomocí klávesnice:

  ŠIPKY NAHORU/DOLU     ... Pohyb výběru v menu
  ENTER                 ... Potvrzení volby v menu
  ŠIPKY DOLEVA/DOPRAVA  ... Pohyb rakety
  MEZERNÍK              ... Vystřelení rakety
  ESC                   ... Návrat do menu 
  
Většina ovládání je specifikována v průběhu hry a hráč bude vyzván, kterou klávesu stisknout.

--------------------------------------------------------------------------------
3. CÍL HRY:
--------------------------------------------------------------------------------

Zničit všechny nepřátelské lodě a získat co nejvyšší skóre. Hra končí, pokud 
hráč ztratí všechny životy, nebo pokud nepřátelké lodě dojdou na konec obrazovky.

--------------------------------------------------------------------------------
4. POŽADOVANÉ KNIHOVNY
--------------------------------------------------------------------------------
Hra běží na Linuxu. Pro úspěšný překlad a spuštění hry je nutné mít nainstalované následující 
knihovny:

- GCC (nebo jiný C kompilátor)
- CMake
- SDL2 
- SDL2_image 
- SDL2_ttf

Instalace knihoven: 
sudo apt-get install cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev

--------------------------------------------------------------------------------
5. JAK PŘELOŽIT PROJEKT 
--------------------------------------------------------------------------------

Po úspěšném stahnutí souborů musíme program nejprve přeložit. Docílíme toho postupným zadáním těchto příkazů: 

    mkdir -p build
    cd build
    cmake ..
    make

Pokud vše proběhlo bez potíží, můžeme program spustit. Spustitelný soubor se nachází ve složce build. 
Program spustíme pomocí: 
    ./spaceinvaders

