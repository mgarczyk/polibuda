# Description

The application recognizes whether there is a human in the given photo, compared with the data set - random protrets can be found on the ThisXDoesNotExist.com website

# Algorithm

- We have to create the dataset with examples. 

- Then assume that the size of the image is always the same (we should resize all pictures to some constant size).

- Firstly we should create the method that check the similarity (how many of the pixels in our picture agree with the same pixels on the pictures from the dataset (by RGB colors)). 

- Then we use RMSE method.

- And SSIM method.

- If a given picture is more than 80% correct, then the method return true value.

- Finally, assuming that, for example, 2/3 methods return that the picture is ok, then we write it to the user and add the given photo to the dataset.

# Libraries

SEWAR, sckit-image, Tensorflow libraries could will be useful to us.
