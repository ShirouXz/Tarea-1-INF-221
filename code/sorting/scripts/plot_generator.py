import pandas as pd
import matplotlib.pyplot as plt
import os

os.makedirs("../data/plots", exist_ok=True)
df = pd.read_csv("../data/measurements/results.csv")

#Filtra para los N >= 1000
#Filtra la columna 'T' para utilizar unicamente la distribucion 'aleatorio'
df_filtrado = df[(df['N'] >= 1000) & (df['T'] == 'aleatorio')]

#Agrupar por Algoritmo y N calculando el promedio de tiempo
res = df_filtrado.groupby(['Algoritmo', 'N'])['Tiempo_ms'].mean().unstack(level=0)

#permite visualizar la diferencia de pendientes entre los 4 algoritmos.
plt.figure(figsize=(12, 8))

#engrosa las lineas y evita la superposicion
res.plot(marker='o', linewidth=2.5, markersize=8, ax=plt.gca())

#colocar titulos de eje x e y y titulo general
plt.title("Tiempo de Ejecución Promedio vs N (Sorting - Caso Aleatorio)")
plt.xlabel("Tamaño del Arreglo (N)")
plt.ylabel("Tiempo (ms)")

#Eje X logaritmico para las dimensiones, Eje Y lineal para marcar el contraste
plt.xscale('log')
plt.yscale('linear')
plt.grid(True)

#Guarda el grafico en la carpeta de plots.
plt.savefig("../data/plots/sorting_time.png", bbox_inches='tight')
plt.close()

#Ahora crear tabla latex que mida tiempo de ejecucion de algoritmo por cantidad de elementos de un arreglo

#conversion de ms a segundos para mayor legibilidad en dimensiones grandes
res_segundos = res / 1000.0

#Extraer los valores de N evaluados para las columnas
Ns = res_segundos.index.tolist()

#crear la definicion de columnas (ej: |l|c|c|c|)
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
for algoritmo in res_segundos.columns:
    row_values = [algoritmo]
    for n in Ns:
        val = res_segundos.loc[n, algoritmo]
        if pd.isna(val):
             row_values.append("-")
        else:
             row_values.append(f"{val:.3f}")
             
    latex += "    " + " & ".join(row_values) + r" \\ \hline" + "\n"

latex += r"""    \end{tabular}
    \caption{Tiempos de ejecucion (en segundos) para algoritmos de ordenamiento (Distribucion Aleatoria).}
    \label{tab:sorting_time}
\end{table}
"""
#Muestra por consola el codigo latex de la tabla a pegar.
print(latex)