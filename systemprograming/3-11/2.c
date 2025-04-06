
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char *, char *);
int main(int ac, char *av[])
{
	int in_fd, out_fd, n_chars;
	char buf[BUFFERSIZE];
    char    i;
	
    int fp;

    if (ac == 4)
    {
        if (strcmp("-i",av[1])==0)
        {
            fp=open(av[3],O_RDONLY);
            if (fp != -1)
            {
                if (strcmp(av[2],av[3])==0)
                {
                    printf("cp1: '%s' 와 '%s' 는 같은 파일\n",av[2],av[3]);
                    return (0);
                }
                printf("cp1: '%s'를 덮어쓸까요 (y/n)? ",av[3]);
                scanf("%c",&i);
                if (i == 'y')
                {
                    /* open files */
	                if( (in_fd=open(av[2], O_RDONLY)) == -1)
                        oops("Cannot open ", av[2]);

                    if( (out_fd = creat(av[3], COPYMODE)) == -1)
                        oops("Cannot creat ", av[3]);

                        /* copy files */
                    while(( n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
                        if( write( out_fd, buf, n_chars ) != n_chars )
                            oops("Write error to ", av[3] );

                        if( n_chars == -1 )
                            oops( "Read error from ", av[2] );

                        /* close files */
                        if( close(in_fd) == -1 || close(out_fd) == -1 )
                            oops("Error closing files", "" );
                    
                }
                else
                {
                    return (0);
                }              


            }

        }
    }
    else if( ac != 3) {
		fprintf( stderr, "usage: %s source destination\n", *av);
		exit(1);
	}

    if (strcmp(av[1],av[2]) == 0 )
    {
        printf("cp1: '%s' 와 '%s' 는 같은 파일",av[1],av[2]);
        return (0);
    }

	/* open files */
	if( (in_fd=open(av[1], O_RDONLY)) == -1)
		oops("Cannot open ", av[1]);

	if( (out_fd = creat(av[2], COPYMODE)) == -1)
		oops("Cannot creat ", av[2]);

	/* copy files */
	while(( n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
		if( write( out_fd, buf, n_chars ) != n_chars )
			oops("Write error to ", av[2] );

	if( n_chars == -1 )
		oops( "Read error from ", av[1] );

	/* close files */
	if( close(in_fd) == -1 || close(out_fd) == -1 )
		oops("Error closing files", "" );
}

void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s ", s1);
	perror(s2);
	exit(1);
}


