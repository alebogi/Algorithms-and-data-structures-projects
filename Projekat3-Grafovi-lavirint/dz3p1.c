#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 500
#define ZID 219 //Ispis zida ascii 219
#define ULAZ 239 //ascii
#define IZLAZ X


struct koordinate {
	int x;
	int y;
};

struct graph {
	int mat[MAX][MAX];
	int maze[MAX][MAX];
	int br_izlaza;
	struct koordinate exit[20];
	struct koordinate ulaz;
	struct koordinate kraj_put;
	struct koordinate poc_put;
	int m;
	int n;
	struct elem *skupovi;
};

struct elem {
	int cvor;
	int br_skupa;
	struct elem *sled;
};


int Nadji(int x, int y, struct graph *graf) { //x,y su koordinate u lavirintu, i->polozaj u matrici susednosti
	int i, j, m, n;
	n = graf->n;
	m = graf->m;
	i = x * n + y;
	return i;
}

int Provera_susednosti(int x1, int y1, int x2, int y2) {
	int jesu = 1, max, nisu = 0;

	if (x1 == x2) {
		if (y2 < y1) {
			max = y1;
			y1 = y2;
			y2 = max;
		}
		if (y1 == y2 - 1) {
			jesu = 1;
			return jesu;
		}
	}
	if (y1 == y2) {
		if (x2 < x1) {
			max = x1;
			x1 = x2;
			x2 = max;
		}
		if (x1 == x2 - 1) {
			jesu = 1;
			return jesu;
		}

	}

	return nisu;
}

struct graph * StvaranjeGrafa(struct graph *graf) {
	int i, j, dim;
	dim = graf->m *graf->n;
	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
			if (i == j) graf->mat[i][j] = 0;
			else graf->mat[i][j] = INT_MAX;
		}
	}
	return graf;
}

struct graph *DodajCvor(struct graph *graf) { //dodaje ceo red matrici kako lavirint ne bi izgubio oblik
	int i, j, dim;
	dim = (graf->m + 1)*(graf->n + 1);
	for (i = 0; i++; i < graf->m) {
		for (j = graf->n; j < dim; j++) {
			if (i == j) graf->mat[i][j] = 0;
			else graf->mat[i][j] = INT_MAX;
		}
	}
	for (i = graf->m; i < dim; i++) {
		for (j = 0; j < dim; j++) {
			if (i == j) graf->mat[i][j] = 0;
			else graf->mat[i][j] = INT_MAX;
		}
	}
	graf->m++;
	graf->n++;

	return graf;
}

struct graph * DodajGranu(int x1, int y1, int x2, int y2, struct graph *graf) { //x1y1 i x2y2 koordinate polja izmedju koji pravimo granu
	int i, j;

	if ((x1 == x2) && (y1 == y2)) return graf;
	j = Nadji(x1, y1, graf);
	i = Nadji(x2, y2, graf);
	graf->mat[i][j] = 1;
	graf->mat[j][i] = 1;

	return graf;
}



struct graph * ObrisiCvor(struct graph *graf) {  //brise ceo red 
	int i, j, dim;
	graf->m--;
	graf->n--;
}

struct graph * ObrisiGranu(int x1, int y1, int x2, int y2, struct graph *graf) {   //x1y1 i x2y2 koordinate polja izmedju koji brisemo granu
	int i, j;

	j = Nadji(x1, y1, graf);
	i = Nadji(x2, y2, graf);
	graf->mat[i][j] = 0;
	graf->mat[j][i] = 0;

	return graf;
}

struct graph * BrisanjeGrafa(struct graph *graf) {
	free(graf);
	graf = NULL;
	return graf;
}

int Postojanje_grane(int x1, int y1, int x2, int y2, struct graph *graf) {
	int i, j, postoji = 0;
	if ((x1 == x2) && (y1 == y2)) return postoji;
	j = Nadji(x1, y1, graf);
	i = Nadji(x2, y2, graf);

	if (graf->mat[i][j] == 1) postoji = 1;
	else postoji = 0;

	return postoji;
}

