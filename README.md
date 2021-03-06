# Engine for text based RPG (gamebook) 
Programming and Algorithmics 2 course at FIT CTU (2019/2020).

Detailed description is written only in Czech.

## Engine pro textové RPG

Autor: Lukáš Paukert

## Téma z ProgTestu:
Naprogramujte engine pro textové RPG (gamebook)

Váš engine:
1. ze souboru nahraje definici světa (lokace, přechody mezi lokacemi, události, rozhovory, věci, příšery, ...)
2. umožní vytvořit herní postavu (její atributy a schopnosti) a následnou hru
3. implementuje jednoduchý soubojový systém a inventář
4. umožňuje ukládat a načítat rozehrané hry
5. umožňuje interakci světa volitelným způsobem (volba u nabídky, klíčova slova ala Zork nebo Albion, ...)

Kde lze využít polymorfismus? (doporučené)
- Soubojové vlastnosti: postava, příšera, stroj (např. past, bomba,...)
- Efekty akcí: souboje, události (pád ze stromu,...), přechod do jiné místnosti
- Inventář: postava, batoh (slouží jako věc i inventář zároveň), toulec, kapsa

Další informace:
- https://cs.wikipedia.org/wiki/Gamebook
- https://www.projectaon.org/en/Main/Books

## Zadání
Vytvořím engine pro textové RPG (gamebook). Engine po spuštění umožní načíst definici nového světa nebo nabídne načtení již rozehrané hry. Při vybrání možnosti načíst rozehranou hru ze souboru se hra nastaví do stejného stavu, jako byla, když byl tento "save" vytvořen. V druhém případě, tj. po vybrání načtení nového světa ze souboru se hra nastaví do stavu, jaký určil samotný autor hry. Následně bude hráč vyzván, aby si vytvořil svého hrdinu, respektive mu rozdělil dovednostní body mezi jeho schopnosti (síla, štěstí, životy).

Každý hráč bude mít svůj inventář, který bude mít omezenou kapacitu. Během hry bude mít hráč možnost sbírat itemy, které mohou ovlivňovat sílu útoku (buď item hráči zvyšuje sílu nebo mu může přidávat štestí na udělení kritického zásahu).

Samotná hra se bude skládat z kolekce lokací, na každé z nich je hráči vždy zobrazen nějaký text (příběh) a pod ním bude zobrazena nabídka, z níž si hráč musí vybrat nějakou možnost. Možnosti budou moci být jednoho z následujících typů:
1) Přechod na jinou lokaci
2) Souboj s nepřítelem
3) Přidání nového itemu do inventáře
4) Zobrazení inventáře
5) Uložení rozehrané hry

Hráč vyhrál, pokud se dostane do cílové lokace, kterou nastavil autor hry.

### Popis soubojového systému:
Souboj mezi hráčem a nepřítelem probíhá v těchto fázích:
1) Hráč útočí, nepřítel se brání
2) Nepřítel útočí, hráč se brání

Tyto fáze se střídají do té doby, dokud jeden z účastníků souboje neumře.

**Hráč:**
Při útoku je hráči zobrazena jednoduchá matematická rovnice a pokud správně určí výsledek, je síla jeho útoku dvojnásobná. Pokud má hráč štěstí, může udělit tzv. kritický zásah, tj. síla útoku je násobena ještě dvěma! V případě, že je na hráče veden útok, tak opět odpovídá na matematickou rovnici. Správná odpověď znamená snížení síly útoku na polovinu.

**Monstrum:**
Síla útoku monstra je vždy stejná jako jeho `m_Strength`. Monstrum se brání vygenerováním náhodného čísla z intervalu ⟨0.5;1⟩, kterým je útok, jenž je na něj vedený, vynásoben. 

**Čaroděj:**
Útok čaroděje je pro soupeře zatím velkou neznámou, a proto se proti němu nedokáží bránit. Síla útoku je stejná jako jeho `m_Strength`. Čaroděj se na druhou stranu však sám nedokáže útokům nijak bránit.

Pokud hráč souboj vyhrál, zůstává na stejné lokaci, získá odměnu za zneškodnění nepřítele a hra pokračuje dále. V opačném případě hra končí a hráči je nabídnut návrat do hlavní nabídky.

## Kde mám polymorfismus?
Polymorfismus využívám u třídy `CEntity`, ta má dvě virtuální metody pro souboj (`attack` a `defend`), které každá z entit (`CPlayer`, `CMonster` a `CWizard`) implementuje různým způsobem (podrobné informace jsou v sekci popis soubojového systému).

Samotné polymorfní volání mám ve třídě `CPlayer`, kde z metody `attack` volám metodu `defend` u oponenta. Ten v tomto případě může být buď třídy `CMonster` nebo `CWizard`. Jak je již zmíněno výše, každý z nich si tuto metodu implementuje svým vlastním způsobem. Toto řešení usnadňuje případné rozšíření enginu o další typy oponentů.
