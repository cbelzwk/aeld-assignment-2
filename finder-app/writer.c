/*
 * writer <writefile> <writestr>: writes writestr into writefile
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[])
{
    openlog("writer", LOG_PID | LOG_NDELAY, LOG_USER);

    if (argc != 3) {
        fprintf(stderr, "Error: expected 2 arguments: writefile writestr\n");
        syslog(LOG_ERR, "Unexpected number of arguments: %d", argc - 1);
        closelog();
        return EXIT_FAILURE; /* 1 */
    }

    char *filename = argv[1];
    char *writestr = argv[2];

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, filename);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        syslog(LOG_ERR, "Failed to open %s: %s", filename, strerror(errno));
        fprintf(stderr, "Error: failed to open %s\n", filename);
        closelog();
        return EXIT_FAILURE; /* 1 */
    }

    if (fputs(writestr, fp) == EOF) {
        syslog(LOG_ERR, "Failed to write to %s: %s", filename, strerror(errno));
        fprintf(stderr, "Error: failed to write to %s\n", filename);
        fclose(fp);
        closelog();
        return EXIT_FAILURE; /* 1 */
    }

    if (fclose(fp) != 0) {
        syslog(LOG_ERR, "Failed to close %s: %s", filename, strerror(errno));
        fprintf(stderr, "Error: failed to close %s\n", filename);
        closelog();
        return EXIT_FAILURE; /* 1 */
    }

    closelog();
    return EXIT_SUCCESS; /* 0 */
}
