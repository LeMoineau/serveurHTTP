#include <stdio.h>
#include <stdlib.h>

#include "serveur.h"

int main(int argc, char** argv)
{
	char *adresseServeur = malloc(sizeof(char)* TAILLE_BUFFER);
	char *portServeur = malloc(sizeof(char)* TAILLE_BUFFER);
	char *racineServeur = malloc(sizeof(char)* TAILLE_BUFFER);

	//Lecture du fichier de configuration
	FILE *config = fopen("./etc/server.conf", "r");
	if (config != NULL) {
		fscanf(config, "%s %s %s", adresseServeur, portServeur, racineServeur);
		fclose(config);
	}

	run(adresseServeur, portServeur, racineServeur);
}
