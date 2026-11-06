from PIL import Image

original_image = Image.open("Lab_02_image.tif")
img1 = Image.open("upsampled_bilinear.tif")
img2 = Image.open("upsampled_NN.tif")
img3 = Image.open("downsampled_bilinear.tif")
img4 = Image.open("downsampled_NN.tif")

original_image.save("original_image.png")
img1.save("upsampled_bilinear.png")
img2.save("upsampled_nearest.png")
img3.save("downsampled_bilinear.png")
img4.save("downsampled_nearest.png")