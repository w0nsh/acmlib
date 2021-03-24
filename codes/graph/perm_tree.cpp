#include<bits/stdc++.h>
using namespace std;

#define f first
#define s second
#define pb push_back
#define sz(s) (int)s.size()

struct Perm_tree{
    struct Node{
        int lo, hi, pocz, kon, id;
        int parent = -1;
        vector<int> sons;
        bool cut;

        Node(int l, int h, int p, int k, int i, bool c = false) : lo(l), hi(h), pocz(p), kon(k), id(i), cut(c) {}
    };
    
    struct Seg_tree{
        int T = 1;
        vector<pair<int, int> > tree;
        vector<int> ids, lazy;

        Seg_tree(int n){
            while(n + 7 > T)
                T *= 2;

            tree.resize(T * 2);
            lazy.resize(T * 2);
            for(int i = 0; i < T; i++)
                tree[i + T].s = i;
            for(int i = T - 1; i >= 1; i--)
                tree[i].s = tree[i + i + 1].s;
        }

        int first_zero(int pocz, int kon, int v, int lo, int hi){
            push(v);
            if(kon < pocz)
                return -1;
            if(hi < pocz or kon < lo)
                return -1;

            if(pocz <= lo and hi <= kon)
                return tree[v].f == 0 ? tree[v].s : -1;

            int mid = (lo + hi) / 2;
            int prawo = first_zero(pocz, kon, v * 2 + 1, mid + 1, hi);
            
            if(prawo != -1)
                return prawo;
            return first_zero(pocz, kon, v * 2, lo, mid);
        }

        int first_zero(int pocz, int kon){
            int ans = first_zero(pocz, kon, 1, 0, T - 1);
            return ans;
        }

        void push(int v){
            tree[v].f += lazy[v];
            if(v < T){
                lazy[v * 2] += lazy[v];
                lazy[v * 2 + 1] += lazy[v];
            }
            lazy[v] = 0;
        }

        void add(int pocz, int kon, int val, int v, int lo, int hi){
            push(v);
            if(kon < pocz)
                return;
            if(hi < pocz or kon < lo)
                return;

            if(pocz <= lo and hi <= kon){
                lazy[v] += val;
                push(v);
                return;
            }

            int mid = (lo + hi) / 2;
            add(pocz, kon, val, v * 2, lo, mid);
            add(pocz, kon, val, v * 2 + 1, mid + 1, hi);
            
            tree[v].f = max(tree[v * 2].f, tree[v * 2 + 1].f);
            tree[v].s = (tree[v].f == tree[v * 2 + 1].f ? tree[v + v + 1].s : tree[v + v].s);
        }

        void add(int pocz, int kon, int val){
            add(pocz, kon, val, 1, 0, T - 1);
        }

        int ask_max(int pocz, int kon, int v, int lo, int hi){
            push(v);
            if(hi < pocz or kon < lo)
                return -1e9;

            if(pocz <= lo and hi <= kon)
                return tree[v].f;

            int mid = (lo + hi) / 2;
            return max(ask_max(pocz, kon, v * 2, lo, mid),
                       ask_max(pocz, kon, v * 2 + 1, mid + 1, hi));
        }

        int ask_max(int pocz, int kon){
            return ask_max(pocz, kon, 1, 0, T - 1);
        }
    };

    vector<Node> tree;
    int Root;
    vector<int> gdzie;

    vector<vector<int> > skoki;
    vector<int> preorder;
    vector<int> postorder;
    int cnt = 0;

    bool jest_przodkiem(int a, int b){
        return preorder[a] <= preorder[b] and postorder[a] >= postorder[b];
    }

    void dfs(int start){
        preorder[start] = cnt++;

        for(auto & u : tree[start].sons)
            dfs(u);

        postorder[start] = cnt++;
    }

    int LOG = 0;

    void prep_LCA(){
        postorder.resize(sz(tree));
        preorder.resize(sz(tree));
        dfs(Root);

        while((1 << LOG) < sz(tree))
            LOG++;
        LOG++;
        skoki = vector<vector<int> >(sz(tree), vector<int> (LOG));

        for(int i = 0; i < sz(tree); i++)
            skoki[i][0] = tree[i].parent;

        for(int poz = 1; poz < LOG; poz++)
            for(int i = 0; i < sz(tree); i++)
                skoki[i][poz] = skoki[skoki[i][poz - 1]][poz - 1];
    }

    pair<int, pair<int, int> > LCA(int a, int b){ // podaję pozycje z vec indeksowane od 0 !!! 
        // funkcja zwraca pozycję noda w tree, który jest LCA i z niego można odczytać poz i kon;
        // drugi element pary, to bezpośredni potomkowie LCA na ścieżkach z a i b

        a = gdzie[a], b = gdzie[b];
        if(jest_przodkiem(a, b))
            return {a, {a, a}};
        if(jest_przodkiem(b, a))
            return {b, {b, b}};
        
        for(int poz = LOG - 1; poz >= 0; poz--)
            if(!jest_przodkiem(skoki[a][poz], b))
                a = skoki[a][poz];

        for(int poz = LOG - 1; poz >= 0; poz--)
            if(!jest_przodkiem(skoki[b][poz], a))
                b = skoki[b][poz];

        return {skoki[a][0], {a, b}};
    }

