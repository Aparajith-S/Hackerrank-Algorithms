long arrayManipulation(int n, vector<vector<int>> queries) 
{
/*Create an array of n elements and init to 0*/
long *Arr = new long [n];
long max=0,size,a,b,k;
size=queries.size();
//O(N)
for (int i = 0; i < n; i++)
    Arr[i]=0;
//O(N)
for (int i = 0; i < size; i++)
{   // 1 2 3 4 .... n
    // idx 0 1 2 3 4 ... n-1
    a=queries[i][0]-1;
    b=queries[i][1]-1;
    k=queries[i][2];
    *(Arr+a)+=k;
    if((b+1)<(n))
    *(Arr+b+1)-=k;
}
max=Arr[0];
for (int i = 1; i < n; i++)
{   Arr[i]+=Arr[i-1];
    if(max<Arr[i])
    max = Arr[i];
}
return max;
}


