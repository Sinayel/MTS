#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

const char *nomsDossiers_texture[] = {"block", "item", "particle", "font"};
const char *nomsDossiers_armor[] = {"color_palettes", "items", "armor"};

const char *cheminsSources[] = {
    "Ressource_pack_classic/VanillaDefault+1.20/assets/minecraft/textures/block",
    "Ressource_pack_classic/VanillaDefault+1.20/assets/minecraft/textures/item",
    "Ressource_pack_classic/VanillaDefault+1.20/assets/minecraft/textures/particle",
    "Ressource_pack_classic/VanillaDefault+1.20/assets/minecraft/font"
};
const char *cheminsSources_armor[] = {
    "Ressource_pack/VanillaDefault+1.20/assets/minecraft/textures/trims",
    "Ressource_pack/VanillaDefault+1.20/assets/minecraft/textures/trims/models",
    "Ressource_pack/VanillaDefault+1.20/assets/minecraft/textures"
};

void copierDossier(const char *source, const char *destination) {
    DIR *dir;
    struct dirent *entry;

    // Ouvrir le dossier source
    if ((dir = opendir(source)) == NULL) {
        perror("Erreur lors de l'ouverture du dossier source");
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

    // Dossier de destination ou sont clonés les dossiers armurs etc..
    const char *destination_armor = "Ressourcepackcustom/classic/assets/minecraft/textures";

    // Dossier de destination spécifique pour le fichier pack.mcmeta
    const char *destinationMcmeta = "Ressourcepackcustom/classic/assets/minecraft/";

    // Nom du fichier .mcmeta à copier
    const char *nomFichierMcmeta = "pack.mcmeta";

    // Chemin complet vers le fichier .mcmeta source
    const char *cheminSourceMcmeta = "Ressource_pack_classic/VanillaDefault+1.20" "/" "pack.mcmeta";

    // Copier le fichier .mcmeta dans le dossier de destination spécifique
    char cheminDestinationMcmeta[512];
    snprintf(cheminDestinationMcmeta, sizeof(cheminDestinationMcmeta), "%s/%s", destinationMcmeta, nomFichierMcmeta);
    FILE *fileSourceMcmeta = fopen(cheminSourceMcmeta, "rb");
    FILE *fileDestinationMcmeta = fopen(cheminDestinationMcmeta, "wb");
    if (fileSourceMcmeta && fileDestinationMcmeta) {
        char buffer[1024];
        size_t bytesRead;
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), fileSourceMcmeta)) > 0) {
            fwrite(buffer, 1, bytesRead, fileDestinationMcmeta);
        }
        fclose(fileSourceMcmeta);
        fclose(fileDestinationMcmeta);
        printf("Fichier %s copié avec succès dans le dossier de destination !\n", nomFichierMcmeta);
    } else {
        perror("Erreur lors de la copie du fichier .mcmeta");
    }

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

    // Parcourir la liste des armurs
    for (int i = 0; i < sizeof(nomsDossiers_armor) / sizeof(nomsDossiers_armor[0]); i++) {
        const char *nomDossierDestination = nomsDossiers_armor[i];
        char cheminDestination[512];
        snprintf(cheminDestination, sizeof(cheminDestination), "%s/%s", destination_armor, nomDossierDestination);

        // Créer le dossier de destination
        mkdir(cheminDestination, 0777);

        // Copier le dossier correspondant
        copierDossier(cheminsSources_armor[i], cheminDestination);

        printf("Dossiers copiés avec succès dans le dossier %s !\n", nomDossierDestination);
    }

    return 0;
}
