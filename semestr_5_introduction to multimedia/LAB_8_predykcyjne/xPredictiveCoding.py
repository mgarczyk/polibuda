import os
import math
import numpy as np
#-----------------------------------------------------------------------------------------------------------------------
# Quantization functions
#-----------------------------------------------------------------------------------------------------------------------
def QuantScale(Value, Nbits, Range) :
  SignMax = 2**(Nbits-1)-1
  SignMin = -(1+SignMax)
  Q   = 2**Nbits-1
  T   = (Q+1)/(2*Range)
  u   = (Value+Range)*T
  u   = u+SignMin
  return math.floor(u)

def InvScale(Value, Nbits, Range) :
  W = 2**(Nbits-1)
  T = Range*(2**(1-Nbits))
  return (Value+W)*T - Range

def NonUniQuantScale(Value, Nbits, Range, Mu) :
  Value = np.double(Value)
  NUQ   = Range * (math.log10(1+Mu*np.abs(Value)/Range)/math.log10(1+Mu))*np.sign(Value)
  return np.int16(QuantScale(NUQ, Nbits, Range))

def NonUniInvScale(Value, Nbits, Range, Mu) :
  Value = np.double(Value)
  NUDQ = (Range / Mu) * (10**((math.log10(1+Mu)/Range)*np.abs(Value))-1)*np.sign(Value)
  return np.int16(InvScale(NUDQ, Nbits, Range))

def xQuantScale(PredErr, QuantBits=None, NonUniformity=None):
  PredErrQ = QuantScale(PredErr, QuantBits, 255) if NonUniformity==None else NonUniQuantScale(PredErr, QuantBits, 255, NonUniformity) 
  return PredErrQ

def xInvScale(PredErrQ, QuantBits=None, NonUniformity=None):
  PredErrS = InvScale(PredErrQ, QuantBits, 255) if NonUniformity==None else NonUniInvScale(PredErrQ, QuantBits, 255, NonUniformity) 
  return PredErrS

#-----------------------------------------------------------------------------------------------------------------------
# Prediction codig functions
#-----------------------------------------------------------------------------------------------------------------------
def xPredict(PredType, ImgRec, x, y):
  """
  see: https://en.wikipedia.org/wiki/Portable_Network_Graphics
  """
  NoDataVal = np.int16(128)

  if PredType == 0: #no prediction
    PredictionV = 0

  if PredType == 1: #1-point left
    PredictionV = NoDataVal if x==0 else ImgRec[y, x-1]

  elif PredType == 2: #1-point above
    PredictionV = NoDataVal if y==0 else ImgRec[y-1, x]

  elif PredType == 3: #3-point
    if  (x==0 and y==0): PredictionV = NoDataVal
    elif(x==0         ): PredictionV = ImgRec[y-1, x]
    elif(         y==0): PredictionV = ImgRec[y, x-1]
    else               : PredictionV = np.int16(math.floor((ImgRec[y-1, x] + ImgRec[y-1, x-1] + ImgRec[y, x-1]) / 3))

  elif PredType == 4: #Paeth
    if  (x==0 and y==0): PredictionV = NoDataVal
    elif(x==0         ): PredictionV = ImgRec[y-1, x]
    elif(         y==0): PredictionV = ImgRec[y, x-1]
    else: 
      A = ImgRec[y  , x-1]
      B = ImgRec[y-1, x  ]
      C = ImgRec[y-1, x-1]
      p = A + B - C
      ABC = np.asarray([A, B, C])
      idx = (np.abs(ABC - p)).argmin()
      PredictionV = ABC[idx]

  return PredictionV

#-----------------------------------------------------------------------------------------------------------------------

