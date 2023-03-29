#include <iostream>
#include <random>
#include <vector>
#include <unordered_set>
#include <stack>
#include <fstream>
#include <algorithm>
#include <queue>

/* c++ --version = 23 */
/* [[nodiscard]]: Se usa para indicar que el valor de retorno de una función no debe ignorarse  */
/* cuando realiza una llamada a la función. Si se ignora el valor de retorno, el compilador /// */
/* debe dar una advertencia al respecto. ////////////////////////////////////////////////////// */

class randomNums {
private:
    // Attributes
    int min, max;
public:
    // Constructor
    randomNums(int min, int max) : min(min), max(max) {};

    // Methods
    [[nodiscard]] int getRandom() const {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(gen);
    }

    // Getters & Setters
    [[nodiscard]] int getMin() const {
        return min;
    }

    [[nodiscard]] int getMax() const {
        return max;
    }

    void setMin(int value) {
        min = value;
    }

    void setMax(int value) {
        max = value;
    }
};


class Node {
private:
    // Attributes
    int x;
    int y;
    Node *up;           // [0]
    Node *down;         // [1]
    Node *right;        // [2]
    Node *left;         // [3]
    Node *upLeft;       // [4]
    Node *upRight;      // [5]
    Node *downLeft;     // [6]
    Node *downRight;    // [7]
    Node *parent;
public:
    // Constructor
    Node() : up(nullptr), down(nullptr), right(nullptr), left(nullptr),
             upLeft(nullptr), upRight(nullptr), downLeft(nullptr), downRight(nullptr),
             x(0), y(0) {};

    // Setters & Getters
    void setParent(Node *p){
        parent = p;
    }
    Node* getParent(){
        return parent;
    }
    void setX(int value) {
        x = value;
    }

    void setY(int value) {
        y = value;
    }

    void setUp(Node *node) {
        up = node;
    }

    void setDown(Node *node) {
        down = node;
    }

    void setRight(Node *node) {
        right = node;
    }

    void setLeft(Node *node) {
        left = node;
    }

    void setUpLeft(Node *node) {
        upLeft = node;
    }

    void setUpRight(Node *node) {
        upRight = node;
    }

    void setDownLeft(Node *node) {
        downLeft = node;
    }

    void setDownRight(Node *node) {
        downRight = node;
    }

    [[nodiscard]] int getX() const {
        return x;
    }

    [[nodiscard]] int getY() const {
        return y;
    }

    Node *getUp() {
        return up;
    }

    Node *getDown() {
        return down;
    }

    Node *getRight() {
        return right;
    }

    Node *getLeft() {
        return left;
    }

    Node *getUpLeft() {
        return upLeft;
    }

    Node *getUpRight() {
        return upRight;
    }

    Node *getDownLeft() {
        return downLeft;
    }

    Node *getDownRight() {
        return downRight;
    }
};

