
#include <iostream>
#include <cstdlib>

#include "CImg.h"

using namespace cimg_library;
using namespace std;


int derivate_forward(int fx, int fx_next, int dx){
    return (fx_next - fx) / dx;
}
int derivate_backward(int fx,int fx_back,int dx){
    return (fx - fx_back) / dx;
}
int derivate_central(int fx_next, int fx_back, int dx){
    return (fx_next - fx_back) / (2 * dx);
}

int main() {
    CImg<unsigned char> img("city.pgm");

    int w = img.width();
    int h = img.height(); 

    CImg<unsigned char> edge_x(w,h,1,1);
    CImg<unsigned char> edge_y(w,h,1,1);
    CImg<unsigned char> edge_xy(w,h,1,1);
    CImg<unsigned char> malha(w,h, 1, 1);
    //ative caso queira suavizar a imagem
    //img.blur(1);


    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            int pixel_value;
            if(x == 0){
                pixel_value = derivate_forward(img(x, y), img(x + 1, y), 1);
            }
            else if(x == w - 1){
                pixel_value = derivate_backward(img(x, y), img(x - 1, y), 1);
            }
            else{
                pixel_value = derivate_central(img(x + 1, y), img(x - 1, y), 1);
            }
            if(pixel_value < 0){
                pixel_value *= (-1);
            }
            //limite para ser ou não considerada uma aresta
            if(pixel_value > 50)
                edge_x(x, y) = 255;
            else
                edge_x(x, y) = 0;
            malha(x, y)  = pixel_value;


            if(y == 0){
                pixel_value = derivate_forward(img(x, y), img(x , y + 1), 1);
            }
            else if(y == h - 1){
                pixel_value = derivate_backward(img(x, y), img(x , y - 1), 1);
            }
            else{
                pixel_value = derivate_central(img(x, y + 1), img(x , y - 1), 1);
            }
            if(pixel_value < 0){
                pixel_value *= (-1);
            }
            //limite para ser ou não considerada uma aresta
            if(pixel_value > 50)
                edge_y(x, y) = 255;
            else
                edge_y(x, y) = 0;

            if(edge_x(x, y) == 255 ||  edge_y(x, y) == 255)
                edge_xy(x, y) = 255;
            else
                edge_xy(x, y) = 0;
        }
    }


    CImgDisplay original(img, "Original");
    malha.display("edges in the x axis");

    edge_x.display("edges in the x axis");
    edge_y.display("edges in the y axis");
    edge_xy.display("edges in both axis");
}