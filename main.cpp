#include <iostream>
#include <windows.h>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

//MENU LOGOWANIE

struct Uzytkownik {
    int idUzytkownika;
    string nazwaUzytkownika;
    string hasloUzytkownika;
};

void wczytywanieUzytkownikowPlik(vector <Uzytkownik>& uzytkownicy) {
    string linia, tymczasowyZapis;
    char znak;
    int nr_linii = 1;
    int nrElementu = 0;

    fstream plik;
    plik.open("uzytkownicy.txt", ios::in);

    if(plik.good() == true) {

        while (getline(plik, linia)) {

            Uzytkownik nowyUzytkownik;
            nrElementu = 0;

            for (int i = 0; i < linia.length(); i++) {
                znak = linia[i];

                if (znak != '|') {
                    tymczasowyZapis += znak;

                } else {

                    switch(nrElementu) {
                    case 0:
                        nowyUzytkownik.idUzytkownika = atoi(tymczasowyZapis.c_str());
                        break;
                    case 1:
                        nowyUzytkownik.nazwaUzytkownika = tymczasowyZapis;
                        break;
                    case 2:
                        nowyUzytkownik.hasloUzytkownika=tymczasowyZapis;
                        break;
                    }

                    tymczasowyZapis = "";
                    nrElementu++;

                }
            }

            uzytkownicy.push_back(nowyUzytkownik);
            nr_linii++;
        }

        plik.close();
    }
}

void dodajUzytkownikaDoPliku (vector <Uzytkownik> &uzytkownicy) {

    fstream plik;
    plik.open("uzytkownicy.txt", ios::out | ios::app);

    if (plik.good()) {
        plik << uzytkownicy.back().idUzytkownika << '|' << uzytkownicy.back().nazwaUzytkownika << '|' << uzytkownicy.back().hasloUzytkownika << '|' << endl;
        plik.close();

        cout << "Uzytkownik dodany do listy" << endl;
        Sleep(1000);

    } else {
        cout << "Nie mozna otworzyc pliku" << endl;
    }

}

bool sprawdzCzyUzytkownikIstnieje (string nazwa, vector <Uzytkownik>& uzytkownicy) {
    bool czyUzytkownikIstnieje = false;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        if (itr -> nazwaUzytkownika == nazwa) {
            czyUzytkownikIstnieje = true;
        }
    }
    return czyUzytkownikIstnieje;
}

int logowanie (vector <Uzytkownik>& uzytkownicy) {
    string nazwa, haslo;
    bool flaga = true;
    //bool czyJestesZalogowany = false;
    bool czyUzytkownikIstnieje = false;
    int idZalogowanegoUzytkownika = 0;

    system("cls");

    cout << "Podaj nazwe uzytkownika" << endl;
    cin >> nazwa;

    czyUzytkownikIstnieje = sprawdzCzyUzytkownikIstnieje (nazwa, uzytkownicy);

    if (czyUzytkownikIstnieje) {
        for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
            if (itr -> nazwaUzytkownika == nazwa) {
                for (int i = 1; i <= 3; i++) {
                    system("cls");
                    cout << "Proba nr: " << i << ". Podaj haslo:" << endl;
                    cin >> haslo;
                    if (itr -> hasloUzytkownika == haslo) {
                        cout << "Haslo poprawne. Jestes zalogowany" << endl;
                        Sleep (1000);
                        flaga = false;
                        //czyJestesZalogowany = true;
                        return idZalogowanegoUzytkownika = itr -> idUzytkownika;
                        //break;
                    }
                }
                if (flaga) {
                    cout << "3 razy wprowadzono haslo niepoprawne. Poczekaj 3s i sprobuj ponownie." << endl;
                    Sleep(3000);
                }
            }
        }
    } else {
        cout << "Podany uzytkownik nie istnieje. Zarejestruj sie." << endl;
        Sleep (2000);
        return 0;
    }
    //return czyJestesZalogowany;
}

