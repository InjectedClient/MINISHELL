#include <stdio.h>
#include <errno.h>
#include <string.h>

int main() {
    FILE *file = fopen("inexistant.txt", "r");
    if (!file) {
        printf("Erreur numéro : %d\n", errno);
        printf("Description : %s\n", strerror(errno)); // Convertir errno en message
    }
    return 0;
}
