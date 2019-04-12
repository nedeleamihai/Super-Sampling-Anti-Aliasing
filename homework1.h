#ifndef HOMEWORK_H1
#define HOMEWORK_H1

typedef struct {
	char color[3];
	int width;
	int maxval;
	unsigned char *buffer;
}image;

void initialize(image *im);
void render(image *im);
void writeData(const char * fileName, image *img);

#endif /* HOMEWORK_H1 */
