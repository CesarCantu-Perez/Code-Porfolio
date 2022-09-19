"""Name: Cesar Cantu-Perez
   ID# 1001463763
   Python 3.8.10
   Ubuntu VM """


"""import from dictionaries for use in the recursive function directSize"""
from pathlib import Path
import os

"""start by initializing a variable to hold the path '.' which represents current directory"""
p = Path('.')
"""the function directSize accepts two arguments: the directory and a variable for the size of the directory"""
def directSize(dir, size):
    """uses a for loop to iterate through each directory"""
    for x in dir.iterdir():
        """if x is a directory the program will call the directSize function again this time for the new directory
            and if x is not a directory the program will use the getsize function found in the os dictionary to get the
            and add the size to the current size that was passed into the directSize function  """
        if x.is_dir():
            size = directSize(x, size)
        else:
            fileSize = os.path.getsize(x)
            print(x,' is ',fileSize, 'bytes.')
            size = size + fileSize

    return size

"""program calls the directSize function to find the size of the current directory ('.')"""
directSum = directSize(p, 0)
print('The size of the directory is: ',directSum, 'bytes.')
