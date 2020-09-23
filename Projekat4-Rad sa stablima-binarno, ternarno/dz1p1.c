#include <stdio.h>
#include <stdlib.h>

struct node {
	int key;
	int cnt;
	struct node *left;
	struct node *right;
};

struct queue {
	struct node *BSTnode;
	struct queue *next;
};

//deklaracije funkcija
struct node * CreateNode();
struct node * CreateBST();
int SearchBST(); 
struct node * InsertNode(); 
void PrintBST(); 
struct node * DeleteNode(); 
struct node * DeleteBST();
void PrintRightNode();

struct queue *InsertQ();
struct queue* DeleteQ();
int EmptyQ();
int CountQ();
//kraj deklaracija

struct queue *InsertQ(struct queue *first, struct node *bst) {
	struct queue *new;
	struct queue *pt = first;
	if (EmptyQ(first) == 1) {
		first = (struct queue *)malloc(sizeof(struct queue));
		first->BSTnode = bst;
		first->next = NULL;
	}
	else {
		new = (struct queue *)malloc(sizeof(struct queue));
		new->BSTnode = bst;
		new->next = NULL;
		while (pt->next != NULL)
			pt = pt->next;
		pt->next = new;
	}
	return first;
}

struct queue* DeleteQ(struct queue *first) { //prethodi operacija next=myQueue->BSTnode; myQueue=DeleteQ(myQueue);
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

struct node * CreateNode(struct node *node) {
	node = (struct node *)malloc(sizeof(struct node));
	node->cnt = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}

struct node * CreateBST(struct node *root) {
	root = CreateNode(root);
	printf("Unesite vrednost kljuca korena stabla koji formirate: ");
	scanf("%d", &root->key);
	return root;
}

int SearchBST(struct node *root) {
	struct node *pt = root;
	int findKey, succesful = 1, fail = 0;
	printf("Ukucajte vrednost kljuca koji zelite da pretrazite: ");
	scanf("%d", &findKey);
	while ((pt != NULL) && (pt->key!=findKey)) {
		if (findKey < pt->key)
			pt = pt->left;
		else if (findKey > pt->key)
			pt = pt->right;
	}

	if (pt != NULL)
		return succesful;
	else
		return fail;
}

struct node * InsertNode(struct node *root) {
	struct node *pt = root;
	struct node *hpt = NULL;
	int insertKey;
	printf("Ukucajte vrednost kljuca koji dodajete: ");
	scanf("%d", &insertKey);
	while (pt != NULL) {
		hpt = pt;
		if (insertKey < pt->key)
			pt = pt->left;
		else if (insertKey > pt->key)
			pt = pt->right;
		else if (insertKey == pt->key) {
			pt->cnt++;
			break;
		}
	}
	if (pt == NULL) {
		if (insertKey < hpt->key) {
			hpt->left = CreateNode(hpt->left);
			hpt->left->key = insertKey;
		}
		else if (insertKey > hpt->key) {
			hpt->right = CreateNode(hpt->right);
			hpt->right->key = insertKey;
		}
	}
	printf("Kljuc je uspesno dodat.\n");
	return root;
}

void PrintBST(struct node *root) { //level-order
	int i;
	struct node *next=root;
	struct queue *myQueue = NULL;
	if (root == NULL) {
		printf("Stablo je prazno.\n");
	}
	else {
		myQueue = InsertQ(myQueue, next);
		while (EmptyQ(myQueue) != 1) {
			next = myQueue->BSTnode;
			myQueue = DeleteQ(myQueue);
			if (next->cnt == 1) {
				printf("%d ", next->key);
			}
			else {
				printf("%d ", next->key);
				i = next->cnt - 1;
				for (; i > 0; i--) {
					printf("[%d] ", next->key);
				}
			}
			if (next->left != NULL)
				myQueue = InsertQ(myQueue, next->left);
			if (next->right != NULL)
				myQueue = InsertQ(myQueue, next->right);
		}
	}
}

struct node * DeleteBST(struct node *root) {
	struct node *next = root;
	struct node *old;
	struct queue *myQueue = NULL;
	myQueue = InsertQ(myQueue, next);
	while (EmptyQ(myQueue) != 1) {
		next = myQueue->BSTnode;
		old = next;
		myQueue = DeleteQ(myQueue);
		if (next->left != NULL)
			myQueue = InsertQ(myQueue, next->left);
		if (next->right != NULL)
			myQueue = InsertQ(myQueue, next->right);
		free(old);
	}
	root = NULL;
	return root;
}

struct node * DeleteNode(struct node *root) {
	int deleteKey;
	struct node *pt = root;
	struct node *hpt = NULL;
	struct node *rpt, *f, *s;
	printf("Unesite broj kljuca koji zelite da uklonite: ");
	scanf("%d", &deleteKey);
	while ((pt != NULL) && (deleteKey != pt->key)) { //pretraga kljuca
		hpt = pt;
		if (deleteKey < pt->key) {
			pt = pt->left;
		}
		else {
			pt = pt->right;
		}
	}//kraj pretrage

