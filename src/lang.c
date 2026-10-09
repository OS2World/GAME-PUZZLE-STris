/*******************************************************************************
*                                                                             *
* LANG.C                                                                      *
* ------                                                                      *
*                                                                             *
* Language strings for STris. ASCII only (ae/oe/ue instead of a/o/u with      *
* diacritics) so that the resource is codepage independent. Menu strings      *
* carry a '~' mnemonic character; strings drawn into the window or used as    *
* buttons/dialog labels are plain text.                                      *
*                                                                             *
*******************************************************************************/

#define INCL_WIN
#include <os2.h>
#include <string.h>

#include "stris.h"
#include "window.h"
#include "lang.h"
#include "stris_id.h"

#include "help.h"


/*** Variables ****************************************************************/

int     current_lang = LANG_EN;

char    *lang_strings[LANG_COUNT][NUM_STRINGS] =
{
    /* LANG_EN  ..................................................... */
    {
        "~Game",
        "~New Game\tCtrl+N",
        "~Pause Game\tCtrl+P",
        "~Quit Game\tCtrl+Q",
        "E~xit\tCtrl+X",
        "~Options",
        "~Settings...",
        "Define ~Keys...",
        "~Hiscore...",
        "~Detail",
        "~High",
        "~Medium",
        "~Low",
        "~Language",
        "~Background Run\tCtrl+B",
        "~Frame Controls\tCtrl+F",
        "Save settings on e~xit",
        "~Help",
        "~Using Help",
        "Help ~Index",
        "~Contents",
        "~How to play",
        "~Keys",
        "~About STris...",
        "~English",
        "~Espanol",
        "~Nederlands",
        "~Deutsch",
        "~Francais",
        "~Italiano",
        "Start Game",
        "Stop Game",
        "Hiscore...",
        "Options...",
        "About...",
        "Pause",
        "Hiscore",
        "Score",
        "Lines",
        "Level",
        "New Hiscore",
        "Hall of Fame",
        "Options",
        "Key Bindings",
        "Please enter your name:",
        "These are the best STris players:",
        "No.",
        "Name",
        "Score",
        "Lines",
        "Level",
        "Settings",
        "Difficulty",
        "Sound",
        "Grid",
        "Next Piece",
        "Rotate clockwise",
        "Remain paused",
        "Palette",
        "Solid colors",
        "Speed",
        "Startlevel",
        "Keys",
        "Select the function you wish to change:",
        "Press the new key now...",
        "Press a key to %s, ESC to abort",
        "move the piece leftwards",
        "move the piece rightwards",
        "rotate counter-clockwise",
        "rotate clockwise",
        "drop the piece",
        "Key definition successfully completed.",
        "Key definition aborted.",
        "Key already used. Please try another.",
        "This key is internally used by STris. Please try another.",
        "Sorry. I can't recognize this key. Please try another.",
        "Standard",
        "Red to Yellow",
        "Green to Yellow",
        "Bluescale",
        "Grayscale",
        "Black & White",
        "Congratulations! You are one",
        "of the best STris players.",
        "Do you want to abort the current game?",
        "Start with ~extra squares"
    },

    /* LANG_ES  ..................................................... */
    {
        "~Juego",
        "~Nuevo juego\tCtrl+N",
        "~Pausar juego\tCtrl+P",
        "~Terminar juego\tCtrl+Q",
        "Sa~lir\tCtrl+X",
        "~Opciones",
        "~Ajustes...",
        "Definir ~teclas...",
        "~Puntuaciones...",
        "~Detalle",
        "~Alto",
        "~Medio",
        "~Bajo",
        "~Idioma",
        "~Ejecutar en segundo plano\tCtrl+B",
        "~Controles de marco\tCtrl+F",
        "Guardar ajustes al sa~lir",
        "~Ayuda",
        "~Como usar la ayuda",
        "Ayuda: ~indice",
        "~Contenidos",
        "~Como se juega",
        "~Teclas",
        "~Acerca de STris...",
        "~Ingles",
        "~Espanol",
        "~Neerlandes",
        "~Aleman",
        "~Frances",
        "~Italiano",
        "Iniciar juego",
        "Detener juego",
        "Puntuaciones...",
        "Opciones...",
        "Acerca de...",
        "Pausa",
        "Puntuacion maxima",
        "Puntos",
        "Lineas",
        "Nivel",
        "Nueva puntuacion",
        "Salon de la fama",
        "Opciones",
        "Asignacion de teclas",
        "Escriba su nombre:",
        "Estos son los mejores jugadores de STris:",
        "No.",
        "Nombre",
        "Puntos",
        "Lineas",
        "Nivel",
        "Ajustes",
        "Dificultad",
        "Sonido",
        "Rejilla",
        "Pieza siguiente",
        "Girar en sentido horario",
        "Mantener pausa",
        "Paleta",
        "Colores solidos",
        "Velocidad",
        "Nivel inicial",
        "Teclas",
        "Elija la funcion que desea cambiar:",
        "Pulse la tecla nueva ahora...",
        "Pulse una tecla para %s, ESC para cancelar",
        "mover la pieza a la izquierda",
        "mover la pieza a la derecha",
        "girar en sentido antihorario",
        "girar en sentido horario",
        "soltar la pieza",
        "Definicion de tecla completada.",
        "Definicion de tecla cancelada.",
        "La tecla ya esta en uso. Pruebe otra.",
        "Esta tecla la usa STris internamente. Pruebe otra.",
        "No reconozco esta tecla. Pruebe otra.",
        "Estandar",
        "Rojo a amarillo",
        "Verde a amarillo",
        "Tonos azules",
        "Tonos grises",
        "Blanco y negro",
        "Enhorabuena, usted esta entre",
        "los mejores jugadores de STris.",
        "Quiere abandonar la partida actual?",
        "Empezar con ~casillas extra"
    },

    /* LANG_NL  ..................................................... */
    {
        "~Spel",
        "~Nieuw spel\tCtrl+N",
        "Spel ~pauzeren\tCtrl+P",
        "~Spel beeindigen\tCtrl+Q",
        "~Afsluiten\tCtrl+X",
        "~Opties",
        "~Instellingen...",
        "Toetsen ~definieren...",
        "~Highscore...",
        "~Detail",
        "~Hoog",
        "~Gemiddeld",
        "~Laag",
        "~Taal",
        "~Op de achtergrond spelen\tCtrl+B",
        "~Kaderbediening\tCtrl+F",
        "Instellingen bewaren bij ~afsluiten",
        "~Help",
        "~Help gebruiken",
        "Help-~index",
        "~Inhoud",
        "~Hoe te spelen",
        "~Toetsen",
        "~Over STris...",
        "~Engels",
        "~Spaans",
        "~Nederlands",
        "~Duits",
        "~Frans",
        "~Italiaans",
        "Spel starten",
        "Spel stoppen",
        "Highscore...",
        "Opties...",
        "Over...",
        "Pauze",
        "Highscore",
        "Score",
        "Regels",
        "Niveau",
        "Nieuwe highscore",
        "Eregalerij",
        "Opties",
        "Toetsbindingen",
        "Voer uw naam in:",
        "Dit zijn de beste STris-spelers:",
        "Nr.",
        "Naam",
        "Score",
        "Regels",
        "Niveau",
        "Instellingen",
        "Moeilijkheid",
        "Geluid",
        "Rooster",
        "Volgend blok",
        "Met de klok mee draaien",
        "Gepauzeerd blijven",
        "Palet",
        "Effen kleuren",
        "Snelheid",
        "Startniveau",
        "Toetsen",
        "Kies de functie die u wilt wijzigen:",
        "Druk nu de nieuwe toets...",
        "Druk een toets voor %s, ESC om te annuleren",
        "het blok naar links verplaatsen",
        "het blok naar rechts verplaatsen",
        "tegen de klok in draaien",
        "met de klok mee draaien",
        "het blok laten vallen",
        "Toetsdefinitie voltooid.",
        "Toetsdefinitie geannuleerd.",
        "Toets is al in gebruik. Kies een andere.",
        "Deze toets gebruikt STris intern. Kies een andere.",
        "Ik herken deze toets niet. Kies een andere.",
        "Standaard",
        "Rood naar geel",
        "Groen naar geel",
        "Blauwtinten",
        "Grijstinten",
        "Zwart-wit",
        "Gefeliciteerd, u hoort bij",
        "de beste STris-spelers.",
        "Wilt u het huidige spel afbreken?",
        "Beginnen met ~extra blokjes"
    },

    /* LANG_DE  ..................................................... */
    {
        "~Spiel",
        "~Neues Spiel\tCtrl+N",
        "Spiel ~pausieren\tCtrl+P",
        "~Spiel beenden\tCtrl+Q",
        "~Beenden\tCtrl+X",
        "~Optionen",
        "~Einstellungen...",
        "~Tastatur...",
        "~Highscore...",
        "~Darstellung",
        "~Hoch",
        "~Mittel",
        "~Niedrig",
        "~Sprache",
        "Im ~Hintergrund spielen\tCtrl+B",
        "~Fensterrahmen bedienen\tCtrl+F",
        "Einstellungen beim ~Beenden speichern",
        "~Hilfe",
        "~Hilfe benutzen",
        "~Stichwortverzeichnis",
        "~Inhalt",
        "~Wie man spielt",
        "~Tasten",
        "~Ueber STris...",
        "~Englisch",
        "~Spanisch",
        "~Niederlaendisch",
        "~Deutsch",
        "~Franzoesisch",
        "~Italienisch",
        "Spiel starten",
        "Spiel stoppen",
        "Highscore...",
        "Optionen...",
        "Info...",
        "Pause",
        "Highscore",
        "Punkte",
        "Zeilen",
        "Level",
        "Neuer Highscore",
        "Highscore-Liste",
        "Optionen",
        "Tastenbelegung",
        "Bitte geben Sie Ihren Namen ein:",
        "Das sind die besten STris-Spieler:",
        "Nr.",
        "Name",
        "Punkte",
        "Zeilen",
        "Level",
        "Einstellungen",
        "Schwierigkeit",
        "Ton",
        "Raster",
        "Naechstes Teil",
        "Im Uhrzeigersinn drehen",
        "Pausiert bleiben",
        "Palette",
        "Volle Farben",
        "Geschwindigkeit",
        "Startlevel",
        "Tasten",
        "Waehlen Sie die Funktion, die Sie aendern wollen:",
        "Neue Taste druecken...",
        "Taste fuer %s druecken, ESC zum Abbrechen",
        "das Teil nach links bewegen",
        "das Teil nach rechts bewegen",
        "gegen den Uhrzeigersinn drehen",
        "im Uhrzeigersinn drehen",
        "das Teil fallen lassen",
        "Tastenbelegung erfolgreich uebernommen.",
        "Tastenbelegung abgebrochen.",
        "Taste bereits belegt. Bitte eine andere waehlen.",
        "Diese Taste wird von STris intern benutzt. Bitte eine andere waehlen.",
        "Diese Taste wird nicht erkannt. Bitte eine andere waehlen.",
        "Standard",
        "Rot nach Gelb",
        "Gruen nach Gelb",
        "Blauskala",
        "Grauskala",
        "Schwarz-Weiss",
        "Glueckwunsch, Sie gehoeren zu den",
        "besten STris-Spielern.",
        "Wollen Sie das aktuelle Spiel abbrechen?",
        "Mit ~zusaetzlichen Bloecken starten"
    },

    /* LANG_FR  ..................................................... */
    {
        "~Jeu",
        "~Nouvelle partie\tCtrl+N",
        "~Pause\tCtrl+P",
        "~Terminer la partie\tCtrl+Q",
        "~Quitter\tCtrl+X",
        "~Options",
        "~Reglages...",
        "Definir les ~touches...",
        "~Meilleur score...",
        "~Detail",
        "~Haute",
        "~Moyenne",
        "~Basse",
        "~Langue",
        "~Jouer en arriere-plan\tCtrl+B",
        "~Controles de la fenetre\tCtrl+F",
        "Enregistrer les reglages en ~quittant",
        "~Aide",
        "~Utilisation de l'aide",
        "Aide : ~index",
        "~Sommaire",
        "~Comment jouer",
        "~Touches",
        "~A propos de STris...",
        "~Anglais",
        "~Espagnol",
        "~Neerlandais",
        "~Allemand",
        "~Francais",
        "~Italien",
        "Commencer la partie",
        "Arreter la partie",
        "Meilleurs scores...",
        "Options...",
        "A propos...",
        "Pause",
        "Meilleur score",
        "Score",
        "Lignes",
        "Niveau",
        "Nouveau record",
        "Tableau d'honneur",
        "Options",
        "Affectation des touches",
        "Entrez votre nom :",
        "Voici les meilleurs joueurs de STris :",
        "N.",
        "Nom",
        "Score",
        "Lignes",
        "Niveau",
        "Reglages",
        "Difficulte",
        "Son",
        "Grille",
        "Piece suivante",
        "Tourner dans le sens horaire",
        "Rester en pause",
        "Palette",
        "Couleurs pleines",
        "Vitesse",
        "Niveau de depart",
        "Touches",
        "Choisissez la fonction a modifier :",
        "Appuyez maintenant sur la nouvelle touche...",
        "Appuyez sur une touche pour %s, ECHAP pour annuler",
        "deplacer la piece vers la gauche",
        "deplacer la piece vers la droite",
        "tourner dans le sens antihoraire",
        "tourner dans le sens horaire",
        "laisser tomber la piece",
        "Definition de la touche reussie.",
        "Definition de la touche annulee.",
        "Touche deja utilisee. Essayez-en une autre.",
        "Cette touche est utilisee par STris. Essayez-en une autre.",
        "Je ne reconnais pas cette touche. Essayez-en une autre.",
        "Standard",
        "Rouge vers jaune",
        "Vert vers jaune",
        "Tons de bleu",
        "Tons de gris",
        "Noir et blanc",
        "Felicitations, vous faites partie",
        "des meilleurs joueurs de STris.",
        "Voulez-vous abandonner la partie en cours ?",
        "Commencer avec des ~carres en plus"
    },

    /* LANG_IT  ..................................................... */
    {
        "~Gioco",
        "~Nuova partita\tCtrl+N",
        "~Pausa\tCtrl+P",
        "~Termina partita\tCtrl+Q",
        "~Esci\tCtrl+X",
        "~Opzioni",
        "~Impostazioni...",
        "Definisci ~tasti...",
        "~Record...",
        "~Dettaglio",
        "~Alto",
        "~Medio",
        "~Basso",
        "~Lingua",
        "~Esegui in background\tCtrl+B",
        "~Controlli finestra\tCtrl+F",
        "Salva impostazioni all'~uscita",
        "~Aiuto",
        "~Uso dell'aiuto",
        "Aiuto: ~indice",
        "~Contenuto",
        "~Come si gioca",
        "~Tasti",
        "~Informazioni su STris...",
        "~Inglese",
        "~Spagnolo",
        "~Olandese",
        "~Tedesco",
        "~Francese",
        "~Italiano",
        "Avvia partita",
        "Ferma partita",
        "Record...",
        "Opzioni...",
        "Informazioni...",
        "Pausa",
        "Record",
        "Punteggio",
        "Righe",
        "Livello",
        "Nuovo record",
        "Albo d'onore",
        "Opzioni",
        "Assegnazione tasti",
        "Inserisci il tuo nome:",
        "Questi sono i migliori giocatori di STris:",
        "N.",
        "Nome",
        "Punteggio",
        "Righe",
        "Livello",
        "Impostazioni",
        "Difficolta",
        "Audio",
        "Griglia",
        "Prossimo pezzo",
        "Ruota in senso orario",
        "Resta in pausa",
        "Tavolozza",
        "Colori pieni",
        "Velocita",
        "Livello iniziale",
        "Tasti",
        "Scegli la funzione da modificare:",
        "Premi ora il nuovo tasto...",
        "Premi un tasto per %s, ESC per annullare",
        "spostare il pezzo a sinistra",
        "spostare il pezzo a destra",
        "ruotare in senso antiorario",
        "ruotare in senso orario",
        "lasciar cadere il pezzo",
        "Definizione del tasto completata.",
        "Definizione del tasto annullata.",
        "Tasto gia in uso. Provane un altro.",
        "Questo tasto e usato internamente da STris. Provane un altro.",
        "Non riconosco questo tasto. Provane un altro.",
        "Standard",
        "Rosso verso giallo",
        "Verde verso giallo",
        "Blu",
        "Grigi",
        "Bianco e nero",
        "Complimenti, sei tra",
        "i migliori giocatori di STris.",
        "Vuoi abbandonare la partita in corso?",
        "Iniziare con ~quadretti extra"
    }
};


