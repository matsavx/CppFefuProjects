#include <cmath>
#include "ppm.h"
#include "PerlinNoise.h"

int main() {

    unsigned int width = 500, height = 500;

    ppm image(width, height);

    PerlinNoise pn;

    unsigned int kk = 0;

    for(unsigned int i = 0; i < height; ++i) {
        for(unsigned int j = 0; j < width; ++j) {
            double x = (double)j/((double)width);
            double y = (double)i/((double)height);

            double n = pn.noise(10 * x, 10 * y, 0.8);

            n = 20 * pn.noise(x, y, 0.8);
            n = n - floor(n);

            image.r[kk] = floor(255 * n/(rand()%5+1));
            image.g[kk] = floor(255 * n/(rand()%3+1));
            image.b[kk] = floor(255 * n/(rand()%2+1));
            kk++;
        }
    }

    image.write("figure_42_R.ppm");

    return 0;
}