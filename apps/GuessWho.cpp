//developer VIP
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>  // Per la funzione tolower()
#include <unistd.h>  // Per la funzione sleep()

using namespace std;

void print_title() {
    cout << endl;
    cout << " Sfida da Campione: Indovina il Calciatore! " << endl;
    cout << "--------------------------------------------------" << endl;
}


// Funzione per convertire una stringa in minuscolo
string to_lowercase(const string& str) {
    string lower_str = str;
    for (char& c : lower_str) {
        c = tolower(c);  // Converte ogni carattere in minuscolo
    }
    return lower_str;
}

// Funzione per stampare separatori per un aspetto più bello
void print_separator() {
    cout << "--------------------------------------------------" << endl;
}

// Funzione per stampare il messaggio di benvenuto
void print_welcome_message() {
    print_separator();
    cout << "  *** Benvenuto al gioco 'Indovina il Calciatore' ***" << endl;
    print_separator();
}

// Funzione per stampare le informazioni del calciatore
void stampa_info(const string& nazionalita, const string& ruolo, const string& squadra) {
    cout << "  Nazionalita: " << nazionalita << endl;
    cout << "  Ruolo: " << ruolo << endl;
    cout << "  Squadra: " << squadra << endl;
}

// Funzione per il messaggio di vittoria
void print_victory_message(int stelle) {
    print_separator();
    cout << "  Congratulazioni! Hai vinto con " << stelle << " stelle!" << endl;
    print_separator();
}

// Funzione per il messaggio di sconfitta
void print_loss_message() {
    print_separator();
    cout << "  Mi dispiace, hai perso! Riprova!" << endl;
    print_separator();
}

// Funzione per chiedere se l'utente vuole giocare ancora
bool ask_to_play_again() {
    string risposta;
    print_separator();
    cout << "Vuoi giocare ancora? (Si/No): ";
    cin >> risposta;
    cout << endl;
    return to_lowercase(risposta) == "si";
}

// Funzione per chiedere se vogliamo iniziare a giocare
bool ask_to_start_game(int& partite_vinte_consecutive) {
    string risposta;
    print_separator();
    cout << "Vuoi iniziare a giocare? (Si/No): ";
    cin >> risposta;
    cout << endl;
    
     if (to_lowercase(risposta) == "bobby") {
        cout << "\033[38;5;46m";
        cout << "Sesso con Enri" << endl;
        cout << "\033[0m";  // Ripristina il colore normale
        return false;  // Non iniziare il gioco
    }
    
     if (to_lowercase(risposta) == "ventu") {
        cout << "\033[38;5;46m";
        cout << "Emila ti scopo" << endl;
        cout << "\033[0m";  // Ripristina il colore normale
        return false;  // Non iniziare il gioco
    }
    
    
    if (to_lowercase(risposta) == "campa") {
        // Stampa il messaggio in rosa
        cout << "\033[38;5;129m";
        cout << "Guendalina la mia sugar mamy" << endl;
        cout << "\033[0m";  // Ripristina il colore normale
        return false;  // Non iniziare il gioco
    }
    
     // Controlla se l'utente scrive "jackson"
    if (to_lowercase(risposta) == "jackson") {
        // Stampa il messaggio in rosa
        cout << "\033[38;5;13m";  // Imposta il colore rosa
        cout << "i vip scopano duro con ada e gli vengono dappertutto" << endl;
        cout << "\033[0m";  // Ripristina il colore normale
        return false;  // Non iniziare il gioco
    }
    
    // Controlla se l'utente scrive "ronzo"
    if (to_lowercase(risposta) == "ronzo") {
        // Stampa il messaggio speciale in rosso
        cout << "\033[1;31m";  // Imposta il colore rosso
        cout << "ronzo e klea amore infinito" << endl;
        cout << "\033[0m";  // Ripristina il colore normale
        return false;  // Non iniziare il gioco
    }
    
    // Controlla se l'utente scrive "banana" per la scorciatoia segreta
    if (to_lowercase(risposta) == "banana") {
        partite_vinte_consecutive = 19;  // Imposta 19 vittorie consecutive
        cout << "Hai attivato la scorciatoia segreta! Inizi con 19 vittorie consecutive!" << endl;
        return true;  // Prosegui con il gioco
    }
    
    return to_lowercase(risposta) == "si";
}


