#include <vector>
#include <string>

#ifndef PPM_H
#define PPM_H

class ppm {
    void init();

    unsigned int nr_lines;
    unsigned int nr_columns;

public:

    std::vector<unsigned char> r;
    std::vector<unsigned char> g;
    std::vector<unsigned char> b;

    unsigned int height;
    unsigned int width;
    unsigned int max_col_val{};

    unsigned int size;

    ppm();

    explicit ppm(const std::string &fname);

    ppm(unsigned int _width, unsigned int _height);

    void read(const std::string &fname);

    void write(const std::string &fname);
};

#endif