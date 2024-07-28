using System;
using System.Collections.Generic;

class GFG
{
	static List<int> CountSort(List<int> inputArray)
	{
		int N = inputArray.Count;
		// Finding the maximum element of the array inputArray[].
		int M = 0;
		for (int i = 0; i < N; i++)
			M = Math.Max(M, inputArray[i]);
		// Initializing countArray[] with 0
		List<int> countArray = new List<int>(new int[M + 1]);
		// Mapping each element of inputArray[] as an index
		// of countArray[] array
		for (int i = 0; i < N; i++)
			countArray[inputArray[i]]++;
		// Calculating prefix sum at every index
		// of array countArray[]
		for (int i = 1; i <= M; i++)
			countArray[i] += countArray[i - 1];
		// Creating outputArray[] from the countArray[] array
		List<int> outputArray = new List<int>(new int[N]);
		for (int i = N - 1; i >= 0; i--)
		{
			outputArray[countArray[inputArray[i]] - 1] = inputArray[i];
			countArray[inputArray[i]]--;
		}
		return outputArray;
	}
	// Driver code
	static void Main()
	{
		// Input array
		List<int> inputArray = new List<int> { 4, 3, 12, 1, 5, 5, 3, 9 };
		// Output array
		List<int> outputArray = CountSort(inputArray);
		for (int i = 0; i < inputArray.Count; i++)
			Console.Write(outputArray[i] + " ");
		Console.WriteLine();
	}
}
