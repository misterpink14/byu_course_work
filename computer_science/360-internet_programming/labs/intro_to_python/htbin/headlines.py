#!/usr/bin/env python

import requests

from bs4 import BeautifulSoup

print 'Content-type: text/html'
print 
print '<h1>Headlines</h1><br>'
print

r = requests.get('http://news.google.com')

soup = BeautifulSoup(r.content)

stuff = soup.find_all('span', {'class':'titletext'});

for thing in stuff:
	print thing 
	print '<br>'
