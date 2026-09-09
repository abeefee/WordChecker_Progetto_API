#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

/*
 * Lista mixata a BST per dizionario
 *
 * next: nodo seguente lista
 * left: figlio sinistro
 * right: figlio destro
 * inPartita: stato della parola nella partita
 * s: parola
 */
struct node{
    struct node *next, *left, *right;
    int inPartita;
    char s[];
} typedef node;

/*
 * Lista per vincoli
 *
 * next: nodo seguente lista
 * s: parola
 * res: vincolo generato
 */
struct node_v{
    struct node_v *next;
    char *s;
    char *res;
} typedef node_v;

/*
 * Struct con risultato del confronto
 *
 * s: parola
 * res: vincolo generato
 * result: 0 se sbagliata, 1 se corretta, 2 se non esiste parola
 */
struct ris_c{
    char *s;
    char *res;
    int result;
} typedef ris_c;

/*
 * Effettua push di una parola in testa
 *
 * head: puntatore testa lista
 * str: stringa da inserire
 */
void push(node **head, char* str);

/*
 * Effettua push vincolo in testa
 *
 * head: puntatore testa lista
 * s: parola
 * res: esito vincolo
 */
void pushVincolo(node_v **head, char* s, char* res);

/*
 * Crea nuovo nodo
 *
 * str: stringa
 *
 * Ritorna nodo creato
 */
node* newNode(char str[]);

/*
 * Crea nuovo nodo durante partita
 *
 * str: stringa
 * iP: stato della parola, se in partita o meno
 *
 * Ritorna nodo creato
 */
node* newNodeInGame(char str[], int iP);

/*
 * Effettua inserimento ordinato di nuovo nodo in albero
 *
 * nodo: radice dell'albero
 * str: stringa
 *
 * Ritorna la radice dell'albero
 */
node* insert(node* nodo, char str[]);


/*
 * Effettua inserimento ordinato di nuovo nodo in albero durante la partita
 *
 * nodo: radice dell'albero
 * str: stringa
 * iP: stato della parola, se in partita o meno
 *
 * Ritorna la radice dell'albero
 */
node* insertInGame(node* nodo, char str[], int iP);

/*
 * Effettua la partita
 *
 * root: radice albero
 * head: testa lista
 */
void partita(node **root, node **head);

/*
 * Aggiorna il dizionario della partita con nuovo vincolo
 *
 * d: testa della lista
 * p: parola inserita
 * r: esito confronto
 */
void aggDiz(node *d, char p[], char res[]);

/*
 * Aggiorna le nuove parole inserite con vincoli conosciuti fino a quel momento
 *
 * hd: testa lista nuove parole
 * hv: testa lista vincoli
 */
void aggDizNuoveParole(node *hd, node_v *hv);

/*
 * Rimette tutte le parole in gioco a fine partita
 *
 * h: testa della lista
 */
void refillDiz(node *h);

/*
 * Effettua controllo tra parola giusta e parola inserita
 *
 * d: testa
 * v: testa lista vincoli
 * p: parola inserita
 * r: parola da indovinare
 *
 * Ritorna struct ris_c con risultati del confronto
 */
ris_c controllo(node *d, node_v *v, char p[], char r[]);

/*
 * Controlla che parola inserita sia in dizionario e fa controllo
 *
 * root: radice albero
 * hd: testa lista
 * hv: testa lista vincoli
 * p: parola inserita
 * r: parola da indovinare
 *
 * Ritorna struct ris_c con risultati confronto
 */
ris_c confronto(node *root, node *hd, node_v *hv, char p[], char r[]);

/*
 * Restituisce NULL se stringa non presente in albero
 *
 * root: radice albero
 * str: stringa da cercare
 *
 * Ritorna root
 */
node *ricerca(node *root, char str[]);

/*
 * Stampa parole dell'albero rimaste in partita in modo ordinato
 *
 * root: radice albero
 */
