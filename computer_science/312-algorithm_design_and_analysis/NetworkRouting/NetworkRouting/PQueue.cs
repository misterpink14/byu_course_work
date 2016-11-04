using System;
using System.Collections.Generic;

namespace NetworkRouting
{
	/**
	 * Priority Queue implementation.
	 * 
	 */
	public class PQueue <D> where D : Node, IComparable, IEquatable<D>
    {
		private List<D> heap = new List<D>();
		public List<int> l = new List<int>();

		public PQueue () { }

		/**
		 * Return the heap's count
		 * 
		 */
		public int Count { get { return heap.Count; } }  

		/**
		 * Similar to a push.
		 * 
		 */
		public void Insert(D i, bool isOne = false)
		{
			if (isOne)
				l [i.index] = this.Count;
			BubbleUp (i);
		}

        
		public int FindIndex(int i)//(D dt)
        {
			return l [i];
//            int location = 0;
//            foreach (D curr in heap)
//            {
//                if (dt.Equals(curr))
//                {
//                    break;
//                }
//                location++;
//            }
//
//            return location;
        }

		/**
		 * 	Similar to a pop.
		 * 
		 */
		public D DeleteMin()
		{
			D min = heap[0];
			Node n = (Node)min;
			l [n.index] = -1;
			l [heap[heap.Count - 1].index] = 0;
			heap[0] = heap[heap.Count - 1];
			heap.RemoveAt(heap.Count - 1);
			this.MinHeapify(0);  
			return min;  
		}

		private void MinHeapify(int i)
		{
			// Children
			int left = i * 2;
			int right = i * 2 + 1;
			int smallest = i;

			if (left < heap.Count && (heap[left].CompareTo(heap[smallest]) < 0))  
			{
				smallest = left;
			}
			if (right < heap.Count && (heap [right].CompareTo (heap [smallest]) < 0)) 
			{
				smallest = right;
			}

			if (smallest != i) 
			{
				D temp = heap [i];
				heap[i] = heap[smallest];
				heap[smallest] = temp;
				l [heap[i].index] = smallest;
				l [heap[smallest].index] = i;
				MinHeapify (smallest);
			}
		}

		public void DecreaseKey(int i)
		{
			int parent = i / 2;
			while (heap [parent].CompareTo(heap [i]) > 0) 
			{
				D temp = heap [parent];
				heap [parent] = heap [i];
				heap [i] = temp;
				i = parent;
				parent = parent / 2;

				l [heap[i].index] = parent;
				l [heap[parent].index] = i;
			}
		}

		private void BubbleUp(D dt)
		{

			heap.Add(dt);

			int i = heap.Count - 1;
			while (i > 0)  
			{
				int j = (i + 1) / 2 - 1;  

				// Check if this needs to bubble up
				D val = heap[j];  
				if (val.CompareTo(heap[i]) < 0 || val.CompareTo(heap[i]) == 0)  
				{  
					break;  
				}  

				// Swap the elements  
				D tmp = heap[i];  
				heap[i] = heap[j];  
				heap[j] = tmp;  

				i = j;  
			}
		}

		public static PQueue <D> MakeQueue(List<D> points)
		{
			var q = new PQueue <D> ();
			int i = 0;
			for (i = 0; i < points.Count; i++)
			{
				q.l.Add(i);
			}
			i = 0;
            foreach(D pt in points)
            {
                q.Insert(pt);
            }
			foreach (D pt in q.heap) 
			{
				q.l [pt.index] = i;
				i++;
			}
			return q;
		}

		public void prepL(List<D> points)
		{
			for (int i = 0; i < points.Count; i++) {
				l.Add (-1);
			}
		}
			
	}



    public class Node : IComparable, IEquatable<Node>
    {
        public int index;
        public double dist;
        public Node prev;
        

        public Node () { }

        public Node (int i, double l, Node p) { this.index = i; this.dist = l; this.prev = p; }

        public int CompareTo(object obj)
        {
            Node n = (Node)obj;

            if (n.dist == this.dist)
            {
                return 0;
            }
            
            if (this.dist < n.dist)
            {
                return -1;
            }
            return 1;
        }

        public override string ToString()
        {
            return "Node: " + index + " " + dist;
        }

        public bool Equals(Node other)
        {
            bool ret = (this.index == other.index);
            return ret;
        }
    }
}


