# Description

-The application recognizes whether there is a human in the given photo, compared with the data set - random protrets can be found on the ThisXDoesNotExist.com website

# Algorithm

-We check if the input is the same as from the dataset.

-We check the similarity (how many % of the pixels in our picture agree with the examples of the dataset (by RGB colors), with individual colors). OpenCv Library + -80% pixels to count that there is git, every pixel + -10%

-We assume that the size of the image is always the same (we should resize all pictures to some constant size)

-If a given case is more than 90% correct, it can be saved to the picture database.

-RMSE method.

-SSIM method.

-SEWAR, Tensorflow, SCI KIT_IMAGE libraries

-Exit - we get the results from both our method, RMSE, SSIM, we determine when it returns match (i.e. that the given image is a human).

-Finally, assuming that, for example, 2/3 algorithms return that there is git, then we write it to the user and add the given photo to the dataset
