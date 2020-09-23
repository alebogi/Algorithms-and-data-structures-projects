#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <queue> 

using namespace std;

struct Film {
	string jezik;
	string naziv;
	float yyyymm;
	int godina;
	int dan;
	int mesec;
	double zarada;
	double trajanje;
};

class Zapis {
public:
	Film info;
	int valid;

	friend bool operator>(const Zapis& pod1, const Zapis& pod2);
	friend ostream& operator<<(ostream& it, const Zapis& pod);
};

ostream& operator<<(ostream& it,const Zapis& pod) {
	return it << pod.info.jezik << " " << pod.info.naziv << " " << pod.info.yyyymm << " "
		<< pod.info.godina << "-" << pod.info.mesec << "-" << pod.info.dan << " "
		<< fixed << setprecision(0) << pod.info.zarada << " " << pod.info.trajanje;
}

bool operator>(const Zapis& pod1, const Zapis& pod2) {
	if (pod1.info.godina < pod2.info.godina)
		return false;
	else if (pod1.info.godina > pod2.info.godina)
		return true;
	else if (pod1.info.mesec < pod2.info.mesec)
		return false;
	else if (pod1.info.mesec > pod2.info.mesec)
		return true;
	else if (pod1.info.dan < pod2.info.dan)
		return false;
	else if (pod1.info.dan > pod2.info.dan)
		return true;
	else
		return false;
}

class Cvor { 
public:
	Zapis * zapis;
	double keys[10];
	Zapis * niz_pok_klj[10];
	int br_kluceva = 0;
	Cvor *sinovi[11];
	bool JeList;
	Cvor *next;
	Cvor * otac;
	int br_sinova = 0;
};

Zapis * UcitavanjeDat(ifstream& dat, Zapis *baza, int *vel) {
	char c;
	string jezik;
	char pomc[200];
	int i = 0, j = 0, pomi;
	float pomf;
	double pomd;
	string pomstr, pomstr2;

	int size = 0;
	while (getline(dat, pomstr)) {
		size++;
	}
	*vel = size;
	dat.clear();  //vracam se na pocetak fajla
	dat.seekg(0, ios::beg);

	getline(dat, pomstr);  //uzima prvi red

	baza = new Zapis[size - 1];
	
	
	for (int cnt = size - 1; cnt > 0; cnt--, j++) {
		getline(dat, baza[j].info.jezik, ',');

		if ((c = dat.get()) == '"') {
			i = 0;
			while ((c = dat.get()) != '"') {
				pomc[i++] = c;
			}
			pomc[i] = '\0'; i = 0;
			baza[j].info.naziv = pomc;
			c = dat.get(); //,
		}
		else {
			i = 0;
			pomc[i++] = c;
			while ((c = dat.get()) != ',') {  //???
				pomc[i++] = c;
			}
			pomc[i] = '\0'; i = 0;
			baza[j].info.naziv = pomc;
		}
		
		dat >> baza[j].info.godina;
		c = dat.get(); //-
		dat >> baza[j].info.mesec;
		c = dat.get();//-
		dat >> baza[j].info.dan;
		c = dat.get();//,
		baza[j].info.yyyymm = baza[j].info.godina * 100 + baza[j].info.mesec;
		dat >> baza[j].info.zarada;
		c = dat.get();
		dat >> baza[j].info.trajanje;
		baza[j].valid = 1;
		c = dat.get(); // \n
	}
	
	return baza;
	
}

Zapis * GlavniUlaz(Zapis *baza, int *vel) {
	int cnt;
	int size;
	cout << "Koliko podataka unosite?" << endl;
	cin >> size;
	*vel = size;
	baza = new Zapis[size];

	for (cnt = 0; cnt < size; cnt++) {
		cout << endl << "-----Podaci o " << cnt + 1 << ". filmu-----" << endl;
		cout << "Unesite ime filma : ";
		cin >> baza[cnt].info.naziv;
		cout << "Unesite na kom je jeziku film (prva dva slova): ";
		cin >> baza[cnt].info.jezik;
		cout << "Unesite godinu izlaska filma: ";
		cin >> baza[cnt].info.godina;
		cout << "Unesite mesec izlaska filma: ";
		cin >> baza[cnt].info.mesec;
		cout << "Unesite dan izlaska filma: ";
		cin >> baza[cnt].info.dan;
		cout << "Unesite zaradu: ";
		cin >> baza[cnt].info.zarada;
		cout << "Unesite trajanje filma: ";
		cin >> baza[cnt].info.trajanje;
		baza[cnt].valid = 1;
		baza[cnt].info.yyyymm = baza[cnt].info.godina * 100 + baza[cnt].info.mesec;
	}
	
	return baza;
}

