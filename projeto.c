// André Miguel da Silva Pinho nº32795
// Miguel Ângelo Resende Cardoso nº32936

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

//constantes simbólicas
#define MAX 100

//tipos e estruturas

typedef struct{
	int ano,mes,dia,hora,min;
}Datah;

typedef struct{
	char nome[100], local[200], descricao[2000];
	Datah data;
	int cat,tipo;
}Tarefa;

typedef struct
{									//Informações para contactos
	char nome[100], morada[400], email[200]; 
	int ntel, cat;
}Contacto;

FILE *fp; //útil ao longo do programa
FILE *gp;

Tarefa *ler_Ficheiro(Tarefa *tar,int *x){
		int i=0;
		gp=fopen("tarefas.dat","rb");
		if(gp==NULL){
			gp=fopen("tarefas.dat","wb");
			if(gp==NULL){
				printf("Erro na abertura do ficheiro.\n");
				exit(1);
			}
			tar=(Tarefa *)malloc(sizeof(Tarefa));
			if(tar==NULL){
				printf("Erro na alocação da memória.\n");
				exit(1);
			}
			*x=i;
		}
		else{
			tar=(Tarefa *)malloc(sizeof(Tarefa));
			if(tar==NULL){
				printf("Erro na alocação da memória.\n");
				exit(1);
			}
			while(!feof(gp)){
			//Leitura dos dados dos registros do arquivo para o vetor
			fread(&tar[i], sizeof(Tarefa), 1, gp);
			i++;
		   	//Alocammos o vetor de estruturas de forma
   			//dinamica conforme a capacidade.
   	 		tar=(Tarefa *)realloc(tar,(i+1)*sizeof(Tarefa));
   	 		if(tar==NULL){
   	 			printf("Erro na alocação da memória.\n");
   	 			exit(1);
   	 		}
			}
			*x=i-1;
		}
		fclose(gp);
		return tar;
}

Contacto *lerFicheiro(Contacto *agenda,int *n){
		int i=0;
		FILE *fp;
		fp=fopen("agenda.dat","rb");
		if(fp==NULL){
			printf("Agenda vazia.\n");
			fp=fopen("agenda.dat","wb");
			if(fp==NULL){
				printf("Erro na abertura do ficheiro.\n");
				exit(1);
			}
			agenda=malloc(sizeof(Contacto));
			if(agenda==NULL){
				printf("Erro na alocação da memória.\n");
				exit(1);
			}
			*n=i;
		}
		else{
			agenda=malloc(sizeof(Contacto));
			if(agenda==NULL){
				printf("Erro na alocação da memória.\n");
				exit(1);
			}
			while(!feof(fp)){
			//Leitura dos dados dos registros do arquivo para o vetor
			fread(&agenda[i], sizeof(Contacto), 1, fp);
			i++;
		   	//Alocammos o vetor de estruturas de forma
   			//dinamica conforme a capacidade.
   	 		agenda=(Contacto *)realloc(agenda,(i+1)*sizeof(Contacto));
   	 		if(agenda==NULL){
   	 			printf("Erro na alocação da memória.\n");
   	 			exit(1);
   	 		}
			}
			*n=i-1;
		}
		fclose(fp);
		return agenda;
}

//esta função mostra o menu
//recebe 0 parâmetros
//devolve um valor inteiro que corresponde à opção escolhida
int menu1()
{
	int op;
	do
	{
		printf("1-Contactos\n2-Tarefas\n0-Terminar\n");
		scanf("%d",&op);
		getchar();		//limpa o buffer do teclado
		if(op<0 || op>3)
			printf("O valor introduzido não é válido.\n"); 
	}
	while(op<0 || op>3);
	return op;
}

//esta função mostra o menu dos contactos
//recebe 0 parâmetros
//devolve um valor inteiro que corresponde à opção escolhida
int menu2()
{
	int op;
	do
	{
		printf("1-Acrescentar contacto\n2-Eliminar contacto\n3-Alterar contacto\n4-Pesquisar contacto\n0-Terminar\n");
		scanf("%d",&op);
		getchar();
		if(op<0 || op>4)
			printf("O valor introduzido não é válido.\n");
	}
	while(op<0 || op>4);
	return op;
}

