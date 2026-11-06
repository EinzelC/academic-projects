# MyImageFunctions.py
# Import pillow
from PIL import Image, ImageOps

# Import numpy
import numpy as np
from numpy import asarray

# For sqrt(), floor()
import math

def myImageResize( inImage_pixels, M, N, interpolation_method ):
    """Resize a grayscale image to M rows by N columns."""
    if inImage_pixels.ndim != 2:
        raise ValueError("inImage_pixels must be a 2-D grayscale image")
    if inImage_pixels.shape[0] == 0 or inImage_pixels.shape[1] == 0:
        raise ValueError("inImage_pixels must not be empty")
    if M <= 0 or N <= 0:
        raise ValueError("M and N must be positive")
    if interpolation_method not in ("nearest", "bilinear"):
        raise ValueError("interpolation_method must be 'nearest' or 'bilinear'")

    input_rows, input_cols = inImage_pixels.shape
    row_scale = input_rows / M
    col_scale = input_cols / N
    outImage_pixels = np.zeros((M, N), dtype=np.float32)

    for row in range(M):
        source_y = row * row_scale
        for col in range(N):
            source_x = col * col_scale

            if interpolation_method == "nearest":
                nearest_y = min(math.floor(source_y + 0.5), input_rows - 1)
                nearest_x = min(math.floor(source_x + 0.5), input_cols - 1)
                outImage_pixels[row, col] = inImage_pixels[nearest_y, nearest_x]
            else:
                x1 = math.floor(source_x)
                y1 = math.floor(source_y)
                x2 = min(x1 + 1, input_cols - 1)
                y2 = min(y1 + 1, input_rows - 1)
                outImage_pixels[row, col] = mybilinear(
                    x1, y1, inImage_pixels[y1, x1],
                    x2, y1, inImage_pixels[y1, x2],
                    x1, y2, inImage_pixels[y2, x1],
                    x2, y2, inImage_pixels[y2, x2],
                    source_x, source_y,
                )

    return outImage_pixels


def myRMSE( first_im_pixels, second_im_pixels ):
    if first_im_pixels.shape != second_im_pixels.shape:
        raise ValueError("images must have the same shape")
    if first_im_pixels.size == 0:
        raise ValueError("images must not be empty")

    squared_error = np.mean((first_im_pixels - second_im_pixels) ** 2)
    return math.sqrt(float(squared_error))


def mybilinear(x1,y1,p1,x2,y2,p2,x3,y3,p3,x4,y4,p4,x5,y5):
    x_weight = 0 if x2 == x1 else (x5 - x1) / (x2 - x1)
    y_weight = 0 if y3 == y1 else (y5 - y1) / (y3 - y1)

    top = p1 * (1 - x_weight) + p2 * x_weight
    bottom = p3 * (1 - x_weight) + p4 * x_weight
    return top * (1 - y_weight) + bottom * y_weight