struct NetOfNodes {
private:
    // Attributes
    int ROWS;
    int COLS;
    float pBorrado;
    std::vector<std::vector<Node>> net;
    std::vector<std::pair<int, int>> dfsPath;
    std::vector<std::pair<int, int>> bfsPath;
    Node *initNode;
    Node *endNode;
public:
    // Constructor
    NetOfNodes(float pBorrado, int ROWS, int COLS) : net(ROWS, std::vector<Node>(COLS)), initNode(nullptr),
                                                     endNode(nullptr), ROWS(ROWS), COLS(COLS), pBorrado(pBorrado) {
        std::cout << "# Creating the Nodes ..." << std::endl;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                net[i][j].setX(i);
                net[i][j].setY(j);
            }
        }
        std::cout << "# Nodes were created ..." << std::endl;
        std::cout << "# Connecting the Nodes ... " << std::endl;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (i > 0) {
                    // Conectar con el nodo de arriba
                    net[i][j].setUp(&net[i - 1][j]);
                }
                if (i < ROWS - 1) {
                    // Conectar con el nodo de abajo
                    net[i][j].setDown(&net[i + 1][j]);
                }
                if (j > 0) {
                    // Conectar con el nodo de la izquierda
                    net[i][j].setLeft(&net[i][j - 1]);
                }
                if (j < COLS - 1) {
                    // Conectar con el nodo de la derecha
                    net[i][j].setRight(&net[i][j + 1]);
                }
                if (i > 0 && j > 0) {
                    // Conectar con el nodo diagonal de arriba a la izquierda
                    net[i][j].setUpLeft(&net[i - 1][j - 1]);
                }
                if (i > 0 && j < COLS - 1) {
                    // Conectar con el nodo diagonal de arriba a la derecha
                    net[i][j].setUpRight(&net[i - 1][j + 1]);
                }
                if (i < ROWS - 1 && j > 0) {
                    // Conectar con el nodo diagonal de abajo a la izquierda
                    net[i][j].setDownLeft(&net[i + 1][j - 1]);
                }
                if (i < ROWS - 1 && j < COLS - 1) {
                    // Conectar con el nodo diagonal de abajo a la derecha
                    net[i][j].setDownRight(&net[i + 1][j + 1]);
                }
            }
        }
        std::cout << "# Nodes were connected ... " << std::endl;
    };

    // Getters & Setters
    [[nodiscard]] std::vector<std::vector<Node>> getNet() const {
        return net;
    }

    std::pair<int, int> getXyValues(int x, int y) {
        return {net[x][y].getX(), net[x][y].getY()};
    }

    static std::pair<int, int> getXyValues(Node *node) {
        return {node->getX(), node->getY()};
    }

    Node *getInitNode() {
        return initNode;
    }

    Node *getEndNode() {
        return endNode;
    }

    Node *getXyNode(int x, int y) {
        return &net[x][y];
    }

    [[nodiscard]] int getCOLS() const {
        return COLS;
    }

    [[nodiscard]] int getROWS() const {
        return ROWS;
    }

    std::vector<std::pair<int, int>> getPathDFS() {
        sort(dfsPath.begin(), dfsPath.end());
        return dfsPath;
    }

    std::vector<std::pair<int, int>> getPathBFS() {
        sort(bfsPath.begin(), bfsPath.end());
        return bfsPath;
    }


    // Methods
    void setInitEnd() {
        randomNums rd(0, COLS - 1);
        int initX;
        int initY;
        int endX;
        int endY;
        bool sePuedeCrear = false;
        while (!sePuedeCrear) {
            initX = rd.getRandom();
            initY = rd.getRandom();
            endX = rd.getRandom();
            endY = rd.getRandom();
            std::cout << "Generado: " << initX << " " << initY << " " << endX << " " << endY << "\n";
            if ((net[initX][initY].getX() != -1 && net[initX][initY].getY() != -1) &&
                (net[endX][endY].getX() != -1 && net[endX][endY].getY() != -1)) {
                sePuedeCrear = true;
            } else {
                std::cout << "Error en la creacion del nodoInicial o nodoFinal. [Nodo borrado]" << std::endl;
            }
        }
        std::cout << "# Set random Init Node ..." << std::endl;
        initNode = &net[initX][initY];
        std::cout << "# Set random End Node ..." << std::endl;
        endNode = &net[endX][endY];
    }

    void setInitEnd(int initX, int initY, int endX, int endY) {
        bool sePuedeCrear = false;
        while (!sePuedeCrear) {
            if ((net[initX][initY].getX() != -1 && net[initX][initY].getY() != -1) &&
                (net[endX][endY].getX() != -1 && net[endX][endY].getY() != -1)) {
                sePuedeCrear = true;
            } else {
                std::cout << "Error en la creacion del nodoInicial o nodoFinal. [Nodo borrado]" << std::endl;
                std::cout << "Vuelva a ingresar las coordenadas de inicio y de fin" << std::endl;
                std::cout << "x1: ";
                std::cin >> initX;
                std::cout << "y1: ";
                std::cin >> initY;
                std::cout << "x2: ";
                std::cin >> endX;
                std::cout << "y1: ";
                std::cin >> endY;
            }
        }
        std::cout << "# Set random Init Node ..." << std::endl;
        initNode = &net[initX][initY];
        std::cout << "# Set random End Node ..." << std::endl;
        endNode = &net[endX][endY];
    }

    void removeNodes() {
        int totalNodes = ROWS * COLS;
        int numNodesToRemove = (int) ((float) totalNodes * pBorrado);
        std::vector<int> indices(totalNodes);
        for (int i = 0; i < totalNodes; i++) {
            indices[i] = i;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(indices.begin(), indices.end(), gen);
        int numNodesRemoved = 0;
        for (int i = 0; i < totalNodes && numNodesRemoved < numNodesToRemove; i++) {
            int idx = indices[i];
            int row = idx / ROWS;
            int col = idx % COLS;
            if (net[row][col].getUp() != nullptr)
                net[row][col].getUp()->setDown(nullptr);
            if (net[row][col].getDown() != nullptr)
                net[row][col].getDown()->setUp(nullptr);
            if (net[row][col].getLeft() != nullptr)
                net[row][col].getLeft()->setRight(nullptr);
            if (net[row][col].getRight() != nullptr)
                net[row][col].getRight()->setLeft(nullptr);
            if (net[row][col].getUpLeft() != nullptr)
                net[row][col].getUpLeft()->setDownRight(nullptr);
            if (net[row][col].getUpRight() != nullptr)
                net[row][col].getUpRight()->setDownLeft(nullptr);
            if (net[row][col].getDownLeft() != nullptr)
                net[row][col].getDownLeft()->setUpRight(nullptr);
            if (net[row][col].getDownRight() != nullptr)
                net[row][col].getDownRight()->setUpLeft(nullptr);
            net[row][col].setUp(nullptr);
            net[row][col].setDown(nullptr);
            net[row][col].setLeft(nullptr);
            net[row][col].setRight(nullptr);
            net[row][col].setUpLeft(nullptr);
            net[row][col].setUpRight(nullptr);
            net[row][col].setDownLeft(nullptr);
            net[row][col].setDownRight(nullptr);
            net[row][col].setX(-1);
            net[row][col].setY(-1);
            numNodesRemoved++;
        }
    }

    bool DFS() {
        std::stack<Node *> nodesToVisit;
        std::unordered_set<Node *> visitedNodes;
        nodesToVisit.push(initNode);

        while (!nodesToVisit.empty()) {
            Node *currentNode = nodesToVisit.top();
            nodesToVisit.pop();

            /* Si se encuentra el nodo, añade las coordenadas al vector. */
            if (currentNode == endNode) {
                dfsPath.emplace_back(currentNode->getX(), currentNode->getY());
                return true;
            }

            /* Si el nodo fue visitado continua con el siguiente. */
            if (visitedNodes.count(currentNode) > 0) {
                continue;
            }
            /* Marca el nodo como visitado. */
            visitedNodes.insert(currentNode);

            /* Agrega los nodos no visitados a la pila. */
            /* .count: número de ocurrencias de un elemento que existen en el set. */
            if (currentNode->getUp() != nullptr && visitedNodes.count(currentNode->getUp()) == 0) {
                nodesToVisit.push(currentNode->getUp());
            }
            if (currentNode->getDown() != nullptr && visitedNodes.count(currentNode->getDown()) == 0) {
                nodesToVisit.push(currentNode->getDown());
            }
            if (currentNode->getLeft() != nullptr && visitedNodes.count(currentNode->getLeft()) == 0) {
                nodesToVisit.push(currentNode->getLeft());
            }
            if (currentNode->getRight() != nullptr && visitedNodes.count(currentNode->getRight()) == 0) {
                nodesToVisit.push(currentNode->getRight());
            }
            if (currentNode->getUpLeft() != nullptr && visitedNodes.count(currentNode->getUpLeft()) == 0) {
                nodesToVisit.push(currentNode->getUpLeft());
            }
            if (currentNode->getUpRight() != nullptr && visitedNodes.count(currentNode->getUpRight()) == 0) {
                nodesToVisit.push(currentNode->getUpRight());
            }
            if (currentNode->getDownLeft() != nullptr && visitedNodes.count(currentNode->getDownLeft()) == 0) {
                nodesToVisit.push(currentNode->getDownLeft());
            }
            if (currentNode->getDownRight() != nullptr && visitedNodes.count(currentNode->getDownRight()) == 0) {
                nodesToVisit.push(currentNode->getDownRight());
            }

            /* Añade las coordenadas al vector. */
            dfsPath.emplace_back(currentNode->getX(), currentNode->getY());
        }
        return false; /* Si no se encontró el nodo, retorna falso */
    }

    bool BFS() {
        std::queue<Node *> nodesToVisit;
        std::unordered_set<Node *> visitedNodes;
        nodesToVisit.push(initNode);
        while (!nodesToVisit.empty()) {
            Node *currentNode = nodesToVisit.front();
            nodesToVisit.pop();

            /* Si el nodo fue visitado continua con el siguiente. */
            if (visitedNodes.count(currentNode) != 0) {
                continue;
            }

            /* Si se encuentra el nodo, añade las coordenadas al vector. */
            if (currentNode == endNode) {
                bfsPath.emplace_back(currentNode->getX(), currentNode->getY());
                return true;
            }

            /* Se agrega el nodo al conjunto de visitados. */
            visitedNodes.insert(currentNode);

            /* Agregar los nodos que no han sido visitados. */
            if (currentNode->getUp() != nullptr && visitedNodes.count(currentNode->getUp()) == 0) {
                nodesToVisit.push(currentNode->getUp());
            }
            if (currentNode->getDown() != nullptr && visitedNodes.count(currentNode->getDown()) == 0) {
                nodesToVisit.push(currentNode->getDown());
            }
            if (currentNode->getLeft() != nullptr && visitedNodes.count(currentNode->getLeft()) == 0) {
                nodesToVisit.push(currentNode->getLeft());
            }
            if (currentNode->getRight() != nullptr && visitedNodes.count(currentNode->getRight()) == 0) {
                nodesToVisit.push(currentNode->getRight());
            }
            if (currentNode->getUpLeft() != nullptr && visitedNodes.count(currentNode->getUpLeft()) == 0) {
                nodesToVisit.push(currentNode->getUpLeft());
            }
            if (currentNode->getUpRight() != nullptr && visitedNodes.count(currentNode->getUpRight()) == 0) {
                nodesToVisit.push(currentNode->getUpRight());
            }
            if (currentNode->getDownLeft() != nullptr && visitedNodes.count(currentNode->getDownLeft()) == 0) {
                nodesToVisit.push(currentNode->getDownLeft());
            }
            if (currentNode->getDownRight() != nullptr && visitedNodes.count(currentNode->getDownRight()) == 0) {
                nodesToVisit.push(currentNode->getDownRight());
            }
            bfsPath.emplace_back(currentNode->getX(),currentNode->getY());
        }
        return false;   /* Si no se encontró el nodo, retorna falso */
    }
};

