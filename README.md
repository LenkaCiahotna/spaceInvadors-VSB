# 🚀 Space Invaders – C/SDL2 hra

Školní projekt klasické **2D arkádové střílečky inspirované legendární hrou Space Invaders**, vytvořený v jazyce **C** s využitím knihovny **SDL2**.  
Hráč ovládá vesmírnou loď a snaží se odrazit invazi nepřátelských lodí.

## 🎮 Funkce

- Úvodní menu
- Tabulku nejlepších skóre
- Jednoduchý návod pro hru

## 🕹 Ovládání

| Klávesa | Akce |
|--------|--------|
| ⬆ / ⬇ | Pohyb v menu |
| ENTER | Potvrzení volby |
| ⬅ / ➡ | Pohyb rakety |
| MEZERNÍK | Vystřelení střely |
| ESC | Návrat do menu |

Během hry mohou být zobrazeny další pokyny přímo na obrazovce.

## 🎯 Cíl hry

- Zničit všechny nepřátelské lodě
- Získat co nejvyšší skóre

Hra končí, pokud:
- hráč ztratí všechny životy  
- nepřátelské lodě dosáhnou spodní části obrazovky  

## 👩🏻‍💻 Použité technologie

- **Jazyk:** C
- **Grafická knihovna:** SDL2
- **Build systém:** CMake

## 📸 Ukázky
<img width="750" alt="image" src="https://github.com/user-attachments/assets/6661e0e2-4db3-4b18-bef5-8470fd31221a" />
<img width="750" alt="image" src="https://github.com/user-attachments/assets/791ea864-ee3d-4a63-bb0c-53a269589696" />
<img width="750" alt="image" src="https://github.com/user-attachments/assets/f9d602de-e4de-43df-9143-cb0aee6cf542" />


## ⚙️ Instalace a spuštění 

Projekt vyžaduje Linuxové prostředí a nainstalované SDL2 knihovny.

### 1️⃣ Naklonování projektu
```bash
git clone https://github.com/lenkaciahotna/kino.git 
```

### 2️⃣ Instalace závislostí

Pro úspěšný překlad a spuštění hry je nutné mít nainstalované následující knihovny: 
- GCC (nebo jiný C kompilátor)
- CMake 
- SDL2 
- SDL2_image 
- SDL2_ttf

Instalace: 
```bash
sudo apt-get install cmake libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
 ```

### 3️⃣ Spuštění

Po úspěšném stahnutí souborů musíme program nejprve přeložit. Docílíme toho postupným zadáním těchto příkazů: 

- mkdir -p 
- build cd 
- build cmake .. 
- make 

Pokud vše proběhlo bez potíží, můžeme program spustit. Spustitelný soubor se nachází ve složce build. 

Program spustíme pomocí: 
```bash
./spaceinvaders
```
