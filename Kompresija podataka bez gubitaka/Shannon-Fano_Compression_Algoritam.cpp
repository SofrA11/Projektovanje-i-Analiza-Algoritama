// C++ program for Shannon Fano Algorithm

// include header files
#include <iostream>
using namespace std;

// declare structure node
struct node {

    // for storing symbol
    string karakter;

    //Predstavlja ucestanost pojavljivanja simobla
    float ucestanost;
    int arr[20];
    //Sadrzi vrh steka
    int top;
} cvor[20]; //Niz cvorova koji sluzi za cuvanje karaktera i njihove ucestanosti

typedef struct node node;



// Funkcija za pronalazenje shanon-ovog koda
//low predstavlja donji indeks od koga se ide
//high predstavlja gornju granicu indeksa do koje se ide
// low i high ogranicavaju blok karaktera konkretne rekurzije
void shannon(int low, int high, node shannon_cvor[])
{
    float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
    int i, d, k, j;
    if ((low + 1) == high || low == high || low > high) {
        if (low == high || low > high)
            return;
        shannon_cvor[high].arr[++(shannon_cvor[high].top)] = 0; //assigns 0 to the symbol, if length is 2 to the highest probability symbol
        shannon_cvor[low].arr[++(shannon_cvor[low].top)] = 1;//assigns 1 to the symbol if length is 2 to the lowest probability symbol
        return;
    }
    else {
        //Sum of all probabilities expect the last one i.e, the highest probability
        for (i = low; i <= high - 1; i++)
            pack1 = pack1 + shannon_cvor[i].ucestanost;

        pack2 = pack2 + shannon_cvor[high].ucestanost;//Last Probability
        diff1 = pack1 - pack2;//Difference between the Sum of all probabilities and last probability i.e, Alpha

        //If difference is negative
        if (diff1 < 0)
            diff1 = diff1 * -1;

        j = 2;
        //Loop to find the number of bits required
        while (j != high - low + 1) {
            k = high - j;
            pack1 = pack2 = 0;
            //Sum of all probabilities
            for (i = low; i <= k; i++)
                pack1 = pack1 + shannon_cvor[i].ucestanost;

            for (i = high; i > k; i--)
                pack2 = pack2 + shannon_cvor[i].ucestanost;

            diff2 = pack1 - pack2;

            //If difference is negative
            if (diff2 < 0)
                diff2 = diff2 * -1; //Make it positive  to compare with the previous difference

            //If difference is greater than previous difference
            if (diff2 >= diff1)
                break;

            diff1 = diff2;//Assign the difference to previous difference
            j++; //Increment the number of bits
        }
        k++;
        //Assign 1 to the symbols with the lowest probability
        for (i = low; i <= k; i++)
            shannon_cvor[i].arr[++(shannon_cvor[i].top)] = 1;

        //Assign 0 to the symbols with the highest probability
        for (i = k + 1; i <= high; i++)
            shannon_cvor[i].arr[++(shannon_cvor[i].top)] = 0;

        // Invoke shannon function
        shannon(low, k, shannon_cvor); //Recursive call to the function to assign the symbols with the lowest probability
        shannon(k + 1, high, shannon_cvor);//Recursive call to the function to assign the symbols with the highest probability
    }
}

//Funkcija sortira karaktere na osnovu njihove ucestanosti, u rastucem redosledu.
void sortByProbability(int n, node cvor_za_sortiranje[])
{
    int i, j;
    //Pomocni cvor koji pomaze pri sortiranju
    node pom;
    for (j = 1; j <= n - 1; j++) {
        for (i = 0; i < n - 1; i++) {
            if ((cvor_za_sortiranje[i].ucestanost) > (cvor_za_sortiranje[i + 1].ucestanost)) {
                pom.ucestanost = cvor_za_sortiranje[i].ucestanost;
                pom.karakter = cvor_za_sortiranje[i].karakter;

                cvor_za_sortiranje[i].ucestanost = cvor_za_sortiranje[i + 1].ucestanost;
                cvor_za_sortiranje[i].karakter = cvor_za_sortiranje[i + 1].karakter;

                cvor_za_sortiranje[i + 1].ucestanost = pom.ucestanost;
                cvor_za_sortiranje[i + 1].karakter = pom.karakter;
            }
        }
    }
}

// Funkcija za prikazivanje koda
void display(int n, node p[])
{
    int i, j;
    cout << "\n\n\n\tSymbol\tUcestanost\tCode";
    for (i = n - 1; i >= 0; i--) {
        cout << "\n\t" << p[i].karakter << "\t\t" << p[i].ucestanost << "\t";
        for (j = 0; j <= p[i].top; j++)
            cout << p[i].arr[j];
    }
}

// Driver code
int main()
{
    int n, i, j;
    float total = 0;
    string ch;
    node temp;

    // Input number of symbols
    cout << "Enter number of symbols\t: ";
    n = 5;
    cout << n << endl;

    // Input symbols
    for (i = 0; i < n; i++) {
        cout << "Enter symbol " << i + 1 << " : ";
        ch = (char)(65 + i);
        cout << ch << endl;

        // Insert the symbol to node
        cvor[i].karakter += ch;
    }

    // Input probability of symbols
    float x[] = { 0.22, 0.28, 0.15, 0.30, 0.05 };
    for (i = 0; i < n; i++) {
        cout << "\nEnter probability of " << cvor[i].karakter << " : ";
        cout << x[i] << endl;

        // Insert the value to node
        cvor[i].ucestanost = x[i];
        total = total + cvor[i].ucestanost;

        // checking max probability
        if (total > 1) {
            cout << "Invalid. Enter new values";
            total = total - cvor[i].ucestanost;
            i--;
        }
    }

    cvor[i].ucestanost = 1 - total;

    // Sorting the symbols based on
    // their probability or frequency
    sortByProbability(n, cvor);

    for (i = 0; i < n; i++)
        cvor[i].top = -1;

    // Find the shannon code
    shannon(0, n - 1, cvor);

    // Display the codes
    display(n, cvor);
    return 0;
}
