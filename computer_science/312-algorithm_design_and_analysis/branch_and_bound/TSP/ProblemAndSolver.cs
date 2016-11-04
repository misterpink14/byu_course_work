using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;

namespace TSP
{

    class ProblemAndSolver
    {

        private class TSPSolution
        {
            /// <summary> 
            /// we use the representation [cityB,cityA,cityC] 
            /// to mean that cityB is the first city in the solution, cityA is the second, cityC is the third 
            /// and the edge from cityC to cityB is the final edge in the path.  
            /// You are, of course, free to use a different representation if it would be more convenient or efficient 
            /// for your node data structure and search algorithm. 
            /// </summary>
            public ArrayList
                Route;

            public TSPSolution(ArrayList iroute)
            {
                Route = new ArrayList(iroute);
            }


            /// <summary>
            /// Compute the cost of the current route.  
            /// Note: This does not check that the route is complete.
            /// It assumes that the route passes from the last city back to the first city. 
            /// </summary>
            /// <returns></returns>
            public double costOfRoute()
            {
                // go through each edge in the route and add up the cost. 
                int x;
                City here;
                double cost = 0D;

                for (x = 0; x < Route.Count - 1; x++)
                {
                    here = Route[x] as City;
                    cost += here.costToGetTo(Route[x + 1] as City);
                }

                // go from the last city to the first. 
                here = Route[Route.Count - 1] as City;
                cost += here.costToGetTo(Route[0] as City);
                return cost;
            }
        }

        #region Private members 

        /// <summary>
        /// Default number of cities (unused -- to set defaults, change the values in the GUI form)
        /// </summary>
        // (This is no longer used -- to set default values, edit the form directly.  Open Form1.cs,
        // click on the Problem Size text box, go to the Properties window (lower right corner), 
        // and change the "Text" value.)
        private const int DEFAULT_SIZE = 25;

        private const int CITY_ICON_SIZE = 5;

        // For normal and hard modes:
        // hard mode only
        private const double FRACTION_OF_PATHS_TO_REMOVE = 0.20;

        /// <summary>
        /// the cities in the current problem.
        /// </summary>
        private City[] Cities;
        /// <summary>
        /// a route through the current problem, useful as a temporary variable. 
        /// </summary>
        private ArrayList Route;
        /// <summary>
        /// best solution so far. 
        /// </summary>
        private TSPSolution bssf; 

        /// <summary>
        /// how to color various things. 
        /// </summary>
        private Brush cityBrushStartStyle;
        private Brush cityBrushStyle;
        private Pen routePenStyle;


        public Stopwatch timer;


        /// <summary>
        /// keep track of the seed value so that the same sequence of problems can be 
        /// regenerated next time the generator is run. 
        /// </summary>
        private int _seed;
        /// <summary>
        /// number of cities to include in a problem. 
        /// </summary>
        private int _size;

        /// <summary>
        /// Difficulty level
        /// </summary>
        private HardMode.Modes _mode;

        /// <summary>
        /// random number generator. 
        /// </summary>
        private Random rnd;
        #endregion

        #region Public members
        public int Size
        {
            get { return _size; }
        }

        public int Seed
        {
            get { return _seed; }
        }
        #endregion

        #region Constructors
        public ProblemAndSolver()
        {
            this._seed = 1; 
            rnd = new Random(1);
            this._size = DEFAULT_SIZE;

            this.resetData();
        }

        public ProblemAndSolver(int seed)
        {
            this._seed = seed;
            rnd = new Random(seed);
            this._size = DEFAULT_SIZE;

            this.resetData();
        }

        public ProblemAndSolver(int seed, int size)
        {
            this._seed = seed;
            this._size = size;
            rnd = new Random(seed); 
            this.resetData();
        }
        #endregion

        #region Private Methods

