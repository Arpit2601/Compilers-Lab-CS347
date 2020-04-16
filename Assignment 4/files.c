

#include "files.h"




int if_file_exist(char * filename){


	FILE *file;
	if ((file = fopen(filename, "r")))
	{
		fclose(file);
		return 1;
	}
	else{
		return 0;

	}
	return 0;


}