	if (pt == NULL)
		printf("Trazeni kljuc ne postoji.\n");
	else {
		if (pt->cnt > 1) { //ako ih ima vise samo smanjimo brojac
			pt->cnt--;
			printf("Kljuc uspesno uklonjen.\n");
		}
		else { //fizicki uklanjamo cvor
			if (pt->left == NULL) //ima samo desnog sina
				rpt = pt->right;
			else if (pt->right == NULL) //ima samo levog sina
				rpt = pt->left;
			else { //ima oba sina
				f = pt;
				rpt = pt->right;
				s = rpt->left;
				while (s != NULL) {
					f = rpt;
					rpt = s;
					s = rpt->left;
				}
				if (f != pt) {
					f->left = rpt->right;
					rpt->right = pt->right;
				}
				rpt->left = pt->left;
			}

			if (hpt == NULL)
				root = rpt;
			else if (pt == hpt->left)
				hpt->left = rpt;
			else
				hpt->right = rpt;
			free(pt);
			printf("Kljuc uspesno uklonjen.\n");
		}		
	}

	return root;
}

void PrintRightNode(struct node *root) {
	struct node *pt = root;
	struct node *next = root;
	int level, lengthQ, lvl;
	printf("Unesite broj nivoa: ");
	scanf("%d", &level);
	lvl = level;
	int fail=1;
	struct queue *myQueue = NULL;
	myQueue = InsertQ(myQueue, next);
	while (EmptyQ(myQueue) != 1) {
		lengthQ = CountQ(myQueue);
		while (lengthQ--) {
			next = myQueue->BSTnode;
			myQueue = DeleteQ(myQueue);
			if (next->left != NULL)
				myQueue = InsertQ(myQueue, next->left);
			if (next->right != NULL)
				myQueue = InsertQ(myQueue, next->right);
			if ((lengthQ == 0) && (level == 0)) {
				printf("Najdesniji cvor %d. nivoa je %d.", lvl, next->key);
				fail = 0;
			}
		}
		level--;
	}
	if (fail) printf("Trazeni nivo ne postoji.\n");
}

void main() {
	int option, end = 0, result;
	struct node *root=NULL;
	while (!end) {
		printf("----------MENI----------\n");
		printf("1. Formiranje stabla\n");
		printf("2. Pretraga stabla\n");
		printf("3. Umetanje kljuca\n");
		printf("4. Ispis stabla\n");
		printf("5. Brisanje kljuca\n");
		printf("6. Brisanje stabla\n");
		printf("7. Ispis krajnjeg desnog kljuca na zadatom nivou\n");
		printf("8. Kraj programa\n");
		printf("-----------------------\n");
		printf("Unesite redni broj zeljene opcije: ");
		scanf("%d", &option);
		switch (option) {
		case 1: root=CreateBST(root); break;
		case 2: result = SearchBST(root);
			if (result == 1)
				printf("Trazeni kljuc postoji.\n");
			else if (result==0)
				printf("Trazeni kljuc ne postoji.\n");
				break;
		case 3: root = InsertNode(root); break;
		case 4: PrintBST(root); break; 
		case 5: root = DeleteNode(root); break; 
		case 6: root = DeleteBST(root); 
			if (root == NULL)
				printf("Stablo je uspesno obrisano.\n");
				break;
				
		case 7: PrintRightNode(root); break;
		case 8: end = 1; break;
		default: printf("Nedozvoljen izbor. Ponovite unos.\n"); break;
		}
		printf("\n----------------------------\n");
	}
	printf("Uzivajte u zivotu!\n\n");
}