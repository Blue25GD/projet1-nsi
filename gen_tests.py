import random
import string

def write_n_numbers(n, filename="test.txt"):
    letters = string.ascii_letters
    digits = "1234567890"

    choice = random.choices
    rand_letters = random.Random().choices
    rand_digits = random.Random().choices

    with open(filename, "w", buffering=1024 * 1024) as f:
        write = f.write

        write("1\n")

        for _ in range(n):
            write(''.join(rand_letters(letters, k=16)))
            write('\n')
            write(''.join(rand_digits(digits, k=9)))
            write('\n')

        write("0\n0\n")


write_n_numbers(10**7)