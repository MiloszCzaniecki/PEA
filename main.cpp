#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <set>
#include <algorithm>
#include <filesystem>
//#include "tinyxml2.h"
//#include <rapidxml.hpp>

//Zrodla:
// Przeszukiwanie naiwne - https://www.geeksforgeeks.org/traveling-salesman-problem-tsp-implementation/
// Przeszukiwanie najblizszego sasiada - https://www.guru99.com/travelling-salesman-problem.html
// Przeszukiwanie losowe - https://www.youtube.com/watch?v=XEbqwbOJTS4
// Formatowanie XML -

using namespace std;
//using namespace tinyxml2;
//namespace fs = std::filesystem;

// prototypy
void readConfig(string& nazwa_pliku,int& iteracje,int& wybor_algorytmu);
vector<vector<double>> parseTXT(string& nazwa_pliku, double& wynikOptymalny);
double TSPBruteforce(vector<vector<double>> graf, int start, vector<int>& wierzcholki_sciezki_minimalnej, double wartoscOptymalna);
double TSPRandom(vector<vector<double>> graf, int start, vector<int>& wierzcholki_sciezki_minimalnej, double wartoscOptymalna);
double TSPNearestNeighbor(vector<vector<double>> graf, int start, vector<int>& wierzcholki_sciezki_minimalnej, double wartoscOptymalna);