struct graph *Ubaci_u_skup(int cvor, struct graph *graf) { //element koji dodajemo u skup
	struct elem *novi = malloc(sizeof(struct elem));
	novi->cvor = cvor;
	novi->br_skupa = cvor;
	novi->sled = graf->skupovi;
	graf->skupovi = novi;
	
	return graf;
}

int Kom_skupu_pripada(int cvor, struct graph *graf) {
	int br_skupa=0;
	struct elem *tek;
	tek = graf->skupovi;
	while (tek != NULL) {
		if (tek->cvor == cvor) {
			br_skupa = tek->br_skupa;
			break;
		}
		tek = tek->sled;
	}

	return br_skupa;
}

struct graph *Spoji_skupove(int skup1, int skup2, int cvor1, int cvor2, struct graph *graf) { 
	int nestaje, zamena;
	nestaje = skup1;
	zamena = skup2;
	struct elem *tek;
	tek = graf->skupovi;
	while (tek != NULL) {
		if (tek->br_skupa == nestaje) {
			tek->br_skupa = zamena;
		}
		tek = tek->sled;
	}
	

	return graf;
}

int Brojac(struct graph *graf) {
	int i, uporedi;
	struct elem *tek;
	tek = graf->skupovi;
	uporedi = tek->br_skupa;
	while (tek != NULL) {
		if (uporedi != tek->br_skupa) return 0;
		tek = tek->sled;
	}
	return 1;
}

struct graph * Kruskal(struct graph *graf) {
	srand(time(NULL));
	int i = 0, j, x1, x2, y1, y2, cvor1, cvor2, br1, br2, k=0;
	int gornja, donja, postoji, brcvr;
	int susednost, skup1, skup2;
	graf->skupovi = NULL;
	int izbor;
	brcvr = graf->n * graf->m;
	
	
	gornja = brcvr;
	donja = 0;
	

	/*ubacujemo sve elemente kao zasebne skupove u jednu listu*/
	for (i = 0; i < brcvr; i++) {
		graf = Ubaci_u_skup(i+1, graf); //!
	}
	i = 0;
	while (k!=1) { //-1
		gornja = brcvr; //-1
		donja = 1; //0
		cvor1 = rand() / ((double)RAND_MAX + 1) * (gornja - donja + 1) + donja;
		
		y1 = cvor1 % graf->n;
		x1 = (cvor1 - y1) / graf->n;

		int ponovi = 1;
		while (ponovi == 1) {
			gornja = 4;
			donja = 1;
			izbor = rand() / ((double)RAND_MAX + 1) * (gornja - donja + 1) + donja;
			switch (izbor) {
			case 1: if (x1 > 0) { //gore
				x2 = x1 - 1;
				y2 = y1;
				ponovi = 0;
			} break;
			case 2: if (x1 < graf->n - 2) { //dole
				x2 = x1 + 1;
				y2 = y1;
				ponovi = 0;
			} break;
			case 3: if (y1 > 0) { //levo
				x2 = x1;
				y2 = y1 - 1;
				ponovi = 0;
			} break;
			case 4: if (y1 < graf->n - 2) { //desno
				x2 = x1;
				y2 = y1 + 1;
				ponovi = 0;
			} break;
			}
		}

		cvor2 = Nadji(x2, y2, graf);

		skup1 = Kom_skupu_pripada(cvor1, graf);
		skup2 = Kom_skupu_pripada(cvor2, graf);

		if (skup1!=skup2) {
			graf = Spoji_skupove(skup1, skup2, cvor1, cvor2, graf);
			postoji = Postojanje_grane(x1, y1, x2, y2, graf);
			if (postoji == 0) {
				graf = DodajGranu(x1, y1, x2, y2, graf);
				i++;
				k = Brojac(graf);
			}
			
		}

		

		
	}
	return graf;
}

