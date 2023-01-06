//Brebenel Dimitria, 321AC

#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
#include <random>
#include <sstream>

using namespace std;

class Actori
{
public:
    string name[800];
    string rol[800];


    int castFirst=0; // cast-ul initial, cel din wednesdayCast.csv

    void citireFirst() // citesc actorii din primul fisier CSV, wednesdayCast.csv
    {
        ifstream file("wednesdayCast.csv");
        string line;
        while(getline(file, line)) // citesc linie cu linie si ma folosesc getline
        {
            int lungime=line.length();
            char linie[lungime+1];
            strcpy(linie, line.c_str());

            char* token=strtok(linie, ",");
            name[castFirst]=token;
            token=strtok(NULL, ",");
            rol[castFirst]=token;

            castFirst++;
        }
        file.close();
    }

    void generareFiguranti(int nrFiguranti) // generez 132 de figuranti
    {
        int i;
        ofstream fout("figuranti.csv");

        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> genereazaNume(1, 100);


        for(i=1; i<=nrFiguranti; i++)
        {
            rol[i]="figurant";
            string numeF = this->name[genereazaNume(generator)];
            fout<<numeF<<","<<rol[i]<< endl;
        }
        fout.close();
    }

    void unire(string numeFisier, string numeFisier2) // unesc cele doua fisiere si creez unul nou
    {
        ifstream file1(numeFisier);
        ifstream file2(numeFisier2);

        ofstream outFile("castFinal.csv");

        string line;
        while (getline(file1, line))
        {
            outFile << line << "\n";
        }

        while (getline(file2, line))
        {
            outFile << line << "\n";
        }

        file1.close();
        file2.close();
        outFile.close();
    }
};

class AsignareCast
{
public:
    void distribuieActori(string numeFisier)
    {
        ifstream file(numeFisier);
        string line;

        random_device rd; // generator de numere aleatoare
        mt19937 generator(rd()); 
        uniform_int_distribution<int> distribuieMonstri(0, 4); // distribuie numere intre 0 si 4

        int numarActori = 0;
        ofstream file_iesire("distribuire.csv");
        file_iesire << "Nume,Rol,Tip Monstru,Cost Machiaj in lei" << endl;
        while (getline(file, line))
        {
            numarActori++;
            string nume, rol,tipMonstru;
            int costMachiaj;

            int pozitieVirgula = line.find(','); // gasim pozitia virgulei din fisier
            nume = line.substr(0, pozitieVirgula); // numele se afla inainte de virgula
            rol = line.substr(pozitieVirgula+1); // rolul se afla dupa virgula

            // verificam daca rolul este "actor" sau "figurant"
            if (!strncmp(rol.c_str(), "actor", 5)) rol = "actor";
            if (rol == "actor" || rol == "figurant")
            {
                int clasaMonstru = distribuieMonstri(generator); // alegem o clasa de monstri

                switch (clasaMonstru)
                {
                case 0:
                    tipMonstru = "Vampiri";
                    costMachiaj = 230;
                    break;
                case 1:
                    tipMonstru = "Vârcolaci";
                    costMachiaj = 555;
                    break;
                case 2:
                    tipMonstru = "Sirene";
                    costMachiaj = 345;
                    break;
                case 3:
                    tipMonstru = "Clarvazatori";
                    costMachiaj = 157;
                    break;
                case 4:
                    tipMonstru = "Om";
                    costMachiaj = 55;
                    break;
                }

                // scriem informatiile intr-un fisier de iesire

                file_iesire << nume << "," << rol << "," << tipMonstru << "," << costMachiaj << std::endl;
            }
        }

        file.close();
        file_iesire.close();
    }

    void asiguraMancare(string numeFisier)
    {
        fstream file(numeFisier);
        string line;

        random_device rd; // generator de numere aleatoare
        mt19937 generator(rd()); 
        uniform_int_distribution<int> distribuieDiete(0, 2); // distribuie numere intre 0 si 2

        int numarActori = 0;
        int costTotal = 0;
        ofstream file_iesire("pranz.csv");
        file_iesire << "Nume, Tip, Cost pranz in lei" << endl;
        while (getline(file, line))
        {
            numarActori++;
            string nume, dieta;
            int costTotal;

            int pozitieVirgula = line.find(','); // gasim pozitia virgulei din fisier
            nume = line.substr(0, pozitieVirgula); // numele se afla inainte de virgula

            {
                // alegem o dieta la intamplare
                int dietaAleasa = distribuieDiete(generator);
                switch (dietaAleasa)
                {
                case 0:
                    dieta = "orice";
                    costTotal = 40;
                    break;
                case 1:
                    dieta = "vegetariana";
                    costTotal = 33;
                    break;
                case 2:
                    dieta = "flexitariana";
                    costTotal = 46;
                    break;
                }
                file_iesire << nume << "," << dieta <<"," << costTotal << std::endl;
            }
        }

        file.close();

    }

