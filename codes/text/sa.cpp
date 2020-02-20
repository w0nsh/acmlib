// https://doi.org/10.1145/1217856.1217858
inline bool leq(int a1, int a2, int b1, int b2){
	return a1 < b1 || (a1 == b1 && a2 <= b2);
}
inline bool leq(int a1, int a2, int a3, int b1, int b2, int b3){
	return a1 < b1 || (a1 == b1 && leq(a2, a3, b2, b3));
}
void radix(int *a, int *b, int *r, int n, int K){
	int *c = new int[K+1];
	for(int i = 0; i <= K; ++i) c[i] = 0;
	for(int i = 0; i < n; ++i) c[r[a[i]]]++;
	for(int i = 0, sum = 0, t = 0; i <= K; ++i) t = c[i], c[i] = sum, sum += t;
	for(int i = 0; i < n; ++i) b[c[r[a[i]]]++] = a[i];
	delete [] c;
}
// A = {1..K}
// T[0..n-1] - word
// T[n] = T[n+1] = T[n+2] = 0
// SA[0..n-1] - output
void suffix_array(int *T, int *SA, int n, int K){
	if(n == 1){
		SA[0] = 0;
		return;
	}
	int n0 = (n+2)/3, n1 = (n+1)/3, n2 = n/3, n02=n0+n2;
	int *R = new int[n02+3];
	int *SA12 = new int[n02+3];
	int *R0 = new int[n02];
	int *SA0 = new int[n02];
	for(int i = 0; i < 3; ++i) R[n02+i] = SA12[n02+i] = 0;
	for(int i = 0, j = 0; i < n+n0-n1; ++i) if(i%3) R[j++] = i;
	radix(R, SA12, T+2, n02, K);
	radix(SA12, R, T+1, n02, K);
	radix(R, SA12, T, n02, K);
	int name = 0, c0 = -1, c1 = -1, c2 = -1;
	for(int i = 0; i < n02; ++i){
		if(T[SA12[i]] != c0 || T[SA12[i]+1] != c1 || T[SA12[i]+2] != c2)
			name++, c0 = T[SA12[i]], c1 = T[SA12[i]+1], c2 = T[SA12[i]+2];
		if(SA12[i]%3 == 1) R[SA12[i]/3] = name;
		else R[SA12[i]/3+n0] = name;
	}
	if(name < n02){
		suffix_array(R, SA12, n02, name);
		for(int i = 0; i < n02; ++i) R[SA12[i]] = i+1;
	}else for(int i = 0; i < n02; ++i) SA12[R[i]-1] = i;
	for(int i = 0, j = 0; i < n02; ++i) if(SA12[i] < n0) R0[j++] = 3*SA12[i];
	radix(R0, SA0, T, n0, K);
	for(int p = 0, t = n0-n1, k = 0; k < n; ++k){
		#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
		int i = GetI();
		int j = SA0[p];
		if(SA12[t] < n0 ?
			leq(T[i], R[SA12[t]+n0], T[j], R[j/3]) :
			leq(T[i], T[i+1], R[SA12[t]-n0+1], T[j], T[j+1], R[j/3+n0])){
			SA[k] = i, t++;
			if(t == n02) for(k++; p < n0; p++, k++) SA[k] = SA0[p];
		}else{
			SA[k] = j; p++;
			if(p == n0) for(k++; t < n02; t++, k++) SA[k] = GetI();
		}
	}
	delete[] R; delete[] SA12; delete[] SA0; delete[] R0;
}
