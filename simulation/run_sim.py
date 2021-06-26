
import pendulum_model as pm
from control.matlab import *
import numpy as np
import matplotlib.pyplot as plt

def _computeLqrGains(system):
    Q = system.C.transpose().dot(system.C) 
    R = 1
    K, S, E = lqr(system, Q, R)

    return K

def _adjointSystem(system):
    K = _computeLqrGains(system)
    Ac = system.A - system.B.dot(K)
    Bc = system.B
    Cc = system.C
    Dc = system.D

    newSys = ss(Ac, Bc, Cc, Dc)

    return newSys

def main():

    pend_model = pm.pendulum_model()
    updated_sys = _adjointSystem(pend_model)

    t_max = 10

    t = np.linspace(0, t_max, t_max*100+1)
    r = 0.2*np.ones(np.size(t))

    yout, tout, xout = lsim(updated_sys, r, t)

    plt.plot(tout, yout[:,0], tout, yout[:,1])
    plt.show()
    plt.savefig("test.png")

    return


if __name__ == "__main__":
    main()