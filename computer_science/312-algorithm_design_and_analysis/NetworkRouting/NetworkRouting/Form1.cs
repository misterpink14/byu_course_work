using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace NetworkRouting
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void generateButton_Click(object sender, EventArgs e)
        {
            int randomSeed = int.Parse(randomSeedBox.Text);
            int size = int.Parse(sizeBox.Text);

            Random rand = new Random(randomSeed);
            seedUsedLabel.Text = "Random Seed Used: " + randomSeed.ToString();

            this.adjacencyList = generateAdjacencyList(size, rand);
            List<PointF> points = generatePoints(size, rand);
            resetImageToPoints(points);
            this.points = points;
            startNodeIndex = -1;
            stopNodeIndex = -1;
            sourceNodeBox.Text = "";
            targetNodeBox.Text = "";
        }

        // Generates the distance matrix.  Values of -1 indicate a missing edge.  Loopbacks are at a cost of 0.
        private const int MIN_WEIGHT = 1;
        private const int MAX_WEIGHT = 100;
        private const double PROBABILITY_OF_DELETION = 0.35;

        private const int NUMBER_OF_ADJACENT_POINTS = 3;

        private List<HashSet<int>> generateAdjacencyList(int size, Random rand)
        {
            List<HashSet<int>> adjacencyList = new List<HashSet<int>>();

            for (int i = 0; i < size; i++)
            {
                HashSet<int> adjacentPoints = new HashSet<int>();
                while (adjacentPoints.Count < 3)
                {
                    int point = rand.Next(size);
                    if (point != i) adjacentPoints.Add(point);
                }
                adjacencyList.Add(adjacentPoints);
            }

            return adjacencyList;
        }

        private List<PointF> generatePoints(int size, Random rand)
        {
            List<PointF> points = new List<PointF>();
            for (int i = 0; i < size; i++)
            {
                points.Add(new PointF((float) (rand.NextDouble() * pictureBox.Width), (float) (rand.NextDouble() * pictureBox.Height)));
            }
            return points;
        }

        private void resetImageToPoints(List<PointF> points)
        {
            pictureBox.Image = new Bitmap(pictureBox.Width, pictureBox.Height);
            Graphics graphics = Graphics.FromImage(pictureBox.Image);
            foreach (PointF point in points)
            {
                graphics.DrawEllipse(new Pen(Color.Blue), point.X, point.Y, 2, 2);
            }

            this.graphics = graphics;
            pictureBox.Invalidate();
        }

        // These variables are instantiated after the "Generate" button is clicked
        private List<PointF> points = new List<PointF>();
        private Graphics graphics;
        private List<HashSet<int>> adjacencyList;

        // Use this to generate routing tables for every node
        private void solveButton_Click(object sender, EventArgs e)
        {
            if (startNodeIndex == -1 || stopNodeIndex == -1)
            {
                return;
            }
            // *** Implement this method, use the variables "startNodeIndex" and "stopNodeIndex" as the indices for your start and stop points, respectively ***

            dijkstrasAll();
            dijkstrasOne();
            double all = Double.Parse(this.allTimeBox.Text);
            double one = Double.Parse(this.oneTimeBox.Text);
            double diff = ((all - one) / all) *100;
            this.differenceBox.Text = diff.ToString();
        }

		private void dijkstrasAll()
		{
			Stopwatch watch = new Stopwatch();
			watch.Start();
			List<Node> g = new List<Node>();
			Node filler = null;
			Node n;

			for (int i = 0; i < adjacencyList.Count; i++)
			{
				if (i == startNodeIndex)
				{
					n = new Node(i, 0, filler);
					g.Add(n);
					continue;
				}
				n = new Node(i, double.MaxValue, filler);
				g.Add(n);
			}

			PQueue<Node> q = PQueue<Node>.MakeQueue(g);

			while (q.Count != 0)
			{
				Node u = q.DeleteMin();
				foreach (int v in adjacencyList[u.index])
				{
					double temp = u.dist + l(u.index, g[v].index);
					if (g[v].dist > temp)
					{
						int i = q.FindIndex(v);
						g[v].dist = temp;
						g[v].prev = u;
						if (i >= q.Count || i == -1)
							continue;
						q.DecreaseKey(i);
					}
				}
			}
			watch.Stop();
			TimeSpan ts = watch.Elapsed;
			string elapsedTime = ts.TotalSeconds.ToString();
			this.allTimeBox.Text = elapsedTime;
			this.DrawPath(g[stopNodeIndex], new Pen(Color.Red));
		}

		private void dijkstrasOne()
		{
			Stopwatch watch = new Stopwatch();
			watch.Start();
			List<Node> g = new List<Node>();
			Node filler = null;
			Node n;

			for (int i = 0; i < adjacencyList.Count; i++)
			{
				if (i == startNodeIndex)
				{
					n = new Node(i, 0, filler);
					g.Add(n);
					continue;
				}
				n = new Node(i, double.MaxValue, filler);
				g.Add(n);
			}
//
			PQueue<Node> q = new PQueue<Node>();
			q.prepL (g);
			q.Insert(g[this.startNodeIndex], true);

			bool breakout = false;

			while (q.Count != 0)
			{
				Node u = q.DeleteMin();
				foreach (int v in adjacencyList[u.index])
				{
					if (g [v].dist == double.MaxValue) {
						q.Insert (g [v], true);
					} else {
						continue;
					}

					double temp = u.dist + l(u.index, g[v].index);
					if (g[v].dist > temp)
					{
						int i = q.FindIndex(v);
						g[v].dist = temp;
						g[v].prev = u;
						if (i < q.Count || i != -1)
							q.DecreaseKey(i);
						if (v == stopNodeIndex)
						{
							breakout = true;
							break;
						}
					}
				}
				if (breakout)
				{
					break;
				}
			}
			watch.Stop();
			TimeSpan ts = watch.Elapsed;
			string elapsedTime = ts.TotalSeconds.ToString();
			this.oneTimeBox.Text = elapsedTime;
			this.DrawPath(g[stopNodeIndex], new Pen(Color.Black));
		}

        private void DrawPath(Node n, Pen pen)
        {
            this.pathCostBox.Text = n.dist.ToString();

            Node p = n.prev;
            while (n.prev != null)
            {
                graphics.DrawLine(pen, points[n.index], points[p.index]);

				// Draw the distance
				string distance = (n.dist - p.dist).ToString();
				PointF pt = new PointF ();	// Create a point to draw it at
				pt.X = Math.Abs(points [n.index].X + points [p.index].X)/2;
				pt.Y = Math.Abs(points [n.index].Y + points [p.index].Y)/2;
				graphics.DrawString (
					distance,
					new Font (
						this.Font, 
						FontStyle.Regular
					),
					new SolidBrush (Color.Black), 
					pt
				);
                
                n = p;
                p = p.prev;
            }
            pictureBox.Refresh();
        }

        private double l(int u, int v)
        {
            double x = Math.Pow(
                (points[u].X - points[v].X),
                2.0
            );
            double y = Math.Pow(
                (points[u].Y - points[v].Y),
                2.0
            );

            return Math.Sqrt(
                x+y
            );
        }

        private int GetIndex(ref List<Node> g, Node n)
        {
            int location = 0;
            g.ForEach(delegate (Node curr)
            {
                if (n.Equals(curr))
                {
                    return;
                }
                location++;
            });
            return location;
        }

        private Boolean startStopToggle = true;
        private int startNodeIndex = -1;
        private int stopNodeIndex = -1;
        private void pictureBox_MouseDown(object sender, MouseEventArgs e)
        {
            if (points.Count > 0)
            {
                Point mouseDownLocation = new Point(e.X, e.Y);
                int index = ClosestPoint(points, mouseDownLocation);
                if (startStopToggle)
                {
                    startNodeIndex = index;
                    sourceNodeBox.Text = "" + index;
                }
                else
                {
                    stopNodeIndex = index;
                    targetNodeBox.Text = "" + index;
                }
                startStopToggle = !startStopToggle;

                resetImageToPoints(points);
                paintStartStopPoints();
            }
        }

        private void paintStartStopPoints()
        {
            if (startNodeIndex > -1)
            {
                Graphics graphics = Graphics.FromImage(pictureBox.Image);
                graphics.DrawEllipse(new Pen(Color.Green, 6), points[startNodeIndex].X, points[startNodeIndex].Y, 1, 1);
                this.graphics = graphics;
                pictureBox.Invalidate();
            }

            if (stopNodeIndex > -1)
            {
                Graphics graphics = Graphics.FromImage(pictureBox.Image);
                graphics.DrawEllipse(new Pen(Color.Red, 2), points[stopNodeIndex].X - 3, points[stopNodeIndex].Y - 3, 8, 8);
                this.graphics = graphics;
                pictureBox.Invalidate();
            }
        }

        private int ClosestPoint(List<PointF> points, Point mouseDownLocation)
        {
            double minDist = double.MaxValue;
            int minIndex = 0;

            for (int i = 0; i < points.Count; i++)
            {
                double dist = Math.Sqrt(Math.Pow(points[i].X-mouseDownLocation.X,2) + Math.Pow(points[i].Y - mouseDownLocation.Y,2));
                if (dist < minDist)
                {
                    minIndex = i;
                    minDist = dist;
                }
            }

            return minIndex;
        }
    }
}
