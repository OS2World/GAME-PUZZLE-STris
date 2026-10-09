:userdoc.
:title.Guida di STris
:docprof toc=12.
:h1 res=1000.Generale
:p.STris &eg. un clone di Tetris per OS/2 Presentation Manager, scritto in origine da Rene Straub (1995-1996).
:p.Pezzi di quattro blocchi cadono nel campo di gioco. Spostateli e ruotateli per riempire righe orizzontali complete. Una riga completa scompare e d&ag. punti. La partita finisce quando non c'&eg. pi&ug. spazio per un nuovo pezzo.
:p.Il menu Guida contiene Come giocare, Tasti e Opzioni; F1 funziona nelle finestre di dialogo.
:p.:link reftype=hd res=4000.Come giocare:elink.
:p.:link reftype=hd res=4100.I tasti:elink.
:p.:link reftype=hd res=11000.Opzioni:elink.
:p.:link reftype=hd res=2200.Informazioni su STris:elink.
:h1 res=4000.Come giocare
:p.Guidate i pezzi che cadono in modo che riempiano righe orizzontali. Eliminare pi&ug. righe insieme d&ag. pi&ug. punti. Anche iniziare da un livello pi&ug. alto o con velocit&ag. maggiore d&ag. pi&ug. punti.
:p.Il pezzo si controlla con i tasti elencati in Tasti. Col procedere del gioco i pezzi cadono pi&ug. velocemente.
:p.Scegliete Inizia partita (Ctrl+N) per cominciare. Pausa (Ctrl+P) ferma il gioco, Termina partita (Ctrl+Q) chiude la partita in corso ed Esci (Ctrl+X) chiude il programma.
:h1 res=4100.I tasti
:p.Questi sono i tasti predefiniti. Si possono cambiare nella finestra Definisci tasti (menu Opzioni).
:table cols='26 22 10' rules=both frame=box.
:row.:c.:hp2.Funzione:ehp2.:c.:hp2.Tasto:ehp2.:c.:hp2.Bloc Num:ehp2.
:row.:c.Sposta a sinistra:c.Cursore sinistra:c.4
:row.:c.Sposta a destra:c.Cursore destra:c.6
:row.:c.Ruota:c.Cursore su:c.8
:row.:c.Scendi pi&ug. veloce:c.Cursore gi&ug.:c.2
:row.:c.Pausa:c.Pausa o Ctrl+P:c. 
:etable.
:p.Per usare il tastierino numerico deve essere attivo Bloc Num. La rotazione nell'altro verso non ha un tasto predefinito; assegnatene uno in Definisci tasti.
:p.:hp2.Scorciatoie:ehp2.
:table cols='12 50' rules=both frame=box.
:row.:c.Ctrl+N:c.Nuova partita (ignorato se una partita &eg. in corso)
:row.:c.Ctrl+P:c.Pausa / riprendi
:row.:c.Ctrl+Q:c.Termina la partita in corso (ignorato senza partita)
:row.:c.Ctrl+X:c.Esci dal programma
:row.:c.Ctrl+B:c.Esecuzione in background s&ig./no
:row.:c.Ctrl+F:c.Controlli della cornice s&ig./no
:etable.
:h1 res=11000.Opzioni
:p.La finestra delle impostazioni e il menu Opzioni modificano il gioco. Tutto viene salvato all'uscita se Salva impostazioni all'uscita &eg. selezionato.
:parml tsize=22 break=none.
:pt.Velocit&ag.
:pd.Velocit&ag. iniziale di caduta dei pezzi.
:pt.Livello iniziale
:pd.Ogni livello inizia con una riga in pi&ug. riempita a caso.
:pt.Suono
:pd.Effetti sonori s&ig./no. Disattivato se non c'&eg. audio disponibile.
:pt.Griglia
:pd.Griglia nel campo di gioco, utile per lasciar cadere i pezzi.
:pt.Pezzo successivo
:pd.Mostra il pezzo successivo.
:pt.Resta in pausa
:pd.Mantiene la pausa quando la finestra riprende il focus.
:pt.Tavolozza
:pd.Seleziona una mappa di colori.
:pt.Colore pieno
:pd.Usa solo colori pieni (schermi a 16 colori).
:pt.Iniziare con quadretti extra
:pd.Riempie in basso righe casuali&colon. tante quante indica il livello iniziale, 4 se &eg. 0. Disattivato = campo vuoto.
:pt.Dettaglio
:pd.Dettaglio di disegno alto, medio o basso.
:pt.Lingua
:pd.Lingua dell'interfaccia e della guida (inglese, spagnolo, olandese, tedesco, francese, italiano).
:pt.Esecuzione in background
:pd.Se selezionato, il gioco continua quando STris non &eg. la finestra attiva. Altrimenti va in pausa da solo.
:pt.Controlli della cornice
:pd.Mostra o nasconde barra del titolo e menu (gioco senza bordi). La finestra si ridimensiona da sola.
:pt.Salva impostazioni all'uscita
:pd.Salva le impostazioni in STris.cfg all'uscita. Attivo per impostazione predefinita.
:eparml.
:h1 res=12000 hide.Classifica
:p.La hall of fame dei migliori giocatori.
:h1 res=13000 hide.Inserisci nome
:p.Avete ottenuto un punteggio da hall of fame. Scrivete il vostro nome nel campo.
:h1 res=14000 hide.Definisci tasti
:p.Selezionate la funzione di cui volete cambiare il tasto premendo il suo pulsante, poi premete il nuovo tasto. Esc annulla. Alcuni tasti non sono utilizzabili; un messaggio vi avvisa.
:p.Il pulsante Predefiniti ripristina i tasti standard.
:h1 res=2200.Informazioni su STris
:p.STris 1.50 per OS/2, ArcaOS ed eComStation.
:p.Autore originale&colon. Rene Straub (1995-1996).
:p.Port su Open Watcom 2.0&colon. comunit&ag. OS2World (2026).
:p.Licenza&colon. GNU General Public License v3. Vedere LICENSE.txt.
:p.:link reftype=hd res=6000.Novit&ag. della 1.50:elink.
:h1 res=6000.Novit&ag. della 1.50
:ul compact.
:li.Portato su Open Watcom 2.0.
:li.Menu&colon. Gioco, Opzioni (con Lingua), Guida; scorciatoie standard.
:li.Sei lingue per interfaccia e guida.
:li.Esecuzione in background, Controlli della cornice, Salva impostazioni all'uscita.
:li.La pausa viene tolta alla fine della partita.
:eul.
:euserdoc.
