#!/usr/bin/env python

import numpy as np
import sys


def loadtxt(file, delimiter=','):
    with open(file, 'r') as f:
        return [list(map(int, line[:-1].split(delimiter))) for line in f]


def getBiclusterMean(bicluster, dataMatrix):
    numRows = len(bicluster[0])
    numCols = len(bicluster[1])
    total_sum = np.sum(dataMatrix[np.ix_(bicluster[0], bicluster[1])])

    return total_sum / (numRows * numCols)


def getBiclusterVariance(bicluster, matrix):
    numRows = len(bicluster[0])
    numCols = len(bicluster[1])
    biclusterMean = getBiclusterMean(bicluster, matrix)

    total_sum = 0
    for row in bicluster[0]:
        for col in bicluster[1]:
            deviation = matrix[row][col] - biclusterMean
            total_sum += deviation * deviation
    return total_sum / (numRows * numCols)


def get_quality(bicluster, variance):
    numRows = len(bicluster[0])
    numCols = len(bicluster[1])
    return np.log(numRows * numCols) / variance


if __name__ == '__main__':
    rows_filename = sys.argv[1]
    cols_filename = sys.argv[2]
    dataMatrix_filename = sys.argv[3]
    rows = loadtxt(rows_filename)
    cols = loadtxt(cols_filename)
    dataMatrix = np.loadtxt(dataMatrix_filename, delimiter=',')
    biclusters = np.array(list(zip(rows, cols)))

    results = []
    print(dataMatrix.shape)
    for i, bicluster in enumerate(biclusters):
        var = getBiclusterVariance(bicluster, dataMatrix)
        quality = get_quality(bicluster, var)
        results.append((quality, var, len(bicluster[0]), len(bicluster[1])))

    total = 0
    for i, bicluster in enumerate(sorted(results, reverse=True)):
        if bicluster[0] != float('inf'):
            print('Bicluster ' + str(i) + ':')
            print('Number of rows: ' + str(bicluster[2]))
            print('Number of columns: ' + str(bicluster[3]))
            print('Variance: ' + str(bicluster[1]))
            print('Quality index: ' + str(bicluster[0]))
            print()
            total += 1
        if total == 4:
            break
