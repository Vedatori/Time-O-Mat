V tomto dokumentu se nachází rozpis programovacích lekcí a zadání programovacích úkolů. 

**Programovací lekce** nejsou povinné, ale jsou velmi vhodné pro začátečníky. Zájem o lekci budete vyjadřovat tak, že na svůj řádek v tabulce připíšete na konec číslo lekce, o kterou máte zájem. Jakmile jste lekci absolvovali, číslo zakroužkujete tak, aby bylo jasné, které lekce už jste absolvovali. Účast na lekci je ohodnocena 1 Chotěcoinem.

**Programovací úkoly** jsou úkoly, které budete řešit samostatně. Ke každému úkolu potřebujete soubor znalostí, který je obsažen v některých z lekcí. Úkoly je však možné řešit i jen pomocí programovacího manuálu (pro pokročilé). Splnění úkolu bude kontrolovat vedoucí a odmění ho 2 - 4 Chotěcoiny. Po splnění úkolu si v tabulce na vašem řádku zaznačte křížkem jeho splnění. 

# Lekce 0
Zprovozníme programovací prostředí VS Code + PlatformIO tak, abyste mohli nahrát kód do Time-O-Mat z vašeho PC.

## Úkol 0 - Blikání LED
Pomocí kódu z manuálu rozsvítit LED.

# Lekce 1
Rozblikáme LED na digitech nebo LED pásku.

## Výsledný kód

```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    ToMat.display.setLED(0, 5, blue);
    delay(500);

    ToMat.display.setLED(0, 5, black);
    delay(500);    
}
```

## Úkol 1 - Blikání LED
Napište program, který bude blikat druhou LED na nultém digitu. Doba svitu i doba zhasnutí je 300 ms.

## Úkol 2 - Záblesky LED
Napište program, který každou vteřinu krátce zobrazí číslo 1 na posledním digitu. Doba zobrazení je 100 ms v každé vteřině.

## Úkol 3 - Železniční přejezd
Napište program, který bude blikat jako železniční přejezd. Blikat budou levý a pravý horní segment na jednom digitu, oba červenou barvou.

# Lekce 2
Přečteme stav tlačítka, ukážeme si binární proměnnou a v závislosti na ní rozezníme piezoakustický měnič.

## Výsledný kód

```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    if(ToMat.buttonRead(0)) {
        ToMat.piezo.tone(100);
    }
    else {
        ToMat.piezo.stop();
    }
    delay(20);
}
```

## Úkol 4 - Manuální blikání LED
Napište program, který bliká libovolnou LED pouze při stisknutém tlačítku nejblíž USB konektoru. Doba svícení je 200 ms. Doba zhasnutí je 200 ms.

## Úkol 5 - Stabilní stav LED
Napište program, který bude stiskem tlačítka přepínat svícení dvou různých segmentů na dvou různách digitech. Vždy bude svítit pouze jeden segment, stiskem tlačítka se tento segment vypne a zapne se ten druhý. Dalším stiskem tlačítka se znovu zapne pouze ten původní segment a proces lze opakovat.

# Lekce 3
Přečteme hodnotu na fotorezistoru, ukážeme si číselnou proměnnou. Hodnotu výstupu z fotorezistoru si zobrazíme na LED.

## Výsledný kód

```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

int x;

void loop() {
    ToMat.display.setFront(black);
    x = (ToMat.illumination.getRaw(0)/205);
    ToMat.display.setLED(0, x, blue);
    printf("%d \n ", x);
    delay(20);
}
```

## Úkol 6 - Rychlost blikání
Napište program, který bude blikat libovolným segmentem a rychlost tohoto blikání se zvětší, když se sníží intenzita osvětlení na předním fotorezistoru (např. bude zakrytý prstem).

## Úkol 7 - Počítadlo stisků tlačítka
Napište program, který počítá, kolikrát bylo stisknuto tlačítko SW1. Při resetování programu se počítadlo vynuluje. Pokud chceme zjistit, kolikrát bylo tlačítko SW1 stisknuto, musíme stisknout tlačítko SW2 a program musí pípnout daným počtem pípnutí.

# Lekce 4
Ukážeme si podmínku "if" na příkladu s LED. Pro ovládání se naučíme použít dotykovou lištu. 

```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    ToMat.display.setFront(black);
    if(ToMat.touchBar.getPressed(2)) {
        ToMat.display.setLED(1, 0, green);
    }
    else if(ToMat.touchBar.getPressed(3)) {
        ToMat.display.setLED(1, 2, green);
    }
    else {
        ToMat.display.setLED(1, 1, red);
    }
    delay(20);
}
```

## Úkol 8 - Zvuková signaliazce tmy
Napište program, který rozezní piezoakustický měnič, pokud Time-O-Mat vneseme do temnoty.

## Úkol 9 - Nastavení jasu LED po stisku tlačítka
Napište program, který při každém stisku jednoho z tlačítek na dotykové liště rozsvítí další LED v rámci jednoho segmentu a původní LED zhasne - "posune" světlo na LED na další pozici(začne se LED s indexem 0 a vždy se zvyšuje o 1). Po dosažení poslední LED se znovu rozsvítí nultá LED a proces se opakuje. Pokud není tlačítlo stisknuto, pořád svítí stejná LED.

# Lekce 5
Time-O-Mat začne komunikovat s počítačem pomocí sériové linky. Vyčteme okolní teplotu.

```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

int teplota;

void loop() {
    teplota = ToMat.getTemperature();
    printf("%d\n", teplota);
    delay(200);
}
```

## Úkol 10 - Vypsání hodnoty LED
Přepracujte úkol 9 tak, aby Time-O-Mat přes sériovou linku přenášel číslo LED, která právě svítí.

## Úkol 11 - Vyslání času od startu Time-O-Mat bez funkce millis()
Napište program, který bude vypisovat celočíselnou proměnnou každou vteřinu. Tuto proměnnou však každou milisekundu zvyšte o 1. Je chování tohoto programu stejné jako v případě použití funkce `millis()`?

