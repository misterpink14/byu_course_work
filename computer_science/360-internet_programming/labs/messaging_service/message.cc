#include "message.h"


Message::Message (stringstream &iss) {
    string arg = "";
    int arg_value = 0;
    int bytes = 0;
    isNeeded = false;
    string value;
    string line;

    if (!getline(iss, line)) // there was an error
    {
        return;
    }

    // Used for parsing
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
                        iss.str(string());
                        iss.clear();
                        command = "error";
                        return;
                    }
                }
                else 
                {
                    iss.str(string());
                    iss.clear();
                    command = "error";
                    return;
                }
            }
            else
            {
                iss.str(string());
                iss.clear();
                command = "error";
                return;
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
                iss.str(string());
                iss.clear();
                command = "error";
                return;
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
                    iss.str(string());
                    iss.clear();
                    command = "error";
                    return;
                }
            }
            else
            {
                iss.str(string());
                iss.clear();
                command = "error";
                return;
            }

        }
        else if (command == "reset")
        {
            true;
        }
        else
        { 
            iss.str(string());
            iss.clear();
            command = "error";
            return;
        }
    }
    else // this wont ever happen
    {
        exit(-1);
    }

    string t;
    
    ss.str(string());
    ss.clear();

    bool isFirst = true;
    while (getline(iss, t))
    {
        if (isFirst)
            ss << t;
        else 
            ss << "\n" << t;
    }

    iss.str(string());
    iss.clear();
    iss << ss.str();
}