// Funzione per pulire lo schermo (Windows o Unix/Linux)
void clear_screen() {
    // Controlla il sistema operativo e pulisce lo schermo di conseguenza
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear");  // Unix/Linux
    #endif
}

// Funzione per cambiare il colore del testo usando codici ANSI
void set_color(const string& color) {
    if (color == "bronze") {
        cout << "\033[38;5;214m";  // Bronzo
    } else if (color == "silver") {
        cout << "\033[38;5;231m";  // Argento
    } else if (color == "gold") {
        cout << "\033[38;5;226m";  // Oro
    } else if (color == "diamond") {
        cout << "\033[38;5;39m";  // Azzurro simile al diamante
    } else if (color == "purple") {
        cout << "\033[38;5;55m";  // Viola
    } else if (color == "yellow") {
        cout << "\033[38;5;226m";  // Giallo
    }
}

// Funzione per resettare il colore del testo
void reset_color() {
    cout << "\033[0m";  // Reset del colore
}

// Funzione per visualizzare la scritta "developer VENTURINI"
void print_developer_venturini() {
    clear_screen();
    cout << "\033[1;32m";  // Imposta il colore verde
    cout << "                         developer VENTURINI                         " << endl;
    cout << "\033[0m";  // Ripristina il colore normale
    sleep(2);  // Pausa di 2 secondi
}

// Funzione per stampare le regole del gioco in giallo
void print_game_rules() {
    set_color("yellow");
    print_separator();
    cout << "Scopo del gioco: Indovina il calciatore!" << endl;
    cout << "Regole:" <<endl;
    cout << "Per vincere una partita devi indovinare 3 calciatori" << endl;
    cout << "Hai massimo 3 tentativi per ogni partita. Puoi fare fino a 3 errori totali in tutta la partita." << endl;
    cout << "Le medaglie vengono assegnate per il numero di vittorie consecutive:" << endl;
    print_separator();
    reset_color();
    set_color ("bronze");
    cout << "- Medaglia di bronzo: 3 vittorie consecutive"<< endl;
    set_color("silver");
    cout << "- Medaglia d'argento: 5 vittorie consecutive" << endl;
    set_color("gold");
    cout << "- Medaglia d'oro: 10 vittorie consecutive" << endl;
    set_color("diamond");
    cout << "- Medaglia di diamante: 20 vittorie consecutive" << endl;
    cout << endl << endl;
    reset_color();
    cout << "!!I GIOCATORI SONO NELLE RISPETTIVE SQUADRE DELLA STAGIONE 2023!!"<< endl;
	reset_color();
	cout << "I NOMI COMPOSTI DA PIU PAROLE NECCESSITANO DEL TRATTINO AL POSTO DELLO SPAZIO" << endl;
}

// Funzione per aggiungere uno spazio tra le domande
void add_space_between_questions() {
    cout << endl << endl;  // Aggiunge due righe vuote
}

