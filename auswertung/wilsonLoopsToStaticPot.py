import numpy as np
import matplotlib.pyplot as plt

dataDir = "../data/"
fileName = "wilsonLoopsFirstRun.txt"

data = np.loadtxt(dataDir + fileName, delimiter=',')
timeLength = data[0,:]
spaceLength = data[1,:]

measurements = data[2:,:]

loopMean = np.average(measurements, axis=0)
loopErr  = np.sqrt(np.var(measurements, axis=0) / np.shape(measurements)[0])



aV = np.log(loopMean[timeLength == np.max(timeLength)-1] / loopMean[timeLength == np.max(timeLength)])
aVerr = np.sqrt()

plt.plot(spaceLength[timeLength == np.max(timeLength)], aV)
plt.show()