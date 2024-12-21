import matplotlib.pyplot as plt
import numpy as np

# Chargement des données
# Assurez-vous que vos fichiers de données sont au bon format et sont accessibles
u_k_data = np.loadtxt("u_k.data")
u_kp1_final_data = np.loadtxt("u_kp1_final.data")
u_ref_exact_data = np.loadtxt("u_ref_exact.data")
#u_kp1_gs_final_data = np.loadtxt("u_kp1_gs_final.data")

# Création de la figure et des axes
plt.figure(figsize=(8, 6))

# Tracer la condition initiale (u_k)
plt.plot(u_k_data[:, 0], u_k_data[:, 1], label="Condition initiale (u_k)", linestyle='-', color='black')

# Tracer la solution numérique Jacobi (u_kp1_final)
plt.plot(u_kp1_final_data[:, 0], u_kp1_final_data[:, 1], label="Jacobi Solution (u_kp1)", linestyle='-', color='blue')

# Tracer la solution exacte (u_ref)
plt.plot(u_ref_exact_data[:, 0], u_ref_exact_data[:, 1], label="Solution exacte (u_ref)", linestyle='-', color='red')

# Tracer la solution Gauss-Seidel (u_kp1_gs_final)
#plt.plot(u_kp1_gs_final_data[:, 0], u_kp1_gs_final_data[:, 1], label="Solution Gauss-Seidel (u_kp1_gs)", linestyle='-', color='green')

# Ajouter des étiquettes aux axes
plt.title("Comparaison des solutions numérique et exacte")
plt.xlabel("x")
plt.ylabel("u(x)")
plt.grid(True)

# Ajouter une légende
plt.legend()

# Sauvegarder l'image
plt.savefig("output.png")

# Afficher le graphique
plt.show()
