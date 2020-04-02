import os
import tarfile
from os import listdir

import re

os.chdir('/home/tek/Documents/csc344')
for i in range(5):


    identifire = set()
    regex = re.compile('//.*|;;.*|%%.*|#.*|\'.*\'|\".*\"|\.|\?|;|!|,|~|\^|\*|\n|\s|%|\[|\]|\{|\}|\(|\)|<|>|-\W|-\d|\+|:|&|\||=|\'|[0-9+]')
    files = [f for f in listdir('/home/tek/Documents/csc344/a'+str(i+1))]
    count = 0
    for f in files:

        file = open("a"+ str(i+1)+"/" + f, "r")

        for line in file:
            count = count+1
            for word in re.split(regex, line):
                 identifire.add(word)

    summaryfile = open("a" + str(i + 1) + "/summary_a" + str(i + 1) + ".html", "w+")
    summaryfile.write("<!DOCTYPE html>\n<html>\n<head>\n")
    summaryfile.write("</head>\n")
    summaryfile.write("<body>\n<h2>Assingment " + str(i + 1) + " documents:</h2>\n")
    summaryfile.write("<h3>Number of Lines:</h3>\n")
    summaryfile.write(str(count))
    summaryfile.write("<h3>list of identifiers:</h3>\n")
    for x in identifire:
        if x: summaryfile.write(x + "\n")
    summaryfile.write("</body>\n</html>")
    summaryfile.close()


    index = open("./index.html", "w+")
    index.write("<!DOCTYPE html>\n<html>\n<head>\n")
    index.write("<title>Class Summary</title>\n</head>\n")
    index.write("<body>\n<h2>Links to summary documents:</h2>\n")

    index.write("<a href='a1/summary_a1.html'>C-Project</a><br>\n")
    index.write("<a href='a2/summary_a2.html'>Clojure</a><br>\n")
    index.write("<a href='a3/summary_a3.html'>Scala</a><br>\n")
    index.write("<a href='a4/summary_a4.html'>Prolog</a><br>\n")
    index.write("<a href='a5/summary_a5.html'>Python</a><br>\n")
    index.close()
    os.chdir('/home/tek/Documents')
    tar = tarfile.open("python.tar.gz", "w:gz")
    for name in ["csc344"]:
        tar.add(name)
    tar.close()
    email = input("Enter email: ")
    os.system('mutt -s "python" ' +email+ ' -a /home/tek/Documents/python.tar.gz ')