void Path(int pocetak, int kraj, int trace[MAX][MAX], struct graph *graf) {
	if (pocetak == kraj) {
		printf("(%d, %d)-->", graf->poc_put.x, graf->poc_put.y);
	}
	else {
		if (trace[pocetak][kraj] == 0)
			printf("Nije moguci naci put do ovog izlaza.\n");
		else {
			Path(pocetak, trace[pocetak][kraj], trace, graf);
			printf("(%d, %d)", graf->kraj_put.x, graf->kraj_put.y);
		}
	}
}

struct graph * FlojdVarsalovAlg(struct graph *graf) {
	int i, j, k, l;
	int mat[100][100], trace[100][100];
	int duzina, brcvr;
	brcvr = graf->m * graf->n;
	for (i = 0; i < brcvr; i++) {  //kopiramo matricu susednosti posto cemo je menjati
		for (j = 0; j < brcvr; j++) {
			mat[i][j] = graf->mat[i][j];
		}
	}

	for (i = 0; i < brcvr; i++) {  //popunjavamo trace matricu na osnovu mat susednosti
		for (j = 0; j < brcvr; j++) {
			if ((graf->mat[i][j] == 0) || (graf->mat[i][j] == INT_MAX))
				trace[i][j] = 0;
			else if (graf->mat[i][j] == 1)
				trace[i][j] = i;
		}
	}



	int zbir;
	/*FLOJD*/
	for (k = 0; k < brcvr; k++) {
		for (i = 0; i < brcvr; i++) {
			for (j = 0; j < brcvr; j++) {
				zbir = mat[i][k] + mat[k][j];
				if (zbir > 1) zbir = 1;
				if (mat[i][j] > zbir) {
					trace[i][j] = trace[k][j];
					zbir = mat[i][k] + mat[k][j];
					if (zbir > 1) zbir = 1;
					mat[i][j] = zbir;
				}
			}
		}
	}

	/*Pozivamo fju path*/
	int pocetak, kraj;
	pocetak = Nadji(graf->poc_put.x, graf->poc_put.y, graf);
	kraj = Nadji(graf->kraj_put.x, graf->kraj_put.y, graf);
	Path(pocetak, kraj, trace, graf);

	return graf;
}

struct graph * Ispis_obrada(struct graph *graf) {
	int i, j, x, y, k = 0, p = 0;
	int dim;
	dim = graf->m * graf->n;


	/*
	printf("\n\n*MATRICA SUSEDNOSTI*\n");  //PPOMOCNI ISPIS
	for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++)
			if (graf->mat[i][j] != INT_MAX)
				printf(" %d ", graf->mat[i][j]);
			else printf(" max ");
			printf("\n");
	}
	printf("\n\n"); //PPOMOCNI ISPIS-KRAJ
	*/


	for (i = 0; i < graf->m; i++) {
		for (j = 0; j < graf->n; j++) {
			x = Nadji(i, j, graf);
			y = Nadji(i + 1, j, graf);

			int desno, ispod;
			if ((graf->mat[x][x + 1] == 0) || (graf->mat[x][x + 1] == INT_MAX)) desno = 0;
			else if (graf->mat[x][x + 1] == 1) desno = 1;
			else desno = 0;
			if ((graf->mat[x][y] == 0) || (graf->mat[x][y] == INT_MAX)) ispod = 0;
			else if (graf->mat[x][y] == 1) ispod = 1;
			else ispod = 0;

			if (ispod == 0 && desno == 0) {
				graf->maze[k][p] = 0; //ili 1?
				graf->maze[k][p + 1] = 0;
				graf->maze[k + 1][p] = 0;
				graf->maze[k + 1][p + 1] = 0;
			}
			else if (ispod == 1 && desno == 0) {
				graf->maze[k][p] = 1;
				graf->maze[k][p + 1] = 0;
				graf->maze[k + 1][p] = 1;
				graf->maze[k + 1][p + 1] = 0;
			}
			else if (ispod == 0 && desno == 1) {
				graf->maze[k][p] = 1;
				graf->maze[k][p + 1] = 1;
				graf->maze[k + 1][p] = 0;
				graf->maze[k + 1][p + 1] = 0;
			}
			else if (ispod == 1 && desno == 1) {
				graf->maze[k][p] = 1;
				graf->maze[k][p + 1] = 1;
				graf->maze[k + 1][p] = 1;
				graf->maze[k + 1][p + 1] = 0;
			}

			if ((p + 2) >= (2 * graf->n)) {
				k += 2;
				p = 0;
			}
			else p += 2;


		}
	}

