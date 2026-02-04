import numpy as np
import matplotlib.pyplot as plt

def normalizar(yraw):
    return -4.51e-3 * yraw + 37900

# Queima entre 163250 e 164000
dados = np.loadtxt('teste-tyto.csv')

# Intervalo da queima
t_ini = 163300
t_fim = 163850

x = dados[:, 0]
y = normalizar(dados[:, 1])

mask = (x >= t_ini) & (x <= t_fim)

x_q = x[mask]
y_q = y[mask]

plt.plot(x_q, y_q)
plt.xlabel('Tempo [ms]')
plt.ylabel('Empuxo')
plt.title('Empuxo do Tyto')

plt.show()