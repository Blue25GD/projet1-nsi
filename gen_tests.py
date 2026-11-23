#!/bin/python3

import random
import string


def generate_tests(n):
    letters = string.ascii_letters
    digits = string.digits

    rand_letters = random.Random().choices
    rand_digits = random.Random().choices

    names = []

    # Sequential write tests
    with open("write_test.txt", "w", buffering=1024 * 1024) as f:
        write = f.write
        write("1\n")

        for _ in range(n):
            name = ''.join(rand_letters(letters, k=16))
            number = ''.join(rand_digits(digits, k=9))

            names.append(name)

            write(name)
            write("\n")
            write(number)
            write("\n")

        write("0\n0\n")

    # Sequential read tests, using previously written names
    with open("read_test.txt", "w", buffering=1024 * 1024) as f:
        write = f.write
        write("2\n")

        for name in names:
            write(name)
            write("\n")

        write("0\n0\n")


if __name__ == "__main__":
    generate_tests(10 ** 6)
