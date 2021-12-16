#pragma once

//taken from https://cp-algorithms.com/algebra/fft.html
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

// a, b => coefficients of polynomials to multiply
// a[i], b[i] = coefficient x^i
vector<ll> multiply (const vector<int> & a, const vector<int> & b) {
	if(a.size() * b.size() <= 256) {
		vector<ll> res(a.size() + b.size(), 0);
		for(int i = 0; i < (int)a.size(); i++)
			for(int j = 0; j < (int)b.size(); j++)
				res[i + j] += 1LL * a[i] * b[j];
		return res;
	}
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n=1;
	while (n<a.size() + b.size()) n<<=1;
	fa.resize(n),fb.resize(n);
	fft (fa,false);  fft(fb,false);
	for (size_t i=0; i<n; ++i)
		fa[i]*=fb[i];
	fft (fa, true);
	vector<ll> res(n);
	for(size_t i=0; i<n; ++i) {
		double realVal = fa[i].real();
		res[i] = realVal > 0 ? realVal + 0.5 : realVal - 0.5;
	}
	return res;
}