Zapis * SortirajBazu(Zapis * baza, int velbaze) {
	int i, j;
	Zapis pom;
	for (i = 0; i < velbaze; i++) {
		for (j = i + 1; j < velbaze; j++) {
			if (baza[i] > baza[j]) { //preklopiti >
				pom = baza[j];  
				baza[j] = baza[i];
				baza[i] = pom;
			}
		}
	}

	return baza;
}

Zapis * BrisanjeIzBaze(Zapis *baza, int velbaze) {
	string ime;
	cout << endl << "Unesite tacan naziv filma koji zelite da obrisete: ";
	cin >> ime;
	for (int i = 0; i < velbaze; i++) {
		if (baza[i].info.naziv.compare(ime) == 0) {
			baza[i].valid = 0;
			cout << endl << "Podatak uspesno uklonjen iz baze." << endl;
			return baza;
		}
	}
	cout << endl << "Trazeni film ne postoji u bazi." << endl;
	return baza;
}

void IspisBaze(Zapis *baza, int velbaze) {
	int i;
	int prazno = 0;
	for (i = 0; i < velbaze; i++) {
		if (baza[i].valid == 1) {
			cout << baza[i] << endl; //preklopiti << baza
			prazno++;
		}	
	}
	if (prazno == 0)
		cout << endl << "Baza je prazna." << endl;
}

Zapis * UnistavanjeBaze(Zapis *baza, int velbaze) {
	delete [] baza;
	baza = nullptr;
	return baza;
}

Cvor * SortirajKljuceve(Cvor *cvor) {
	int i, j, pom;
	Zapis *pomzap;
	for (i = 0; i < cvor->br_kluceva; i++) {
		for (j = i + 1; j < cvor->br_kluceva; j++) {
			if (cvor->keys[i] > cvor->keys[j]) {
				pom = cvor->keys[i];
				pomzap = cvor->niz_pok_klj[i];
				cvor->keys[i] = cvor->keys[j];
				cvor->niz_pok_klj[i] = cvor->niz_pok_klj[j];
				cvor->keys[j] = pom;
				cvor->niz_pok_klj[j] = pomzap;
			}
		}
	}
	return cvor;
}

Cvor * SortirajKljuceveSredina(Cvor  *cvor) {
	int i, j, pom;
	Cvor *pom_pok_cv;

	pom = cvor->keys[cvor->br_kluceva - 1];
	j = cvor->br_kluceva - 2;
	while ((cvor->keys[j] > pom) && (j >= 0))
		j--;
	int poz = j + 1;
	for (i = j + 1; i < cvor->br_kluceva - 1; i++) {
		cvor->keys[i + 1] = cvor->keys[i];
		cvor->sinovi[i + 1] = cvor->sinovi[i];
	}
	cvor->keys[poz] = pom;
	cvor->sinovi[poz] = pom_pok_cv;
	return cvor;
}

Cvor * NadjiKljuc(Cvor *root, float key, int m) {  //!
	Cvor *tek = root, *pret = nullptr;
	int i;
	while (tek) {
		i = 0;
		while (i < tek->br_kluceva && key > tek->keys[i])
			i++;
		if (i <= tek->br_kluceva && key == tek->keys[i]) { //kljuc postoji u datom cvoru
			if (tek->JeList == true)
				return tek; //vraca pok na trazeni kljuc
			pret = tek;  //nije list, spusta se na levo podstablo
			tek = tek->sinovi[i];
			continue;
		}
		else if (i <= tek->br_kluceva && key > tek->keys[i] && (tek->JeList == false)) {  //kljuc je veci od datog cvora, a dati cvor nije list
			pret = tek;
			tek = tek->sinovi[i + 1];  //spusta 
			continue;
		}
		else if (i == tek->br_kluceva && (tek->JeList == true))
			return tek;
	}
	return tek;
}

