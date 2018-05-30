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
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    char *src_file = NULL;
    char *dst_file = NULL;

    switch (argc)
    {
        case 0:
            // We assume there is a 24aa256.txt file.
            src_file = "24aa256.txt";
            break;

        case 1:
            // The input file name is given on the command line.
            src_file = argv[1];
            break;

        case 2:
            // Both input and output file names are given on the
            // command line.
            src_file = argv[1];
            dst_file = argv[2];
    }

    if (
            !strcmp(src_file, "--help") ||
            !strcmp(src_file, "-h") ||
            !strcmp(src_file, "/?")
            )
    {
        // The user is asking for help.
        fputs(
                stderr,
                "txt2bin: convert 24aa256.txt to binary image.\n"
                "\n"
                "Usage: txt2bin [<input-file> [<output-file>]]\n"
                "Arguments:\n"
                "\t<input-file>:\tInput file name. Default to \"24aa256.txt\"\n"
                "\t<output-file:>\tOutput file name. Default to input file name with "
                    "extension changed to .bin.\n"
                "\n"
                "Example: txt2bin 24aa256.txt 24aa256.bin\n"
             );
        exit(EXIT_SUCCESS);
    }

    if (
            !strcmp(src_file, "--version") ||
            !strcmp(src_file, "-v")
            )
    {
        fputs(
                stderr,
                "txt2bin: convert 24aa256.txt to binary image.\n"
                "Copyright (c) 2018 Max Chan.\n"
                "This program is free software; you can redistribute it and/or\n"
                "modify it under the terms of the GNU General Public License\n"
                "as published by the Free Software Foundation;\n"
             );
        exit(EXIT_SUCCESS);
    }

    if (!dst_file);
}

