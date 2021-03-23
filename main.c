#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <errno.h>
#include <unistd.h>
#include <dirent.h>

#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE		1024

static const char *nuestros_nombres = { "Erick Salas Romero\nRicardo Whaibe Martinez\nMariana Peña Hernandez\nMaximiliano Escobar Valencia\nGarciacano Garcia Gabriel\nUriel Castañeda Gomez\n\n" };

static int checar_por_directorio_creado (const char *dirname) {

	struct stat dirstats = { 0 };
	return stat (dirname, &dirstats);

}

static void borrar_directorio (const char *dirname) {

	char buffer[BUFFER_SIZE] = { 0 };

	// borrar archivos dentro del directorio
	DIR *dp = opendir (dirname);
	if (dp) {
		struct dirent *ep = NULL;
		while ((ep = readdir (dp)) != NULL) {
			if (strcmp (ep->d_name, ".") && strcmp (ep->d_name, "..")) {
				(void) snprintf (buffer, BUFFER_SIZE - 1, "%s/%s", dirname, ep->d_name);
				(void) printf ("Borrando archivo %s...\n", buffer);

				(void) remove (buffer);
			}
		}

		(void) closedir (dp);
	}

	// borrar directorio
	if (rmdir (dirname)) {
		(void) printf ("Error %d al borrar el directorio %s!\n\n", errno, dirname);
	}

}

static void listar_directorio (const char *dirname) {

	// listar directorio actual
	DIR *dp = opendir (".");
	if (dp) {
		struct dirent *ep = NULL;
		while ((ep = readdir (dp)) != NULL) {
			// if (strcmp (ep->d_name, ".") && strcmp (ep->d_name, "..")) {
				(void) printf ("Archivo: %s\n", ep->d_name);

				listar_atributos_del_archivo (ep->d_name, false);
			// }
		}

		(void) closedir (dp);
	}

}

int main (int argc, const char **argv) {

	printf ("Hola mundo!\n\n");

	return 0;

}