	/*
	printf("\n*MATRICA LAVIRINTA*\n"); //PPOMOCNI ISPIS
	for (i = 0; i < 2 * graf->m; i++) {
		for (j = 0; j < (2 * graf->n); j++) {
			printf("%d", graf->maze[i][j]);
		}
		printf("\n");
	}  //PPOMOCNI ISPIS-KRAJ
	*/

	for (i = 0; i < 2 * graf->m; i++) { //izlaze postavljamo na 2
		for (j = 0; j < 2 * graf->n; j++) {
			for (int r = 0; r < graf->br_izlaza; r++) {
				if ((i == 2 * graf->exit[r].x) && (j ==  2 * graf->exit[r].y)) {
					graf->maze[i][j] = 2;
				}
			}
		}
	}

	return graf;
}

void Ispis_glavno(struct graph *graf) {
	int i, j;

	printf("\n***LAVIRINT***\n\n");
	for (i = 0; i < 2 * graf->n; i++)
		printf("%c", ZID);
	printf("\n");
	for (i = 0; i < 2 * graf->m; i++) {
		for (j = 0; j < (2 * graf->n); j++) {
			if ((i == 2*graf->ulaz.x) && (j == 2*graf->ulaz.y)) printf("%c", ULAZ);
			else if (graf->maze[i][j] == 1) printf(" ");
			else if (graf->maze[i][j] == 2) printf("X");
			else printf("%c", ZID);
		}
		printf("\n");
	}
}


void Ispis(struct graph *graf) {
	int opcija;
	char *imedat;
	printf("Gde zelite da se ispise resenje lavirinta?\n 1. Na glavnom izlazu\n 2. U tekstualnoj datoteci\n Opcija: ");
	scanf("%d", &opcija);
	graf = Ispis_obrada(graf);
	if (opcija == 1) {
		Ispis_glavno(graf);
	}//ispis na obicnom izlazu
	else if (opcija == 2) {
		printf("Lavirint vam je u datoteci lavirint.txt\n"); //DOPUNITI
		//scanf("%s", imedat); //POVEZIVANJE DATOTEKE ITD
		FILE *izlaz;
		izlaz = fopen("lavirint.txt", "w");

		int i, j;
		fprintf(izlaz, "\n***LAVIRINT***\n\n");
		for (i = 0; i < 2 * graf->n; i++)
			fprintf(izlaz, "*");
		fprintf(izlaz, "\n");
		for (i = 0; i < 2 * graf->m; i++) {
			for (j = 0; j < (2 * graf->n); j++) {
				if ((i == 2 * graf->ulaz.x) && (j == 2 * graf->ulaz.y)) fprintf(izlaz, "O");
				else if (graf->maze[i][j] == 1) fprintf(izlaz, " ");
				else if (graf->maze[i][j] == 2) fprintf(izlaz, "X");
				else fprintf(izlaz, "*");
			}
			fprintf(izlaz, "\n");
		}
		fclose(izlaz);
	}
	else printf("Izabrana opcija ne postoji.\n");
}


struct graph *StvaranjePlatforme(int *izlaz, struct graph *graf) {
	int opcija;
	printf("Unesite dimenzije lavirinta: \nDuzina: ");
	scanf("%d", &graf->m);
	printf("Sirina: ");
	scanf("%d", &graf->n);
	graf = StvaranjeGrafa(graf);

