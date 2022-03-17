#include <iostream>
#include <windows.h>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

struct Kontakt {
    int id = 0;
    string imie = "", nazwisko = "", nrTelefonu = "", email = "", adres = "";
};

void wczytywanieKontaktowPlik(vector <Kontakt>& kontakty) {
    string linia, tymczasowyZapis;
    char znak;
    int nr_linii = 1;
    int nrElementu = 0;


    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

    if(plik.good() == true) {

        while (getline(plik, linia)) {

            Kontakt nowyKontakt;
            nowyKontakt.imie = linia;
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
                        nowyKontakt.imie = tymczasowyZapis;
                        break;
                    case 2:
                        nowyKontakt.nazwisko=tymczasowyZapis;
                        break;
                    case 3:
                        nowyKontakt.nrTelefonu = tymczasowyZapis;
                        break;
                    case 4:
                        nowyKontakt.email = tymczasowyZapis;
                        break;
                    case 5:
                        nowyKontakt.adres = tymczasowyZapis;
                        break;
                    }

                    tymczasowyZapis = "";
                    nrElementu++;

                }
            }

            kontakty.push_back(nowyKontakt);


            nr_linii++;
        }

        plik.close();
    }
}

void aktualizacjaPliku (vector <Kontakt>& kontakty) {
    int rozmiarWektora = kontakty.size();

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::trunc | ios::out);

    if (plik.good() == true) {
        for (int i = 0; i < rozmiarWektora; i++) {

                plik << kontakty[i].id << '|' << kontakty[i].imie << '|' << kontakty[i].nazwisko << '|' << kontakty[i].nrTelefonu << '|' << kontakty[i].email << '|' << kontakty[i].adres << '|' << endl;

        }
        plik.close();

    } else {
        cout << "Nie mozna otworzyc pliku" << endl;
    }

}

void dodajKontakt(vector <Kontakt>& kontakty) {
    string imie, nazwisko, nrTelefonu, email,adres;
    int id;

    if (kontakty.size() == 0) {
        id = 1;
    } else {
        id = (kontakty[kontakty.size()-1].id) + 1;
    }

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
    nowyKontakt.imie = imie;
    nowyKontakt.nazwisko = nazwisko;
    nowyKontakt.nrTelefonu = nrTelefonu;
    nowyKontakt.email = email;
    nowyKontakt.adres = adres;

    kontakty.push_back(nowyKontakt);


    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good()) {
        plik << id << '|' << imie << '|' << nazwisko << '|' << nrTelefonu << '|' << email << '|' << adres << '|' << endl;

        plik.close();
        cout << "Kontakt dodany do listy" << endl;
        Sleep(1000);

    } else {
        cout << "Nie mozna otworzyc pliku" << endl;
    }

}