//esta função mostra o menu das tarefas
int menu3(){
	int op;
	do{
		printf("1-Acrescentar tarefa\n2-Eliminar tarefa\n3-Alterar tarefa\n4-Pesquisar tarefa\n5-Estatistica sobre tarefas\n0-Terminar\n");
		scanf("%d",&op);
		getchar();
		if(op<0 || op>5)
			printf("O valor introduzido não é válido.\n");
	}
	while(op<0 || op>5);
	return op;
}

int lerPessoa(Contacto *agenda, int n)
{
	agenda=(Contacto *)realloc(agenda,(n+1)*sizeof(Contacto));
	if(agenda==NULL){
		printf("Erro na alocação da memória.\n");
		exit(1);
	}
	printf("Introduz o nome:");
	fgets(agenda[n].nome,100,stdin);
	printf("Introduza a morada:");
	fgets(agenda[n].morada,400,stdin);
	printf("Inroduza o e-mail:");
	fgets(agenda[n].email,200,stdin);
	printf("Introduza o Nº de Telefone/Telemóvel:");
	scanf("%ld",&agenda[n].ntel);
	printf("Categoria:\n1-Amigos\n2-Familia\n3-Trabalho\n4-Net\n");
	scanf("%d",&agenda[n].cat);
	n++;
	return n;
}

//Apaga um contacto
int Apaga_Contacto(Contacto *agenda, int n)
{
	char nome[100],x;
	int j=0,i=0;
	printf("Introduza o nome do contacto que deseja eliminar: ");
	fgets(nome,100,stdin);
	while(j<n && strcmp(agenda[j].nome,nome)!=0)	j++;
	if(j==n)	printf("Contacto inexistente.\n");
	else{
		if(strcmp(agenda[i].nome,nome)==0)
		{
			for(j=i+1;j<n;j++)
			{
				strcpy(agenda[j-1].nome,agenda[j].nome);
				agenda[j-1].ntel=agenda[j].ntel;
				strcpy(agenda[j-1].email,agenda[j].email);
				strcpy(agenda[j-1].morada,agenda[j].morada);
				agenda[j-1].cat=agenda[j].cat;
			}
			n--;
			i=n;
			printf("Contacto eliminado com sucesso.\n");
		}
	}
	return n;
}

//função para alterar o contacto
void Altera_Contacto(Contacto *agenda, int n)
{
	char nome[200];
	int ntel,i,j,k=0;
	printf("Que contacto deseja alterar.\n");
	fgets(nome,200,stdin);
	for(i=0;i<n;i++)
	{
		if(strcmp(agenda[i].nome,nome)==0)
		{
			do
			{
				printf("O que deseja alterar:\n1-Nome\n2-Morada\n3-E-mail\n4-Nº de telemóvel\n5-Categoria\n0-Voltar ao menu anterior\n");
				scanf("%d",&j);
				getchar();
				if(j<0 || j>4)
					printf("Opção inválida.\n");
			}
			while(j<0 || j>4);
			if (j==1)
			{
				printf("Introduza novo nome.\n");
				fgets(nome,100,stdin);
				strcpy(agenda[i].nome,nome);
			}
			else if (j==2)
			{
				printf("Introduza nova morada.\n");
				fgets(nome,100,stdin);
				strcpy(agenda[i].morada,nome);
			}
			else if (j==3)
			{
				printf("Introduza novo e-mail.\n");
				fgets(nome,100,stdin);
				strcpy(agenda[i].email,nome);
			}
			else if (j==4)
			{
				printf("Introduza novo número de telemóvel.\n");
				scanf("%d",&agenda[i].ntel);
			}
			else if(j==5){
				printf("Diga a nova categoria.\n1-Amigos\n2-Familia\n3-Trabalho\n4-Net\n");
				scanf("%d",&agenda[i].cat);
			}
		}
	}
}

