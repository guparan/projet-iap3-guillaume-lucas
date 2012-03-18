#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "decompression.h"

FILE* decompression_decompresse(char* nomFichier)
{
    FILE *fichierComp = NULL, *fichierCodage = NULL, *fichierDecomp = NULL;
    char *nomFichierCodage = nomFichier, *extensionFichComp = ".comp", *extensionFichCodage = ".huf", *buffer = NULL;
    int caractereActuel = 0, i = 0, j = 0;
     char** tabCorrespondance = malloc(256*sizeof(char*));
    
    realloc(nomFichierCodage, strlen(nomFichierCodage)+strlen(extensionFichComp)+1);
    fichierCodage = fopen(strcat(nomFichierCodage, extensionFichCodage), "r");
    if (fichierCodage == NULL)
    {
        perror("fopen");
        exit(errno);
    }
    
   /* Création de la table d'association ASCII / codage à utiliser (obtenue par lecture de l'entête du fichier input)*/
        
    while (caractereActuel != EOF)
    {
        caractereActuel = fgetc(fichierComp);   /* on lit l'indice */
        i = caractereActuel;    /* on l'affecte à i */
        caractereActuel = fgetc(fichierComp);   /* on passe le caractère " " (espace) qui sépare l'indice du code */
        caractereActuel = fgetc(fichierComp);   /* lecture du premier chiffre de la fréquence associée */
        
        while (caractereActuel != '\n')     /* on lit le code à placer dans tabCorrespondance[i] */
        {
            j++;    /* nombre de char dans le buffer */
            realloc(buffer, j*sizeof(char));
            buffer[j-1] = caractereActuel;      /* on remplit le buffer avec le code (suite de 0 et 1) */
            caractereActuel = fgetc(fichierComp);   /* on passe au caractère suivant */
        }
        
        tabCorrespondance[i] = buffer;
        j = 0;      /* on réinitialise j */
        free(buffer);   /* on réinitialise le buffer */
    }
    
    fclose(fichierCodage);
    
    /* Décompression du fichier */
    realloc(nomFichier, strlen(nomFichier)+strlen(extensionFichComp)+1);
    fichierComp = fopen(strcat(nomFichier, extensionFichComp), "rb");
    if (fichierComp == NULL)
    {
        perror("fopen");
        exit(errno);
    }
    fichierDecomp = fopen(nomFichier, "wb+");
    
    /* .... */
    
    fclose(fichierComp);
    
    
    return fichierDecomp;
}