void rejestracja (vector <Uzytkownik>& uzytkownicy) {
    string nazwa,haslo;
    int iDUzytkownika;
    bool czyUzytkownikIstnieje = true;
    Uzytkownik nowyUzytkownik;

    while (czyUzytkownikIstnieje) {

        system("cls");
        cout << "Podaj nazwe uzytkownika: " << endl;
        cin >> nazwa;

        czyUzytkownikIstnieje = sprawdzCzyUzytkownikIstnieje(nazwa, uzytkownicy);

        if (czyUzytkownikIstnieje) {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika." << endl;
            Sleep(2000);

        } else {
            cout << "Podaj haslo: " << endl;
            cin >> haslo;
            cout << "Uzytkownik zarejestrowany" << endl;
            Sleep(1000);

        }
    }

    if (uzytkownicy.size() == 0) {
        iDUzytkownika = 1;
    } else {
        iDUzytkownika = uzytkownicy.back().idUzytkownika + 1;
    }

    nowyUzytkownik.idUzytkownika = iDUzytkownika;
    nowyUzytkownik.nazwaUzytkownika = nazwa;
    nowyUzytkownik.hasloUzytkownika = haslo;

    uzytkownicy.push_back(nowyUzytkownik);
    dodajUzytkownikaDoPliku (uzytkownicy);
}

void aktualizujPlikUzytkownicy(vector <Uzytkownik>& uzytkownicy) {
    int rozmiarWektora = uzytkownicy.size();

    fstream plik;
    plik.open("uzytkownicy.txt", ios::trunc | ios::out);

    if (plik.good() == true) {
        for (int i = 0; i < rozmiarWektora; i++) {

            plik << uzytkownicy[i].idUzytkownika << '|' << uzytkownicy[i].nazwaUzytkownika << '|' << uzytkownicy[i].hasloUzytkownika << '|' << endl;

        }
        plik.close();

    } else {
        cout << "Nie mozna otworzyc pliku" << endl;
    }

}

void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {
    string haslo;

    cout << "Zmiana hasla: " << endl;
    cin >> haslo;

    for (vector <Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        if (itr -> idUzytkownika == idZalogowanegoUzytkownika) {
            itr -> hasloUzytkownika = haslo;
            cout << "Haslo zostalo zmienione." << endl;
            aktualizujPlikUzytkownicy(uzytkownicy);
            Sleep(1000);
        }
    }

}

//MENU KSIAZKA ADRESOWA

struct Kontakt {
    int id = 0;
    int idUzytkownika = 0;
    string imie = "", nazwisko = "", nrTelefonu = "", email = "", adres = "";
};

void wczytywanieKontaktowPlik(vector <Kontakt>& kontakty, int idZalogowanegoUzytkownika) {
    string linia, tymczasowyZapis;
    char znak;
    int nr_linii = 1;
    int nrElementu = 0;

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good() == true) {

        while (getline(plik, linia)) {

            Kontakt nowyKontakt;
            nrElementu = 0;

            for (int i = 0; i < linia.length(); i++) {
                znak = linia[i];

                if (znak != '|') {
                    tymczasowyZapis += znak;

                } else {

                    switch(nrElementu) {
                    case 0:
                        nowyKontakt.id = atoi(tymczasowyZapis.c_str());
                        break;
                    case 1:
                        nowyKontakt.idUzytkownika = atoi(tymczasowyZapis.c_str());
                    case 2:
                        nowyKontakt.imie = tymczasowyZapis;
                        break;
                    case 3:
                        nowyKontakt.nazwisko=tymczasowyZapis;
                        break;
                    case 4:
                        nowyKontakt.nrTelefonu = tymczasowyZapis;
                        break;
                    case 5:
                        nowyKontakt.email = tymczasowyZapis;
                        break;
                    case 6:
                        nowyKontakt.adres = tymczasowyZapis;
                        break;
                    }

                    tymczasowyZapis = "";
                    nrElementu++;

                }
            }

            if (nowyKontakt.idUzytkownika == idZalogowanegoUzytkownika) {
                kontakty.push_back(nowyKontakt);
            }


            nr_linii++;
        }

        plik.close();
    }
}

int znajdzOstatnieID (vector <Kontakt> &kontakty) {
    int nrLini = 0;
    int nrElementu;
    int id =0;
    string linia;
    string tymczasowyZapis;
    char znak;

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good() == true) {

        while (getline(plik, linia)) {

            nrElementu = 0;

            for (int i = 0; i < linia.length(); i++) {
                znak = linia[i];

                if (znak != '|') {
                    tymczasowyZapis += znak;

                } else {

                    switch(nrElementu) {
                    case 0:
                        id = atoi(tymczasowyZapis.c_str());
                    default:
                        break;
                    }

                    tymczasowyZapis = "";
                    nrElementu++;

                }
            }
        }


        nrLini++;
    }


    return id;

}

