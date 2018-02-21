import re
from xml.dom.minidom import parse, parseString 

def process_dom_tree(dm):
	lst = []
	# elms = dm.getElementsByTagName('book')
	# print elms.length,elms
	
	# ass=dm.getElementsByTagName("title")
	# lst=map(lambda x: get_text(x), ass) 
	# for x in lst:
	# 	print x

	lst=dom.getElementsByTagName("bookstore")
	elements = map(lambda x: get_text(x),lst)[0]



	for x in elements:
		print x


	# print elements


	# lst=map(lambda x: get_text(x), ass) 
	
	# cocks=dom.childNodes

	# nig=cocks[0]
	# print nig.nodeName

	# for x in lst:
	# 	print type(x.childNodes)
	

	# for x in ass:
	# 	print (x.firstChild.nodeValue)
	# 	if x.firstChild.nodeValue :
	# 		print (x.getAttribute("title").value)


	# for x in ass:
	# 	# cocks= x.getElementsByTagName("year")
	# 	print x.nodeType



	# for x in ass:
	# 	print x.hasAttribute("year")

	# for elm in elms:
	# 	l = get_text(elm)
	# 	lst.append(l)
	
	return lst

def get_text(e):
	lst=[]
	if e.nodeType in (3,4):
		if e.data!='\n':
			lst.append(e.data)
	else:
		for x in e.childNodes:
			lst=lst+get_text(x)
	return lst





def main():
	lst = []
	global dom
	dom = parse('bookstore.xml')
	lst = process_dom_tree(dom)
	return lst


if __name__ == "__main__":
	main()