//Pesuisa Contactos
void Pesquisa_Contacto(Contacto *agenda, int n){
	char nome[200];
	int ntel, i,j=0,cat;
	do{
		printf("Como deseja procurar?\n1-Procurar por nome\n2-Procurar por nº telemóvel\n3-Procurar por categoria.\n0-Terminar\n");
		scanf("%d",&i);
		getchar();
		if(i<0 || i>3)
			printf("Opção inválida.\n");
	}while(i<0 || i>3);
	if(i==1){
		printf("Introduza o nome que deseja procurar.\n");
		fgets(nome,200,stdin);
		while(j<n && strcmp(agenda[j].nome,nome)!=0)
			j++;
		if(j==n)	printf("Contacto inexistente\n");
		else{
			printf("*** Contacto %d ***\n",j+1);
        	printf("Nome: %s\n",agenda[j].nome);
        	printf("Morada: %s\n",agenda[j].morada);
        	printf("E-mail: %s\n",agenda[j].email);
	    	printf("Nº Telémovel: %d\n",agenda[j].ntel);
		}
	}
	if(i==2){		//Procura por número de telemóvel
		printf("Introduza o nº de telemóvel que deseja procurar.\n");
		scanf("%d",&ntel);
		while(j<n && agenda[j].ntel!=ntel)
			j++;
		if(j==n)	printf("Contacto inexistente.\n");
		else{
			printf("*** Contacto %d ***\n",j+1);
    		printf("Nome: %s\n",agenda[j].nome);
        	printf("Morada: %s\n",agenda[j].morada);
        	printf("E-mail: %s\n",agenda[j].email);
	    	printf("Nº Telémovel: %d\n",agenda[j].ntel);
		}
	}
	if(i==3){
		printf("Categorias.\n1-Amigos\n2-Familia\n3-Trabalho\n4-Net\n0-Terminar\n");
		scanf("%d",&cat);
		while(j<n){
			if(agenda[j].cat==cat){
				printf("*** Contato %d ***\n",j+1);
        		printf("Nome: %s\n",agenda[j].nome);
        		printf("Morada: %s\n",agenda[j].morada);
        		printf("E-mail: %s\n",agenda[j].email);
	    		printf("Telefone: %d\n",agenda[j].ntel);
			}	
			j++;
		}
	}
}

//função para organizar por ordem alfabética os contactos
Contacto *BubbleSort(Contacto *agenda, int n){
	int troca=1,i;
	Contacto aux;
	while(troca==1){
		troca=0;
		for(i=0;i<n-1;i++)
			if(strcmp(agenda[i].nome,agenda[i+1].nome)>0){
				aux=agenda[i];
				agenda[i]=agenda[i+1];
				agenda[i+1]=aux;
				troca=1;
			}
	}
	return agenda;
}

Contacto *BubbleSort1(Contacto *agenda, int n){
	int troca=1,i;
	Contacto aux;
	while(troca==1){
		troca=0;
		for(i=0;i<n-1;i++)
			if(agenda[i].cat>agenda[i+1].cat){
				aux=agenda[i];
				agenda[i]=agenda[i+1];
				agenda[i+1]=aux;
				troca=1;
			}
	}
	return agenda;
}

void Escreve_ficheiro(Contacto *agenda, int n){
	fp=fopen("agenda.dat","wb");
	if(fp==NULL){
		printf("Erro na abertura do ficheiro.\n");
		exit(1);
	}
   	//Grava os dados do vetor no arquivo.
   	fwrite(agenda, sizeof(Contacto), n, fp);
    //Fecha arquivo apos a gravacao.
    fclose(fp);
}