        /// <summary>
        /// Reset the problem instance.
        /// </summary>
        private void resetData()
        {

            Cities = new City[_size];
            Route = new ArrayList(_size);
            bssf = null;

            if (_mode == HardMode.Modes.Easy)
            {
                for (int i = 0; i < _size; i++)
                    Cities[i] = new City(rnd.NextDouble(), rnd.NextDouble());
            }
            else // Medium and hard
            {
                for (int i = 0; i < _size; i++)
                    Cities[i] = new City(rnd.NextDouble(), rnd.NextDouble(), rnd.NextDouble() * City.MAX_ELEVATION);
            }

            HardMode mm = new HardMode(this._mode, this.rnd, Cities);
            if (_mode == HardMode.Modes.Hard)
            {
                int edgesToRemove = (int)(_size * FRACTION_OF_PATHS_TO_REMOVE);
                mm.removePaths(edgesToRemove);
            }
            City.setModeManager(mm);

            cityBrushStyle = new SolidBrush(Color.Black);
            cityBrushStartStyle = new SolidBrush(Color.Red);
            routePenStyle = new Pen(Color.Blue,1);
            routePenStyle.DashStyle = System.Drawing.Drawing2D.DashStyle.Solid;
        }

        #endregion

        #region Public Methods

        /// <summary>
        /// make a new problem with the given size.
        /// </summary>
        /// <param name="size">number of cities</param>
        //public void GenerateProblem(int size) // unused
        //{
        //   this.GenerateProblem(size, Modes.Normal);
        //}

        /// <summary>
        /// make a new problem with the given size.
        /// </summary>
        /// <param name="size">number of cities</param>
        public void GenerateProblem(int size, HardMode.Modes mode)
        {
            this._size = size;
            this._mode = mode;
            resetData();
        }

        /// <summary>
        /// return a copy of the cities in this problem. 
        /// </summary>
        /// <returns>array of cities</returns>
        public City[] GetCities()
        {
            City[] retCities = new City[Cities.Length];
            Array.Copy(Cities, retCities, Cities.Length);
            return retCities;
        }

        /// <summary>
        /// draw the cities in the problem.  if the bssf member is defined, then
        /// draw that too. 
        /// </summary>
        /// <param name="g">where to draw the stuff</param>
        public void Draw(Graphics g)
        {
            float width  = g.VisibleClipBounds.Width-45F;
            float height = g.VisibleClipBounds.Height-45F;
            Font labelFont = new Font("Arial", 10);

            // Draw lines
            if (bssf != null)
            {
                // make a list of points. 
                Point[] ps = new Point[bssf.Route.Count];
                int index = 0;
                foreach (City c in bssf.Route)
                {
                    if (index < bssf.Route.Count -1)
                        g.DrawString(" " + index +"("+c.costToGetTo(bssf.Route[index+1]as City)+")", labelFont, cityBrushStartStyle, new PointF((float)c.X * width + 3F, (float)c.Y * height));
                    else 
                        g.DrawString(" " + index +"("+c.costToGetTo(bssf.Route[0]as City)+")", labelFont, cityBrushStartStyle, new PointF((float)c.X * width + 3F, (float)c.Y * height));
                    ps[index++] = new Point((int)(c.X * width) + CITY_ICON_SIZE / 2, (int)(c.Y * height) + CITY_ICON_SIZE / 2);
                }

                if (ps.Length > 0)
                {
                    g.DrawLines(routePenStyle, ps);
                    g.FillEllipse(cityBrushStartStyle, (float)Cities[0].X * width - 1, (float)Cities[0].Y * height - 1, CITY_ICON_SIZE + 2, CITY_ICON_SIZE + 2);
                }

                // draw the last line. 
                g.DrawLine(routePenStyle, ps[0], ps[ps.Length - 1]);
            }

            // Draw city dots
            foreach (City c in Cities)
            {
                g.FillEllipse(cityBrushStyle, (float)c.X * width, (float)c.Y * height, CITY_ICON_SIZE, CITY_ICON_SIZE);
            }

        }

        /// <summary>
        ///  return the cost of the best solution so far. 
        /// </summary>
        /// <returns></returns>
        public double costOfBssf ()
        {
            if (bssf != null)
                return (bssf.costOfRoute());
            else
                return -1D; 
        }

