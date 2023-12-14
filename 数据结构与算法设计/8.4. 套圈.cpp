#include<cstdio>
#include<algorithm>
#include<cmath>
#define MAXSIZE 100005
using namespace std;
struct Point{
    double x, y;
    int id;
}X[MAXSIZE];
int temp[MAXSIZE];

double distance(Point a1, Point b1){
    return sqrt((a1.x-b1.x)*(a1.x-b1.x) + (a1.y-b1.y)*(a1.y-b1.y));
}

bool compareX(Point a, Point b){
    return a.x < b.x;
}

bool compareY(int a, int b){
    return X[a].y < X[b].y;
}

double closest(int l, int r){

    if(r - l == 1)  return distance(X[l], X[r]);
    if(r - l == 2){
        double d1 = distance(X[l], X[l + 1]);
        double d2 = distance(X[l], X[r]);
        double d3 = distance(X[l + 1], X[r]);
        return min(d1, min(d2, d3));
    }
    int m = (l + r) / 2;
    double d = min(closest(l, m), closest(m + 1, r));
    int k = 0;
    for(int i = l ; i <= r ; i++){
        if(fabs(X[i].x - X[m].x) < d){
            temp[k++] = i;
        }
    }
    sort(temp, temp + k, compareY);
    for(int i = 0 ; i < k - 1; i++){
        for(int j = i + 1 ; j < k ; j++){
            if(d > distance(X[temp[i]], X[temp[j]]))    d = distance(X[temp[i]], X[temp[j]]);
        }
    }
    return d;
}

int main(){
    int n = 0;
    double d;
    while(true){
        scanf("%d", &n);
        if(n == 0)  break;
        for(int i = 0 ; i < n ; i++){
            scanf("%lf %lf", &X[i].x, &X[i].y);
        }
        sort(X, X + n, compareX);
        d = closest(0, n - 1);
        printf("%.2f\n", d / 2);
    }
    return 0;
}