    void creareaMeniu()
    {
        ofstream file1;
        file1.open("meniuRomana.csv");

        file1<<"Persoane apte sa manance orice: "<<endl;

        file1<<"Supa de pui" << "," << "Cheeseburger" << "," << "Tarta cu fructe de padure" <<endl;
        file1<<"Supa crema de legume" << "," << "Pizza" << "," << "Brownies" <<endl;
        file1<<"Supa crema de broccoli" << "," << "Spaghetti" << "," << "Cheesecake" <<endl;

        file1<<"Persoane flexitariene: "<<endl;
        file1<<"Supa crema de ciuperci" << "," << "Burger cu somon" << "," << "Tarta cu fructe de padure" <<endl;
        file1<<"Supa crema de legume" << "," << "Peste cu cartofi" << "," << "Brownies" <<endl;
        file1<<"Supa crema de broccoli" << "," << "Risotto cu fructe de mare" << "," << "Cheesecake" <<endl;

        file1<<"Persoane vegetariene: "<<endl;
        file1<<"Supa crema de ciuperci" << "," << "Burger vegan" << "," << "Tarta cu fructe de padure" <<endl;
        file1<<"Supa crema de legume" << "," << "Salata greceasca" << "," << "Brownies" <<endl;
        file1<<"Supa crema de broccoli" << "," << "Risotto cu ciuperci" << "," << "Cheesecake" <<endl;

        file1.close();

        ofstream file2;
        file2.open("meniuEngleza.csv");

        file2<<"People able to eat anything-Menu"<<endl;

        file2<<"Chicken soup" << "," << "Cheeseburger" << "," << "Berry tart" <<endl;
        file2<<"Vegetable cream soup" << "," << "Pizza" << "," << "Brownies" <<endl;
        file2<<"Cream of broccoli soup" << "," << "Spaghetti" << "," << "Cheesecake" <<endl;

        file2<<"Flexitarian people-Menu "<<endl;
        file2<<"Cream of mushroom soup" << "," << "Salmon burger" << "," << "Berry tart" <<endl;
        file2<<"Vegetable cream soup" << "," << "Fish and Chips" << "," << "Brownies" <<endl;
        file2<<"Cream of broccoli soup" << "," << "Seafood risotto" << "," << "Cheesecake" <<endl;

        file2<<"Vegetarian people-Menu"<<endl;
        file2<<"Cream of mushroom soup" << "," << "Vegan burger " << "," << "Berry tart" <<endl;
        file2<<"Vegetable cream soup" << "," << "Greek salad" << "," << "Brownies" <<endl;
        file2<<"Cream of broccoli soup" << "," << "Mushrooms risotto" << "," << "Cheesecake" <<endl;

        file2.close();
    }

};

class Cost
{
public:

    int citireActori() // pentru a vedea numarul cast-ului initial
    {
        ifstream file("wednesdayCast.csv");
        string line;
        int numarActori = 0;

        while (getline(file, line))
        {
            numarActori++;
        }

        file.close();

        return numarActori;
    }

    int citireFiguranti() // pentru a vedea numarul figurantilor
    {
        ifstream file("figuranti.csv");
        string line;
        int numarFiguranti = 0;

        while (getline(file, line))
        {
            numarFiguranti++;
        }

        file.close();

        return numarFiguranti;
    }

