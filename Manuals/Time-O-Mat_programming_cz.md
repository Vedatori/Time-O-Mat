Toto je návod na programování výrobekického pásového vozidla Time-O-Mat. Začneme instalací vývojového prostředí na váš PC, následně si ukážeme základní pravidla programovacího jazyka C++ a poté začneme využívat funkce výrobku Time-O-Mat.

V tomto návodu se budeme zabývat programováním mikrokontroléru (mikropočítače) ESP32. K tomu je od výrobce ESP32 připraven framework (sada nástrojů urychlujících vývoj) ESP-IDF v jazyce C. Nadstavbou tohoto frameworku je další framework [arduino-esp32](https://github.com/espressif/arduino-esp32), který přidává další sadu nástrojů a je již napsán v jazyce C++. Arduino-esp32 používáme v našem projektu pro Time-O-Mat. Bylo k němu potřeba přidat množství kódu (knihovna *Time-O-Mat*), který se stará o *základní životní funkce* Time-O-Mat a umožňuje jednodušší používání jeho funkcionalit (z `main.cpp`). V tomto návodě se budeme zabývat jen uživatelským pohledem na používání knihovny *Time-O-Mat*.

___
# Obsah
* [Vývojové prostředí](#IDE)
* [Nahrání připraveného programu - kontrola](#kontrola)
* [Nový projekt](#novyProjekt)
* [První program](#prvniProgram)
* [Komentáře](#komentare)
* [Proměnné](#promenne)
* [Podmínky](#podminky)
* [Cyklus](#cyklus)
* [Funkce](#funkce)
* [LEDky](#ledky)
* [Tlačítka](#tlacitka)
* [Sériová linka](#seriovka)
* [Výpis textu na LED panel](#panelLed)
* [Bzučák](#buzzer)
* [WiFi](#wifi)
* [Vzdálený příkazový řádek](#remoteCmd)
___

<!-- _________________________________________________________________ -->
# <a name = IDE>Vývojové prostředí</a>

Pro programování Time-O-Mat je použito vývojové prostředí [Visual Studio Code](https://code.visualstudio.com/download) s rozšířením PlatformIO. Pro instalaci prostředí a rozšíření můžete použít tento [návod](https://docs.platformio.org/en/latest/ide/vscode.html#installation), jehož hlavní část je na obrázku níže:

![alt](SupportFiles/prog_install_PlatformIO.png)

<!-- _________________________________________________________________ -->
# <a name = kontrola>Nahrání připraveného programu - kontrola</a>

V této části nahrajete do Time-O-Mat připravený program pro jeho otestování. Program umožňuje připojení Time-O-Mat k WiFi a zobrazení aktuálního času.

Pro naprogramování Time-O-Mat si stáhněte [tento repozitář](https://github.com/vedatori/Time-O-Mat/archive/refs/heads/main.zip). Stáhnutý soubor *Time-O-Mat-main.zip* si rozbalte na disk svého PC na libovolnou lokaci tak, abyste ho našli. 
**Pozor:** PlatformIO nedokáže pracovat s diakritikou v cestě k projektu. Projekt tedy nesmí být součástí složky, která má diakritiku v názvu. Všechny projekty musí být uloženy v cestě bez háčků a čárek!
Pokud vaše uživatelské jméno obsahuje diakritiku, tak nemůžete používat Plochu ani složku Dokumenty, ale musíte vytvořit například *C:/Vedatori/Time-O-Mat-main*.

Ve VS Code otevřete nabídku *File*, klikněte na *Open Folder* a zvolte složku *Software/demo_project* z dříve rozbalené složky-repozitáře *Time-O-Mat-main*.
![alt](SupportFiles/prog_open_folder.png)

Otevřete soubor *main.cpp* který je v cestě *demo_project/src/main.cpp*.
![alt](SupportFiles/prog_open_main.png)

V souboru *main.cpp* upravte název výrobku "<your_name>" tak, aby byl poznatelný, např. jako "Franta" nebo "FrantaFlinta". 
Je možné přidat i heslo pro přihlašování např. takto
"`Time-O-Mat.startWiFiCaptain("<your_name>", "12345678");`".
Heslo musí mít minimálně 8 znaků, jinak nebude použito.
![alt](SupportFiles/prog_set_name.png)

Po otevření projektu bude VS Code chvíli pracovat. Pokud ještě pracuje, počkejte, dokud text na dolní liště nezmizí.
![alt](SupportFiles/Prog_wait_for_load.png)

Připojte Time-O-Mat pomocí USB-C kabelu k PC.

V dolní liště PlatformIO stiskněte šipku a tím nahrejte program do Time-O-Mat.
[alt](SupportFiles/prog_upload.png)

Počkejte, až se dokončí nahrávání a zobrazí v dolním terminálu *SUCCESS*.
![alt](SupportFiles/prog_success.png)

V dolní liště PlatformIO stiskněte tlačítko úplně v pravo a tím spusťe PlatformIO terminál.
![alt](SupportFiles/prog_uploadFS1.png)

Do nově otevřeného termínálu v dolní částí VS Code zadejte příkaz `pio run -t uploadfs` a stiskněte *ENTER*.
![alt](SupportFiles/prog_uploadFS2.png)

Počkejte, až se dokončí nahrávání a zobrazí v dolním terminálu *SUCCESS*.
![alt](SupportFiles/prog_success.png)

Nyní je výrobek plně naprogramován. Pro ovládání na svém chytrém zařízení vyhledejte WiFi síť s názvem *Time-O-Mat_<your_name>*. Zadejte do webového prohlížeče adresu *192.168.4.1* nebo jakoukoli jinou ve tvaru *www.neco.cz*. Načte se hlavní stránka pro ovládání Time-O-Mat.

Pro přihlášení Time-O-Mat k externí WiFi síti klikněte na tlačítko *WiFi setup*. Po delší chvíli se zobrazí stránka s dostupnými WiFi sítěmi. Zde zadejte přihlašovací údaje od externí WiFi a potvrďte přihlášení.
<img src="SupportFiles/prog_web_wifi.png" width="400"/>

Pokud přihlášení k externí WiFi proběhne úspěšně, objeví se potvrzení *connected* a přidělená IP adresa. Tato síť bude uložena a vyhledána i po restartu. Připojte se se svým chytrým zařízením také na externí WiFi a zadejte do prohlížeče IP adresu přidělenou Time-O-Mat. V tomto případě *192.168.88.197*. 
<img src="SupportFiles/prog_web_connected.png" width="400"/>

Načte se opět hlavní stránka ovládání Time-O-Mat. Tímto je vypnuta interní WiFi *Time-O-Mat_<your_name>*. Pro její opětovné zapnutí přejděte do nastavení WiFi a klikněte na tlačítko *Enable AP* nebo restartujte Time-O-Mat.
<img src="SupportFiles/prog_web_softAP.png" width="400"/>

<!-- Pro ovládání Time-O-Mat s připraveným programem můžete používat následující příkazy. Příkazy nejsou citlivé na velikost použitých písmen.
* `blade <angle>` - Nastaví výšku radlice na daný úhel serva. 0-dole, 180-nahoře
* `head <angle>` - Nastaví pozici serva LIDARu. 0-vpravo, 180-vlevo
* `beep` - Zapne buzzer na 0,5 vteřiny na frekvenci 1000Hz
* `take on me` - Zahraje píseň *Take on me* 
* `silence` - Zastaví přehrávání písně -->

<!-- _________________________________________________________________ -->
# <a name = novyProjekt>Nový projekt</a>

Vytvoříme nový projekt a nahrajeme program do Time-O-Mat.

1. Vytvořte si na disku svého PC složku pro vaše budoucí programy, například *C:/Time-O-Mat-moje-programy*.
1. Do této nové složky překopírujte složku *demo_project* ze stáhnutého repozitáře *Time-O-Mat-main*. Tato složka bude sloužit jako šablona tvých budoucích programů pro Time-O-Mat. 
1. Překopírovanou složku *demo_project* přejmenuj novým názvem, například na *01_prvni_program*.
1. Ve VS Code otevřete složku *01_prvni_program* pomocí *File*->*Open folder*.
1. Ve VS Code otevřete soubor *main.cpp* a nahraď jeho obsah následujícím kódem šablony:
    ```
    #include "ToMat/ToMat.h"

    void setup() {
        ToMat.begin();
    }

    void loop() {
        
    }
    ```
1. Připojte Time-O-Mat pomocí USB-C kabelu k PC.
1. V dolní liště PlatformIO stiskněte šipku (*Upload*) a tím nahrajte program do Time-O-Mat.
    ![alt](SupportFiles/prog_upload.png)
1. Počkejte až se dokončí nahrávání a zobrazí v dolním terminálu *SUCCESS*. Nyní je nový program nahrán.
    ![alt](SupportFiles/prog_success.png)

<!-- _________________________________________________________________ -->
# <a name = prvniProgram>První program</a>
Rozebereme si každý řádek šablony a napíšeme náš první program.

Zde je kód šablony:
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    ToMat.display.update();
    delay(20);
}
```

1. `#include "ToMat/ToMat.h"` - Příkaz *#include* přidává do našeho programu kód z jiných míst. Nyní nám stačí přidání knihovny *ToMat.h* ze složky ToMat.
1. `void setup() {}` - Toto je definice funkce. Funkce jsou kusy kódu, které můžeš opakovaně spustit tak, že zavoláš jejich jméno. Kód (tělo) funkce je ohraničen složenými závorkami { a }, a mezi nimi odsazen. Tato funkce se jmenuje *setup* a je spuštěna jedenkrát po zapnutí Time-O-Mat. O to se postará arduino-esp32 framework.
1. `ToMat.begin();` - Toto je volání funkce z knihovny *Time-O-Mat*, která knihovnu inicializuje a připraví všechny její komponenty pro budoucí použití. Toto je třeba provést pouze jednou po startu výrobku, proto je příkaz umístěn ve funkci *setup*.
1. `void loop()` - Toto je definice funkce *loop*. Ta je spouštěna stále dokola dokud je Time-O-Mat zapnutý.
1. `delay(20);` - Toto je příkaz pro čekání-nic nedělání definovanou dobu, zde 20 milisekund.

## Váš kód
Nyní napíšete svůj první vlastní program pro Time-O-Mat. Na konec funkce *setup* připiště `ToMat.display.setLED(0, 0, white);`, tedy nad uzavírací závorku }. Tento příkaz zapříčiní, že se na digitu číslo 1 rozsvítí LED číslo 1 bílou barvou.

Všimněte si, že při psaní vám VS Code napovídá. Stačí napsat `ToMat.` a uvidíte nabídku připravených funkcí z knihovny *Time-O-Mat*. Pokud se tak nestane, nabídku vyvoláte stisknutím *Ctrl + Space*.
![alt](SupportFiles/prog_hint.jpg)

Funkce *setLed()* slouží k zapínání a vypínání LED světel na Time-O-Mat. Jedná se o volání funkce s parametry v kulatých závorkách ( a ).
1. parametr udává, který digit chceme ovládat. Jsou číslovány zleva doprava od 0 po 3. Zadní LED pásek má index 4.
1. parametr udává, kterou LED daného digitu chceme ovládat.
1. parametr udává, jakou barvou má LED svítit. Můžeme použít předdefinované barvy *red, green, blue, cyan, magenta, yellow, black, white*.

Dále dopíšeme příkaz `Tomat.display.update()`, který zajistí aktualizaci stavu LEDek.

Nahrajte program do Time-O-Mat a počkejte, až se první LED rozsvítí. Gratulujeme, toto byl váš první vlastní program pro Time-O-Mat :-)

Zde je výsledný kód programu:
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
    ToMat.display.setLED(0, 0, white);
    ToMat.display.update();
}

void loop() {
    delay(20);
}
```

<!-- _________________________________________________________________ -->
# <a name = komentare>Komentáře</a>

Do svého kódu je někdy vhodné psát komentáře. Komentáře jsou kusy textu, které jsou viditelné pro programátora, čili vás, ale TracJet si jich nevšímá (ani se do něj nenahrají). Jsou vhodné zejména v místech, kdy ze samotného funkčního kódu není zřejmé, co dělá a k čemu slouží.

V jazyce C++ máme 2 typy komentářů:
1. Jenořádkový komentář je uvozen dvojitým lomítkem `//`. Celý zbytek řádku za dvojitým lomítkem je považován za komentář.
1. Víceřádkový komentář je uvozen lomítkem a hvězdičkou `/*`. Ukončen je hvězdičkou a lomítkem `*/`. Veškerý text mezi je považován za komentář. Začátek a konec mohou být na různých řádcích.

Příklad: Tento program nerozsvítí LEDku.
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
    ToMat.display.setLED(0, 0, white); // Toto je komentář
    //ToMat.display.update(); tento řádek se neprovede

    /* Toto je 
    víceřádkový komentář. */
}

void loop() {
    delay(20);
}
```

<!-- _________________________________________________________________ -->
# <a name = promenne>Proměnné</a>

## Motivace
Při psaní programů brzy dojdete k tomu, že potřebujete, aby si program něco *zapamatoval*. Může se jednat o výsledek matematicé operace, počítadlo kroků, uchování měřené hodnoty a tak dále. K tomuto účelu se v programech používají **proměnné**. Proměnné si můžeme představovat jako šuplíky s textovými popisky na sobě. Do šuplíku můžeme *vložit* nějakou informaci a někdy později ji opět vytáhnout. Popisek šuplíku zde představuje název proměnné.

## Vytvoření proměnné
Proměnnou vytvoříme následujícím příkazem:
```
typ_promenne nazev_promenne = hodnota;
```
`typ_promenne` udává jaký typ informace budeme do proměnné ukládat. Říkáme mu také *datový typ proměnné*. Může to být číslo, text atd.

`nazev_promenne` udává název proměnné, pomocí kterého dokážeme od sebe jednotlivé proměnné odlišit. Proto musí mít každá proměnná svůj jedinečný název. Snaž se pojménovávat proměnné výstižně, tedy např. *rychlost* je mnohem lepší než *prom*. V názvu proměnné můžeš používat znaky anglické abecedy, tj. bez diakritiky, velká a malá písmena, čísla a speciální znaky jako podrtžítko `_`. Podtžítkem můžeme oddělovat slova v názvu jedné proměnné.

`=` je operátor sloužící k přiřazení (vložení) určité hodnoty do proměnné.

`;` čili středník slouží k oddělování příkazů a píšeme ho vždy na konec příkazu. Na české klávesnici se nachází pod klávesou *ESC* vlevo nahoře.

## Základní datové typy proměnných
* `int` označuje proměnnou pro ukládání celých čísel, například `3`.
* `float` označuje proměnnou pro ukládání desetinných čísel, například `3.14`.
* `char` označuje jeden textový znak -> znak se udává v apostrofech, například `'c'` označuje znak *c*.
* `bool` označuje pravdivostní hodnotu -> *true* pro pravdu a *false* pro nepravdu.
* `std::string` označuje řetězec textových znaků -> řetězec se ohraničuje uvozovkami, například `"Ahoj svete"`.

## Operace s proměnnými

Operace *přiřazení* slouží k uložení dané hodnoty do proměnné. Hodnota, která je napravo od rovnítka `=` je uložena do proměnné uvedené nalevo od `=`: 
```
nazev_promenne = hodnota;
```

Číselné proměnné můžeme sčítat (+), odečítat (-), násobit (*) a dělit (/). 

Příklad:
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
    int cele_cislo = 0;
    cele_cislo = cele_cislo + 10;   // Zvýšíme hodnotu v proměnné o 10
    cele_cislo += 10;   // Zkrácený zápis stejné operace jako výše
    // Nyní je v proměnné cele_cislo uložena hodnota 20
}

void loop() {
    delay(20);
}
```

Zde jsou uvedeny příklady vytvoření proměnných zmíněných datových typů a uložení hodnoty do nich.
```
// proměnná pro celá čísla se jménem cele_cislo, ve které je hodnota 0
int cele_cislo = 0; 

// promenna pro desetinne cislo ve které je hodnota 3.14
float desetinne_cislo = 3.14; 

// proměnná znak, do které jsme uložili znak 'a'
char znak = 'a';

// proměnná otevreno, do které jsme uložili hodnotu pravda (true)
bool otevreno = true; 

// proměnná pro textový řetězec s hodnotou "nejaky text"
String text = "nejaky text";
```

<!-- _________________________________________________________________ -->
# <a name = podminky>Podmínky</a>

## Motivace
Při programování brzo zjistíte, že potřebujete, aby se váš program choval různě v různých situacích. Jinými slovy aby prováděl určité úseky kódu pouze za splnění daných podmínek. K tomu se používají *podmínky*. Ty umožňují programu provádět *rozhodnutí*.

## Konstrukce `if`
`if` je základní podmínka. Základem této konstrukce je *podmínka*, která se uvádí za `if` do kulatých závorek. Podmínka může být proměnná nebo logický výraz.
```
if(podminka) {
    ...kód který se provede, pokud je podmínka splněna (true)...
}
```
U `if` konstrukce docházi k vyhodnocení podmínky, tj. zjistí se, zda je podmínka pravdivá (`true`) nebo nepravdivá (`false(`). Pokud je pravdivá, provede se kód, který je za `if` uveden ve složených závorkách `{...kód...}`. V opačném případě program pokračuje až za `if`.

## Konstrukce `else`
Může existovat jen v případě, že před ní byl uvedený `if`. Úkolem `else` je provést kód v něm napsaný jen v případě, že předchozí `if` nebyl splněn.
```
if(podminka) {
    ...kód který se provede, pokud je podmínka splněna (true)...
}
else {
    ...kód který se provede, pokud není podmínka splněna (false)...
}
```

## Konstrukce `else if`
Pokud chceme postihnout více možných příapadů než dva dříve zmíněné (`true` a `false`), použijeme konstrukci `else if`.
```
if(podminka_1) {
    ...kód který se provede, pokud je podmínka 1 splněna (true)...
}
else if(podminka_2) {
    ...kód který se provede, pokud je podmínka 2 splněna (true)...
}
else {
    ...kód který se provede, pokud není podmínka 1 ani 2 splněna (false)...
}
```

Poznámka: V jednotlivých konstrukcích větvení je možné libovolně vnořovat další konstrukce větvení.

## Podmínka
Podmínka dotazovaná při větvení určuje zda se bude daný úsek kódu provádět. K tomu je porovnávána s logickými hodnotami `true` a `false`. Tato hodnota může být uložena v pravdivostní proměnné typu `bool`:
```
bool podminka = true;
if(podminka) {
    ...kód je vykonán, protože podmínka je pravdivá...
}
```

K vytvoření podmínky z číselné hodnoty budeme používat tzv. *relační operátory*:
* `==` označuje porovnávání, takže 1 == 1 označuje, že se 1 rovná 1
* `!=` vykřičník před rovnítkem označuje opak, tudíž tento operátor značí nerovnost, tedy 1 != 2 označuje, že se 1 nerovná 2
* `<` menší než
* `>` větší než
* `<=` menší nebo rovno než
* `>=` větší nebo rovno než
Výsledek výrazu s relačními operátory nabývá hodnotu pravda `true` nebo nepravda `false`.
Příklad relačního operátoru:
```
int cele_cislo = 3;
if(cele_cislo < 5) {
    if (cele_cislo > -5) {
        cele_cislo = 0;
    }
}
// V proměnné cele_cislo je uložena hodnota 0, protože obě podmínky byly splněny
```

## Propojování podmínek
Podmínky je možné propojovat do jedné složitější pomocí logických operátorů. Jsou jimi
* `&&` (logické *A*) říká nám, že musí platit obě podmínky, aby byla podmínka splněna, jinak je nesplněna
* `||` (logické *NEBO*) říká nám, že musí platit alespoň jedna podmínka z nich, aby byla podmínka splněna, jinak je nesplněna
Ukázka: Následující program funguje stejně jako předchozí, používá ovšem využívá logické operátory.
```
int cele_cislo = 3;
if(cele_cislo < 5 && cele_cislo > -5) {
    cele_cislo = 0;
}
// V proměnné cele_cislo je uložena hodnota 0, protože obě podmínky byly splněny
```

<!-- _________________________________________________________________ -->
# <a name = cyklus>Cyklus</a>

## Motivace
Při programování se nám často stane, že potřebujeme některé úkony vykonat vícekrát. Případně vykonat velké množství podobných úkonů. K tomuto budeme používat *cykly*, které nám umožní opakovaně vykonávat úseky kódu.

Pro jedno bliknutí LEDkou poslouží tento program:
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();

    ToMat.display.setLED(0, 0, white);
    ToMat.display.update();

    delay(500);

    ToMat.display.setLED(0, 0, black);
    ToMat.display.update();
}

void loop() {
    delay(20);
}
```

V tomto programu používáme příkaz *delay()* pro čekání na místu v kódu o určitý čas. Tento čas čekání je určen v milisekundách (1000 ms = 1s).

Pro 3 bliknutí LEDkou poslouží tento program, ve kterém jsme pouze zopakovali příkazy z minulého:
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();

    ToMat.display.setLED(0, 0, white);
    ToMat.display.update();
    delay(500);
    ToMat.display.setLED(0, 0, black);
    ToMat.display.update();
    delay(500);
    ToMat.display.setLED(0, 0, white);
    ToMat.display.update();
    delay(500);
    ToMat.display.setLED(0, 0, black);
    ToMat.display.update();
    delay(500);
    ToMat.display.setLED(0, 0, white);
    ToMat.display.update();
    delay(500);
    ToMat.display.setLED(0, 0, black);
    ToMat.display.update();
}

void loop() {
    delay(20);
}
```

Ale co kdybychom chtěli bliknout 1000 krát? Kód by nás přerostl. Cykly nám pomohou tento problém vyřešit. 

## Cyklus `while`
Cyklus `while` použijeme v případě, kdy předem nevíme, kolikrát chceme kód opakovat. Cyklus `while` se opakuje dokud je splněna jeho podmínka (`true`).
```
while(podminka){
    ...Co se ma provest pri kazdem opakovani...
}
```

V následném úseku kódu budeme blikat LEDkou dokud bude Time-O-Mat zapnutý:
```
while(true){
    ToMat.display.setLED(0, 0, white);
    ToMat.display.update();
    delay(500);
    ToMat.display.setLED(0, 0, black);
    ToMat.display.update();
}
```

## Cyklus `for`
Cyklus `for` použijeme v případě, kdy dopředu známe, kolikrát chceme kód opakovat. Cyklus `for` má následující formu:
```
for(vytvoreni_promenne; podminka; operace){
    ...Co se ma provest pri kazdem opakovani...
}
```

Oproti cyklu while je zde podmínková část složitější. Skládá se ze 3 částí:
* Vytvoř proměnnou, kterou využiješ v podmínce
* Zadej podmínku, která bude udávat, do kdy máme kód opakovat
* Uprav hodnotu proměnné, pokud je podmínka splněna

Následující program ukazuje, jak bliknout 10x s LED číslo 1 pomocí cyklus `for`.
```
for(int pocet_bliku = 0; pocet_bliku < 10; pocet_bliku++){
    ToMat.display.setLED(0, 0, white);
    ToMat.display.update();
    delay(500);
    ToMat.display.setLED(0, 0, black);
    ToMat.display.update();
}
```
Vytvořili jsme proměnnou `pocet_bliku`, která obsahuje celé číslo 0. Dokud je hodnota této proměnné menší než 10, zvýší se její hodnota 1 a provede se kód uvnitř cyklu. Jakmile hodnota proměnné rovna 10, cyklus se ukončí a program pokračuje směrem dolů.

<!---
___
# <a name = funkce>Funkce</a>
**TODO**
-->

<!-- _________________________________________________________________ -->
# <a name = ledky>LEDky</a>
V této kapitole si pořádně ukážeme ovládání LEDek na Time-O-Mat.

<!-- _________________________________________________________________ -->
# <a name = tlacitko>Tlačítka</a>
Nejjednodušším způsobem, jak můžete Time-O-Mat ovládat je pomocí tlačítek, které najdete na levé straně krabičky. Pro zjištění jestli je tlačítko zmáčknuto budeme používat příkaz `ToMat.buttonRead(int buttonID)` v náslející konstrukci.
```
bool tlacitko_zmacknuto = Time-O-Mat.buttonRead(1);
```
Zde je vytvořena proměnná `tlacitko_zmacknuto` a následně do ní uložen stav tlačítka voláním příkazu `Time-O-Mat.buttonRead()`, který nabývá pravdivostní hodnoty `true` nebo `false`.

Příklad: Tento program rozsvítí LED při stisku tlačítka 1.
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    if(ToMat.buttonRead(1)) {
        ToMat.display.setLED(0, 0, white);
    }
    else {
        ToMat.display.setLED(0, 0, black);
    }
    ToMat.display.update();
    delay(20);
}
```

<!-- _________________________________________________________________ -->
# <a name = seriovka>Sériová linka</a>

## Motivace
Při programování výrobků se často stane, že potřebujete s programem ve výrobku komunikovat. Například když se snažíte odhalit chybu, vypisovat hodnotu senzorů nebo informovat uživatele o ději v programu. Pro tento účel nám poslouží sériová linka.

## Program pro výpis textu na sériové lince
Pro výpis textu na sériové lince budeme používat příkaz `printf`. Abyste na sériové lince jedenkrát vypsali text *Hello World!*, použijte následující program:
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    printf("Hello World!\n");
    delay(1000);
}
```

Okolo textu, který chceme vypsat, je třeba vložit dvojité uvozovky `"text"`. Řetězec `\n` označuje znak pro odřádkování, čili obdoba tlačítka *ENTER* v textových editorech. 

## Spuštění sériové linky
1. Po nahrání programu do Time-O-Mat necháme Time-O-Mat zapnutý a připojený USB kabelem k PC.
1. Pomocí tlačítka v levé dolní liště PlatformIO ve tvaru zásuvky spustíme sériovou linku.

    ![alt](SupportFiles/prog_serial.png)
1. V monitoru sériové linky v dolní částí okna VS Code najdete příchozí zprávy z Time-O-Mat. Uvidíte, že každou vteřinu přijde nová zpráva ve tvaru *Hello World!*, vždy na novém řádku:
    ![alt](SupportFiles/prog_hello.png)

## Výpis hodnot proměnných
Často potřebujeme vypsat i hodnotu některé z našich proměnných. V tomto případě můžeme použít takzvaná formátovací direktiva. V textu začínají znakem `%`:
* %d - (decimal) označuje celé číslo
* %f - (float) značí desetinné číslo
* %c - (char) označuje znak
* %s - (string) značí řetězec 

Pro úpravu formátu vypisovaných proměnných máme mnoho dalších možností, které jsou například na [Wiki](https://cs.wikipedia.org/wiki/Printf#Form%C3%A1tovac%C3%AD_%C5%99et%C4%9Bzec). Pro výpis celočíselné proměnné `cele_cislo` do sériové linky použijeme následující příkaz:
```
printf("%d\n", cele_cislo);
```

Příklad: Pro opakovaný výpis času od startu Time-O-Mat použijeme následující program. Hodnota času je uvedena v milisekundách:
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    printf("%d\n", millis());
    delay(1000);
}
```

Funkce `millis()` nám vrací počet uplynulých milisekund od startu Time-O-Mat jako celé číslo. 

<!-- _________________________________________________________________ -->
# <a name = panelLed>Výpis textu na LED panel</a>

<!-- _________________________________________________________________ -->
# <a name = buzzer>Bzučák</a>

<!-- _________________________________________________________________ -->
# <a name = wifi>WiFi</a>
Pro spuštění WiFi a ovládací webové aplikace slouží funkce `ToMat.startWiFiCaptain("<your_name>")`. Po jejím zavolání bude postaráno o vytvoření WiFi přístupového bodu (AP) v Time-O-Mat a také o připojní k externí WiFi, jakmile má Time-O-Mat správné přihlašovací údaje a je v dosahu. Také je spuštěn server hostující webovou aplikaci pro dálkové ovládání Time-O-Mat.

<!-- _________________________________________________________________ -->
# <a name = remoteCmd>Vzdálený příkazový řádek</a>
Pro dálkové ovládání Time-O-Mat můžete použít i textové příkazy. Ty budete zadávat do pole *Command entry* na webové stránce dálkového ovládání. Po stisku tlačítka *Enter* (funguje i na klávesnici) je zadaný příkaz odeslán do Time-O-Mat. K použítí přijatého příkazu budeme používat následující funkce:
* `ToMat.commandGet()` - vrací textový řetězec (proměnnou typu *String*) obsahující aktuálně přijatý příkaz.
* `ToMat.commandGetIndexed(index)` - vrací textový řetězec obsahující jedno slovo z přijatého příkazu. Slova jsou oddělena mezerami a číslována od 0.
* `ToMat.commandClear()` - vymaže obsah celého aktuálně přijatého příkazu.

Příklad: Následující program blikne LED po obdržení příkazu "blink":
```
#include "Time-O-Mat/Time-O-Mat.h"

void setup() {
    ToMat.begin();
    ToMat.startWiFiCaptain("<your_name>");
}

void loop() {
    if(ToMat.commandGet() == "blink") {
        ToMat.display.setLED(0, 0, white);
        ToMat.display.update();
        delay(500);
        ToMat.display.setLED(0, 0, black);
        ToMat.display.update();
        ToMat.commandClear();  // nutné jinak bude v paměti pořád příkaz "blink" a LED bude pořád svítit
    }
    delay(100);
}
```

Time-O-Mat umožňuje textovou komunikaci i opačným směrem, tedy z Time-O-Mat do webové stránky dálkového ovládání.
* `ToMat.commandDisp(command)` - odešle textový příkaz *command* z Time-O-Mat a zobrazí ho šedě v poli *Command entry*.

Příklad: Následující program bude v textovém poli *Command entry* vypisovat stav tlačítka 1 na Time-O-Mat:
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
    ToMat.startWiFiCaptain("<your_name>");
}

void loop() {
    ToMat.commandDisp(String(Time-O-Mat.buttonRead(1)));
    delay(500);
}
```