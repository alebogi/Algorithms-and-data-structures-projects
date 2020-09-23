#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//deklaracije fja
double * GeneratingLevel();
int BinarySearch();
int TernarySearch();
int HybridSearch();
struct queue *InsertQ();
struct queue* DeleteQ();
int EmptyQ();
int CountQ();
double BinomalCoeff();
double Faktoriel();
void PrintLvl();
void FinalResult();
double * DeleteLevel();
//

struct queue {
	double num;
	struct queue *next;
};

struct queue *InsertQ(struct queue *first, double num) {
	struct queue *new;
	struct queue *pt = first;
	if (EmptyQ(first) == 1) {
		first = (struct queue *)malloc(sizeof(struct queue));
		first->num = num;
		first->next = NULL;
	}
	else {
		new = (struct queue *)malloc(sizeof(struct queue));
		new->num = num;
		new->next = NULL;
		while (pt->next != NULL)
			pt = pt->next;
		pt->next = new;
	}
	return first;
}

struct queue* DeleteQ(struct queue *first) { //prethodi operacija row[i]=myQueue->num; myQueue=DeleteQ(myQueue);
	struct queue *pt;
	pt = first;
	first = first->next;
	free(pt);
	return first;
}

int EmptyQ(struct queue *first) {
	if (first == NULL)
		return 1;
	else return 0;
}

int CountQ(struct queue *first) {
	struct queue *p = first;
	int i = 0;
	if (p == NULL)
		return 0;
	else {
		while (p != NULL) {
			p = p->next;
			i++;
		}
		return i;
	}
}

double Faktoriel(int num) {
	int i;
	double result = 1;
	for (i =num; i >=1; i--) {
		result *= i;
	}
	return result;
}

double BinomalCoeff(int n, int k) {
	int nk;
	double nfak, kfak, nkfak, result;
	nfak = Faktoriel(n); 
	kfak = Faktoriel(k); 
	nk = n - k;
	nkfak = Faktoriel(nk);
	result = nfak / (kfak*nkfak); 
	return result;	
}

double * GeneratingLevel(int n, double *lvl, int *length) {
	int i;
	double elem;
	struct queue *myQ = NULL;
	int newn;
	if (((n + 1) % 2) == 0) {
		newn = (n + 1) / 2;
	}
	else
		newn = (n + 1) / 2 + 1;
	for (i = 0; i < newn ; i++) {
		elem = BinomalCoeff(n, i);
		elem = round(elem);
		myQ = InsertQ(myQ, elem); //stavljamo elemente niza u red
	}
	*length = CountQ(myQ);
	lvl = (double *) malloc((*length) * sizeof(double));
	for (i = 0; i < (*length); i++) {
		lvl[i] = myQ->num;
		myQ = DeleteQ(myQ);
	}
	return lvl;
}

void PrintLvl(double *lvl, int n) {
	int i;
	printf("\n***************\n Ispis reda za pretragu: ");
	for (i = 0; i < n; i++) {
		printf("%.0f ", lvl[i]);
	}
	printf("\n***************\n");
	printf("\n");
}

int BinarySearch(double *arr, int n, double key, int *num) {
	int low = 0, high = n - 1, mid;
	*num = 0;
	int succ = 1, unsucc = 0;
	while (low <= high) {
		mid = (low + high) / 2; 
		if (arr[mid] == key) {
			(*num)++;
			return succ;
		}
		else if (key < arr[mid]) {
			high = mid - 1; 
			(*num)++;
		}
		else if (key>arr[mid]) {
			low = mid + 1;  
			(*num)++;
		}	
	}
	if (arr[low] == key) {
		(*num)++;
		return succ;
	}
	else
		return unsucc;
}

int TernarySearch(double *arr, int n, double key, int *num) {
	int succ = 1, unsucc = 0;
	int low = 0, high = n - 1, first, second;
	*num = 0;
	while (low <= high) {
		first = low + (high - low) / 3;
		second = low + 2 * (high - low) / 3;
		if (key == arr[first]) {
			(*num)++;
			return succ;
		}
		else if (key == arr[second]) {
			(*num) += 2;  //dodajemo 2 pristupa jer je ispitivanje =a? bilo 1 pristup, a =b? je drugi
			return succ;
		}
		else if (key < arr[first]) { 
			(*num) += 2;  
			high = first - 1;
		}
		else if (key < arr[second]) {
			(*num) += 2;
			low = first + 1;
			high = second - 1;
		}
		else if (key > arr[second]) {
			(*num) += 2;
			low = second + 1;
		}
	}
	if ((arr[low] == key) || arr[high] == key) {
		num++;
		return succ;
	}
	else
		return unsucc;
}

