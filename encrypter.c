/*
isaac archer, iarcher
cs201 homework a2
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/file.h>

#define length 81

int main(int argc, char ** argv)
{

/*variables*/
unsigned int seed = 0; //initial seed value for srand();
int key = 0; //value to put the rand() key into
char file_in[length]; //file extension for the infile
char file_out[length]; //file extension for the outfile
int in_fp = 0; //in file pointer
int out_fp = 0; //out file pointer
int byte_number = 4; //number of bytes per character or in to read in

union buff //union for easy encryption of characters
{
unsigned int buff_int;
int buff_char[4];
} buffer_tool;

/*check if there are enough input parameters*/
if(argc < 7)
{
	printf("\ntoo few parameters\n");
	return -1;
}

/*debug---------------------------
printf("%d \n", argc);
printf("%s \n", argv[0]);
printf("%s \n", argv[1]);
printf("%s \n", argv[2]);
printf("%s \n", argv[3]);
printf("%s \n", argv[4]);
printf("%s \n", argv[5]);
printf("%s \n", argv[6]);
-------end debug print arguments*/

/*now parse input parameters*/
if((argv[1][1] == 's') && (argv[1][0] == '-')) //if it finds the flag
{
	/*printf("bla");*/
	seed = atoi(argv[2]); //set the value of the flag's parameter

	if((argv[3][1] == 'i') && (argv[3][0] == '-')) //if it finds the flag
	{
		
		strcpy(file_in, argv[4]); //set the value of the flag's parameter

		if((argv[5][1] == 'o') && (argv[5][0] == '-')) //if it finds the flag
		{
		
		strcpy(file_out, argv[6]); //set the value of the flag's parameter

		}
		else
		{
			printf("\ninvalid parameters\n"); //else exit because there was problem with the flags
			return -1;
		}

		//the rest of the parse if statement tree is all the same so that all possibilities are covered
	}
	else if((argv[3][1] == 'o') && (argv[3][0] == '-'))
	{

		strcpy(file_out, argv[4]);

		if(argv[5][1] == 'i')
		{
		strcpy(file_in, argv[6]);
		}
		else
		{
			printf("\ninvalid parameters\n");
			return -1;
		}
	}
	else
	{
	printf("\ninvalid parameters\n");
	return -1;
	}
}
else if((argv[1][1] == 'i') && (argv[1][0] == '-'))
{
	/*printf("bla");*/
	strcpy(file_in, argv[2]);

	if((argv[3][1] == 's') && (argv[3][0] == '-')){

		seed = atoi(argv[4]);

		if((argv[5][1] == 'o') && (argv[5][0] == '-'))
		{
		
		strcpy(file_out, argv[6]);

		}
		else
		{
			printf("\ninvalid parameters\n");
			return -1;
		}
	}
	else if((argv[3][1] == 'o') && (argv[3][0] == '-')){

		strcpy(file_out, argv[4]);

		if((argv[5][1] == 's') && (argv[5][0] == '-'))
		{
			seed = atoi(argv[6]);
		}
		else
		{
			printf("\ninvalid parameters\n");
			return -1;
		}
	}
	else{
	printf("\ninvalid parameters\n");
	return -1;
	}

}
else if((argv[1][1] == 'o') && (argv[1][0] == '-'))
{

	/*printf("bla");*/
	strcpy(file_out, argv[2]);

	if((argv[3][1] == 'i') && (argv[3][0] == '-')){

		strcpy(file_in, argv[4]);

		if((argv[5][1] == 's') && (argv[5][0] == '-'))
		{

			seed = atoi(argv[6]);

		}
		else
		{
			printf("\ninvalid parameters\n");
			return -1;
		}
	}
	else if((argv[3][1] == 's') && (argv[3][0] == '-')){

		seed = atoi(argv[4]);

		if((argv[5][1] == 'i') && (argv[5][0] == '-'))
		{

			strcpy(file_in, argv[6]);
		}
		else
		{
			printf("\ninvalid parameters\n");
			return -1;
		}
	}
	else
	{
	printf("\ninvalid parameters\n");
	return -1;
	}

}
else
{
//printf("\ninvalid parameters\n");
return -1;
}

//printf("file in:%s file out:%s %d\n", file_in, file_out, seed);
/*end parse*/

in_fp = open(file_in, O_RDONLY, 0); //file open to the file the user specified to read from
/*printf("\nopen %d %s \n", in_fp, file_in);*/
out_fp = creat(file_out, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); //file to print to the user specified

//printf("\nopen %d %s\n", out_fp, file_out);

srand(seed); //srand to pass information to the randomnumber generator

byte_number = read(in_fp, buffer_tool.buff_char, 4); //initial read to prevent read errors
/*printf("%d", byte_number);*/

while(byte_number > 0)
{
	key = rand(); //get the key from the random number generator
	//printf("Processing %d bytes\n",byte_number);
	//int i = 0;
	//for (i = 0; i < byte_number; i++)
		//printf("%2.2x ",buffer_tool.buff_char[i]);
	//printf("\n");	
//	printf("%s \n", buffer_tool.buff_char);	
	
	buffer_tool.buff_int = buffer_tool.buff_int ^ key; //cipher

	byte_number = write(out_fp, buffer_tool.buff_char, byte_number); //get the ammount written for debug

	//printf("Outputting %d processed bytes\n",byte_number);
	//for (i = 0; i < byte_number; i++)
		//printf("%2.2x ",buffer_tool.buff_char[i]);
	//printf("\n");	
//	printf("bytes: %d %s\n", byte_number, buffer_tool.buff_char);
	byte_number = read(in_fp, buffer_tool.buff_char, 4); //set the byte number to the correct value for the next iteration
							     //of the loop
	
}

close(in_fp); //close the infile
close(out_fp); //close the outfile

return 0; //exit success
}

