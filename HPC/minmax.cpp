#include <bits/stdc++.h>

#include <omp.h>

using namespace std;

void min_red(vector<int> &arr, int n)
{
  int min_val = INT_MAX;
#pragma omp parallel for reduction(min : min_val) 
  for (int i = 0; i < n; i++)
  {
    if (arr[i] < min_val)
    {
      min_val = arr[i];
    }
  }
  cout<< " minimum value is :" << min_val<<endl;
}
void max_red(vector<int> &arr, int n)
{
  int max_elem = INT_MIN;
#pragma omp parallel for reduction(max : max_elem)   
  for (int i = 0; i < n; i++)
  {
    if (arr[i] > max_elem)
    {
      max_elem = arr[i];
    }
  }
  cout << "the max value is " << max_elem<<endl;
}

void sum_red(vector<int> &arr, int n)
{

  int sum = 0;
#pragma omp parallel for reduction(+ : sum) 
  for (int i = 0; i < n; i++)
  {
    sum += arr[i];
  }
  cout << "the sum is :" << sum;
}

void avg_red(vector<int> &arr, int n)
{
  int sum = 0;
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < n; i++)
  {
    sum += arr[i];
  }
  double avg = double(sum) / (n - 1);
  cout << "avg is:" << avg<<endl;
}



int main()
{

  int n;

  vector<int> arr(n);
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> arr[i];
  }

  min_red(arr, n);
  max_red(arr, n);
  sum_red(arr, n);
  avg_red(arr, n);

  return 0;
}