int adicionarTarefa(Tarefa *tar,int x){
		//Capacidade esgotada, devemos aumentar o 
		//vetor usando "realloc" (ex: dobrar capacidade).
    tar = realloc(tar, (x+1)*sizeof(Tarefa));
    if(tar==NULL){
       	printf("Erro na alocação da memória.\n");
       	exit(1);
 	}
	printf("Introduz o titulo:");
	fgets(tar[x].nome,100,stdin);
	printf("Introduza o local:");
	fgets(tar[x].local,200,stdin);
	printf("Inroduza a descrição da tarefa:");
	fgets(tar[x].descricao,2000,stdin);
	printf("Introduza a data em que a tarefa se vai realizar no formato: aaaa/mm/dd:");
	scanf("%d%d%d",&tar[x].data.ano,&tar[x].data.mes,&tar[x].data.dia);
	printf("Introduza a hora que se vai realizar(formato hh:mm):\n");
	scanf("%d%d",&tar[x].data.hora,&tar[x].data.min);
	printf("Categorias:\n1-Trabalho\n2-Lazer\n3-Casa\n4-Desporto\n");
	scanf("%d",&tar[x].cat);
	tar[x].tipo=1;
	x++;
	return x;
}

//Apaga um contacto
int Apaga_Tarefa(Tarefa *tar, int x)
{
	char nome[100],n;
	int j=0,i;
	printf("Introduza o nome da tarefa que deseja eliminar: ");
	fgets(nome,100,stdin);
	while(j<x && strcmp(tar[j].nome,nome)!=0)	j++;
	if(j==x)	printf("Tarefa inexistente.\n");
	else{
		for(j=i+1;j<n;j++)
			{
				strcpy(tar[j-1].nome,tar[j].nome);
				tar[j-1].data=tar[j].data;
				strcpy(tar[j-1].local,tar[j].local);
				strcpy(tar[j-1].descricao,tar[j].descricao);
				tar[j-1].cat=tar[j].cat;
			}
			x--;
			i=x;
			printf("Tarefa eliminada com sucesso.\n");
	}	
	return x;
}

void Altera_Tarefa(Tarefa *tar, int x)
{
	char nome[2000];
	int i,j=0;
	printf("Que tarefa deseja alterar.\n");
	fgets(nome,200,stdin);
	while(j<x && strcmp(tar[j].nome,nome)!=0)	j++;
	if(j==x)	printf("Tarefa inexistente");
	else{
		if(strcmp(tar[j].nome,nome)==0)
		{
			do
			{
				printf("O que deseja alterar:\n1-Titulo\n2-Local\n3-Descrição\n4-Data\n5-Categoria\n6-Estado\n0-Voltar ao menu anterior\n");
				scanf("%d",&j);
				getchar();
				if(j<0 || j>6)
					printf("Opção inválida.\n");
			}
			while(j<0 || j>6);
			if (j==1)
			{
				printf("Introduza novo título.\n");
				fgets(nome,2000,stdin);
				strcpy(tar[i].nome,nome);
			}
			else if (j==2)
			{
				printf("Introduza novo local.\n");
				fgets(nome,2000,stdin);
				strcpy(tar[i].local,nome);
			}
			else if (j==3)
			{
				printf("Introduza nova descrição.\n");
				fgets(nome,2000,stdin);
				strcpy(tar[i].descricao,nome);
			}
			else if (j==4)
			{
				printf("Introduza nova data(formato aaaa/mm/dd -- hh:mm).\n");
				scanf("%d",&tar[i].data.ano);
				scanf("%d",&tar[i].data.mes);
				scanf("%d",&tar[i].data.dia);
				scanf("%d",&tar[i].data.hora);
				scanf("%d",&tar[i].data.min);
			}
			else if(j==5){
				printf("Categorias:\n1-Trabalho\n2-Lazer\n3-Casa\n4-Desporto\n0-Terminar");
				do{
					scanf("%d",&tar[i].cat);
					if(tar[i].cat<0 || tar[i].cat>4)	printf("Erro. Tem de seleccionar uma opção válida.\n");
				}while(tar[i].cat<0 || tar[i].cat>4);
			}
			else if(j==6){
				printf("Estado:\n1-Agendada\n2-Concluida\n3-A decorrer\n4-Adiada\n");
				do{
					scanf("%d",&tar[i].tipo);
					if(tar[i].tipo<0 || tar[i].cat>4)	printf("Erro. Tem de seleccionar uma opção válida.\n");
				}while(tar[i].tipo<0 || tar[i].cat>4);
			}
		}
	}
}

