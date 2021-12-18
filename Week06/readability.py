from cs50 import get_string

s = get_string("Text: ").strip()
words_count, letters_count, sentences_count = 0, 0, 0

for i in range(len(s)):
    if (i == 0 and s[i] != ' ') or (i != len(s) - 1 and s[i] == ' ' and s[i + 1] != ' '):
        words_count +=1
    if s[i].isalpha():
        letters_count += 1
    if s[i] == '.' or s[i] == '?' or s[i] == '!':
        sentences_count += 1


_l = letters_count / words_count * 100
_s = sentences_count / words_count * 100
index = round(0.0588 * _l - 0.296 * _s - 15.8)
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")