// Drzewo zwracajace liczbe roznych elementow na przedziale
const int T = 1 << 18;
struct Per_Seg_Tree{
private:
  struct Node{
    int suma;
    Node* L;
    Node* P;

    Node(int _suma, Node* _L, Node* _P) : suma(_suma), L(_L), P(_P) {}
    Node(){}
  };
  
  vector<Node*> tree;
  vector<int> poz_tree_dla_czasu; // na ktorej pozycji jest wskaznik do roota w odpowiednim czasie
  map<int, int> ostatnia_pozycja; 

  void add_tree(Node* node, int poz, int val, int dol = 0, int gora = T - 1){
    if(dol == gora){
      tree.push_back(new Node(node -> suma + val, nullptr, nullptr));
      return;
    }

    int mid = (dol + gora) / 2;
    if(poz <= mid){
      add_tree(node -> L, poz, val, dol, mid);
      tree.push_back(new Node(node -> suma + val, tree.back(), node -> P));
    }
    else{
      add_tree(node -> P, poz, val, mid + 1, gora);
      tree.push_back(new Node(node -> suma + val, node -> L, tree.back()));
    }
  }
  
  int ask_tree(Node * node, int a, int b, int dol = 0, int gora = T - 1){
    if(b < dol or gora < a or a > b)
      return 0;
    if(a <= dol and gora <= b)
      return node -> suma;
    int mid = (dol + gora) / 2;
    return ask_tree(node -> L, a, b, dol, mid) + ask_tree(node -> P, a, b, mid + 1, gora);
  }

  void add(int poz, int val){
    if(ostatnia_pozycja.count(val))
      add_tree(tree.back(), ostatnia_pozycja[val], -1);
    ostatnia_pozycja[val] = poz;
    add_tree(tree.back(), poz, 1);
  }

public:
  void init(vector<int> t){
    int n = t.size();
    tree.resize(T * 2);
    for(int i = T; i < T * 2; i++)
      tree[i] = new Node(0, nullptr, nullptr);

    for(int i = T - 1; i > 0; i--)
      tree[i] = new Node(0, tree[i * 2], tree[i * 2 + 1]);

    //Swapuje miejscami wskazniki korzenia i ostatniego liscia, bo chce zeby korzen byl na koncu wektora
    swap(tree[1], tree.back());
    poz_tree_dla_czasu.push_back(tree.size() - 1);

    for(int i = 0; i < n; i++){
      add(i, t[i]);
      poz_tree_dla_czasu.push_back(tree.size() - 1);
    }
  }

  int ask(int pocz, int kon){
    return ask_tree(tree[poz_tree_dla_czasu[kon + 1]], pocz, kon);
  }
};
