#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct director{
    char *name;
    struct director *parent, *left, *right, *directories;
    struct fisier *files;
}Tdirector;

typedef struct fisier{
    char *name;
    struct director *parent;
    struct fisier *left, *right;
}Tfisier;

Tdirector *ConstrDFr(char *x){
Tdirector *aux = malloc (sizeof(Tdirector));
	if (!aux) return NULL;
    aux->name = malloc(strlen(x));
	memcpy(aux->name, x, strlen(x)); 
    aux->left = aux->right = NULL;
	return aux;
}
int InserareD_ABC(Tdirector **a, char *x, Tdirector *curent){
	Tdirector *aux, *p, *n;
	if(*a == NULL){	
		*a = ConstrDFr(x);
        (*a)->parent = curent;
		if(!*a) return 0;
		return 1;
	}
	n = *a;
	while(n){
		p = n;
		if(strcmp(x, n->name) == 0) 
			return 2;
		if(strcmp(x, n->name) < 0)
			n = n->left;
		else	
			n = n->right;
	}
	aux = ConstrDFr(x);
	if(!aux) return 0;
    aux->parent = curent;

	if(strcmp(x, p->name) < 0)
		p->left = aux;
	else	
		p->right = aux;
	return 1;
}

Tfisier *ConstrFFr(char *x){
Tfisier *aux = malloc (sizeof(Tfisier));
	if (!aux) return NULL;
    aux->name = malloc(strlen(x));
	memcpy(aux->name, x, strlen(x)); 
    aux->left = aux->right = NULL;
	return aux;
}
int InserareF_ABC(Tfisier **a, char *x,Tdirector *curent){
	Tfisier *aux, *p, *n;
	if(*a == NULL){	
		*a = ConstrFFr(x);
		if(!*a) return 0;
		return 1;
	}
	n = *a;
	while(n){
		p = n;
		if(strcmp(x, n->name) == 0) 
			return 2;
		if(strcmp(x, n->name) < 0)
			n = n->left;
		else	
			n = n->right;
	}
	aux = ConstrFFr(x);
	if(!aux) return 0;
    aux->parent = curent;

	if(strcmp(x, p->name) < 0)
		p->left = aux;
	else	
		p->right = aux;
	return 1;
}

int verificare(Tdirector *curent, char *nfile){
    if(curent == NULL){
        return 0;
    }
    Tdirector *directories = curent->directories;
    Tfisier *files = curent->files;
    int a = 0, b = 0;
    while(directories && a == 0){
        if(strcmp(nfile, directories->name) == 0) a = 1;
        if(strcmp(nfile, directories->name) < 0)directories = directories->left;
        else
        directories = directories->right;
    }
    if(a == 1) return 1;

    while(files && b == 0){
        if(strcmp(nfile, files->name) == 0) b = 1;
        if(strcmp(nfile, files->name) < 0)files = files->left;
        else
        files = files->right;
    }
    if(b == 1) return 2;
    return 0;
}

void touch(char *nfile, Tdirector **curent){
    if(verificare(*curent, nfile) == 1)
    printf("Directory %s already exists!\n", nfile);
    else{
        if(verificare(*curent, nfile) == 2)
        printf("File %s already exists!\n", nfile);
        else{
            InserareF_ABC(&((*curent)->files), nfile, *curent);
        }
    }
}

void mkdir(char *nfile, Tdirector **curent){
    if(verificare(*curent, nfile) == 1)
    printf("Directory %s already exists!\n", nfile);
    else{
        if(verificare(*curent, nfile) == 2)
        printf("File %s already exists!\n", nfile);
        else{
            InserareD_ABC(&((*curent)->directories), nfile, *curent);
        }
    }
}

Tfisier *valoareminima(Tfisier *curent){
    Tfisier *nou = curent;

    while(nou && nou->left != NULL)
    nou = nou->left;

    return nou;
}
Tfisier *rm(char *nfile, Tfisier *curent){
    if(curent == NULL) return NULL; 

    if(strcmp(nfile, curent->name) < 0)
    curent->left = rm(nfile, curent->left);
    else if(strcmp(nfile, curent->name) > 0)
    curent->right = rm(nfile, curent->right);

    else{
        if(curent->left == NULL){
            Tfisier *ceva = curent->right;
            free(curent);
            return ceva;
        }
        else if(curent->right == NULL){
            Tfisier *ceva = curent->left;
            free(curent);
            return ceva;
        }
        Tfisier *ceva = valoareminima(curent->right);
        curent->name = ceva->name;

        curent->right = rm(ceva->name, curent->right);
    }
    return curent;
}
Tdirector *valoareminimaD(Tdirector *curent){
    Tdirector *nou = curent;

    while(nou && nou->left != NULL)
    nou = nou->left;

    return nou;
}

