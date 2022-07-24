def internalize(word, fix_len):
    #functions assumes correct fix_len value
    return ''.join((word[0:fix_len], str(len(word) - 2 * fix_len), word[-fix_len:]))


#read the data
count = int(input()) #assume only correct inputs there

words = [] #no need in set since there we are guaranteed that words are already unique

#just simple reading of word into the list
for index in range(count):
    word = input()
    words.append(word)

met_i10ns = {}

i10ns = [] #i10ns of the word by index2

#I decided to use the sets to check for repeated i10ns. Of course I could write a comprehensive algorithm to know in place if words would have the same i10ns
#but I think using a set would be an acceptable trade-off between used resources RAM vs CPU and also the simplicity of the code and time to write it

#let's iterate through words
for index in range(count):
    i10ns.append([])
    for fix_len in range(1, len(words[index])//2):
        i10n = internalize(words[index], fix_len)
        i10ns[-1].append(i10n)
        met_i10ns[i10n] = met_i10ns.setdefault(i10n, 0) + 1

for index in range(count):
    for i10n in i10ns[index]:
        if met_i10ns[i10n] == 1:
            print(i10n)
            break
    else:
        print(words[index])