Cvor * DodajCvor(Cvor * cvor, const int m) { //!

	return cvor;
}

Cvor * UbaciKljuc(Cvor *root, const int m, const float kljuc, Zapis *kljucnizapis) {
	double pom_niz_kljuceva[10];
	Zapis * pom_niz_pok_zapis[10];
	int j, i, smesti = 0;
	if (root == nullptr) {
		root = new Cvor;
		root->keys[root->br_kluceva] = kljuc;
		root->niz_pok_klj[root->br_kluceva] = kljucnizapis;  
		root->br_kluceva++;
		for (i = 0; i < 10; i++) {
			root->sinovi[i] = nullptr;
		}
		root->JeList = true;
		root->next = nullptr;
		root->otac = nullptr;
		return root;
	}
	else {
		Cvor * pok = NadjiKljuc(root, kljuc, m);
			if ((pok->br_kluceva != m - 1) && (pok->JeList == true)) { //ima mesta u listu
				pok->keys[pok->br_kluceva] = kljuc;
				pok->niz_pok_klj[root->br_kluceva] = kljucnizapis;
				pok->br_kluceva++;
				pok = SortirajKljuceve(pok);
				pok->next = nullptr;
				return root;
			}
			else {  //pun list
				pok->keys[pok->br_kluceva] = kljuc;
				pok->niz_pok_klj[pok->br_kluceva] = kljucnizapis;
				pok = SortirajKljuceve(pok);
				for (i = 0; i < pok->br_kluceva + 1; i++) {  //smestamo sortirano sve u pomocni niz
					pom_niz_kljuceva[i] = pok->keys[i];
					pom_niz_pok_zapis[i] = pok->niz_pok_klj[i];
				}
				int duzina_niza = pok->br_kluceva + 1;
				Cvor *novi = new Cvor;
				for (i = (duzina_niza / 2 + (duzina_niza % 2)), j = 0; i < duzina_niza; i++, j++) {
					novi->keys[j] = pok->keys[i];
					novi->niz_pok_klj[j] = pok->niz_pok_klj[i];
				}
				pok->br_kluceva = duzina_niza / 2;
				novi->br_kluceva =duzina_niza - (duzina_niza / 2 + (duzina_niza % 2));
				novi->next = pok->next;
				pok->next = novi;
				novi->JeList = true;

				//nzm
				if (pok->otac == nullptr) {
					Cvor *noviotac = new Cvor;
					if (smesti == 0)
						noviotac->keys[0] = pok->keys[pok->br_kluceva - 1];
					else
						noviotac->keys[0] = pom_niz_kljuceva[duzina_niza / 2];
					noviotac->sinovi[0] = pok;
					noviotac->sinovi[1] = novi;
					noviotac->otac = nullptr;
					noviotac->br_kluceva = 1;
					noviotac->br_sinova = 2;
					noviotac->JeList = false;
					root = noviotac;
					return root;
				}
				//nzm

				while (1) {//?
					if ((pok->otac == nullptr) && (pok->br_kluceva > m - 1)) {   //deoba korena
						Cvor *noviotac = new Cvor;
						if (smesti == 0)
							noviotac->keys[0] = pok->keys[pok->br_kluceva - 1];
						else
							noviotac->keys[0] = pom_niz_kljuceva[duzina_niza / 2];
						noviotac->sinovi[0] = pok;
						noviotac->sinovi[1] = novi;
						noviotac->otac = nullptr;
						noviotac->br_kluceva = 1;
						noviotac->br_sinova = 2;
						noviotac->JeList = false;
						root = noviotac;
						return root;
					}
					else if (pok->otac != nullptr && pok->br_kluceva > m - 1) { //azuriranje stabla od lista ka korenu
						Cvor *tek = pok;
						Cvor *otac = pok->otac;
						otac->sinovi[otac->br_sinova] = novi;
						otac->br_sinova = otac->br_sinova + 1;
						otac->keys[otac->br_kluceva] = novi->keys[novi->br_kluceva];
						otac = SortirajKljuceveSredina(otac);
						if (otac->br_sinova <= m && otac->br_kluceva <= m - 1) { //ne treba dalje azuriranje
							root = otac;
							return root;
						}
						else {
							pok = otac;
							novi = new Cvor;
							Cvor *left = pok;
							Cvor *right = novi;
							pok->otac->sinovi[pok->otac->br_sinova] = novi;
							for (i = 0; i < pok->br_kluceva + 1; i++) {  //smestamo sortirano sve u pomocni niz
								pom_niz_kljuceva[i] = pok->keys[i];
								pom_niz_pok_zapis[i] = pok->niz_pok_klj[i];
							}
							duzina_niza = pok->br_kluceva + 1;
							for (i = (duzina_niza / 2 + 1), j = 0; i < duzina_niza; i++, j++) {
								novi->keys[j] = pok->keys[i];
							}
							novi->br_kluceva = j + 1;
							pok->br_kluceva -= novi->br_kluceva - 1;
							if (pok->otac) { //pok nije root
								pok->otac->keys[pok->otac->br_kluceva++] = pom_niz_kljuceva[duzina_niza / 2];
							}
							else { //pok jeste root
								smesti = pom_niz_kljuceva[duzina_niza / 2];
							}
							pok = pok->otac;
						}
						
					}
					else {
						root = pok->otac;
						return root;
					}
				}// end of ?

				//novi->otac = pok->otac;
			}
		return root;
	}
}


