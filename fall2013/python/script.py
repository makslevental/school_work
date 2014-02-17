pyg = 'ay'

original = raw_input('Enter a word:')
word = original.lower()
first = word[0]
if len(original) > 0 and original.isalpha():
    if word[0] in ['a','e','i','o','u']:
        new_word = word + pyg
        print new_word
    else:
        new_word = word[1:len(word)] + word[0] + pyg
        print new_word
else:
    print 'empty'