#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <iterator>
#include "PerformanceCalculator.h"
using namespace std;

class Heap {
private:
	struct node {
		int key;
		int degree;
		node* parent;
		node* child;
		node* sibling;
		node(int k, node* par = nullptr, node* sib = nullptr, node* ch = nullptr) :
			key(k), degree(0), parent(par), sibling(sib), child(ch) {}
	};
	node * H;
	int type; //da li je min-heap(1) ili max-heap(2)
	list<node*> lst;
public:
	Heap() : lst() {  //konstruktor
		lst.clear();
	}
	Heap(int t) : lst() {  
		init();
		type = t;
	}

	//trazene metode
	void init(){//stvaranje novog praznog hipa
		H = nullptr;
	} 
    void add(int elem, int &steps); //dodavanje el u hip
	int get(); //dohvatanje max/min elementa
	int Delete(int &steps); //brisanje max/min el
	Heap& Union(Heap h, int &steps); //dodavanje jednog hipa drugom(spajanje). rezultat je izmenjen hip za koji se operacija poziva
	Heap& convert(); //min u max/max u min
	void destroy(); //brisanje/unistavanje hipa

	//dodatne metode
	bool is_empty() {
		return lst.empty();
	}
	void podesi(int &steps);
	bool uporedi(node *p, node *q) {
		if (type == 1) {
			if (p->key < q->key)
				return true;
			return false;
		}
		else {
			if (p->key > q->key)
				return true;
			return false;
		}
	}
	node *merge(node *, node*);
	Heap ukloniM();
	void resetH() {
		list<node*>::iterator p = lst.begin();
		list<node*>::iterator q = lst.end();
		if (lst.size() < 1) {
			H = nullptr;
			return;
		}
		H = *p;
		while (p != q) {
			if (uporedi(*p, H))
				H = *p;
			p++;
		}
	}

	~Heap() { //destruktor
		H = nullptr;
		lst.clear();
	}
};

//metode klase heap
Heap::node* Heap::merge(node *p, node*q) { //u p ubacujemo q
	if (!uporedi(p, q))
		swap(p, q);
	q->parent = p;
	q->sibling = p->child;
	p->child = q;
	p->degree++;
	return p;
}

Heap Heap::ukloniM() {
	node *temp = H->child;
	int steps = 0;
	lst.remove(H);
	delete H;
	Heap ostatak(type);
	if (!temp)
		return ostatak;
	while (temp) {
		node *tek = temp;
		temp->parent = nullptr;
		ostatak.lst.push_front(temp);
		temp = temp->sibling;
		tek->sibling = nullptr;
	}
	return ostatak;
}


void Heap::podesi(int &steps) {
	if (lst.size() <= 1)
		return;
	list <node*> novi;
	list <node*>::iterator i1, i2, i3;
	i1 = i2 = i3 = lst.begin();

	if (lst.size() == 2) {
		i2++;
		i3 = lst.end();
	}
	else {
		i2++;
		i3 = i2;
		i3++;
	}
	while (i1 != lst.end()) {
		if (i2 == lst.end())
			i1++;
		else if ((*i1)->degree < (*i2)->degree) {
			i1++;
			i2++;
			if (i3 != lst.end())
				i3++;
		}
		else if(i3!=lst.end() && (*i1)->degree == (*i2)->degree && (*i1)->degree == (*i3)->degree){
			i1++;
			i2++;
			i3++;
		}
		else if ((*i1)->degree == (*i2)->degree) {
			*i1 = merge(*i1, *i2); //spajanje stabala istog stepena
			steps++;
			i2 = lst.erase(i2);
			if (i3 != lst.end())
				i3++;
		}
		else { 
			i1++; 
			if (i2 != lst.end())
				i2++; 
			if (i3 != lst.end())
				i3++;
		}
	}
}

void Heap::add(int elem, int &steps) { //dodavanje el u hip
	if (is_empty()) {
		H = new node(elem);
		lst.push_front(H);
		return;
	}
	else {
		node* novi = new node(elem);
		lst.push_front(novi);
		if (uporedi(novi, H))
			H = novi;
		podesi(steps);
	}
}

int Heap::get() { //dohvatanje max/min elementa
	if (H)
		return H->key;
	else
		return -1;
}

int Heap:: Delete(int &steps) { //brisanje max/min el
	if (is_empty())
		return -1;
	Heap novi(type), ostatak(type);
	list<node*>::iterator p;
	p = lst.begin();
	while (p != lst.end()) {  //u novi ubacuje sve sem stabla iz kog se brise
		if (*p != H)
			novi.lst.push_back(*p);
		p++;
	}
	resetH();
	int m = H->key;
	ostatak = ukloniM();
	novi.Union(ostatak, steps);
	novi.resetH();
	*this = novi;
	return m;
}

Heap& Heap:: Union(Heap h, int &steps) { //dodavanje jednog hipa drugom(spajanje). rezultat je izmenjen hip za koji se operacija poziva
	list<node*> novalista;
	list <node*>::iterator p = lst.begin();
	list<node*>::iterator q = h.lst.begin();
	while (p != lst.end() && q != h.lst.end()) {
		if ((*p)->degree <= (*q)->degree){
			novalista.push_back(*p);
			p++;
		}
		else {
			novalista.push_back(*q);
			q++;
		}
		steps++;
	}
	while (p != lst.end()) {
		novalista.push_back(*p);
		p++;
		steps++;
	}
	while (q != h.lst.end()) {
		novalista.push_back(*q);
		q++;
		steps++;
	}
	lst.clear();
	lst = novalista;
	podesi(steps);
	return *this;

}

