#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h> // for uint8_t

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

// Function to apply gaussian filter on an image
void gaussianFilter(uint8_t *image, uint8_t *output, int width, int height, int channels, int filterSize, float sigma)
{
    int i, j, k, l;
    float sum, val, weight, totalWeight;
    int halfFilterSize = filterSize / 2;
    float *filter = (float *)malloc(filterSize * filterSize * sizeof(float));
    float *gaussianFilter = (float *)malloc(filterSize * filterSize * sizeof(float));
    totalWeight = 0;

    // Generate the Gaussian filter
    for (i = -halfFilterSize; i <= halfFilterSize; i++)
    {
        for (j = -halfFilterSize; j <= halfFilterSize; j++)
        {
            weight = exp(-(i * i + j * j) / (2 * sigma * sigma));
            filter[(i + halfFilterSize) * filterSize + (j + halfFilterSize)] = weight;
            totalWeight += weight;
        }
    }

    // Normalize the filter
    for (i = 0; i < filterSize; i++)
    {
        for (j = 0; j < filterSize; j++)
        {
            gaussianFilter[i * filterSize + j] = filter[i * filterSize + j] / totalWeight;
        }
    }

    // Apply the filter to the image
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            for (int c = 0; c < channels; c++)
            {
                sum = 0;
                for (k = -halfFilterSize; k <= halfFilterSize; k++)
                {
                    for (l = -halfFilterSize; l <= halfFilterSize; l++)
                    {
                        // Check boundary conditions
                        int row = i + k;
                        int col = j + l;
                        if (row >= 0 && row < height && col >= 0 && col < width)
                        {
                            val = image[(row * width + col) * channels + c];
                        }
                        else
                        {
                            val = 0;
                        }
                        sum += val * gaussianFilter[(k + halfFilterSize) * filterSize + (l + halfFilterSize)];
                    }
                }
                // Store the filtered value at the location of the original pixel
                output[(i * width + j) * channels + c] = (uint8_t)sum;
            }
        }
    }

    // Free memory
    free(filter);
    free(gaussianFilter);
}

int main()
{
    // Load the input image
    int width, height, channels;
    uint8_t *image = stbi_load("input.png", &width, &height, &channels, 0);
    printf("Image width: %dpx\n", width);
    printf("Image height: %dpx\n", height);
    printf("Number of channels: %d\n", channels);

    if (image == NULL)
    {
        printf("Error loading image: %s\n", stbi_failure_reason());
        return 1;
    }

    // Define filter properties
    float sigma = 0.9;
    int filterSize = (int)(2 * 3.14159265359 * sigma); // Approximation of 2 * pi * sigma
    printf("Filter size: %d\n", filterSize);

    // Allocate memory for output image
    uint8_t *output = (uint8_t *)malloc(width * height * channels * sizeof(uint8_t));

    // Apply Gaussian filter
    gaussianFilter(image, output, width, height, channels, filterSize, sigma);

    // Save the processed image
    if (!stbi_write_png("output3.png", width, height, channels, output, width * channels))
    {
        printf("Error writing image: %s\n", stbi_failure_reason());
        return 1;
    }

    // Free memory
    stbi_image_free(image);
    free(output);

    return 0;
}
