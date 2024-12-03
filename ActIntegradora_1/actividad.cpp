#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return "";
    }

    string contenido((istreambuf_iterator<char>(archivo)),
                           istreambuf_iterator<char>());

    archivo.close();
    return contenido;
}

bool repeat(string mcode, string transmission, bool print) {
    for (int i = 0; i < (transmission.length() - mcode.length()); i++){
        if (transmission[i] == mcode[0]){
            bool check = false;
            for (int j = 1; j < mcode.length(); j++){
                if (transmission[i+j] != mcode[j]) {
                    check = true;
                    break;
                }
            }
            if (!check) {
                if (print) {
                    cout << "true " << i + 1 << endl;
                }
                return true;
            }
        }
    }return false;
}

void palindrome(string transmission){
    string pal = "";
    int l = 0;
    int ini = 0;
    int fin = 0;
    int jj = 0;
    int ii = 0;
    for (int i = 0; i < transmission.length(); i++){
        for (int j = i + 1; j < transmission.length(); j++){
            bool check = true;
            if (j - i > l){
                jj = j;
                ii = i;
                while (i < j){
                    if (transmission[i] != transmission[j]){
                        check = false;
                        break;
                    }
                    i++;
                    j--;
                }
                if (check == true){
                    l = jj - ii;
                    ini = ii;
                    fin = jj;
                }
            }
            
        }
    }
    cout << ini+1 << " " << fin+1 << endl;
}

void longesSubstring(string transmission1, string transmission2) {
    int l = 0;
    int ini = 0;
    int fin = 0;
    for (int i = 0; i < transmission1.length(); i++) {
        for (int j = i + 1; j < transmission1.length(); j++){
            if (repeat(transmission1.substr(i,j), transmission2, false) && j - i > l) {
                l = j - i;
                ini = i;
                fin = j;
            }
        }
    }
    cout << ini+1 << " " << fin+1 << endl;
}


int main() {
    string mcode1 = leerArchivo("mcode1.txt");
    string mcode2 = leerArchivo("mcode2.txt");
    string mcode3 = leerArchivo("mcode3.txt");

    string transmission1 = leerArchivo("transmission1.txt");
    string transmission2 = leerArchivo("transmission2.txt");

    cout << "Prueba 1" << endl;
    repeat(mcode1, transmission1, true);

    cout << endl;
    cout << "Prueba 2" << endl;
    palindrome(transmission2);

    cout << endl;
    cout << "Prueba 3" << endl;
    longesSubstring(transmission1,transmission2);

    return 0;
}
