using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace primality_test
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /**
         * Click solve button action
         * 
         */
        private void solve_Click(object sender, EventArgs e)
        {
            // Get values from the textboxes - Convert to int
            int N = 0;
            int k = 0;
            try
            {
                N = Convert.ToInt32(input.Text);
                k = Convert.ToInt32(k_value.Text);
            } // TODO: use a less generic exception
            catch (Exception ex)    // If the text cannot be converted to int, it will throw an Exception
            {   // Error message and return
                output.Text = "Enter a integer";
                return;
            }

            // Reset the output Text
            output.Text = "";

            // Check for valid input
            bool isValid = true;
            if (N < 1)
            {
                isValid = false;
                output.Text += "N must be positive\n";
            }
            if (k < 1)
            {
                isValid = false;
                output.Text += "k must be positive\n";
            }
            if (!isValid)
            {
                return;
            }

            // Find the probability of N being prime
            double result = primality(N, k);
            if (result == 0.0) // Not prime
            {
                output.Text = "No";
            }
            else // Most likely prime
            {
                output.Text = "Yes, with a probability of " + (result);
            }
        }

        /*
         * Primality Test
         * 
         *  @param N    positive integer - find prime status
         *  @param k    positive integer - number of attempts we will take
         *  @return     positive double - probability of being prime, 
         *                      0.0 indicates the number is not prime
         * 
         */
        private double primality(int N, int k)
        {
            // Build a list 1 to one less than N (in this case N-1 values)
            var number_list = new List<int>();
            number_list.AddRange(Enumerable.Range(1, N - 1));

            // Randomize the list
            Random rand = new Random();
            number_list = number_list.OrderBy(item => rand.Next()).ToList();

            // If k is too large, reassign it to the max value
            if (k > N-1)
            {
                k = N-1;
            }

            double ret = 1.0; // Return value - probabiliy of not being prime

            // Loop through k times (requested amount of user, or max amount)
            for (int i = 0; i < k; i++) // n^3
            {
                // Calculate number_list[i] ^ N - 1
                long exp = modexp(number_list[i], N-1, N); // n^2
                if (exp == 1 % N) // Could be prime
                {
                    if (ret == 1.0)
                    {
                        ret = .5;
                    }
                    else
                    {
                        ret /= 2;
                    }
                }
                else // Not Prime
                {
                    return 0.0;
                }
            }

            return 1.0 - ret;
        } // n^3

        /**
         * Find the solution to x^y mod N
         * 
         * @param x     positive integer
         * @param y     positive integer
         * @param N     positive integer
         * 
         */
        private int modexp(int x, int y, int N)
        {
            if (y == 0)
            {
                return 1;
            }

            // Remove a bit from y
            int z = modexp(x, y / 2, N);

            if ((y % 2) == 0)   // even
            {
                return (z * z) % N;
            }
            else // odd
            {
                return (x * z * z) % N;
            }
        } // n^2
    }
}
