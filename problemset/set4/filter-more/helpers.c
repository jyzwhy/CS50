#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Sobel operator
BYTE sobel(BYTE color[]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE avar = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen + 1) / 3;

            image[i][j].rgbtBlue = avar;
            image[i][j].rgbtRed = avar;
            image[i][j].rgbtGreen = avar;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][width - j - 1];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = 0, red = 0, green = 0;
            BYTE index = 0;
            for (int k = -1; k < 2 && i + k < height; k++)
            {
                if (i + k < 0)
                {
                    continue;
                }
                for (int l = -1; l < 2 && j + l < width; l++)
                {
                    if (j + l < 0)
                    {
                        continue;
                    }
                    blue += copy[i + k][j + l].rgbtBlue;
                    red += copy[i + k][j + l].rgbtRed;
                    green += copy[i + k][j + l].rgbtGreen;
                    index += 1;
                }
            }

            image[i][j].rgbtBlue = blue / (float) index + 0.5;
            image[i][j].rgbtRed = red / (float) index + 0.5;
            image[i][j].rgbtGreen = green / (float) index + 0.5;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height + 2][width + 2];

    RGBTRIPLE black;

    black.rgbtRed = 0;
    black.rgbtGreen = 0;
    black.rgbtBlue = 0;

    // set black
    for (int i = 0; i < width + 2; i++)
    {
        copy[0][i] = black;
        copy[height + 1][i] = black;
    }

    for (int i = 1; i < height + 1; i++)
    {
        copy[i][0] = black;
        copy[i][width + 1] = black;
    }
    // copy image to the middle
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            copy[i][j] = image[i - 1][j - 1];
        }
    }

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            BYTE red[9], blue[9], green[9];
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    red[3 * (k + 1) + l + 1] = copy[i + k][j + l].rgbtRed;
                    blue[3 * (k + 1) + l + 1] = copy[i + k][j + l].rgbtBlue;
                    green[3 * (k + 1) + l + 1] = copy[i + k][j + l].rgbtGreen;
                }
            }
            image[i - 1][j - 1].rgbtRed = sobel(red);
            image[i - 1][j - 1].rgbtBlue = sobel(blue);
            image[i - 1][j - 1].rgbtGreen = sobel(green);
        }
    }
    return;
}

BYTE sobel(BYTE color[])
{
    int gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1}, sumx = 0;
    int gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1}, sumy = 0;

    for (int i = 0; i < 9; i++)
    {
        sumx += gx[i] * color[i];
        sumy += gy[i] * color[i];
    }

    float x = sumx, y = sumy;

    if (sqrt(x * x + y * y) > 255)
    {
        return 255;
    }
    else
    {
        return (int) (sqrt(x * x + y * y) + 0.5);
    }
}
