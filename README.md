# (Non) Gravitar

Gravitar è un gioco arcade a colori pubblicato da Atari nel 1982. Questa è una versione semplificata nella quale non è presente l'effetto della gravità.
Il progetto è stato conseguito a compimento del corso di programmazione del primo anno di studio di scienze informatiche presso l'università di Bologna.

## Funzionamento

Il funzionamento del gioco è il seguente:
Il giocatore controlla una navicella che può muovere utilizzando i tasti W A S D, consumando carburante.
Il gioco inizia in una visuale universo, in questa visuale sono presenti dei pianeti su cui il giocatore può "atterrare" colpendo con la navicella il pianeta.
Il gioco cambia dunque dalla visuale universo alla visuale mondo, in questa visuale viene generato casualmente il terreno e su questo terreno sono presenti Bunker che il giocatore deve distruggere e Fuel che il giocatore deve raccogliere.
Per distruggere i Bunker il giocatore può sparare utilizzando il tasto SPAZIO e per raccogliere il fuel può utilizzare il tasto B.
Nella visuale mondo andando a destra/sinistra dello schermo si genera la schermata successiva/precedente, il numero delle schermate è leggibile in alto a sinistra dello schermo.
Il giocatore può uscire da un pianeta in qualsiasi momento dirigendosi verso l'alto della finestra.
Una volta distrutti tutti i bunker in ogni schermata di un pianeta il giocatore uscendo dal pianeta distrugge il pianeta, distrutti tutti i pianeti ne vengono generati altri finchè il gioco non termina.
Il gioco termina quando la vita del giocatore scende a zero oppure quando esaurisce il carburante.

## Installazione
Il gioco utilizza oltre alle librerie standard C/C++ la libreria grafica SFML che può essere installata tramite il comando:
sudo apt-get install libsfml-dev.
Per generare il MakeFile del gioco occorre utilizzare il programma CMAKE e inserire in "where is the source code" il percorso della cartella contenente questo readme, e in "where to build the binaries" il percorso di dove si vuole  generare l'eseguibile.
Copiare poi la cartella Media dove si è "installato" il gioco e compilare tramite il comando make.
Il gioco puo essere eseguito eseguendo ./Gravitar

## Comandi
W A S D  --   movimento\\n
Spazio   --   sparare\\n
B        --   raggio traente\\n

## Licenza
Il software è distribuito sotto licenza MIT.
