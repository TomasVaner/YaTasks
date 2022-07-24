#we assume that user does not input incorrect strings instead of numbers
numbers = input().split()
str_len = int(numbers[0])
count = int(numbers[1])

#we also will assume that all strings are the length of str_len
for pair_iter in range(count):
    strings = input().split()
    str_closest = "" #the result
    hamming = [0, 0] #hamming distances from different strings
    for str_iter in range(str_len):
        if strings[0][str_iter] == strings[1][str_iter]: #if strings match at the index
            str_closest += strings[0][str_iter] #we just use the symbol at the index 
        else: #else we should decide which string's symbol to use
            if hamming[0] >= hamming[1]: #we are further from left than from the right string or are equally distanced
                str_closest += strings[0][str_iter]
                hamming[1] += abs(ord(strings[0][str_iter]) - ord(strings[1][str_iter]))
            else: #we are further from right string
                str_closest += strings[1][str_iter]
                hamming[0] += abs(ord(strings[0][str_iter]) - ord(strings[1][str_iter]))
    print(str_closest)

"""
if we need to improve the algorithm further and make it work with general strings
instead of only strings consisting of 0s and 1s we would need to rework the 
last part of the algorithm. We would find such a symbol thet would make distances
as equal as possible. And prefer one of the strings as in the algorithm above.
My solution prefers to make string closer to the left than to right. Yet again
the algorithm can be improved by changing how to handle such situation: take a 
random (left, right) symbol in such case, or alternate preferred string as we go
through
"""