def PredCode(ImgOrg, PredType, QuantBits=None, NonUniformity=None):
  """
  PredErr, ImgErr = PredCode(ImgOrg, PredType, QuantBits=None, NonUniformity=False)
  The function calculates linear prediction error
  Moreover prediction error can be quantized using uniform or nonuniform quantizer
  with different number of quantization levels

  Usage examples :
  PredErr, ImgErr = PredCode(ImgOrg, PredType)
  PredErr, ImgErr = PredCode(ImgOrg, PredType, QuantBits)
  PredErr, ImgErr = PredCode(ImgOrg, PredType, QuantBits, NonUniformity)

  Variables description:
  ImgOrg        : pixel array
  PredType      : 1 - one-point predictor (left)
                  2 - one-point predictor (above)
                  3 - three-point predictor (average)
                  4 - three-point predictor (Paeth)
  QuantBits     : number of bits (number of quantizer levels NQL = 2^QuantBits)
  NonUniformity : nonuniform factor (for uniform/linear: NonUniformity = None)  
  PredErr       : prediction error
  ImgErr        : prediction error arranged as an image in order to be displayed using imshow( )

  PredErr, ImgErr = PredCode(ImgOrg, PredType, QuantBits=None, NonUniformity=False)
  Funkcja wyznaczająca błąd predykcji liniowej.
  Umożliwia również kwantowanie obliczonego błędu predykcji z użyciem kwantyzatora równomiernego 
  lub nierównomiernego z zadaną liczbą poziomów kwantyzacji

  sposób użycia:
  PredErr, ImgErr = PredCode(ImgOrg, PredType)
  PredErr, ImgErr = PredCode(ImgOrg, PredType, QuantBits)
  PredErr, ImgErr = PredCode(ImgOrg, PredType, QuantBits, NonUniformity)

  Opis zmiennych:
  ImgOrg           : zmienna przechowującą obraz wejściowy
  PredType         : 1 - predykcja jednopunktowa (lewy)
                     2 - predykcja jednopunktowa (górny)
                     3 - predykcja trzypunktowa (średnia)
                     4 - predykcja trzypunktowa (algorytm Paeth)
  QuantBits        : liczba bitów (liczba poziomów kwantyzacji NQL = 2^QuantBits)
  NonUniformity    : wspóczynnik nieliniowości kwantyzatora (dla równomiernego/liniowego: NonUniformity = None)
  PredErr          : błąd predykcji
  ImgErr           : błąd predykcji w formacie umożliwiającym wyświetlenie z użyciem imshow( ) 
  """

  NoDataVal = np.int16(128)
  ImgOrgNP  = np.array(ImgOrg,dtype=np.int16)
  Height    = ImgOrgNP.shape[0]
  Width     = ImgOrgNP.shape[1]
  PredErrM  = np.zeros_like(ImgOrgNP)
  ImgRec    = np.zeros_like(ImgOrgNP)
  ImgErr    = np.zeros_like(ImgOrgNP)

  if(PredType != 1 and PredType!=2 and PredType!=3 and PredType!=4):
    print('\nOnly left (1) and three-points (3) prediction is supported!\n\n')
    return None

  if (QuantBits==None):
    for y in range(Height): #loop over Y
      for x in range(Width) : # loop over X
        Pred    = xPredict(PredType, ImgRec, x, y)
        Current = ImgOrgNP[y, x]
        PredErr = Current - Pred
        Recon   = Pred + PredErr
        PredErrM[y, x] = PredErr
        ImgRec  [y, x] = Recon
  else:
    for y in range(Height): #loop over Y
      for x in range(Width) : # loop over X
        Pred     = xPredict(PredType, ImgRec, x, y)
        Current  = ImgOrgNP[y, x]
        PredErr  = Current - Pred
        PredErrQ = xQuantScale(PredErr , QuantBits, NonUniformity)
        PredErrS = xInvScale  (PredErrQ, QuantBits, NonUniformity)
        Recon    = Pred + PredErrS
        PredErrM[y, x] = PredErrQ
        ImgRec  [y, x] = Recon
        ImgErr  [y, x] = PredErrS
  
  if QuantBits==None: ImgErr = PredErrM
  return PredErrM, ImgErr

#-----------------------------------------------------------------------------------------------------------------------

def PredDecode(PredErr, PredType, QuantBits=None, NonUniformity=None):
  """
  ImgRec = PredDecode(PredErr, PredType, QuantBits=None, NonUniformity=None)
  The function calculates linear prediction error
  Moreover prediction error can be quantized using uniform or nonuniform quantizer
  with different number of quantization levels

  Usage examples:
  ImgRec = Preddecode(PredErr, PredType)
  ImgRec = Preddecode(PredErr, PredType, QuantBits)
  ImgRec = Preddecode(PredErr, PredType, QuantBits, NonUniformity)

  Variables description:
  PredErr       : prediction error
  PredType      : 1 - one-point predictor (left)
                  2 - one-point predictor (above)
                  3 - three-point predictor (average)
                  4 - three-point predictor (Paeth)
  QuantBits     : number of bits (number of quantizer levels NQL = 2^QuantBits)
  NonUniformity : nonuniform factor (for uniform/linear: NonUniformity = None)
  ImgRec        : reconstructed image

  ImgRec = PredDecode(PredErr, PredType, QuantBits=None, NonUniformity=None)
  Funkcja rekonstruująca obraz na podstawie błędu predykcji.
  Umożliwia również kwantowanie odwrotne błędu predykcji z użyciem kwantyzatora równomiernego
  lub nierównomiernego z podaną liczbą poziomów kwantyzacji

  Sposób użycia:
  ImgRec = Preddecode(PredErr, PredType)
  ImgRec = Preddecode(PredErr, PredType, QuantBits)
  ImgRec = Preddecode(PredErr, PredType, QuantBits, NonUniformity)

  Opis zmiennych: 
  PredErr          : zmienna zawierająca tablicę błędu predykcji poszczególnych punktów obrazu
  PredType         : 1 - predykcja jednopunktowa (lewy)
                     2 - predykcja jednopunktowa (górny)
                     3 - predykcja trzypunktowa (średnia)
                     4 - predykcja trzypunktowa (algorytm Paeth)
  QuantBits        : liczba bitów (liczba poziomów kwantyzacji NQL = 2^QuantBits)
  NonUniformity    : wspóczynnik nieliniowości kwantyzatora (dla równomiernego/liniowego: NonUniformity = None)
  ImgRec           : zdekodowany obraz
  """

  NoDataVal = np.int16(128)
  PredErrNP = np.array(PredErr,dtype=np.int16)
  Height    = PredErrNP.shape[0]
  Width     = PredErrNP.shape[1]
  ImgRec    = np.zeros_like(PredErrNP)

  if(PredType != 1 and PredType!=2 and PredType!=3 and PredType!=4):
    print('\nOnly left (1) and three-points (3) prediction is supported!\n\n')
    return None

  if (QuantBits==None):
    for y in range(Height): #loop over Y
      for x in range(Width) : # loop over X
        Pred    = xPredict(PredType, ImgRec, x, y)
        PredErr = PredErrNP[y, x]
        Recon   = Pred + PredErr
        ImgRec[y, x] = Recon
  else:
    for y in range(Height): #loop over Y
      for x in range(Width) : # loop over X
        Pred     = xPredict(PredType, ImgRec, x, y)
        PredErrQ = PredErrNP[y, x]
        PredErrS = xInvScale(PredErrQ, QuantBits, NonUniformity)
        Recon    = Pred + PredErrS
        ImgRec[y, x] = Recon

  return ImgRec.clip(0, 255).astype(np.uint8)

#-----------------------------------------------------------------------------------------------------------------------