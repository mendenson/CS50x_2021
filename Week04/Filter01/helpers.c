#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int average = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }

}

int ole(int value)
{
    return value > 255 ? 255 : value;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int red_ = pixel.rgbtRed;
            int blue_ = pixel.rgbtBlue;
            int green_ = pixel.rgbtGreen;
            image[i][j].rgbtRed = ole(round(0.393 * red_ + 0.769 * green_ + 0.189 * blue_));
            image[i][j].rgbtGreen = ole(round(0.349 * red_ + 0.686 * green_ + 0.168 * blue_));
            image[i][j].rgbtBlue = ole(round(0.272 * red_ + 0.534 * green_ + 0.131 * blue_));
        }
    }
}

void der(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    RGBTRIPLE temp = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            der(&image[i][j], &image[i][width - 1 - j]);
        }
    }
    return;
}

bool valid_pixel(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}

RGBTRIPLE get_blurred(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int rValue, bValue, gValue;
    rValue = bValue = gValue = 0;
    int validPixels = 0;
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            int i_ = i + di;
            int j_ = j + dj;
            if (valid_pixel(i_, j_, height, width))
            {
                validPixels++;
                rValue += image[i_][j_].rgbtRed;
                bValue += image[i_][j_].rgbtBlue;
                gValue += image[i_][j_].rgbtGreen;
            }
        }
    }
    RGBTRIPLE blurred_pixel;
    blurred_pixel.rgbtRed = round((float) rValue / validPixels);
    blurred_pixel.rgbtGreen = round((float) gValue / validPixels);
    blurred_pixel.rgbtBlue = round((float) bValue / validPixels);
    return blurred_pixel;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_img[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_img[i][j] = get_blurred(i, j, height, width, image);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_img[i][j];
        }
    }
}