	printf("Da li zelite da rucno unosite koordinate ulaza i izlaza?\n 1. Da\n 2. Ne\n Opcija: ");
	scanf("%d", &opcija);
	if (opcija == 1) {
		printf("Unesite koordinate ulaza: ");
		scanf("%d %d", &graf->ulaz.x, &graf->ulaz.y);
		printf("Koliko izlaza zelite da lavirint ima? ");
		scanf("%d", &graf->br_izlaza);
		for (int i = 0; i < graf->br_izlaza; i++) {
			printf("Unesite koordinate %d. izlaza: ", i + 1);
			scanf("%d %d", &graf->exit[i].x, &graf->exit[i].y);
		}
	}
	return graf;
}

struct graph * StvaranjeLavirinta(struct graph *graf) {
	int opcija, x1, y1, x2, y2;
	printf("Odaberite nacin generisanja lavirinta:\n -->1. Rucno\n -->2. Automatski\n Opcija: ");
	scanf("%d", &opcija);
	if (opcija == 1) {
		printf("Unesite koordinate prolaza(unosite koordinate polja izmedju kojih zelite da srusite zid):\n");
		printf("(Unos se prekida unosenjem dve iste kooordinate)\n");
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		while ((x1 != x2) || (y1 != y2)) {
			graf = DodajGranu(x1, y1, x2, y2, graf);
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		}
	}
	else if (opcija == 2) {
		graf = Kruskal(graf); //Kruskalov algoritam
	}
	Ispis(graf);

	return graf;
}



struct graph * Resavanje(struct graph *graf) {
	int opcija;
	printf("Odaberite vrstu igre: \n -->1. Nalazenje izlaza\n -->2. Postani Jovica\n Opcija: ");
	scanf("%d", &opcija);
	if (opcija == 1) {
		printf("Do kog izlaza zelite da nadjete put?\n Unesite koordinate: ");
		scanf("%d %d", &graf->kraj_put.x, &graf->kraj_put.y);
		graf->poc_put = graf->ulaz;
		graf = FlojdVarsalovAlg(graf); //poslati koordinate ulaza i izlazaa
	}
	else if (opcija == 2) {
		printf("Zdravo Jovice! Tvoj drug Perica se izgubio i uplasen je. Probaj da nadjes put do njega i pomozi mu da otera strah!\n");
		printf("Unesite Pericine koordinate: ");
		scanf("%d %d", &graf->kraj_put.x, &graf->kraj_put.y); //PERICINE KOORDINATE
		printf("Unesite Jovicine koordinate: ");
		scanf("%d %d", &graf->poc_put.x, &graf->poc_put.y); //JOVICINE KOORDINATE
		graf = FlojdVarsalovAlg(graf); //poslati pericine i jovicine koordinate
	}


	return graf;
}


void main() {
	int opcija, kraj = 0, izlaz;
	//struct graph *graf = malloc(sizeof(struct graph));

	while (!kraj) {
		printf("----------MENI-----------\n 1. Kreiraj platformu za igru\n 2. Kreiraj lavirint\n 3. Resavanje lavirinta\n 4. Resetuj\n ");
		printf("5. Kraj programa\n");
		printf("Unesite redni broj zeljene opcije: ");
		scanf("%d", &opcija);
		switch (opcija) {
		case 1: struct graph *graf = malloc(sizeof(struct graph));
			graf = StvaranjePlatforme(&izlaz, graf); break;
		case 2: graf = StvaranjeLavirinta(graf); break;
		case 3: graf = Resavanje(graf); break;
		case 4: graf = BrisanjeGrafa(graf); break;
		case 5: kraj = 1; break;
		default: printf("Nedozvoljen izbor. Ponovite unos.\n"); break;
		}
		printf("\n---------------------------\n");
	}
	printf("\nPoyy!\n\n\n");
}