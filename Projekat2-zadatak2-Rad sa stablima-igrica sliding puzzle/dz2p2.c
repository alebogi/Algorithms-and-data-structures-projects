#include <stdio.h>
#include <stdlib.h>


typedef struct cvor {
	int mat[3][3];
	struct cvor **pp; //pokazivac na niz pok koji pokazuju na sinove
} Cvor;
Cvor *root = NULL;
Cvor *posl = NULL;

typedef struct lista{
	struct cvor *pok;
	struct lista *next;
} Lista;
Lista **list = NULL;

Cvor * Unos(Cvor *lst) {
	int i, j;
	printf("Unesite izgled pocetne pozicije(popunjavajuci po vrstama): \n");
	Cvor *novi = malloc(sizeof(Cvor));
	novi->pp = malloc(4 * sizeof(Cvor*));
	for (i = 0; i < 4; i++) {
		novi->pp[i] = NULL;
	}
	lst = novi;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			scanf("%d", &lst->mat[i][j]);
	}
	printf("Izgled pocete:\n"); //PROVERA ISPIS
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d ", lst->mat[i][j]);
		} 
		printf("\n");
	}//KRAJ PROVERA ISPIS
	return lst;
}

void Unos_kraj(int krajnja[][3]) {
	int i, j;
	printf("Unesite izgled krajnje pozicije(popunjavajuci po vrstama): \n");
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++)
			scanf("%d", &krajnja[i][j]);
	}
	printf("Izgled krajnje:\n"); //PROVERA ISPIS
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d ", krajnja[i][j]);
		}
		printf("\n");
	}//KRAJ PROVERA ISPIS
}


Cvor * Generisi_poc(Cvor *lst) {
	int i, j,k, m, upisan=0,postoji=0,niz[9],duzina_niza=0;
	printf("Pocetna pozicija: \n");
	Cvor *novi = malloc(sizeof(Cvor));
	novi->pp = malloc(4 * sizeof(Cvor*));
	for (i = 0; i < 4; i++) {
		novi->pp[i] = NULL;
	}
	lst = novi;
		
	for (i = 0; i<3; i++) {
		for (j = 0; j<3; j++) {
			upisan = 0;
			while (upisan != 1) {
				postoji = 0;
	    	  lst->mat[i][j] = rand() / ((double)RAND_MAX + 1) * 9;		//generise broj	
				for (k = 0; k < duzina_niza; k++) { //pretraga niza
					if (niz[k]==lst->mat[i][j]) postoji++; //ako je generisan br u nizu detektuje ga 
							
				 }
				if (postoji) upisan = 0;  //ako je bio u nizu, moramo opet da generisemo
				else {     //ako nije bio u nizu dodamo ga u niz i produzimo duzinu niza i kazemo da je generisani broj ok, i ne moramo vise da ga gen.
					niz[duzina_niza] = lst->mat[i][j];
					duzina_niza++;
					upisan = 1; 
				}
			 }
		 }
	 }
		
	
	for (i = 0; i < 3; i++) {//Ispis
		for (j = 0; j < 3; j++) {
			printf("%d ", lst->mat[i][j]);
		} 
		printf("\n");
	}
	return lst;
}

void Generisi_kraj(int krajnja[][3], Cvor *root) {
	int i, j, red, kol, pom;
	printf("Krajnja pozicija: \n");
	for (i = 0; i < 3; i++) { //kopiranje pocetne
		for (j = 0; j < 3; j++)
			krajnja[i][j] = root->mat[i][j];
	}
	//shuffle
	for (i = 0; i <2; i++) {
		for (j = 0; j < 2; j++) {
			red = rand() / ((double)RAND_MAX + 1)*(2 + 1);
			kol = rand() / ((double)RAND_MAX + 1)*(2 + 1);
			pom = krajnja[i][j];
			krajnja[i][j] = krajnja[red][kol];
			krajnja[red][kol] = pom;
		}
	}
	for (i = 0; i < 3; i++) {// Ispis
		for (j = 0; j < 3; j++) {
			printf("%d ", krajnja[i][j]);
		}
		printf("\n");
	}
}