    pair<int, int> min_good(int a, int b){
        pair<int, pair<int, int> > pom = LCA(a, b);
        if(tree[pom.f].cut)
            return {tree[pom.f].pocz, tree[pom.f].kon};
        return {tree[pom.s.f].pocz, tree[pom.s.s].kon};
    }

    Perm_tree(vector<int> vec){
        // vec musi być permutacją 
        // funkcja poprawnie policzy wierzchołki drzewa permutacji i informację o nich umieści w drzewie tree
        int n = sz(vec);
        Seg_tree st(n + 1);

        vector<int> stos;
        vector<pair<int, int> > mini = {{-1, 0}};
        vector<pair<int, int> > maxi = {{-1, n + 1}};

        gdzie = vec;
        for(int i = 0; i < n; i++){
            Node teraz(vec[i], vec[i], i + 1, i + 1, sz(tree));
            gdzie[i] = teraz.id;

            while(mini.back().s > vec[i]){
                st.add(mini[sz(mini) - 2].f + 1, mini.back().f, -mini.back().s);
                mini.pop_back();
            }

            while(maxi.back().s < vec[i]){
                st.add(maxi[sz(maxi) - 2].f + 1, maxi.back().f, maxi.back().s);
                maxi.pop_back();
            }

            st.add(0, sz(stos) - 1, 1);
            st.add(mini.back().f + 1, sz(stos) - 1, teraz.lo);
            st.add(maxi.back().f + 1, sz(stos) - 1, -teraz.hi);

            bool on_stack = false;

            while(true){
                assert(st.ask_max(sz(stos), sz(stos)) == 0);

                if(!on_stack){
                    mini.pb({sz(stos), teraz.lo});
                    maxi.pb({sz(stos), teraz.hi});
                
                    tree.pb(teraz);
                    stos.pb(teraz.id);
                }

                // jeżeli poprzedni wierzchołek nie jest liściem, i jest join, to sprawdz, czy
                // można się pod niego "podpiąć" jako syn

                if(sz(stos) > 1){
                    auto & u = tree[stos[sz(stos) - 2]];
                    if(!u.cut and sz(u.sons) >= 2){
                        bool malejacy = (tree[u.sons[0]].hi - tree[u.sons.back()].hi) > 0;

                        if(malejacy and teraz.hi == tree[u.sons.back()].lo - 1){
                            u.sons.pb(tree[stos.back()].id);
                            u.kon = tree[stos.back()].kon;
                            u.lo = tree[stos.back()].lo;
                            tree[stos.back()].parent = u.id;
                            stos.pop_back();
                            mini.back().f--;
                            maxi.pop_back();
                            on_stack = true;
                            teraz = tree[stos.back()];
                            continue;
                        }
                        else if(!malejacy and teraz.lo == tree[u.sons.back()].hi + 1){
                            u.sons.pb(tree[stos.back()].id);
                            u.kon = tree[stos.back()].kon;
                            u.hi = tree[stos.back()].hi;
                            tree[stos.back()].parent = u.id;
                            stos.pop_back();
                            maxi.back().f--;
                            mini.pop_back();
                            on_stack = true;
                            teraz = tree[stos.back()];
                            continue;
                        }
                    }
                }

                on_stack = false;
                
                int border = st.first_zero(0, sz(stos) - 2);

                if(border == -1)
                    break;
                bool cutnode = true;
                if(border == sz(stos) - 2)
                    cutnode = false;

                Node nastepny(teraz.lo, teraz.hi, teraz.pocz, teraz.kon, sz(tree), cutnode);
                while(maxi.back().f >= border)
                    maxi.pop_back();

                while(mini.back().f >= border)
                    mini.pop_back();
                
                while(sz(stos) > border){
                    st.add(sz(stos) - 1, sz(stos) - 1, -st.ask_max(sz(stos) - 1, sz(stos) - 1));
                    tree[stos.back()].parent = nastepny.id;
                    nastepny.sons.pb(stos.back());
                    nastepny.pocz = tree[stos.back()].pocz;
                    nastepny.lo = min(nastepny.lo, tree[stos.back()].lo);
                    nastepny.hi = max(nastepny.hi, tree[stos.back()].hi);
                    stos.pop_back();
                }
                reverse(nastepny.sons.begin(), nastepny.sons.end());

                swap(teraz, nastepny);
            }
        }
        assert(sz(stos) == 1);
        for(int i = 0; i < sz(tree); i++)
            assert(tree[i].id == i);

        Root = stos[0];
        tree[Root].parent = Root; 
        prep_LCA();
    }
};

int main(){
    int n;
    cin >> n;

    vector<int> tab(n);
    for(auto & u : tab)
        cin >> u;

    Perm_tree tree(tab);

    int q;
    cin >> q;

    while(q -- ){
        int a, b;
        cin >> a >> b;
        a--, b--;

        pair<int, int> przed = tree.min_good(a, b);
        cout << przed.f << ' ' << przed.s << '\n';
    }
}