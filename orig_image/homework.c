#include "homework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

int num_threads;
int resize_factor;
int numcolors = 1;
int width;
int height;
image outt;
unsigned char *greyscale = NULL;
unsigned char *red = NULL;
unsigned char *green = NULL;
unsigned char *blue = NULL;

void readInput(const char * fileName, image *img) {
	char color[3];
	int maxval, LungimeImagine;
	
	//Citeste din fileName
	FILE *f = fopen(fileName, "rb");	
	fscanf(f, "%s", color);
	fscanf(f, "%d", &width);
	fscanf(f, "%d", &height);
	fscanf(f, "%d\n", &maxval);
	
	LungimeImagine = width * height;
	if(strcmp(color, "P6") == 0){
		numcolors = 3;
		red = (unsigned char *)malloc(sizeof(unsigned char) * LungimeImagine);	
		green = (unsigned char *)malloc(sizeof(unsigned char) * LungimeImagine);	
		blue = (unsigned char *)malloc(sizeof(unsigned char) * LungimeImagine);
		LungimeImagine *= 3;
	}
	
	greyscale = (unsigned char *)malloc(sizeof(unsigned char) * LungimeImagine);	
	fread(greyscale, sizeof(unsigned char), LungimeImagine, f);
	
	//Scrie datele in img	
	memcpy(img->color, color, 3 * sizeof(char));
	img->width = width;
	img->height = height;
	img->maxval = maxval;
	img->buffer = (unsigned char*)malloc(LungimeImagine * sizeof(unsigned char));
	memcpy(img->buffer, greyscale, LungimeImagine * sizeof(unsigned char));
	
	fclose(f);
}

void writeData(const char * fileName, image *img) {
	FILE *f = fopen(fileName, "wb");

    	fprintf (f, "%s\n", img->color);
    	fprintf (f, "%d %d\n", img->width, img->height);
    	fprintf (f, "%d\n", img->maxval);

    	fwrite(img->buffer, img->width * img->height * numcolors * sizeof(unsigned char), 1, f);
    	fclose(f);
}

void* threadFunction(void *var){
	
	int x, y, i, j, lin, col;
	int s;
	int GK[3][3] = {{1, 2, 1},{2, 4, 2},{1, 2, 1}};
	int dimensiune = resize_factor * resize_factor;
	
	int thread_id = *(int*)var;	
	int intervalSize = ceil((float)outt.height/num_threads);
	int low = thread_id * intervalSize;
	int high = fmin((thread_id + 1) * intervalSize, outt.height);	
	
	for(x = low; x < high; x++){
		for(y = 0; y < outt.width; y++){
			s = 0;
			if(resize_factor == 3){
				for(i = x * resize_factor; i < (x + 1) * resize_factor; i++){
					lin = i % 3;
					for(j = y * resize_factor; j < (y + 1) * resize_factor; j++){
						col = j % 3;
						s += greyscale[i * width + j] * GK[lin][col];
					}
				}		
				outt.buffer[x * outt.width + y] = s / 16;
			}else{
				for(i = x * resize_factor; i < (x + 1) * resize_factor; i++){
					for(j = y * resize_factor; j < (y + 1) * resize_factor; j++){
						s += (int)(greyscale[i * width + j]);
					}
				}
				outt.buffer[x * outt.width + y] = (unsigned char)(s / dimensiune);
			}
				
		}
	}
	
	return NULL;
}

void resize(image *in, image * out) { 
	memcpy(out->color, in->color, 3 * sizeof(char));
	out->width = in->width/resize_factor;
	out->height = in->height/resize_factor;
	out->maxval = in->maxval;
	int i, j, LungimeImagine = out->width * out->height * numcolors;
	out->buffer = (unsigned char*)malloc(LungimeImagine * sizeof(unsigned char));
	
	memcpy(outt.color, out->color, 3 * sizeof(char));	
	outt.width = out->width;
	outt.height = out->height;
	outt.maxval = out->maxval;
	outt.buffer = (unsigned char*)malloc(LungimeImagine * sizeof(unsigned char));
	
	if(numcolors == 3){
		for(i = 0; i < height; i++){
			memcpy(red + i * width, greyscale + 3 * i * width, width * sizeof(unsigned char));
			memcpy(green + i * width, greyscale + (3 * i + 1) * width, width * sizeof(unsigned char));
			memcpy(blue + i * width, greyscale + (3 * i + 2) * width, width * sizeof(unsigned char));
		}
	}	
	
	pthread_t tid[num_threads];
	int thread_id[num_threads];
	
	for(i = 0; i < num_threads; i++){
		thread_id[i] = i;
	}

	for(i = 0; i < num_threads; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < num_threads; i++) {
		pthread_join(tid[i], NULL);
	}	
	
	for(i = 0; i < LungimeImagine; i++){
		out->buffer[i] = outt.buffer[i];
	}	
	
}
