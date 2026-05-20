# Font
Tato složka obsahuje skripty pro **vytváření a použití českého bitmapového fontu** v STM32CubeIDE. 

## [bdf-converter.py](./bdf-converter.py)
Konvertuje libovolný font ve formátu `.bdf` na soubor `.c`, který lze použít v STM32CubeIDE. 

### Použití
```bash
python3 bdf-converter.py input.bdf [output.c] [font_name]
```

### Zdroje
 - [DeepSeek](https://chat.deepseek.com/) - Generování kódu
 - Chyby v kódu opraveny týmem Pentagon

# Použití diakritiky
Vzhledem k tomu, že **STM32CubeIDE nepodporuje enkódování ISO-8859-2**, je pro zobrazení diakritiky a speciálních znaků potřeba text **převést do hexadecimálního formátu**. To obstarává skript [text-to-array.py](./text-to-array.py) (viz níže). 

## [text-to-array.py](./text-to-array.py)
Konvertuje **text na C array** s hexadecimálními hodnotami představujícími znaky ve formátu ISO-8859-2. 

### Použití
```bash
python3 text-to-array.py "your text here" [array_name]
```

### Zdroje
 - [DeepSeek](https://chat.deepseek.com/) - Generování kódu