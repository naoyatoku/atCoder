#include <iostream>
#include <string>
#include "string.h"

using namespace std;


//再帰呼び出しによる二分探索の実装
//ターゲットが配列Aにあるとは限らない。最終的にleftとrightが隣り合う場所で探索終了する。
//どちらかを選択するには、A[left_idx]とA[right_idx]のどちらがターゲットに近いかを比較して返す。
//Aはソート済みであることが前提。


void _assert(bool a, const char *msg)
{
	if (!a) {
		cerr << "Assertion failed: " << msg << endl;
		exit(1);
	}
}
void _swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
int _qsort(int* A, int N)
{
	_assert(N > 0, "N must be greater than 0");
	if (N == 1) {
		return A[0]; // クラスが一つしかない場合は、絶対値を出力して終了
	}
	int pivot = A[N / 2]; // 中央の要素をピボットとする
	int left_idx = 0;
	int right_idx = N - 1;
	while (left_idx <= right_idx) {
		while (A[left_idx] < pivot) {
			left_idx++;
		}
		while (A[right_idx] > pivot) {
			right_idx--;
		}
		if (left_idx <= right_idx) {
			_swap(A[left_idx], A[right_idx]);
			left_idx++;
			right_idx--;
		}
	}
	if (right_idx > 0) {
		_qsort(A, right_idx + 1); // 左側の部分配列を再帰的にソート
	}
	if (left_idx < N) {
		_qsort(A + left_idx, N - left_idx); // 右側の部分配列を再帰的にソート
	}
	return 0;
}

int _nearest_class_idx(int *A, int N, int target)
{
	_assert(N > 0, "N must be greater than 0");
	if (N == 1) {
		return A[0]; // クラスが一つしかない場合は、絶対値を出力して終了
	}
	int l_idx = 0;
	int r_idx = N - 1;
    while (r_idx - l_idx > 1) {
		int mid = (l_idx + r_idx) / 2;
        //やらなくてもいいけど早くみつかるかと思って
        if (A[mid] == target) { // midがターゲットと一致する場合
            return mid; // midを返す
        }
		if (A[mid] < target) {
			l_idx = mid + 1; // 右側を探索
		} else {
			r_idx = mid; // 左側を探索
		}
	}
	// 最終的にl_idxとr_idxが隣り合う場所で探索終了する。
	if (abs(A[r_idx] - target) < abs(target - A[l_idx])) { //midのほうが近い場合
		return r_idx; //midを返す
	} else {
		return l_idx; //l_idxを返す
	}
}

int _solve()
{
    int N,Q;					//Nクラス、Q人の生徒
    cin >> N;					//Nクラス
    int *A = new int[N];		//各クラスの人数
    for(int i=0 ; i < N ; ++i){
        cin >> A[i];
    }
	//Aはソート済みであることが前提なので、ソートを行う
	_qsort(A, N); // クラスの人数をソート

    cin >> Q;					//Q人の生徒
    int *B = new int[Q];		//各生徒のクラス番号
    for(int i=0 ; i<Q ;++i){
        cin >> B[i];
    }
#if   1 //標準入力から得た変数をすべて出力する  //
    cout << "N=" << N << endl;
    cout << "Q=" << Q << endl;
    cout << "A=";
    for(int i=0 ; i < N ; ++i){
        cout << A[i] << " ";
    }
    cout << endl;
    cout << "B=";
    for(int i=0 ; i < Q ; ++i){
        cout << B[i] << " ";
    }
    cout << endl;
#endif    //===============================================================
    //人数分(B[Q人]) に対してバイナリサーチを掛けていき、その差分を足していきます。
    //クラスが一個しかない場合もある・・
    for (int j = 0; j < Q; ++j) {
        int idx = _nearest_class_idx(A, N, B[j]); // クラスのインデックスを取得
        cout << abs(A[idx] - B[j]) << endl; // 結果を出力
    }
_fin:
    return 0;
}


int main()
{
	for( ;cin.peek()!=EOF  ; ){
		_solve();
	}
	return 0;
}
