import numpy as np
from control.matlab import *

class pendulum_model():

    M = 0.04
    m = 0.05
    b = 0.1
    L = 0.3048
    l = L/2
    I = 1/12 * M * L * L
    g = 9.8
    
    p = 0
    A = np.zeros((4, 4))
    B = np.zeros((4, 1))
    C = np.zeros((2, 4))
    D = np.zeros((2, 1))

    sys = ss(A, B, C, D)

    def __init__(self):
        self._computeMatrices()

    def _computeMatrices(self):
        self.p = self.I * (self.M + self.m) + self.M * self.m * self.l**2
        
        self.A = np.array( [[0  ,1                                              ,0                                                      ,0],
                            [0  ,-(self.I + self.m * self.l**2)*self.b/self.p   ,(self.m**2 * self.g * self.l**2)/self.p                ,0],
                            [0  ,0                                              ,0                                                      ,1],
                            [0  ,-(self.m * self.l * self.b)/self.p             ,self.m * self.g * self.l * (self.M + self.m)/self.p    ,0]])
        
        self.B = np.array( [[0                                      ],
                            [(self.I + self.m * self.l**2)/self.p   ],
                            [0                                      ],
                            [self.m * self.l/self.p                 ]])

        self.C = np.array( [[1  ,0  ,0  ,0],
                            [0  ,0  ,1  ,0]])

        self.D = np.array( [[0],
                            [0]])

        self.sys = ss(self.A, self.B, self.C, self.D)
    