/*** Functions ****************************************************************/

/*******************************************************************************
* tr(id)
* Return pointer to the string with the given number for the current language.
*******************************************************************************/

char *tr(int id)
{
    if( id < 0 || id >= NUM_STRINGS )
        return "";

    return lang_strings[current_lang][id];
}


/*******************************************************************************
* get_submenu(hMnu, id)
* Return the handle of the submenu with the given id or NULLHANDLE.
*******************************************************************************/

static HWND get_submenu(HWND hMnu, USHORT id)
{
    MENUITEM mi;

    memset(&mi, 0, sizeof(mi));

    if( (BOOL)WinSendMsg(hMnu, MM_QUERYITEM, MPFROM2SHORT(id, FALSE), MPFROMP(&mi)) )
        return mi.hwndSubMenu;

    return NULLHANDLE;
}


/*******************************************************************************
* menu_set_text(hMnu, id, text)
* Change the text of the menu item with the given id.
*******************************************************************************/

static void menu_set_text(HWND hMnu, USHORT id, const char *text)
{
    WinSendMsg(hMnu, MM_SETITEMTEXT, MPFROMSHORT(id), MPFROMP((PSZ)text));
}


/*******************************************************************************
* set_language_menu(hMenu)
* Re-label the complete menu bar for the current language.
*******************************************************************************/

