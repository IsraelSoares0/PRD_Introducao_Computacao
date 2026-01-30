import numpy as np
import matplotlib.pyplot as plt

dados = np.loadtxt('teste-tyto.csv')

plt.plot(dados[:, 0], dados[:, 1])
plt.xlabel('Tempo [ms]')
plt.ylabel('Empuxo')
plt.title('Empuxo do Tyto')

plt.show()