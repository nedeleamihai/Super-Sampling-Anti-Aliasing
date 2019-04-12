#include "homework1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>

int num_threads;
int resolution;
image *imt;

void initialize(image *im) {
	memcpy(im->color, "P5", 3 * sizeof(char));
	im->width = resolution;
	im->maxval = 255;
	im->buffer = (unsigned char*)malloc(im->width * im->width * sizeof(unsigned char));	
	memset(im->buffer, 255, im->width * im->width * sizeof(unsigned char));
	imt = im;
}

void* threadFunction(void *var){
	float x, y, LungimeBloc = 100 / (float)imt->width;
	int i, j;
	
	int thread_id = *(int*)var;	
	int intervalSize = ceil((float)imt->width/num_threads);
	int low = thread_id * intervalSize;
	int high = fmin((thread_id + 1) * intervalSize, imt->width);
	
	for(i = low; i < high; i++){
		for(j = 0; j < imt->width; j++){
			x = (float)j * LungimeBloc + LungimeBloc / 2;
			y = 100 - (float)i * LungimeBloc - LungimeBloc / 2 ;
			
			float l = abs((-1) * x + 2 * y) / sqrt(5);			
			if(l < 3){
				imt->buffer[i * imt->width + j] = 0;
			}
		}
	}
	
	return NULL;
}

void render(image *im) {
	
	pthread_t tid[num_threads];
	int thread_id[num_threads];
	int i;
	
	for(i = 0; i < num_threads; i++){
		thread_id[i] = i;
	}

	for(i = 0; i < num_threads; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < num_threads; i++) {
		pthread_join(tid[i], NULL);
	}
	
	im = imt;
}

void writeData(const char * fileName, image *img) {
	FILE *f = fopen(fileName, "wb");

    	fprintf (f, "%s\n", img->color);
    	fprintf (f, "%d %d\n", img->width, img->width);
    	fprintf (f, "%d\n", img->maxval);

    	fwrite(img->buffer, img->width * img->width * sizeof(unsigned char), 1, f);
    	fclose(f);
}

