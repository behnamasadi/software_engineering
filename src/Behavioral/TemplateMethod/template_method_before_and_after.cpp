#include <iostream>

using namespace std;
class SortUp
{
    // Shell sort
  public:
    void sort(int v[], int n)
    {
        for (int g = n / 2; g > 0; g /= 2)
          for (int i = g; i < n; i++)
            for (int j = i - g; j >= 0; j -= g)
              if (v[j] > v[j + g])
                doSwap(v[j], v[j + g]);
    }
  private:
    void doSwap(int &a, int &b)
    {
        int t = a;
        a = b;
        b = t;
    }
};

class SortDown
{
  public:
    void sort(int v[], int n)
    {
        for (int g = n / 2; g > 0; g /= 2)
          for (int i = g; i < n; i++)
            for (int j = i - g; j >= 0; j -= g)
              if (v[j] < v[j + g])
                doSwap(v[j], v[j + g]);
    }
  private:
    void doSwap(int &a, int &b)
    {
        int t = a;
        a = b;
        b = t;
    }
};

int main()
{
  const int NUM = 10;
  int array[NUM];
  srand((unsigned)time(0));
  for (int i = 0; i < NUM; i++)
  {
    array[i] = rand() % 10+1;
    cout << array[i] << ' ';
  }
  cout << '\n';

  SortUp upObj;
  upObj.sort(array, NUM);
  for (int u = 0; u < NUM; u++)
    cout << array[u] << ' ';
  cout << '\n';

  SortDown downObj;
  downObj.sort(array, NUM);
  for (int d = 0; d < NUM; d++)
    cout << array[d] << ' ';
  cout << '\n';
  system("pause");
}
