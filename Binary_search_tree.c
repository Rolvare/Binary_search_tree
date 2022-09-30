/*  
  Arquivo: Binary_search_tree
  Autor: LUCCA ROLVARE
  Date: 30/08/22 16:38
  Descricao: Esse é um programa da arvore binaria de busca.
*/
#include <stdio.h>
#include<stdlib.h>;

typedef struct No{
    int item;
    int size;
    struct No *pai;
    struct No *esq;
    struct No *dir;
}No;

typedef No *ABB;

//interface
    ABB criarAbb();
    void mostrarDados(ABB); //mostra dados em ordem crescente
No *buscarABB(ABB, int);
ABB *inserir(ABB, int);
No *obterMinimo(ABB); //menor elemento
No *obterMaximo(ABB); //maior elemento
No *selection(ABB, int); //obter elemento de ordem k na ordem crescente
    int rank(ABB, int);
No *obterAnterior(ABB, int); //devolve a ref. do no anterior na ordem cresc.
No *obterSeguinte(ABB, int);

//main
int main(){
    ABB a;
    //a = criarABB();
}

//desenvolvimento
ABB criarABB(){
    ABB tree;
    
    tree = NULL;
    return tree;
}

void mostrarDados(ABB ap){  //caminhamento eRd
    if(ap != NULL){
        mostrarDados(ap->esq);
        printf("\n %d \n", ap->item);
        mostrarDados(ap->dir);
    }
}

No *buscarABB(ABB ap, int y){
    No *p;
    
    p = ap;
    while((p != NULL) && (p->item != y)){  //especificamente nessa ordem
        if(y < p->item){
            p = p->esq;
        }else{
            p = p->dir;
        }
    }
    return p;
}

ABB *inserir(ABB ap, int y){
    No *novo, *p, *ant;
    
    novo = malloc(sizeof(No));
    novo->item = y;
    novo->size = 1;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    if(ap == NULL){
        ap = novo;
    }else{
        p = ap;
        while(p != NULL){
            ant = p;
            p->size = p->size + 1;
            if(novo->item < p->item){
                p = p->esq;
            }else{
                p = p->dir;
            }
        }
        if(novo->item < ant->item){
            ant->esq = novo;
        }else{
            ant->dir= novo;
        }
    }
    return ap;
}

No *obterMinimo(ABB ap){
    No *p;
    
    p = ap;
    if(p != NULL){
        while (p->esq != NULL){ //tem filho esquerdo
            p = p->esq;
        }
    }
    return p;
}

No *obterMaximo(ABB ap){
    No *p;

    p = ap;
    if(p != NULL){
        while(p->dir != NULL){  //tem filho direito
            p = p->dir;
        }
    }
    return p;
}

No *selection(ABB ap, int k){
    No *p, *e;
    int j;
    p = ap;

    if(ap != NULL){
        if(p->esq == NULL){
            j = 0;
        }else {
            e = p->esq;
            j = e->size;
        }
        if(k < j+1){
            p = sect(ap->esq, k);
        }else if(k > j+1){
            p = select(ap->dir, k-j-1);
        }
    }
    return p;
}

int rank(ABB ap, int y){
    int R = 0;
    No *p, *e, *d;
    
    if(ap != NULL){
        p = ap;
    }
    while((p != NULL) && (y != p->item)){
        if(y > p->item){
            d = p->dir;
            if(d != NULL){
                R = R + p->size - d->size; //menores
                p = p->dir;
            }
        }else{
            p = p->esq;
        }
        if(p != NULL){
            R = R + 1; //o proprio
            e = p-> esq;
            if(e != NULL){
                R = R + e->size; //menores
            }else{
                R = 0;
            }
        }
    }
    return R;
}
No *obterAnterior(ABB ap, int y){
    No *p, *ant, *R, *fa;
    ant = NULL;
    p = ap;
    while((p != NULL) && (p->item != y)){ //busca
        if(y < p->item){
            p = p->esq;
        }else{
            p = p->dir;
        }

        if(p != NULL){
            R = p->esq;
            if(R != NULL){
                p = R;      //maximo do lado esquerdo
                while(p->dir != NULL){ 
                    p = p->dir;
                    ant = p;
                }
            }else{  //ancestral mais proximo e menor
                fa = p->pai;
                while((fa != NULL) && (fa->esq == p)){
                    p = fa;
                    fa = p->pai;
                }
                if(fa != NULL){
                    ant = fa;
                }
            }
        }
    }
    return ant;
}

No *obterSeguinte(ABB ap, int y){
    No *p, *suc, *R, *fa;
    suc = NULL;
    p = ap;
    while((p != NULL) && (p->item != y)){  //busca
        if(y < p->item){
            p = p->esq;
        }else{
            p = p->dir;
        }
    }
    if (p != NULL){
        R= p->dir;
        if(R != NULL){
            p = R;               //minimo do lado direito
            while(p->esq != NULL)
            p = p->esq;
            suc = p;
        }else{                  //ancestral mais proximo e maior
            while((fa != NULL) && (fa->dir == p)){
                p = fa; 
                fa = p->pai;
            }
            if (fa != NULL){
                suc = fa;
            }
        }
    }
    return suc;
}