void dodajKontakt(vector <Kontakt>& kontakty, int idZalogowanegoUzytkownika) {
    string imie, nazwisko, nrTelefonu, email,adres;
    int id, ostatnieID;

    ostatnieID = znajdzOstatnieID(kontakty);
    id = ostatnieID + 1;

    /*if (ostatnieID == 0) {
        id = 1;
    } else {
        id = ostatnieID+1;
    }*/
    cout << "id = " << id<<endl;

    cout << "Podaj imie: " << endl;
    cin >> imie;
    cout << "Podaj nazwisko: " << endl;
    cin >> nazwisko;
    cout << "Podaj nr telefonu: " << endl;
    cin >> nrTelefonu;
    cout << "Podaj email: " << endl;
    cin >> email;
    cin.sync();
    cout << "Podaj adres: " << endl;
    getline(cin,adres);

    Kontakt nowyKontakt;

    nowyKontakt.id = id;
    nowyKontakt.idUzytkownika = idZalogowanegoUzytkownika;
    nowyKontakt.imie = imie;
    nowyKontakt.nazwisko = nazwisko;
    nowyKontakt.nrTelefonu = nrTelefonu;
    nowyKontakt.email = email;
    nowyKontakt.adres = adres;

    kontakty.push_back(nowyKontakt);


    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good()) {
        plik << id << '|' << idZalogowanegoUzytkownika << '|' << imie << '|' << nazwisko << '|' << nrTelefonu << '|' << email << '|' << adres << '|' << endl;

        plik.close();
        cout << "Kontakt dodany do listy" << endl;
        Sleep(1000);

    } else {
        cout << "Nie mozna otworzyc pliku" << endl;
    }

}

void wyszukajKontaktImie(vector <Kontakt>& kontakty, int idZalogowanegoUzytkownika) {
    string imie;
    string imieDoPorownania;
    int idDoPorownania;
    bool flag = true;
    int rozmiarWektora = kontakty.size();
    cout << "Podaj imie: " << endl;
    cin >> imie;
    transform(imie.begin(),imie.end(),imie.begin(),::tolower);

    for (int i = 0; i < rozmiarWektora; i++) {
        imieDoPorownania = kontakty[i].imie;
        idDoPorownania = kontakty[i].idUzytkownika;
        transform(imieDoPorownania.begin(),imieDoPorownania.end(),imieDoPorownania.begin(),::tolower);

        if (imie == imieDoPorownania && idDoPorownania == idZalogowanegoUzytkownika) {
            flag = false;
            cout << "ID Kontaktu " << kontakty[i].id << endl;
            //cout << "ID Uzytkownika " << kontakty[i].idUzytkownika << endl;
            cout << "Imie: "<<kontakty[i].imie << endl;
            cout << "Nazwisko: " << kontakty[i].nazwisko << endl;
            cout << "Numer telefonu: " << kontakty[i].nrTelefonu << endl;
            cout << "Email: " << kontakty[i].email << endl;
            cout << "Adres: " << kontakty[i].adres << endl;
            cout << endl;
        }
    }

    if (flag) {
        cout << "Nie znaleziono kontaktu z imieniem: " << imie << endl;
    }
    system("pause");

}

