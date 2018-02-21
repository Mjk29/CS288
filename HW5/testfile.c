#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
    {

    FILE *file;
    char line[256];
    char *t;
    int q=0;
    file = fopen(argv[1],"r");
    char *fields[4];
     
      //Tokenizes every line line = the whole line t = each token
    while ( fgets (line, sizeof(line), file)){
        // printf("%s\n", line);
        q=0;
        fields[0]=strtok(line,",\n");
        // fields[0] = t;
        printf("%s\n ", fields[0]);

        while( fields[q] != NULL ) {
            // printf( "%s %i \n",t, q);
            // printf("%i ",q);

            q++;
            fields[q] = strtok( NULL, ",\n" );
            // fields[q] = t;
            // q++;
        }
        // q=0;
        // fields[0]=NULL;
        // fields[1]=NULL;
        // fields[2]=NULL;
        // fields[3]=NULL;
        

        printf("%s\n ", fields[1]);
        printf("%s\n ", fields[2]);
        printf("%s \n\n", fields[3]);




        // for (int i = 0; i < 4; ++i){
        //     printf("%i %s \n", i, fields[i]);
        // }

        
    }
    fclose (file);
}