int HybridSearch(double *arr, int n, double key, int *num) {
	int succ = 1, unsucc = 0;
	*num = 0;
	int low = 0, high = n - 1, mid, first, second;

	first = low + (high - low) / 3;
	second = low + 2 * (high - low) / 3;
	mid = (high - low) / 2;

	if (key == arr[first]) {
		(*num)++;
		return succ;
	}
	else if (key == arr[mid]) {
		(*num) += 2;
		return succ;
	}
	else if (key == arr[second]) {
		(*num) += 3;
	}
	else if (key < arr[first]) {
		high = first - 1;
	}
	else if (key < arr[mid]) {
		low = first + 1;
		high = mid - 1;
	}
	else if (key < arr[second]) {
		low = mid + 1;
		high = second - 1;
	}
	else if (key > arr[second]) {
		low = second + 1;
	}
	while (low <= high) { //nastavlja binarno
		mid = (low + high) / 2;
		if (arr[mid] == key) {
			(*num)++;
			return succ;
		}
		else if (key < arr[mid]) {
			high = mid - 1;
			(*num)++;
		}
		else if (key>arr[mid]) {
			low = mid + 1;
			(*num)++;
		}
	}
	if (arr[low] == key) {
		(*num)++;
		return succ;
	}
	else
		return unsucc;
}

void FinalResult(int result, int num) {
	if (result) {
		printf("\nKljuc je uspesno pronadjen. Broj potrebnih pristupa je: %d.\n", num);
	}
	else
		printf("\nNeuspesna pretraga. Trazeni kljuc ne postoji u datom nivou.\n");
}

double *DeleteLevel(double *arr) {
	double *old;
	old = arr;
	free(old);
	arr = NULL;
}

void main() {
	int end = 0, n, lvlLength, option, repeat = 1, num = 0, result, repeatSearch = 1;
	double *level = NULL;
	double key;
	while (!end) {  //vrti ceo program
		printf("----------PASKALOV TROUGAO----------\n");
		printf("----->Unesite broj reda koji zelite da pretrazite\n");
		scanf("%d", &n);
		level = GeneratingLevel(n, level, &lvlLength);
		PrintLvl(level, lvlLength); 

		repeatSearch = 1;
		while (repeatSearch == 1) { //vrti jedan isti generisani red
			printf("-----> Unesite broj kljuca koji zelite da pretrazite\n");
			scanf("%lf", &key);
			key = round(key);
			printf("\nIzaberite opciju pretrage: \n1. Binarna pretraga\n");
			printf("2. Ternarna pretraga\n");
			printf("3. Hibridna pretraga\n");
			printf("4. Pretrazi na sva tri nacina i prikazi rezultate pretrage\n");
			printf("Biram opciju: ");
			scanf("%d", &option);
			repeat = 1;
			while (repeat == 1) {
				switch (option) {
				case 1: result = BinarySearch(level, lvlLength, key, &num);
					    FinalResult(result, num);
					    repeat = 0; break;
				case 2: result = TernarySearch(level, lvlLength, key, &num);
					    FinalResult(result, num);
						repeat = 0; break;
				case 3: result = HybridSearch(level, lvlLength, key, &num);
					    FinalResult(result, num);
						repeat = 0; break;
				case 4: int bin = 0, ter = 0, hib = 0;
					result = BinarySearch(level, lvlLength, key, &bin);
					result = TernarySearch(level, lvlLength, key, &ter);
					result = HybridSearch(level, lvlLength, key, &hib);
					if (result) {
						printf("\nBroj potrebnih pristupa binarnom pretragom: %d\nBroj potrebnih pristupa ternarnom pretragom: %d\n", bin, ter);
						printf("Broj potrebnih pristupa hibridnom pretragom: %d\n", hib);
					}
					else printf("\nPretrage su neuspesne-trazeni kljuc nije u datom nivou\n");
					repeat = 0;
					break;
				default: printf("Trazena opcija ne postoji.\n");
					printf("Unesite zeljenu opciju ponovo: ");
					scanf("%d", &option);
				}
			}

			printf("\n--------------------\nDa li zelite da pretrazite jos neki broj?\n1. Da\n2. Ne\n Biram opciju: ");
			scanf("%d", &option);
			switch (option) {
			case 1: repeatSearch = 1; break;
			case 2: repeatSearch = 0; break;
			}
		} //vrti generisani red
		printf("\n---------------------------------\n");

		level = DeleteLevel(level);
		printf("\nDa li zelite da izadjete iz programa?\n");
		printf("1. Da\n2. Ne, ponovo pokreni program\n Biram opciju: ");
		scanf("%d", &option);
		switch (option) {
		case 1: end = 1;
			printf("\n*****Dovidjenja uzivajte u zivotu******\n\n");
			break;
		case 2: end = 0; break;
		}
	} //ceo program
}