        /// <summary>
        ///  solve the problem.  This is the entry point for the solver when the run button is clicked
        /// right now it just picks a simple solution. 
        /// </summary>
        public void solveProblem()
        {
            int x;
            Route = new ArrayList();
            // this is the trivial solution. 
            for (x = 0; x < Cities.Length; x++)
            {
                Route.Add( Cities[Cities.Length - x -1]);
            }

            // call this the best solution so far.  bssf is the route that will be drawn by the Draw method. 
            bssf = new TSPSolution(Route);
            // update the cost of the tour. 
            Program.MainForm.tbCostOfTour.Text = " " + bssf.costOfRoute();
            // do a refresh. 
            Program.MainForm.Invalidate();

        }


        public int MaxStates = 0;
        public int BssfUpdates = 0;
        public int TotalStates = 0;
        public int TotalPrunes = 0;


        /*
        * Setup for the Branch and Bound algorithm
        */
        public void BranchAndBoundSetup()
		{
			// Get the length only once
			int len = Cities.Length;

			// Build the reduced cost matrix and get the initial bound
			double[,] boundingMatrix = new double[len, len];
			double bound = this.BuildReducedCostMatrix (ref boundingMatrix, len);
			State initialState = new State (bound, boundingMatrix);

			this.BranchAndBound(ref initialState, len, ref bound);
		}


        /*
        * The actual Branch and Bound algorithm
        */
        private void BranchAndBound (ref State state, int len, ref double bound)
        {
            MinHeap<State> S = new MinHeap<State>();
            S.Add(state); // Add the initial State to the queue
            TotalStates++;

            // Set the best solution so far to infinity
            State best_so_far = new State();
            best_so_far.Bound = Double.PositiveInfinity; // upper bound
            
            while (S.Count > 0)
            {
                if (this.timer.ElapsedMilliseconds >= 30000)
                {
                    break;
                }
                // Get the next smallest state and copy that to the include/exclude states
                if (S.Count > MaxStates)
                {
                    MaxStates = S.Count;
                }
                State s = S.ExtractDominating();
                State include = s.copy(len);
                State exclude = s.copy(len);
                TotalStates++;
                TotalStates++;

                // Find the location of the subproblem 
                int x = -1, y = -1; // Location of the next path
                this.findNextPath(ref s, len, ref x, ref y, ref include, ref exclude, ref best_so_far);
                if (x == -1 || exclude.Bound > best_so_far.Bound) { this.TotalPrunes++;  continue; } // Don't add if we finished/had an error or the exclude is too large
                
                S.Add(exclude);

                // Go all the way left(include) adding exclude states to the queue
                this.greedyBranchAndBound(ref S, ref include, len, ref best_so_far);
            }
	        if (!Double.IsInfinity (best_so_far.Bound)) 
	        {
		        this.BranchAndBoundDraw (ref best_so_far);
	        }
        }


        /*
        * Finds a greedy solution to a given problem, adding the exclude solutions to the queue
        */
        public int greedyBranchAndBound(ref MinHeap<State> S, ref State s, int len, ref State best_so_far)
        {
            State include = s.copy(len); // Include
            State exclude = s.copy(len); // Exclude
            TotalStates++;
            TotalStates++;

            // Find the location of the subproblem 
            int x = -1;
            int y = -1;
            this.findNextPath(ref s, len, ref x, ref y, ref include, ref exclude, ref best_so_far);

            if (x == -1 ) { this.TotalPrunes++;  return -1; } // Prune
            if (exclude.Bound < best_so_far.Bound) // Prune 
            {
                S.Add(exclude);
	        }
            else
            { this.TotalPrunes++; }
	        if (x == -1 ) { this.TotalPrunes++;  return -1; } // Prune
            if (include.Bound > best_so_far.Bound) { this.TotalPrunes++; return -1; } // Prune
            return greedyBranchAndBound(ref S, ref include, len, ref best_so_far);
            
        }


