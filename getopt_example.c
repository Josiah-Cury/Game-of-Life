#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> /* used for getopt */
#include <errno.h>

/* command line arguments */
/* process - options */

/* find -n -h -a -l -w -f filename -p pattern */
/* find the pattern in the file, -n print out line numbers */

/* rather than rolling your own command line argument reader, use getopt */

/* do a better job of error processing with getopt */

int main(int argc, char *argv[])
{

	int line_num = 0;	  /* print line numbers */
	int print_line = 0; 		/* print the whole line */
	int print_word = 0;	/* print the word the pattern is found in */
	int find_all = 0;	/* find all occurrences of pattern */
	FILE *fp = NULL;
	int c;
        char *pattern = NULL;


	if (argc == 1) {
		printf("usage: find [-n -l -a -w] -f filename -p pattern\n");
		exit(EXIT_FAILURE);
	}
	/* pass a string of options to getopt
         * the colon after a letter signifies that the option expects an argument 
         * leading colon lets you distinguish between invalid option and missing argument cases
         */
	while((c = getopt(argc, argv, ":hnlawf:p:")) != -1)
		switch(c) {
		case 'n':
			line_num = 1;
 			break;
		case 'l':
			print_line = 1;
			break;
		case 'a':
			find_all = 1;
			break;
		case 'w':
			print_word = 1;
			break;
		case 'f':
			errno = 0; /* set to 0 so can process it if an error occurs */
                        /* assume filename comes after -f */
			/* optarg contains the argument for the option */
			fp = fopen(optarg, "r");
			if (fp == NULL) {
				/* strerror */
				fprintf(stderr, "%s: argument to option '-f' failed: %s\n", argv[0], strerror(errno));
				exit(EXIT_FAILURE);
			}

			break;

		case 'p':
			pattern = optarg;
			break;
		case 'h': 	/* help */
			printf("usage: find [-n -l -a -w] -f filename -p pattern\n");
			printf("or\n");
			printf("usage: find -nlawf filename -p pattern\n");
			printf("n: print line numbers\n");
			printf("l: print lines\n");
			printf("a: find all occurrences of pattern\n");
			printf("w: print word where pattern is found\n");
			printf("f: process file (required)\n");
			printf("filename: the name of the file\n");
			printf("pattern: the pattern to look for\n");
			exit(EXIT_SUCCESS);
		case ':':
			/* missing option argument */
			/* optopt contains the option */
			/* argv[0] is the programs name */
			/* stderr is 1 of 3 files open for you -- stdin, stdout, stderr. Usually they are mapped to the same location */
			fprintf(stderr, "%s: option '-%c' requires an argument\n", argv[0], optopt);
			exit(EXIT_FAILURE);
		case '?': 	/* getopt default invalid option */
		default:
			printf("illegal option %c - ignored\n", optopt);
			printf("usage: find -n -l -a -w -f filename pattern\n");
			break;
				
		}

		/* todo */
		/* now that you have got the command line arguments
		 * do something with them */

                printf("line_num = %d\n", line_num);
                printf("print_line = %d\n", print_line);
   		printf("find_all = %d\n", find_all);
		printf("print_word = %d\n", print_word);
                printf("pattern = %s\n", pattern);

	
	return 0;
}