int main(int argc, char* argv[]) {

    string czesc_sciezki = "../data/";
    string czesc_plikowa;
    string nazwa_pliku;
    int iteracje;
    int wybor_algorytmu;

    readConfig(nazwa_pliku,iteracje,wybor_algorytmu);

    //czesc_plikowa = nazwa_pliku;
    //nazwa_pliku = (sciezka_data / nazwa_pliku).string();
    nazwa_pliku = czesc_sciezki + nazwa_pliku;
    
    double wynikOptymalny;
    vector<vector<double>> graf = parseTXT(nazwa_pliku, wynikOptymalny);
//    vector<vector<double>> graf = {
//            { 0, 10, 15, 20 },
//            { 10, 0, 35, 25 },
//            { 15, 35, 0, 30 },
//            { 20, 25, 30, 0 }
//    };
    int start = 0; //wierzcholek poczatkowy

    auto start_bruteforce = chrono::high_resolution_clock::now();
    auto end_bruteforce = chrono::high_resolution_clock::now();
    auto czas_bruteforce = chrono::duration_cast<chrono::milliseconds>(end_bruteforce - start_bruteforce).count();

    auto start_random = chrono::high_resolution_clock::now();
    auto end_random = chrono::high_resolution_clock::now();
    auto czas_random = chrono::duration_cast<chrono::milliseconds>(end_random - start_random).count();

    auto start_nearest = chrono::high_resolution_clock::now();
    auto end_nearest = chrono::high_resolution_clock::now();
    auto czas_nearest = chrono::duration_cast<chrono::milliseconds>(end_nearest - start_nearest).count();

    double wynik_bruteforce = 0;
    double wynik_random =  0;
    double wynik_nearest = 0;
    vector<int> wierzcholki_bruteforce;
    vector<int> wierzcholki_random;
    vector<int> wierzcholki_nearest;

    wierzcholki_bruteforce.resize(graf.size() + 1);
    wierzcholki_random.resize(graf.size() + 1);
    wierzcholki_nearest.resize(graf.size() + 1);

    for (int i = 0; i < graf.size() + 1; i++) {
        wierzcholki_bruteforce[i] = 0;
        wierzcholki_random[i] = 0;
        wierzcholki_nearest[i] = 0;
    }

    ofstream plik_wynikowy("results.txt");
    switch (wybor_algorytmu) {
        case 1: //Bruteforce


            for(int i = 0; i < iteracje; i++){
                start_bruteforce = chrono::high_resolution_clock::now();
                wynik_bruteforce = TSPBruteforce(graf, start, wierzcholki_bruteforce, wynikOptymalny);
                end_bruteforce = chrono::high_resolution_clock::now();
                cout << wynik_bruteforce << endl;
                czas_bruteforce = chrono::duration_cast<chrono::milliseconds>(end_bruteforce - start_bruteforce).count();
                cout << czas_bruteforce << " ms" << endl;

                plik_wynikowy << nazwa_pliku << endl;                // plik z grafem
                plik_wynikowy << graf.size() << endl;        // rozmiar grafu
                plik_wynikowy << "Bruteforce" << endl;           // jaki algorytm
                plik_wynikowy << iteracje + 1 << endl;                    // która iteracja
                plik_wynikowy << wynik_bruteforce << endl;         // koszt ścieżki
                plik_wynikowy << czas_bruteforce << " ms" << endl; // czas wykonania
                for (int w : wierzcholki_bruteforce) {
                    plik_wynikowy << w << " ";
                }
                plik_wynikowy << endl;

            }

            plik_wynikowy.close();
            break;
        case 2: //Random

            for(int i = 0; i < iteracje; i++){
                start_random = chrono::high_resolution_clock::now();
                wynik_random = TSPRandom(graf, start, wierzcholki_random, wynikOptymalny);
                end_random = chrono::high_resolution_clock::now();
                cout << wynik_random << endl;
                czas_random = chrono::duration_cast<chrono::milliseconds>(end_random - start_random).count();
                cout << czas_random << " ms" << endl;

                plik_wynikowy << nazwa_pliku << endl;                // plik z grafem
                plik_wynikowy << graf.size() << endl;        // rozmiar grafu
                plik_wynikowy << "Random" << endl;           // jaki algorytm
                plik_wynikowy << iteracje + 1 << endl;                    // która iteracja
                plik_wynikowy << wynik_random << endl;         // koszt ścieżki
                plik_wynikowy << czas_random << " ms" << endl; // czas wykonania
                for (int w : wierzcholki_random) {
                    plik_wynikowy << w << " ";
                }
                plik_wynikowy << endl;
            }
            plik_wynikowy.close();
            break;
        case 3: //NearestNeighbor
            for(int i = 0; i < iteracje; i++){
                start_nearest = chrono::high_resolution_clock::now();
                wynik_nearest = TSPNearestNeighbor(graf, start, wierzcholki_nearest, wynikOptymalny);
                end_nearest = chrono::high_resolution_clock::now();
                cout << wynik_nearest << endl;
                czas_nearest = chrono::duration_cast<chrono::milliseconds>(end_nearest - start_nearest).count();
                cout << czas_nearest << " ms" << endl;

                plik_wynikowy << nazwa_pliku << endl;                // plik z grafem
                plik_wynikowy << graf.size() << endl;        // rozmiar grafu
                plik_wynikowy << "NearestNeighbor" << endl;           // jaki algorytm
                plik_wynikowy << iteracje + 1 << endl;                    // która iteracja
                plik_wynikowy << wynik_nearest << endl;         // koszt ścieżki
                plik_wynikowy << czas_nearest << " ms" << endl; // czas wykonania
                for (int w : wierzcholki_nearest) {
                    plik_wynikowy << w << " ";
                }
                plik_wynikowy << endl;
            }
            plik_wynikowy.close();
            break;
        case 4: ////////////////////// WSZYSTKIE
            for(int i = 0; i < iteracje; i++){
                start_bruteforce = chrono::high_resolution_clock::now();
                wynik_bruteforce = TSPBruteforce(graf, start, wierzcholki_bruteforce, wynikOptymalny);
                end_bruteforce = chrono::high_resolution_clock::now();
                cout << wynik_bruteforce << endl;
                czas_bruteforce = chrono::duration_cast<chrono::milliseconds>(end_bruteforce - start_bruteforce).count();
                cout << czas_bruteforce << " ms" << endl;

                start_random = chrono::high_resolution_clock::now();
                wynik_random = TSPRandom(graf, start, wierzcholki_random, wynikOptymalny);
                end_random = chrono::high_resolution_clock::now();
                cout << wynik_random << endl;
                czas_random = chrono::duration_cast<chrono::milliseconds>(end_random - start_random).count();
                cout << czas_random << " ms" << endl;

                start_nearest = chrono::high_resolution_clock::now();
                wynik_nearest = TSPNearestNeighbor(graf, start, wierzcholki_nearest, wynikOptymalny);
                end_nearest = chrono::high_resolution_clock::now();
                cout << wynik_nearest << endl;
                czas_nearest = chrono::duration_cast<chrono::milliseconds>(end_nearest - start_nearest).count();
                cout << czas_nearest << " ms" << endl;

                if (!plik_wynikowy.is_open()) {
                    cerr << "Plik wyjsciowy sie nie zapisal" << endl;
                    return 1;
                }

                for (int it = 0; it < graf.size()+1; it++) {
                    plik_wynikowy << wierzcholki_bruteforce[it] << " ";
                }
                plik_wynikowy << "" << endl;
                plik_wynikowy << wynik_bruteforce << endl;
                plik_wynikowy << czas_bruteforce << " ms" << endl;

                plik_wynikowy << "" << endl;

                for (int it = 0; it < graf.size()+1; it++) {
                    plik_wynikowy << wierzcholki_random[it] << " ";
                }
                plik_wynikowy << "" << endl;
                plik_wynikowy << wynik_random << endl;
                plik_wynikowy << czas_random << " ms" << endl;

                plik_wynikowy << "" << endl;

                for (int it = 0; it < graf.size()+1; it++) {
                    plik_wynikowy << wierzcholki_nearest[it] << " ";  // Zapis wierzchołków
                }
                plik_wynikowy << "" << endl;
                plik_wynikowy << wynik_nearest << endl;
                plik_wynikowy << czas_nearest << " ms" << endl;
            }
            plik_wynikowy.close();
            break;
        default: ///////////////////////////////////// TESTY TESTY TESTY TESTY   wpisac 5

                vector<string> pliki_z_danymi = {
                        "asymetryczne_tsp17.txt", "asymetryczne_tsp33.txt", "asymetryczne_tsp64.txt",
                        "identyczne_tsp5.txt", "identyczne_tsp6.txt", "identyczne_tsp7.txt", "identyczne_tsp8.txt",
                        "identyczne_tsp9.txt", "identyczne_tsp10.txt", "niepelne_asymetryczne_tsp5.txt",
                        "niepelne_asymetryczne_tsp6.txt", "niepelne_asymetryczne_tsp7.txt", "niepelne_asymetryczne_tsp8.txt",
                        "niepelne_asymetryczne_tsp9.txt", "niepelne_asymetryczne_tsp10.txt", "niepelne_asymetryczne_tsp11.txt",
                        "niepelne_asymetryczne_tsp12.txt", "niepelne_asymetryczne_tsp13.txt", "niepelne_asymetryczne_tsp14.txt",
                        "niepelne_tsp5.txt", "niepelne_tsp6.txt", "niepelne_tsp7.txt", "niepelne_tsp8.txt", "niepelne_tsp9.txt",
                        "niepelne_tsp10.txt", "niepelne_tsp11.txt", "niepelne_tsp12.txt", "tsp4.txt", "tsp5.txt",
                        "tsp6.txt", "tsp7.txt", "tsp8.txt", "tsp9.txt", "tsp10.txt", "tsp14.txt", "tsp16.txt",
                        "tsp17.txt", "tsp21.txt", "tsp22.txt", "tsp24.txt"
                };

            vector<string> dzialajace_pliki_z_danymi = {
                    /*"asymetryczne_tsp17.txt", "asymetryczne_tsp33.txt", "asymetryczne_tsp64.txt",*/
                    "identyczne_tsp5.txt", "identyczne_tsp6.txt", "identyczne_tsp7.txt", "identyczne_tsp8.txt",
                    "identyczne_tsp9.txt", "identyczne_tsp10.txt", "niepelne_asymetryczne_tsp5.txt",
                    "niepelne_asymetryczne_tsp6.txt", "niepelne_asymetryczne_tsp7.txt", "niepelne_asymetryczne_tsp8.txt",
                    "niepelne_asymetryczne_tsp9.txt", "niepelne_asymetryczne_tsp10.txt", "niepelne_asymetryczne_tsp11.txt",
                    "niepelne_asymetryczne_tsp12.txt", "niepelne_asymetryczne_tsp13.txt", "niepelne_asymetryczne_tsp14.txt",
                    "tsp4.txt", "tsp5.txt",
                    "tsp6.txt", "tsp7.txt", "tsp8.txt", "tsp10.txt", "tsp14.txt", "tsp16.txt",
                    "tsp17.txt", "tsp21.txt"
            };



                for (auto& nazwa_pliku_1z40 : dzialajace_pliki_z_danymi) {
                    string nazwa_pliku_bez_sciezki = nazwa_pliku_1z40.substr(nazwa_pliku_1z40.find_last_of("/\\") + 1);
                    graf = parseTXT(nazwa_pliku_1z40, wynikOptymalny);
                    int liczba_wierzcholkow = graf.size();
    
                    int liczba_iteracji = 1;
                    //
                    if(liczba_wierzcholkow <= 12){
                        for (int ite = 0; ite < liczba_iteracji; ++ite) {
                            cout << "Przetwarzanie pliku: " << nazwa_pliku_bez_sciezki << ", Iteracja: " << (ite + 1) << endl;

                            // -------------------- Bruteforce --------------------
                            vector<int> wierzcholkiBruteforce;
                            auto start_Bruteforce = chrono::high_resolution_clock::now();
                            double wynik_Bruteforce = TSPBruteforce(graf, start, wierzcholkiBruteforce, wynikOptymalny);
                            auto end_Bruteforce = chrono::high_resolution_clock::now();
                            auto czas_Bruteforce = chrono::duration_cast<chrono::milliseconds>(end_Bruteforce - start_Bruteforce).count();

                            // zapis do pliku wynikowego
                            plik_wynikowy << nazwa_pliku_bez_sciezki << endl;                // plik z grafem
                            plik_wynikowy << liczba_wierzcholkow << endl;        // rozmiar grafu
                            plik_wynikowy << "Bruteforce" << endl;           // jaki algorytm
                            plik_wynikowy << ite + 1 << endl;                    // która iteracja
                            plik_wynikowy << wynik_Bruteforce << endl;         // koszt ścieżki
                            plik_wynikowy << czas_Bruteforce << " ms" << endl; // czas wykonania
                            for (int w : wierzcholkiBruteforce) {
                                plik_wynikowy << w << " ";
                            }
                            plik_wynikowy << endl;
                        }
                    }

                    liczba_iteracji = 1;

                    if(liczba_wierzcholkow <= 12){
                        for (int iter = 0; iter < liczba_iteracji; ++iter) {
                            cout << "Przetwarzanie pliku: " << nazwa_pliku_bez_sciezki << ", Iteracja: " << (iter + 1) << endl;
                            // -------------------- Random --------------------
                            vector<int> wierzcholkiRandom;
                            auto start_Random = chrono::high_resolution_clock::now();
                            double wynik_Random = TSPRandom(graf, start, wierzcholkiRandom, wynikOptymalny);
                            auto end_Random = chrono::high_resolution_clock::now();
                            auto czas_Random = chrono::duration_cast<chrono::milliseconds>(
                                    end_Random - start_Random).count();

                            // zapis do pliku wynikowego
                            plik_wynikowy << nazwa_pliku_bez_sciezki << endl;                // plik z grafem
                            plik_wynikowy << liczba_wierzcholkow << endl;        // rozmiar grafu
                            plik_wynikowy << "Random" << endl;          // jaki algorytm
                            plik_wynikowy << iter + 1 << endl;                    // która iteracja
                            plik_wynikowy << wynik_Random << endl;      // koszt ścieżki
                            plik_wynikowy << czas_Random << " ms" << endl; // czas wykonania
                            for (int w: wierzcholkiRandom) {
                                plik_wynikowy << w << " ";
                            }
                            plik_wynikowy << endl;
                        }
                    }

                    liczba_iteracji = 1;

                    for (int itera = 0; itera < liczba_iteracji; ++itera) {
                        cout << "Przetwarzanie pliku: " << nazwa_pliku_bez_sciezki << ", Iteracja: " << (itera + 1) << endl;
                        // -------------------- NearestNeighbor --------------------
                        vector<int> wierzcholkiNearestNeighbor;
                        auto start_NearestNeighbor = chrono::high_resolution_clock::now();
                        double wynik_NearestNeighbor = TSPNearestNeighbor(graf, start, wierzcholkiNearestNeighbor,
                                                                          wynikOptymalny);
                        auto end_NearestNeighbor = chrono::high_resolution_clock::now();
                        auto czas_NearestNeighbor = chrono::duration_cast<chrono::milliseconds>(
                                end_NearestNeighbor - start_NearestNeighbor).count();

                        // zapis do pliku wynikowego
                        plik_wynikowy << nazwa_pliku_bez_sciezki << endl;                // plik z grafem
                        plik_wynikowy << liczba_wierzcholkow << endl;        // rozmiar grafu
                        plik_wynikowy << "NearestNeighbor" << endl;                    // jaki algorytm
                        plik_wynikowy << itera + 1 << endl;                    // która iteracja
                        plik_wynikowy << wynik_NearestNeighbor << endl;                // koszt ścieżki
                        plik_wynikowy << czas_NearestNeighbor << " ms" << endl;        // czas wykonania
                        for (int w: wierzcholkiNearestNeighbor) {
                            plik_wynikowy << w << " ";
                        }
                        plik_wynikowy << endl;
                    }
                }
    
                plik_wynikowy << "" << endl;
                plik_wynikowy << "" << endl;
                plik_wynikowy << "Jak odczytywac plik wynikowy?" << endl;
                plik_wynikowy << "Nazwa pliku z grafem" << endl;
                plik_wynikowy << "Rozmiar grafu" << endl;
                plik_wynikowy << "Algorytm" << endl;
                plik_wynikowy << "Ktora iteracja" << endl;
                plik_wynikowy << "Koszt sciezki" << endl;
                plik_wynikowy << "Czas wykonania" << endl;
                plik_wynikowy << "Sciezka" << endl;
    
                plik_wynikowy.close(); // zamknij plik po zakonczeniu wszystkich obliczen
                break;
        }

    cin.get();

    return 0;
}