        /**
        * Greedily find the next path
        */
        private void findNextPath(ref State s, int len, ref int x, ref int y, ref State include, ref State exclude, ref State best_so_far)
        {
            double cost = 0.0;
            for (int i = 0; i < len; i++)
            {
                for (int j = 0; j < len; j++)
                {
                    if (s.BoundingMatrix[i,j] == 0)
                    {
                        double newCost = s.minCol(i, j, len) + s.minRow(i, j, len);
                        if (cost < newCost) // Get the location of the 0 with the largest difference in cost
                        {
                            cost = newCost;
                            x = i;
                            y = j;
                        }
                    }
                }
            }

            if (x == -1) { // the end of the line0
		        if (s.Bound < best_so_far.Bound && !s.isLoop(len))  // set BSSF
                {
                    BssfUpdates++;
                    best_so_far = s;
                }
                else
                {
                    this.TotalPrunes++;
                }
                return;
            } // The end of the line

            // Set the include state
            include.setRowToInfinity(x, len);
            include.setColumnToInfinity(y, len);
            include.BoundingMatrix[y, x] = Double.PositiveInfinity;
            include.calcBound(len);
            include.In.Add(x);
            include.Out.Add(y);

            // Set the exclude state
            exclude.setExcludeState(x, y, len);
            exclude.calcBound(len);
        }


        public void BranchAndBoundDraw(ref State s)
        {
            Route = new ArrayList();
            Route.Add(Cities[(int)s.In[0]]);
            int prev = (int)s.Out[0];
            Route.Add(Cities[prev]);
            
            for (int i = 1; i < s.Out.Count; i ++)
            {
                int index = -1;
                for (int j = 0; j < s.In.Count; j ++)
                {
                    if ((int)s.In[j] == prev)
                    {
                        index = j;
                        break;
                    }
                }
                prev = (int)s.Out[index];
                Route.Add(Cities[prev]);
            }

            // call this the best solution so far.  bssf is the route that will be drawn by the Draw method. 
            bssf = new TSPSolution(Route);
            // update the cost of the tour. 
            Program.MainForm.tbCostOfTour.Text = " " + bssf.costOfRoute();
            // do a refresh. 
            Program.MainForm.Invalidate();
        }


        /*
        * Build reduced cost matrix
        */
        private double BuildReducedCostMatrix(ref double[,] boundingMatrix, int len)
        {
	        double bound = 0.0;

	        double[] lowest_row_value = new double[len];

            // Set the default lowest row / column values
	        for (int i = 0; i < len; i++) 
	        {
		        lowest_row_value [i] = Double.PositiveInfinity;
	        }
	        double[] lowest_col_value = new double[len];
	        for (int i = 0; i < len; i++) 
	        {
		        lowest_col_value [i] = Double.PositiveInfinity;
	        }

            // Populate the bounding matrix -- find column reductions as you go
	        for (int i = 0; i < len; i++) 
	        {
		        for (int j = 0; j < len; j ++)
		        {
			        if (i == j) // The diagonal should be set to infinity
			        {
				        boundingMatrix [i, j] = Double.PositiveInfinity;
				        continue;
			        }

			        double cost = Cities [i].costToGetTo (Cities [j]);
			        boundingMatrix [i, j] = cost;


			        if (lowest_row_value [i] > cost)
                    {
				        lowest_row_value [i] = cost;
			        }
		        }
	        }

            // Reduce rows
            int k = 0;
	        foreach (double lowest in lowest_row_value)
            {
		        // Skip infinity and 0
		        if (Double.IsPositiveInfinity (lowest)) { continue; }
		        if (lowest == 0) { continue; }
                
		        bound += lowest; // Increment the bound and reduce the row
		        for (int j = 0; j < len; j++)
		        {
                    if (k == j) { continue; }
			        boundingMatrix [k, j] = boundingMatrix [k, j] - lowest;
		        }
		        k++;
	        }

	        // Find column reductions
	        k = 0;
	        for (; k < len; k++) // k is the row
	        {
		        for (int j = 0; j < len; j++) // j is the column
		        {
			        if (lowest_col_value [j] > boundingMatrix [k, j]) 
			        {
                        lowest_col_value [j] = boundingMatrix [k, j];
			        }
		        }
	        }

	        // Reduce columns
	        k = 0;
	        foreach (double lowest in lowest_col_value) {
		        // Skip infinity and 0
		        if (Double.IsPositiveInfinity (lowest)) { k++; continue; }
		        if (lowest == 0) { k++; continue; }

		        bound += lowest; // Increment the bound and reduct the column
		        for (int j = 0; j < len; j++)
                {
                    if (k == j) { continue; }
                    boundingMatrix [j, k] = boundingMatrix [j, k] - lowest;
		        }
		        k++;
	        }
            return bound;
        }

        #endregion
    }

}
