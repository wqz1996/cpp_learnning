from subprocess import list2cmdline
import numpy as np

list2 = [0, 1, 0, 0, 3, 0, 0, 5]

print(list2[np.flatnonzero(list2)[0]])

print(list2[np.flatnonzero(list2)[-1]])