void Resivost(Cvor *lst,int krajnja[][3]) {
	int i, j, zamena = 0, k, m, red_poc, red_kraj, kol_poc, kol_kraj, temp;
	Cvor *pom= malloc(sizeof(Cvor));
	for (i = 0; i<3; i++)   //da ne bismo promenili root
		for (j = 0; j<3; j++)
			pom->mat[i][j] = lst->mat[i][j];
	//prvo pravilima igre dovesti 0 na isto mesto gde je i u krajnjoj poziciji
	for (i = 0; i < 3; i++) { 
		for (j = 0; j < 3; j++) {
			if (krajnja[i][j] == 0) { 
				red_kraj = i;
				kol_kraj=j;
				break;
			}
		}
	} //lokacija praznog polja u krajnjoj poziciji
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (pom->mat[i][j] == 0) {
				red_poc = i;
				kol_poc = j;
				break;
			}
		}
	} //lokacija pranog polja u pocetnoj poziciji

	if (red_poc < red_kraj){
		while (red_poc != red_kraj){
			pom->mat[red_poc][kol_poc] = pom->mat[red_poc + 1][kol_poc];
			pom->mat[red_poc + 1][kol_poc] = 0;
			red_poc++;
		}

	}

	if (red_poc > red_kraj) {
		while (red_poc!=red_kraj) {
			pom->mat[red_poc][kol_poc] = pom->mat[red_poc - 1][kol_poc];
			pom->mat[red_poc - 1][kol_poc] = 0;
			red_poc--;
		}
	}

	if (kol_poc < kol_kraj){
		while (kol_poc != kol_kraj){
			pom->mat[red_poc][kol_poc] = pom->mat[red_poc][kol_poc + 1];
			pom->mat[red_poc][kol_poc + 1] = 0;
			kol_poc++;
		}
	}

	if (kol_poc > kol_kraj){
		while (kol_poc != kol_kraj){
			pom->mat[red_poc][kol_poc] = pom->mat[red_poc][kol_poc - 1];
			pom->mat[red_poc][kol_poc - 1] = 0;
			kol_poc--;
		}
	}

	//uporedjujem mesta na poc i krajnjoj poziciji,ako se razlikuju nadjem taj element i zamenim mu mesto
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (pom->mat[i][j] == krajnja[i][j]) continue;
			else {
				for (k = 0; k < 3; k++) {
					for (m =0; m < 3; m++) {
						if ((pom->mat[k][m]) == (krajnja[i][j])) { 
							temp = pom->mat[i][j];
							pom->mat[i][j] = pom->mat[k][m];
							pom->mat[k][m] = temp;
							zamena++;
						}
					}
				}
			}
		}
	}
	//ako je br zamena paran-resivo je
	if (zamena % 2==0) {
		printf("Zadatu kombinaciju je moguce resiti.\n");
	}
	else  {
		printf("Zadatu kombinaciju nije moguce resiti.\n");
	}	
}

void Ispis(Cvor *lst) {
	int i, j;
	for (i = 0; i < 3; i++) {//Ispis
		for (j = 0; j < 3; j++) {
			printf("%d ", lst->mat[i][j]);
		}
		printf("\n");
	}

	printf("  |\n  V\n");
}

int Zavrsna_provera(Cvor *tek, int krajnja[][3]) {
	int i, j, razl=0;
	for (i=0;i<3;i++)
		for (j = 0; j < 3; j++) {
			if (tek->mat[i][j] != krajnja[i][j]) razl++;
		}
	if (razl) return 0; //jos nije kraj
	else return 1; //jeste kraj
}

int Slicnost(Cvor *tek, int krajnja[][3]) {
	int i, j, sl = 0;
	for (i = 0; i<3; i++)
		for (j = 0; j < 3; j++) {
			if (tek->mat[i][j] == krajnja[i][j]) sl++;
		}
	return sl;
}


