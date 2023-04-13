Toto je návod na programování hodin Time-O-Mat. Začneme instalací vývojového prostředí na váš PC, následně si ukážeme základní pravidla programovacího jazyka C++ a poté začneme využívat funkce výrobku Time-O-Mat.

V tomto návodu se budeme zabývat programováním mikrokontroléru (mikropočítače) ESP32. K tomu je od výrobce ESP32 připraven framework (sada nástrojů urychlujících vývoj) ESP-IDF v jazyce C. Nadstavbou tohoto frameworku je další framework [arduino-esp32](https://github.com/espressif/arduino-esp32), který přidává další sadu nástrojů a je již napsán v jazyce C++. Arduino-esp32 používáme v našem projektu pro Time-O-Mat. Bylo k němu potřeba přidat množství kódu (knihovna *Time-O-Mat*), který se stará o *základní životní funkce* Time-O-Mat a umožňuje jednodušší používání jeho funkcionalit (z `main.cpp`). V tomto návodě se budeme zabývat jen uživatelským pohledem na používání knihovny *Time-O-Mat*.

___
# Obsah
* [Vývojové prostředí](#IDE)
* [Nahrání demo programu - kontrola](#kontrola)
* [Ovládání demo programu](#ovladani)
* [Nový projekt](#novyprojekt)
* [První program](#prvniprogram)
* [Komentáře](#komentare)
* [Proměnné](#promenne)
* [Podmínky](#podminky)
* [Cyklus](#cyklus)
* [Funkce](#funkce)
* [LEDky](#ledky)
* [Tlačítka](#tlacitka)
* [Piezoakustický měnič](#piezo)
* [Fotorezistory](#fotorezistory)
* [Dotyková lišta](#lista)
* [Teploměr](#teplomer)
* [Sériová linka](#seriovka)
* [Displej a podsvícení](#displej)
* [WiFi](#wifi)
* [Vzdálený příkazový řádek](#prikazy)
___

<!-- _________________________________________________________________ -->
# <a name = IDE>Vývojové prostředí</a>

Pro programování Time-O-Mat je použito vývojové prostředí [Visual Studio Code](https://code.visualstudio.com/download) s rozšířením PlatformIO. Pro instalaci prostředí a rozšíření můžete použít tento [návod](https://docs.platformio.org/en/latest/ide/vscode.html#installation), jehož hlavní část je na obrázku níže:

![alt](SupportFiles/prog_install_PlatformIO.png)

<!-- _________________________________________________________________ -->
# <a name = kontrola>Nahrání demo programu - kontrola</a>

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

![alt](SupportFiles/prog_wait_for_load.png)

Připojte Time-O-Mat pomocí USB-C kabelu k PC.

V dolní liště PlatformIO stiskněte šipku a tím nahrejte program do Time-O-Mat.

![alt](SupportFiles/prog_upload.png)

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

Demo program umožňuje také nastavení Time-O-Mat.
* Nastavení času pomocí tlačítek: 
* Nastavení času pomocí webového rozhraní: 
* Nastavení barvy displeje pomocí tlačítek: 
* Nastavení barvy displeje pomocí webového rozhraní: 
* 
* 

<!-- _________________________________________________________________ -->
# <a name = ovladani>Ovládání demo programu</a>

Time-O-Mat je možné skrze právě nahraný demo program uživatelsky ovládat a nastavovat jeho parametry. Jedná se o uživatelské funkce Time-O-Mat SW knihovny, které jsou zpravidla nastaveny v hlavním souboru *main.cpp*. Zde je také možné je jednoduše měnit a přizpůsobovat si funkčnost Time-O-Matu. Demo program je možné ovládat násedujícími způsoby:

## Fyzická tlačítka a dotyková lišta
* Nastavení času: Při přidržení tlačítka 0 na levé straně (nejdále od displeje) a dotýkání se 2 dotykových tlačítek nejvíce vlevo je možné nastavit čas po minutách dolů (levé) a nahoru (pravé). Po tomto nastavení se přestane synchronizovat čas s internetovým časem až do restartu.
* Nastavení barvy displeje: Při přidržení tlačítka 0 na levé straně (nejdále od displeje) a dotýkání se zleva 3. a 4. dotykového tlačítka je možné nastavit červenou složku barvy displeje. Levým ubereme a pravým přidáme na intenzitě. Pro zelenou složku použijeme 5. a 6. dotykové tlačítko. Pro modrou složku použijeme 7. a 8. tlačítko.
* Zahrání táborové znělky: Stiskem tlačítka 1 na levé straně (uprostřed) spustíme demo skladbu *Maniac*.
* Reset: Stiskem tlačítka 2 na levé straně (nejblíže displeji) resetujeme Time-O-Mat.

## Webové rozhraní
* Nastavení času: Do pole *Command entry* zadáme příkaz je ve tvaru `settime HH MM`. Parametry `HH` a `MM` odpovídají hodinám a minutám. Například pro nastavení času 12:34 použijeme příkaz `settime 12 34`. Příkaz odešleme stiskem tlačítka *Enter*.
* Nastavení časové zóny: Do pole *Command entry* zadáme příkaz je ve tvaru `setzone X`. Parametr `X` je textový řetězec (kód) popisující danou časovou zónu. [Seznam časových zón a jejich kódů je zde](https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv). Například pro nastavení české časové zóny včetně časových posuvů použijeme příkaz `setzone CET-1CEST,M3.5.0,M10.5.0/3`. Změna času po úspěšné změně časové zóny se za dostupného internetu projeví okamžitě. Pozor, v případě zadání nesprávného kódu časové zóny bude automatická sychronizace času vypnuta (neprobíhá kontrola validnosti zadaného kódu).
* Nastavení barvy displeje: Do pole *Command entry* zadáme příkaz je ve tvaru `rgb R G B`. Parametry `R`, `G` a `B` odpovídají jednotlivým hodnotám RGB kódu zvolené barvy v rozsahu 0-255. Například pro nastavení zelené barvy použijeme příkaz `rgb 0 255 0`. Příkaz odešleme stiskem tlačítka *Enter*.

<!-- _________________________________________________________________ -->
# <a name = novyprojekt>Nový projekt</a>

Vytvoříme nový projekt a nahrajeme program do Time-O-Mat.

## Postup
Vytvořte si na disku svého PC složku pro vaše budoucí programy, například *C:/Time-O-Mat-moje-programy*.

Do této nové složky překopírujte složku *demo_project* ze stáhnutého repozitáře *Time-O-Mat-main*. Tato složka bude sloužit jako šablona tvých budoucích programů pro Time-O-Mat. 

Překopírovanou složku *demo_project* přejmenuj novým názvem, například na *01_prvni_program*.

Ve VS Code otevřete složku *01_prvni_program* pomocí *File*->*Open folder*.

Ve VS Code otevřete soubor *main.cpp* a nahraď jeho obsah následujícím kódem šablony:
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    
}
```
Jednotlivé řádky šablony mají následující význam:
* `#include "ToMat/ToMat.h"` - Příkaz *#include* přidává do našeho programu kód z jiných míst. Nyní nám stačí přidání knihovny *ToMat.h* ze složky ToMat.
* `void setup() {}` - Toto je definice funkce. Funkce jsou kusy kódu, které můžeš opakovaně spustit tak, že zavoláš jejich jméno. Kód (tělo) funkce je ohraničen složenými závorkami { a }, a mezi nimi odsazen. Tato funkce se jmenuje *setup* a je spuštěna jedenkrát po zapnutí Time-O-Mat. O to se postará arduino-esp32 framework.
* `ToMat.begin();` - Toto je volání funkce z knihovny *Time-O-Mat*, která knihovnu inicializuje a připraví všechny její komponenty pro budoucí použití. Toto je třeba provést pouze jednou po startu výrobku, proto je příkaz umístěn ve funkci *setup*.
* `void loop()` - Toto je definice funkce *loop*. Ta je spouštěna stále dokola dokud je Time-O-Mat zapnutý.

Připojte Time-O-Mat pomocí USB-C kabelu k PC.

V dolní liště PlatformIO stiskněte šipku (*Upload*) a tím nahrajte program do Time-O-Mat.
![alt](SupportFiles/prog_upload.png)

Počkejte až se dokončí nahrávání a zobrazí v dolním terminálu *SUCCESS*. Nyní je nový program nahrán.
![alt](SupportFiles/prog_success.png)

<!-- _________________________________________________________________ -->
# <a name = prvniprogram>První program</a>

Nyní napíšete svůj první vlastní program pro Time-O-Mat. Do šablony kódu na konec funkce *setup* připiště příkaz `ToMat.display.setLED(0, 0, white);`, tedy nad uzavírací závorku }. Tento příkaz vydá požadavek, aby se na digitu číslo 0 rozsvítila LED číslo 0 bílou barvou.

Všimněte si, že při psaní vám VS Code napovídá. Stačí napsat `ToMat.` a uvidíte nabídku připravených funkcí z knihovny *Time-O-Mat*. Pokud se tak nestane, nabídku vyvoláte stisknutím *Ctrl + Space*.
![alt](SupportFiles/prog_hint.jpg)

Nahrajte program do Time-O-Mat a počkejte, až se LED rozsvítí. Gratulujeme, toto byl váš první vlastní program pro Time-O-Mat :-)

## Výsledný kód

```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
    ToMat.display.setLED(0, 0, white);
}

void loop() {}
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
    //ToMat.display.setLED(0, 0, black); tento řádek se neprovede

    /* Toto je 
    víceřádkový komentář. */
}

void loop() {}
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
* `String` označuje řetězec textových znaků -> řetězec se ohraničuje uvozovkami, například `"Ahoj svete"`.

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

void loop() {}
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

Poznámka: Do jednotlivých konstrukcí větvení je možné libovolně vnořovat další konstrukce větvení.

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

    delay(500);

    ToMat.display.setLED(0, 0, black);
}

void loop() {}
```

V tomto programu používáme příkaz *delay()* pro čekání na místu v kódu o určitý čas. Tento čas čekání je určen v milisekundách (1000 ms = 1s).

Pro 2 bliknutí LEDkou poslouží tento program, ve kterém jsme pouze zopakovali příkazy z minulého:
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();

    ToMat.display.setLED(0, 0, white);
    delay(500);
    ToMat.display.setLED(0, 0, black);
    delay(500);
    ToMat.display.setLED(0, 0, white);
    delay(500);
    ToMat.display.setLED(0, 0, black);;
}

void loop() {}
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
    delay(500);
    ToMat.display.setLED(0, 0, black);
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
    delay(500);
    ToMat.display.setLED(0, 0, black);
}
```
Vytvořili jsme proměnnou `pocet_bliku`, která obsahuje celé číslo 0. Dokud je hodnota této proměnné menší než 10, zvýší se její hodnota 1 a provede se kód uvnitř cyklu. Jakmile hodnota proměnné rovna 10, cyklus se ukončí a program pokračuje směrem dolů.

<!-- _________________________________________________________________ -->
# <a name = ledky>LEDky</a>
V této kapitole si podrobněji ukážeme ovládání LEDek na Time-O-Mat.

Jednotlivé LEDky budeme ovládat pomocí příkazu `ToMat.display.setLED(int segmentID, int ledID, ColorRGB color)`. Jedná se o volání funkce s parametry v kulatých závorkách:
* `segmentID` udává, který digit chceme ovládat.
* `ledID` udává, kterou LED daného digitu chceme ovládat.
* `color` udává, jakou barvou má daná LED svítit. Můžeme použít předdefinované barvy *red, green, blue, cyan, magenta, yellow, black, white*, nebo si definovat vlastní.

Parametr `segmentID` nabývá následujících hodnot:
* `0` pro první digit zleva.
* `1` pro druhý digit zleva.
* `2` pro dvojtečku uprostřed.
* `3` pro třetí digit zleva.
* `4` pro čtvrtý digit zleva.
* `5` pro zadní LED pásek.

Parametr `ledID` čísluje LEDky v jednotlivých digitech v následujícím pořadí:
![alt](SupportFiles/osmicka.jpg)

Parametr  `ledID` čísluje LEDky na dvojtečce od 0 (nahoře) po 1 (dole).

Parametr `ledID` čísluje LEDky na zadním LED pásku od 0 (vlevo) po 8 (vpravo) při pohledu na hodiny ze zadu.

Pro definování vlastní barvy použijeme kontrukci podobnou vytváření proměnných. Existují 2 formáty, pomocí kterých můžeme definovat vlastní barvu:
* RGB (red-červená, green-zelená, blue-modrá) příkazem `ColorRGB cervena = {255, 0, 0};`
* HSV (hue-chromatičnost, saturation-saturace, value-jas) příkazem `ColorHSV cervena = {0, 1, 1};`

Oba formáty dokážou definovat jakoukoli barvu, kterou umí barevné LEDky vysvítit, ale každý má své výhody a nevýhody. RGB popisuje barvy podobně jako stroje, tj. jak intenzivně má svítit která barevná složka každé z LEDek. HSV naopak popisuje barvy podobně, jako lidé a je v mnoha případech pohodlnější k použití, např. pro změnu barvy při zachování jasu.

Pomocí komentářů si v následujícím kódu vyberte jednu z definic barvy `cervena` a ověřte, že výsledkem je stejná červená barva.
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();

    ColorRGB cervena = {255, 0, 0};
    ColorHSV cervena = {0, 1, 1};
    ToMat.display.setLED(0, 0, cervena);
}

void loop() {}
```

<!-- _________________________________________________________________ -->
# <a name = tlacitka>Tlačítka</a>
Nejjednodušším způsobem, jak můžete Time-O-Mat ovládat je pomocí tlačítek, která najdete na levé straně krabičky. Pro zjištění jestli je tlačítko zmáčknuto, budeme používat příkaz `ToMat.buttonRead(int buttonID)`. Parametrem `buttonID` určujeme, na které tlačítko se ptáme. Tlačítka jsou číslována od 0 (blíže USB) po 2 (dále od USB).

Příklad: Tento program rozsvítí LED při stisku tlačítka 0.
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    if(ToMat.buttonRead(0)) {
        ToMat.display.setLED(0, 0, white);
    }
    else {
        ToMat.display.setLED(0, 0, black);
    }
    delay(20);
}
```

<!-- _________________________________________________________________ -->
# <a name = piezo>Piezoakustický měnič</a>
## Základy
Time-O-Mat obsahuje tzv. piezoakustický měnič, pomocí kterého dokáže vydávat zvuk.

* Stálý tón zapneme pomocí `ToMat.piezo.tone(uint16_t freq);`, kde `freq` je freqence v Hz.
* Veškerý zvuk vypneme pomocí `ToMat.piezo.stop();`.

Následující příklad přerušovaně "pípá" na frekvenci 1kHz.
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    ToMat.piezo.tone(1000);
    delay(500);
    ToMat.piezo.stop();
    delay(500);
}
```

## Melodie
Time-O-Mat zvládá i jednoduché melodie. Jen pamatujte na to, že nedokáže hrát více tónů zároveň.
Pro spuštění melodie budeme používat `ToMat.piezo.playMelody(melodie);`.

### Melodie z Arduino songs
Asi nejjednoduším způsobem, jak přehrát melodii, je stáhnout ji z https://github.com/robsoncouto/arduino-songs.
Tam si najděte melodii, otevřte ji a zkopírujte `int melody[] = { ...` a `int tempo = ...`.
Melodii poté přehrajete pomocí `ToMat.piezo.playMelody(melody, sizeof(melody)/sizeof(melody[0]), tempo);`

Následující příklad zahraje melodi Nokie.

```
#include "ToMat/ToMat.h"

// Zkopírováno z Arduino songs
int nokieTempo = 180;
int nokieMelody[] = {

  // Nokia Ringtone 
  // Score available at https://musescore.com/user/29944637/scores/5266155
  
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2, 
};

void setup() {
    ToMat.begin();
    ToMat.piezo.playMelody(nokieMelody, sizeof(nokieMelody)/sizeof(nokieMelody[0]), nokieTempo);
}

void loop() {
}
```

### Vlastní melodie
Psaní vlastních melodií je trochu složitější, ale zvládnutelné.

Vlastní melodii budeme zapisovat pomocí klasického notového zápisu, který v našem provedení vypadá následovně (celou melodii musíme psát do uvozovek): 
`Melody nazevMelodie("F5#/8 F5#/8 D5/8 B4/8 R/8*");`

Každá nota se skládá ze dvou částí.
* Před lomítkem se udává výška noty. `#` zvedá notu o 1/2 noty. `R` znamená pauza.
* Za lomítkem se udává délka noty. `*` prodlužuje notu o půlku.
    * `1` -> celá nota
    * `8` -> 1/8 celé noty
    * `2*` -> 1/2 + 1/4 -> 3/4 celé noty

#### Tempo
Vlastní melodii musíme nastavit i tempo. To se udává v BPM (beats per minute), nebo-li počet čtvrtnot za minutu.
Tempo lze nastavit dvěma způsoby.

Při definici melodie: 
```
Melody nazevMelodie("TEMPO=180 F5#/8 F5#/8 D5/8 B4/8 R/8*");
```

Nebo později:
```
Melody nazevMelodie("F5#/8 F5#/8 D5/8 B4/8 R/8*");
nazevMelodie.tempo = 180;
```
Ale pozor! `nazevMelodie.tempo = 180;` lze volat pouze uvnitř funkce (`void setup()`, `void loop()`, ... ). Proto doporučuji spíše první způsob.

#### Přehrání
Vlastní melodii přehrajeme pomocí `ToMat.piezo.playMelody(nazevMelodie);`.

Příklad:
```
#include "ToMat/ToMat.h"

Melody melodyTest("TEMPO=180 c3/4 d3/4 e3/4 f3/4 g3/4 g3/4 a3/4 h3/4 c4/2* c4#/1*");

void setup() {
    ToMat.begin();
	ToMat.piezo.playMelody(melodyTest);
}

void loop() {
}
```

## Další funkce ToMat.piezo
`ToMat.piezo.getState();` vrací aktuální stav.
* `0` -> nic nehraje
* `1` -> stálý tón
* `2` -> hraje melodie

<!-- _________________________________________________________________ -->
# <a name = fotorezistory>Fotorezistory</a>

Pro snímání úrovně osvětlení v okolí Time-O-Mat slouží fotorezistory. Hodiny jsou osazeny dvěma fotorezistory:
* Fotorezistor ID 0 je umístěn na horní straně krabice.
* Fotorezistor ID 1 je umístěn na zadní straně krabice.

Pro zjištění úrovně osvitu jednotlivých fotorezistorů použijeme příkaz `ToMat.illumination.getRaw(int photoresID);`, kde `photoresID` udává index fotorezistoru. Vrácena je nám celočíselná hodnota v rozsahu 0 (tma) až 4095 (světlo).

Následující příklad zjistí hodnotu osvitu fotorezistoru 0 a nastaví podle něj jas LEDky.
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    int osvit = ToMat.illumination.getRaw(0);
    ColorRGB barva = {osvit/16, 0, 0};
    ToMat.display.setLED(0, 0, barva);
    delay(20);
}
```

<!-- _________________________________________________________________ -->
# <a name = lista>Dotyková lišta</a>

Pro detekci doteku prstu na horní dotykové liště použijeme příkaz `ToMat.touchBar.getPressed(int buttonID);`, kde `buttonID` udvává index dotykového tlačítka. Tlačítka jsou číslována od 0 (vlevo) po 7 (vpravo). Vrácena je binární hodnota 0 (nezmáčknuto) nebo 1 (zmáčknuto).

Následující příklad rozsvítí LED při zmáčknutí levého dotykového tlačítka (0).
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    if(ToMat.touchBar.getPressed(0)) {
        ToMat.display.setLED(0, 0, white);
    }
    else {
        ToMat.display.setLED(0, 0, black);
    }
    delay(20);
}
```

<!-- _________________________________________________________________ -->
# <a name = teplomer>Teploměr</a>

Pro zjištění teploty v okolí Time-O-Mat pomocí senzoru DS18B20 použijeme příkaz `ToMat.getTemperature();`. Vráceno je desetinné číslo reprezentující teplotu ve stupních Celsia.

Následující příklad zjistí teplotu, uloží je do proměnné `teplota` a rozsvítí červenou LED pokud je vyšší než 25.
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
}

void loop() {
    int teplota = ToMat.getTemperature();
    if(teplota > 25.0) {
        ToMat.display.setLED(0, 0, red);
    }
    else {
        ToMat.display.setLED(0, 0, black);
    }
    delay(200);
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
* %d - (decimal) označuje proměnnou pro ukládání celých čísel, například `3`.
* %f - (float) označuje proměnnou pro ukládání desetinných čísel, například `3.14`.
* %c - (char) označuje jeden textový znak, například `'c'` označuje znak *c*.
* %s - (string) označuje řetězec textových znaků -> řetězec se ohraničuje uvozovkami, například `"Ahoj svete"`.

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
# <a name = displej>Displej a podsvícení</a>
Pro ovládání LEDek na displeji a na zadním podsvícení je možné použít i schopnější funkce než `.setLED()`, která umí ovládat pouze jednu LEDku.

Pro rosvícení celého segmentu ledek jedním příkazem je možné použít konstrukci `ToMat.display.setSegment(int segmentID, ColorRGB color);`. Jedná se o volání funkce s parametry v kulatých závorkách:
* `segmentID` který segment (úsek LEDek) chceme ovládat. Odpovídají rozdělení jako u funkce `.setLED()`.
* `color` udává, jakou barvou má daný segment svítit.

Pro rozsvícení několika vybraných segmentů jedním příkazem použijeme konstrukci `ToMat.display.ssetSegments(SegmentSelector selector, ColorRGB color);`. Jedná se o volání funkce s parametry v kulatých závorkách:
* `selector` který definuje skupinu segmentů, které mají svítit. 
* `color` udává, jakou barvou mají dané segmenty svítit.

Parametr `selector` zde nabývá následujících hodnot:
* `all` - Svítí všechny LED.
* `frontlight` - Svítí všechny LED na předním panelu.
* `backlight` - Svítí všechny LED na zadním LED pásku.
* `digits` - Svítí všechny LED v digitech.
* `colon` - Svítí obě LED ve dvojtečce.

Pro definování vlastní kombinace pro rozsvícení více segmentů jedním příkazem použijeme kontrukci podobnou vytváření proměnných `SegmentSelector vyber = {0, 0, 0, 0, 0, 0};` Ve výčtu hodnota `0` udává, že daný segment nemá být rozsvícen a hodnota `1`, že daný digit má být rozsvícen. Hodnoty jsou ve stejném pořadí segmentů, jako je použito ve funkci `.setLED()`. 

Následující příklad nejdříve vybere 2 krajní digity s dvojtečkou a následně je rozsvítí červenou barvou.
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
    SegmentSelector vyber = {1, 0, 1, 0, 1, 0};
    ToMat.display.setSegments(vyber, red);
}

void loop() {}
```

Zobrazit znak na 1 digit z předního displeje je možné pomocí konstrukce `ToMat.display.setChar(int charID, char character, ColorRGB color);`. Jedná se o volání funkce s parametry v kulatých závorkách:
* `charID` udává, který digit chceme ovládat. Jsou číslovány od 0 (vlevo) po 3 (vpravo).
* `character` udává, jaké písmeno se má na digitu zobrazit. Hodnotou může být např. `"A"`.
* `color` udává, jakou barvou má daná LED svítit.

Konstrukce `ToMat.display.setText(String text, ColorRGB color);` slouží k nastavení všech 4 digitů na text definovaný v parametru `text` (typ String). Zobrazí se pouze první 4 písmena z parametru `text` a rozsvítí se barvou z parametru `color`.

Konstrukce `ToMat.display.setBrightness(SegmentSelector selector, float brightness);` nastaví jas všech LEDek na vybraných segmentech. Všechny následující příkazy nastavující barvu LEDek vybraných segmentů budou nastavovat barvu se sníženým jasem. Jedná se o volání funkce s parametry v kulatých závorkách:
* `selector` udává výběr segmentů pro provedení nastavení.
* `brightness` nastavuje hodnotu jasu v rozsahu 0 (nesvítí vůbec) po 1 (svítí naplno).

Konstrukce `setTransition(SegmentSelector selector, TransitionType aTransitionType, float aTransitionRate);` slouží k nastavení přechodových animací, např. pro nastavení plynulých přechodů mezi různými stavy rozsvícení. Jedná se o volání funkce s parametry v kulatých závorkách:
* `selector` udává výběr segmentů pro provedení nastavení.
* `aTransitionType` udává druh přechodové animace. Možnosti jsou `Linear` a `Exponential`, kde 2. varianta je vizuálně přirozenější.
* `aTransitionTime` udává dobu trvání přechodové animace ve vteřinách. Např. `1.0` odpovídá přechodu plného rozsahu z tmy až do plného bílého svitu přechodem trvajícím 1 vteřinu.

Následující příklad nastaví jas předního displeje na `0.5`, plynulý přechod s rychlostí `2.0` a zobrazí červeně slovo `AHOJ` na předním displeji.
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
    ToMat.display.setBrightness(front, 0.5);
    ToMat.display.setTransition(front, linear, 2.0);
    ToMat.display.setText("AHOJ", red);
}

void loop() {}
```

Jas LED je shora omezen maximálním elektrickým proudem, který je možné udebírat z USB nabíječky. Proto nemusí být vždy možné dosáhnout plného jasu všech LED. USB-C nabíječky umožňují automatické zjištění maximálního dodávaného proudu, což Time-O-Mat podporuje. V standardním nastavení je zjišťování proudového limitu nabíječky automatické. Režim omezení odebíraného proudu je však možné nastavit i manuálně pomocí funkce `ToMat.power.setMode(PowerMode mode)`, kde parametr `mode` nabývá hodnot:
* `USB2_500mA` - Omezení proudu na 500mA
* `USB3_900mA` - Omezení proudu na 900mA
* `Medium_1500mA` - Omezení proudu na 1500mA
* `High_3000mA` - Omezení proudu na 3000mA
* `Automatic` - Automatické nastavení

Tuto funkci stačí zavolat pouze jednou a to umístěním do funkce `setup()`.

<!-- _________________________________________________________________ -->
# <a name = wifi>WiFi</a>
Pro spuštění WiFi a ovládací webové aplikace slouží funkce `ToMat.startWiFiCaptain("<your_name>")`. Po jejím zavolání bude postaráno o vytvoření WiFi přístupového bodu (AP) v Time-O-Mat a také o připojní k externí WiFi, jakmile má Time-O-Mat správné přihlašovací údaje a je v dosahu. Také je spuštěn server hostující webovou aplikaci pro dálkové ovládání Time-O-Mat.

<!-- _________________________________________________________________ -->
# <a name = prikazy>Vzdálený příkazový řádek</a>
Pro dálkové ovládání Time-O-Mat můžete použít i textové příkazy. Ty budete zadávat do pole *Command entry* na webové stránce dálkového ovládání. Po stisku tlačítka *Enter* (funguje i na klávesnici) je zadaný příkaz odeslán do Time-O-Mat. K použítí přijatého příkazu budeme používat následující funkce:
* `ToMat.commandGet()` - vrací textový řetězec (proměnnou typu *String*) obsahující aktuálně přijatý příkaz.
* `ToMat.commandGetIndexed(index)` - vrací textový řetězec obsahující jedno slovo z přijatého příkazu. Slova jsou oddělena mezerami a číslována od 0.
* `ToMat.commandClear()` - vymaže obsah celého aktuálně přijatého příkazu.

Příklad: Následující program blikne LED po obdržení příkazu "blink":
```
#include "ToMat/ToMat.h"

void setup() {
    ToMat.begin();
    ToMat.startWiFiCaptain("<your_name>");
}

void loop() {
    if(ToMat.commandGet() == "blink") {
        ToMat.display.setLED(0, 0, white);
        delay(500);
        ToMat.display.setLED(0, 0, black);
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