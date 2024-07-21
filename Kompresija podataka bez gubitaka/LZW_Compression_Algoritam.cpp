#include <unordered_map>
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
// Popunjavanje default dela tabele ASCII karakterima od 0 do 255
unordered_map<string, int> setDefault() {
	unordered_map<string, int> tabela;
	for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += (char)i;
		tabela[ch] = i;
	}
	return tabela;
}
vector<int> encoding(string ulazni_niz_karaktera)
{
	cout << "Kodiranje poruke: "<<ulazni_niz_karaktera<<endl;
	unordered_map<string, int> tabela = setDefault();

	string trenutni_slog = "";
	string trenutni_karakter = "";

	//trenutni_slog dobija vrednost prvog karaktera ulaznog niza
	trenutni_slog += ulazni_niz_karaktera[0];
	int code = 256;
	vector<int> kodirani_niz;
	cout << "String\tOutput_Code\tAddition\n";

	for (int i = 0; i < ulazni_niz_karaktera.length(); i++) {
		if (i != ulazni_niz_karaktera.length() - 1)
			trenutni_karakter += ulazni_niz_karaktera[i + 1];
		else
			break;

		//Pokusava da nadje niz karaktera u tabeli, koji je jednak 
		//nizu dobijenom nadovezivanjem trenutni_karakter , iz ulaznog niza "ulazni_niz_karaktera", na niz trenutni_slog 
		if (tabela.find(trenutni_slog + trenutni_karakter) != tabela.end()) {
			//Niz karaktera trenutni_slog + trenutni_karakter se NALAZI u tabeli
			// pa se nizu trenutni_slog nadovezuje trenutni_karakter
			trenutni_slog = trenutni_slog + trenutni_karakter;		
		}
		else {
			cout << trenutni_slog << "\t" << tabela[trenutni_slog] << "\t\t"
				<< trenutni_slog + trenutni_karakter << "\t" << code << endl;
			//Niz trenutni_slog + trenutni_karakter se NE nalazi u tabeli pa se vrsi njegovo dodavanje 
			kodirani_niz.push_back(tabela[trenutni_slog]);
			tabela[trenutni_slog + trenutni_karakter] = code;
			code++;
			trenutni_slog = trenutni_karakter;
		}
		trenutni_karakter = "";
	}
	cout << trenutni_slog << "\t" << tabela[trenutni_slog] << endl;
	kodirani_niz.push_back(tabela[trenutni_slog]);
	return kodirani_niz;
}

void decoding(vector<int> op)
{
	cout << "\nDecoding\n";
	unordered_map<int, string> table;
	for (int i = 0; i <= 255; i++) {
		string ch = "";
		ch += char(i);
		table[i] = ch;
	}
	int old = op[0], n;
	string s = table[old];
	string c = "";
	c += s[0];
	cout << s;
	int count = 256;
	for (int i = 0; i < op.size() - 1; i++) {
		n = op[i + 1];
		if (table.find(n) == table.end()) {
			s = table[old];
			s = s + c;
		}
		else {
			s = table[n];
		}
		cout << s;
		c = "";
		c += s[0];
		table[count] = table[old] + c;
		count++;
		old = n;
	}
}
int main()
{
	string s = "TOBEORNOTTOBEORTOBEORNOT";
	vector<int> output_code = encoding(s);
	cout << "Output Codes are: ";
	for (int i = 0; i < output_code.size(); i++) {
		cout << output_code[i] << " ";
	}
	cout << endl;
	decoding(output_code);
}
