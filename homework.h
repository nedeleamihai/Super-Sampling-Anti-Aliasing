#ifndef HOMEWORK_H
#define HOMEWORK_H

typedef struct {
	char color[3];
	int width;
	int height;
	int maxval;
	unsigned char *buffer;
}image;

void readInput(const char * fileName, image *img);

void writeData(const char * fileName, image *img);

void resize(image *in, image * out);

#endif /* HOMEWORK_H */
