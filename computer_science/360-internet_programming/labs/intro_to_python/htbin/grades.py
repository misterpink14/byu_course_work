#!/usr/bin/env python

import fileinput

print 'Content-type: text/html'
print 
for line in fileinput.input(["grades.txt"]):
  if not line or line == "":
    continue
  elif (line[0]) == '#':
    temp_list = line.split(" ")
    print "<h2>" + temp_list[1] + " " + temp_list[2] + "</h2>"
  else:
    temp_list = line.split(" ")
    if not len(temp_list) == 2:
      continue
    print temp_list[0] + "<br>"
    print temp_list[1] + "<br>"