Lista *Upisi_u_listu(Lista **poc, Cvor *lst) {
	int i, j;
	Lista *tek,*novi=NULL;
	Lista **pom;

	if (poc != NULL) {
		Lista *novi = malloc(sizeof(Lista));
		novi->pok = lst;
		novi->next = *poc;
		*poc = novi;
	}
	
	tek = *poc;
	return *poc;
}

Cvor *Pomeri_desno(Cvor *tek) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (tek->mat[i][j] == 0) {
				tek->mat[i][j] = tek->mat[i][j + 1];
				tek->mat[i][j + 1] = 0;
				return tek;
			}
		}
	}
}

Cvor *Pomeri_levo(Cvor *tek) {
	int i, j;
	for (i = 0; i<3; i++)
		for (j = 0; j < 3; j++) {
			if (tek->mat[i][j] == 0) {
				tek->mat[i][j] = tek->mat[i][j - 1];
				tek->mat[i][j - 1] = 0;
				return tek;
			}
		}
}

Cvor *Pomeri_gore(Cvor *tek) {
	int i, j,temp;
	for (i =0 ; i<3; i++)
		for (j = 0; j < 3; j++) {
			if (tek->mat[i][j] == 0) {
				temp = tek->mat[i][j];
				tek->mat[i][j] = tek->mat[i - 1][j];
				tek->mat[i-1][j] = temp;
				return tek;
			}
		}
}

Cvor *Pomeri_dole(Cvor *tek) {
	int i, j;
	for (i = 0; i<3; i++)
		for (j = 0; j < 3; j++) {
			if (tek->mat[i][j] == 0) {
				tek->mat[i][j] = tek->mat[i+1][j];
				tek->mat[i+1][j] = 0;
				return tek;
			}
		}
}

void Koordinate_nule(Cvor *tek, int *pi, int *pj) {
	int i, j;
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++)
			if (tek->mat[i][j] == 0) {  //koordinate praznog mesta
				*pi = i;
				*pj = j;
				break;
			}
}

int Najbolji(int niz[4]) {
	int i, pozicija=0, max;
	max = niz[0];
	for (i = 0; i < 4; i++) {
		if (niz[i] > max) {
			max = niz[i];
			pozicija = i;
		}
	}
	return pozicija;
}

Cvor *Proveri_sinove(Cvor *lst, int krajnja[][3], Lista **list) {
	int i, j, sl,niz[4];
	Cvor *tek;
	for (i = 0; i < 4; i++) {
		if (lst->pp[i] != NULL) {
			tek = lst->pp[i];
			sl = Slicnost(tek,krajnja);
			niz[i] = sl;
		}
	}
	i = Najbolji(niz); //nasao najboljeg
	if (list == NULL) {
		list = malloc(sizeof(Lista*));
		*list = malloc(sizeof(Lista));
		(*list)->pok = lst;
		(*list)->next = NULL;
	} 
	else *list = Upisi_u_listu(list, lst); //upise u listu oca
	lst = lst->pp[i]; //sin sada postaje glavni
	Ispis(lst); //ispise ga
	return lst;
}

int Vec_postoji(Cvor *sin, Lista **list) {
	int i, j, isti = 0, postoji = 0;
	Lista *tek;
	if (list != NULL) {
		tek = *list;
		while (tek != NULL) {
			isti = 0;
			for (i = 0; i < 3; i++)
				for (j = 0; j < 3; j++) {
					if ((tek->pok->mat[i][j]) == (sin->mat[i][j])) isti++;
				}
			if (isti == 9) {
				postoji = 1;
				break;
			}
			tek = tek->next;
		}
	}
	if (postoji) return 1;
	else return 0;
}

