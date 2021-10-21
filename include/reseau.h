#ifndef RESEAU_H_INCLUDED
#define RESEAU_H_INCLUDED

#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <regex.h>

/** 
* construireAdresseTCPUDPDepuisChaine() Constuit l'adresse de la socket a partir des chaines d'adresse ip et de port
* @param adresseIP adresse ip ou creer la socket
* @param port port de la socket
* @return structure d'adresse pour la socket
*/ 
struct sockaddr_in construireAdresseTCPUDPDepuisChaine(char* adresseIP, char* port);

/** 
* creerSocketTCPUDPServeur() creer la socket du serveur pour TCP ou UDP
* @param adresse structure d'adresse pour la socket
* @param mode mode de la socket a construire
* @return resultat de l'execution (reusssite/echec) 
*/ 
int creerSocketTCPUDPServeur(struct sockaddr_in adresse, int mode);

/** 
* creerSocketTCPServeur() creer une socket de serveur TCP
* @param adresse structure d'adresse de la socket
* @return resultat de l'execution (reusssite/echec) 
*/ 
int creerSocketTCPServeur(struct sockaddr_in adresse);

#endif // RESEAU_H_INCLUDED