    void calculCazare(int numarActori, int numarFiguranti, int costCamera2Persoane, int costCamera3Persoane)
    {
        int numarCamere2Persoane = ceil((double) numarActori / 2.0); // calculeaza de cate camera de 2 persoane o sa avem nevoie
        int costPerNoapte2Persoane = numarCamere2Persoane * costCamera2Persoane; // calculeaza costul pe noapte a camerelor de 2 persoane

        int numarCamere3Persoane = ceil((double) numarFiguranti / 3.0); // calculeaza de camere de 3 persoane o sa avem nevoie
        int costPerNoapte3Persoane = numarCamere3Persoane * costCamera3Persoane; // calculeaza costul pe noapte a camerelor de 3 persoane

        int costTotalPerNoapte = costPerNoapte2Persoane + costPerNoapte3Persoane; // costul total a unei singure nopti

        ofstream foutL;
        foutL.open("costLei.csv", ios::app);
        foutL<<"Cazare: "<<endl;
        foutL << "Costul total pentru toate camerele pentru 30, 45, 60 si 100 de zile: " << 30*costTotalPerNoapte << " lei"<< ", " << 45*costTotalPerNoapte << " lei"<< ", " << 60*costTotalPerNoapte << " lei"<<", "<< 100*costTotalPerNoapte << " lei"  <<endl;
        foutL.close();
       
        ofstream foutD;
        foutD.open("costDolari.csv", ios::app);
        foutD<<"Accommodation"<<endl;
        foutD<< fixed << "Total cost for all rooms for 30, 45, 60 and 100 days: " << (30*costTotalPerNoapte)/4.64 << " dollars"<< ", " << (45*costTotalPerNoapte)/4.64 << " dollars"<< ", " << (60*costTotalPerNoapte)/4.64 << " dollars"<<", "<< (100*costTotalPerNoapte)/4.64 << " dollars"  <<endl;
        foutD.close();
        
    }

    int citireTotal() // pentru a vedea numarul total
    {
        ifstream file("castFinal.csv");
        string line;
        int numarPersoane = 0;

        while (getline(file, line))
        {
            numarPersoane++;
        }

        file.close();

        return numarPersoane;
    }

    void calculTransport(int numarPersoane) // calcularea costului pentru transportul actorilor
    {
        int costAutocar=5680;
        int numarAutocare = ceil((double) numarPersoane / 50.0); // calcularea numarului de autocare necesare (rontunjire la urmatorul intreg mai mare, deoarece avem 17 autocare de 50 de persoane si unul cu 17 persoane)
        int costTransport = numarAutocare * costAutocar; // costului total doar pentru dus

        ofstream foutL;
        foutL.open("costLei.csv", ios::app);
        foutL<<"Transport: "<<endl;
        foutL << "Numarul de autocare necesare: " << numarAutocare << endl;
        foutL << "Costul total pentru transport exprimat in lei: " << 2*costTransport << " lei" << endl; // costul transportului dus-intors in lei
        foutL.close();
        
        ofstream foutD;
        foutD.open("costDolari.csv",ios::app);
        foutD<<"Transport: "<<endl;
        foutD << "Number of buses needed: " << numarAutocare << endl;
        foutD << "The total cost for transportation expressed in dollars: " << (2*costTransport)/4.64 << " dollars" << endl; // costul transportului dus-intors in dolari
        foutD.close();
        
    }


    void calculMancareApa(int numarPersoane)
    {
        ifstream file("pranz.csv");

        // Declaram variabilele pentru costurile totale pentru fiecare tip de dieta
        int costTotalOricine = 0;
        int costTotalVegetarian = 0;
        int costTotalFlexitarian = 0;

        string linie;
        while (getline(file, linie))
        {
            // Separarea valorilor prin utilizarea strtok si virgula ca delimitator
            char* linieC = strdup(linie.c_str());
            char* nume = strtok(linieC, ",");
            char* dieta = strtok(NULL, ",");

            // Adauga?i costul corespunzator la totaluri
            if (strcmp(dieta, "orice") == 0)
            {
                costTotalOricine += 40;
            }
            else if (strcmp(dieta, "vegetariana") == 0)
            {
                costTotalVegetarian += 33;
            }
            else if (strcmp(dieta, "flexitariana") == 0)
            {
                costTotalFlexitarian += 46;
            }
        }

        file.close();

        int costTotalPranz = costTotalOricine + costTotalVegetarian + costTotalFlexitarian;
        float costTotalBauturi= (6/2)*numarPersoane+(30*0.5)*numarPersoane+((8*0.8)/2)*numarPersoane;

        float costTotalMancareApa= costTotalPranz + costTotalBauturi;

        ofstream foutL;
        foutL.open("costLei.csv", ios::app);
        foutL<<"Mancare si apa: "<<endl;
        foutL<<fixed << "Costul total pentru mancare si apa pentru 30, 45, 60 si 100 de zile: " << 30*costTotalMancareApa << " lei"<< ", " << 45*costTotalMancareApa << " lei"<< ", " << 60*costTotalMancareApa << " lei"<<", "<< 100*costTotalMancareApa << " lei"  <<endl;
        foutL.close();

        ofstream foutD;
        foutD.open("costDolari.csv",ios::app);
        foutD<<"Food and Water: "<<endl;
        foutD<<fixed<< "Total cost for food and water for 30, 45, 60 and 100 days: " << (30*costTotalMancareApa)/4.64 << " dollars"<< ", " << (45*costTotalMancareApa)/4.64 << " dollars"<< ", " << (60*costTotalMancareApa)/4.64 << " dollars"<<", "<< (100*costTotalMancareApa)/4.64 << " dollars"  <<endl;
        foutD.close();
        
    }

