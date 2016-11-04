using System;
using System.Collections;

namespace TSP
{
	public class State : IComparable
    {
        public ArrayList In = new ArrayList(); // of City-s
        public ArrayList Out = new ArrayList(); // of City-s
        public double Bound;
		public double[,] BoundingMatrix;

		public State () { }

		public State (double bound, double [,] boundingMatrix)
		{
			this.Bound = bound;
			this.BoundingMatrix = boundingMatrix;
		}

        public State copy(int len)
        {
            State newState = new State(this.Bound, this.copyBoundingMatrix(len));

            foreach (var r in this.In)
            {
                newState.In.Add(r);
            }

            foreach (var r in this.Out)
            {
                newState.Out.Add(r);
            }
            return newState;
        }

        public double[,] copyBoundingMatrix (int len)
        {
            double[,] newBoundingMatrix = new double [len, len];
            for (int i = 0; i < len; i++)
            {
                for (int j = 0; j < len; j++)
                {
                    newBoundingMatrix[i, j] = this.BoundingMatrix[i, j];
                }
            }
            return newBoundingMatrix;
        }

        public int CompareTo(object obj)
        {
            State o = (State)obj;
            if (this.Bound == o.Bound)
            {
                return 0;
            }
            else if (this.Bound < o.Bound)
            {
                return -1;
            }
            return 1;
        }

        
        public double minRow(int i, int y, int len)
        {
            double min = Double.PositiveInfinity;
            for (int j = 0; j < len; j++)
            {
                if (min > this.BoundingMatrix[i,j] && j != y)
                {
                    min = this.BoundingMatrix[i, j];
                }
            }

            return min;
        }

        public double minCol(int x, int j, int len)
        {
            double min = Double.PositiveInfinity;
            for (int i = 0; i < len; i++)
            {
                if (min > this.BoundingMatrix[i, j] && i != x)
                {
                    min = this.BoundingMatrix[i, j];
                }
            }

            return min;
        }


        public void setColumnToInfinity(int column, int len)
        {
            for (int i = 0; i < len; i++)
            {
                this.BoundingMatrix[i, column] = Double.PositiveInfinity;
            }
        }


        public void setRowToInfinity(int row, int len)
        {
            for (int i = 0; i < len; i++)
            {
                this.BoundingMatrix[row, i] = Double.PositiveInfinity;
            }
        }


        public void setExcludeState(int i, int j, int len)
        {
            this.BoundingMatrix[i, j] = Double.PositiveInfinity;
        }

        public void calcBound(int len)
        {
            // Reset row
            double lowest = Double.PositiveInfinity;
            for (int i = 0; i < len; i++)
            {
                lowest = Double.PositiveInfinity;
                for (int j = 0; j < len; j++)
                {
                    if (Double.IsPositiveInfinity(this.BoundingMatrix[i,j])) { continue; }
                    if (this.BoundingMatrix[i, j] < lowest)
                    {
                        lowest = this.BoundingMatrix[i, j];
                    }
                }
                if (lowest != 0 && lowest != Double.PositiveInfinity)
                {
                    for (int k = 0; k < len; k++)
                    {
                        if (!Double.IsPositiveInfinity(this.BoundingMatrix[i, k]))
                        {
                            this.BoundingMatrix[i, k] = this.BoundingMatrix[i, k] - lowest;
                        }
                    }
                    this.Bound += lowest;
                }
            }

            // Reset Column
            for (int i = 0; i < len; i++)
            {
                lowest = Double.PositiveInfinity; // Set the lowest value to default (Infinity)
                for (int j = 0; j < len; j++)
                {
                    if (Double.IsPositiveInfinity(this.BoundingMatrix[j, i])) { continue; }
                    if (this.BoundingMatrix[j, i] < lowest) // Find the lowest value in the row
                    {
                        lowest = this.BoundingMatrix[j, i];
                    }
                }
                if (lowest != 0 && lowest != Double.PositiveInfinity) // Skip if 0 or infinity to save time
                {
                    for (int k = 0; k < len; k++)
                    {
                        if (!Double.IsPositiveInfinity(this.BoundingMatrix[k, i]))
                        {
                            this.BoundingMatrix[k, i] = this.BoundingMatrix[k, i] - lowest;
                        }
                    }
                    this.Bound += lowest;
                }
            }
        }

        /*
        * When a potential solution has been found (assume we have used all Cities), 
        *   then check if it is valid
        */
        public bool isLoop(int len)
        {
            if (this.In.Count != len) // just a confirmation (should always get past this)
            {
                return true;
	        }

            int first = (int)this.In[0]; // unchanging value of the first in
            int prev_out = (int)this.Out[0]; // updating value of the previous out

            SortedList visited = new SortedList();
            visited.Add(first, true);
            visited.Add(prev_out, true);
            int count = 1;

            while (prev_out != first)
            {
                for (int j = 1; j < this.In.Count; j++)
                {
                    if ((int)this.In[j] == prev_out)
                    {
                        prev_out = (int)this.Out[j];
				        if (visited.ContainsKey (prev_out)) 
				        {
					        if (prev_out == first && visited.Count == len) {
						        return false;
					        }

					        return true;
				        } 
				        else 
				        {
					        visited.Add (prev_out, true);
				        }
			        }
			        count++;
                }
            }
            return false;
        }


        public void printBoundingMatrix(int len)
        {
            Console.WriteLine();
            Console.WriteLine("MATRIX");
            for (int i = 0; i < len; i ++)
            {
                for (int j = 0; j < len; j++)
                {
                    Console.Write(this.BoundingMatrix[i, j] + " ");
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }
    }
}

