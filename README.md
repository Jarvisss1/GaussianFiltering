# Gaussian Filter Image Processing

This repository contains C code for applying a Gaussian filter to an input image. The Gaussian filter is a common image processing technique used for smoothing images and reducing noise. The code uses a convolution operation with a Gaussian kernel to perform the filtering. It loads an input image (in PNG format) using the `stb_image` library, applies the Gaussian filter to the image, and saves the processed image as an output PNG file using the `stb_image_write` library.

## Technique Description

The Gaussian filter technique involves convoluting the input image with a Gaussian kernel, which is a weighted matrix that represents a two-dimensional Gaussian distribution. Each element of the kernel represents the contribution of the corresponding pixel's neighborhood to the filtered value of the pixel. By convoluting the image with this kernel and calculating the weighted average of the neighboring elements of each pixel, the filter effectively smoothens the image and reduces noise.

## Features

- Applies Gaussian filter to input image.
- Supports images with multiple channels (e.g., RGB).
- Adjustable parameters: filter size and sigma value.
- Saves processed image as PNG.

## Usage

1. Compile the `gaussianFilteringOnImage.c`file.
2. Run the compiled executable with the input PNG image as an argument.
3. Or run the `gaussianFilteringOnMatrix.c` to apply gaussian filtering on a Matrix rather than image itself 

## Dependencies

- `stb_image`: A single-header library for loading images in various formats.
- `stb_image_write`: A single-header library for writing images in various formats.

