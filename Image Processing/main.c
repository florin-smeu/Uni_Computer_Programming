#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmp_header.h"

#define MAX_NAME_SIZE 50

struct pixel {
	unsigned char b, g, r;
};

int main(void)
{
	FILE *file;
	
	short height, width, padding_size, i, j, k, p, q, x, y, aux;
	
	int filters[3][3][3] = {{{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}}, 
				{{0, 1, 0}, {1, -4, 1}, {0, 1, 0}}, 
				{{1, 0, -1}, {0, 0, 0}, {-1, 0, 1}}};
	
	char image_name_bmp[MAX_NAME_SIZE], image_name_bw[MAX_NAME_SIZE];
	char image_name_filters[3][MAX_NAME_SIZE];
	char image_compressed[MAX_NAME_SIZE];
	
	struct bmp_fileheader fileheader;
	struct bmp_infoheader infoheader;
	struct pixel **matrix, **matrix_grey;
	struct pixel aux_pixel;
	
	//Read input file
	file = fopen("input.txt", "rt");
	
	if (file == NULL) {
		fprintf(stderr, "ERROR READING input.txt!\n");
		return 1;
	}
	
	fscanf(file, "%s", image_name_bmp);
	fscanf(file, "%hd", &aux);
	fscanf(file, "%s", image_compressed);
	fscanf(file, "%s", image_compressed);
	fclose(file);
	
	//Compute file names
	strcpy(image_name_bw, image_name_bmp);
	
	for (i = 0; image_name_bw[i] != '\0'; i++) {
		if (image_name_bw[i] == '.') {
			image_name_bw[i] = '\0';
			break;
		}
	}
	
	strcpy(image_name_filters[0], image_name_bw);
	strcpy(image_name_filters[1], image_name_bw);
	strcpy(image_name_filters[2], image_name_bw);
	
	strcat(image_name_bw, "_black_white.bmp");
	strcat(image_name_filters[0], "_f1.bmp");
	strcat(image_name_filters[1], "_f2.bmp");
	strcat(image_name_filters[2], "_f3.bmp");

	//Read bitmap
	
	//Read bmp file's header
	file = fopen(image_name_bmp, "rb");
	
	if (file == NULL) {
		fprintf(stderr, "ERROR READING bmp!\n");
		return 1;
	}
	
	fread(&fileheader, sizeof(struct bmp_fileheader), 1, file);
	fread(&infoheader, sizeof(struct bmp_infoheader), 1, file);
	fseek(file, fileheader.imageDataOffset, SEEK_SET);
	
	//Allocate matrices 
	height = infoheader.height;
	width = infoheader.width;
	
	matrix = malloc(height * sizeof(struct pixel *));
	matrix_grey = malloc(height * sizeof(struct pixel *));
	
	for (i = 0; i < height; i++) {
		matrix[i] = malloc(width * sizeof(struct pixel));
		matrix_grey[i] = malloc(width * sizeof(struct pixel));
	}
	
	padding_size = 0;
	
	while ((width * 3 + padding_size) % 4 != 0) {
		 padding_size++;
	}
	
	for (i = height - 1; i >= 0; i--) {
		for (j = 0; j < width; j++) {
			fread(&matrix[i][j], sizeof(struct pixel), 1, file);
		}
	}
	
	fclose(file);

	//Task1 - Black and white

	//Compute pixel values
	for (i = 0; i < height; ++i) {
		for (j = 0; j < width; j++) {
			aux = (matrix[i][j].r + matrix[i][j].g + 
			       matrix[i][j].b) / 3;
			matrix_grey[i][j].r = aux;
			matrix_grey[i][j].g = aux;
			matrix_grey[i][j].b = aux;
		}
	}
	
	//Write black and white bmp file's header
	file = fopen(image_name_bw, "wb");
	
	fwrite(&fileheader, sizeof(struct bmp_fileheader), 1, file);
	fwrite(&infoheader, sizeof(struct bmp_infoheader), 1, file);
	fseek(file, fileheader.imageDataOffset, SEEK_SET);
	
	//Write black and white bmp file's matrix
	for (i = height - 1; i >= 0; i--) {
		for (j = 0; j < width; j++) {
			fwrite(&matrix_grey[i][j], sizeof(struct pixel), 1,
			       file);
		}
		fseek(file, padding_size, SEEK_CUR);
	}
	
	fclose(file);

	//Task 2 - Filters

	//There are 3 filters to be applied
	for (k = 0; k < 3; k++) {

		//Write filtered bmp file's header
		file = fopen(image_name_filters[k], "wb");
		
		fwrite(&fileheader, sizeof(struct bmp_fileheader), 1, file);
		fwrite(&infoheader, sizeof(struct bmp_infoheader), 1, file);
		fseek(file, fileheader.imageDataOffset, SEEK_SET);
		
		//Compute filtered values of pixels and write them 
		for (i = height - 1; i >= 0; i--) {
			for (j = 0; j < width; j++) {
				aux = 0;
				for (p = 0; p < 3; p++) {
					for (q = 0; q < 3; q++) {
						x = j + q - 1;
						y = i + p - 1;
						
						if (x >= 0 && y >= 0 &&
						    x < width && y < height) {
							aux += matrix_grey[y][x].r * filters[k][p][q];
						}
					}
				}
				
				if (aux < 0) aux = 0;
				if (aux > 255) aux = 255;
				
				aux_pixel.r = aux;
				aux_pixel.g = aux;
				aux_pixel.b = aux;
				
				fwrite(&aux_pixel, sizeof(struct pixel), 1, 
				       file);
			}
			fseek(file, padding_size, SEEK_CUR);
		}
		fclose(file);
	}

	//Task 4 - Decompress

	//Read compressed bmp file's header
	file = fopen(image_compressed, "rb");
	
	if (file == NULL) {
		fprintf(stderr, "ERROR READING bmp!\n");
		return 1;
	}
	
	fread(&fileheader, sizeof(struct bmp_fileheader), 1, file);
	fread(&infoheader, sizeof(struct bmp_infoheader), 1, file);
	fseek(file, fileheader.imageDataOffset, SEEK_SET);
	
	height = infoheader.height;
	width = infoheader.width;
	padding_size = 0;
	
	while ((width * 3 + padding_size) % 4 != 0) {
		padding_size++;
	}
	
	do {	
		fread(&y, sizeof(short), 1, file);
		fread(&x, sizeof(short), 1, file);
		fread(&aux_pixel.r, 1, 1, file);
		fread(&aux_pixel.g, 1, 1, file);
		fread(&aux_pixel.b, 1, 1, file);
		
		for (i = x - 1; i < width; i++) {
			 matrix[y - 1][i] = aux_pixel;
		}
	}
	while (x != width ||  y != height);
	
	//Write decompressed bmp file's header
	file = fopen("decompressed.bmp", "wb");
	fwrite(&fileheader, sizeof(struct bmp_fileheader), 1, file);
	fwrite(&infoheader, sizeof(struct bmp_infoheader), 1, file);
	fseek(file, fileheader.imageDataOffset, SEEK_SET);
	
	//Write decompressed bmp file's matrix
	for (i = height - 1; i >= 0; i--) {
		for (j = 0; j < width; j++) {
			fwrite(&matrix[i][j], sizeof(struct pixel), 1, file);
		}
		fseek(file, padding_size, SEEK_CUR);
	}
	fclose(file);

	return 0;
}
