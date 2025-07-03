#include <iostream>
#include <string>
#include <utility>
#include <math.h>

const double PI = 3.141592653589793;
using namespace std;

void _assert(bool a, const char* msg)
{
	if (!a) {
		cerr << "Assertion failed: " << msg << endl;
		exit(1);
	}
}

struct Pt
{
	int x, y; //座標を表す構造体
	Pt(int _x,int _y):	x(_x), y(_y) {}
	Pt(): x(0), y(0) {} //デフォルトコンストラクタ
};
struct vect
{
	double x, y; //2次元ベクトルを表す構造体
	vect(Pt a,Pt b) : x(b.x - a.x), y(b.y - a.y) {} //2点からベクトルを作成
	double norm() const
	{
		return sqrt(x * x + y * y); //ベクトルのノルムを計算する
	}
	double dot(const vect& other) const
	{
		return x * other.x + y * other.y; //ベクトルの内積を計算する
	}	

};

//


int _solve()
{
	int N;
	cin >> N;					//まず座標の数。

	Pt*p = new Pt[N];
	for(int i=0 ; i <N; i++) {
		int x, y;
		cin >> x >> y;			//座標を入力
		p[i] = Pt(x, y); //座標をペアにして保存
	}


#if   1 //標準入力から得た変数をすべて出力する  //
	for(int i=0; i<N; i++) {
		cout << "p[" << i << "] = (" << p[i].x << ", " << p[i].y << ")" << endl;
	}
#endif    //===============================================================
	//これらの組み合わせから、三点を選択してPi,Pj,Pkのなす角が最大となる組み合わせを見つけて、度で解答する。
	_assert(N >= 3, "座標の数は3以上でなければなりません。");
	int max_theta = 0; //最大の角度を保存する変数
	for (int i = 0; i < N; ++i) {	///全部の組み合わせを考える
		for (int j = 1; j < N; ++j) {
			for(int k= 2 ; k < N ;++k ){
				if (i == j || i == k || j == k)continue; //同じ点を選ばない
				//ベクトルaを作ります。
				vect a(p[j],p[i]); //p[j] - p[i]は、p[i]からp[j]へのベクトル
				//ベクトルbを作ります。
				vect b(p[k],p[i]); //p[k] - p[i]は、p[i]からp[k]へのベクトル

				//あとは自分で書くので余計なことすんな
				//内積/|a|| * |b|| = cos(θ)を作ります。
				double cos_theta = a.dot(b) /(a.norm() * b.norm());
				//cos(θ)からθを求めます。
				double theta = acos(cos_theta)/PI; //ラジアンで求まる.角度はπ以内の側とする。
				if( theta > max_theta) {
					max_theta = theta; //最大の角度を更新
				}
			}
		}
	}
	//ここでmax_thetaは最大の角度をラジアンで持っているので、度に変換します。
	cout << max_theta /PI * 180 << endl; //ラジアンを度に変換して出力

_fin:
	return 0;
}


int main()
{
	for (; cin.peek() != EOF; ) {
		_solve();
	}
	return 0;
}