void printNet(std::vector<std::vector<Node>> net) {
    for (int i = 0; i < net.size(); i++) {
        for (int j = 0; j < net[0].size(); j++) {
            if (net[i][j].getX() == -1 && net[i][j].getY() == -1) {
                std::cout << ' ' << " ";
            } else {
                std::cout << '0' << " ";
            }
        }
        std::cout << std::endl;
    }
}

void setFileNetDots(std::vector<std::vector<char>> map, Node *init, Node *end, bool dfs_bfs) {
    std::ofstream archivo("../src/data.txt", std::ios::out);
    if (dfs_bfs) {
        /* true = DFS */
        archivo << "DFS" << "\n";
    } else {
        /* false = BFS */
        archivo << "BFS" << "\n";
    }
    archivo << "Inicio: [" << init->getX() << "," << init->getY() << "]" << "\n";
    archivo << "Fin: [" << end->getX() << "," << end->getY() << "]" << "\n";
    int rows = (int) map.size();
    int cols = (int) map[0].size();
    archivo << "COLS: " << rows << "\n";
    archivo << "ROWS: " << cols << "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            archivo << map[i][j];
        }
        archivo << "\n";
    }
}

std::vector<std::vector<char>> setMap(std::vector<std::vector<Node>> net, const std::vector<std::pair<int, int>> &path, Node *init, Node *end) {
    int rows = (int) net.size();
    int cols = (int) net[0].size();
    std::vector<std::vector<char>> map(rows, std::vector<char>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (net[i][j].getX() == -1 && net[i][j].getY() == -1) {
                // Si el valor del nodo tiene coordenadas -1,-1
                map[i][j] = ' ';
            } else {
                // Caso contrario, se considera una ruta.
                map[i][j] = '0';
            }
        }
    }
    for (auto &i: path) {
        map[i.first][i.second] = '+';
    }
    map[init->getX()][init->getY()] = 'A';
    map[end->getX()][end->getY()] = 'B';
    return map;
}