void Pesquisa_Tarefa(Tarefa *tar, int x){
	char nome[200];
	int i,j=0,n=0,cat,est,op;
	time_t timer;
  	struct tm *timeinfo;
	Datah data;
	do{
		printf("Como deseja procurar?\n1-Procurar por titulo\n2-Procurar por data\n3-Procurar por categoria\n4-Procurar por estado\n0-Terminar\n");
		scanf("%d",&i);
		getchar();
		if(i<0 || i>4)
			printf("Opção inválida.\n");
	}while(i<0 || i>4);
	if(i==1){
		printf("Introduza o titulo da tarefa que deseja procurar.\n");
		fgets(nome,200,stdin);
		while(j<x && strcmp(tar[j].nome,nome)!=0)
			j++;
		if(j==x)	printf("Tarefa inexistente.\n");
		else{
			printf("*** Tarefa %d ***\n",j+1);
        	printf("Titulo: %s\n",tar[j].nome);
			printf("Local: %s\n",tar[j].local);
        	printf("Descrição: %s\n",tar[j].descricao);
	    	printf("Data: %d/%d/%d ------- %d:%dh\n",tar[j].data.ano,tar[j].data.mes,tar[j].data.dia,tar[j].data.hora,tar[j].data.min);
	    	if(tar[j].cat==1)	printf("Trabalho\n");
	    	else if(tar[j].cat==2)	printf("Lazer\n");
	    	else if(tar[j].cat==3)	printf("Casa\n");
	    	else if(tar[j].cat==4)	printf("Desporto\n");
	    	if(tar[j].tipo==1)	printf("Tarefa agendada.\n");
	    	else if(tar[j].tipo==2)	printf("Tarefa concluida.\n");
	    	else if(tar[i].tipo==3)	printf("Tarefa a decorrer.\n");
	    	else	printf("Tarefa adiada.\n");
		}
	}
	if(i==2){
		printf("Deseja procurar por:\n1-Ano\n2-Mes\n3-Data completa\n");
		scanf("%d",&op);
		if(op==1){
			printf("Introduz o ano.\n");
			scanf("%d",&data.ano);
			while(n<x){
				if(tar[n].data.ano==data.ano){
					printf("%s\n",tar[n].nome);
      				printf("%s\n",tar[n].local);
      				printf("%s\n",tar[n].descricao);
      				printf("%d/%d/%d ----- %d:%d\n",tar[n].data.ano,tar[n].data.mes,tar[n].data.dia,tar[n].data.hora,tar[n].data.min);
      				if(tar[n].tipo==1)	printf("Tarefa agendada.\n");
      				else if(tar[n].tipo==2)	printf("Tarefa concluida.\n");
      				else if(tar[n].tipo==3)	printf("Tarefa a decorrer.\n");
      				else	printf("Tarefa adiada.\n");
				}
				n++;
			}
		}
		else if(op==2){
			printf("Introduz o mes.\n");
			scanf("%d",&data.mes);
			while(x<n){
			if(tar[n].data.mes==data.mes){
				printf("%s\n",tar[n].nome);
    			printf("%s\n",tar[n].local);
      			printf("%s\n",tar[n].descricao);
      			printf("%d/%d/%d ----- %d:%d\n",tar[n].data.ano,tar[n].data.mes,tar[n].data.dia,tar[n].data.hora,tar[n].data.min);
      			if(tar[n].tipo==1)	printf("Tarefa agendada.\n");
      			else if(tar[n].tipo==2)	printf("Tarefa concluida.\n");
      			else if(tar[n].tipo==3)	printf("Tarefa a decorrer.\n");
      			else	printf("Tarefa adiada.\n");
      		}
      		n++;
      		}
      	}
      	else if(op==3){
      		printf("Introduz a data(formato:aaaa/mm/dd).\n");
			scanf("%d%d%d",&data.ano,&data.mes,&data.dia);
			while(n<x){
				if(tar[n].data.ano==data.ano){
					if(tar[n].data.mes==data.mes){
						if(tar[n].data.dia==data.dia){
							printf("%s\n",tar[n].nome);
      						printf("%s\n",tar[n].local);
      						printf("%s\n",tar[n].descricao);
      						printf("%d/%d/%d ----- %d:%d\n",tar[n].data.ano,tar[n].data.mes,tar[n].data.dia,tar[n].data.hora,tar[n].data.min);
      						if(tar[n].tipo==1)	printf("Tarefa agendada.\n");
      						else if(tar[n].tipo==2)	printf("Tarefa concluida.\n");
      						else if(tar[n].tipo==3)	printf("Tarefa a decorrer.\n");
      						else	printf("Tarefa adiada.\n");
						}
					}	
				}	
				n++;
			}
		}
	}
	if(i==3){
		printf("Categorias:\n1-Trabalho\n2-Lazer\n3-Casa\n4-Desporto\n");
		scanf("%d",&cat);
		while(n<x){
			if(tar[n].cat==cat){	
      			printf("%s\n",tar[n].nome);
      			printf("%s\n",tar[n].local);
      			printf("%s\n",tar[n].descricao);
      			printf("%d/%d/%d ----- %d:%d\n",tar[n].data.ano,tar[n].data.mes,tar[n].data.dia,tar[n].data.hora,tar[n].data.min);
      			if(tar[n].tipo==1)	printf("Tarefa agendada.\n");
      			else if(tar[n].tipo==2)	printf("Tarefa concluida.\n");
      			else if(tar[n].tipo==3)	printf("Tarefa a decorrer.\n");
      			else	printf("Tarefa adiada\n");
			}
		n++;
		}
	}
	if(i==4){
		printf("Estado:\n1-Concluida\n2-Agendada\n3-A decorer\n4-Adiada\n");
		scanf("%d",&est);
		printf("Quer pesquisar até quando?(Introduza uma data no formato aaaa/mm/dd)\n");
		scanf("%d%d%d",&data.ano,&data.mes,&data.dia);
		time (&timer);
  		timeinfo= localtime(&timer);
  		while(n<x){
			while((timeinfo->tm_year)>=(tar[n].data.ano-1900) && tar[n].data.ano<=data.ano){
				while((timeinfo->tm_mon)>=(tar[n].data.mes-1) && tar[n].data.mes<=data.mes){
					while(timeinfo->tm_mday>=tar[n].data.dia && tar[n].data.dia<=data.dia){
						while(timeinfo->tm_hour>=tar[n].data.ano && tar[n].data.ano<=data.ano){
							while(timeinfo->tm_min>=tar[n].data.ano && tar[n].data.ano<=data.ano){
								printf("%s\n",tar[n].nome);
      							printf("%s\n",tar[n].local);
      							printf("%s\n",tar[n].descricao);
      							printf("%d/%d/%d ----- %d:%d\n",tar[n].data.ano,tar[n].data.mes,tar[n].data.dia,tar[n].data.hora,tar[n].data.min);
      							if(tar[n].tipo==1)	printf("Tarefa agendada.\n");
      							else if(tar[n].tipo==2)	printf("Tarefa concluida.\n");
      							else if(tar[n].tipo==3)	printf("Tarefa a decorrer.\n");
      							else	printf("Tarefa adiada\n");
							}
						}
					}
				}
			}
			n++;
		}
	}
}

