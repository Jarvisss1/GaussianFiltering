#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Gaussian Denoising on an Image Matrix using a 3x3 Gaussian Filter

// Function to apply gaussian filter on an image
void gaussianFilter(int *image, int *output, int width, int height, int filterSize, float sigma)
{
    int i, j, k, l;
    float sum, val, weight, totalWeight;
    int halfFilterSize = filterSize / 2;
    float *filter = (float *)malloc(filterSize * filterSize * sizeof(float));
    float *gaussianFilter = (float *)malloc(filterSize * filterSize * sizeof(float));
    float pi = 3.14159265359;
    float e = 2.71828182846;
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

    // Print the Gaussian filter
    printf("Gaussian Filter:\n");
    for (i = 0; i < filterSize; i++)
    {
        for (j = 0; j < filterSize; j++)
        {
            printf("%f ", gaussianFilter[i * filterSize + j]);
        }
        printf("\n");
    }
    printf("\n");

    // Apply the filter to the image
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            sum = 0;
            for (k = -halfFilterSize; k <= halfFilterSize; k++)
            {
                for (l = -halfFilterSize; l <= halfFilterSize; l++)
                {
                    // Check boundary conditions
                    if (i + k >= 0 && i + k < height && j + l >= 0 && j + l < width)
                    {
                        val = image[(i + k) * width + (j + l)];
                        
                    }
                    else
                    {
                        val = 0;
                    }
                    sum += val * gaussianFilter[(k + halfFilterSize) * filterSize + (l + halfFilterSize)];
                }
            }
            output[i * width + j] = (int)sum; // Store the filtered value
        }
    }

    // Free memory
    free(filter);
    free(gaussianFilter);
}

int main()
{
    // Define image properties
    int width = 10;
    int height = 10;

    float sigma = 2.0;
    float pi = 3.14159265359;
    //int filterSize = 3;
    int filterSize = (int)(2 * pi * sigma);
    printf("filterSize: %d\n", filterSize);

    printf("for sigma = %f\n", sigma);

    // Sample input image
    int image[100] = {
        120, 150, 110, 130, 140, 120, 125, 130, 135, 140,
        125, 255, 120, 140, 125, 130, 140, 135, 145, 120,
        130, 120, 130, 140, 150, 120, 110, 135, 130, 125,
        140, 150, 140, 130, 120, 125, 135, 130, 125, 120,
        150, 140, 135, 120, 130, 140, 130, 125, 120, 130,
        130, 125, 130, 140, 150, 140, 135, 130, 125, 120,
        140, 135, 140, 120, 130, 120, 130, 140, 150, 130,
        125, 120, 130, 140, 130, 125, 120, 140, 130, 150,
        120, 250, 120, 130, 140, 150, 130, 125, 254, 130,
        130, 125, 130, 140, 130, 125, 120, 130, 140, 150};

    // Allocate memory for output image
    int *output = (int *)malloc(width * height * sizeof(int));

    // Print the input image
    printf("Input Image:\n");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%3d ", image[i * width + j]);
        }
        printf("\n");
    }
    printf("\n");

    // Apply Gaussian filter
    gaussianFilter(image, output, width, height, filterSize, sigma);

    // Print the filtered image
    printf("Filtered Image:\n");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%3d ", output[i * width + j]);
        }
        printf("\n");
    }

    // Free memory
    free(output);

    return 0;
}