void stampa_filtrate(node *root);

/*
 * Svuota lista nuove parole inserite dopo averle aggiunte all'albero
 *
 * h: testa lista nuove parole
 */
void svuotaLista(node *h);

/*
 * Ripristina array con caratteri rimossi a fine partita
 */
void svuotaArrRim();

/*
 * Confronta due stringhe
 *
 * s1: stringa 1
 * s2: stringa 2
 *
 * ritorna 1 se s1 > s2, -1 se s1 < s2, 0 se s1 = s2
 */
int faststrcmp(char *s1, char* s2);

/*
 * Conta quante volte un carattere compare in una stringa
 *
 * s: stringa
 * x: carattere
 *
 * Ritorna numero di volte in cui x compare in s
 */
int contaChar(char s[], char x);

/*
 * Conta quante volte compare in posizione giusta o sbagliata un carattere
 *
 * x: carattere
 * s: parola
 * r: esito confronto
 *
 * Ritorna numero di volte in cui x compare giusta in s
 */
int contaInR(char x, char s[], char r[]);

/*
 * Inizializzazione variabili globali
 *
 * k: lunghezza parole
 * nParoleTot: numero parole in dizionario
 * nParoleInGame: numero parole attualmente in partita
 * countRim: numero di caratteri sbagliati imparato dai vincoli
 * inGame: 0 se fuori partita 1 se in partita
 * rim: array contenente i caratteri già rimossi dai vincoli
 * hList: puntatore a ultimo nodo inserito
 */
int k, nParoleTot = 0, nParoleInGame, countRim, inGame = 0;
char rim[64];
node *hList = NULL;

int main(){
    int isNotCmd = 1;
    char str[MAX];
    node *root = NULL;

    if(scanf("%d", &k));
    while(getchar() != '\n');

    while(isNotCmd){
        if(scanf("%s", str));
        if(str[0] == '+'){
            isNotCmd--;
        }
        else{
            root = insert(root, str);
            nParoleTot++;
        }
    }

    if(str[1] == 'n'){
        partita(&root, &hList);
    } else if(str[0] == '+' && str[12] == 'n'){
        int notFineIns = 1;
        while(notFineIns){
            if(scanf("%s", str));

            if(str[0] == '+'){
                notFineIns = 0;
            } else{
                root = insert(root, str);
                nParoleTot++;
            }
        }
    }

    while(fgets(str, MAX, stdin) != NULL){
        if(str[0] == '+' && str[1] == 'n'){
            partita(&root, &hList);
        }else if(str[0] == '+' && str[12] == 'n'){
            int notFineIns = 1;
            while(notFineIns){
                if(scanf("%s", str));

                if(str[0] == '+'){
                    notFineIns = 0;
                } else{
                    root = insert(root, str);
                    nParoleTot++;
                }
            }
        }
    }

    return 0;
}

void push(node **head, char* str){
    node *temp = malloc(sizeof(node) + sizeof(char)*(k+1));
    strcpy(temp->s, str);
    temp->inPartita = 1;
    temp->next = *head;
    *head = temp;
}

void pushVincolo(node_v **head, char* s, char* res){
    node_v * tmp = malloc(sizeof(node_v));

    tmp->s = malloc(sizeof(char)*(k+1));
    tmp->res = malloc(sizeof(char)*(k+1));

    strcpy(tmp->s,s);
    strcpy(tmp->res,res);

    tmp->next = *head;
    *head = tmp;
}

node* newNode(char str[]){
    struct node* temp = malloc(sizeof(struct node) +sizeof(char)*k);
    strcpy(temp->s, str);
    temp->left = temp->right = NULL;
    temp->inPartita = 1;
    temp->next = hList;
    hList = temp;
    return temp;
}

node* newNodeInGame(char str[], int iP){
    struct node* temp = malloc(sizeof(struct node) +sizeof(char)*k);
    strcpy(temp->s, str);
    temp->left = temp->right = NULL;
    temp->inPartita = iP;
    temp->next = hList;
    hList = temp;
    return temp;
}

