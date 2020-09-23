#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100;

typedef struct cvor {
	int broj;
	int popunjeno;
	struct cvor **pp; //pokazivac na niz pok koji pokazuju na sinove
	struct cvor *next; //sinove ulancavam jednostruko
} Cvor;
Cvor *root = NULL;
Cvor *posl_gen = NULL;

Cvor* Stvaranje(Cvor *lst, Cvor *posl_gen, int *pm,int *obrisan) {
	  int i;
	  printf("Unesite red stabla: ");
	  scanf("%d", pm);
   	  Cvor *novi = malloc(sizeof(Cvor));
	  novi->pp = malloc((*pm) * sizeof(Cvor*));
	  for (i = 0; i < *pm; i++) {
		 novi->pp[i] = NULL;
	  }
	  novi->next = NULL;
	  novi->popunjeno = 0;
	  lst = novi;
	  posl_gen = novi;
	  *obrisan = 0;
	  return lst;
	}


Cvor* Umetanje(Cvor *posl_gen, int m, int *plvl, int *p_br_cvorova) {
	int i,j,k,el,smesten=0,pomeri=0;
	Cvor *tek, *tek0, *novi,*sl_brat, *premosti,*preth;
	sl_brat = NULL;
	preth = NULL;
	tek = posl_gen;
	printf("Unesite element: ");
	scanf("%d", &el);
	if (tek->popunjeno == 0) {  //popunjavanje korena stabla
		tek->broj = el;
		tek->popunjeno = 1;
		*plvl = 0;
		(*p_br_cvorova)++;
	}
	else {  //popunjavanje ostalih cvorova
		while (smesten == 0) { //dok se ne javi da je br upisan u stablo vrti petlju
			tek = posl_gen;
			tek0 = NULL;
			do {
				for (i = 0; i < m; i++) { //BR CLANOVA POSLEDNJE GEN,krece se po braci
					if (tek->pp[i] == NULL) { //neki od pok na sina je nula-tu moze da se doda sin
						Cvor *novi = malloc(sizeof(Cvor));
						novi->pp = malloc(m * sizeof(Cvor*));
						for (j = 0; j < m; j++) {
							novi->pp[j] = NULL;
						}
						if ((i + 1) < m)   //ulancavam sinove kao bracu 
							sl_brat = tek->pp[i + 1];
						else sl_brat = NULL;
						novi->broj = el;
						novi->next = sl_brat;
						tek->pp[i] = novi;
						if (i > 0) {
							preth=tek->pp[i - 1];
							preth->next = novi;
						}
						smesten = 1;
						break;
					}
				}
				pomeri++;
				if (tek0) {
					premosti = tek0->pp[m - 1];
					premosti->next = tek->pp[0];
				}
				tek0 = tek;
				tek = tek->next;
			} while ((pomeri != pow(m, *plvl)) && (smesten == 0));
			if (smesten == 0) { //popunjena cela posl gen, pomeramo posl gen
				posl_gen = posl_gen->pp[0];
				(*plvl)++;
				tek = posl_gen;
			}
		}
		(*p_br_cvorova)++;
	}	
	return posl_gen;
}

void Ispis(Cvor *lst, int br_cvorova, int m, int obrisan) {
	Cvor *tek1,*tek2,*poc;
	int i = 0,j;
	tek1=tek2 = poc = lst;
	printf("Izgled stabla: \n");
	if (tek1 && (obrisan!=1)) {
		printf("%d ", tek1->broj); //ispis korena	
		i++;
	  while (i != br_cvorova) {
		printf("\n");
		poc = poc->pp[0];
		tek1= poc;
		while (tek1 != NULL) {
			printf("%d ", tek1->broj);
			i++;
			tek1 = tek1->next;
		}
	  }
	}
	else {
		printf("Stablo je prazno.");
	}
}

void Brisanje(Cvor *lst, int lvl, int *pobrisan, int *pbr_cvorova) {
	Cvor *stari, *tek;
	int i;
	while ((*pobrisan)!=1) { //sve dok ne obrisemo koren
		tek = lst;
		for (i = 0; i < (lvl+1); i++) { //spustamo se na poslednji nivo 
			tek = tek->pp[0];
		}	
		if (tek) {
			while (tek != NULL) {
				stari = tek;
				tek = tek->next;
				free(stari);
			}
		}
		lvl--;
		if ((lvl+1) == 0) {
			free(lst);
			*pobrisan = 1;
			*pbr_cvorova = 0;
		}
	}
}


void main() {
	int opcija, kraj=0,m,lvl,br_cvorova=0, obrisan;
	while (!kraj) {
		printf("----------MENI-----------\n 1. Stvaranje stabla\n 2. Umetanje novog elementa\n 3. Ispis stabla\n 4. Brisanje stabla\n 5. Broj cvorova?\n 6. Kraj programa\n");
		printf("Unesite redni br zeljene opcije: ");
		scanf("%d", &opcija);
		switch (opcija) {
		   case 1: root=Stvaranje(root, posl_gen, &m, &obrisan);
			       posl_gen = root; break;
		   case 2: posl_gen=Umetanje(posl_gen, m, &lvl, &br_cvorova); break;
		   case 3: Ispis(root, br_cvorova,m, obrisan); break;
		   case 4: Brisanje(root, lvl, &obrisan, &br_cvorova); break;
		   case 5: printf("Broj cvorova je: %d ",br_cvorova); break;
		   case 6: kraj = 1; break;
		   default: printf("Nedozvoljen izbor. Ponovite unos.\n"); break; 
		}
		printf("\n---------------------------\n");
	}
}