#include <iostream>
#include <string>

using namespace std;


void _search(const string &src ,const string &dst , int src_idx , int dst_idx , int &n )
{
	//指定された,src[src_idx]の文字を,場所dst_idxから、最後まで探します。見つけたら、次の文字に進み、探す指示を出す。
	//もし最後の文字を見つけたら、通し番号をインクリメントしていく。
	for(int i=dst_idx; i<dst.size(); i++) {
		if (src[src_idx] == dst[i]) {
			//見つかった
			if(src_idx == src.size() - 1) { //最後の文字まで見つかったか？	
				//最後の文字まで見つかったので、通し番号をインクリメント
				n++;
				return;
			}
			//次の文字を探す
			_search(src, dst, src_idx + 1, i + 1, n); //次の文字を探す
		}
	}
}

void _assert(bool a, const char* msg)
{
	if (!a) {
		cerr << "Assertion failed: " << msg << endl;
		exit(1);
	}
}
#define MOD	(1000000000 + 7)

int _solve()
{
	int N;
	cin >> N;
	//
	pair 

	cin >> S;

#if   0 //標準入力から得た変数をすべて出力する  //
	cout << "N=" << N << endl;
	cout << "S=" << S << endl;
#endif    //===============================================================
	//[atcoder]を作る。
	const string T = "atcoder";
	int ans=0;

	vector<vector<long long>> dp(N + 1, vector<long long>(T.size()+1, 0));
	                                 //^^^^^^^^^^^^^^^^^^^^^^^^^^^^   ^^					//dp[i][j]は、Sの最初のi文字までを使って、srcの最初のj文字までを作る方法の数を表す。	
	                                 //配列の数						 全要素初期値
	dp[0][0] = 1; // 初期状態：何も選んでいない

	for (int i = 0; i < N; ++i) {		//
		for (int j = 0; j <= T.size() ; ++j) {
			// 文字を使わない場合
			dp[i + 1][j] = (dp[i + 1][j] + dp[i][j] ) % MOD;

			// 文字を使う場合（次の文字が合っているなら）
			if (j < 7 && S[i] == T[j]) {
				dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j] ) % MOD;
			}
		}
	}

	cout << dp[N][7] << endl;
#if 0
	//dp配列を列挙してみるか
	for (int j = 0; j <= T.size(); j++) {
		for(int i=0; i<=N; i++) {
			cout << "[" << dp[i][j]%100 << "]";
		}
		cout << endl;
	}
#endif
//	_search(src, S , 0, 0, ans);

//	cout << ans << endl;
	//これでansが見つかるよね？
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
