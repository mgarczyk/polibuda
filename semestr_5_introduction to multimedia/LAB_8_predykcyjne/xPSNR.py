import math
import numpy as np

#-----------------------------------------------------------------------------------------------------------------------
# PSNR functions
#-----------------------------------------------------------------------------------------------------------------------
def PSNR(ImageA, ImageB) :
  """ 
  PURPOSE: To find the PSNR (peak signal-to-noise ratio) between two
          intensity images A and B, each having values in the interval
          [0,1]. The answer is in decibels (dB).
          There is also a provision, in EXAMPLE 3 below, for images 
          stored in the interval [0,255], i.e. 256 gray levels. 

  SYNOPSIS: PSNR(A,B)

  DESCRIPTION: The following is quoted from "Fractal Image Compression",
              by Yuval Fisher et al.,(Springer Verlag, 1995),
              section 2.4, "Pixelized Data".
              "...PSNR is used to measure the difference between two
              images. It is defined as

                            PSNR = 20 * log10(b/rms)

              where b is the largest possible value of the signal
              (typically 255 or 1), and rms is the root mean square
              difference between two images. The PSNR is given in
              decibel units (dB), which measure the ratio of the peak 
              signal and the difference between two images. An increase
              of 20 dB corresponds to a ten-fold decrease in the rms
              difference between two images.
                
              There are many versions of signal-to-noise ratios, but
              the PSNR is very common in image processing, probably
              because it gives better-sounding numbers than other
              measures."

  EXAMPLE:  For images with 256 gray levels: this function PSNR was 
            originally written for matrix-values between 0 and 1,
            because of MATLAB's preference for that interval.

            However, suppose the matrix has values in [0,255]. Taking
            Example 1 above, we could change the image to 256 gray levels.
          
            load clown
            A = ind2gray(X,map); % Convert to intensity image in [0,1]
            AA = uint8(255*A);   % Change to integers in [0,255]
            BB = 0.95*AA;        % Make BB close to AA.

            Now we must alter the code for this new case. Comment out the
            existing program (using %) and uncomment the alternative 
            underneath it.

            PSNR(AA,BB)          % ---> "PSNR = +33.56 dB"

            Note the slightly different result from Example 1, because
            decimal values were rounded into integers.
  """
  #PSNR (Peak Signal to noise ratio)
  A = np.array(ImageA)
  B = np.array(ImageB)
  if A.shape != B.shape: print('The size of the 2 matrix are unequal'); return float('NaN') 
  elif (A==B).all()    : print('Images are identical: PSNR has infinite value'); return float('Inf')   
  else:
    MSE = ((A - B)**2).mean() # Calculate MSE, mean square error.
    PSNR = 10 * math.log10(255**2 / MSE) # Calculate PSNR (Peak Signal to noise ratio)
    return PSNR