Cvor *Napravi_sinove(Cvor *lst, int *pi0, int *pj0, Lista **list, Lista **sinovi) {
	int i, j, k,levo=0, desno=0, gore=0, dole=0, napravljen=0;
	Cvor *sin;
	for (k = 0; k < 4; k++) { //da napravi svako dete
		Cvor *novi = malloc(sizeof(Cvor));
		novi->pp = malloc(4 * sizeof(Cvor*));
		for (i = 0; i < 4; i++) {
			novi->pp[i] = NULL;
		}
		for (i = 0; i<3; i++)   //kopiramo od oca matricu
			for (j = 0; j<3; j++)
				novi->mat[i][j] = lst->mat[i][j];
		sin = novi;
		napravljen = 0;
		//vrsimo izmenu na sinu
		if ((*pi0) > 0 && gore == 0 && napravljen==0) {  //pomera prazno polje gore
			sin = Pomeri_gore(sin);
			gore = 1;
			napravljen = 1;
		}

		if ((*pj0)<2 && desno==0 && napravljen == 0) {      //desno
			sin = Pomeri_desno(sin);
			desno = 1;
			napravljen = 1;
		}

		if ((*pj0)>0 && levo==0 && napravljen == 0) {     //levo
			sin = Pomeri_levo(sin);
			levo = 1;
			napravljen = 1;
		}

		if ((*pi0)<2 && dole == 0 && napravljen == 0) {   //pomera dole
			sin = Pomeri_dole(sin);
			dole = 1;
			napravljen = 1;
		}

		if (napravljen == 0) {
			sin = NULL;
			lst->pp[k] = NULL;
		}
		else if(napravljen==1){
			if (Vec_postoji(sin, list) == 0) {
				*sinovi = Upisi_u_listu(sinovi,sin);
				lst->pp[k] = sin; 
			}//ne postoji u listi i treba granati
		}
	}
	return lst;
}

void Simulacija(Cvor *lst, int krajnja[][3]) {
	int i, j, temp, i_0, j_0, kraj=0, prolazak=0;	
	Cvor *tek, *pom=NULL;	
	Lista **list; //pok na pocetak liste
	list = malloc(sizeof(Lista*));
	*list = malloc(sizeof(Lista));
	(*list)->pok = lst;
	(*list)->next = NULL;
	Lista **sinovi;
	sinovi = malloc(sizeof(Lista*));
	*sinovi = malloc(sizeof(Lista));
	(*sinovi)->pok = lst;
	(*sinovi)->next = NULL;

	Ispis(lst);
	while (kraj!=1) {
		Koordinate_nule(lst, &i_0, &j_0); 
		lst=Napravi_sinove(lst, &i_0, &j_0,list,sinovi); 
		lst=Proveri_sinove(lst,krajnja,list);
		kraj=Zavrsna_provera(lst, krajnja);
		prolazak++;
		if (prolazak > 80) {
			lst = (*sinovi)->next->pok;
			*sinovi = (*sinovi)->next;
		}
	}
	printf("CESTITAMO! Uspesno ste resili slagalicu!");
}

void main() {
	int opcija, kraj = 0, m, krajnja[3][3], i,j,red, kol,pom, prazno = 0;
	while (!kraj) {
		printf("----------MENI-----------\n 1. Unosenje pocetne i krajnje pozicije\n 2. Generisi pocetnu i krajnju poziciju\n 3. Provera resivosti\n 4. Simulacija igre\n 5. Kraj programa\n");
		printf("Unesite redni br zeljene opcije: ");
		scanf("%d", &opcija);
		switch (opcija) {
		case 1: root = Unos(root);
			Unos_kraj(krajnja);
			break;
		case 2: root = Generisi_poc(root);
			Generisi_kraj(krajnja,root);
			break;
		case 3: Resivost(root,krajnja); break;
		case 4: Simulacija(root,krajnja); break;
		case 5: kraj = 1; break;
		default: printf("Nedozvoljen izbor. Ponovite unos.\n"); break;
		}
		printf("\n---------------------------\n");
	}
}