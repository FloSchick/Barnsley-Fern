#include "real_consumer.h"
#include <mutex>
#include <vector>
#define cimg_display 0
#define cimg_use_jpeg
#include "CImg.h"

// settings
int img_x = 10000;
int img_y = 20000;
// size of mutex cell in with*height
int cell_size = 1000;
//cell size on img
int cell_count_x = img_x / cell_size;
int cell_count_y = img_y / cell_size;
// mutex array
std::vector<std::mutex> cells(cell_count_x *cell_count_y);
//std::mutex cells[10 * 20];

typedef std::pair<double, double> pair;
cimg_library::CImg<unsigned char> image(img_x, img_y, 1, 3);
cimg_library::CImg<unsigned char> *real_consumer::jpg = &image;

std::mutex mut;

bool real_consumer::consume(pair &data)
{
    int x = ((data.first + 2.2) / 4.9) * img_x;
    int y = (data.second) / 10 * img_y;
    unsigned char increment;
    unsigned char pixel = *jpg->data(x, y, 1);
    if (pixel > 0)
    {
        increment = 0;
    }
    else
    {
        increment = 255;
    }

    unsigned char green[3];
    green[0] = 0;
    green[1] = pixel + increment;
    green[2] = 0;

    // calc mutex number for pixel
    int cell_number_x = x / cell_size;
    int cell_number_y = y / cell_size;
    int mutex_nr = (cell_number_y * cell_count_x) + cell_number_y;
    //increase Pixel
    std::lock_guard<std::mutex> lock(cells[mutex_nr]);
    jpg->draw_point(x, y, green);
    return true;
}

void real_consumer::save_img()
{
    std::lock_guard<std::mutex> lock(mut);
    if (jpg != 0)
    {
        jpg->rotate(180);
        jpg->save_png("farn.png");
        std::cout << "saved img" << std::endl;
        jpg = 0;
    }
}