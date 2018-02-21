

# CS288 Homework 9
# Read the skeleton code carefully and try to follow the structure
# You may modify the code but try to stay within the framework.

import libxml2
import sys
import os
import commands
import re
import sys

import MySQLdb

from xml.dom.minidom import parse, parseString

# for converting dict to xml 
from cStringIO import StringIO
from xml.parsers import expat

def get_elms_for_atr_val(tag):
	lst=[]
	elms = dom.getElementsByTagName(tag)
	# ............
	t=elms.item(2)
	lst=t.childNodes[1:]
	return lst

# get all text recursively to the bottom
def get_text(e):
	lst=[]
	# ............
	if e.nodeType in (3,4):
		if e.data!='\n':
			lst.append(e.data)
	else:
		for x in e.childNodes:
			lst=lst+get_text(x)
	return lst

# replace whitespace chars
def replace_white_space(str):
	p = re.compile(r'\s+')
	new = p.sub(' ',str)   # a lot of \n\t\t\t\t\t\t
	return new.strip()

	# replace but these chars including ':'
def replace(s):
	p = re.compile(r'[^a-zA-Z0-9-]+')
	#   p = re.compile(r'\W+') # replace whitespace chars
	new = p.sub('',s)
	return new.strip()

	# convert to xhtml
# use: java -jar tagsoup-1.2.jar --files html_file
def html_to_xml(fn):
	# ............
	xhtml_file=os.popen("java -jar tagsoup-1.2.jar --files "+fn)
	print(xhtml_file,"something before this line")
	type(xhtml_file)
	return xhtml_file

def extract_values():
	lst = []
	l = get_elms_for_atr_val('table')
	# ............
	lst=[get_text(e) for e in l]
	# ............

	return lst

def remove_num_id(lst):
	return [i[1:] for i in lst]

def fix_list(lst):
	test=lambda x: [x.split(' (')[0],x.split(' (')[1].split(')')[0]]
	return [test(i[0])+i[1:] for i in lst]

	# mysql> describe most_active;
def insert_to_db(l,tbl):
	# ............
	conn=MySQLdb.connect(host='localhost',user='cs288',passwd='cs288pw',db='stock_market')
	cursor=conn.cursor()
	cmd='create table '+tbl+'(symbol varchar(10),name varchar(80),price float,chng float,pchng float,volume integer)'
	cursor.execute(cmd)

	for i in l:
		cmd='insert into '+tbl+" values('"+i[1]+"','"+i[0]+"',"+replace(i[3])+','+i[4]+','+i[5]+','+replace(i[2])+')'
		cursor.execute(cmd)
	conn.commit()

	# show databases;
	# show tables;
def main():
	'''
	html_fn = sys.argv[1]
	fn = html_fn.replace('.html','')
	xhtml_fn = html_to_xml(html_fn)
	'''
	xhtml_fn = sys.argv[1]
	fn = xhtml_fn.replace('.xhtml','')

	global dom
	dom = parse(xhtml_fn)
	print("after parsing")

	# lst = extract_values()
	# print("after extracting")
	# lst = remove_num_id(lst)
	# print("removed first")
	# lst = fix_list(lst)

	# # make sure your mysql server is up and running
	# cursor = insert_to_db(lst,fn) # fn = table name for mysql
	'''
	l = select_from_db(cursor,fn) # display the table on the screen

	# make sure the Apache web server is up and running
	# write a PHP script to display the table(s) on your browser

	return xml
	# end of main()
	'''

if __name__ == "__main__":
	print("start of main")
	main()

print("END OF ")
# end of hw7.py