Tarefa *BubbleSort2(Tarefa *tar,int x){
	int troca=1,i;
	Tarefa aux;
	while(troca==1){
		troca=0;
		for(i=0;i<x-1;i++)
			if(tar[i].data.ano<tar[i+1].data.ano){
				if(tar[i].data.mes<tar[i+1].data.mes){
					if(tar[i].data.dia<tar[i+1].data.dia){
						if(tar[i].data.hora<tar[i+1].data.hora){
							if(tar[i].data.min<tar[i+1].data.min){
								aux=tar[i];
								tar[i]=tar[i+1];
								tar[i+1]=aux;
								troca=1;
							}
						}
					}
				}
			}
	}
	return tar;
}

Tarefa *BubbleSort3(Tarefa *tar,int x){
	int troca=1,i;
	Tarefa aux;
	while(troca==1){
		troca=0;
		for(i=0;i<x-1;i++)
			if(tar[i].tipo>tar[i+1].tipo){
				aux=tar[i];
				tar[i]=tar[i+1];
				tar[i+1]=aux;
				troca=1;
			}
	}
	return tar;
}

Tarefa *BubbleSort4(Tarefa *tar,int x){
	int troca=1,i;
	Tarefa aux;
	while(troca==1){
		troca=0;
		for(i=0;i<x-1;i++)
			if(tar[i].cat>tar[i+1].cat){
				aux=tar[i];
				tar[i]=tar[i+1];
				tar[i+1]=aux;
				troca=1;
			}
	}
	return tar;
}