Tdirector *rmdir(char *nfile, Tdirector *curent){
    if(curent == NULL) return NULL; 

    if(strcmp(nfile, curent->name) < 0)
    curent->left = rmdir(nfile, curent->left);
    else if(strcmp(nfile, curent->name) > 0)
    curent->right = rmdir(nfile, curent->right);
    else{
        if(curent->left == NULL){
            Tdirector *ceva = curent->right;
            free(curent);
            return ceva;
        }
        else if(curent->right == NULL){
            Tdirector *ceva = curent->left;
            free(curent);
            return ceva;
        }
        Tdirector *ceva = valoareminimaD(curent->right);
        curent->name = ceva->name;

        curent->right = rmdir(ceva->name, curent->right);
    }
    return curent;
}

Tdirector *cd(Tdirector *curent, char *nfile){ 
    if(strcmp(curent->name, nfile) == 0) return curent;
    if(strcmp(curent->name, nfile) > 0) 
    return cd(curent->left, nfile);
    return cd(curent->right, nfile);
}

void SRD_F(Tfisier *a){
    if(a != NULL){
        if(a->left != NULL) SRD_F(a->left);
        printf("%s ", a->name);
        if(a->right != NULL) SRD_F(a->right);
    }
}

void SRD_D(Tdirector *a){
    if(a != NULL){
        if(a->left != NULL) SRD_D(a->left);
        printf("%s ", a->name);
        if(a->right != NULL) SRD_D(a->right);
    }
}

void ls(Tdirector *curent){
    SRD_D(curent->directories); 
    SRD_F(curent->files);
    printf("\n");
}

int main()
{
    Tdirector *root = malloc(sizeof(Tdirector));
    if(!root){
        free(root);
        return 0;
    }
    root->name = malloc(sizeof(char) * 50);
    if(!root->name){
        free(root->name);
        free(root);
        return 0;
    }

    memcpy(root->name, "root", 5);
    root->parent = NULL;
    root->directories = NULL;
    root->files = NULL;
    root->left = NULL;
    root->right = NULL;

    Tdirector *curent = root;
    char *token;
    bool comanda = true;
    char *input = malloc(256 * sizeof(char));

    while(comanda){
        fgets(input,255,stdin);
        token = strtok(input, " \n");

        if(!strcmp(token,"touch")){
            token = strtok(NULL, " \n");
            touch(token, &curent);
        }
        else
        if(!strcmp(token,"mkdir")){
            token = strtok(NULL, " \n");
            mkdir(token, &curent);
        }
        else
        if(!strcmp(token,"ls")){
            ls(curent);
        }
        else
        if(!strcmp(token,"rm")){
            token = strtok(NULL, " \n");
            if(curent->files != NULL && strcmp(curent->files->name,token) == 0)curent->files = rm(token, curent->files);
            else{
            if(verificare(curent, token) == 0 || verificare(curent, token) == 1){ 
            printf("File %s doesn't exist!\n", token);
            }
            else
            rm(token, curent->files);
            }
        }
        else
        if(!strcmp(token,"rmdir")){
            token = strtok(NULL, " \n");
            if(curent->directories != NULL && strcmp(curent->directories->name,token) == 0)curent->directories = rmdir(token, curent->directories);
            else{
            if(verificare(curent, token) == 0 || verificare(curent, token) == 2){
            printf("Directory %s doesn't exist!\n", token);
            }
            else
            rmdir(token, curent->directories);
            }
        }
        else
        if(!strcmp(token,"cd")){
            token = strtok(NULL, " \n");
            if(strcmp(token,"..") == 0)curent = curent->parent;
            else
            if((verificare(curent, token) == 0 || verificare(curent, token) == 2))
            printf("Directory not found!\n");
            else
            curent = cd(curent->directories, token);
        }
        
        else
        if(!strcmp(token,"quit")){
            token = strtok(NULL, " \n");
            if(token == NULL){
                free(input);
                comanda = false;
            }
        }        
    }
    return 0;
}
