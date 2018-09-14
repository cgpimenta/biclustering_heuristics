
import sys


def read_csv(filename, sep=',', skiprows=0, skipcols=0):
    matrix = []
    with open(filename, 'r') as f:
        for i in range(skiprows):
            f.readline()
        matrix = [list(line.split(sep)[skipcols:]) for line in f]

    return matrix


def save_csv(matrix, output_filename, sep=','):
    with open(output_filename, 'w') as f:
        for row in matrix:
            f.write(sep.join(row))


input_filename = sys.argv[1]
output_filename = sys.argv[2]
skiprows = int(sys.argv[3])
skipcols = int(sys.argv[4])


save_csv(read_csv(input_filename, skiprows=skiprows, skipcols=skipcols),
         output_filename)
