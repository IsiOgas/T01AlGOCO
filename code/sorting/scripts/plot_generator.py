import os
import glob
import re
import matplotlib.pyplot as plt
from collections import defaultdict

def parse_measurements():
    times_data = defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: defaultdict(list))))
    mem_data = defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: defaultdict(list))))
    
    for filepath in glob.glob('../data/measurements/*.txt'):
        algo = os.path.basename(filepath).replace('.txt', '')
        
        with open(filepath, 'r') as f:
            current_filename = ""
            for line in f:
                # leemos y guardamos el nombre del archivo
                if ".txt:" in line:
                    current_filename = line.split(':')[0].strip()
                #extraemos los datos en la siguiente linea
                elif "tardo:" in line and current_filename:
                    parts = current_filename.split('_')
                    if len(parts) >= 4:
                        n = int(parts[0])
                        tipo = parts[1]
                        dominio = parts[2]
                        
                        time_match = re.search(r'tardo:\s*(\d+)\s*us', line)
                        mem_match = re.search(r'memoria usada:\s*(\d+)\s*KB', line)
                        
                        if time_match and mem_match:
                            times_data[tipo][dominio][algo][n].append(int(time_match.group(1)))
                            mem_data[tipo][dominio][algo][n].append(int(mem_match.group(1)))
                            
    return times_data, mem_data

def generar_graficos(data, metrica, ylabel):
    os.makedirs('../data/plots', exist_ok=True)
    
    for tipo in data:
        for dominio in data[tipo]:
            plt.figure(figsize=(10, 6))
            
            for algo in data[tipo][dominio]:
                ns = sorted(list(data[tipo][dominio][algo].keys()))
                promedios = [sum(data[tipo][dominio][algo][n]) / len(data[tipo][dominio][algo][n]) for n in ns]
                
                plt.plot(ns, promedios, marker='o', label=algo)
            
            plt.title(f'{metrica} - Arreglo {tipo.capitalize()} ({dominio})')
            plt.xlabel('Tamaño del arreglo (n)')
            plt.ylabel(ylabel)
            plt.xscale('log')
            plt.yscale('log')
            plt.grid(True, which="both", ls="--", alpha=0.5)
            plt.legend()
            
            filename = f'../data/plots/{metrica.lower()}_{tipo}_{dominio}.png'
            plt.savefig(filename, bbox_inches='tight')
            plt.close()

if __name__ == '__main__':
    tiempos, memorias = parse_measurements()
    generar_graficos(tiempos, "Tiempos", "Tiempo de ejecución (us)")
    generar_graficos(memorias, "Memoria", "Uso de RAM (KB)")
    print("¡Gráficos de ordenamiento generados con éxito en data/plots/!")