int main() {
	print_title();
	#ifdef _WIN32
        system("color");  // Abilita i colori per Windows
    #endif
	
    // Dati dei calciatori (solo i cognomi e le squadre corrette)
    struct Calciatore {
        string cognome;
        string nazionalita;
        string ruolo;
        string squadra;
    };

    Calciatore calciatori[] = {
        
    {"Courtois", "Belgio", "Portiere", "Real Madrid"},
    {"Ter-Stegen", "Germania", "Portiere", "Barcellona"},
    {"Alisson", "Brasile", "Portiere", "Liverpool"},
    {"Maignan", "Francia", "Portiere", "Milan"},
    {"Oblak", "Slovenia", "Portiere", "Atletico Madrid"},
    {"Donnarumma", "Italia", "Portiere", "Paris Saint-Germain"},
    {"Ederson", "Brasile", "Portiere", "Manchester City"},
    {"Ramsdale", "Inghilterra", "Portiere", "Arsenal"},
    {"Martinez", "Argentina", "Portiere", "Aston Villa"},
    {"Pope", "Inghilterra", "Portiere", "Newcastle"},
    
    {"Hakimi", "Marocco", "Terzino destro", "Paris Saint-Germain"},
    {"Trippier", "Inghilterra", "Terzino destro", "Newcastle"},
    {"Walker", "Inghilterra", "Terzino destro", "Manchester City"},
    {"James", "Inghilterra", "Terzino destro", "Chelsea"},
    {"Kounde", "Francia", "Terzino destro", "Barcellona"},
    {"Alexander-Arnold", "Inghilterra", "Terzino destro", "Liverpool"},
    {"Cancelo", "Portogallo", "Terzino destro", "Manchester City"},
    {"Carvajal", "Spagna", "Terzino destro", "Real Madrid"},
    {"Di-Lorenzo", "Italia", "Terzino destro", "Napoli"},
    {"Frimpong", "Olanda", "Terzino destro", "Bayer Leverkusen"},
    
    {"Dias", "Portogallo", "Difensore centrale", "Manchester City"},
    {"Gvardiol", "Croazia", "Difensore centrale", "Lipsia"},
    {"Alaba", "Austria", "Difensore centrale", "Real Madrid"},
    {"Saliba", "Francia", "Difensore centrale", "Arsenal"},
    {"Militao", "Brasile", "Difensore centrale", "Real Madrid"},
    {"Araujo", "Uruguay", "Difensore centrale", "Barcellona"},
    {"Van-Dijk", "Paesi Bassi", "Difensore centrale", "Liverpool"},
    {"Lisandro Martinez", "Argentina", "Difensore centrale", "Manchester United"},
    {"Bastoni", "Italia", "Difensore centrale", "Inter"},
    {"Kim-Min-Jae", "Corea del Sud", "Difensore centrale", "Napoli"},
    
    {"Davies", "Canada", "Terzino sinistro", "Bayern Monaco"},
    {"Hernandez", "Francia", "Terzino sinistro", "Milan"},
    {"Zinchenko", "Ucraina", "Terzino sinistro", "Arsenal"},
    {"Robertson", "Scozia", "Terzino sinistro", "Liverpool"},
    {"Ake", "Paesi Bassi", "Terzino sinistro", "Manchester City"},
    {"Shaw", "Inghilterra", "Terzino sinistro", "Manchester United"},
    {"Estupinian", "Ecuador", "Terzino sinistro", "Brighton"},
    {"Balde", "Spagna", "Terzino sinistro", "Barcellona"},
    {"Guerreiro", "Portogallo", "Terzino sinistro", "Bayern Monaco"},
    {"Spinazzola", "Italia", "Terzino sinistro", "Roma"},
    
    {"Bellingham", "Inghilterra", "Centrocampista", "Real Madrid"},
    {"De-Bruyne", "Belgio", "Centrocampista", "Manchester City"},
    {"Odegaard", "Norvegia", "Centrocampista", "Arsenal"},
    {"Bernardo Silva", "Portogallo", "Centrocampista", "Manchester City"},
    {"Musiala", "Germania", "Centrocampista", "Bayern Monaco"},
    {"Bruno Fernandes", "Portogallo", "Centrocampista", "Manchester United"},
    {"Brandt", "Germania", "Centrocampista", "Borussia Dortmund"},
    {"Gavi", "Spagna", "Centrocampista", "Barcellona"},
    {"Brahim Diaz", "Spagna", "Centrocampista", "Real Madrid"},
    {"Paqueta", "Brasile", "Centrocampista", "West Ham"},
    {"Barella", "Italia", "Centrocampista", "Inter"},
    
    {"Saka", "Inghilterra", "Ali", "Arsenal"},
    {"Kvaratskhelia", "Georgia", "Ali", "Napoli"},
    {"Grealish", "Inghilterra", "Ali", "Manchester City"},
    {"Dembele", "Francia", "Ali", "Barcellona"},
    {"Martinelli", "Brasile", "Ali", "Arsenal"},
    {"Mahrez", "Algeria", "Ali", "Manchester City"},
    {"Coman", "Francia", "Ali", "Bayern Monaco"},
    {"Rodrygo", "Brasile", "Ali", "Real Madrid"},
    {"Foden", "Inghilterra", "Ali", "Manchester City"},
    {"Diaby", "Francia", "Ali", "Bayer Leverkusen"},
    
    {"Mbappe", "Francia", "Seconda punta", "Paris Saint-Germain"},
    {"Vinicius Junior", "Brasile", "Seconda punta", "Real Madrid"},
    {"Messi", "Argentina", "Seconda punta", "Inter Miami"},
    {"Salah", "Egitto", "Seconda punta", "Liverpool"},
    {"Griezmann", "Francia", "Seconda punta", "Atletico Madrid"},
    {"Rashford", "Inghilterra", "Seconda punta", "Manchester United"},
    {"Leao", "Portogallo", "Seconda punta", "Milan"},
    {"Lautaro Martinez", "Argentina", "Seconda punta", "Inter"},
    {"Nkunku", "Francia", "Seconda punta", "Chelsea"},
    {"Neymar", "Brasile", "Seconda punta", "Paris Saint-Germain"},
    
    {"Haaland", "Norvegia", "Centravanti", "Manchester City"},
    {"Benzema", "Francia", "Centravanti", "Al-Ittihad"},
    {"Kane", "Inghilterra", "Centravanti", "Tottenham"},
    {"Osimhen", "Nigeria", "Centravanti", "Napoli"},
    {"Lewandowski", "Polonia", "Centravanti", "Barcellona"},
    {"Jesus", "Brasile", "Centravanti", "Arsenal"},
    {"Kolo-Muani", "Francia", "Centravanti", "Eintracht Francoforte"},
    {"Isak", "Svezia", "Centravanti", "Newcastle"},
    {"Vlahovic", "Serbia", "Centravanti", "Juventus"},
    {"David", "Canada", "Centravanti", "Lille"},
    
    {"Rodri", "Spagna", "Centrocampista", "Manchester City"},
    {"Pedri", "Spagna", "Centrocampista", "Barcellona"},
    {"Gundogan", "Germania", "Centrocampista", "Barcellona"},
    {"Modric", "Croazia", "Centrocampista", "Real Madrid"},
    {"Casemiro", "Brasile", "Centrocampista", "Manchester United"},
    {"Mac-Allister", "Argentina", "Centrocampista", "Liverpool"},
    {"Kimmich", "Germania", "Centrocampista", "Bayern Monaco"},
    {"De-Jong", "Paesi Bassi", "Centrocampista", "Barcellona"},
    {"Guimaraes", "Brasile", "Centrocampista", "Newcastle"}


    };

    // Numero di calciatori
    int num_calciatori = sizeof(calciatori) / sizeof(calciatori[0]);

    // Inizializza il generatore di numeri casuali
    srand(time(0));

    int partite_vinte_consecutive = 0;

    // Mostra le regole del gioco
    print_game_rules();

    // Chiede all'utente se vuole iniziare a giocare
    if (!ask_to_start_game(partite_vinte_consecutive)) {
        cout << "Arrivederci!" << endl;
        return 0;
    }

    do {
        // Inizializza il contatore dei successi e degli errori (reset per ogni nuova partita)
        int successi = 0;
        int errori = 0;  // Contatore degli errori totali
        int tentativi_restanti = 3;  // Massimo 3 errori totali per partita

        // Pulisce lo schermo all'inizio di ogni partita
        clear_screen();

        // Mostra la scritta "developer VENTURINI"
        print_developer_venturini();

        // Messaggio di benvenuto
        print_welcome_message();

        // Gioco: indovina 3 calciatori consecutivi
        while (successi < 3 && errori < 3) {
            int indice = rand() % num_calciatori;
            string cognome = calciatori[indice].cognome;
            string nazionalita = calciatori[indice].nazionalita;
            string ruolo = calciatori[indice].ruolo;
            string squadra = calciatori[indice].squadra;

            // Stampa informazioni del calciatore
            stampa_info(nazionalita, ruolo, squadra);

            bool risposta_corretta = false;

            // Chiede fino a quando non si indovina o si esauriscono i tentativi disponibili
            string risposta;
            while (tentativi_restanti > 0 && !risposta_corretta) {
                cout << "Indovina il cognome del calciatore: ";
                cin >> risposta;

                if (to_lowercase(risposta) == to_lowercase(cognome)) {
                    risposta_corretta = true;
                    successi++;
                    cout << "Ben fatto! Hai indovinato!" << endl;
                } else {
                    tentativi_restanti--;
                    cout << "Risposta errata! Tentativi rimanenti: " << tentativi_restanti << endl;
                }
                add_space_between_questions();
            }
            // Modifica questa parte del ciclo che chiede la risposta
		


            cout << "Hai " << successi << " su 3 indovinati." << endl;

            // Aggiungi uno spazio tra le domande
            add_space_between_questions();

            // Se sono finiti i tentativi senza vincere
            if (tentativi_restanti == 0) {
                cout << "Hai perso! Il calciatore che non sei riuscito a indovinare era: " << cognome << endl;
                break;  // Uscita dal loop del gioco
            }
        }

        // Se hai indovinato 3 calciatori
        /*if (successi == 3) {
            int stelle = (errori == 0) ? 3 : (errori == 1) ? 2 : 1;
            print_victory_message(stelle);
            partite_vinte_consecutive++;
        } else {
            print_loss_message();
            partite_vinte_consecutive = 0;  // Reset del contatore delle vittorie consecutive
        }*/
        
        if (successi == 3) {
    int stelle = (errori == 0) ? 3 : (errori == 1) ? 2 : 1;
    print_victory_message(stelle);
    
    // Incrementa il contatore delle vittorie consecutive
    partite_vinte_consecutive++;

    // Mostra il numero di vittorie consecutive
    cout << "Hai " << partite_vinte_consecutive << " vittorie consecutive!" << endl;

    // Assegna e mostra la medaglia in base alle vittorie consecutive
    if (partite_vinte_consecutive >= 20) {
        set_color("diamond");
        cout << "Hai guadagnato la Medaglia di Diamante!" << endl;
        reset_color();
    } else if (partite_vinte_consecutive >= 10) {
        set_color("gold");
        cout << "Hai guadagnato la Medaglia d'Oro!" << endl;
        reset_color();
    } else if (partite_vinte_consecutive >= 5) {
        set_color("silver");
        cout << "Hai guadagnato la Medaglia d'Argento!" << endl;
        reset_color();
    } else if (partite_vinte_consecutive >= 3) {
        set_color("bronze");
        cout << "Hai guadagnato la Medaglia di Bronzo!" << endl;
        reset_color();
    }

} else {
    print_loss_message();
    partite_vinte_consecutive = 0;  // Reset del contatore delle vittorie consecutive
}


        // Chiedi all'utente se vuole rigiocare
    } while (ask_to_play_again());

    cout << "Grazie per aver giocato! Arrivederci!" << endl;
    return 0;
}