Cvor * StvaranjeStabla(Cvor *root, int& m, Zapis *baza, const int velbaze) {
	cout << "Unesite red stabla: ";
	cin >> m;
	int i, prekid = 0;
	for (i = 0; i < velbaze; i++) {
		if ((i == 0) && (baza[0].valid == 1))
			root = UbaciKljuc(root, m, baza[i].info.yyyymm, &baza[i]);
		else if ((baza[i].valid == 1) && (baza[i].info.yyyymm != baza[i - 1].info.yyyymm)) {
			root = UbaciKljuc(root, m, baza[i].info.yyyymm, &baza[i]);
		}

		/*ofstream izlaznadat; //provera
		izlaznadat.open("PROVERA.txt");

		izlaznadat.close();*/
	}
	return root;
}



int Visina(Cvor *root) {
	int h = -1;
	Cvor *tek = root;
	while (tek) {
		tek = tek->sinovi[0];
		h++;
	}
	return h;
}

void IspisStabla(Cvor * root) { 
	Cvor *tek = root; int h;
	if (root == nullptr) {
		cout << "Stablo je prazno.\n";
		return;
	}
	else {
		h = Visina(root);
		ofstream izlaznadat;
		izlaznadat.open("Ispis_stabla.txt");
		if (!izlaznadat.is_open()) {
			cout << "Neuspesno otvaranje izlazne datoteke\n"; 
			exit(1);
		}
		else {
			queue <Cvor*> MyQ;
			MyQ.push(tek);
			Cvor *pok;
			int j, i; int duzina_reda;
			for (i = 0; i < h + 1; i++) {
				if (i == 0) izlaznadat << "Koren: ";
				else izlaznadat << "[nivo " << i << "]: ";
				duzina_reda = MyQ.size();
				while (duzina_reda--) {
					pok = MyQ.front();
					MyQ.pop();
					int cnt = 0;
					while (cnt < pok->br_sinova) { //stavljamo sinove u red
						MyQ.push(pok->sinovi[cnt++]);
					}
					cnt = 0;
					while (cnt < pok->br_kluceva) {
						if (cnt == 0)
							izlaznadat << "|";
						izlaznadat << "-" << pok->keys[cnt++] << "-";
					}
					izlaznadat << "|        ";
				}
				izlaznadat << endl;
			}
			izlaznadat << endl;
			izlaznadat.close();
			cout << "Stablo je ispisano u datoteku 'Ispis_stabla.txt'. \n";
		}
	}

}