node* insert(node* nodo, char str[]){
    if (nodo == NULL){
        return newNode(str);
    }
    if (faststrcmp(str, nodo->s) < 0){
        nodo->left = insert(nodo->left, str);
    } else if (faststrcmp(str, nodo->s) > 0){
        nodo->right = insert(nodo->right, str);
    }
    return nodo;
}

node* insertInGame(node* nodo, char str[], int iP){
    if (nodo == NULL){
        return newNodeInGame(str, iP);
    }
    if (faststrcmp(str, nodo->s) < 0){
        nodo->left = insertInGame(nodo->left, str, iP);
    } else if (faststrcmp(str, nodo->s) > 0){
        nodo->right = insertInGame(nodo->right, str, iP);
    }
    return nodo;
}

void partita(node **root, node **head){
    int correct = 0, t, tEff = 0;
    ris_c ris;
    char r[k+1], str[MAX];
    node_v *hv = NULL;
    nParoleInGame = nParoleTot;
    countRim = 0;
    inGame = 1;

    if(scanf("%s", r));

    if(scanf("%d", &t));
    while(getchar() != '\n');

    while(tEff < t && correct == 0){
        if(scanf("%s", str));
        if(str[0] != '+'){
            ris = confronto(*root, *head, hv, str, r);

            if(ris.result == 0){
                aggDiz(*head, ris.s, ris.res);
                printf("%d\n", nParoleInGame);
                pushVincolo(&hv, ris.s, ris.res);
                tEff++;
            } else if(ris.result == 1){
                printf("ok\n");
                refillDiz(*head);
                svuotaArrRim();
                inGame = 0;
                return;
            } else if(ris.result == 2){
                printf("not_exists\n");
            }
        } else if(str[0] == '+' && str[1] == 's'){
            stampa_filtrate(*root);
        } else if(str[0] == '+' && str[12] == 'n'){
            int notFineIns = 1;
            node *nW = NULL;
            while(notFineIns){
                if(scanf("%s", str));
                if(str[0] == '+'){
                    aggDizNuoveParole(nW, hv);
                    for(node *l = nW; l != NULL; l = l->next){
                        *root = insertInGame(*root, l->s, l->inPartita);
                    }
                    notFineIns = 0;
                    svuotaLista(nW);
                } else{
                    push(&nW, str);
                    nParoleInGame++;
                    nParoleTot++;
                }
            }
        }
    }
    if(correct == 0){
        printf("ko\n");
        refillDiz(*head);
        svuotaArrRim();
        inGame = 0;
    }

}

void aggDiz(node *d, char p[], char res[]){
    int n[k];
    for (int i = 0; i < k; i++){
        n[i] = contaInR(p[i], p, res);
    }
    for(node *l = d; l != NULL; l = l->next){
        if(l->inPartita){
            for(int i = 0; i < k && l->inPartita; i++){

                if(res[i] == '/'){
                    if(n[i] >= 1){
                        if(l->inPartita && contaChar(l->s, p[i]) != n[i]){
                            l->inPartita = 0;
                            nParoleInGame--;
                        }
                    }
                    if(n[i] != 0){
                        if(l->inPartita && l->s[i] == p[i]){
                            l->inPartita = 0;
                            nParoleInGame--;
                        }
                    } else if (n[i] == 0){
                        int ctrl = 1;
                        for(int j = 0; j < k && ctrl; j++){
                            if(l->inPartita &&  l->s[j] == p[i]){
                                l->inPartita = 0;
                                nParoleInGame--;
                                ctrl = 0;
                            }
                        }
                    }
                } else if(res[i] == '|'){
                    if(l->inPartita && l->s[i] == p[i]){
                        l->inPartita = 0;
                        nParoleInGame--;
                    }else if (l->inPartita){
                        if(n[i] >= 1){
                            if(l->inPartita && contaChar(l->s, p[i]) < n[i]){
                                l->inPartita = 0;
                                nParoleInGame--;
                            }
                        }
                    }
                } else if(res[i] == '+'){
                    if(l->inPartita && l->s[i] != p[i]){
                        l->inPartita = 0;
                        nParoleInGame--;
                    } else if(l->inPartita){
                        if(n[i] > 1){
                            if(l->inPartita && contaChar(l->s, p[i]) < n[i]){
                                l->inPartita = 0;
                                nParoleInGame--;
                            }
                        }
                    }
                }
            }
        }
    }

}

