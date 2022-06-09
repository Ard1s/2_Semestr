#define _CRT_SECURE_NO_WARNINGS
#include "bitmap.h"

#include "getopt.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>

int iteration_to_color(int i, int max);
int iterations_at_point(double x, double y, int max);
void compute_image(struct bitmap* bm, double xmin, double xmax, double ymin, double ymax, int max);

void show_help()
{
	printf("Use: mandel [options]\n");
	printf("Where options are:\n");
	printf("-m <max>    The maximum number of iterations per point. (default=1000)\n");
	printf("-x <coord>  X coordinate of image center point. (default=0)\n");
	printf("-y <coord>  Y coordinate of image center point. (default=0)\n");
	printf("-s <scale>  Scale of the image in Mandlebrot coordinates. (default=4)\n");
	printf("-W <pixels> Width of the image in pixels. (default=500)\n");
	printf("-H <pixels> Height of the image in pixels. (default=500)\n");
	printf("-o <file>   Set output file. (default=mandel.bmp)\n");
	printf("-h          Show this help text.\n");
	printf("\nSome examples are:\n");
	printf("mandel -x -0.5 -y -0.5 -s 0.2\n");
	printf("mandel -x -.38 -y -.665 -s .05 -m 100\n");
	printf("mandel -x 0.286932 -y 0.014287 -s .0005 -m 1000\n\n");
}

int main(int argc, char* argv[])
{
	char c;

	const char* outfile = "fractal.bmp";
	double xcenter = 0;
	double ycenter = 0;
	double scale = 4;
	int    image_width = 500;
	int    image_height = 500;
	int    max = 1000;



	while ((c = getopt(argc, argv, "x:y:s:W:H:m:o:h")) != -1) 
	{
		switch (c) 
		{
		case 'x':
			xcenter = atof(optarg);
			break;
		case 'y':
			ycenter = atof(optarg);
			break;
		case 's':
			scale = atof(optarg);
			break;
		case 'W':
			image_width = atoi(optarg);
			break;
		case 'H':
			image_height = atoi(optarg);
			break;
		case 'm':
			max = atoi(optarg);
			break;
		case 'o':
			outfile = optarg;
			break;
		case 'h':
			show_help();
			exit(1);
			break;
		}
	}

	printf("mandel: x=%lf y=%lf scale=%lf max=%d outfile=%s\n", xcenter, ycenter, scale, max, outfile);

	struct bitmap* bm = bitmap_create(image_width, image_height);

	bitmap_reset(bm, MAKE_RGBA(0, 0, 255, 0));

	compute_image(bm, xcenter - scale, xcenter + scale, ycenter - scale, ycenter + scale, max);

	if (!bitmap_save(bm, outfile)) 
	{
		fprintf(stderr, "mandel: couldn't write to %s: %s\n", outfile, strerror(errno));
		return 1;
	}

	return 0;
}



void compute_image(struct bitmap* bm, double xmin, double xmax, double ymin, double ymax, int max)
{
	int i, j;

	int width = bitmap_width(bm);
	int height = bitmap_height(bm);


	for (j = 0; j < height; j++) 
	{

		for (i = 0; i < width; i++) 
		{

			double x = xmin + i * (xmax - xmin) / width;
			double y = ymin + j * (ymax - ymin) / height;

			int iters = iterations_at_point(x, y, max);

			bitmap_set(bm, i, j, iters);
		}
	}
}


int iterations_at_point(double x, double y, int max)
{
	double x0 = x;
	double y0 = y;

	int iter = 0;

	while ((x * x + y * y <= 4) && iter < max) 
	{

		double xt = x * x - y * y + x0;
		double yt = 2 * x * y + y0;

		x = xt;
		y = yt;

		iter++;
	}

	return iteration_to_color(iter, max);
}


int iteration_to_color(int i, int max)
{
	int gray = 255 * i / max;
	return MAKE_RGBA(gray, gray, gray, 0);
}