/*
w pliku nazwy sa wg tej konwencji:
nazwa_pliku_z_danymi
wybrany_algorytm
ilosc_powtorzen
 */

void readConfig(string& nazwa_pliku,int& iteracje,int& wybor_algorytmu){

    // UZYWAC DO PRACY W CLION
    ifstream configFile("../config.txt");

    // UZYWAC DO PRACY W CMD
    //ifstream configFile("config.txt");

    if (configFile.is_open()) {
        //cout << "Otwarto plik konfiguracyjny";
        getline(configFile, nazwa_pliku);       // nazwa pliku z danymi
        configFile >> wybor_algorytmu;          // wybór algorytmu
        configFile >> iteracje;                 // ilość powtórzeń

        configFile.close();                     // zamykamy plik po odczycie
    } else {
        cerr << "Nie mozna otworzyc pliku konfiguracyjnego" << endl;
    }

}

/*string& nazwa_pliku*/
vector<vector<double>> parseTXT(string& nazwa_pliku, double& wynikOptymalny) {

    string czesc_sciezki = "../data/";
    nazwa_pliku = czesc_sciezki + nazwa_pliku;

    // UZYWAC TEGO DO CMD
//    cout << "Nazwa pliku to " << nazwa_pliku << endl;
//    if (nazwa_pliku.rfind("../", 0) == 0) { // Sprawdza, czy ścieżka zaczyna się od "../"
//        nazwa_pliku.erase(0, 3); // Usuwa pierwsze trzy znaki "../"
//    }
//    cout << "Poprawiona nazwa pliku to " << nazwa_pliku << endl;

    // ZWYKLA NAZWE PLIKU UZYWAC DO CLIONA
    ifstream plikTXT(nazwa_pliku);
    if (!plikTXT.is_open()) {
        cerr << "Nie mozna otworzyc pliku z grafem!" << endl;
    }

    // pierwsza linijka to rozmiar grafu
    int n;
    plikTXT >> n;

    //macierz n x n
    vector<vector<double>> macierz_sasiedztwa(n, vector<double>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            plikTXT >> macierz_sasiedztwa[i][j];
        }
    }

    plikTXT >> wynikOptymalny;
    
    plikTXT.close();

    return macierz_sasiedztwa;
}

