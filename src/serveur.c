
#include "reseau.h"
#include "serveur.h"

int ecouter(int socketServeur, int longueurFileDAttente, char racineServeur[]) {
    int longueurAdresseClient;
    struct sockaddr_in adresseClient;
    int socketClient;
    int erreur=0;
    pid_t PID;
    erreur=listen(socketServeur, longueurFileDAttente);

    while (erreur!=-1) {
        longueurAdresseClient=sizeof adresseClient;
        socketClient=accept(socketServeur, (struct sockaddr *)&adresseClient, (socklen_t *)&longueurAdresseClient);

        if (socketClient!=-1) {
            if ((PID=fork())!=-1) {
                if (PID==0) {
                    if (traiterRequete(socketClient, racineServeur)) {
                        close(socketClient);
                        exit(0);
                    } else
                        erreur=-1;
                }
            } else
                erreur=-1;
        } else
            erreur=-1;
    }
    return erreur;
}

int traiterRequete(int socketClient, char racineServeur[]) {
    char requete[TAILLE_BUFFER];
    if (lireRequete(socketClient, requete) != -1)
        return envoyerResultat(socketClient, requete, racineServeur);
    else
        return -1;
}

int lireRequete(int socket, char requete[]) {
	int nbCaracteres = 0;
	nbCaracteres = read(socket, requete, TAILLE_BUFFER-1);
	
	if (nbCaracteres != -1)
		requete[nbCaracteres] = '\0';

	return nbCaracteres; 
}

int envoyerResultat(int socket, char requete[], char racineServeur[]){
	
	char *path = malloc(sizeof(char) * TAILLE_BUFFER);
	char *relativePath;
	int HTTPVersion;
	int res;

	path = strcpy(path, racineServeur);
	if (obtenirInformationRequete(requete, &relativePath, &HTTPVersion) == -1) {
		return -1;
	}

	strcat(path, relativePath);

	res = envoyerDonnees(socket, path);
	free(path);

	return res;
}

int obtenirInformationRequete(char requete[], char **chemin, int *HTTPversion) {

	printf("\nrequete: \n%s", requete);

	*chemin = malloc(sizeof(char) * TAILLE_BUFFER);
	sscanf(requete, "GET %" STR(TAILLE_BUFFER) "[^ ] HTTP/1.%" STR(TAILLE_BUFFER) "d", *chemin, HTTPversion);

	printf("\nchemin: '%s', version HTTP: HTTP/1.%d", *chemin, *HTTPversion);

	if(strcmp(*chemin, "/") == 0) {
 		*chemin = "/index.html";
 	}

	return 0;
	
}

int envoyerDonnees(int socket, char* chemin){

	FILE *file = fopen(chemin, "rb");
 	int nbChars;
 	char HTTPHeaders[TAILLE_BUFFER*2];
 	char *contentType;
 	char *extension;
 	char *resource;
 	int contentLength;

 	if(file == NULL) {
 		return -1;
 	}

	// Content length
 	fseek(file, 0, SEEK_END);
 	contentLength = ftell(file);
 	rewind(file);

 	// Content types
 	extension = strrchr(chemin, '.');
 	if(strcmp(extension, ".html") == 0) {
 		contentType = "text/html";
 	} else if (strcmp(extension, ".png") == 0) {
 		contentType = "image/png";
 	} else if (strcmp(extension, ".gif") == 0) {
 		contentType = "image/gif";
 	} else if ((strcmp(extension, ".jpg") == 0) || (strcmp(extension, ".jpeg") == 0)) {
 		contentType = "image/jpeg";
 	} else {
 		contentType = "text/plain";
 	}

 	// Ecriture du Header HTTP
 	sprintf(HTTPHeaders, "HTTP/1.0 200 OK\nContent-Length: %d\nContent-type: %s\n\n", contentLength, contentType);

 	// Lecture de la ressource demandée
 	resource = malloc(contentLength + 1);
 	fread(resource, contentLength, 1, file);
 	fclose(file);
 	resource[contentLength] = 0;

 	// Envoie des données par les sockets
 	nbChars = strlen(HTTPHeaders) * sizeof(char);
 	write(socket, HTTPHeaders, nbChars);
 	nbChars = contentLength * sizeof(char);
 	write(socket, resource, nbChars);
 	free(resource);
 	return 0;
}


int run(char *adresseServeur, char* portServeur, char* racineServeur) {
	int socketServeur;

	printf("%s %s %s \n", adresseServeur, portServeur, racineServeur);
	socketServeur = creerSocketTCPServeur(construireAdresseTCPUDPDepuisChaine(adresseServeur, portServeur));

	if (socketServeur!=-1)
		ecouter(socketServeur, 10, racineServeur);

	return 1;
}




