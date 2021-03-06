# ASCIICraft
Autor: Jan Hlaváč

Jedná se o jednoduchou tahovou sandbox hru, kterou lze ovládat příkazy v terminálu. 
## Příkazy
### Hlavní menu
- `new` - vytvoří novou hru dle hráčem poskytnuté mapy v souboru (obvykle `*.map`), dále se doptá hráče na počet nepřátel
- `load` - načte rozehranou hru ze souboru (obvykle `*.save`)
- `quit` - ukončí hru

### Pauza
- `resume` - pokračuje ve hře
- `craft` - umožňuje hráči zadat řetězec ID předmětů (reprezentovaných jako znaky, viz níže) a vyrobí výsledný produkt podle předdefinovaných receptů (opět viz níže)
- `save` - umožní uložit hru do souboru, který hráč specifikuje
- `quit` - ukončí hru

### Režim hraní
- `w/a/s/d` - pohyb hráče po mapě
- `hit` - provede útok na všechny nepřátele v bezprostředním okolí 1 bloku
- `mine` - vykope blok před hráčem (pokud na to hráč vlastní potřebný vercajk)
- `build` - umístí stavební blok, tj. kámen před hráče
- `plant` - zasadí na blok před hráčem semeno nebo strom (na což se hráče doptá)
- `eat` - sní 1 donut a doléčí tím hráče
- `pause` - pozastaví hru


## Bloky a předměty
Bloky jsou v uživatelském rozhraní reprezentovány následujícími znaky. Tyto znaky jsou zároveň využívány v crafting receptech, tedy každému bloku a předmětu, který může sloužit pro další výrobu, přísluší právě jeden znak.

- Air: ` `
- Stone: `X`
- Lava: `L`
- Iron: `I`
- Tree: `T`
- Wood: `W`
- Seed: `.`
- Wheat: `:`
- Steel: `S`
- Donut: `D`

## Crafting recepty

- Pickaxe = `wwxxx`
- Sword = `wwiii`
- Steel = `ii`
- Spear = `wwss`
- Iron armor = `iiiii`
- Steel armor = `sssss`
- Donut = `::::`

## Herní soubory

### `.map` soubory
- 1.řádek: rozměry herního pole šířka x výška
- následuje pole znaků těchto rozměrů, které odpovídají požadovaným blokům (viz výše)

```
15 10
IIX            
IX             
X    XX      W 
            WWW
 I           W 
 I    XXXXX    
      XLLLX    
      XLLLX    
      XXXXX    
               
```

### `.save` soubory
- 1.část souboru: herní pole, stejný formát jako `.map`
- následuje:
    - počet dynamických bloků n
    - n řádků, kde jsou následující atributy odděleny mezerami:
        - ID bloku
        - souřadnice y
        - souřadnice x
        - (další info, v případě stromu a semene uplynulá doba růstu)
    - atributy hráče oddělené mezerou:
        - souřadnice y
        - souřadnice x
        - HP hráče 
    - počet různých itemů v inventáři m
    - m řádků, kde jsou následující atributy odděleny mezerami:
        - ID itemu
        - počet kusů od tohoto itemu v inventáři
	- počet nepřátel k
  	- k řádků, kde jsou následující atributy odděleny mezerami:
  		- souřadnice y
    	- souřadnice x
      	- HP nepřítele 

    