void wyszukajKontaktImie(vector <Kontakt>& kontakty) {
    string imie;
    string imieDoPorownania;
    int j = 1;
    int flag = true;
    int rozmiarWektora = kontakty.size();
    cout << "Podaj imie: " << endl;
    cin >> imie;
    transform(imie.begin(),imie.end(),imie.begin(),::tolower);

    for (int i = 0; i < rozmiarWektora; i++) {
        imieDoPorownania=kontakty[i].imie;
        transform(imieDoPorownania.begin(),imieDoPorownania.end(),imieDoPorownania.begin(),::tolower);

        if (imie == imieDoPorownania) {
            flag = false;
            cout << "Kontakt nr " << (j++) << endl;
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

void wyszukajKontaktNazwisko(vector <Kontakt>& kontakty) {
    string nazwisko, nazwiskoDoPorownania;
    int j = 1;
    int flag = true;
    int rozmiarWektora = kontakty.size();
    cout << "Podaj nazwisko: " << endl;
    cin >> nazwisko;
    transform(nazwisko.begin(),nazwisko.end(),nazwisko.begin(),::tolower);

    for (int i = 0; i < rozmiarWektora; i++) {
        nazwiskoDoPorownania = kontakty[i].nazwisko;
        transform(nazwiskoDoPorownania.begin(),nazwiskoDoPorownania.end(),nazwiskoDoPorownania.begin(),::tolower);

        if (nazwisko == nazwiskoDoPorownania) {
            flag = false;
            cout << "Kontakt nr " << (j++) << endl;
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

void wyswietlKontakty(vector <Kontakt>& kontakty) {
    int rozmiarWektora = kontakty.size();

    if (rozmiarWektora == 0) {
        cout << "Lista kontaktow jest pusta" << endl;

    } else {

        for (int i = 0; i < rozmiarWektora; i++) {
            cout << "Kontakt nr " << kontakty[i].id << endl;
            cout << "Imie: " << kontakty[i].imie << endl;
            cout << "Nazwisko: " << kontakty[i].nazwisko << endl;
            cout << "Numer telefonu: " << kontakty[i].nrTelefonu << endl;
            cout << "Email: " << kontakty[i].email << endl;
            cout << "Adres: " << kontakty[i].adres << endl;
            cout << endl;
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

void usunKontakt(vector <Kontakt>& kontakty) {
    int rozmiarWektora = kontakty.size();
    int IdDoUsuniecia;
    bool czyKontaktIstnieje = false;
    cout << "Podaj ID kontaktu, ktory chcesz usunac: ";
    cin >> IdDoUsuniecia;

    czyKontaktIstnieje = sprawdzCzyKontaktIstnieje(IdDoUsuniecia, kontakty);

    if (czyKontaktIstnieje) {


        for (int i = 0 ; i < rozmiarWektora; i++) {
            if (kontakty[i].id == IdDoUsuniecia) {
                cout << "Jesli chcesz usunac kontakt wcisnij klawisz 't': " << endl;
                char znak;
                cin >> znak;
                if (znak == 't') {
                    kontakty.erase(kontakty.begin()+i);
                    cout << "Kontakt zostal usuniety." << endl;
                    aktualizacjaPliku (kontakty);
                } else {
                    cout << "Kontakt nie zostal usuniety" << endl;
                }
            }
        }
    } else cout << "Kontakt o podanym ID nie istnieje" << endl;


}

Kontakt wczytanieKontaktu(vector <Kontakt>& kontakty, int pozycja) {
    Kontakt osoba;
    osoba.id = kontakty[pozycja].id;
    osoba.imie = kontakty[pozycja].imie;
    osoba.nazwisko = kontakty[pozycja].nazwisko;
    osoba.nrTelefonu = kontakty[pozycja].nrTelefonu;
    osoba.email = kontakty[pozycja].email;
    osoba.adres = kontakty[pozycja].adres;

    return osoba;

}

void edytujKontakt(vector <Kontakt>& kontakty) {
    int id;
    int wybor;
    bool czyKontaktIstnieje = false;
    int rozmiarWektora = kontakty.size();
    string imie, nazwisko, nrTelefonu, email, adres;

    cout << "Podaj id kontaktu do edycji" << endl;
    cin >> id;

    czyKontaktIstnieje = sprawdzCzyKontaktIstnieje(id, kontakty);

    if (czyKontaktIstnieje) {

    cout << "MENU EDYCJI" << endl;
    cout << "1 - imie" << endl;
    cout << "2 - nazwisko" << endl;
    cout << "3 - numer telefonu" << endl;
    cout << "4 - email" << endl;
    cout << "5 - adres" << endl;
    cout << "6 - powrot do menu glownego" << endl;


    cout << "Wybierz pozycje do edycji" << endl;
    cin >> wybor;

    for (int i = 0; i < rozmiarWektora; i++) {
        if (kontakty[i].id == id) {
            Kontakt osoba;
            osoba = wczytanieKontaktu(kontakty, i);
            switch (wybor) {
            case 1: {
                cout << "Podaj imie: " <<endl;
                cin >> imie;
                osoba.imie = imie;
                break;
            }
            case 2: {
                cout << "Podaj nazwisko: " <<endl;
                cin >> nazwisko;
                osoba.nazwisko = nazwisko;
                break;
            }
            case 3: {
                cout << "Podaj numer telefonu: " <<endl;
                cin >> nrTelefonu;
                osoba.nrTelefonu = nrTelefonu;
                break;
            }
            case 4: {
                cout << "Podaj email: " <<endl;
                cin >> email;
                osoba.email = email;
                break;
            }
            case 5: {
                cout << "Podaj adres: " <<endl;
                cin >> adres;
                osoba.adres = adres;
                break;
            }
            case 6: {
                break;
            }
            default:
                break;

            }
            kontakty.erase(kontakty.begin()+i);
            kontakty.insert(kontakty.begin()+i,osoba);
        }
    }
    aktualizacjaPliku (kontakty);
    } else cout << "Kontakt o podanym ID nie istnieje" << endl;
}


int main() {
    char wybor;
    vector <Kontakt> kontakty;
    wczytywanieKontaktowPlik(kontakty);

    while(1) {
        system ("cls");
        cout << "Ksiazka adresowa" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;

        cin>>wybor;

        if (wybor == '1') {

            dodajKontakt(kontakty);
            system("pause");

        } else if (wybor == '2') {

            wyszukajKontaktImie(kontakty);

        } else if (wybor == '3') {

            wyszukajKontaktNazwisko(kontakty);

        } else if (wybor == '4') {

            wyswietlKontakty(kontakty);

        } else if (wybor == '5') {

            usunKontakt(kontakty);
            system("pause");

        } else if (wybor == '6') {

            edytujKontakt(kontakty);
            system("pause");

        } else if (wybor == '9') {

            exit(0);

        } else {

            cout << "Wybrano nieprawidlowa opcje. Podaj numer jeszcze raz" << endl;
            Sleep(2000);
        }
    }

    return 0;
}
