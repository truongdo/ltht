#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
char *locale;

/*
char *get_utf8_input()
{
    char *line, *u8s;
    unsigned int *wcs;
    int len;
	

    
    line = readline("");
    if (locale_is_utf8) {
        return line;
    }
    else {
        len = mbstowcs(NULL, line, 0)+1;
        wcs = malloc(len * sizeof(int));
        mbstowcs(wcs, line, len);
        u8s = malloc(len * sizeof(int));
        u8_toutf8(u8s, len*sizeof(int), wcs, len);
        free(line);
        free(wcs);
        return u8s;
    }
  */  
int main (int argc, char** argv ){
	locale = setlocale(LC_ALL, "");
		char *string;
		//string = get_utf8_input();
		printf("get string %s \n",locale);
}
