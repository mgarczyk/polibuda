# Description

The application recognizes whether there is a human in the given photo, compared with the data set - random protrets can be found on the ThisXDoesNotExist.com website

# Algorithm

- We assume that the size of the image is always the same (we should resize all pictures to some constant size)

- We check the similarity (how many % of the pixels in our picture agree with the examples of the dataset (by RGB colors), with individual colors). OpenCv Library + -80% pixels to count that there is git, every pixel + -10%, firstly we create our own method that compare whole photo pixel by pixel.

- Then we use RMSE method.

- And SSIM method.

- If a given picture is more than 80% correct, then the method return true value.

- Finally, assuming that, for example, 2/3 methods return that the picture is ok, then we write it to the user and add the given photo to the dataset

# Libraries

SEWAR, sckit-image, Tensorflow libraries could will be useful to us.
