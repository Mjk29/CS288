import libxml2
import sys
import os
import commands
import re
import sys

import MySQLdb

import requests


from xml.dom.minidom import parse, parseString

from bs4 import BeautifulSoup

# for converting dict to xml 
from cStringIO import StringIO
from xml.parsers import expat



def html_to_xml(fn):
	print("test")
	# for x in fn:
	# 	print(x)

	# return xhtml_file




def main():
	

	# page = requests.get("http://forecast.weather.gov/MapClick.php?lat=37.7772&lon=-122.4168")
	# soup = BeautifulSoup(page.content, 'html.parser')
	# seven_day = soup.find(id="seven-day-forecast")
	# forecast_items = seven_day.find_all(class_="tombstone-container")
	# tonight = forecast_items[0]
	# print(tonight.prettify())


	html_fn = open(sys.argv[1])
	soup = BeautifulSoup(html_fn, 'html.parser')
	html_fn.close()

	tableData=soup.find("table", attrs={"class":"column0"})

	# tableData=soup.find_all(id="column0")

	print(type(tableData))

	# for x in tableData:
	# 	print x

	# print(tableData.childNode)

	# global dom
	# dom = parse(html_fn)


	# data = []

	# col=soup.find('column0', attrs=)

	# print(type(col))


	# table = soup.find('table', attrs={'class':"mdcTable"})
	# table_body = table.find('column0')

	# print(type(table_body))

	# rows = table_body.find_all('tr')
	# for row in rows:
	# 	cols = row.find_all('td')
	# 	cols = [ele.text.strip() for ele in cols]
	# 	data.append([ele for ele in cols if ele])
	# 	# print(row) 


	# print(type(rows))

	# for row in rows:
	# 	print(row)


	# # table = soup.find(id="tbody")

	# table = soup.find_all("table", {"class":"mdcTable"})

	# print(type(table_body))
	# for x in table_body:
	# print(table_body)

	# print(table.attributes)

	# for x in table:
	# 	print(type(x))


	# print(table.pretify())
	# dong=soup.find_all('p')[0].get_text()
	# print(dong)


	# print(soup.prettify())

	# dong=list(soup.children)[1]
	# print(dong)

	# import re
	# for tag in soup.find_all("title"):
	# 	print(tag.name)




	# print(soup.find_all('div'))




	# link = soup.a
	# link
	# <a class="sister" href="http://example.com/elsie" id="link1">Elsie</a>
	# for parent in link.parents:
	#     if parent is None:
	#         print(parent)
	#     else:
	#         print(parent.name)


	# print(soup.pretify())

	# for x in soup:
	# 	print(x)

	# for x in html_fn:
	# 	print(x)

	# fn = html_fn.replace('.html','')
	# xhtml_fn = html_to_xml(html_fn)

	# outfile = open('output.txt','w')
	# for x in soup:
	# 	outfile.write(soup)

	# outfile.close()


	pass






if __name__ == "__main__":
	main()


