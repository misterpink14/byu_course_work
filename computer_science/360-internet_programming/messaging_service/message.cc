#include "message.h"


Message::Message (stringstream &iss) {
    string arg = "";
    int arg_value = 0;
    int bytes = 0;
    isNeeded = false;

    string value;
    string line;
    if (!getline(iss, line))
    {
        exit(-1);
    }
    stringstream ss (line);
    if (ss >> command)
    {
        if (command == "put")
        {
            if (ss >> value)
            {   // name
                params.push_back(value);
                if (ss >> value)
                {   // subject
                    params.push_back(value);
                    if (ss >> value)
                    {   // length
                        params.push_back(value);
                        if (stoi(value) != 0)
                        {
                            isNeeded = true;
                        }
                    }
                    else
                    {
                        cout << "message2 \n";
                        exit(-1);
                    }
                }
                else 
                {
                    cout << "message3 \n";
                    exit(-1);
                }
            }
            else
            {
                cout << "message4\n";
                exit(-1);
            }
        }
        else if (command == "list")
        {
            if(ss >> value)
            {   // name
                params.push_back(value);
            }
            else
            {
                cout << "message5\n";
            }
        }
        else if (command == "get")
        {
            if (ss >> value)
            {   // name
                params.push_back(value);
                if (ss >> value)
                {   // index
                    params.push_back(value);
                }
                else
                {
                    cout << "message6\n";
                }
            }
            else
            {
                cout << "message7\n";
            }

        }
        else if (command == "reset")
        {
            true;
        }
        else
        {
            cout << "message1 : " << command << endl;
            exit(-1);
            // invalid
        }
    }
    else
    {
        cout << "message4 exit -1" << endl;
        exit(-1);
    }

    line = "";
    string t;
    while (getline(iss, t))
    {
        line += t + "\n";
    }
    iss.str(string());
    iss.clear();
    iss << line;
}
