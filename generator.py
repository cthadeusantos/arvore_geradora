import networkx as nx
import numpy as np

# func create, write and close the file
def writeFile(fileName, order, mat):
    f = open(fileName, "w")
    f.write(str(order) + "\n")
    for row in mat:
        linha = ""
        for value in row:
            linha += str(value) + " "
        f.write(linha + "\n")
    f.close()

# --- Dados de Entrada -------------
# Dados para o grafo bi partido
BPG_n = 10
BPG_m = 5
BPG_p = 0.6
BPG_name = "gb_" + str(BPG_n) + "_" + str(BPG_m) + "_" + str(BPG_p) + ".txt"
BPG_path = "HeuristicsAND_ExactParallel2/grafos_bi_partido/"


# Dados para o grafo barabasi albert
BAG_n = 10
BAG_m = 6
BAG_name = "gba_" + str(BAG_n) + "_" + str(BAG_m) + ".txt"
BAG_path = ""

# Dados para o grafo Watts Strogatz
WSG_n = 30
WSG_k = 3
WSG_p = 0.8
WSG_name = "gws_" + str(WSG_n) + "_" + str(WSG_k) + "_" + str(WSG_p) + ".txt"
WSG_path = ""

# Dados para o grafo Erdos Reny
ERG_n = 20
ERG_p = 0.4
ERG_name = "ger_" + str(ERG_n) + "_" + str(ERG_p) + ".txt"
ERG_path = ""

# --- Construção dos grafos -------------------------
BiPartidGraph = nx.bipartite.random_graph(BPG_n, BPG_m, BPG_p)
BarabasiGraph = nx.generators.random_graphs.barabasi_albert_graph(BAG_n, BAG_m)
WattsGraph = nx.generators.random_graphs.connected_watts_strogatz_graph(WSG_n, WSG_k, WSG_p)
ErdosGraph = nx.gnp_random_graph(ERG_n, ERG_p)

# Construção das matrizes de adjacência
matBiPartid = nx.adjacency_matrix(BiPartidGraph).todense()
matBarabasiGraph = nx.adjacency_matrix(BarabasiGraph).todense()
matWattsGraph = nx.adjacency_matrix(WattsGraph).todense()
matErdosGraph = nx.adjacency_matrix(ErdosGraph).todense()

# Escreve nos arquivos
writeFile(BPG_path + BPG_name, BiPartidGraph.order(), matBiPartid.A)
writeFile(BAG_path + BAG_name, BarabasiGraph.order(), matBarabasiGraph.A)
writeFile(WSG_path + WSG_name, WattsGraph.order(), matWattsGraph.A)
writeFile(ERG_path + ERG_name, ErdosGraph.order(), matErdosGraph.A)
