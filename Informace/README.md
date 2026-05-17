> [!IMPORTANT]
> ### Stanice `MMPa meteo` se momentálně skládá ze dvou desek.
> **Deska vnější** je vybavena sensory, ze kterých po intervalech čte data a technologií [LoRa](/Informace/README.md#komunikace) je posílá desce vnitřní.  
> **Deska vnitřní** data přijímá z desky vnější, ukazuje je uživateli a zapisuje do SD karty.

> [!TIP]
> Projekt je budován tak, aby naplnil [základní kompetenční ustanovení](Informace/zakladni-kompetecni-listina.md).  
> Projekt při operaci musí naplňovat stanovení **MVP** (**M**inimum **V**iable **P**roduct), označeno ⁕.

## Složení stanice
`[`Ozávorkované`]` body čekají na implementaci.  
```mermaid
ishikawa-beta
    MMPa assembly
    Senzory
        [Akustický anemometr]
          rychlost větru
        BME280
          teplota
          relativní vlhkost
          tlak
        [osvětlení]
        [akcelerace (zemětřesení)]
    Komunikace
        Wireless
          LoRa
          [Bluetooth]
        Wired
          [RS-422]
          [RS-485]
    User
        INPUT
            Rotační enkodér
        OUTPUT
            Displej
            SD karta
    +
      GPS
```
> [!TIP]
> Pokud jsi **nováček**, doporučujeme přečíst [Pojmy & zkratky](/Informace/pojmy-zkratky).
### Senzorová soustava
|     Veličina    ||       Senzor        |       Vstup       |      Výstup      |
|:---------------:|:-:|:---------------------:|:-----------------:|:----------------:|
||||||
| Vítr - rychlost ||  Akustický anemometr dvouosý  | 2x zvuková křivka |        $\text{ms}^{-1}$       | 
|   Vítr - směr   ||  Akustický anemometr dvouosý  | 2x zvuková křivka |      $\degree$      |
|     Teplota     |⁕|         BME280        |   Binární data   |     $\textdegree C$    |
|     Vlhkost     |⁕|         BME280        |   Binární data   |     %     |
|       Tlak      |⁕|         BME280        |   Binární data   |     $\text{MPa}$   |
|       Čas       |⁕|         GPS           |      LoRa        |   $\text{ms}$    |
|   Zemětřesení   ||  Akcelerometr LIS3DH  |      *TBD*       |  st. zemětřesení  |
|   Světlo        ||     2 diody BPW34S    |      Analog.     | oblačnost |
#### BME280
BME je modul měříci teplotu, vlhkost vzduchu a tlak okolí. K desce je připojen přes **SPI**.
##### Pocitová teplota
K teplotě ještě řadíme **pocitovou teplotu**, kterou získáme ze vzorce, přičemž potřebujeme hodnotu:
 - reálné teploty
 - rychlosti větru
 - vlhkosti vzduchu

Možné vzorce pro použití:
- [AAT](https://en.wikipedia.org/wiki/Apparent_temperature)  (australský systém, navržen pro celoroční výpočty)
- [Wind Chill](https://en.wikipedia.org/wiki/Wind_chill)  (kanadský standard, navržen pro nižší teploty cca do 10°C)
- [Heat Index](https://en.wikipedia.org/wiki/Heat_index) (pro teplejší počasí nad 27°C s vlhkostí nad 40%)

>[!NOTE]
>Vzorce jsou hlavně určené pro měření ve **stínu**.  
>Lze použít více vzorců pro různá období.  
  
#### Osvětlení
Pro detekci osvětlení se používají dvě fotodiody [BPW34S](https://look.ams-osram.com/m/1f206a499ac1f0b2/original/BPW-34-S.pdf). Jejich výstupy budou zavedeny do MCU jako kanály nízkofrekvenčního ADC
Každá fotodioda je sériově připojena k resistoru s odporem $R$ a k němu paralelně operačnímu zesilovači.
- **Denní osvětlení** vrací dioda `D800`, na kterou navazuje se zesilovačem odpor $R = 10 \text{ k}\Omega$, dokážeme s ní tedy zachycovat makroskopické měřítko s přesností pro denní svit dostatečnou.
- **Noční osvětlení** (světelný smog) vrací dioda `D801`, kde $R = 1 \text{ M}\Omega$, lze s ní receptovat malé rozmezí s velmi velkou přesností.
Spoluprácí obou diod dokážeme optimálně pokrýt celé reálné světelné rozmezí.

Viz. [schéma](/Schema/schema.pdf).

### Komunikace

| Typ komunikace || Rychlost            | Dosah  |
|----------------|-|---------------------|--------|
| [LoRa](https://cs.wikipedia.org/wiki/LoRa)|⁕| 11 $\text{bps}$ - 203 $\text{kbps}$   | 4.8 $\text{km}$ |
| 2.4 $\text{GHz}$ Wi-Fi  || 450 $\text{Mbps}$ - 600 $\text{Mbps}$ | 36 $\text{m}$   |
| 5 $\text{GHz}$ Wi-Fi    || 1.3 $\text{Gbps}$            | 12 $\text{m}$   |
|   [Bluetooth](https://cs.wikipedia.org/wiki/Bluetooth)|| dle verze (max 24 $\text{MBps}$)| dle verze (max 100 $\text{m}$)|

> [!NOTE]
> Jde pouze o přibližné hodnoty, skutečný dosah a rychlost budou omezeny rychlostí mikrokontroléru, rušením signálu a typem prostředí. 
