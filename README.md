# RS015-potapanje-brodova

Klasična igra potapanja brodova u dvoje igrača preko servera.

## Server

Server je baziran na [cppresdsdk](https://github.com/Microsoft/cpprestsdk/) biblioteci. Komunikacija ide preko
standardnih HTTP GET zahteva. Autentifikacija klijenata se radi uz pomoć `username`/`secret` para, gde se `secret`
dobija  od servera pri registraciji. Server vodi računa o korisnicima i igrama (kreiranje, izvršavanje poteza,
brisanje neaktivnih igrača i igara).

### Build

Server se kompajlira koristeći CMake:

`mkdir build`

`cd build`

`cmake ../`

`cmake --build . --target WebServer`

## Klijent

Klijent je baziran na Qt tehnologiji. Za komunikaciju sa serverom je takođe korišćena
[cppresdsdk](https://github.com/Microsoft/cpprestsdk/) biblioteka.

### Build

Za build se preporučuje korišćenje Qt Creator programa.