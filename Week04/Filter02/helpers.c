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

int cap(int value)
{
    return value < 255 ? value : 255;
}

RGBTRIPLE get_edge(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{ -1, 0, 1}, { -2, 0, 2}, { -1, 0, 1}};
    int rValueX, gValueX, bValueX, rValueY, gValueY, bValueY;
    rValueX = gValueX = bValueX = rValueY = gValueY = bValueY = 0;
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            if (valid_pixel(i + di, j + dj, height, width))
            {
                int weightX = Gx[di + 1][dj + 1];
                rValueX += weightX * image[i + di][j + dj].rgbtRed;
                gValueX += weightX * image[i + di][j + dj].rgbtGreen;
                bValueX += weightX * image[i + di][j + dj].rgbtBlue;

                int weightY = Gx[dj + 1][di + 1];
                rValueY += weightY * image[i + di][j + dj].rgbtRed;
                gValueY += weightY * image[i + di][j + dj].rgbtGreen;
                bValueY += weightY * image[i + di][j + dj].rgbtBlue;
            }
        }
    }
    RGBTRIPLE pixel;
    pixel.rgbtRed = cap(round(sqrt(rValueX * rValueX + rValueY * rValueY)));
    pixel.rgbtBlue = cap(round(sqrt(bValueX * bValueX + bValueY * bValueY)));
    pixel.rgbtGreen = cap(round(sqrt(gValueX * gValueX + gValueY * gValueY)));
    return pixel;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_img[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_img[i][j] = get_edge(i, j, height, width, image);
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
