#buscar y leer archivos 
import os 
import glob
#para buscar textos especificos
import re
import matplotlib.pyplot as plt #para los graficos
from collections import defaultdict #es para ahorrarme los if para ir cadena a cadena y asi este los crea sin darme error xd 

def parse_measurements():
    #nos ayuda a organizar lo que sale del .txt siendo visualmente algo asi [tipo][dominio][algo (de algoritmo xd)][n]
    times_data = defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: defaultdict(list))))
    mem_data = defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: defaultdict(list))))
    
    for filepath in glob.glob('../data/measurements/*.txt'): #para tarer todos los txt
        #lo uso para borrarle el txt y asi sabe que algoritmo es
        algo = os.path.basename(filepath).replace('.txt', '') 
        
        with open(filepath, 'r') as f: #abre el algoritmo y lo lee 
            current_filename = ""
            for line in f:
                if ".txt:" in line: #leera el archivo por dentro y buscara algo escrito con un .txt luego nos guarda ese nombre en el current_filename
                    current_filename = line.split(':')[0].strip()
                #si encuentra la linea tardo: 
                elif "tardo:" in line and current_filename:
                    #separa las partes del current con un _ "10000000_aleatorio_D1_a" que seria "n_tipo_dominio"
                    parts = current_filename.split('_')
                    if len(parts) >= 4:
                        n = int(parts[0])
                        tipo = parts[1]
                        dominio = parts[2]
                        
                        time_match = re.search(r'tardo:\s*(\d+)\s*us', line) #buscamos con re en la linea
                        mem_match = re.search(r'memoria usada:\s*(\d+)\s*KB', line)
                        
                        if time_match and mem_match:
                            times_data[tipo][dominio][algo][n].append(int(time_match.group(1))) #le pegamos el tiempo 
                            mem_data[tipo][dominio][algo][n].append(int(mem_match.group(1))) #le pegamos la memoria
                            
    return times_data, mem_data

def generar_graficos(data, metrica, ylabel):
    #le decimos creame la carpeta... pero si existe que la deje ahí
    os.makedirs('../data/plots', exist_ok=True)
    
    for tipo in data:
        for dominio in data[tipo]:
            #creo un cuadro de 10x6 para cada tipo y dominio
            plt.figure(figsize=(10, 6))
            
            #aca empiezo a crear las curvas
            for algo in data[tipo][dominio]:
                ns = sorted(list(data[tipo][dominio][algo].keys())) #ordeno de menor a mayor
                promedios = [sum(data[tipo][dominio][algo][n]) / len(data[tipo][dominio][algo][n]) for n in ns] #genero la lista final de promedios
                
                #en el eje x pone los ns y en el Y los promedios
                plt.plot(ns, promedios, marker='o', label=algo)
            
            #es para los titulos
            plt.title(f'{metrica} - Arreglo {tipo.capitalize()} ({dominio})')
            plt.xlabel('Tamaño del arreglo (n)')
            plt.ylabel(ylabel)
            #uso escala log para q se vea mas linda y todo feo 
            plt.xscale('log')
            plt.yscale('log')
            #hace el cuadro q pone de que color es cada linea
            plt.grid(True, which="both", ls="--", alpha=0.5)
            plt.legend()
            
            filename = f'../data/plots/{metrica.lower()}_{tipo}_{dominio}.png'
            plt.savefig(filename, bbox_inches='tight')
            plt.close() #cierra el cuadro para no crear el otro grafico encima xd

if __name__ == '__main__':
    tiempos, memorias = parse_measurements()
    generar_graficos(tiempos, "Tiempos", "Tiempo de ejecución (us)")
    generar_graficos(memorias, "Memoria", "Uso de RAM (KB)")
    print("¡Gráficos de ordenamiento generados con éxito en data/plots/!")