double TSPBruteforce(vector<vector<double>> graf, int start, vector<int>& wierzcholki_sciezki_minimalnej, double wartoscOptymalna) {
    int n = graf.size();
    vector<int> wierzcholki;

    // dodajemy wszystkie wierzchołki poza startowym do permutowania
    for (int i = 0; i < n; i++) {
        if (i != start) {
            wierzcholki.push_back(i);
        }
    }

    double minimalna_sciezka = INT_MAX;
    vector<int> bufor_wierzcholkow;
    auto czas_poczatkowy = chrono::high_resolution_clock::now();

    do {

        // koszt permutacji
        double koszt = 0;
        int obecny_wierzcholek = start;

        bufor_wierzcholkow.clear();
        bufor_wierzcholkow.push_back(start);

        bool istnieje_krawedz = true;

        // przejście przez wszystkie wierzchołki w permutacji
        for (int wierzcholek : wierzcholki) {
            // sprawdzenie czy krawedz do nastepnego wierzcholka istnieje
            // <<graf niepełny>>
            if (graf[obecny_wierzcholek][wierzcholek] == 0) {
                istnieje_krawedz = false;  // brak krawedzi, przerywamy te permutacje
                break;
            }
            koszt += graf[obecny_wierzcholek][wierzcholek];
            bufor_wierzcholkow.push_back(wierzcholek);
            obecny_wierzcholek = wierzcholek;
        }

        // powrót do wierzchołka początkowego
        // jesli istnieje krawedz
        if (istnieje_krawedz && graf[obecny_wierzcholek][start] != 0) {
            koszt += graf[obecny_wierzcholek][start];
            bufor_wierzcholkow.push_back(start);

            // sprawdzenie, czy osiągnięto wartość optymalną
            if (koszt == wartoscOptymalna && wartoscOptymalna != -2) {
                wierzcholki_sciezki_minimalnej = bufor_wierzcholkow;
                for (int k : wierzcholki_sciezki_minimalnej) {
                    cout << k << " ";
                }
                cout << endl;
                return wartoscOptymalna;
            }

            // aktualizacja minimalnej ścieżki, jeśli znaleziono lepszą
            if (koszt < minimalna_sciezka) {
                minimalna_sciezka = koszt;
                wierzcholki_sciezki_minimalnej = bufor_wierzcholkow;
            }
        }


        // WARUNEK 30 MINUT
        auto obecny_czas = chrono::high_resolution_clock::now();
        auto miniony_czas = chrono::duration_cast<chrono::minutes>(obecny_czas - czas_poczatkowy);
        if (miniony_czas.count() >= 30) {
            cout << "Czas wykonania przekroczyl 30 minut. Program zakonczony." << endl;
            return minimalna_sciezka;
        }

    } while (next_permutation(wierzcholki.begin(), wierzcholki.end()));
    // i tak dla wszystkich permutacji
    // lepiej wykonywac biezaca permutacje dla kazdego obliczenia
    // niz wektor ze wszystkimi permutacjami

    // wyświetlenie minimalnej ścieżki
    for (int k : wierzcholki_sciezki_minimalnej) {
        cout << k << " ";
    }
    cout << endl;

    if(minimalna_sciezka == INT_MAX){
        cout << "Rozwiazanie nie istnieje" << endl;
        return 0;
    }

    return minimalna_sciezka;
}