Heap& Heap:: convert() { //min u max/max u min
	int t, steps = 0, br;
	if (type == 1)
		t = 2;
	else t = 1;
	Heap novi(t);
	while (!is_empty()) {
		br = Delete(steps);
		steps = 0;
		novi.add(br, steps);
	}
	destroy();
	*this = novi;
	return *this;
}

void Heap:: destroy() { //brisanje/unistavanje hipa
	int steps = 0;
	while (!is_empty())
		Delete(steps);
	lst.clear();
	H = nullptr;
}

void performanse() {
	PerformanceCalculator pc;
	ifstream dat; 
	int st_ins = 0, st_del = 0, br, type;
	int vel = 10;
	double time_ins, time_del;
	cout << "Koji broj ima veci prioritet?\n1. Manji\t2. Veci\n";
	cin >> type;
	cout << setw(20) << "Velicina skupa" << setw(20) << "Vreme umetanja" << setw(20) << "Broj koraka" << setw(20) << "Vreme izbacivanja" << setw(20) << "Broj koraka" << endl;
	string imedat = "test_10";
	while (imedat != "test_1000000") {
		Heap myQ(type);
		dat.open(imedat + ".txt");
		if (!dat.is_open()) {
			cout << "Greska pri otvaranju dat.\n";
		}
		else {
			pc.start();
			while (!dat.eof()) {
				dat >> br;
				myQ.add(br, st_ins);
			}
			pc.stop();
			time_ins = pc.elapsedMillis();
			dat.close();
		}
		
		pc.start();
		while (!myQ.is_empty()) 
			myQ.Delete(st_del);
		pc.stop();
		time_del = pc.elapsedMillis();

		cout << setw(20) <<  vel << setw(20) << time_ins / 1000 << setw(20) << st_ins << setw(20) << time_del / 1000 << setw(20) << st_del << endl;
		myQ.destroy();
		imedat += "0"; 
		vel *= 10;
	}
}

int main() {
	
	int kraj = 0, opcija, vrsta;
	int br, st = 0, el, min, max;
	Heap myQ;
	string imedat;
	ifstream dat;
	while (!kraj) {
		cout << "----- M E N I -----\n";
		cout << "1. Stvaranje reda\n2. Da li je red prazan?\n3. Dohvati prvi element reda\n4. Obrisi prvi element reda\n5. Umetni element u red\n6. Performanse\n7. Promena prioriteta reda\n8. Kraj programa\n";
		cout << " -> Unesite zeljenu opciju: ";
		cin >> opcija;
		switch (opcija) {
		case 1:
			cout << "\nKoji broj ima veci prioritet?\n 1. Manji \t 2. Veci \n";
			int t;
			cin >> t;
			myQ = Heap(t);
			cout << "Operacija uspesno obavljena.\n";
			break;
		case 2: if (myQ.is_empty())
			       cout << "Red je prazan. \n";
				else
					cout << "Red nije prazan.\n";
			break;
		case 3: br = myQ.get();
			if (br >= 0) cout << "Prvi element reda je : " << br << endl;
			else
				cout << "Red je prazan." << endl;
			break;
		case 4: cout << "1. Bez dohvatanja \t 2. sa dohvatanjem\n ->Unesite zeljenu opciju: ";
			cin >> opcija;
			st = 0;
			br = myQ.Delete(st);
			if (br == -1)
				cout << "Red je prazan.\n";
			else {
				if (opcija == 2)
					cout << "Obrisani element je " << br << endl;
				else 
					cout << "Element uspesno obrisan." << endl;
			}
			break;
		case 5: cout << "\nKako zelite da unosite elemente?\n";
			cout << "1. Sa glavnog ulaza\t2. Citajuci iz datoteke\t3. Generisi random\n ->Unesite zeljenu opciju: ";
			cin >> opcija;
			switch (opcija) {
			case 1: st = 0;
				cout << "Koliko brojeva unosite? ";
				cin >> br;
				for (int i = 0; i < br; i++) {
					cout << "Unesite " << i + 1 << ". broj: ";
					cin >> el;
					myQ.add(el, st);
				}
				break;
			case 2: cout << "Unesite ime datoteke: ";
				cin >> imedat;
				dat.open(imedat);
				if (!dat.is_open()) {
					cout << "Greska pri otvaranju datoteke.";
				}
				else {
					while (!dat.eof()) {
						st = 0;
						dat >> el;
						myQ.add(el, st);
					}
					dat.close();
				}
				break;
			case 3: cout << "Unesite broj elemenata: ";
				cin >> br;
				cout << "Unesite opseg za generisanje (min-max)";
				cin >> min >> max;
				for (int i = 0; i < br; i++) {
					st = 0;
					el = static_cast<double>(rand() / (RAND_MAX + 1.0)*(max - min)) + min; 		
					myQ.add(el, st);
				}
				break;
			 }
			cout << "Operacija uspesno obavljena.\n";
			break;
		case 6: performanse();
			break;
		case 7: myQ.convert();
			cout << "Operacija uspesno obavljena.\n";
			break;
		case 8: kraj = 1; break;
		default: cout << "Izabrali ste nepostojecu stavku.\n"; break;
		}

	}
	return 0;
}