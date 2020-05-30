#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// initilalize the two "kernels" for the sobel operator / edge detection
// Gx
int Gx[3][3] =
{
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};
// Gy
int Gy[3][3] =
{
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}
};

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int value = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtRed = value;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < floor(width / 2); j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
}

/*
Calculates a pixel with a special colour by averaging the colour values of the pixels surrounding it and
the colour value of the pixel itself. In other words, we put a "box" with the center as int row and int column
and calculate the average blue, green, red of all the pixels inside the "box".
int height and int width are the limits of the image.
int amount is the size of the box. If size is 1 then the box is 3x3, if is 2 then 4x4, and so on.
Return: A RGBTRIPLE pixel with the colour values averaging all the pixels inside the "box".
*/
RGBTRIPLE avg_surround(int row, int column, int height, int width, RGBTRIPLE image[height][width], int amount)
{
    RGBTRIPLE result_pixel;

    int blue = 0, green = 0, red = 0;
    // number of pixels inside the "box"
    float counter = 0.0;

    // goes through the "box" on the y axis
    for (int i = row - amount; i <= row + amount; i++)
    {
        // we don't want to go beyond the limits of the image on the y axis
        if (i >= 0 && i < height)
        {
            // goes through the "box" on the x axis
            for (int j = column - amount; j <= column + amount; j++)
            {
                // we don't want to go beyond the limits of the image on the x axis
                if (j >= 0 && j < width)
                {
                    blue += image[i][j].rgbtBlue;
                    green += image[i][j].rgbtGreen;
                    red += image[i][j].rgbtRed;
                    counter++;
                }
            }
        }
    }

    // calculate the average of the each colour value
    result_pixel.rgbtBlue = round(blue / counter);
    result_pixel.rgbtGreen = round(green / counter);
    result_pixel.rgbtRed = round(red / counter);

    return result_pixel;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // allocate in the memory a temporary image
    RGBTRIPLE(*tmp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (tmp == NULL)
    {
        fprintf(stderr, "Can't allocate memory for the temporary image.\n");
    }

    // copy the image to a temporary image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    // blur the image with the help of the temporary image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = avg_surround(i, j, height, width, tmp, 1);
        }
    }

    // free the allocated memory of the temporary image
    free(tmp);
}

/*
Applies the sobel operator logic to a pixel given by int row and int column.
int height and int width are the limits of the image.
Return: A RGBTRIPLE pixel with its colour values changed by the sobel operator logic.
*/
RGBTRIPLE sobel_operator(int row, int column, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE result_pixel;

    // counter for both Gx and Gy "kernels"
    int counter_row = 0, counter_col = 0;
    int gx_blue = 0, gx_green = 0, gx_red = 0, gy_blue = 0, gy_green = 0, gy_red = 0;

    // goes through the 3x3 box on the y axis
    for (int i = row - 1; i <= row + 1; i++)
    {
        // we don't want to go beyond the limits of the image on the y axis
        if (i >= 0 && i < height)
        {
            counter_col = 0;
            // goes through the 3x3 box on the x axis
            for (int j = column - 1; j <= column + 1; j++)
            {
                // we don't want to go beyond the limits of the image on the x axis
                if (j >= 0 && j < width)
                {
                    // using the "kernel" Gx
                    gx_blue += Gx[counter_row][counter_col] * image[i][j].rgbtBlue;
                    gx_green += Gx[counter_row][counter_col] * image[i][j].rgbtGreen;
                    gx_red += Gx[counter_row][counter_col] * image[i][j].rgbtRed;
                    // using the "kernel" Gy
                    gy_blue += Gy[counter_row][counter_col] * image[i][j].rgbtBlue;
                    gy_green += Gy[counter_row][counter_col] * image[i][j].rgbtGreen;
                    gy_red += Gy[counter_row][counter_col] * image[i][j].rgbtRed;
                }
                counter_col++;
            }
        }
        counter_row++;
    }

    int blue = round(sqrt((gx_blue * gx_blue) + (gy_blue * gy_blue)));
    (blue > 255) ? (result_pixel.rgbtBlue = 255) : (result_pixel.rgbtBlue = blue);

    int green = round(sqrt((gx_green * gx_green) + (gy_green * gy_green)));
    (green > 255) ? (result_pixel.rgbtGreen = 255) : (result_pixel.rgbtGreen = green);

    int red = round(sqrt((gx_red * gx_red) + (gy_red * gy_red)));
    (red > 255) ? (result_pixel.rgbtRed = 255) : (result_pixel.rgbtRed = red);

    return result_pixel;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // allocate in the memory a temporary image
    RGBTRIPLE(*tmp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (tmp == NULL)
    {
        fprintf(stderr, "Can't allocate memory for the temporary image.\n");
    }

    // copy the image to a temporary image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    // detect the edges wiht the help of the temporary image and using the sobel operator logic
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = sobel_operator(i, j, height, width, tmp);
        }
    }

    // free the allocated memory of the temporary image
    free(tmp);
}
