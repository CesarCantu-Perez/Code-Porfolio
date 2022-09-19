#Name: Cesar Cantu-Perez
#ID: 1001463763
#Date: 4/7/2022
#OS: Windows 10 (using Python 3.10.2)

import os

#Using the os library to find a path to input_RPN.txt that way it will work on any PC as long as its in the same folder
path = os.path.basename("input_RPN.txt")
file = open(path, "r")
#For this lab I decided to use a stack to hold the values since this is postfix notation
stack = []
#I created a variable called answer to hold the last answer that was given from the operations that will be done
answer = 0
#Using readlines(), I was able to split the input line by line allowing the program to work line by line
RPNs = file.readlines()
#I needed a double for loop to iterate through every symbol on each line
for line in RPNs:
    for i in line:
        #if the current symbol in the input is a number I needed to add it to the stack using append()
        if i.isdigit() == True:
            stack.append(i)
        #whenever the current symbol in the input is an operator (+,-,*,/) I would do their respective operation and then append the answer to the stack
        elif i == '+':
            answer = int(stack.pop()) + int(stack.pop())
            stack.append(answer)
        elif i == '-':
        #I switched the numbers around so that that it would subtract properly
            secondNum = int(stack.pop())
            firstNum = int(stack.pop())
            answer = firstNum - secondNum
            stack.append(answer)
        elif i == '*':
            answer = int(stack.pop()) * int(stack.pop())
            stack.append(answer)
        elif i == '/':
            #When doing division I noticed that the program would switch the intended divisor and divided resulting in the wrong answer
            #To fix this problem I made the first number popped from the stack the divisor and then the other number was the dividend
            divisor = int(stack.pop())
            dividend = int(stack.pop())
            answer = dividend / divisor
            stack.append(answer)
        #Whenever a line ended I had the program print the last answer given
        elif i == '\n' or '':
            print(answer)
file.close()
#The program would not print the answer to the final line in the loop so I printed it after closing the file
print(answer)

