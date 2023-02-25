#include <iostream>
using namespace std;


int degree[10000];

int main()
{
  int n;
  int m;
  for (int i = 0; i < 10000; i++) degree[i] = 0;

  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    degree[a] ++;
    degree[b] ++;
  }

  int oddCount = 0;
  int odds[3];

  for (int i = 0; i < n and oddCount < 3; i++)
    if(degree[i] %2 == 1)
      odds[oddCount ++] = i;

  if(oddCount == 0)
    cout << "CYCLE\n";
  else if (oddCount == 2)
    cout << "PATH " << odds[0] << " " << odds[1] << endl;
  else
    cout << "IMPOSSIBLE\n";
}