void printXY(std::pair<int, int> xy) {
    std::cout << "[" << xy.first << " " << xy.second << "]" << std::endl;
}

void printXY(Node *xy) {
    std::cout << "[" << xy->getX() << " " << xy->getY() << "]" << std::endl;
}

int main() {

    float porcentajeBorrado;
    bool opBfsDfs;
    int cantidadFilas;
    int cantidadCols;

    std::cout << "Ingrese el porcentaje de nodos a borrar [Ejemplo: 40% = 0.40]:";
    std::cin >> porcentajeBorrado;
    std::cout << "Ingrese la cantidad de filas:";
    std::cin >> cantidadFilas;
    std::cout << "Ingrese la cantidad de cols:";
    std::cin >> cantidadCols;

    NetOfNodes test(0.40, cantidadFilas, cantidadCols);
    test.removeNodes(); // Elimina un porcentaje de nodos.
    // printNet(test.getNet());

    test.setInitEnd();
    std::cout << "Inicio:\n";
    printXY(NetOfNodes::getXyValues(test.getInitNode()));
    std::cout << "Fin:\n";
    printXY(NetOfNodes::getXyValues(test.getEndNode()));
    std::cout << "BFS = 0, DFS = 1\n";
    std::cin >> opBfsDfs;

    /*
     * BFS = false
     * DFS = true
     */

    if (opBfsDfs) {
        std::cout << "DFS\n";
        if (test.DFS()) {
            /*for(auto i : test.getPathDFS()) {
                std::cout  << i.first << " " << i.second << " ";
            }*/

            setFileNetDots(setMap(test.getNet(), test.getPathDFS(), test.getInitNode(), test.getEndNode()),
                           test.getInitNode(), test.getEndNode(), true);
        } else {
            std::cout << "No se encontro el camino" << std::endl;
        }

    } else if (!opBfsDfs) {
        std::cout << "BFS\n";
        if (test.BFS()) {
            /*for(auto i : test.getPathBFS()) {
                std::cout  << i.first << " " << i.second << " ";
            }*/
            setFileNetDots(setMap(test.getNet(), test.getPathBFS(), test.getInitNode(), test.getEndNode()),
                           test.getInitNode(), test.getEndNode(), false);
        } else {
            std::cout << "No se encontro el camino" << std::endl;
        }
    } else {
        /* ERROR */
        std::cout << "Opcion incorrecta.\n";
    }

    return 0;
}
