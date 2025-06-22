#include <iostream>
#include <string>
#include "string.h"

using namespace std;


//再帰呼び出しによる二分探索の実装
//ターゲットが配列Aにあるとは限らない。最終的にleftとrightが隣り合う場所で探索終了する。
//どちらかを選択するには、A[left_idx]とA[right_idx]のどちらがターゲットに近いかを比較して返す。
//Aはソート済みであることが前提。
int binary_search(int *A, int l_idx, int r_idx, int target)
{
    if (l_idx > r_idx) {
        return -1; // 見つからなかった場合
    }
    int mid = (l_idx + r_idx) / 2;
    if (A[mid] == target) {
        return mid; // 見つかった場合
    } else if (A[mid] < target) {
        //mid +  1をして、rightと一致してしまう場合は、終了です。
        if(mid+1 >= r_idx){
            ;
            
        }
        return binary_search(A, mid + 1, r_idx, target); // 右側を探索
    } else {
        //mid - 1をして、leftと一致してしまう場合は、ここで終了。
        return binary_search(A, l_idx, mid - 1, target); // 左側を探索
    }
}

int main()
{
    int N,Q;            //Nクラス、Q人の生徒
    cin >> N;            //Nクラス
    int *A = new int[N];    //各クラスの人数
    for(int i=0 ; i < N ; ++i){
        cin >> A[i];
    }
    cin >> Q;            //Q人の生徒
    int *B = new int[Q];    //各生徒のクラス番号
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
    return 0;
#endif    //===============================================================

    int *_ans = new int[Q];    //各生徒のクラス番号
    //BはQ人分の生徒のレーティング数値、
    //AはNクラスのレーティング数値。
    //Bそれぞれについて一番近いレーティングクラスを探す。
    //B(1<j<Q)で、クラスA(1<i<N)のレーティング数値と比較して、一番近いクラスを探す。
    //各生徒のレーティング数値と、クラスのレーティング数値の差を求める。
    //どこに所属するかを決める。二分探索で探す。
    {
        int idx = N/2;    //二分探索の初期値
        int left,right;    //二分探索のための変数
        for(int i=0 ; i < Q ; ++i){
            if(A[idx] < B[i]){      //B[i]がA[idx]より大きい場合、右側を探索
                left = idx;
                right = N-1;
                while(left <= right){
                    int mid = (left + right) / 2;
                    if(A[mid] < B[i]){
                        left = mid + 1;
                    }else{
                        right = mid - 1;
                    }
                }
            }else{
                //B[i]がA[idx]より小さい場合、左側を探索
                int left = 0;
                int right = idx;
                while(left <= right){
                    int mid = (left + right) / 2;
                    if(A[mid] < B[i]){
                        left = mid + 1;
                    }else{
                        right = mid - 1;
                    }
                }
            }
        }
    }
}