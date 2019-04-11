#!/usr/local/anaconda3/bin/python
#Filename:extend.py
import numpy as np

def getPricePathByNumpy(S_0, sigma, tua, steps, simulationTimes, rf):
    dt = tua / steps
    S = np.zeros((steps + 1, simulationTimes))
    S[0] = S_0
    #     np.random.seed(2000)
    for t in range(1, steps + 1):
        z = np.random.standard_normal(simulationTimes)
        S[t] = S[t - 1] * np.exp((rf - 0.5 * sigma ** 2) * dt + sigma * np.sqrt(dt) * z)

    return S