# BlockChain

## Version 0.1

![image](https://user-images.githubusercontent.com/12825358/71241242-d13ce080-2313-11ea-9f6f-e0bcf38b4c3f.png)

### Bloko saugomi duomenys:
- Prieš tai einančio blocko hashas
- Esamo bloko išminintas hashas
- Time stampas (diena, mėnesis, diena, laikas, metai)
- Versija (Version1)
- Merkel tree (pildomas tik v0.3)
- Nonce
- Difficulty target (nulių kiekis hasho priekyje)
- Transactions (dabar programa atvaizduoja kiek transakcijų yra bloke)

## Version 0.2

![image](https://user-images.githubusercontent.com/12825358/71241653-d2224200-2314-11ea-8c18-82c5b8badd18.png)

Iš 1000 transakcijų tik 604 gautos tesingos (t.y. siuntėjo turimas balansas nėra mažesnis už siunčiamą sumą. Visos neteisingos transakcijos buvo ištrintos).


![image](https://user-images.githubusercontent.com/12825358/71241913-64c2e100-2315-11ea-81b7-a41ad43c50f5.png)

Jei po transakcijų apdorojimo transakcijų skaičių dalinant iš bloko talpinamo transakcijų skaičiaus liekana nėra lygi nuliui, tai paskutinio bloko transakcijų skaičius lygus tai liekanai (šiuo atveju liko 4 nepriskirtos transakcijos, todėl jos buvo sudėtos į paskutinį bloką).

## Version 0.3

![image](https://user-images.githubusercontent.com/12825358/71242191-19f59900-2316-11ea-84c1-87892aa266f9.png)

Kuriamas Merkle hashas. Buvo naudotas create_merkle pateiktas pavyzdys, tik tais adaptuotas, kad gražintų std::string reikšmę.

![image](https://user-images.githubusercontent.com/12825358/71242374-7eb0f380-2316-11ea-9bb5-f63bf50e3f77.png)

Merkle hashas priskiriamas kiekvienam blokui.