    void costMachiaj()
    {
        // deschide fisierul de ie?ire pentru citire
        ifstream file("distribuire.csv");

        // citim prima linie care con?ine titlurile coloanelor
        string line;
        getline(file, line);

        int costTotalMachiaj = 0; // variabila pentru costul total
        while (getline(file, line))
        {
            string nume, rol, tipMonstru;
            int costMachiaj;

            // citim informatiile pentru fiecare persoana
            stringstream linie(line);
            getline(linie, nume, ',');
            getline(linie, rol, ',');
            getline(linie, tipMonstru, ',');
            linie >> costMachiaj;

            // adaugam costul zilnic de machiaj pentru aceasta persoana la costul total
            costTotalMachiaj += costMachiaj;
        }
        file.close();

        ofstream foutL;
        foutL.open("costLei.csv", ios::app);
        foutL<<"Machiaj: "<<endl;
        foutL<<fixed << "Costul total pentru machiaj pentru 30, 45, 60 si 100 de zile: " << 30*costTotalMachiaj << " lei"<< ", " << 45*costTotalMachiaj << " lei"<< ", " << 60*costTotalMachiaj << " lei"<<", "<< 100*costTotalMachiaj << " lei"  <<endl;
        foutL.close();

        ofstream foutD;
        foutD.open("costDolari.csv",ios::app);
        foutD<<"Make-up: "<<endl;
        foutD<<fixed<< "The total cost for makeup for 30, 45, 60 and 100 days: " << (30*costTotalMachiaj)/4.64 << " dollars"<< ", " << (45*costTotalMachiaj)/4.64 << " dollars"<< ", " << (60*costTotalMachiaj)/4.64 << " dollars"<<", "<< (100*costTotalMachiaj)/4.64 << " dollars"  <<endl;
        foutD.close();
       
    }

    void costInchiriere()
    {
        int i;
        int zile[]= {30, 45, 60, 100}; // vectorul de perioade de filmare
        ofstream foutL;
        foutL.open("costLei.csv", ios::app);
        foutL<<"Inchiriere spatiu: "<<endl;
        foutL<< "Costul total pentru inchirierea castelului Cantacuzino pentru 30, 45, 60 si 100 de zile: " ;


        ofstream foutD;
        foutD.open("costDolari.csv",ios::app);
        foutD<<"Rent for space: "<<endl;
        foutD<<"The total cost for renting the Cantacuzino castle for 30, 45, 60 and 100 days: " ;

        for (i=0; i<4; i++)
        {
            int x=zile[i];
            int reducere = 10000 * 2 * x / 100;
            int costTotalSpatiu = 10000 * x - reducere;

            foutL<<fixed << costTotalSpatiu <<" lei"<< " ," ;
            foutD<<fixed << (costTotalSpatiu)/4.64 <<" dollars"<<" ,";
        }

        foutL.close();
        foutD.close();
    }
};


int main()
{
    Actori actori;
    actori.citireFirst();
    actori.generareFiguranti(132);
    actori.unire("wednesdayCast.csv", "figuranti.csv");

    AsignareCast asignare;
    asignare.distribuieActori("castFinal.csv");
    asignare.asiguraMancare("castFinal.csv");
    asignare.creareaMeniu();

    Cost cost;
    int numarActori=cost.citireActori();
    int numarFiguranti=cost.citireFiguranti();
    int numarPersoane=cost.citireTotal();
    cost.calculTransport(numarPersoane);
    cost.calculCazare(numarActori, numarFiguranti, 350, 420);
    cost.calculMancareApa(numarPersoane);
    cost.costMachiaj();
    cost.costInchiriere();

    return 0;

}







