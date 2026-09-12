import pandas as pd
import matplotlib.pyplot as plt
import os

#Creacion del directorio si es que no existe, en donde ira el grafico.
os.makedirs("../data/plots", exist_ok=True)
df = pd.read_csv("../data/measurements/results.csv")

res = df.groupby(['Algoritmo', 'N'])['Tiempo_ms'].mean().unstack(level=0)

plt.figure(figsize=(10, 6))
res.plot(marker='s')
plt.title("Tiempo de Ejecución Promedio vs N (Matrix Multiplication)")
plt.xlabel("Dimensión de la Matriz (N)")
plt.ylabel("Tiempo (ms)")
plt.xscale('log', base=2)
plt.yscale('log')
plt.grid(True)

#Exportacion del archivo PNG directamente a la subcarpeta de plots
plt.savefig("../data/plots/matrix_time.png")
plt.close()

#Crea tabla en formato latex para mostrar en el miniinforme.

#Extrae los valores de N evaluados para las columnas
Ns = res.index.tolist()

#Crear la definición de columnas (ej: |l|c|c|c|c|)
col_def = "|l|" + "c|" * len(Ns)

#Generar la cabecera con los valores de N
headers = ["\\textbf{Algoritmo}"] + [f"\\textbf{{$N={int(n)}$}}" for n in Ns]
header_row = " & ".join(headers) + r" \\ \hline"

latex = f"""\\begin{{table}}[htbp]
    \\centering
    \\begin{{tabular}}{{{col_def}}}
    \\hline
    {header_row}
"""

#Iterar sobre las columnas (Algoritmos) e imprimir cada fila
for algoritmo in res.columns:
    row_values = [str(algoritmo)]
    for n in Ns:
        val = res.loc[n, algoritmo]
        if pd.isna(val):
             row_values.append("-")
        else:
             row_values.append(f"{val:.3f}")
             
    latex += "    " + " & ".join(row_values) + r" \\ \hline" + "\n"

latex += r"""    \end{tabular}
    \caption{Tiempos de ejecución (en milisegundos) para multiplicacion de matrices. Se observa que el metodo Naive mantiene tiempos inferiores, demostrando el sobrecosto operativo de Strassen en dimensiones previas al umbral de transicion.}
    \label{tab:matrix_time}
\end{table}
"""

print(latex)