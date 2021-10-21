#ifndef SERVEUR_H_INCLUDED
#define SERVEUR_H_INCLUDED

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define TAILLE_BUFFER 128
#define STR_(X) #X //Pour transformer un DEFINE en String
#define STR(X) STR_(X)

/** 
* run() lance le serveur
* @param adresseServeur adresse ou ecouter
* @param portServeur port ou ecouter
* @param racineServeur repertoire des fichier a envoyer
* @return resultat de l'execution (reusssite/echec) 
*/ 
int run(char *adresseServeur, char* portServeur, char* racineServeur);

/** 
* ecouter() lance l'écoute sur la socketServeur
* @param socketServeur socket du serveur 
* @param longueurFileDAttente longueur de la file d'attente acceptable
* @return resultat de l'execution (reusssite/echec) 
*/ 
int ecouter(int socketServeur, int longueurFileDAttente, char racineServeur[]);

/** 
* traiterRequete() traite les requete recu sur la socket du serveur
* @param socketClient socket du client qui a lance une requete au serveur
* @param racineServeur repertoire des fichiers a envoyer
* @return resultat de l'execution (reusssite/echec) 
*/ 
int traiterRequete(int socketClient, char racineServeur[]);

/** 
* lireRequete() compte le nombre de caractere de la requete 
* @param socket socket du client 
* @param requete requete a compter
* @return nombre de caractere de la requete 
*/ 
int lireRequete(int socket, char requete[]);

/** 
* envoyerResultat() organise l'envoie de la reponse au client
* @param socket socket du client
* @param requete requete envoyee au serveur
* @param racineServeur repertoire des fichier a envoyer
* @return resultat de l'execution (reusssite/echec) 
*/ 
int envoyerResultat(int socket, char requete[], char racineServeur[]);

/** 
* obtenirInformationRequete() recupere l'url demande par le client
* @param requete requete envoye au serveur
* @param chemin stockage du chemin demande
* @param HTTPVersion stockage de la version HTTP utilisee
* @return resultat de l'execution (reusssite/echec) 
*/ 
int obtenirInformationRequete(char requete[], char **chemin, int *HTTPversion);

/** 
* envoyerDonnees() envoie les fichiers au client
* @param socket socket du client 
* @param chemin chemin demande par le client
* @return resultat de l'execution (reusssite/echec) 
*/ 
int envoyerDonnees(int socket, char* chemin);

#endif // SERVEUR_H_INCLUDED
