/*
 * txt2bin.c
 *
 * Converts 24aa256.txt into SigmaLink USBi firmware binary.
 *
 * You need a C compiler capable of building ISO C99 code.
 *
 * Copyright (c) 2018 Max Chan. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor
 * Boston, MA  02110-1301, USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <err.h>

int main(int argc, const char *argv[])
{
    char *src_file = NULL;
    char *dst_file = NULL;

    switch (argc)
    {
        case 1:
            // We assume there is a 24aa256.txt file.
            src_file = strdup("24aa256.txt");
            break;

        case 2:
            // The input file name is given on the command line.
            src_file = strdup(argv[1]);
            break;

        default:
            // Both input and output file names are given on the
            // command line.
            src_file = strdup(argv[1]);
            dst_file = strdup(argv[2]);
    }

    if (
            !strcmp(src_file, "--help") ||
            !strcmp(src_file, "-h") ||
            !strcmp(src_file, "/?")
            )
    {
        // The user is asking for help.
        fputs(
              "txt2bin: convert 24aa256.txt to binary image.\n"
              "\n"
              "Usage: txt2bin [<input-file> [<output-file>]]\n"
              "Arguments:\n"
              "\t<input-file>:\tInput file name. Default to \"24aa256.txt\"\n"
              "\t<output-file:>\tOutput file name. Default to input file name"
                    "with extension changed to .bin.\n"
              "\n"
              "Example: txt2bin 24aa256.txt 24aa256.bin\n",
              stderr
              );
        exit(EXIT_SUCCESS);
    }

    if (
            !strcmp(src_file, "--version") ||
            !strcmp(src_file, "-v")
            )
    {
        fputs(
              "txt2bin: convert 24aa256.txt to binary image.\n"
              "Copyright (c) 2018 Max Chan.\n"
              "This program is free software; you can redistribute it "
                    "and/or\n"
              "modify it under the terms of the GNU General Public License\n"
              "as published by the Free Software Foundation;\n",
              stderr
             );
        exit(EXIT_SUCCESS);
    }

    if (!dst_file)
    {
        if (!strcmp(src_file, "-"))
        {
            // We are dumping from stdin to stdout.
            dst_file = strdup("-");
        }
        else
        {
            // Change the extension to .bin if we have one, add it otherwise.
            size_t limit = strlen(src_file) + 5;
            dst_file = malloc(limit);
            if (!dst_file)
                err(EXIT_FAILURE, "Failed to allocate memory");
            strncpy(dst_file, src_file, limit);
            char *ext = strrchr(dst_file, '.');
            if (ext)
                *ext = 0;
            strcat(dst_file, ".bin");
        }
    }
    
    FILE *src = strcmp(src_file, "-") ? fopen(src_file, "r") : stdin;
    if (!src)
        err(EXIT_FAILURE, "Failed to open source file \"%s\"", src_file);
    
    FILE *dst = strcmp(dst_file, "-") ? fopen(dst_file, "wb") : stdout;
    if (!dst)
        err(EXIT_FAILURE, "Failed to open destination file \"%s\"", dst_file);
    
    int value = 0;
    int count = 0;
    while (fscanf(src, "%2x", &value) > 0)
    {
        count++;
        fputc(value, dst);
    }
    
    fprintf(
            stderr,
            "Converted %d bytes to %s.\n",
            count,
            strcmp(dst_file, "-") ?
            dst_file :
            "standard output"
            );
    
    if (src != stdin)
        fclose(src);
    if (dst != stdout)
        fclose(dst);
    
    free(src_file);
    free(dst_file);
}

