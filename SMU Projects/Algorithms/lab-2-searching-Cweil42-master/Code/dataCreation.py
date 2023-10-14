import os
import random

def rand(num):
    l = random.sample(range(0,num), num)
    with open((str(num)+"_Random.txt"), "x") as filehandle:
        filehandle.writelines("%s\n" % place for place in l)

def reverseSort(num):
    f = open((str(num)+"_Reverse.txt"), "x")
    for x in range(0, num):
        f.write(str(num-x)+"\n")
    f.close()

def twenty_percent_unique(num):
    l = random.sample(range(0,int(num/5)), int(num/5))
    for i in range(int(num/5),num):
        n = random.randint(int(num/5), int(num/5*2))
        l.append(n)
    random.shuffle(l)
    with open((str(num)+"_20%Unique.txt"), "x") as filehandle:
        filehandle.writelines("%s\n" % place for place in l)

def thirthy_percent_random(num):
    l = []
    for x in range(1, int(num+1)):
        if x%3 == 0:
            n = random.randint(num, int(num*2))
            l.append(n)
        else:
            l.append(x)
    with open((str(num)+"_30%Random.txt"), "x") as filehandle:
        filehandle.writelines("%s\n" % place for place in l)


num = 10
reverseSort(num)
rand(num)
twenty_percent_unique(num)
thirthy_percent_random(num)
num = 1000
reverseSort(num)
rand(num)
twenty_percent_unique(num)
thirthy_percent_random(num)
num = 10000
reverseSort(num)
rand(num)
twenty_percent_unique(num)
thirthy_percent_random(num)
num = 100000
reverseSort(num)
rand(num)
twenty_percent_unique(num)
thirthy_percent_random(num)