static void set_language_menu(HWND hMenu)
{
    HWND hGame, hOptions, hDetail, hLanguage, hHelp;
    int  i;

    if( hMenu == NULLHANDLE )
        return;

    hGame    = get_submenu(hMenu, IDM_SUBMENU_GAME);
    hOptions = get_submenu(hMenu, IDM_SUBMENU_OPTIONS);
    hHelp    = get_submenu(hMenu, IDM_SUBMENU_HELP);

    menu_set_text(hMenu, IDM_SUBMENU_GAME,    tr(STR_GAME));
    menu_set_text(hMenu, IDM_SUBMENU_OPTIONS, tr(STR_OPTIONS));
    menu_set_text(hMenu, IDM_SUBMENU_HELP,    tr(STR_HELP));

    if( hGame )
    {
        menu_set_text(hGame, IDM_NEW,   tr(STR_NEW));
        menu_set_text(hGame, IDM_PAUSE, tr(STR_PAUSE));
        menu_set_text(hGame, IDM_QUIT,  tr(STR_QUIT));
        menu_set_text(hGame, IDM_EXIT,  tr(STR_EXIT));
    }

    if( hOptions )
    {
        hDetail    = get_submenu(hOptions, IDM_SUBMENU_DETAIL);
        hLanguage  = get_submenu(hOptions, IDM_SUBMENU_LANGUAGE);

        menu_set_text(hOptions, IDM_SETTINGS,     tr(STR_SETTINGS));
        menu_set_text(hOptions, IDM_KEYS,         tr(STR_KEYS));
        menu_set_text(hOptions, IDM_HISCORE_MENU, tr(STR_HISCORE));
        menu_set_text(hOptions, IDM_SUBMENU_DETAIL,    tr(STR_DETAIL));
        menu_set_text(hOptions, IDM_SUBMENU_LANGUAGE,  tr(STR_LANGUAGE));
        menu_set_text(hOptions, IDM_BACKGRND,     tr(STR_BACKGROUND));
        menu_set_text(hOptions, IDM_FRAME,        tr(STR_FRAME));
        menu_set_text(hOptions, IDM_SAVEONEXIT,   tr(STR_SAVEONEXIT));

        if( hDetail )
        {
            menu_set_text(hDetail, IDM_HIGHDET,   tr(STR_DETAIL_HIGH));
            menu_set_text(hDetail, IDM_MEDIUMDET, tr(STR_DETAIL_MEDIUM));
            menu_set_text(hDetail, IDM_LOWDET,    tr(STR_DETAIL_LOW));
        }

        /* Show the language names in the current UI language */
        if( hLanguage )
        {
            menu_set_text(hLanguage, IDM_LANG_EN, tr(STR_LANG_EN));
            menu_set_text(hLanguage, IDM_LANG_ES, tr(STR_LANG_ES));
            menu_set_text(hLanguage, IDM_LANG_NL, tr(STR_LANG_NL));
            menu_set_text(hLanguage, IDM_LANG_DE, tr(STR_LANG_DE));
            menu_set_text(hLanguage, IDM_LANG_FR, tr(STR_LANG_FR));
            menu_set_text(hLanguage, IDM_LANG_IT, tr(STR_LANG_IT));
        }
    }

    if( hHelp )
    {
        menu_set_text(hHelp, IDM_HELPUSING,     tr(STR_USINGHELP));
        menu_set_text(hHelp, IDM_HELPINDEX,     tr(STR_HELPINDEX));
        menu_set_text(hHelp, IDM_HELPCONTENTS,  tr(STR_HELPCONTENTS));
        menu_set_text(hHelp, IDM_HELPHOWTOPLAY, tr(STR_HOWTOPLAY));
        menu_set_text(hHelp, IDM_HELPKEYS,      tr(STR_KEYSHELP));
        menu_set_text(hHelp, IDM_ABOUT_MENU,    tr(STR_ABOUT));
    }

    for( i = 0; i < LANG_COUNT; i++ )
        WinCheckMenuItem(hMenu, (USHORT)(IDM_LANG_EN + i), (current_lang == i));
}


/*******************************************************************************
* set_language(hMenu, lang)
* Switches the current language and re-labels the complete user interface.
*******************************************************************************/

void set_language(HWND hMenu, int lang)
{
    int old_lang;

    if( lang < 0 || lang >= LANG_COUNT )
        lang = LANG_EN;

    old_lang    = current_lang;
    current_lang = lang;

    if( hMenu != NULLHANDLE )
        set_language_menu(hMenu);

    UpdateUILanguage(hwndClient);      /* window buttons + in-window labels  */

    if( lang != old_lang )
        SetHelpLanguage(lang);         /* swap help library file             */

    SetDetailMenu();                   /* keep detail checks in sync         */
}
