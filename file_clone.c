#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

const char *nomsDossiers_texture[] = {"block", "item", "particle", "font", "armor"};

const char *cheminsSources[] = {
    "Ressource_pack_classic/VanillaDefault+1.20/assets/minecraft/textures/block",
    "Ressource_pack_classic/VanillaDefault+1.20/assets/minecraft/textures/item",
    "Ressource_pack_classic/VanillaDefault+1.20/assets/minecraft/textures/particle",
    "Ressource_pack_classic/VanillaDefault+1.20/assets/minecraft/font",
    "Ressource_pack_classic/VanillaDefault+1.20/assets/minecraft/textures/models/armor"
};

void copierDossier(const char *source, const char *destination) {
    DIR *dir;
    struct dirent *entry;

    // Ouvrir le dossier source
    if ((dir = opendir(source)) == NULL) {
        perror("Erreur lors de l'ouverture du dossier source");
        printf("Erreur lors de l'ouverture du dossier %s", source);
        exit(EXIT_FAILURE);
    }

    // Créer un dossier de destination avec un nom prédéfini
    char *nomDossierDestination = "."; // Changez ceci au nom souhaité
    char pathDestination[512];
    snprintf(pathDestination, sizeof(pathDestination), "%s/%s", destination, nomDossierDestination);
    mkdir(pathDestination, 777);

    // Parcourir les fichiers et sous-dossiers du dossier source
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            // Construire les chemins complets pour le fichier source et le fichier destination
            char pathSource[512];
            char pathDestinationFile[512];
            snprintf(pathSource, sizeof(pathSource), "%s/%s", source, entry->d_name);
            snprintf(pathDestinationFile, sizeof(pathDestinationFile), "%s/%s", pathDestination, entry->d_name);

            // Copier le fichier ou le dossier
            if (entry->d_type == DT_DIR) {
                // Si c'est un dossier, appeler récursivement la fonction
                copierDossier(pathSource, pathDestination);
            } else {
                // Si c'est un fichier le copier
                FILE *fileSource = fopen(pathSource, "rb");
                FILE *fileDestination = fopen(pathDestinationFile, "wb");
                if (fileSource && fileDestination) {
                    char buffer[1024];
                    size_t bytesRead;
                    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fileSource)) > 0) {
                        fwrite(buffer, 1, bytesRead, fileDestination);
                    }
                    fclose(fileSource);
                    fclose(fileDestination);
                } else {
                    perror("Erreur lors de la copie du fichier");
                }
            }
        }
    }

    // Fermer le dossier source
    closedir(dir);
}

int main() {
    // Dossier de destination ou sont clonés les dossiers items/block etc..
    const char *destination = "Ressourcepackcustom/classic/assets/minecraft/textures";

    // Dossier de destination spécifique pour le fichier pack.mcmeta
    const char *destinationMcmeta = "Ressourcepackcustom/classic";
    const char *destinationIcon = "Ressourcepackcustom/classic";

    // Nom du fichier .mcmeta et icon à copier
    const char *FichierMcmeta = "pack.mcmeta";
    const char *icon = "pack.png";

    // Chemin complet vers le fichier .mcmeta source
    const char *cheminSourceMcmeta = "Ressource_pack_classic/VanillaDefault+1.20" "/" "pack.mcmeta";
    const char *cheminSourceIcon = "Ressource_pack_classic/VanillaDefault+1.20" "/" "pack.png";

    // Copier le fichier .mcmeta et Icon dans le dossier de destination spécifique
    char cheminDestinationMcmeta[512];
    char cheminDestinationIcon[512];

    snprintf(cheminDestinationMcmeta, sizeof(cheminDestinationMcmeta), "%s/%s", destinationMcmeta, FichierMcmeta);
    snprintf(cheminDestinationIcon, sizeof(cheminDestinationIcon), "%s/%s", destinationIcon, icon);

    FILE *fileSourceMcmeta = fopen(cheminSourceMcmeta, "rb");
    FILE *fileDestinationMcmeta = fopen(cheminDestinationMcmeta, "wb");
    FILE* fileSourceIcon = fopen(cheminSourceIcon, "rb");
    FILE* fileDestinationIcon = fopen(cheminDestinationIcon, "wb");

    if (fileSourceMcmeta && fileDestinationMcmeta) {
        char buffer[1024];
        size_t bytesRead;
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), fileSourceMcmeta)) > 0)
        {
            fwrite(buffer, 1, bytesRead, fileDestinationMcmeta);
            fclose(fileSourceMcmeta);
            fclose(fileDestinationMcmeta);
        }
        printf("Fichier %s copié avec succès dans le dossier de destination !\n", FichierMcmeta);
    }else
        perror("Erreur lors de la copie du fichier .mcmeta");

    if (fileSourceIcon && fileDestinationIcon){
        char buffer[1024];
        size_t bytesRead;
        while((bytesRead = fread(buffer, 1, sizeof(buffer), fileSourceIcon)) > 0)
        {
            fwrite(buffer, 1, bytesRead, fileDestinationIcon);
            fclose(fileSourceIcon);
            fclose(fileDestinationIcon);
        }
        printf("Fichier %s copié avec succès dans le dossier de destination !\n", icon);
    }else
        perror("Erreur lors de la copie du fichier pack.png");

    // Parcourir la liste de block/items
    for (int i = 0; i < sizeof(nomsDossiers_texture) / sizeof(nomsDossiers_texture[0]); i++) {
        const char *nomDossierDestination = nomsDossiers_texture[i];
        char cheminDestination[512];
        snprintf(cheminDestination, sizeof(cheminDestination), "%s/%s", destination, nomDossierDestination);

        // Créer le dossier de destination
        mkdir(cheminDestination, 0777);

        // Copier le dossier correspondant
        copierDossier(cheminsSources[i], cheminDestination);

        printf("Dossiers copiés avec succès dans le dossier %s !\n", nomDossierDestination);
    }

    return 0;
}