void Escreveficheiro(Tarefa *tar, int x){
	gp=fopen("tarefas.dat","wb");
	if(gp==NULL){
		printf("Erro na abertura do ficheiro.\n");
		exit(1);
	}
   	//Grava os dados do vetor no arquivo.
   	fwrite(tar, sizeof(Tarefa), x, gp);
    //Fecha arquivo apos a gravacao.
    fclose(gp);
}

void estatistica(Tarefa *tar,int x){
	
	int i,soma=0,soma1=0,soma2=0,soma3=0;
	for(i=0;i<x;i++){
		if(tar[i].tipo==1)
			soma++;
		else if(tar[i].tipo==2)
			soma1++;
		else if(tar[i].tipo==3)
			soma2++;
		else if(tar[i].tipo==4)
			soma3++;
	}
	printf("As tarefas agendadas são %d\n",soma);
	printf("As tarefas concluidas são %d\n",soma1);
	printf("As tarefas a decorrer são %d\n",soma2);
	printf("As tarefas adiadas são %d\n",soma3);
}

void showContactos(Contacto *agenda, int *tam){
	if(*tam<0)	printf("Lista de Contactos vazia\n");
	for(int i=0;i<*tam;i++){
		printf("");
	}
}

int main(int argc, char *argv[])
{
	Contacto *agenda;
	Tarefa *tar;
	int n,i=0, op, op1, op2, op3, x,y,w;
	char ch;
	system(CLEAR);
	printf("-----------------BEM-VINDO-----------------\nPrime enter para continuar...");
	getchar();
	system(CLEAR);
	//chamada dos menus
	do{
		op1=menu1();
		switch(op1){
			case 1:agenda=lerFicheiro(agenda,&n);
			system(CLEAR);
			if(n<=0)	printf("Agenda vazia\n");
			else{
				printf("Ordenar por:\n 1-Categoria\n2-Ordem Alfabética\n");
				scanf("%d",int c);
				do{
				if(c==1){
					int j=0;
					for(int i=0;i<n;i++){
					int x=agenda[i].cat;
					if(x!=j){
						j=x;
						if(agenda[i].cat==1)	printf("--------Amigos--------");
						else	if(agenda[i].cat==2)	printf("--------Familia-------");
						else	if(agenda[i].cat==3)	printf("--------Trabalho------");
						else	if(agenda[i].cat==4)	printf("--------Net-----------");
					}
					for(int i=0;i<n;i++){
						if(agenda[i].cat==1)	printf("Nome: %s\nMorada: %s\nEmail: %s\nNº telemovel: %d\n, Categoria: Amigos\n",agenda[i].nome,agenda[i].morada,agenda[i].email,agenda[i].ntel);
						else if(agenda[i].cat==2)	printf("Nome: %s\nMorada: %s\nEmail: %s\nNº telemovel: %d\n, Categoria: Familia\n",agenda[i].nome,agenda[i].morada,agenda[i].email,agenda[i].ntel);
						else if(agenda[i].cat==3)	printf("Nome: %s\nMorada: %s\nEmail: %s\nNº telemovel: %d\n, Categoria: Trabalho\n",agenda[i].nome,agenda[i].morada,agenda[i].email,agenda[i].ntel);
						else	printf("Nome: %s\nMorada: %s\nEmail: %s\nNº telemovel: %d\n, Categoria: Net\n",agenda[i].nome,agenda[i].morada,agenda[i].email,agenda[i].ntel);
						}
					}
				}
				if(c==2){
					for(int i=0;i<n;i++){
				if(agenda[i].cat==1)	printf("Nome: %s\nMorada: %s\nEmail: %s\nNº telemovel: %d\n, Categoria: Amigos\n",agenda[i].nome,agenda[i].morada,agenda[i].email,agenda[i].ntel);
				else if(agenda[i].cat==2)	printf("Nome: %s\nMorada: %s\nEmail: %s\nNº telemovel: %d\n, Categoria: Familia\n",agenda[i].nome,agenda[i].morada,agenda[i].email,agenda[i].ntel);
				else if(agenda[i].cat==3)	printf("Nome: %s\nMorada: %s\nEmail: %s\nNº telemovel: %d\n, Categoria: Trabalho\n",agenda[i].nome,agenda[i].morada,agenda[i].email,agenda[i].ntel);
				else	printf("Nome: %s\nMorada: %s\nEmail: %s\nNº telemovel: %d\n, Categoria: Net\n",agenda[i].nome,agenda[i].morada,agenda[i].email,agenda[i].ntel);
				}
				}
				else	printf("Opção não existe\n");
				}while(op!=1 || op!=2);
				getchar();
			}
					do
					{
						system(CLEAR);
						op2=menu2();
						switch(op2)
						{
							case 1:n=lerPessoa(agenda,n);
							printf("Deseja ordenar por:\n1-Categoria\n2-Ordem Alfabetica\n");
							scanf("%d",&op);
							if(op==1){	agenda=BubbleSort(agenda,n);agenda=BubbleSort1(agenda,n);}
							else if(op==2)	agenda=BubbleSort(agenda,n);break;
							case 2:n=Apaga_Contacto(agenda,n);break;
							case 3:Altera_Contacto(agenda,n);break;
							case 4:Pesquisa_Contacto(agenda,n);break;
						};
					}
					while(op2!=0);
					if(op==1)	agenda=BubbleSort1(agenda,n);
					else if(op==2)	agenda=BubbleSort(agenda,n);
					Escreve_ficheiro(agenda,n);
					//Liberta a memória alocada no vetor
					free(agenda);break;
			case 2:tar=ler_Ficheiro(tar,&x);
					do{
						op3=menu3();
						switch(op3){
							case 1: x=adicionarTarefa(tar,x);
							printf("Deseja ordenar por:\n1-Data\n2-Estado\n3-Categoria\n");
							scanf("%d",&op);
							if(op==1)	tar=BubbleSort2(tar,x);
							else if(op==2)	tar=BubbleSort3(tar,x);
							else if(op==3)	tar=BubbleSort4(tar,x);break;
							case 2: x=Apaga_Tarefa(tar,x);break;
							case 3: Altera_Tarefa(tar,x);break;
							case 4: Pesquisa_Tarefa(tar,x);break;
							case 5: estatistica(tar,x);break;
						}
					}
					while(op3!=0);
					if(op==1)	tar=BubbleSort2(tar,x);
					else if(op==2)	tar=BubbleSort3(tar,x);
					else if(op==3)	tar=BubbleSort4(tar,x);
					Escreveficheiro(tar,x);
					//Liberta a memória alocada no vetor
					free(tar);break;
		}
	}while(op1!=0);
	return 0;
}
