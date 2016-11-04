#include "Tree.h"


using namespace std;


/*******************************************
*
*	Main Function
*
********************************************/
int main(int argc, char* argv[])
{
	string cmd;
	string item;
	Tree<string> ll;

	ifstream in;
	ofstream out;

	in.open(argv[1]);
	out.open(argv[2]);

	while (in >> cmd)
	{
		out << cmd;
		if (cmd == "add")
		{
			in >> item;
			out << " " << item;
			ll.Add(item);
		}
		else if (cmd == "remove")
		{
			in >> item;
			out << " " << item;
			ll.Remove(item);
		}
		else if (cmd == "find")
		{
			in >> item;
		//	out << " " << item << " " << ll.Find(item);
		}
		else if (cmd == "print")
		{
			ll.Print(out);  ///
		}
		else // (clear)
		{
//			ll.Clear();
		}
		out << endl;
	}
	//delete ll;
	out.close();
	in.close();
}
