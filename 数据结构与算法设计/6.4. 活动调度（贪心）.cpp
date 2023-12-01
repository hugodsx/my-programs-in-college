#include<cstdio> 
#include<algorithm> 
#define N 1000010 

int start[N];
int end[N];
 
int main() 
{ 
    
    int n, i;
    scanf("%d", &n); 
    for(i = 0 ; i < n ; i++) 
    { 
        scanf("%d%d", &start[i], &end[i]); 
    } 
    std::sort(start, start + n); 
    std::sort(end, end + n);
    i = 0;
    int room = 0, ans = 0, j = 0;
    while(i < n && j < n)
    {
        if(start[i] < end[j])//开始早于结束
        {
            room++;
            i++;
            ans = std::max(ans, room);
        }
        else if(start[i] > end[j])
        {
            room--;
            j++;
        }
        else
        {
            i++;
            j++;
            ans = std::max(ans, room);
        }
    }
    printf("%d\n", ans); 
    return 0; 
} 