void wyszukajKontaktNazwisko(vector <Kontakt>& kontakty, int idZalogowanegoUzytkownika) {
    string nazwisko, nazwiskoDoPorownania;
    bool flag = true;
    int rozmiarWektora = kontakty.size();
    int idDoPorownania;
    cout << "Podaj nazwisko: " << endl;
    cin >> nazwisko;
    transform(nazwisko.begin(),nazwisko.end(),nazwisko.begin(),::tolower);

    for (int i = 0; i < rozmiarWektora; i++) {
        nazwiskoDoPorownania = kontakty[i].nazwisko;
        idDoPorownania = kontakty[i].idUzytkownika;
        transform(nazwiskoDoPorownania.begin(),nazwiskoDoPorownania.end(),nazwiskoDoPorownania.begin(),::tolower);

        if (nazwisko == nazwiskoDoPorownania && idDoPorownania == idZalogowanegoUzytkownika) {
            flag = false;
            cout << "ID Kontaktu " << kontakty[i].id << endl;
            //cout << "ID Uzytkownika " << kontakty[i].idUzytkownika << endl;
            cout << "Imie: " << kontakty[i].imie << endl;
            cout << "Nazwisko: " << kontakty[i].nazwisko << endl;
            cout << "Numer telefonu: " << kontakty[i].nrTelefonu << endl;
            cout << "Email: " << kontakty[i].email << endl;
            cout << "Adres: " << kontakty[i].adres << endl;
            cout << endl;
        }
    }

    if (flag) {
        cout << "Nie znaleziono kontaktu z nazwiskiem: " << nazwisko << endl;
    }

    system("pause");

}

void wyswietlKontakty(vector <Kontakt>& kontakty, int idZalogowanegoUzytkownika) {
    int rozmiarWektora = kontakty.size();

    if (rozmiarWektora == 0) {
        cout << "Lista kontaktow jest pusta" << endl;

    } else {

        for (int i = 0; i < rozmiarWektora; i++) {
            if (kontakty[i].idUzytkownika == idZalogowanegoUzytkownika) {
                cout << "ID Kontaktu " << kontakty[i].id << endl;
                //cout << "ID Uzytkownika " << kontakty[i].idUzytkownika << endl;
                cout << "Imie: " << kontakty[i].imie << endl;
                cout << "Nazwisko: " << kontakty[i].nazwisko << endl;
                cout << "Numer telefonu: " << kontakty[i].nrTelefonu << endl;
                cout << "Email: " << kontakty[i].email << endl;
                cout << "Adres: " << kontakty[i].adres << endl;
                cout << endl;
            }
        }
    }
    system("pause");

}

bool sprawdzCzyKontaktIstnieje(int IdDoUsuniecia, vector <Kontakt>& kontakty) {
    bool flaga = false;

    for (int i = 0; i < kontakty.size(); i++) {
        if (IdDoUsuniecia == kontakty[i].id) {
            flaga = true;
            return flaga;
            break;
        }
    }

}

void zapiszKontaktDoPlikuTymczasowego(Kontakt nowyKontakt) {

    fstream plik;
    plik.open("ksiazkaAdresowa_tymczasowy.txt", ios::out | ios::app);

    if (plik.good()) {
        plik << nowyKontakt.id << '|' << nowyKontakt.idUzytkownika << '|' << nowyKontakt.imie << '|' << nowyKontakt.nazwisko << '|' << nowyKontakt.nrTelefonu << '|' << nowyKontakt.email << '|' << nowyKontakt.adres << '|' << endl;

        plik.close();

    } else {
        cout << "Nie mozna otworzyc pliku" << endl;
    }

}

void aktualizacjaPlikuKontaktyUsuniecie(vector <Kontakt> &kontakty, int idDoUsuniecia) {
    string linia, tymczasowyZapis;
    char znak;
    int nr_linii = 1;
    int nrElementu = 0;

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good() == true) {

        while (getline(plik, linia)) {

            Kontakt nowyKontakt;
            nrElementu = 0;

            for (int i = 0; i < linia.length(); i++) {
                znak = linia[i];

                if (znak != '|') {
                    tymczasowyZapis += znak;

                } else {

                    switch(nrElementu) {
                    case 0:
                        nowyKontakt.id = atoi(tymczasowyZapis.c_str());
                        break;
                    case 1:
                        nowyKontakt.idUzytkownika = atoi(tymczasowyZapis.c_str());
                    case 2:
                        nowyKontakt.imie = tymczasowyZapis;
                        break;
                    case 3:
                        nowyKontakt.nazwisko=tymczasowyZapis;
                        break;
                    case 4:
                        nowyKontakt.nrTelefonu = tymczasowyZapis;
                        break;
                    case 5:
                        nowyKontakt.email = tymczasowyZapis;
                        break;
                    case 6:
                        nowyKontakt.adres = tymczasowyZapis;
                        break;
                    }

                    tymczasowyZapis = "";
                    nrElementu++;

                }
            }

            nr_linii++;

            if (nowyKontakt.id != idDoUsuniecia) {
                zapiszKontaktDoPlikuTymczasowego(nowyKontakt);
            }
        }

        plik.close();
    }

    remove("ksiazkaAdresowa.txt");
    rename("ksiazkaAdresowa_tymczasowy.txt", "ksiazkaAdresowa.txt");


}

