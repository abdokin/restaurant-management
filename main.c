#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// the product struct 
const int MAX =100;
struct product
{
    int code;
    char name[MAX];
    float prix;
    int q;
    struct product * next;
    struct product * prev;

};
typedef struct product * panier;
// function :
void add_info(panier q){
         printf("ajouter le code de cette product:");
        scanf("%d",&q->code);
        printf("name :");
        scanf("%s",q->name);
        printf("prix :");
        scanf("%f",&q->prix);
        printf("quantite :");
        scanf("%d",&q->q);
}
panier ajouter_panier(panier p){
    panier q = (panier)malloc(sizeof(panier));
    // adding the data of one product:
    add_info(q);
    if(p == NULL){
        q->next = p;
        q->prev = q;
        return q;
    }
    q->next = p;
    p->prev = q;
    q->prev = q;
    return q;
}
// function helper for collecting info for the product
panier copy_info(panier p,panier q){
        panier tmp =(panier) malloc(sizeof(panier));
        strcpy(tmp->name ,p->name);
        printf(" tmp->name %s\n",tmp->name);
        tmp->code = p->code;
        tmp->prix = p->prix;
        tmp->q = p->q;
        tmp->next = q;
        return tmp; 

}
panier fusionner_panier(panier p1,panier p2){
    do
    {
        printf("its runs\n");
        p1= copy_info(p2,p1);
        p2=p2->next;
    }
    while (p2 !=NULL);
    return p1;
}

void trier_panier(panier p1){
    int per=0;panier tmp;panier p = p1;
    while (per != 0)
    {
        per =1;
          while (p->next !=NULL)
     {
         printf("im here ");
         if(p->code > p->next->code){
            //  swap p and p->next 
            // tmp = p->next to save value of p->next
            // and p->next = p 
            // and p = tmp
            tmp =p->next;
            p->next = p;
            p=tmp;
            per = 0;
         }
         p = p->next;
     }
    }
  

}

/* function to swap data of two nodes a and b*/
void swap(panier a, panier b)
{
	int temp_code = a->code;
    int q = a->q;
	char tmp_name[MAX];
    strcpy(tmp_name,a->name);
    float tmp_prix =a->prix;
	a->code = b->code;
    a->q = b->q;
    a->prix = b->prix;
    strcpy(a->name,b->name);
	b->code = temp_code;
	b->prix = tmp_prix;
	b->q = q;
    strcpy(b->name,tmp_name);
}
panier bubbleSort(panier start)
{
	int swapped, i;
	panier ptr1;
	panier lptr = NULL;

	/* Checking for empty list */
	if (start == NULL)
		return NULL;

	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != lptr)
		{
			if (ptr1->code > ptr1->next->code)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
	while (swapped);
    return start;
}
void print_list(panier p1){
     panier w = p1;
    while (w != NULL)
    {
        printf("  %d ->",w->code);
        w = w->next;
    }
    printf("\n");
}

// calculler prix
float prix_total(panier p1 ){
    panier p=p1;
    float prix=0;
    while (p != NULL)
    {
        prix = p->prix * p->q +prix;
        p =p->next;
    }
    return prix;
}
// afficher panier 
void afficher_panier(panier p1){
    panier p = p1;
    while (p != NULL)
    {
        printf("CODE: %d   NOME :%s   quantite : %d   prix unitaire: %f \n", p->code,p->name,p->q, p->prix);
        p = p->next;
    }
    float prix_t =prix_total(p1);
    printf(" le prix total est : %f\n", prix_t);
    free(p);
    
}
void afficher_panier_file(panier p1, FILE *ptr){
    panier p = p1;
    while (p != NULL)
    {
        fprintf(ptr,"CODE: %d   NOME :%s   quantite : %d   prix unitaire: %f \n", p->code,p->name,p->q, p->prix);
        p = p->next;
    }
    fprintf(ptr," le prix total est : %f", prix_total(p));
    free(p);
    
}

// search for product

panier rechercher_produit(panier p1, int code){
        panier p = p1;
        while (p != NULL)
        {
            if(p->code == code ) {
                return p;
            }
            p = p->next;
        }
        return NULL;       
}

void suppremier_produit(panier* head_ref, panier del)
{
    /* base case */
    if (*head_ref == NULL || del == NULL)
        return;
 
    /* If node to be deleted is head node */
    if (*head_ref == del)
        *head_ref = del->next;
 
    /* Change next only if node to be
    deleted is NOT the last node */
    if (del->next != NULL)
        del->next->prev = del->prev;
 
    /* Change prev only if node to be
    deleted is NOT the first node */
    if (del->prev != NULL)
        del->prev->next = del->next;
 
    /* Finally, free the memory occupied by del*/
    free(del);
    return;
}
void enregister_panier(panier p1){
    FILE *fptr;
    char name[MAX];
    printf("enter name of the file :");
    scanf("%s",name);
    fptr = fopen(name,"w");
    afficher_panier_file(p1,fptr);
    fclose(fptr);
    
}
panier plus_cher(panier p1){
    panier p=p1,cher=malloc(sizeof(panier));cher->prix =0;
    while (p != NULL)
    {   
        if(cher->prix < p->prix){
            cher = p;
        }
        p = p->next;
    }
    return cher;
}

int menu(){
    int choix;
    printf("Remplir le premier panier           taper 1\n");
    printf("Remplir le deuxierme panier         taper 2\n");
    printf("Fusionner le deux paniers           taper 3\n");
    printf("Trier le Panier                     taper 4\n");
    printf("Chercher le produit le plus cher    taper 5\n");
    printf("Supprimer le produit le plus cher   taper 6\n");
    printf("Afficher le panier                  taper 7\n");
    printf("Enregister le panier                taper 8\n");
    printf("Quitter                             taper 0\n");
    scanf("%d",&choix);
    return choix;
}
int main(){
    panier p1=NULL,p2=NULL;
    panier cher;
    int choix = menu();
    while (choix != 0)
    {
        switch (choix)
        {
        case 1:
            p1 = ajouter_panier(p1);
            break;
        case 2:
            p2 = ajouter_panier(p2);
            break;
        case 3:
            p1 = fusionner_panier(p1,p2);
            printf("done\n");
            break;
        case 4:
            p1 = bubbleSort(p1);
            printf("done\n");
            break;
        case 5:
            cher = plus_cher(p1);
            printf("cher name : %s\n",cher->name);
            printf("cher prix : %f\n",cher->prix);
            break;
        case 6:
            suppremier_produit(&p1,cher);
            printf("done delete product with name %s\n",cher->name);
            break;
        case 7:
            afficher_panier(p1);
            break;
        case 8:
            enregister_panier(p1);
            break;
        default:
            break;
        }
        choix = menu();
    }
    
    return 0;
}