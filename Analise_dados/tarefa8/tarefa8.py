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

t_queima = (t_fim - t_ini) / 1000
empuxo_medio = np.mean(y_q)
empuxo_max = np.max(y_q)
t_pico = (np.argmax(y_q) + t_ini) / 1000
impulso = np.trapezoid(y_q, x_q * 1e-3)

print("\n----- RESULTADOS PRINCIPAIS -----\n")

print(f"Tempo de queima [s]: {t_queima:.2f}")
print(f"Empuxo medio [N]: {empuxo_medio:.2f}")
print(f"Empuxo maximo [N]: {empuxo_max:.2f}")
print(f"Tempo de pico [s]: {t_pico:.2f}")
print(f"Impulso total [N·s]: {impulso:.2f}\n")