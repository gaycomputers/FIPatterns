#!/usr/bin/python

import sys, getopt

def strip_helper(to_strip):
    for line in to_strip:
        stripped = line.strip()
        if stripped == "== Fault details":
            return to_strip

def strip_files(file_name):
    dict_faults = {}
    with open(file_name, "r") as file_open:
        file_open = strip_helper(file_open)
        counter = 1
        buffer = ""
        category = ""
        for line in file_open:
            #print(line)
            buffer += line
            if(counter == 3):
                counter = 1
                dict_faults[category].append(buffer)
                category = ""
                buffer = ""
            elif(counter == 1):
                category = line
                if category not in dict_faults:
                    dict_faults[category] = []
                counter += 1
            else:
                counter += 1
    return dict_faults

def intersect(file_one, file_two):
    dict_one = strip_files(file_one)
    dict_two = strip_files(file_two)
    dict_intersection = {}
    for i in dict_one:
        for j in dict_two:
            if i == j:
                dict_intersection[i] = list(set(dict_one[i]).intersection(set(dict_two[i])))
    #dict_intersection = list(set(dict_one).intersection(set(dict_two)))
    print("==================== INTERSECTIONS ================")
    for i in dict_intersection:
        if len(dict_intersection[i]) > 0:
            print("========>"+i)
            for j in dict_intersection[i]:
                print(j)

def nonintersect(file_one, file_two):
    dict_one = strip_files(file_one)
    dict_two = strip_files(file_two)
    dict_nonintersection = {}
    for i in dict_one:
        dict_nonintersection[i] = []
    for i in dict_nonintersection:
        if(i in dict_two.keys()):
            dict_nonintersection[i] = list(set(dict_one[i]).difference(set(dict_two[i])))#list(set(dict_one[i]) ^ set(dict_two[i]))
        else:
            dict_nonintersection[i] = dict_one[i]

    #dict_intersection = list(set(dict_one).intersection(set(dict_two)))
    #print(dict_nonintersection)
    print("==================== NONINTERSECTION of "+file_one+"================")
    for i in dict_nonintersection:
        if len(dict_nonintersection[i]) > 0:
            print("========> "+str(len(dict_nonintersection[i]))+" fault(s) in " + i)
            for j in dict_nonintersection[i]:
                print(j)

#cookie cutter python getopts function
def main(argv): 
    file_one = ''
    file_two = ''
    try:
        opts, args = getopt.getopt(sys.argv[1:], "a:b:")
    except getopt.GetoptError:
        print ('compare.py -a <file_one> -b <file_two>')
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print ('compare.py -a <file_one> -b <file_two>')
            sys.exit()
        else:
            if opt == "-a":
                file_one = arg
            if opt == "-b":
                file_two = arg
    nonintersect(file_one, file_two)
    nonintersect(file_two,file_one)
    intersect(file_one, file_two)

if __name__ == "__main__":
    main(sys.argv[1:])