bool FindKey(Cvor *root, float kljuc) {
	Cvor *tek = root, *pret = nullptr;
	int i;
	while (tek) {
		i = 0;
		while (i < tek->br_kluceva && kljuc > tek->keys[i])
			i++;
		if (i <= tek->br_kluceva && kljuc == tek->keys[i]) { //kljuc postoji u datom cvoru
			if (tek->JeList == true)
				return true; //vraca pok na trazeni kljuc
			pret = tek;  //nije list, spusta se na levo podstablo
			tek = tek->sinovi[i];
			continue;
		}
		else if (i <= tek->br_kluceva && kljuc > tek->keys[i] && (tek->JeList == false)) {  //kljuc je veci od datog cvora, a dati cvor nije list
			pret = tek;
			tek = tek->sinovi[i + 1];  //spusta 
			continue;
		}
		else if (i == tek->br_kluceva && kljuc > tek->keys[i] && (tek->JeList == true)) {  //kljuc je veci od datog cvora, a dati cvor je list
			return false;
		}
		tek = tek->sinovi[i];
	}
	return false;
}

void PronalazenjeFilmova(Cvor *root) {
	int poc_godina, poc_mesec, kraj_godina, kraj_mesec;
	cout << "Unesite period za koji zelite da izracunate broj izdatih filmova: "
		<< "pocetak perioda(godina): ";
	cin >> poc_godina;
	cout << "pocetak perioda(mesec): ";
	cin >> poc_mesec;
	int yyyymm_poc, yyyymm_kraj;
	yyyymm_poc = poc_godina * 100 + poc_mesec;
	cout << "kraj perioda(godina): ";
	cin >> kraj_godina;
	cout << "kraj perioda(mesec): ";
	cin >> kraj_mesec;
	yyyymm_kraj = kraj_godina * 100 + kraj_mesec;
	/* Nadjemo u stablu yyyymm_poc, spustimo se u bazu i krecemo se sve do yyyymm_kraj */

	Cvor *tek = root, *pret = nullptr;
	int i, skok = 0;
	while (tek) {
		i = 0;
		while (i < tek->br_kluceva && yyyymm_poc > tek->keys[i])
			i++;
		if (i <= tek->br_kluceva && yyyymm_poc == tek->keys[i]) { //kljuc postoji u datom cvoru
			if (tek->JeList == true) {
				Zapis *pok = tek->niz_pok_klj[i];
				int cnt = 0;
				while (yyyymm_kraj >= pok->info.yyyymm) {
					if (pok->valid == 1) {
						cnt++;
						if (cnt == 1)
							cout << "\nNazivi filmova: " << endl;
						cout << pok->info.naziv << endl;
					}
					pok++;
				}
				cout << "Ukupan broj filmova iz datog perioda je: " << cnt << endl << endl;
				return;
			}
			pret = tek;  //nije list, spusta se na levo podstablo
			tek = tek->sinovi[i];
			continue;
		}
		else if (i <= tek->br_kluceva && yyyymm_poc > tek->keys[i] && (tek->JeList == false)) {  //kljuc je veci od datog cvora, a dati cvor nije list
			pret = tek;
			tek = tek->sinovi[i + 1];  //spusta 
			continue;
		}
		else if (i <= tek->br_kluceva && yyyymm_poc < tek->keys[i] && (tek->JeList == true)) {  //kljuc je manji od kljuceva datog cvora, a dati cvor je list
			yyyymm_poc += 1; //pomeramo se sa januara na feb-mart-april..povecavamo kljuc pocetnog perioda
			skok = 1;
		}
		if (skok == 1)
			tek = root;
		else
			tek = tek->sinovi[i];
	}

}

