//      Tonatiuh2CSV.c
//      
//      Copyright 2011 Pablo Benito <pbenito@cener.com>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


void usage();
double swap(uint64_t);


struct record {

	uint64_t id;
	uint64_t x;
	uint64_t y;
	uint64_t z;
	uint64_t surface;
	uint64_t previousId;
	uint64_t nextId;
	
};

int main(int argc, char** argv)
{
	FILE *inputFile;
	FILE *outputFile;
	
	struct record myRecord;
	uint64_t powerPerPhoton; 
	
	// We need 2 arguments. 
	if (argc!=2) {
		usage(); 
		return -1;
	}
	
	
	inputFile = fopen(argv[1],"rb");
	
	if(inputFile) {
		
		// Read the first 8 bytes, powerPerPhoton
		if(fread(&powerPerPhoton,sizeof(uint64_t),1,inputFile)<=0) {
			fprintf(stderr,"Error: Input file is empty or not readable\n");
			usage();
			return -1;
		};
		
		outputFile = fopen(strcat(argv[1],".csv"),"w");
		if (!outputFile) { 
			fprintf(stderr,"Error writing to output file %s\n",strcat(argv[1],".csv"));
			usage();
			return -1;
		}
		
		fprintf(outputFile,"PowerPerPhoton;%e\n",swap(powerPerPhoton));
		fprintf(outputFile,"Photon ID;x-coordinate;y-coordinate;z-coordinate;surface side;Previous PhotonID;Next PhotonID\n");
		
		// Read the rest of the file. 
		while(!feof(inputFile)) {
			if (fread(&myRecord,sizeof(struct record),1,inputFile)) {
				fprintf(outputFile,"%0.f;%e;%e;%e;%0.f;%0.f;%0.f\n",
					swap(myRecord.id),
					swap(myRecord.x),
					swap(myRecord.y),
					swap(myRecord.z),
					swap(myRecord.surface),
					swap(myRecord.previousId),
					swap(myRecord.nextId));			
				printf("%0.f;%e;%e;%e;%0.f;%0.f;%0.f\n",
					swap(myRecord.id),
					swap(myRecord.x),
					swap(myRecord.y),
					swap(myRecord.z),
					swap(myRecord.surface),
					swap(myRecord.previousId),
					swap(myRecord.nextId));						
			}
		}
		
		// Close the files
		fclose(outputFile);
		fclose(inputFile);
	}
	else {
		printf("Error opening file %s\n",argv[1]);
		usage();
		return -1;
	}
	return 0;
}

// Swap bytes for big-endianness
double swap(uint64_t a) 
{

	double d;
	unsigned char *src = (unsigned char *)&a;
	unsigned char *dst = (unsigned char *)&d;

	dst[0] = src[7];
	dst[1] = src[6];
	dst[2] = src[5];
	dst[3] = src[4];
	dst[4] = src[3];
	dst[5] = src[2];
	dst[6] = src[1];
	dst[7] = src[0];

	return d;
}


void usage() {

	printf("Tonatiuh2CSV\n\n");
	printf("This program converts an output file of Tonatiuh (binary file) to a Comma-separated values (.csv) file\n\n");
	printf("Usage: Tonatiuh2CSV inputFile \n\n");
	printf("Generates a file called inputFile.csv\n\n");
	printf("Author: Pablo Benito (pbenito@cener.com)\n");
	printf("Bugs: Probably... just 20 minutes coding\n");
	return;
	
}
