const double PI=acos(-1);
typedef complex<double> base;
inline void fft (vector<base> & a, bool invert) {
	int n=(int) a.size();
	for (int i=1, j=0; i<n; ++i) {
		int bit=n>>1;
		for (;j>=bit;bit>>=1)
			j-=bit;
		j+=bit;
		if(i<j)
			swap(a[i],a[j]);
	}
	for (int len=2; len<=n; len<<=1) {
		double ang = 2*PI/len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i=0; i<n; i+=len) {
			base w(1);
			for (int j=0; j<len/2; ++j) {
				base u=a[i+j], v=a[i+j+len/2]*w;
				a[i+j]=u+v;
				a[i+j+len/2]=u-v;
				w*=wlen;
			}
		}
	}
	if (invert)
		for(int i=0;i<n;++i)
			a[i]/=n;
}

// a, b => coefs to multiply,  res => resulting coefs
// a[0], b[0], res[0] = coef x^0
inline void multiply (const vector<int> & a, const vector<int> & b, vector<int> & res) {//change res to int if needed
	if(a.size() * b.size() <= 256) {
		res.resize(a.size() + b.size()+1, 0);
		for(int i = 0; i < (int)a.size(); i++)
			for(int j = 0; j < (int)b.size(); j++)
				res[i + j] += 1LL * a[i] * b[j];
		while(res.size()>1 && res.back() == 0) res.pop_back();
		return;
	}
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n=1;
	while (n<max(a.size(),b.size())) n<<=1;
	n<<=1;
	fa.resize(n),fb.resize(n);
	fft (fa,false);  fft(fb,false);
	for (size_t i=0; i<n; ++i)
		fa[i]*=fb[i];
	fft (fa, true);
	res.resize (n);
	for(size_t i=0; i<n; ++i)
		res[i]=(int)(fa[i].real()>0 ? fa[i].real()+0.5 : fa[i].real()-0.5);
	while(res.size()>1 && res.back() == 0) res.pop_back();
}