void aggDizNuoveParole(node *hd, node_v *hv){
    for(node_v *l = hv; l != NULL; l = l->next){
        aggDiz(hd,l->s, l->res);
    }
}

void refillDiz(node *h){
    for(node* l = h; l != NULL; l = l->next){
        l->inPartita = 1;
        nParoleInGame--;
    }
}

ris_c controllo(node *d, node_v *v, char p[], char r[]){
    ris_c risultato;

    risultato.s = malloc(sizeof(char)*(k+1));
    risultato.res = malloc(sizeof(char)*(k+1));

    char  rCopia[k+1];
    strcpy(risultato.s, p);
    strcpy(rCopia, r);
    int ctrl, j;

    if(faststrcmp(p,r) == 0){
        risultato.result = 1;
        return risultato;
    }
    else{

        for(int i = 0; i < k; i++){
            if(p[i] == rCopia[i]){
                p[i] = '*';
                rCopia[i] = '*';
                risultato.res[i] = '+';
            }
        }
        for(int i = 0; i < k; i++){
            if(p[i] != '*'){
                j = 0;
                ctrl = 1;
                while(j < k && ctrl){
                    if(p[i] == rCopia[j]){
                        p[i] = '*';
                        rCopia[j] = '*';
                        risultato.res[i] = '|';
                        ctrl = 0;
                    }
                    j++;
                }
                if(ctrl == 1){
                    p[i] = '*';
                    risultato.res[i] = '/';
                }
            }
        }
        risultato.res[k] = '\0';
        printf("%s\n", risultato.res);
        risultato.result = 0;

        return risultato;
    }
}

ris_c confronto(node *root, node *hd, node_v *hv, char p[], char r[]){
    if(ricerca(root, p) != NULL){
        return controllo(hd, hv, p, r);
    }
    else {
        ris_c ris;
        ris.result = 2;
        return ris;
    }
}

node *ricerca(node *root, char str[]){
    if(root == NULL || (faststrcmp(root->s, str) == 0)){
        return root;
    } else if(faststrcmp(str, root->s) < 0){
        return ricerca(root->left, str);
    } else{
        return ricerca(root->right, str);
    }
}

void stampa_filtrate(node *root){
    if(root != NULL){
        stampa_filtrate(root->left);
        if(root->inPartita){
            printf("%s\n", root->s);
        }
        stampa_filtrate(root->right);
    }
}

void svuotaLista(node *h){
    node *tmp;
    while(h != NULL){
        tmp = h;
        h = h->next;
        free(tmp);
    }
}

void svuotaArrRim(){
    for(int i = 0; i < countRim; i++){
        rim[i] = '*';
    }
}

int faststrcmp(char *s1, char* s2){
    int i = 0;
    while(i < k){
        if(s1[i] > s2[i]){
            return 1;
        } else if(s1[i] < s2[i]){
            return -1;
        } else{
            i++;
        }
    }
    return 0;
}

int contaChar(char s[], char x){
    int n = 0;
    for(int i = 0; i < k; i++){
        if(s[i] == x){
            n++;
        }
    }
    return n;
}

int contaInR(char x, char s[], char r[]){
    int n = 0;
    for(int i = 0; i < k; i++){
        if(s[i] == x && (r[i] == '+' || r[i] == '|')){
            n++;
        }
    }
    return n;
}