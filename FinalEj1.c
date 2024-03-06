typedef struct nodo{
	int dato;
	struct nodo *sig;
}NODO;

typedef NODO *TLISTAC;

void cargalista(TLISTAC *pult);
void deleteordouble(TLISTAC *pult);

int main(){
	TLISTAC pult;
	cargalista(&pult);
	deleteordouble(&pult);

	return 0;
}

void cargalitsa(TLISTAC *pult){
	;
}

void deleteordouble(TLISTAC *pult){
	int cc=0;
	TLISTAC ant, aux=(*pult);
	if( aux != NULL ){
		do{
			ant=aux; aux=aux->sig;
			if (aux->dato%2==0){
				if(aux->dato%7==0){
					if(aux->sig==aux){ //Unico elemento
						*pult=NULL;
					}
					else if(aux==*pult){ //Ultimo elemento
						ant->sig=aux->sig;
						*pult=ant;
					}
					else{ //Primero o medio
						ant->sig=aux->sig;
					}
					free(aux);
				}
				else{
					aux->dato*=2;
				}
			}
		}while( aux!=*pult);
		aux=(*pult);
		if(aux!=NULL){
			do{
				ant=aux; aux=aux->sig;
				if(aux->dato%7==0)
					cc++;
			}while(aux!=*pult);
			printf("La cantidad de multiplos de 7 que quedaron en la lista es: %d\n", cc);
		}
		printf("La lista fue vaciada.");
	}
	else{
		printf("La lista esta vacia.");
	}
}