int znajdzPozycjaKontaktu(vector <Kontakt> &kontakty, int idDoUsuniecia) {

    for (int i = 0; i < kontakty.size(); i++) {
        if (kontakty[i].id == idDoUsuniecia) {
            return i;
        }
    }
}

void aktualizacjaPlikuKontaktyEdycja(vector <Kontakt> &kontakty, int idDoUsuniecia) {
    string linia, tymczasowyZapis;
    char znak;
    int nr_linii = 1;
    int nrElementu = 0;
    int pozycjaKontaktu;
    bool czyKontaktUsuniety = false;

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good() == true) {

        while (getline(plik, linia)) {

            Kontakt nowyKontakt;
            nrElementu = 0;

            for (int i = 0; i < linia.length(); i++) {
                znak = linia[i];

                if (znak != '|') {
                    tymczasowyZapis += znak;

                } else {

                    switch(nrElementu) {
                    case 0:
                        nowyKontakt.id = atoi(tymczasowyZapis.c_str());
                        break;
                    case 1:
                        nowyKontakt.idUzytkownika = atoi(tymczasowyZapis.c_str());
                    case 2:
                        nowyKontakt.imie = tymczasowyZapis;
                        break;
                    case 3:
                        nowyKontakt.nazwisko=tymczasowyZapis;
                        break;
                    case 4:
                        nowyKontakt.nrTelefonu = tymczasowyZapis;
                        break;
                    case 5:
                        nowyKontakt.email = tymczasowyZapis;
                        break;
                    case 6:
                        nowyKontakt.adres = tymczasowyZapis;
                        break;
                    }

                    tymczasowyZapis = "";
                    nrElementu++;

                }
            }
            nr_linii++;

            if (nowyKontakt.id != idDoUsuniecia) {
                zapiszKontaktDoPlikuTymczasowego(nowyKontakt);
            } else {
                pozycjaKontaktu = znajdzPozycjaKontaktu(kontakty,idDoUsuniecia);
                zapiszKontaktDoPlikuTymczasowego(kontakty[pozycjaKontaktu]);
            }
        }

        plik.close();
    }

    remove("ksiazkaAdresowa.txt");
    rename("ksiazkaAdresowa_tymczasowy.txt", "ksiazkaAdresowa.txt");

}

void usunKontakt(vector <Kontakt>& kontakty) {
    //int rozmiarWektora = kontakty.size();
    int IdDoUsuniecia;
    bool czyKontaktIstnieje = false;
    cout << "Podaj ID kontaktu, ktory chcesz usunac: ";
    cin >> IdDoUsuniecia;

    czyKontaktIstnieje = sprawdzCzyKontaktIstnieje(IdDoUsuniecia, kontakty);

    if (czyKontaktIstnieje) {

        for (vector <Kontakt>::iterator itr = kontakty.begin(); itr != kontakty.end(); itr++) {
            if (itr -> id == IdDoUsuniecia) {
                cout << "Jesli chcesz usunac kontakt wcisnij klawisz 't': " << endl;
                char znak;
                cin >> znak;
                if (znak == 't') {
                    kontakty.erase(itr);
                    cout << "Kontakt zostal usuniety." << endl;
                    aktualizacjaPlikuKontaktyUsuniecie(kontakty, IdDoUsuniecia);
                    break;

                } else {
                    cout << "Kontakt nie zostal usuniety" << endl;

                }
            }
        }
    } else cout << "Kontakt o podanym ID nie istnieje" << endl;


}

