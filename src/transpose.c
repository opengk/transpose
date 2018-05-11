/*  transpose: outputs horizontal table vertically
    Copyright (C) 2018  Guillaume Koehl <opengk@free.fr>
   
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

/* Written by Guillaume Koehl */

/* Thanks a lot to the K&R Learning C book which
 * almost explicits all the code  and to the GNU
 * coreutils source code which is a great source
 * of inspiration for coding in the linux system*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <getopt.h>


#define PROG_NAME   "transpose"
#define BUFSIZE     8192
#define STREQ(a, b) (*(a) == *(b) && strcmp((a), (b)) == 0)


static struct option const longopts[] =
{
    {"help",    no_argument, NULL, 'h'},
    {"version", no_argument, NULL, 'v'},
};

void usage(int status)
{
    if (status != EXIT_SUCCESS) {
        fprintf (stderr, "Try '%s -h or --help' for more information.\n", PROG_NAME);
    } else {
        printf ("Usage: %s [FILE]\n\
Display text vertically, for example create a vertical histogram from an horizontal input.\n\n\
Without FILE, read standard input.\n\n\
  -h, --help     Show help and exit\n\
  -v, --version  Show version\n", PROG_NAME);
    }
    exit(status);
}

int count_lines(char *input)
{
    int lines = 0;
    for (size_t i = 0; i < strlen(input); ++i)
        if (input[i] == '\n')
            lines++;

    return lines;
}

int count_longest_line(char *input)
{
    int curr_char = 0, max_char = 0, curr_line = 0;
    for (size_t i = 0; i < strlen(input); ++i) {
        curr_char++;
        if (input[i] == '\n') {
            if (curr_char > max_char)
                max_char = curr_char;
            curr_line++;
            curr_char = 0;
        }
    }
    return max_char;
}

void transpose(const char *file)
{
    /* Open Stdin or a File */
    int fd;
    if (STREQ(file, "stdin")) {
        fd = STDIN_FILENO; /* stdin */
    } else {
        fd = open(file, O_RDONLY); /* read from file */
        if (fd == -1)
            perror("Could not open file");
    }
    
    /* Read file */
    char buf[BUFSIZE];              /* buffer */
    char input[BUFSIZE];            /* all text */
    size_t read_bytes, tot_bytes;   /* bytes */
    while (1) { 
        read_bytes = read(fd, buf, BUFSIZE); /* copy to buffer */
        
        if (read_bytes == 0) /* EOF */
            break;
        
        if (read_bytes == -1) {
            perror("read");
            break;
        }
        
        tot_bytes += read_bytes;

        for (size_t i = 0; i < read_bytes; i++) /* record each line */
            input[i+tot_bytes-read_bytes] = buf[i];
    }
    
    /* Count lines and longest line chars number */
    int lines = count_lines(input);             
    int max_char = count_longest_line(input);   
    
    /* Store data in an array to facilitate transposing */
    int text[lines][max_char];
    for (int i = 0; i < lines; ++i)
        for (int j = 0; j < max_char; ++j)
            text[i][j] = 0;
    
    int curr_char = 0, curr_line = 0;
    for (size_t i = 0; i < strlen(input); ++i) {
        if (input[i] == '\n') {
            curr_char = 0;
            curr_line++;
        } else {
            if (input[i] == '\t') /* tab is converted to space character */
                text[curr_line][curr_char] = ' ';
            else
                text[curr_line][curr_char] = input[i];
            curr_char++;
        }
    }
    
    /* Transpose the table */
    for (int j = max_char - 2; j >= 0; --j) {
        for (int i = 0; i < lines; ++i) {
            if (text[i][j] != 0)
                printf("%c ", text[i][j]);
            else
                printf("  ");
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    /* Parameters with getopts */
    int c;
    while ((c = getopt_long (argc, argv, "hv", longopts, NULL)) != -1) {
        switch (c) {
            case 'h': /* help */
                usage(EXIT_SUCCESS);
                break;
            
            case 'v': /* version */
                printf("transpose  Copyright (C) 2018  Guillaume Koehl\n\
GNU General Public License v3 (GPL-3). This program comes with ABSOLUTELY NO WARRANTY.\n\
This is free software, and you are welcome to redistribute it under certain conditions.\n");
                exit(EXIT_SUCCESS);
                break;
            
            default: /* usage */
                usage(EXIT_FAILURE);
        }
    }
    
    /* Get source and transpose */
    int files = argc - optind;
    if (files == 0)
        transpose("stdin");
    else if (files == 1)
        transpose(argv[1]);
    else
        usage(EXIT_SUCCESS);

    exit(EXIT_SUCCESS);
}
