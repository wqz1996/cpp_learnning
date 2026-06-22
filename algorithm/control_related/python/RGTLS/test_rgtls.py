#!/usr/bin/env python3
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import logging
import pandas as pd

XN = 2  # system state number
ObservNum = 1  # system observer number
ControlNum = 1  #system control number
logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.INFO)

file_path = '/home/wu/debug_file/20240119T083129_pdb-l4e-b0002_18_635to1235/data.txt'
data = pd.read_csv(file_path,
                   sep=" ",
                   header=None,
                   engine='python',
                   names=["Label", "Value"])

y_data = data[data['Label'] == 'y']
phi_0_0_data = data[data['Label'] == 'phi_0_0']
phi_0_1_data = data[data['Label'] == 'phi_0_1']

y_val = y_data['Value']
phi_0_0_val = phi_0_0_data['Value']
phi_0_1_val = phi_0_1_data['Value']

FIG_CONFIG = {
    'figsize': (25, 20),
    'dpi': 80,
    'fontsize': 12,
    'subplots_adjust_left': 0.08,
    'subplots_adjust_bottom': 0.06,
    'subplots_adjust_right': 0.92,
    'subplots_adjust_top': 0.95,
    'subplots_adjust_wspace': 0.15,
    'subplots_adjust_hspace': 0.20,
}

Param = {}
noise_covariance = 0.1
p = [0.0001, 0.01, 0.001]
forget_factor = 0.999


class RGTLS:

    def __init__(self):
        self._state = np.mat(np.zeros((XN, 1)))
        self._K = np.mat(np.zeros((XN + 1, 1)))
        self._P = np.mat(np.zeros((XN + 1, XN + 1)))
        np.fill_diagonal(self._P, p)
        self._V = np.mat(np.zeros((XN + 1, 1)))
        self._Z = np.mat(np.zeros((XN + 1, 1)))
        self._P_r = np.mat(np.eye(XN + 1)) * noise_covariance
        self._last_P = np.mat(np.zeros((XN + 1, XN + 1)))
        self._F = np.mat(np.zeros((XN + 1, XN + 1)))

    def Update(self, y, phi):
        #print("start update")
        state = self._state
        K = self._K
        P = self._P
        V = self._V
        Z = self._Z
        last_P = self._last_P
        F = self._F
        P_r = self._P_r

        Z[:XN, 0] = np.mat(phi).T
        Z[XN, 0] = np.mat(y)
        #print("matrix Z: \n", Z)
        K = P * Z / (1 + Z.T * P * Z)
        #print("matrix K: \n", K)
        beta = forget_factor - (1 - forget_factor) / (Z.T * P * Z)
        #print("beta: \n", beta)
        F = np.mat(np.eye(XN + 1)) - (1 - beta.item()) * Z * Z.T * P
        #print("matrix F: \n", F)
        last_P = P * np.linalg.pinv(F)
        #print("matrix last_P: \n", last_P)
        #print("matrix P(k-1): \n", P)
        P = last_P - (last_P * Z * Z.T * last_P) / (1 + Z.T * last_P * Z)
        #print("matrix P(k): \n", P)
        #print("matrix P_r: \n", P_r)
        V[:XN, 0] = state
        V[XN, 0] = -1
        #print("matrix V(k-1): \n", V)
        V = P * P_r * V
        #print("matrix V(k): \n", V)

        state = -V[:XN] / V[XN, 0]
        #print("V[:XN] \n", V[:XN])
        #print("V[XN, 0] \n", V[XN, 0])
        #print("before bounded | matrix state(k): \n", state)
        # state[0][0] = max(-100.0, min(state[0][0].item(), 100.0))
        # state[1][0] = max(15000.0, min(state[1][0].item(), 50000.0))

        self._state = state
        self._K = K
        self._P = P
        self._V = V
        self._Z = Z
        self._last_P = last_P
        self._F = F

    def SetInitState(self, state):
        self._state = state


if __name__ == '__main__':
    #print("main function")
    state_0_to_plot = []
    state_1_to_plot = []
    rgtls = RGTLS()
    init_state = np.mat([[80.0], [35000.0]])
    #print("init state: %%", init_state)
    rgtls.SetInitState(init_state)
    count = 0
    for i, j, k in zip(y_val, phi_0_0_val, phi_0_1_val):
        count += 1
        y = i
        phi = np.mat([j, k])
        #print("count {} y {} phi_0_0 {} phi_0_1 {}".format(count, i, j, k))
        rgtls.Update(y, phi)
        state_0_to_plot.append(rgtls._state[0][0].item())
        state_1_to_plot.append(rgtls._state[1][0].item())
        #print("Update state: \n", rgtls._state)
        #print("state_0", rgtls._state[0][0].item())
        #print("state_1", rgtls._state[1][0].item())
    plt.subplot(2, 1, 1)
    plt.plot(state_0_to_plot, label='state_0')
    plt.title("state_0")
    plt.legend()
    plt.grid()

    plt.subplot(2, 1, 2)
    plt.plot(state_1_to_plot, label='state_1')
    plt.legend()
    plt.grid()
    plt.show()
