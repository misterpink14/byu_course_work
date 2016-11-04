using System;
using System.Collections.Generic;
using System.Text;

namespace GeneticsLab
{
    class PairWiseAlign
    {
        
        /// <summary>
        /// Align only 5000 characters in each sequence.
        /// </summary>
        private int MaxCharactersToAlign = 5000; 

        /// <summary>
        /// this is the function you implement.
        /// </summary>
        /// <param name="sequenceA">the first sequence</param>
        /// <param name="sequenceB">the second sequence, may have length not equal to the length of the first seq.</param>
        /// <param name="resultTableSoFar">the table of alignment results that has been generated so far using pair-wise alignment</param>
        /// <param name="rowInTable">this particular alignment problem will occupy a cell in this row the result table.</param>
        /// <param name="columnInTable">this particular alignment will occupy a cell in this column of the result table.</param>
        /// <returns>the alignment score for sequenceA and sequenceB.  The calling function places the result in entry rowInTable,columnInTable
        /// of the ResultTable</returns>
        public int Align(GeneSequence sequenceA, GeneSequence sequenceB, ResultTable resultTableSoFar, int rowInTable, int columnInTable)
		{
			int result = 0;

			if (sequenceA.Sequence != sequenceB.Sequence) 
			{
				result = this.extraction ( sequenceA.Sequence,  sequenceB.Sequence);
				this.scoring(sequenceA.Sequence,  sequenceB.Sequence);
			}
			return result;
        }


		private int pos = -1;


		private int extraction ( string aSequence,  string bSequence)
		{
			int aLength = aSequence.Length;
			int bLength = bSequence.Length;

			if (aLength > MaxCharactersToAlign) 
			{
				aLength = MaxCharactersToAlign;
			}

			if (bLength > MaxCharactersToAlign) 
			{
				bLength = MaxCharactersToAlign;
			}

			Node[] row1 = new Node[bLength+1];
			Node[] row2 = new Node[bLength+1];
			setRowDefaults (ref row1, bLength);

			Node prev = new Node (0, null);
			row1 [0] = prev;

			// Set defaults
			for (int i = 0; i < bLength; i++) 
			{
				row1 [i+1] = new Node((i+1) * 5, prev);
				prev = row1 [i + 1];
			}

			prev = row1 [0];

			for (int i = 0; i < aLength; i++) // foreach row
			{
				row2 [0] = new Node ((i + 1) * 5, prev); // row to check -- row1 is the prev row
				for (int j = 0; j < bLength; j++) // foreach col
				{
					int cost = min (
			           5 + row1 [j + 1].value, // prev row, curr col
			           5 + row2 [j].value, // curr row, prev col
			           (diff (
				           ref aSequence, 
				           ref bSequence, 
				           i, 
				           j
			           ) + row1 [j].value)
		           );

					Node p;
					switch (this.pos) {
						case 1:
							p = row1 [j + 1];
							break;
						case 2:
							p = row2 [j];
							break;
						case 3:
							p = row1 [j];
							break;
						default:
							throw new Exception ("Broken link");
					}
					row2 [j+1] = new Node (cost, p);
				}
				row1 = row2;
				row2 = new Node[bLength+1];
			}

			return row1 [bLength].value;
		}


		private void setRowDefaults(ref Node[] row1, int bLength)
		{
			Node prev = new Node (0, null);
			row1 [0] = prev;

			// Set defaults
			for (int i = 0; i < bLength; i++) 
			{
				row1 [i+1] = new Node((i+1) * 5, prev);
				prev = row1 [i + 1];
			}
		}


		private void scoring( string aSequence,  string bSequence) 
		{
			int aLength = aSequence.Length;
			int bLength = bSequence.Length;

			if (aLength > MaxCharactersToAlign) 
			{
				aLength = MaxCharactersToAlign;
			}

			if (bLength > MaxCharactersToAlign) 
			{
				bLength = MaxCharactersToAlign;
			}

			Node[,] table = new Node [aLength+1, bLength+1];
			this.setTableDefaults (ref table, aLength, bLength);

			for (int i = 0; i < aLength; i++) 
			{
				for (int j = 0; j < bLength; j++)
				{
					int cost =  min (
						5 + table [i, j+1].value, // prev row, curr col
						5 + table [i+1, j].value, // curr row, prev col
						(diff (
							ref aSequence, 
							ref bSequence, 
							i, 
							j
						) + table [i, j].value)
					);

					Node prev;
					char c = '-';
					switch (this.pos) {
						case 1:
							prev = table [i, j+1];
							break;
						case 2:
							prev = table [i+1, j];
							break;
						case 3:
							c = aSequence [i];
							prev = table [i, j];
							break;
						default:
							throw new Exception ("Broken link");
					}
					table [i+1, j+1] = new Node (cost, prev, c);
				}
			}
			this.getValue(table[aLength, bLength]);
		}

		private void getValue(Node n) 
		{
			List<char> clist = new List<char> ();
			string str = "";
			clist.Add (n.c);
			while (n.prev != null) 
			{
				clist.Add (n.c);
				n = n.prev;
			}

			clist.Reverse ();
			foreach(char c in clist) 
			{
				str += c;
				if (str.Length == 100) {
					break;
				}
			}

			Console.WriteLine (str);
		}


		private int diff (ref string aSequence, ref string bSequence, int i, int j)
		{
			char a = aSequence [i];
			char b = bSequence [j]; 
			if (a == b)
			{
				return -3;
			}
			else 
			{
				return 1;
			}
		}


		private int min(int i, int j, int k)
		{
			if (i < j) 
			{
				if (i < k) 
				{
					this.pos = 1;
					return i;
				}
			} 
			else 
			{
				if (j < k) 
				{
					this.pos = 2;
					return j;
				}
			}
			this.pos = 3;
			return k;
		}


		private void setTableDefaults(ref Node[,] table, int aLength, int bLength)
		{                                                                                                                                                                                                                          
			Node prev = new Node (0, null, ' ');
			table [0, 0] = prev;

			for (int i = 0; i < aLength; i++) 
			{
				table [i+1, 0] = new Node((i+1) * 5, prev, '-');
				prev = table [i+1, 0];
			}

			prev = table [0, 0];

			for (int j = 0; j < bLength; j++) 
			{
				table [0, j+1] = new Node((j+1) * 5, prev, '-');
				prev = table [0, j+1];
			}
		}
    }
}