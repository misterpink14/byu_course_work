using System;

namespace GeneticsLab
{
    public class Node
    {
        public Node()
        {
        }

        public Node(int value)
        {
            this.value = value;
        }

        public Node(int value, Node prev)
        {
            this.value = value;
            this.prev = prev;
        }

        public Node(int value, Node prev, char c)
        {
            this.value = value;
            this.prev = prev;
            this.c = c;
        }



        public Node prev = null;
        public int value;
        public char c;
    }
}

