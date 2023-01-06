import numpy as np
import collections
import heapq
import copy

#-----------------------------------------------------------------------------------------------------------------------
# Huffmann codig functions
#-----------------------------------------------------------------------------------------------------------------------
class xHuffTree:
  def __init__(self, Value, Count, Left=None, Right=None):
    if(Value != None):
      self.Value = Value
      self.Count = int(Count)
      self.Left  = None
      self.Right = None
    else:
      self.Value = None
      self.Count = Left.Count + Right.Count
      self.Left  = Left
      self.Right = Right
    return  
  def __lt__(self, other): return (self.Count < other.Count)

def __init__(self):
  self.HuffmanTree = []
  return

#-----------------------------------------------------------------------------------------------------------------------

def xHuffmanTree(Vals):
  HuffmanTree = []
  #insert values
  for Val, Count in Vals.items():
    heapq.heappush(HuffmanTree, xHuffTree(Val, Count, None, None))
  #build tree
  while len(HuffmanTree)>1:
    L = heapq.heappop(HuffmanTree)
    R = heapq.heappop(HuffmanTree)
    heapq.heappush(HuffmanTree, xHuffTree(None, None, L,R))    
  return HuffmanTree[0]

#-----------------------------------------------------------------------------------------------------------------------

def xGenerateCode(Node:xHuffTree, Code, Length):
  CodeTable = {}
  if(not Node.Left and not Node.Right):
    CodeTable[Node.Value] = Code
  else:
    CodeTable.update(xGenerateCode(Node.Left , Code+"0", Length+1))
    CodeTable.update(xGenerateCode(Node.Right, Code+"1", Length+1))
  return CodeTable

#-----------------------------------------------------------------------------------------------------------------------

def HuffmanCodeBook(Vals):
  Tree     = xHuffmanTree(Vals)
  CodeBook = xGenerateCode(Tree, "", 0)
  return CodeBook

#-----------------------------------------------------------------------------------------------------------------------

def HuffmanEncode(CodeBook, Data):
  CodeSymbols = [CodeBook[D] for D in Data]
  Code = "".join(CodeSymbols)
  return Code

#-----------------------------------------------------------------------------------------------------------------------

def HuffmanDecode(CodeBook, CodeStr01, UseEndOfData = False):
  InvCodeBook = {Code: Value for Value, Code in CodeBook.items()}
  
  Decoded = []
  TmpCodes = copy.copy(CodeStr01)
  CurrCode = ""
  while(len(TmpCodes)):
    OneBit = TmpCodes[0]
    TmpCodes = TmpCodes[1:]
    CurrCode += OneBit
    if CurrCode in InvCodeBook:
      Value    = InvCodeBook[CurrCode]
      if UseEndOfData and Value == "END": break
      CurrCode = ""
      Decoded.append(Value)

  return Decoded

#-----------------------------------------------------------------------------------------------------------------------

#def StringOfZerosOnesToBytes(StringOfZerosOnes):
#  Bits  = bitarray.bitarray(StringOfZerosOnes)
#  Bytes = Bits.tobytes()
#  return Bytes

#def BytesToStringOfZerosOnes(Bytes):
#  Bits = bitarray.bitarray()
#  Bits.frombytes(Bytes)
#  StringOfZerosOnes = Bits.to01()
#  return StringOfZerosOnes

#-----------------------------------------------------------------------------------------------------------------------

def HuffmanCodeBits(ImgData):
  """
  Huffman coding - calculates the average number of bits per symbol (sample)

  Usage:
  BitsPerSample = HuffmanCodeBits (ImgData)

  Variables description:
  ImgData       : vector/array of samples to be encoded
  BitsPerSample : average number of bits per symbol (sample)

  Kodowanie Huffmana

  Sposób użycia:
  BitsPerSample = HuffmanCodeBits(ImgData)

  Variables description:
  ImgData       : wektor/macierz próbek do zakodowania
  BitsPerSample : średnia liczba bitów na symbol
  """

  DataIn  = np.array(ImgData).ravel()
  Counts  = collections.Counter(DataIn)
  Book    = HuffmanCodeBook(Counts)
  Code    = HuffmanEncode(Book, DataIn)
  CodeLen = len(Code)
  DataLen = len(DataIn)
  BitsPerSample = CodeLen / DataLen
  return BitsPerSample

#-----------------------------------------------------------------------------------------------------------------------