void edytujKontakt(vector <Kontakt>& kontakty) {
    int idDoUsuniecia;
    int wybor;
    bool czyKontaktIstnieje = false;
    //int rozmiarWektora = kontakty.size();
    string imie, nazwisko, nrTelefonu, email, adres;

    cout << "Podaj id kontaktu do edycji" << endl;
    cin >> idDoUsuniecia;

    czyKontaktIstnieje = sprawdzCzyKontaktIstnieje(idDoUsuniecia, kontakty);

    if (czyKontaktIstnieje) {

        cout << "MENU EDYCJI" << endl;
        cout << "1 - imie" << endl;
        cout << "2 - nazwisko" << endl;
        cout << "3 - numer telefonu" << endl;
        cout << "4 - email" << endl;
        cout << "5 - adres" << endl;
        cout << "6 - powrot do menu glownego" << endl;

        for (vector <Kontakt>::iterator itr = kontakty.begin(); itr != kontakty.end(); itr++) {
            if (itr -> id == idDoUsuniecia) {
                cout << "Wybierz pozycje do edycji" << endl;
                cin >> wybor;

                switch (wybor) {
                case 1: {
                    cout << "Podaj imie: " <<endl;
                    cin >> imie;
                    itr -> imie = imie;
                    break;
                }
                case 2: {
                    cout << "Podaj nazwisko: " <<endl;
                    cin >> nazwisko;
                    itr -> nazwisko = nazwisko;
                    break;
                }
                case 3: {
                    cout << "Podaj numer telefonu: " <<endl;
                    cin >> nrTelefonu;
                    itr -> nrTelefonu = nrTelefonu;
                    break;
                }
                case 4: {
                    cout << "Podaj email: " <<endl;
                    cin >> email;
                    itr -> email = email;
                    break;
                }
                case 5: {
                    cout << "Podaj adres: " <<endl;
                    cin >> adres;
                    itr -> adres = adres;
                    break;
                }
                case 6: {
                    break;
                }
                default:
                    break;
                }

                aktualizacjaPlikuKontaktyEdycja(kontakty, idDoUsuniecia);
                break;

            }
        }


    } else cout << "Kontakt o podanym ID nie istnieje" << endl;
}

int main() {
    vector <Uzytkownik> uzytkownicy;
    vector <Kontakt> kontakty;
    char wybor;
    int idZalogowanegoUzytkownika = 0;
    bool czyJestesZalogowany = false;
    bool wejscieDoMenu = true;

    wczytywanieUzytkownikowPlik(uzytkownicy);

    while(1) {
        system("cls");

        cout << "MENU:" << endl;
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl;

        cout << "Wybierz opcje z menu" << endl;
        cin >> wybor;

        if (wybor == '1') {

            idZalogowanegoUzytkownika = logowanie(uzytkownicy);

            if (idZalogowanegoUzytkownika != 0) {
                wejscieDoMenu = true;
                wczytywanieKontaktowPlik(kontakty, idZalogowanegoUzytkownika);

                while(wejscieDoMenu) {
                    system ("cls");
                    cout << "Ksiazka adresowa" << endl;
                    cout << "1. Dodaj adresata" << endl;
                    cout << "2. Wyszukaj po imieniu" << endl;
                    cout << "3. Wyszukaj po nazwisku" << endl;
                    cout << "4. Wyswietl wszystkich adresatow" << endl;
                    cout << "5. Usun adresata" << endl;
                    cout << "6. Edytuj adresata" << endl;
                    cout << "7. Zmien haslo" << endl;
                    cout << "8. Wyloguj sie" << endl;

                    cin>>wybor;

                    if (wybor == '1') {

                        dodajKontakt(kontakty, idZalogowanegoUzytkownika);
                        //system("pause");

                    } else if (wybor == '2') {

                        wyszukajKontaktImie(kontakty, idZalogowanegoUzytkownika);

                    } else if (wybor == '3') {

                        wyszukajKontaktNazwisko(kontakty, idZalogowanegoUzytkownika);

                    } else if (wybor == '4') {

                        wyswietlKontakty(kontakty, idZalogowanegoUzytkownika);

                    } else if (wybor == '5') {

                        usunKontakt(kontakty);
                        system("pause");

                    } else if (wybor == '6') {

                        edytujKontakt(kontakty);
                        system("pause");

                    } else if (wybor == '7') {

                        zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);

                    } else if (wybor == '8') {

                        kontakty.clear();
                        wejscieDoMenu = false;

                    } else {
                        cout << "Wybrano nieprawidlowa opcje. Podaj numer jeszcze raz" << endl;
                        Sleep(2000);
                    }
                }

            }

        } else if (wybor == '2') {

            rejestracja(uzytkownicy);

        } else if (wybor == '3') {

            exit(0);
        }
    }


    return 0;
}