double TSPRandom(vector<vector<double>> graf, int start, vector<int>& wierzcholki_sciezki_minimalnej, double wartoscOptymalna) {
    int n = graf.size();
    vector<int> wierzcholki;

    // wszystkie wierzchołki poza startowym
    for (int i = 0; i < n; i++) {
        if (i != start) {
            wierzcholki.push_back(i);
        }
    }

    double minimalna_sciezka = INT_MAX;
    vector<int> bufor_wierzcholkow;

    // wprowadzamy losowosc przez inicjalizacje generatora losowego
    random_device rd;
    mt19937 g(rd());

    set<vector<int>> odwiedzone_permutacje;

    auto czas_poczatkowy = chrono::high_resolution_clock::now();

    while (true) {

        // losowa permutacja wierzchołków
        do {
            shuffle(wierzcholki.begin(), wierzcholki.end(), g);
        } while (odwiedzone_permutacje.find(wierzcholki) != odwiedzone_permutacje.end());
        // permutacje się nie powtarzają
        odwiedzone_permutacje.insert(wierzcholki);

        // obliczenie kosztu dla danej losowej permutacji
        double koszt = 0;
        int obecny_wierzcholek = start;

        bufor_wierzcholkow.clear();
        bufor_wierzcholkow.push_back(start);

        bool istnieje_krawedz = true;

        for (int wierzcholek : wierzcholki) {
            // czy istnieje krawędź z obecnego wierzchołka do kolejnego
            if (graf[obecny_wierzcholek][wierzcholek] == 0) {
                istnieje_krawedz = false;  // Brak krawędzi, przerywamy tę permutację
                break;
            }
            koszt += graf[obecny_wierzcholek][wierzcholek];
            bufor_wierzcholkow.push_back(wierzcholek);
            obecny_wierzcholek = wierzcholek;
        }

        // czy mozna wrocic do wierzcholka poczatkowego
        if (istnieje_krawedz && graf[obecny_wierzcholek][start] != 0) {
            koszt += graf[obecny_wierzcholek][start];
            bufor_wierzcholkow.push_back(start);

            // czy osiągnięto wartość optymalną
            // WARUNEK WARTOSC OPTYMALNA
            if (koszt == wartoscOptymalna && wartoscOptymalna != -2) {
                wierzcholki_sciezki_minimalnej = bufor_wierzcholkow;
                for (int k : wierzcholki_sciezki_minimalnej) {
                    cout << k << " ";
                }
                cout << endl;
                return wartoscOptymalna;
            }

            // aktualizacja minimalnej ścieżki, jeśli znaleziono lepszą
            if (koszt < minimalna_sciezka) {
                minimalna_sciezka = koszt;
                wierzcholki_sciezki_minimalnej = bufor_wierzcholkow;
            }
        }

        // WARUNEK 30 MINUT
        auto obecny_czas = chrono::high_resolution_clock::now();
        auto miniony_czas = chrono::duration_cast<chrono::minutes>(obecny_czas - czas_poczatkowy);
        if (miniony_czas.count() >= 30) {
            cout << "Czas wykonania przekroczyl 30 minut. Program zakonczony." << endl;
            if (minimalna_sciezka == INT_MAX) {
                cout << "Rozwiazanie nie istnieje" << endl;
                return 0;
            }
            return minimalna_sciezka;
        }

    }  // WARUNEK PRZEGLAD ZUPELNY
    // dla wszystkich permutacji

    for (int k : wierzcholki_sciezki_minimalnej) {
        cout << k << " ";
    }
    cout << endl;

    if (minimalna_sciezka == INT_MAX) {
        cout << "Rozwiazanie nie istnieje" << endl;
        return 0;
    }

    return minimalna_sciezka;
}