void Statistika(Cvor *root) {
	float godina;
	cout << "Unesite godinu za koju zelite da izracunate broj izdatih filmova: ";
	cin >> godina;
	/*Spustimo se do lista u stablu koji predstavlja kljuc najblizi datoj godini*100 (najmanji kljuc iz date godine)
	Preko tog lista se povezujemo sa bazom, i krecemo se po bazi i brojimo filmove sve dok se ne poveca broj godine
	Vratimo broj izbrojanih filmova
	*/
	float kljuc = godina * 100 + 1;
	Cvor *tek = root, *pret = nullptr;
	int i, skok = 0;
	while (tek) {
		i = 0;
		while (i < tek->br_kluceva && kljuc > tek->keys[i])
			i++;
		if (i <= tek->br_kluceva && kljuc == tek->keys[i]) { //kljuc postoji u datom cvoru
			if (tek->JeList == true) {
				Zapis *pok = tek->niz_pok_klj[i];
				int cnt = 0;
				while (godina == pok->info.godina) {
					if (pok->valid == 1) {
						cnt++;
					}
					pok++;
				}
				cout << "Broj filmova iz date godine je: " << cnt << endl;
				return;
			}
			pret = tek;  //nije list, spusta se na levo podstablo
			tek = tek->sinovi[i];
			continue;
		}
		else if (i <= tek->br_kluceva && kljuc > tek->keys[i] && (tek->JeList == false)) {  //kljuc je veci od datog cvora, a dati cvor nije list
			pret = tek;
			tek = tek->sinovi[i + 1];  //spusta 
			continue;
		}
		else if (i<= tek->br_kluceva && kljuc < tek->keys[i]) {  //kljuc je manji od kljuceva datog cvora, a dati cvor je list
			kljuc += 1; //pomeramo se sa januara na feb-mart-april..povecavamo kljuc
			//tek = root;
			skok = 1;
		}
		
		if (skok == 1)
			tek = root;
		else
			tek = tek->sinovi[i];
		//tek = tek->sinovi[i];
	}
	cout << "Ne postoje podaci za datu godinu. \n";
}

int main() {
	int velbaze = 0; Zapis *baza = nullptr;
	int kraj = 0, opcija;
	Cvor * root = nullptr;
	int m; //red stabla
	while (!kraj) {
		cout << "------MENI------" << endl;
		cout << "1. Stvaranje baze" << endl << "2. Brisanje zapisa iz baze" << endl
			<< "3. Unistavanje baze" << endl << "4. Ispis baze" << endl
			<< "5. Stvaranje stabla" << endl << "6. Nadji kljuc u stablu" << endl
			<< "7. Ispis stabla (u datoteku)" << endl  
			<< "8. Brisanje kljuca iz stabla" << endl << "9. Pretrazi filmove" << endl
			<< "10. Statistika" << endl << "11. Kraj programa" << endl
			<< "Izaberite opciju: ";
		cin >> opcija;
		switch (opcija) {
		case 1: cout << "Da li zelite da ucitate bazu" << endl << "1. iz datoteke" << endl << "2. sa glavnog ulaza?" << endl << "Opcija: ";
			cin >> opcija;
			if (opcija == 1) {
				string imedat;
				cout << "Unesite ime datoteke: ";
				cin >> imedat;
				ifstream dat;
				dat.open(imedat);
				if (!dat.is_open()) {
					cout << "Greska pri otvaranju datoteke." << endl;
					exit(1);
				}
				else {
					baza = UcitavanjeDat(dat, baza, &velbaze);
					velbaze--;
					dat.close();
				}
			}
			else if (opcija == 2) {
				baza = GlavniUlaz(baza, &velbaze);
			}
			else {
				cout << "Trazena opcija ne postoji." << endl;
				exit(1);
			}
			baza = SortirajBazu(baza, velbaze);
			break;
		case 2: baza = BrisanjeIzBaze(baza, velbaze);
			break;
		case 3: baza = UnistavanjeBaze(baza, velbaze);
			break;
		case 4: if (baza != nullptr)
			        IspisBaze(baza, velbaze);
				else
					cout << "Baza ne postoji." << endl;
			break;
		case 5: root = StvaranjeStabla(root, m, baza, velbaze); 
			break;
		case 6: cout << "Unesite vrednost kljuca koji pretrazujete: ";
			float findkljuc;
			cin >> findkljuc;
			if (FindKey(root, findkljuc))
				cout << "Kljuc postoji.\n";
			else
				cout << "Kljuc ne postoji.\n";
			break;
		case 7: IspisStabla(root);
			break;
		case 8: cout << "\n!!!!\nERROR 404\n ~Brisanje kljuca iz stabla~ NOT FOUND\n!!!!\nStavka je u izradi.\n" << endl;
			break;
		case 9: PronalazenjeFilmova(root); break;
		case 10: Statistika(root); break;
		case 11: kraj = 1; break;
		default: cout << "Ne postoji trazena opcija." << endl; break;
		}
	}

	return 0;
}