# MyHEFunctions.py

# Import numpy
import numpy as np

def compute_histogram( image_pixels ):
    pixels = np.asarray(image_pixels)
    if pixels.size == 0:
        raise ValueError("image_pixels must not be empty")
    if not np.issubdtype(pixels.dtype, np.number):
        raise TypeError("image_pixels must contain numeric intensities")
    if not np.all(np.isfinite(pixels)):
        raise ValueError("image_pixels must contain only finite intensities")
    if np.any((pixels < 0) | (pixels > 255)):
        raise ValueError("image_pixels intensities must be between 0 and 255")

    bins = np.floor(pixels).astype(np.intp)
    histogram = np.bincount(bins.ravel(), minlength=256).astype(float)
    return histogram / pixels.size

def equalize( in_image_pixels ):
    pixels = np.asarray(in_image_pixels)
    histogram = compute_histogram(pixels)
    intensity_mapping = 255 * np.cumsum(histogram)
    bins = np.floor(pixels).astype(np.intp)
    return intensity_mapping[bins]

def plot_histogram( hist ):
    # Plot the normalized histogram and equalization transform in separate figures.
    #
    # Syntax:
    #   plot_histogram( hist )
    #
    # Input:
    #   hist = The length 256 normalized histogram vector.
    #
    # Output:
    #   none
    #
    # History:
    #   S. Newsam     10/18/2026   created

    # Import plotting functions from matplotlib.
    import matplotlib.pyplot as plt

    histogram = np.asarray(hist)
    if histogram.shape != (256,):
        raise ValueError("hist must be a length 256 histogram")

    intensity_levels = np.arange(256)
    mapping = 255 * np.cumsum(histogram)

    plt.figure()
    plt.bar(intensity_levels, histogram)
    plt.xlabel("Input intensity value")
    plt.ylabel("Probability mass")
    plt.title("Image histogram")

    plt.figure()
    plt.plot(intensity_levels, mapping)
    plt.xlabel("Input intensity value")
    plt.ylabel("Output intensity value")
    plt.title("Histogram equalization transform")
    plt.xlim(0, 255)
    plt.ylim(0, 255)
    plt.grid(True)
    plt.show()
