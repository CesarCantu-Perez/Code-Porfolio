#Name: Cesar Cantu-Perez
#ID: 1001463763
#Date: 4/26/2022
#OS: Windows 10 (using Python 3.10.2)

import os

#Using the os library to find a path to input.txt so that input.txt just needs to be in the same folder as this program
path = os.path.basename("input.txt")
file = open(path, "r")
#I created a few variables called indentCount and comment, indent count will be used to keep track the nesting depth of input.txt
#comment is used to check if the current tokens are in a comment or not, comment needs to be 2 or more to be considered a comment
indentCount = 0
comment = 0
#I also created a few boolean variables to be able to establish certain conditions that would arise
#backIndent is set to 0 and would be set to 1 if the indent is a } meaning it is the end of a block which still needs to be indented like the first part of the block
#ignore is set to 0 and would be set to 1 if we current tokens are in quotation marks ("") and it would be set to 2 when the tokens are in a comment
#multicomment is a boolean variable that indicates if the current comment is a multiline comment (/*.....*/)
#endcomment is used to determine if the comment is going to end or not it becomes 1 when the "/" is read and would be set back to 0 once the comment ends or when something other than a "*" is read
backIndent = 0
ignore = 0
multiComment = 0
endComment = 0
#Using readlines(), I was able to split the input line by line allowing the program to work line by line
fileInput = file.readlines()
#I needed a double for loop to iterate through every symbol on each line
for line in fileInput:
    #comment and ignore need to be set to 0 at the beginning of each line
    comment = 0
    ignore = 0
    #comment should not be set to 0 if the comment is a multiline comment
    if multiComment == 1:
        comment = 2
    for i in line:
        #this checks if the line is set to be a comment so it ignores everything in the line (except for the multicomment ending code)
        if comment == 2 or multiComment == 1:
            ignore = 2
        #this checks for the "{" and if it does find one then the indentCount increses to reflect the current depth level
        if i == '{':
            endComment = 0
            if ignore == 0:
                indentCount += 1
        #this is like the previous comment but it also uses the backIndent to flag that the indent should stay the same for this one line
        elif i == '}':
            endComment = 0
            if ignore == 0:
                indentCount -= 1
                backIndent = 1
        #whenever a " is read from the file, it will continue to ignore everything until another " is read
        elif i == '"':
            endComment = 0
            if ignore == 0:
                ignore = 1
            elif ignore == 1:
                ignore = 0
        #when the / is read, it would increase by 1 but comment needs to be more than 1 so the // would work also, reading a / after reading a * will end a multi line comment
        elif i == '/':
            if ignore == 0:
                comment += 1
            elif endComment == 1:
                multiComment = 0
                endComment = 0
                comment = 0
        elif i == '*':
            if comment > 0 and multiComment == 0:
                multiComment = 1
            elif multiComment == 1:
                endComment = 1
    #this would check if the } is used to display the depth correctly
    if backIndent == 1:
        print(indentCount + 1 , end = line)
        backIndent = 0
    else:
        print(indentCount, end = line)
#this is an error checker to see if the number of { and } match
if indentCount > 0:
        print("")
        print("Error: expected '}' but found EOF. Output may be incorrect.")
if indentCount < 0:
        print("")
        print("Error: Too many '}'. Output may be incorrect.")
file.close()