double TSPNearestNeighbor(vector<vector<double>> graf, int start, vector<int>& wierzcholki_sciezki_minimalnej, double wartoscOptymalna) {
    vector<int> bufor_wierzcholkow;
    vector<bool> odwiedzone(graf.size(), false);

    odwiedzone[start] = true;
    int obecny_wierzcholek = start;
    double koszt = 0;

    wierzcholki_sciezki_minimalnej.clear();
    wierzcholki_sciezki_minimalnej.push_back(start);

    auto czas_poczatkowy = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < graf.size(); i++) {
        auto obecny_czas = std::chrono::high_resolution_clock::now();
        auto miniony_czas = std::chrono::duration_cast<std::chrono::minutes>(obecny_czas - czas_poczatkowy);


        //koszt = 0;
        int nastepny_wierzcholek = -1;
        double minimalna_sciezka = INT_MAX;

        for (int j = 0; j < graf.size(); j++) { //szukamy najblizszego wierzcholka wzgledem wierzcholka z indeksem i
            if (!odwiedzone[j] && graf[obecny_wierzcholek][j] < minimalna_sciezka) { // jesli wierzcholek nie zostal odwiedzony i znaleziono lepsza krawedz
                minimalna_sciezka = graf[obecny_wierzcholek][j]; // aktualizujemy dystans
                //bufor_wierzcholkow.push_back(j); // dodajemy wierzcholek do bufora
                nastepny_wierzcholek = j;
            }
        }

        if (nastepny_wierzcholek == -1 || minimalna_sciezka == INT_MAX) {
            cout << "Rozwiazanie nie istnieje, brak krawedzi do nieodwiedzonego wierzcholka" << endl;
            return 0;
        }

        odwiedzone[nastepny_wierzcholek] = true;
        koszt += minimalna_sciezka;

//        bufor_wierzcholkow.push_back(start);
//        obecny_wierzcholek = nastepny_wierzcholek;
//        wierzcholki_sciezki_minimalnej = bufor_wierzcholkow;
        wierzcholki_sciezki_minimalnej.push_back(nastepny_wierzcholek);
        obecny_wierzcholek = nastepny_wierzcholek;

        if (miniony_czas.count() >= 30) {
            cout << "Czas wykonania przekroczyl 30 minut. Program zakonczony." << endl;
            return koszt;
        }
    }

    if(koszt == wartoscOptymalna && wartoscOptymalna != -2){
        wierzcholki_sciezki_minimalnej = bufor_wierzcholkow;
        for (int k = 0; k < graf.size() + 1; k++){ // + 1 bo wracamy do wierzcholka poczatkowego
            cout << wierzcholki_sciezki_minimalnej[k] << " ";
        }
        return wartoscOptymalna;
    }

    // iterujemy przez kazdy istniejacy wierzcholek jaka sciezka
    // np: od wierzcholka startowego 0 przechodzimy do wierzcholka 1, nie sprawdzamy krawedzi 01 bo już jest odwiedzona
    // zatem od wierzchołka 1 sprawdzamy jego dystans z wierzcholkiem 2. Wierzcholek 2 nie byl odwiedzany i krawedz 01 jest mniejsza niz nieskonczonosc.
    // minimalny dystans od wierzcholka 1 do innego staje sie dlugoscia krawedzi 12.

    if(graf[obecny_wierzcholek][start] != 0){
        koszt += graf[obecny_wierzcholek][start];
        wierzcholki_sciezki_minimalnej.push_back(start);
    } else {
        cout << "Rozwiazanie nie istnieje, brak sciezki powrotnej" << endl;
        return 0;
    }

    for (int k = 0; k < graf.size() + 1; k++){ // + 1 bo wracamy do wierzcholka poczatkowego
        cout << wierzcholki_sciezki_minimalnej[k] << " ";
    }
    cout << "" << endl;

    return koszt;
}

    // iterujemy przez kazdy istniejacy wierzcholek jaka sciezka
    // np: od wierzcholka startowego 0 przechodzimy do wierzcholka 1, nie sprawdzamy krawedzi 01 bo już jest odwiedzona
    // zatem od wierzchołka 1 sprawdzamy jego dystans z wierzcholkiem 2. Wierzcholek 2 nie byl odwiedzany i krawedz 01 jest mniejsza niz nieskonczonosc.
    // minimalny dystans od wierzcholka 1 do innego staje sie dlugoscia krawedzi 12.

/*
 Losowe + Brute Force + Pierwszy sąsiad
 Z wierzchu wierzcholki poczatkowe
 Z boku wierzcholki docelowe
    0   1   2   3
0   0   8   9   7
1   8   0   3   1
2   9   3   0   1
3   7   1   1   0
 Startowy -> 0
 0 -> permutacja reszty -> 0
 np.
 0 -> 3 -> 2 -> 1 -> 0
 03 + 32 + 21 + 10
 Czyli rozwazamy krawedzi
 Graf[0][3]+Graf[3][2]+Graf[2][1]+Graf[1][0]
 A że będziemy rozważać wszystkie permutacje
 Graf[s][x1]+Graf[x1][x2]+Graf[x2][x3]+Graf[x3][s]
 Czyli dla V wierzcholkow
 Graf[s][x1]+Graf[x1][x2]+...+Graf[xn-1][xn]+Graf[xn][s]
 */
